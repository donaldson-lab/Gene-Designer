# KnotSeeker: heuristic pseudoknot detection in long RNA sequences
# Jana Sperschneider
# Amitava Datta

# Copyright (C) 2007-2008 Jana Sperschneider
# Send comments/bug reports to: Jana Sperschneider <janaspe@csse.uwa.edu.au>

# Copyright

# KnotSeeker is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# KnotSeeker is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with KnotSeeker.  If not, see <http://www.gnu.org/licenses/>.
 
# Permission is granted for research, educational, and commercial use
# and modification so long as 1) the package and any derived works are
# not redistributed for any fee, other than media costs, 2) proper
# credit is given to the authors.

# If you want to include this software in a commercial product, please contact 
# the authors.

import os
import sys

# Method to generate RNAeval input file
def structure_file(stem_list):
    fpath = "stem_structure.txt"
    stem_structure = file(fpath,'w')
    for i in range(0,len(stem_list),2):
        header = stem_list[i]
        seq = stem_list[i+1]
        indices = header.split()
        s = ""
        # Hairpin loops
        if len(indices) < 6:
            if int(indices[4])-2*int(indices[3]) >= 3:
                for i in range(int(indices[3])):
                    s += "("
                for j in range(int(indices[4])-2*int(indices[3])):
                    s += ":"
                for k in range(int(indices[3])):
                    s += ")"
                stem_structure.writelines(header)
                stem_structure.write("\n")
                stem_structure.writelines(seq)
                stem_structure.write("\n")
                stem_structure.writelines(s)
                stem_structure.write("\n")
            if int(indices[4])-2*int(indices[3]) <= 2:
                if int(indices[3]) > 3:
                    for i in range(int(indices[3])-1):
                        s += "("
                    for j in range(int(indices[4])-2*int(indices[3])+2):
                        s += ":"
                    for k in range(int(indices[3])-1):
                        s += ")"
                header_new = indices[0] +" "+ indices[1] +" "+ indices[2] +" "+ str(int(indices[3])-1) +" "+indices[4]
                stem_structure.writelines(header_new)
                stem_structure.write("\n")
                stem_structure.writelines(seq)
                stem_structure.write("\n")
                stem_structure.writelines(s)
                stem_structure.write("\n")                
        # Bulge loops 
        if len(indices) > 6:
            stem_structure.writelines(header)
            stem_structure.write("\n")
            stem_structure.writelines(seq)
            stem_structure.write("\n")
            if indices[4] == 'r':       
                for i in range(int(indices[5])+int(indices[6])):
                    s += "("
                for j in range(int(indices[2])-int(indices[1])+1-2*int(indices[3])-1):
                    s += ":"
                for k in range(int(indices[6])):
                    s += ")"
                s += ":"
                for k in range(int(indices[5])):
                    s += ")"
                stem_structure.writelines(s)
                stem_structure.write("\n")
            if indices[4] == 'l':
                for k in range(int(indices[5])):
                    s += "("
                s += ":"
                for k in range(int(indices[6])):
                    s += "("
                for j in range(int(indices[2])-int(indices[1])+1-(2*int(indices[3]))-1):
                    s += ":"
                for i in range(int(indices[3])):
                    s += ")"                         
                stem_structure.writelines(s)
                stem_structure.write("\n")
    stem_structure.close()
    return

# GUUGle returns duplicates, therefore we need a method to remove these
def remove_duplicates(hloops):
    hloops_new = hloops[:]
    for i in range(0,len(hloops)-1,2):
        hloops_new.remove(hloops[i])
    return hloops_new

# Find bulge loops, given list of stems
def bulges(stem_list):
    stem_bulges_list = stem_list[:]
    for i in range(0,len(stem_list)-2,2):
        element1 = stem_list[i]
        seq = stem_list[i+1]
        str(element1)
        x = element1.split()
        for j in range(i,len(stem_list),2):
            element2 = stem_list[j]
            str(element2)
            y = element2.split()
            if int(y[1]) - int(x[1]) - int(x[3]) > 3 or int(x[2]) < int(y[2]):
                break
            else:
                # simple bulge loops
                if int(x[1])+int(x[3]) == int(y[1]):      # bulge to the right
                    if int(x[2])-int(x[3]) - 1 == int(y[2]):
                        header = str(x[0])+" "+str(x[1])+" "+str(x[2])+" "+str(int(x[3])+int(y[3]))+" "+'r'+" "+str(x[3])+" "+str(y[3])
                        index = stem_bulges_list.index(element1)
                        stem_bulges_list.insert(index+2,header)
                        stem_bulges_list.insert(index+3,seq)
                if int(x[1])+int(x[3])-1 + 2 == int(y[1]):      # bulge to the left
                    if int(x[2])-int(x[3])+ 1 - 1 == int(y[2]):
                        header = str(x[0])+" "+str(x[1])+" "+str(x[2])+" "+str(int(x[3])+int(y[3]))+" "+'l'+" "+str(x[3])+" "+str(y[3])
                        index = stem_bulges_list.index(element1)
                        stem_bulges_list.insert(index+2,header)
                        stem_bulges_list.insert(index+3,seq)    
                # bulge loops with an overlap
                if int(x[1])+int(x[3])-1 == int(y[1]):          # bulge to the right
                    if int(x[2])-int(x[3])+1 - 1 == int(y[2]):
                        header = str(x[0])+" "+str(x[1])+" "+str(x[2])+" "+str(int(x[3])+int(y[3])-1)+" "+'r'+" "+str(x[3])+" "+str(int(y[3])-1)
                        index = stem_bulges_list.index(element1)
                        stem_bulges_list.insert(index+2,header)
                        stem_bulges_list.insert(index+3,seq) 
                if int(x[1])+int(x[3])-1+1 == int(y[1]):        # bulge to the left
                    if int(x[2])-int(x[3]) == int(y[2]):
                        header = str(x[0])+" "+str(x[1])+" "+str(x[2])+" "+str(int(x[3])+int(y[3])-1)+" "+'l'+" "+str(int(x[3])-1)+" "+str(y[3])
                        index = stem_bulges_list.index(element1)
                        stem_bulges_list.insert(index+2,header)
                        stem_bulges_list.insert(index+3,seq)  
    return stem_bulges_list

# Keep only those stems with energy lower than +2.0 kcal/mol
def stem_list_func(stem_list):
    stems_enf = []
    for i in range(0,len(stem_list),3):
        header = stem_list[i]
        seq = stem_list[i+1]
        structure_energy = stem_list[i+2]
        seq = seq.strip()
        field = header.split()
        stemlength = int(field[3])
        info = structure_energy.split()
        if len(info) > 2:
            energy = info[2]
            energy = float(str(energy)[0:len(energy)-1])
        else:
            energy = info[1]
            energy = float(str(energy)[1:len(energy)-1])
        
        #### FIRST HEURISTIC #####
        if energy < 2.0:
            stems_enf.append(header)
            stems_enf.append(seq)
            stems_enf.append(energy)
    return stems_enf

#### Hairpin Filter ####
def mycmp(first, second):
    return cmp(first[1], second[1])

def parse_stems(stems_enf):
    list = []
    for i in range(0,len(stems_enf),3):
        header = stems_enf[i]
        field = header.split()
        firstindex = int(field[1])
        secondindex =  int(field[2])
        stemlength = int(field[3])
        index = field[4]
        energy = float(stems_enf[i+2])
        if index == 'r':
            entry = (firstindex,secondindex,stemlength,energy,'b')
        elif index == 'l':
            entry = (firstindex,secondindex,stemlength,energy,'b')    
        else:
            entry = (firstindex,secondindex,stemlength,energy,'n')
        list.append(entry) 
    list_result = list[:]

    # Rule 1
    x = len(list)
    for i in range(x):
        for j in range(i+1,x):
            if list[i][0] == list[j][0]:
                if list[i][3] < list[j][3]:
                    if abs(list[j][3] - list[i][3]) >= 0.0:
                        if list[j][4] == 'n':
                            if list[i][4] == 'n':
                                if list[j] in list_result:
                                    list_result.remove(list[j])

    list_second = []

    for i in range(len(list_result)):
        list_second.append(list_result[i])

    list_result.sort(mycmp)

    # Rule 2
    x = len(list_result)
    for i in range(x):
        for j in range(i+1,x):
            if list_result[i][1] == list_result[j][1]:
                if list_result[i][3] > list_result[j][3]:
                    if abs(list_result[j][3] - list_result[i][3]) >= 0.0:
                        if list_result[j][4] == 'n':
                            if list_result[i][4] == 'n':
                                if list_result[i] in list_second:
                                    list_second.remove(list_result[i])

    a = frozenset(list_second)
    result = []
    for element in frozenset(a):
        result.append(element)
    result.sort()

    #### Second round ####

    list_second = list[:]
    list_second.sort(mycmp)
    list_third = list[:]

    # Rule 2
    x = len(list_second)
    for i in range(x):
        for j in range(i+1,x):
            if list_second[i][1] == list_second[j][1]:
                if list_second[i][3] > list_second[j][3]:
                    if abs(list_second[j][3] - list_second[i][3]) >= 0.0:
                        if list_second[j][4] == 'n':
                            if list_second[i][4] == 'n':
                                if list_second[i] in list_third:
                                    list_third.remove(list_second[i])

    list_result = list_third[:]

    # Rule 1
    x = len(list_third)
    for i in range(x):
        for j in range(i+1,x):
            if list_third[i][0] == list_third[j][0]:
                if list_third[i][3] < list_third[j][3]:
                    if abs(list_third[j][3] - list_third[i][3]) >= 0.0:
                        if list_third[j][4] == 'n':
                            if list_third[i][4] == 'n':
                                if list_third[j] in list_result:
                                    list_result.remove(list_third[j])

    b = frozenset(list_result)
    list = []
    for element in frozenset(b):
        list.append(element)
    list.sort()
    c = a.union(b)

    list = []
    for element in frozenset(c):
        list.append(element)
    list.sort()
    return list

#### Pseudoknot Construction ####

def build_pseudoknots(list):
    pseudoknot_intervals = []
    for x in range(len(list)-1):
        i = list[x][0]
        j = list[x][1]
        stemlength1 = list[x][2]
        energy1 = list[x][3]
        for y in range(x,len(list)):
            k = list[y][0]
            l = list[y][1]
            stemlength2 = list[y][2]
            energy2 = list[y][3]
            if (float(energy1)+float(energy2)) < -2.5:
                # DEFINE LOOP1, between 0 and 20
                looplength1 = k - (i+stemlength1-1) - 1
                if looplength1 >= 0 and looplength1 <= 20:                
                    #DEFINE LOOP2, between 0 and 35
                    looplength2 = (j-stemlength1+1) - (k+stemlength2-1) - 1
                    if looplength2 <= 35 and looplength2 >= -3:
                        # DEFINE LOOP3, between 0 and 75
                        looplength3 = (l-stemlength2+1) - j - 1
                        if looplength3 <= 75:
                            if looplength3 >= 0:
                                if l-i+1 > 15:
                                    string = str(i)+" "+str(l)+" : "+str(i)+" "+str(j)+" "+str(stemlength1)+" "+str(k)+" "+str(l)+" "+str(stemlength2)+" "+str((float(energy1)+float(energy2)))
                                    pseudoknot_intervals.append(string)
    return pseudoknot_intervals
                            
# Write file with filtered hairpin and bulge loops with free energy < 2.0 kcal/mol
def parsed_stems(list,files,output):
    for x in range(len(list)):
        element = list[x]
        i = int(element[0])
        j = int(element[1])
        for y in range(0,len(files),3):
            header = files[y]
            seq = files[y+1]
            energy = float(files[y+2])
            info = header.split()
            k = info[1].strip()
            l = info[2].strip()   
            if int(k) == i:
                if int(l) == j:
                    #### SECOND HEURISTIC ####
                    if float(energy) < 2.0:
                        output.writelines(str(header))
                        output.writelines((str(seq),'\n'))
                        output.writelines((str(energy),'\n'))

# Write fasta file for pknotsRG input with potential pseudoknot sequence fragments
def fasta(pseudoknot_intervals,sequence,output):
    for i in range(len(pseudoknot_intervals)):
        header = pseudoknot_intervals[i]
        field = header.split()
        firstindex = int(field[0])
        secondindex =  int(field[1])
        i = int(field[3])
        j = int(field[4])
        stemlength1 = int(field[5])
        k = int(field[6])
        l = int(field[7])
        stemlength2 = int(field[8])
        length1 = j-i+1
        length2 = l-k+1
        output.write('> ')
        output.writelines((str(firstindex),' '))
        output.writelines((str(secondindex),' '))
        output.writelines((str(i),' '))
        output.writelines((str(j),' '))
        output.writelines((str(stemlength1),' '))
        output.writelines((str(k),' '))
        output.writelines((str(l),' '))
        output.writelines((str(stemlength2),'\n'))
        output.write(sequence[firstindex-1:secondindex])
        output.write('\n')
    output.close()        

# Scan GUUGle output file and extract stem regions
def script(fasta_file):
    f = open('guugle_output.txt','r')
    list = []  
    for line in f:
        str(line)
        if line.startswith("O") == False:
            if line.startswith("5") == False:
                if line.startswith("3") == False:
                    if line.startswith("Ma") == True:
                        s = ""
                        at = line.find("at ")
                        line_sub = line[0:16]
                        for n in line_sub:
                            if n in '1234567890':
                                s += n
                        if s.isdigit() == True:
                            list.append(int(s))

                        s = ""
                        vs = line.find("vs")                        
                        line_sub = line[at:vs]
                        for n in line_sub:
                            if n in '1234567890':
                                s += n
                        if s.isdigit() == True:
                            list.append(int(s))
                            
                        s = ""
                        line_sub = line[vs:]
                        at = line_sub.find("at ")
                        line_sub2 = line_sub[at:]
                        for n in line_sub2:
                            if n in '1234567890':
                                s += n
                        if s.isdigit() == True:
                            list.append(int(s)) 
    f.close()

    # One GUUGle output entry has three numbers i.e. stemlength and indices i,j
    # Generate a list of all hairpin loops from the GUUGle output
    hloops = []
    for i in range(0,len(list),3):
        stemlength = list[i]
        firstindex = list[i+1]
        secondindex = list[i+2]
        if firstindex-secondindex >= 6:
            triple = (secondindex,firstindex+stemlength-1,stemlength)
            hloops.append(triple)
        if secondindex-firstindex >= 6:
            triple = (firstindex,secondindex+stemlength-1,stemlength)
            hloops.append(triple)
    hloops.sort()
    hloops = remove_duplicates(hloops)
    # Generate a list of hairpin and bulge loops
    stem_list = []
    
    for i in range(len(hloops)):
        header = "> "+str(hloops[i][0])+" "+str(hloops[i][1])+" "+str(hloops[i][2])+" "+str(hloops[i][1]-hloops[i][0]+1)
        sequence = seq[hloops[i][0]-1:hloops[i][1]]
        stem_list.append(header)
        stem_list.append(sequence)

    stem_list = bulges(stem_list)
    structure_file(stem_list)

    string = "cat" + " " + "stem_structure.txt | ./ViennaRNA-1.8.4/Progs/RNAeval"
    eval = os.popen(string)
    
    energy = eval.read()
    fpath = "stems_energy.txt"
    output = file(fpath,'w')
    output.write(energy)    
    output.close()
    output = file(fpath,'r')
    
    stem_list = []
    for i in output:
        stem_list.append(i)

    stems_enf = stem_list_func(stem_list)

    list = parse_stems(stems_enf)

    f = open(fasta_file,'r')
    id = f.readline()
    sequence = f.readline()
    f.close()

    pseudoknot_intervals = build_pseudoknots(list)
    fpath = "pknotsRG_input.txt"
    output = file(fpath,'w')
    fasta(pseudoknot_intervals,sequence,output)
    output.close()

    fpath = "hairpin_bulge.txt"
    output = file(fpath,'w')
    parsed_stems(list,stems_enf,output)
    output.close()

    string = "pknotsRG-1.3/src/pknotsRG -p 9 -n 0.3 -F" + " " + "pknotsRG_input.txt"
    result = os.popen(string)
    pseudoknots = result.read()

    fpath = "pknotsRG_output.txt"
    output = file(fpath,'w')
    output.write(pseudoknots)    
    output.close()

# Step2: Given the pknotsRG ouput file, apply the pseudoknot filter and minimum weight independent set calculation 

# Pseudoknot Filter
def pseudoknot(file):
    pseudoknots = []
    for i in range(0,len(file)-1,3):
        header = file[i]
        field = header.split()
        firstindex = int(field[1])
        secondindex =  int(field[2])
        stem1_end = int(field[4])
        stemlength1 = int(field[5])
        stem2_start = int(field[6])
        stemlength2 = int(field[8])
        structure = file[i+2]
        info = structure.split()
        structure = info[0]
        energy = info[1][1:len(info[1])-1]
        length = len(structure)

        if structure.find("[") >= 0 and structure.find("[") <= 1:                         # Structure starts with "[" or ".["
            if structure[len(structure)-1] == "}" or structure[len(structure)-2] == "}":  # Structure ends with "}" or ".}"
                if stem1_end - (structure.rfind("]") + firstindex) <= 1:                  # Second part of stem S1 is at correct position
                    if stem1_end - (structure.rfind("]") + firstindex) >= -1:    
                        if stemlength1 - structure.find(".",1,len(structure)) <= 2:                        # Stemlength S1 is correct
                            if stemlength1 - structure.find(".",1,len(structure)) >= 0:
                                if structure.find("{") + firstindex - stem2_start <= 1:          # First part of stem S2 is at correct position
                                    if structure.find("{") + firstindex - stem2_start >= -1: 
                                        if structure[length-stemlength2+1] == "}" or (structure[length-stemlength2+1] == "." and structure[length-stemlength2+3] == "}"):    # Stemlength S2 is correct
                                            if length <= 90:
                                                ##### HEURISTIC #####
                                                if float(energy) <= 0:
                                                    if structure[stem1_end:length].find("[") < 0:   # no two pseudoknots in same sequence fragment
                                                        if structure.find("[") == 0:                # no basepair missing at start of stem S1
                                                            if structure.count("["[0:stemlength1+1]) >= stemlength1 - 3:    
                                                                if structure[len(structure)-1] == "}":
                                                                    if structure[len(structure)-stemlength2:len(structure)].count("}") >= stemlength2-3:
                                                                        pseudoknots.append(header)
                                                                        pseudoknots.append(structure)
                                                                        pseudoknots.append(energy)
                                                                elif structure[len(structure)-1] == ".": # one basepair missing at end of pseudoknot
                                                                    header = "> "+str(int(firstindex))+" "+str(int(secondindex)-1)+" "+str(field[3])+" "+str(stem1_end)+" "+str(stemlength1)+" "+str(stem2_start)+" "+str(field[7])+" "+str(stemlength2)
                                                                    if structure[len(structure)-stemlength2:len(structure)].count("}") >= stemlength2-2:
                                                                        pseudoknots.append(header)
                                                                        pseudoknots.append(structure[0:len(structure)-1])
                                                                        pseudoknots.append(energy)                                                                   
                                                        elif structure.find("[") == 1:              # one basepair missing at start of stem S1   
                                                            header = "> "+str(int(firstindex)+1)+" "+str(secondindex)+" "+str(field[3])+" "+str(stem1_end)+" "+str(stemlength1)+" "+str(stem2_start)+" "+str(field[7])+" "+str(stemlength2)
                                                            if structure.count("["[0:stemlength1]) >= stemlength1 - 1:
                                                                if structure[len(structure)-1] == "}":
                                                                    if structure[len(structure)-stemlength2:len(structure)].count("}") >= stemlength2-3:
                                                                        pseudoknots.append(header)
                                                                        pseudoknots.append(structure[1:len(structure)])
                                                                        pseudoknots.append(energy)
                                                                elif structure[len(structure)-1] == ".":
                                                                    if structure[len(structure)-stemlength2:len(structure)].count("}") >= stemlength2-2:
                                                                        pseudoknots.append(header)
                                                                        pseudoknots.append(structure)
                                                                        pseudoknots.append(energy)
    return pseudoknots

# MWIS calculation, create sorted endpoints list
def create_sorted_endpointlist(result):
    sorted_list = []
    firstpoint = ()
    secondpoint = ()
    for i in range(len(result)):
        element = result[i]
        firstpoint = (int(element[0]),'l',float(element[4]),int(i+1))
        sorted_list.append(firstpoint)
        secondpoint = (int(element[1]),'r',float(element[4]),int(i+1))
        sorted_list.append(secondpoint)
    sorted_list.sort()
    for i in range(len(sorted_list)):
        for j in range(i+1,len(sorted_list)):
            if int(sorted_list[i][0]) == int(sorted_list[j][0]):
                if result[sorted_list[i][3]-1][2] > 3:
                    if sorted_list[i][1] < sorted_list[j][1]:       #right endpoints first, than left endpoints 
                        temp = sorted_list[i]
                        sorted_list[i] = sorted_list[j]
                        sorted_list[j] = temp
                if result[sorted_list[j][3]-1][2] > 3:
                    if sorted_list[i][1] < sorted_list[j][1]:       #right endpoints first, than left endpoints
                        temp = sorted_list[i]
                        sorted_list[i] = sorted_list[j]
                        sorted_list[j] = temp
                else:
                    if sorted_list[i][1] > sorted_list[j][1]:       #left endpoints first, than right endpoints
                        temp = sorted_list[i]
                        sorted_list[i] = sorted_list[j]
                        sorted_list[j] = temp
    return sorted_list

# MWIS calculation 
def MWIS(list,sorted_endpointlist):
    value = []
    #Step 1
    temp_max = 0.0
    Smax1 = []
    last_interval = 0
    for j in range(0,len(sorted_endpointlist)):
        value.insert(j,0.0)
    #Step 2
    for i in range(0,len(sorted_endpointlist)):
        if sorted_endpointlist[i][1] == 'l':
            c = sorted_endpointlist[i][3] - 1
            value[c] = temp_max + sorted_endpointlist[i][2]
        if sorted_endpointlist[i][1] == 'r':
            c = sorted_endpointlist[i][3] - 1
            if value[c] <= temp_max:
                temp_max = value[c]
                last_interval = c    
    #Step 3
    Smax1.insert(0,list[last_interval])
    temp_max = temp_max - list[last_interval][4]

    
    for j in range(last_interval-1,-1,-1):
        if round(value[j],2) == round(temp_max,2):
            if list[j][1] -1 <= list[last_interval][0]:    
                Smax1.append(list[j])
                temp_max = temp_max - list[j][4]
                last_interval = j
    return Smax1
    
# Function for finding nested intervals, given a right endpoint
def find_nested(tuple1,list_init):
    result = []
    interval_index = tuple1[3]
    interval = list_init[interval_index-1]
    interval_left = interval[0]+interval[2]-1
    interval_right = interval[1]-interval[3]+1
    for i in range(0,len(list_init)):
        compare_interval = list_init[i]
        if compare_interval[0] >= interval_left:                              
            if compare_interval[1] <= interval_right:                            
                result.append(compare_interval)
    return result

def print_output(result_large,list_energy,list_information,file,detected_pks):
    result = list_energy.index(result_large)
    entry = list_information[result*2+1]
    if len(entry) > 0:        
        for i in range(len(entry)-1,-1,-1):
            if entry[i][5] == 'pk':                     # print pseudoknots only
                detected_pks.append(entry[i][0])
                detected_pks.append(entry[i][1])
                detected_pks.append(entry[i][4])
                detected_pks.append(file[entry[i][6]+1])
            result = list_energy.index(entry[i])
            if len(list_information[result*2+1]) > 0:
                print_output(entry[i],list_energy,list_information,file,detected_pks)
    return detected_pks

# MWIS
def methode(file):
    list = []
    detected_pks = []
    for i in range(0,len(file),3):
        header = str(file[i])
        field = header.split()
        energy = float(file[i+2])
        if len(field) == 5:
            firstint = int(field[1])
            secondint =  int(field[2])
            stemlength1 = int(field[3])
            quadruple = (firstint,secondint,stemlength1,stemlength1,energy,"hp")
            list.append(quadruple)
        elif len(field) == 7:
            firstint = int(field[1])
            secondint =  int(field[2])
            stemlength1 = int(field[3])
            quadruple = (firstint,secondint,stemlength1,stemlength1,energy,"hp","b")
            list.append(quadruple)
        elif len(field) == 9: 
            firstint = int(field[1])
            secondint =  int(field[2])
            stemlength1 = int(field[5])
            stemlength2 = int(field[8])
            quadruple = (firstint,secondint,stemlength1,stemlength2,energy,"pk",i)
            list.append(quadruple)
    list.sort()
    list_information = list[:]

    for i in range (0,len(list_information)*2,2):
        list_information.insert(i+1,[])

    list_init = list[:]
    sorted_endpoint_list = create_sorted_endpointlist(list)

    for i in range(len(sorted_endpoint_list)):
        sorted_endpointlist = []
        list = []
        index = 0
        if sorted_endpoint_list[i][1] == 'r':
            index = sorted_endpoint_list[i][3]
            if list_init[index-1][5] == 'hp':
                list = find_nested(sorted_endpoint_list[i],list_init)
                if len(list) > 0:
                    sorted_endpointlist = create_sorted_endpointlist(list)
                    result = MWIS(list, sorted_endpointlist)
                    sub_energy = list_init[index-1][4]                
                    if len(result) > 0:
                        sub_energy = sub_energy - 1.5 # NESTING HEURISTIC ASSUMPTION
                    for j in range(len(result)):    # add sub-energy
                        sub_energy = sub_energy + result[j][4]
                    list_information[list_information.index(list_init[index-1])+1] = result
                    list_init[index-1] = (list_init[index-1][0],list_init[index-1][1],list_init[index-1][2],list_init[index-1][3],sub_energy,list_init[index-1][5])
    list_energy = list_init[:]

    ### MAIN MWIS CALCULATION ###
    sorted_endpointlist = create_sorted_endpointlist(list_energy)
    result = MWIS(list_energy, sorted_endpointlist)
        
    # print pseudoknots only
    for j in range(len(result)):
        if result[j][5] == 'pk':
            detected_pks.append(result[j][0])
            detected_pks.append(result[j][1])
            detected_pks.append(result[j][4])
            detected_pks.append(file[result[j][6]+1])
   
    for i in range(len(result)):
        result_large = result[i]
        pk_list = []
        pk_list = print_output(result_large,list_energy,list_information,file,detected_pks)
    
    return pk_list

# Replace square brackets [ ] with ( )
# Replace curly brackets { } with [ ]  
def pseudoviewer(FINAL_sorted):
    FINAL_new = []
    for j in range(len(FINAL_sorted)):
        FINAL_new.append(FINAL_sorted[j][0])
        FINAL_new.append(FINAL_sorted[j][1])
        FINAL_new.append(FINAL_sorted[j][2])
        str(FINAL_sorted[j][3])
        pk1 = FINAL_sorted[j][3].replace('[','(')
        pk2 = pk1.replace(']',')')
        pk3 = pk2.replace('{','[')
        pk4 = pk3.replace('}',']')
        FINAL_new.append(pk4)
    return FINAL_new

############################################
# Main method, run KnotSeeker with sequence
############################################
seq_file = sys.argv[1]
f = open(seq_file,'r')
seq_id = f.readline()
seq = f.readline()

# Call GUUGle and write output in temporary file
print "Pseudoknot detection starts..."
guugle_path = seq_file
string = "./guugle/guugle -d 3 -l 50000" +" "+ guugle_path +" "+ guugle_path
guugle = os.popen(string)
result = guugle.read()
guugle_file = file('guugle_output.txt','w')
guugle_file.write(result)   
guugle_file.close()
script(seq_file)

f = open('pknotsRG_output.txt','r')
files = f.readlines()
f.close()
pseudoknots = pseudoknot(files)
f = open('hairpin_bulge.txt','r')
files = f.readlines()
f.close()

for i in range(len(pseudoknots)):
    files.append(pseudoknots[i])
FINAL = []
FINAL_sorted = []

if len(files) > 0:
    FINAL = methode(files)
    if len(FINAL) > 0:
        for i in range(0,len(FINAL),4):
            pseudoknot = ()
            pseudoknot = (FINAL[i],FINAL[i+1],FINAL[i+2],FINAL[i+3])
            FINAL_sorted.append(pseudoknot)
            FINAL_sorted.sort()
    FINAL = []
    FINAL = pseudoviewer(FINAL_sorted) 
    print "Detected pseudoknots for", seq_id[1:]
    for i in range(0,len(FINAL),4):
        print "Position: ", FINAL[i], "...", FINAL[i+1]
        print seq[FINAL[i]-1:FINAL[i+1]]
        print FINAL[i+3]
        print "Energy calculated by pknotsRG:", FINAL[i+2], "kcal/mol" "\n"
    else:
        print "No pseudoknots were detected for",seq_id[1:]
else:
    print "No pseudoknots were detected for",seq_id[1:]
sys.exit(0)