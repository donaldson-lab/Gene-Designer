'''
Created on Nov 3, 2010

@author: virushunter2
'''
import os
import re
import shutil

def model(fasta, path):
    with open(fasta) as file:
        template = file.readline()
        template = template.split('>')[1]
        template = template.split('\n')[0]
        pdb = path + template + '.pdb'
        shutil.copy(pdb, os.getcwd())
        template_seq = file.readline()
        seq = file.readline()
        seq = seq.split('>')[1]
        seq = seq.split('\n')[0]
        sequence = seq
        seq = seq + '_000000'
        aln_file = seq +'.ali'
    
    
    with open(pdb) as pdb:
        prev_res_num = -100
        pdb_seq = ''
        residue_list = []
        aminoacids = {'ALA': 'A', 'ARG': 'R', 'ASN': 'N',
                             'ASP': 'D', 'CYS': 'C', 'GLU': 'E',
                             'GLN': 'Q', 'GLY': 'G', 'HIS': 'H',
                             'ILE': 'I', 'LEU': 'L', 'LYS': 'K',
                             'MET': 'M', 'PHE': 'F', 'PRO': 'P',
                             'SER': 'S', 'THR': 'T', 'TRP': 'W',
                             'TYR': 'Y', 'VAL': 'V'}
        for line in pdb:
            if line.startswith('ATOM'):
                res_name = line[17:20].replace(' ', '')
                res_num = line[22:26].replace(' ', '')
                if res_num != prev_res_num:
                    pdb_seq = pdb_seq + aminoacids[res_name]
                    residue_list.append(res_num)
                prev_res_num = res_num
            elif line.startswith('HETATM'):
                res_num = line[22:26].replace(' ', '')
                if (res_num != prev_res_num):
                    pdb_seq = pdb_seq + '-'
                    residue_list.append(res_num)
                prev_res_num = res_num
    
        start = re.search(template_seq[:5], pdb_seq).start()
        
        first = int(residue_list[re.search(template_seq[:5], pdb_seq).start()])
        last = first + len(template_seq) -2
    command = path + 'proba2pir.pl' 
    os.system('probA --prot --noPS --score_matrix blosom_62 -T 1 -N 1 < %s > probA.out' %fasta)
    os.system('perl %s -if probA.out -of %s -structure u -first %s -last %s' %(command, sequence, first, last))
    os.remove('proba.out')
    
    with open(aln_file) as aln:
            name1 = aln.readline()
            info1 = aln.readline()
            sequence = aln.readline()
            name2 = aln.readline()
            info2 = aln.readline()
            sequence2 = aln.readline()
    
    index = 0
    for char in sequence:
        if char == '-':
            pdb_seq = pdb_seq[:index+start] +'-' +pdb_seq[index+start:]
        elif char == '*':
            pdb_seq = pdb_seq[:index+start] + '*' + '\n'
        index += 1
    pdb_seq = pdb_seq[start:]
    
    tmp = open('tmp.txt', 'w')
    tmp.write(name1)
    tmp.write(info1)
    tmp.write(pdb_seq)
    tmp.write(name2)
    tmp.write(info2)
    tmp.write(sequence2)
    tmp.close()
    os.remove(aln_file)
    pdb = os.getcwd()+'/' +template + '.pdb'
    os.rename('tmp.txt', aln_file)
                
    os.system('mod9v8 model.py %s %s %s' %(aln_file, template, seq))
    os.system('/Applications/MacPyMOL.app/Contents/MacOS/MacPyMOL *.pdb -d')

