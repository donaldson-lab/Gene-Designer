'''
Created on Jul 12, 2010

@author: Doug Crandell
'''
import os
import build_re_db
import codon_usage_db
import vectors_db
import linkers_db
import template_db
import rna_folding
import sqlite3
import Bio
from Bio.Seq import Seq
from Bio.Alphabet import generic_dna
import sys
import wx
import wx.grid as grd
import random
import re
import math
import rna_format_conversion as rfc
import help
import homology
import KnotSeeker

ID_ENZYMEREF = 101
ID_CODONREF = 102
ID_DB = 103
ID_ECOLIK12 = 104
ID_TOX = 105
ID_ABOUT = 106
ID_EXIT = 107
ID_ADDENZYME = 108
ID_ADDORG = 109
ID_ADDVECTOR = 110
ID_DELETEORG = 111
ID_DELETEVECTOR = 112
ID_DELETEENZYME = 113
ID_COMMERCIALREF = 114
ID_ORF = 115
ID_UNDO = 116
ID_REDO = 117
ID_HELP = 118
ID_HOMOLOGY = 119
ID_TEMPLATES = 120
ID_NEWTEMPLATES = 121
ID_CURRENT = 122

class Search():   
    def __init__(self):
        self = self
    
    def find_pattern(self, sequence, pattern):
        pattern = pattern.upper()
        #Build a regular expression based off of the pattern and search the sequence for the target reg. exp. Allows for ambiguous nucleotides
        dna = 'ACGTU'
        target = ''
        dictionary = {'N':'[ACGTU]','R':'[AG]', 'Y': '[CT]', 'W':'[AT]','S':'[GC]','M':'[AC]', 'K':'[GT]', 'B':'[CGT]', 'D':'[AGT]', 'H':'[ACT]', 'V':'[ACG]'} #Dictionary of ambiguous bases
        for char in pattern:
            if char in dna:
                target += char
            else:
                try:
                    target += dictionary[char]
                except KeyError:
                    target = pattern
        starts = [match.start() for match in re.finditer(target, str(sequence))] #Pattern matching gets list of starting location for each match
        return starts
    
    def find_aa_motif(self, sequence, pattern):
        #Build a regular expression and search amino acid sequence for the target.  Allows for ambiguous amino acids
        aa = 'FLSYCWPHQRIMTNKVADEGZ'
        target = ''
        dictionary = {'X': '[FLSYCWPHQRIMTNKVADEGZ]'}
        pattern = pattern.upper()
        for char in pattern:
            if char in aa:
                target += char
            elif char == '*':
                target += 'Z'
            else:
                try:
                    target += dictionary[char]
                except KeyError:
                    pass
        sequence = str(sequence)
        for char in range(len(sequence)):
            if sequence[char] == '*':
                sequence = sequence[:char] + "Z" + sequence[char+1:]
        starts = [match.start() for match in re.finditer(target, str(sequence))]
        return starts  
                 
    def db_retrieve(self):
        #Retrieve list of enzymes from restriction enzyme database and build a dictionary with enzymes as keys and their target patterns as values
        enzyme_list, vector_list, pattern_dict  = [], [], {}
        connection = sqlite3.connect('re.db')
        cursor = connection.cursor()
        cursor.execute('SELECT r_enz_name, pattern FROM enzymes')
        for row in cursor:
            enzyme_list.append(row[0])
            pattern_dict[row[0]] = row[1]
        connection1 = sqlite3.connect('vectors.db')
        cursor1 = connection1.cursor()
        cursor1.execute('SELECT vector_name FROM vectors')
        for row in cursor1:
            vector_list.append(row[0])
        return enzyme_list, pattern_dict, vector_list
    
    def db_cutting_info(self, enzyme_list):
        #Retrieve cutting information from database and store it in dictionaries
        db = 're.db'
        connection = sqlite3.connect(db)
        cursor = connection.cursor()
        cut_dict, blunt_dict, down_dict, up_dict = {}, {}, {}, {}
        cursor.execute('SELECT r_enz_name, downstream_top, downstream_bottom, upstream_top, upstream_bottom, blunt FROM enzymes')
        for row in cursor:
            cutting_list = [row[1], row[2], row[3], row[4], row[5]]
            if row[0] in enzyme_list:
                cut_dict[row[0]] = cutting_list
                if str(row[1]) != '' and str(row[2]) != '':
                    down_dict[row[0]] = [row[1], row[2]]
                if str(row[3]) != '' and str(row[4]) != '':
                    up_dict[row[0]] = [row[3], row[4]]
                blunt_dict[row[0]] = row[5]
        return cut_dict, blunt_dict, down_dict, up_dict
    
    def find_sites_in(self, sequence, enz_list, left_range, right_range):
        #Find restriction sites in a specified range
        pattern_dict = self.db_retrieve()[1] #Create a dictionary of patterns with enzymes as keys
        result_list, nohit_list, start_list = [], [], []
        updict, downdict, bluntdict = {}, {}, {}
        for enz in enz_list:
            qlist, bluntlist, uplist, down_list, split_list = [], [], [], [], []
            cut = self.db_cutting_info(enz)[0] #Get enzyme cutting information
            result = self.find_pattern(str(sequence), pattern_dict[enz]) #Match pattern
            item = pattern_dict[enz]
            print "%s appears at: %s" %(item, result)
            if result == []:
                nohit_list.append(str(enz)) #If no match, add enzyme to nohitlist
            if left_range == None and right_range == None: #If no ranges specified
                if cut[enz][4] == -2:
                            for num in result:
                                split_list.append(num)
                                down_list.append([num + int(cut[enz][0]), num + int(cut[enz][1])])
                                downdict[str(enz)] = down_list
                if cut[enz][4] != -1 and cut[enz][4] == -2: #Enzyme makes blunt cut
                    for num in result:
                        bluntlist.append(num)
                        qlist.append(num + cut[enz][4])
                    bluntdict[str(enz)] = qlist
                else:
                    if cut[enz][0] == '' and cut[enz][1] == '' and cut[enz][2] == '' and cut[enz][3] == '' and cut[enz][4] == -1: #Enzyme makes blunt cut at end of pattern
                        for num in result:
                            bluntlist.append(num)
                            qlist.append(num + len(item))
                        bluntdict[str(enz)] = qlist 
                    if cut[enz][0] != '' and cut[enz][1] != '': #Enzyme cuts strands differently downstream
                        for num in result:
                            split_list.append(num)
                            down_list.append([num + int(cut[enz][0])+ len(item), num + int(cut[enz][1])+ len(item)])
                        downdict[str(enz)] = down_list
                    if cut[enz][2] != '' and cut[enz][3] != '': #Enzyme cuts strands differently upstream
                        for num in result:
                            split_list.append(num)
                            uplist.append([num - int(cut[enz][2]), num - int(cut[enz][3])])
                        updict[str(enz)] = uplist
            else: #If ranges specified
                if cut[enz][4] != -1: #Enzyme makes blunt cut
                    for num in result:
                        bluntlist.append(num)
                        q = num + cut[enz][4]
                        if q >= int(left_range) and q <= int(right_range):
                            qlist.append(q)
                    bluntdict[str(enz)] = qlist
                else:
                    if cut[enz][0] == '' and cut[enz][1] == '' and cut[enz][2] == '' and cut[enz][3] == '' and cut[enz][4] == -1: #Enzyme makes blunt cut at end of pattern
                        for num in result:
                            bluntlist.append(num)
                            q = num + len(item)
                            if q >= int(left_range) and q <= int(right_range):
                                qlist.append(q)
                        bluntdict[str(enz)] = qlist 
                    if cut[enz][0] != '' and cut[enz][1] != '': #Enzyme cuts strands differently downstream
                        for num in result:
                            split_list.append(num)
                            t = num + int(cut[enz][0])
                            b = num + int(cut[enz][1])
                            if (t >= int(left_range) and b >= int(left_range)) or (t <= int(right_range) and b <= int(right_range)):
                                down = [num + int(cut[enz][0])+ len(item), num + int(cut[enz][1])+ len(item)]
                                down_list.append(down)
                        downdict[str(enz)] = down_list
                    if cut[enz][2] != '' and cut[enz][3] != '': #Enzyme cuts strands differently upstream
                        for num in result:
                            split_list.append(num)
                            t = num - int(cut[enz][2])
                            b = num - int(cut[enz][3])
                            if (t >= int(left_range) and b >=int(left_range)) or (t <= int(right_range) and b <= int(right_range)):
                                up = [num - int(cut[enz][2]), num - int(cut[enz][3])]
                                uplist.append(up)
                        updict[str(enz)] = uplist
            if bluntlist != []:
                    result_list.append(bluntlist)
            if split_list != []:
                start_list.append(split_list)
        return result_list, bluntdict, downdict, updict, nohit_list, start_list
    
    def find_sites_out(self, sequence, enz_list, left_range, right_range):
        pattern_dict = self.db_retrieve()[1] #Get pattern dictionary
        nohit_list, result_list, start_list = [], [], []
        downdict, updict, bluntdict = {}, {}, {}
        methylation = self.find_methylation(sequence)
        for enz in enz_list:
            up_list, down_list, qlist, blunt_list, split_list = [], [], [], [], []
            cut = self.db_cutting_info(enz)[0] #Get enzyme cutting info
            result = self.find_pattern(str(sequence), pattern_dict[enz])
            item = pattern_dict[enz]
            print "%s appears at: %s" %(item, result)
            if result == []:
                nohit_list.append(str(enz))
            else:
                if left_range == None and right_range == None: #If no ranges specified
                    if cut[enz][4] == -2:
                            for num in result:
                                split_list.append(num)
                                down_list.append([num + int(cut[enz][0]), num + int(cut[enz][1])])
                                downdict[str(enz)] = down_list
                    if cut[enz][4] != -1 and cut[enz][4] != -2: #Enzyme makes blunt cut
                        for num in result:
                            blunt_list.append(num)
                            qlist.append(num + cut[enz][4])
                            bluntdict[str(enz)] = qlist  
                    else:
                        if cut[enz][0] == '' and cut[enz][1] == '' and cut[enz][2] == '' and cut[enz][3] == '' and cut[enz][4] == -1: #Enzyme makes blunt cut at end of pattern
                            for num in result: 
                                blunt_list.append(num)
                                qlist.append(num + len(item))
                                bluntdict[str(enz)] = qlist
                        if cut[enz][4] !=-2:
                            if cut[enz][0] != '' and cut[enz][1] != '': #Enzyme cuts strands differently downstream
                                for num in result:
                                    split_list.append(num)
                                    down_list.append([num + int(cut[enz][0]) + len(item), num + int(cut[enz][1]) + len(item)])
                                    downdict[str(enz)] = down_list
                            if cut[enz][2] != '' and cut[enz][3] != '': #Enzyme cuts strands differently upstream
                                for num in result:
                                    split_list.append(num)
                                    up_list.append([num - int(cut[enz][2]), num - int(cut[enz][3])])
                                    updict[str(enz)] = up_list
                else: #No ranges specified
                    if cut[enz][4] != -1: #Enzyme makes blunt cut
                        for num in result:
                            blunt_list.append(num)
                            q = num + cut[enz][4]
                            if q < int(left_range) or q > int(right_range):
                                qlist.append(q)
                    else:
                        if cut[enz][0] == '' and cut[enz][1] == '' and cut[enz][2] == '' and cut[enz][3] == '' and cut[enz][4] == -1: #Enzyme makes blunt cut at pattern end
                            for num in result:
                                q = num + len(item)
                                blunt_list.append(num)
                                if q < int(left_range) or q > int(right_range):
                                    qlist.append(q)
                                    bluntdict[str(enz)] = qlist
                        if cut[enz][0] != '' and cut[enz][1] != '': #Enzyme cuts strands differently downstream
                            for num in result:
                                split_list.append(num)
                                t = num + int(cut[enz][0])
                                b = num + int(cut[enz][1])
                                if (t < int(left_range) and b<int(left_range)) or (t > int(right_range) and b > int(right_range)):
                                    down = [num + int(cut[enz][0]) + len(item), num + int(cut[enz][1])+ len(item)]
                                    down_list.append(down)
                                    downdict[str(enz)] = down_list
                        if cut[enz][2] != '' and cut[enz][3] != '': #Enzyme cuts strands differently upstream
                            for num in result:
                                split_list.append(num)
                                t = num - int(cut[enz][2])
                                b = num - int(cut[enz][3])
                                if (t < int(left_range) and b<int(left_range)) or (t > int(right_range) and b > int(right_range)):
                                    up = [num - int(cut[enz][2]), num - int(cut[enz][3])]
                                    up_list.append(up)
                                    updict[str(enz)] = up_list
                if blunt_list != []:
                    result_list.append(blunt_list)
                if split_list != []:
                    start_list.append(split_list)
        return result_list, bluntdict, downdict, updict, nohit_list, start_list, methylation
    
    def find_methylation(self, sequence):
        methylation = {}
        dam = self.find_pattern(str(sequence), 'GATC')
        dcm = self.find_pattern(str(sequence), 'CCWGG')
        for site in dam:
            site = site + 1
            methylation[site] = 'Dam'
        for site in dcm:
            site = site + 1
            methylation[site] = 'Dcm'
        return methylation
            
class MutationPanel(wx.Panel):
    mlist = []
    def __init__(self, parent, id, searchInstance, enzyme_list, vector_list, target_list, nb, mainframe):
        wx.Panel.__init__(self, parent)
        self.name = 'Mutation Panel'
        self.frag = False
        self.search = searchInstance
        self.enzyme_list, self.vector_list, self.target_list = enzyme_list, vector_list, target_list
        self.vector_list = vector_list
        self.nb = nb
        self.mainframe = mainframe
        self.panel = wx.Panel(self)
        self.previous_seq, self.previous_vector, self.previous_aaseq = [''], [''], ['']
        self.rf = 1 #Set initial reading frame
        #Create sizers
        self.sizer = wx.FlexGridSizer(5,5,5,5)
        self.blanksizer = wx.BoxSizer(wx.HORIZONTAL)
        self.seqsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.gcsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.motifsizer = wx.BoxSizer(wx.VERTICAL)
        self.mutoptionssizer = wx.GridBagSizer(1,3)
        self.seqnumsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.nummutsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.numsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.mutrangespacer = wx.BoxSizer(wx.HORIZONTAL)
        self.mutrangesizer = wx.BoxSizer(wx.HORIZONTAL)
        self.totalmutsizer = wx.BoxSizer(wx.VERTICAL)
        self.rangeouthoriz = wx.BoxSizer(wx.HORIZONTAL)
        self.rangeoutvert = wx.BoxSizer(wx.VERTICAL)
        self.rangeinhoriz = wx.BoxSizer(wx.HORIZONTAL)
        self.rangeinvert = wx.BoxSizer(wx.VERTICAL)
        self.cutrangesizer = wx.BoxSizer(wx.VERTICAL)
        self.enzymesizer = wx.BoxSizer(wx.HORIZONTAL)
        self.cuttersizer = wx.BoxSizer(wx.VERTICAL)
        self.totalcutsizer = wx.BoxSizer(wx.VERTICAL)
        self.fraghoriz1 = wx.BoxSizer(wx.HORIZONTAL)
        self.fraghoriz2 = wx.BoxSizer(wx.HORIZONTAL)
        self.fragvert = wx.BoxSizer(wx.VERTICAL)
        self.fragmentsizer = wx.GridBagSizer(5,1)
        self.aaoptionssizer = wx.BoxSizer(wx.VERTICAL)
        self.frequencysizer = wx.BoxSizer(wx.HORIZONTAL)
        self.aamutbuttonsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.aalabelsizer = wx.BoxSizer(wx.VERTICAL)
        self.aasizer = wx.BoxSizer(wx.HORIZONTAL)
        self.aamutnumsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.aamutrangesizer = wx.BoxSizer(wx.HORIZONTAL)
        self.posdispsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.mutseqlabelsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.mutseqsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.mutseqoptionssizer =wx.BoxSizer(wx.HORIZONTAL)
        self.totalmutseqsizer = wx.BoxSizer(wx.VERTICAL)
        self.vectorsizer = wx.BoxSizer(wx.VERTICAL)
        self.vector_listbox_sizer = wx.BoxSizer(wx.VERTICAL)
        self.total_vector_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.row1sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.row2sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.row3sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.totalsizer = wx.BoxSizer(wx.VERTICAL)
        self.indelsizer = wx.BoxSizer(wx.HORIZONTAL)
        #Content relating to sequence display and sequence GC content
        self.seq_disp_label = wx.StaticText(self.panel, wx.ID_ANY,"Sequence: ")
        self.seq_disp = wx.TextCtrl(self.panel, size = (400,150), style = wx.TE_PROCESS_ENTER|wx.TE_MULTILINE)
        self.seq_disp.name = 'SeqDisp'
        self.seq_disp.Bind(wx.EVT_TEXT_ENTER, self.submit_event)
        self.seq_disp.Bind(wx.EVT_TEXT, self.translate_and_gc)
        self.seq_disp.Bind(wx.EVT_KEY_UP, self.update_seq_status)
        self.seq_disp.Bind(wx.EVT_SET_FOCUS, self.GetParent().GetParent().GetParent().on_focus)
        self.seq_gc_disp_label = wx.StaticText(self.panel, wx.ID_ANY, 'GC Content: ',)
        self.seq_gc_disp = wx.TextCtrl(self.panel, size = (50,20), style = wx.TE_READONLY)
        self.find_motif_button = wx.Button(self.panel, -1, 'Find Motif')
        self.find_motif_button.Bind(wx.EVT_LEFT_DOWN, self.find_motif)
        # Add Linkers
        self.linker_button = wx.Button(self.panel, -1, 'Add Linkers')
        self.linker_button.Bind(wx.EVT_LEFT_DOWN, self.add_linkers)
        #Vectors
        self.vector_label = wx.StaticText(self.panel, wx.ID_ANY, "Vector: ")
        self.vector_disp = wx.TextCtrl(self.panel, size = (600,125), style = wx.TE_PROCESS_ENTER|wx.TE_MULTILINE)
        self.vector_disp.name = 'VectorDisp'
        self.vector_disp.Bind(wx.EVT_TEXT_ENTER, self.submit_event)
        self.vector_disp.Bind(wx.EVT_TEXT, self.fix_vector)
        self.vector_disp.Bind(wx.EVT_KEY_UP, self.update_vector_status)
        self.vector_disp.Bind(wx.EVT_SET_FOCUS, self.GetParent().GetParent().GetParent().on_focus)
        #Cursor Display Box
        self.position_disp_label = wx.StaticText(self.panel, wx.ID_ANY, 'Cursor Positon: ')
        self.position_disp = wx.TextCtrl(self.panel, size = (60,20), style = wx.TE_PROCESS_ENTER)
        self.position_disp.Bind(wx.EVT_TEXT_ENTER, self.move_cursor)
        #Amino Acid Sequence and AA Mutations and Reading Frame along with amino acid mutation options
        self.aa_seq_label = wx.StaticText(self.panel, wx.ID_ANY, 'Amino Acid Sequence:')
        self.aa_disp = wx.TextCtrl(self.panel, size = (325,150), style = wx.TE_PROCESS_ENTER|wx.TE_MULTILINE)
        self.aa_disp.name = 'AADisp'
        self.aa_disp.Bind(wx.EVT_KEY_UP, self.update_aa_status)
        self.aa_disp.Bind(wx.EVT_TEXT, lambda evt, previous = self.previous_aaseq: self.aa_seq_value(previous))
        self.aa_disp.Bind(wx.EVT_SET_FOCUS, self.GetParent().GetParent().GetParent().on_focus)
        self.codon_freq_button = wx.Button(self.panel, -1, 'Codon Frequency')
        self.codon_freq_button.Bind(wx.EVT_LEFT_DOWN, self.codon_frequency)
        self.aa_freq_button = wx.Button(self.panel, -1, 'Amino Acid Frequency')
        self.aa_freq_button.Bind(wx.EVT_LEFT_DOWN, self.aa_frequency)
        self.reading_frame_button = wx.Button(self.panel, -1, 'Reading Frame')
        self.reading_frame_button.Bind(wx.EVT_LEFT_DOWN, self.select_reading_frame)
        self.aa_motif_button = wx.Button(self.panel, -1, 'Find AA Motif')
        self.aa_motif_button.Bind(wx.EVT_LEFT_DOWN, self.find_aa_motif)
        self.reverse_mutation_button = wx.Button(self.panel, -1, 'Engineer Mutations')
        self.reverse_mutation_button.Bind(wx.EVT_LEFT_DOWN, self.reverse_mutate)
        self.insertion_button = wx.Button(self.panel, -1, 'Insertions')
        self.insertion_button.Bind(wx.EVT_LEFT_DOWN, self.insertion)
        self.deletion_button = wx.Button(self.panel, -1, 'Deletions')
        self.deletion_button.Bind(wx.EVT_LEFT_DOWN, self.deletion)
        self.num_aa_mutations_label = wx.StaticText(self.panel, -1, 'Number of AA mutations:')
        self.num_aa_mutations = wx.SpinCtrl(self.panel, -1, '1')
        self.random_aa_button = wx.Button(self.panel, -1, 'Random AA Mutations')
        self.random_aa_button.Bind(wx.EVT_LEFT_DOWN, self.random_amino_acid_mutations)
        self.aa_mutation_range_label = wx.StaticText(self.panel, wx.ID_ANY, 'Insert mutation in range:')
        self.aa_left_mutation_range = wx.TextCtrl(self.panel, size = (40,20), style = wx.TE_PROCESS_ENTER)
        self.aa_left_mutation_range.Bind(wx.EVT_TEXT, self.aa_mutation_ranges)
        self.aa_right_mutation_range = wx.TextCtrl(self.panel, size = (40,20), style = wx.TE_PROCESS_ENTER)
        #self.use_aa_mutation_range = wx.CheckBox(self.panel, 8, 'Use Mutation Range?')
        self.aa_mut_colon = wx.StaticText(self.panel, wx.ID_ANY, ":")
        self.reversion_box = wx.CheckBox(self.panel, 10,'Avoid Reversion')
        #Fragment and potential site buttons
        #self.fragment_button = wx.Button(self.panel, -1, 'Fragment Sequence')
        #self.fragment_button.Bind(wx.EVT_LEFT_DOWN, self.fragment)
        #self.fragment_length_disp = wx.TextCtrl(self.panel, 11,size = (50,20), style = wx.TE_PROCESS_ENTER)
        #self.overlap_length_disp = wx.TextCtrl(self.panel, 12, size = (50,20), style = wx.TE_PROCESS_ENTER)
        #self.overlap_length_disp.SetValue(str(20))
        #self.fragment_length_text = wx.StaticText(self.panel, -1, 'Fragment Length:')
        #self.overlap_length_text = wx.StaticText(self.panel, -1, 'Overlap Length (min:20; max:100):')
        self.potential_button = wx.Button(self.panel, -1, 'Find Potential Sites')
        self.potential_button.Bind(wx.EVT_LEFT_DOWN, lambda evt, sequence = str(self.seq_disp.GetValue()): self.find_potential_sites(sequence, self.nb))
        #Enzyme list and options
        self.enzyme_listbox_label = wx.StaticText(self.panel, wx.ID_ANY,"Enzymes: ")
        self.enzyme_listbox = wx.ListBox(self.panel, 26, wx.DefaultPosition, (125, 250), sorted(self.enzyme_list), wx.LB_EXTENDED)
        self.deselect_button = wx.Button(self.panel, -1, 'Deselect All')
        self.deselect_button.Bind(wx.EVT_LEFT_DOWN, self.deselect)
        self.commercial_box = wx.CheckBox(self.panel, 20, 'Use only commercially available?')
        self.commercial_box.Bind(wx.EVT_CHECKBOX, self.commercial)
        #Vector list and buttons
        self.vector_listbox_label = wx.StaticText(self.panel, wx.ID_ANY, 'Vectors: ')
        self.vector_listbox = wx.ListBox(self.panel, 27, wx.DefaultPosition, (175, 125), sorted(self.vector_list, reverse=True))
        self.vector_listbox.Bind(wx.EVT_LISTBOX, self.load_vector)
        #Cutting Ranges
        self.range_out_label = wx.StaticText(self.panel, wx.ID_ANY, 'Do not cut in range:')
        self.range_in_label = wx.StaticText(self.panel, wx.ID_ANY,'Look for cut in range:')
        self.left_range_out = wx.TextCtrl(self.panel, size = (40,20), style = wx.TE_PROCESS_ENTER)
        self.left_range_out.Bind(wx.EVT_TEXT, self.ranges_out)
        self.right_range_out = wx.TextCtrl(self.panel, size = (40,20), style = wx.TE_PROCESS_ENTER)
        self.left_range_in = wx.TextCtrl(self.panel,  size = (40,20), style = wx.TE_PROCESS_ENTER)
        self.left_range_in.Bind(wx.EVT_TEXT, self.ranges_in)
        self.right_range_in = wx.TextCtrl(self.panel, size = (40, 20), style = wx.TE_PROCESS_ENTER)
        self.colon_in = wx.StaticText(self.panel, wx.ID_ANY, ":")
        self.colon_out = wx.StaticText(self.panel, wx.ID_ANY, ':')
        #Number of cuts
        self.onecut = wx.CheckBox(self.panel, 1, 'One Cutters')
        self.onecut.SetValue(True)
        self.twocut = wx.CheckBox(self.panel, 2, 'Two Cutters')
        self.threecut = wx.CheckBox(self.panel, 3, 'Three Cutters')
        self.allcut = wx.CheckBox(self.panel, 4, 'All Cuts')
        self.onecut.Bind(wx.EVT_CHECKBOX, self.first_handle)
        self.twocut.Bind(wx.EVT_CHECKBOX, self.first_handle)
        self.threecut.Bind(wx.EVT_CHECKBOX, self.first_handle)
        self.allcut.Bind(wx.EVT_CHECKBOX, self.second_handle)
        #Mutation options
        self.mutate_button = wx.Button(self.panel, -1, 'Mutate')
        self.mutate_button.Bind(wx.EVT_LEFT_DOWN, self.mutate)
        self.silent = wx.RadioButton(self.panel, 6, 'Silent Mutations')
        self.silent.SetValue(True)
        self.random = wx.RadioButton(self.panel,7, 'Random Mutations',)
        self.mutation_range_label = wx.StaticText(self.panel, wx.ID_ANY, 'Insert mutation in range:')
        self.left_mutation_range = wx.TextCtrl(self.panel, size = (40,20), style = wx.TE_PROCESS_ENTER)
        self.left_mutation_range.Bind(wx.EVT_TEXT, self.mutation_ranges)
        self.right_mutation_range = wx.TextCtrl(self.panel,size = (40,20), style = wx.TE_PROCESS_ENTER)
        #self.use_mutation_range = wx.CheckBox(self.panel, 8, 'Use Mutation Range?')
        self.mutcolon = wx.StaticText(self.panel, wx.ID_ANY, ":")
        self.numlabel = wx.StaticText(self.panel, wx.ID_ANY, "Number of mutations:")
        self.num = wx.SpinCtrl(self.panel, -1, '1', (70,-1))
        self.num.SetRange(1, 1000)
        self.num_mutants_label = wx.StaticText(self.panel, wx.ID_ANY, 'Number of mutants:')
        self.num_mutants = wx.SpinCtrl(self.panel, -1, '1')
        #Mutant displays, mutant GC content, and export button
        self.mutation_seq_disp_label = wx.StaticText(self.panel, wx.ID_ANY, 'Mutated Sequence:')
        self.mutation_seq_disp = wx.TextCtrl(self.panel, size = (400,150), style = wx.TE_MULTILINE | wx.TE_READONLY| wx.TE_RICH2)
        self.mutation_seq_disp.Bind(wx.EVT_TEXT, self.allow_export)
        self.mutation_aa_disp_label = wx.StaticText(self.panel, wx.ID_ANY, 'Mutated Amino Acid Sequence:')
        self.mutation_aa_disp = wx.TextCtrl(self.panel,  size = (325,150), style = wx.TE_MULTILINE |wx.TE_READONLY| wx.TE_RICH2)
        self.mutation_seq_gc_disp_label = wx.StaticText(self.panel, wx.ID_ANY, 'Mutant GC Content: ')
        self.mutation_seq_gc_disp = wx.TextCtrl(self.panel, size = (50,20), style = wx.TE_READONLY)
        self.export_button = wx.Button(self.panel, -1, 'Export')
        self.export_button.Bind(wx.EVT_LEFT_DOWN, self.export)
        self.export_button.Disable()
        #Reset Button
        self.reset_button = wx.Button(self.panel, -1, 'Reset')
        self.reset_button.Bind(wx.EVT_LEFT_DOWN, self.reset)
        self.resetsizer = wx.BoxSizer(wx.VERTICAL)
        #Add elements to sizers and fit total sizer to panel
        self.seqsizer.AddMany([self.seq_disp_label, self.seq_disp])
        self.seqnumsizer.AddMany([self.numlabel, self.num])
        self.nummutsizer.AddMany([self.num_mutants_label, self.num_mutants])
        self.numsizer.AddMany([self.seqnumsizer, self.nummutsizer])
        self.gcsizer.AddMany([self.seq_gc_disp_label, self.seq_gc_disp])
        self.motifsizer.AddMany([self.gcsizer, (self.find_motif_button, 0, wx.TOP, 10), (self.linker_button, 0, wx.TOP, 10)])
        self.mutoptionssizer.AddMany([(self.mutate_button, (0,0)), (self.silent, (0,1)), (self.random, (0,2))])
        self.mutrangespacer.AddMany([self.left_mutation_range, self.mutcolon, self.right_mutation_range])
        self.mutrangesizer.AddMany([self.mutation_range_label, (self.mutrangespacer, 1, wx.LEFT, 3)])
        self.totalmutsizer.AddMany([(self.mutoptionssizer, 0, wx.TOP, -40), (self.numsizer, 1, wx.TOP, 5), self.mutrangesizer])
        self.rangeouthoriz.AddMany([self.left_range_out, self.colon_out, self.right_range_out])
        self.rangeoutvert.AddMany([self.range_out_label, self.rangeouthoriz])
        self.rangeinhoriz.AddMany([self.left_range_in, self.colon_in, self.right_range_in])
        self.rangeinvert.AddMany([self.range_in_label, self.rangeinhoriz])
        self.cutrangesizer.AddMany([self.rangeoutvert, self.rangeinvert])
        #self.fraghoriz1.AddMany([self.fragment_length_text, (self.fragment_length_disp, 1, wx.LEFT, 8)])
        #self.fraghoriz2.AddMany([self.overlap_length_text, (self.overlap_length_disp, 1, wx.LEFT, 5)])
        #self.fragvert.AddMany([self.fraghoriz1, (self.fraghoriz2, 0, wx.TOP, 5)])
        self.fragmentsizer.AddMany([(self.potential_button, (1,0)), (self.commercial_box, (2,0)), (self.deselect_button, (3,0))])
        self.vector_listbox_sizer.AddMany([self.vector_listbox_label, (self.vector_listbox, 1, wx.EXPAND)])
        self.total_vector_sizer.AddMany([(self.vectorsizer, 1, wx.EXPAND), (self.vector_listbox_sizer, 0, wx.EXPAND|wx.LEFT, 10)])
        self.vectorsizer.AddMany([self.vector_label, (self.vector_disp, 1, wx.EXPAND|wx.LEFT, 3)])
        self.cuttersizer.AddMany([self.onecut, self.twocut, self.threecut, self.allcut, (self.fragmentsizer, 1, wx.TOP, 10)])
        self.enzymesizer.AddMany([(self.enzyme_listbox, 0, wx.EXPAND), (self.cuttersizer, 0, wx.EXPAND)])
        self.totalcutsizer.AddMany([self.cutrangesizer, self.enzyme_listbox_label, (self.enzymesizer, 1, wx.EXPAND)])
        self.frequencysizer.AddMany([self.codon_freq_button, (self.aa_freq_button, 1, wx.LEFT, 5)])
        self.aalabelsizer.AddMany([(self.aa_seq_label, 0, wx.LEFT, 5), (self.reading_frame_button, 1, wx.TOP, 10), (self.aa_motif_button, 0, wx.TOP, 10)])
        self.aasizer.AddMany([self.aalabelsizer, (self.aaoptionssizer, 1, wx.LEFT, 3)])
        self.aamutbuttonsizer.AddMany([self.reverse_mutation_button, (self.random_aa_button, 1, wx.LEFT, 5)])
        self.aamutnumsizer.AddMany([self.num_aa_mutations_label, (self.num_aa_mutations,1, wx.LEFT, 5), self.reversion_box])
        self.aamutrangesizer.AddMany([self.aa_mutation_range_label, (self.aa_left_mutation_range, 1, wx.LEFT, 3), self.aa_mut_colon, self.aa_right_mutation_range])
        self.indelsizer.AddMany([self.insertion_button, (self.deletion_button, 0, wx.LEFT, 5)])
        self.aaoptionssizer.AddMany([self.aa_disp, (self.frequencysizer, 1, wx.TOP, 10), (self.aamutbuttonsizer,1, wx.TOP, 10), (self.indelsizer, 1, wx.TOP, 5), (self.aamutnumsizer, 1, wx.TOP, 5), (self.aamutrangesizer, 1, wx.TOP, 5)])
        self.posdispsizer.AddMany([self.position_disp_label, self.position_disp])
        self.resetsizer.AddMany([self.posdispsizer, (self.reset_button, 0, wx.TOP|wx.LEFT, 100)])
        self.mutseqlabelsizer.AddMany([(self.mutation_seq_disp_label, 0, wx.LEFT, 35), (self.export_button, 1, wx.LEFT|wx.BOTTOM, 5), (self.mutation_aa_disp_label, 0, wx.LEFT, 240)])
        self.mutseqsizer.AddMany([(self.mutation_seq_disp, 0, wx.LEFT, 35), (self.mutation_aa_disp, 0, wx.LEFT, 35)])
        self.mutseqoptionssizer.AddMany([(self.mutation_seq_gc_disp_label,0, wx.TOP, 5), (self.mutation_seq_gc_disp, 0, wx.TOP, 5)])
        self.totalmutseqsizer.AddMany([self.mutseqlabelsizer, self.mutseqsizer, (self.mutseqoptionssizer, 1, wx.LEFT, 35), (self.total_vector_sizer, 0, wx.EXPAND|wx.LEFT, 35)])
        self.row1sizer.AddMany([self.seqsizer, (self.motifsizer, 0, wx.LEFT, 10), (self.aasizer, 0, wx.LEFT, 1), (self.resetsizer, 1, wx.LEFT, -20)])
        self.row2sizer.AddMany([(self.totalmutsizer, 1, wx.LEFT, 60)])
        self.row3sizer.AddMany([(self.totalcutsizer, 1, wx.EXPAND|wx.TOP, -50), (self.totalmutseqsizer, 0, wx.LEFT, -230)])
        self.totalsizer.Add(self.row1sizer, 0, wx.TOP, 10)
        self.totalsizer.Add(self.row2sizer,1, wx.TOP, -130)
        self.totalsizer.Add(self.row3sizer, 0, wx.EXPAND)
        self.panel.SetSizerAndFit(self.totalsizer)
        
    def insertion(self, event):
        dlg = wx.TextEntryDialog(None, 'Enter a sequence to insert:', 'Sequence Insert')
        if dlg.ShowModal() == wx.ID_OK:
            insert_seq = str(dlg.GetValue())
            insertion_point = self.aa_disp.GetInsertionPoint()
            self.aa_disp.SetValue(self.aa_disp.GetValue()[:insertion_point] + insert_seq + self.aa_disp.GetValue()[insertion_point:])
            self.reverse_mutate(event)
            self.aa_disp.SetValue(self.mutation_aa_disp.GetValue().split('\n')[1])
            self.seq_disp.SetValue(self.seq_disp.GetValue()[:insertion_point*3] + self.mutation_seq_disp.GetValue().split('\n')[1][insertion_point*3:len(insert_seq)*3+insertion_point*3] + self.seq_disp.GetValue()[insertion_point*3:])
            self.mutation_aa_disp.SetValue("")
            self.mutation_seq_disp.SetValue("")
        dlg.Destroy()
        
    def deletion(self, event):
        if self.aa_disp.GetSelection():
            self.seq_disp.SetValue(self.seq_disp.GetValue()[:self.aa_disp.GetSelection()[0]*3] + self.seq_disp.GetValue()[self.aa_disp.GetSelection()[1]*3:])
            self.aa_disp.SetValue(self.aa_disp.GetValue()[:self.aa_disp.GetSelection()[0]]+self.aa_disp.GetValue()[self.aa_disp.GetSelection()[1]:])
            
    def reset(self, event):
        self.seq_disp.SetValue("")
        self.seq_gc_disp.SetValue("")
        self.vector_disp.SetValue("")
        self.mutation_aa_disp.SetValue("")
        self.mutation_seq_disp.SetValue("")
        self.mutation_seq_gc_disp.SetValue("")
        self.position_disp.SetValue("")
        self.enzyme_listbox.SetSelection(-1)
        self.rf = 1
        self.onecut.SetValue(True)
        self.twocut.SetValue(False)
        self.threecut.SetValue(False)
        self.allcut.SetValue(False)
        self.export_button.Disable()
        self.silent.SetValue(True)
        self.num.SetValue(1)
        self.num_mutants.SetValue(1)
        self.num_aa_mutations.SetValue(1)
        self.reversion_box.SetValue(False)
        self.vector_listbox.SetSelection(-1)
        self.aa_left_mutation_range.SetValue("")
        self.aa_right_mutation_range.SetValue("")
        #self.fragment_length_disp.SetValue("")
        #self.overlap_length_disp.SetValue("")
        self.commercial_box.SetValue(False)
        self.left_range_out.SetValue("")
        self.left_mutation_range.SetValue("")
        self.left_range_in.SetValue("")
        self.right_range_out.SetValue("")
        self.right_mutation_range.SetValue("")
        self.right_range_in.SetValue("")
        self.GetParent().GetPage(1).seq_disp.SetValue("")
        self.GetParent().GetPage(1).new_seq_disp.SetValue("")
        self.GetParent().GetPage(1).aa_disp.SetValue("")
        self.GetParent().GetPage(1).new_aa_disp.SetValue("")
        self.GetParent().GetPage(1).deoptimize_left.SetValue("")
        self.GetParent().GetPage(1).deoptimize_right.SetValue("")
        self.GetParent().GetPage(1).optimize_left.SetValue("")
        self.GetParent().GetPage(1).optimize_right.SetValue("")
        self.GetParent().GetPage(1).reversion_box.SetValue(0)
        self.GetParent().GetPage(1).seq_freq.SetValue(0)
        self.GetParent().GetPage(1).specific_text.SetValue("")
        self.GetParent().GetPage(1).specific_deopt_button.SetValue(1)
        self.GetParent().GetPage(1).export_button.Disable()
        self.GetParent().GetParent().GetParent().organisms.Check(104,1)
        
    def move_cursor(self, event):
        self.aa_disp.SetFocus()
        self.aa_disp.SetInsertionPoint(int(self.position_disp.GetValue()))
        
    def allow_export(self, event):
        #Un-grays the export button once a mutated sequence is in the box
        if self.mutation_seq_disp.GetValue() != '':
            self.export_button.Enable()
       
    def seq_value(self, previous_seq):
        #Creates a list of previous values in sequence display for undo/redo
        seq = str(self.seq_disp.GetValue())
        length = len(previous_seq)
        if seq != '' and len(previous_seq) > 0:
            if seq != previous_seq[length-1]:    
                previous_seq.insert(0,seq)
                
    def vector_value(self, previous_vector):
        #Creates a list of previous vector values for undo/redo
        vector = str(self.vector_disp.GetValue())
        length = len(previous_vector)
        if vector != '' and len(previous_vector) > 0:
            if vector != previous_vector[length-1]:
                previous_vector.insert(0, vector)
                
    def aa_seq_value(self, previous_aaseq):
        #Creates a list of previous amino acid sequence values for undo/redo
        aaseq = str(self.aa_disp.GetValue())
        length = len(previous_aaseq)
        if aaseq != '' and len(previous_aaseq) > 0:
            if aaseq != previous_aaseq[length-1]:
                previous_aaseq.insert(0, aaseq)
                
    def load_vector(self, event):
        connection = sqlite3.connect('vectors.db')
        cursor = connection.cursor()
        cursor.execute('SELECT vector_name, vector_sequence FROM vectors')
        vector = self.get_selected_vectors()[0]
        for row in cursor:
            if row[0] == vector:
                self.vector_disp.SetValue(row[1])

    def deselect(self, event):
        #Deselect all enzymes in enzyme list
        self.enzyme_listbox.SetSelection(-1)
        
    def commercial(self, event):
        #Filter enzyme list with only commercially available enzymes
        connection = sqlite3.connect('re.db') #Connect to database
        cursor = connection.cursor()
        cursor.execute('SELECT r_enz_name, commercial FROM enzymes') #Get enzyme names and commerical availabilty from db
        sourcedict, original_list = {}, []
        enzyme_listbox = self.GetParent().GetPage(0).enzyme_listbox
        enz_list = self.GetParent().GetPage(0).enzyme_list
        enzyme_listbox.Clear()
        for row in cursor:
            sourcedict[row[0]] = row[1]
            original_list.append(row[0]) #Create a list of all enzymes including those not commercially available
        available = []
        if self.GetParent().GetPage(0).commercial_box.GetValue(): #If Use Only Commercially Available box is checked
            for enz, sources in sourcedict.iteritems():
                if sources != '':
                    available.append(enz)
            commercial = filter(lambda x: x in available, enz_list) #Filter for only commercially available enzymes
            for item in commercial: #Populate the list
                enzyme_listbox.Append(item)
            enzyme_listbox.Refresh()
        else:
            #Repopulate with original list of enzymes if unchecked
            enzyme_listbox.Clear()
            for item in original_list:
                enzyme_listbox.Append(item)
            enzyme_listbox.Refresh()
                
    def export(self, event):
        #Export mutated sequence and amino acid files
        filename = ''
        dlg = wx.TextEntryDialog(None, 'Enter a name for the file', 'Filename', '.fasta') #Get filename
        if dlg.ShowModal() == wx.ID_OK:
            filename = str(dlg.GetValue())
        dlg.Destroy()
        text = str(self.mutation_seq_disp.GetValue())
        if filename != '':
            if not os.path.exists(filename): #Write sequence to file
                file = open(filename, 'w')
                file.write(">"+filename+'\n')
                file.write(text)
                file.close()
            if not os.path.exists('%s_aa.txt' %filename): #Create a file for amino acid sequence
                file = open('%s_aa.txt' %filename, 'w')
                file.write(str(self.mutation_aa_disp.GetValue()))
                file.close()
            
    def add_linkers(self, event):
        connection = sqlite3.connect('linkers.db')
        cursor = connection.cursor()
        linker_list = []
        cursor.execute('''SELECT linker_name FROM linkers''')
        for row in cursor:
            linker_list.append(row[0])
        connection.commit()
        self.linker_page = linkers_db.LinkerPanel(self.nb, -1, linker_list, str(self.seq_disp.GetValue()))
        self.nb.AddPage(self.linker_page, 'Linkers')
        self.nb.SetSelection(self.nb.GetPageCount()-1)

    def update_seq_status(self, event):
        #Update cursor position display
        self.position_disp.SetValue(str(self.seq_disp.GetInsertionPoint()))
        #Edits to the sequence on the mutation panel also appear on optimization panel
        self.GetParent().GetPage(1).seq_disp.SetValue(self.seq_disp.GetValue())
        
    def update_aa_status(self, event):
        #Update cursor postion display
        self.position_disp.SetValue(str(self.aa_disp.GetInsertionPoint()))
        
    def update_vector_status(self, event):
        #Update cursor position display
        current = self.vector_disp.GetInsertionPoint()
        self.vector_disp.SetValue(self.vector_disp.GetValue().upper())
        self.vector_disp.SetInsertionPoint(current)
        self.position_disp.SetValue(str(self.vector_disp.GetInsertionPoint()))  
              
    def fix_vector(self, event):
        #Remove any non-letter characters from vector upon submission  
        str(self.vector_disp.SetValue(filter(lambda x: x.isalpha(), str(self.vector_disp.GetValue()))))
        self.vector_value(self.previous_vector)
        
    def select_reading_frame(self, event):
        #Launch panel for selecting reading frame and add to notebook
        nb = self.nb
        reading_frame_panel = ReadingFramePanel(nb, -1, self.seq_disp.GetValue())
        nb.AddPage(reading_frame_panel, 'Reading Frames')
        nb.SetSelection(nb.GetPageCount()-1)
        
    def mutate(self, event):
        #Mutates the nucleotide sequence either silently or randomly
        seq = str(self.seq_disp.GetValue())
        oseq = seq #Store original sequence
        #Get reading frame
        if self.rf == 2:
            seq = seq[1:]
        elif self.rf == 3:
            seq = seq[2:]
        new_seq = seq
        number = int(self.num.GetValue()) #Get number of mutations to insert
        insert_list, olist, nlist = [], [], []
        silent = self.silent.GetValue() #Check to see if silent mutations required
        back_table = codon_usage_db.db().codon_tables()[1]
        if self.left_mutation_range.GetValue() and self.right_mutation_range.GetValue(): #Check to see if ranges necessary
            ranges = True 
        else:
            ranges = False
        num_mutants = int(self.num_mutants.GetValue()) #Get number of mutatnts to create
        j = 0
        mutseqs, aamuts = '', ''
        if seq:
            if silent: #IF silent mutations required
                while j < num_mutants: #Until we have desired number of mutants
                    new_seq, oseq = seq, seq
                    i = 0
                    while i < number:
                        if ranges: #Get random choice from range
                            insert = int(random.choice(range(int(self.left_mutation_range.GetValue())-1, int(self.right_mutation_range.GetValue()))))
                        else: #If no range, get random position in sequence
                            insert = random.choice(range(len(seq)))
                        #Check location of mutation position in its codon in order to get codon to ensure silent mutations
                        if insert%3 == 0:
                            if insert+1 == len(seq) and insert != 0:
                                insert = insert - 3
                            elif insert+2 == len(seq) and insert != 0:
                                insert = insert -3
                            insert_list.append(insert)
                            region = seq[insert:insert+3]
                            olist.append(region)
                            translation = Seq.translate(Seq(region, generic_dna))
                            if str(translation) != '':
                                mutation_list = back_table[str(translation)]
                                if region in mutation_list:
                                    mutation_list.remove(region)
                                r = random.choice(mutation_list)
                                nlist.append(r)
                                new_seq = new_seq[:insert] + r + new_seq[insert+3:]
                                oseq = oseq[:insert] + r + oseq[insert+3:]
                        elif insert%3 == 1:
                            if insert+1 == len(seq) and insert != 1:
                                insert = insert - 3
                            insert_list.append(insert-1)
                            region = seq[insert-1:insert+2]
                            olist.append(region)
                            translation = Seq.translate(Seq(region, generic_dna))
                            if str(translation) != '':
                                mutation_list = back_table[str(translation)]
                                if region in mutation_list:
                                    mutation_list.remove(region)
                                r = random.choice(mutation_list)
                                nlist.append(r)
                                new_seq = new_seq[:insert-1] + r + new_seq[insert+2:]
                                oseq = oseq[:insert-1] + r + oseq[insert+2:]
                        elif insert%3 == 2:
                            insert_list.append(insert-2)
                            region = seq[insert-2:insert+1]
                            olist.append(region)
                            translation = Seq.translate(Seq(region, generic_dna))
                            if str(translation) != '':
                                mutation_list = back_table[str(translation)]
                                if region in mutation_list:
                                    mutation_list.remove(region)
                                r = random.choice(mutation_list)
                                nlist.append(r)
                                new_seq = new_seq[:insert-2] + r + new_seq[insert+1:]
                                oseq = oseq[:insert-2] + r + oseq[insert+1:]
                        i += 1
                    #Add titles describing mutations to sequences
                    if j == 0:
                        title = ''
                        i = 0
                        for site, orig, new in zip(insert_list, olist, nlist):
                            if i == len(insert_list)-1:
                                title = title + orig + str(site+1) + new 
                            else:
                                title = title + orig + str(site+1) + new + '.'
                            i +=1
                        mutseqs = '>' + title + '\n'
                        mutseqs = mutseqs + str(oseq)
                        aamuts = '>' + title + '\n'
                        aamuts = aamuts + str(Seq.translate(Seq(new_seq)))
                    else:
                        i = 0
                        for site, orig, new in zip(insert_list, olist, nlist):
                            title = ''
                            if i == len(insert_list)-1:
                                title = title + orig + str(site+1) + new 
                            else:
                                title = title + orig + str(site+1) + new + '.'
                            i +=1
                        mutseqs = mutseqs + '\n' +'>' +  title + '\n'
                        mutseqs= mutseqs + oseq
                        aamuts = aamuts + '\n' + '>' + title + '\n'
                        aamuts = aamuts + str(Seq.translate(Seq(new_seq)))
                    j += 1 
            else: #Random mutations
                while j < num_mutants: #Until reach desired number of mutants
                    new_seq = seq
                    oseq = seq
                    i = 0
                    while i < number:
                        if ranges: #Get random location inside range
                            insert = int(random.choice(range(int(self.left_mutation_range.GetValue())-1, int(self.right_mutation_range.GetValue()))))
                            insert_list.append(insert)
                            olist.append(new_seq[insert])
                        else:
                            insert = random.choice(range(len(seq)))
                            insert_list.append(insert)
                            olist.append(new_seq[insert])
                        if new_seq[insert] == 'A':
                            choice_list = ['T', 'C', 'G']
                            r = random.choice(choice_list)
                            new_seq = new_seq[:insert] + r + new_seq[insert+1:]
                            nlist.append(r)
                            oseq = oseq[:insert] + r + oseq[insert+1:]
                        elif new_seq[insert] == 'C':
                            choice_list = ['A', 'G', 'T']
                            r = random.choice(choice_list)
                            nlist.append(r)
                            new_seq = new_seq[:insert] + r + new_seq[insert+1:]
                            oseq = oseq[:insert] + r + oseq[insert+1:]
                        elif new_seq[insert] == 'G':
                            choice_list = ['A', 'C', 'T']
                            r = random.choice(choice_list)
                            nlist.append(r)
                            new_seq = new_seq[:insert] + r + new_seq[insert+1:]
                            oseq = oseq[:insert] + r + oseq[insert+1:]
                        elif new_seq[insert] == 'T':
                            choice_list = ['A', 'C', 'G']
                            r = random.choice(choice_list)
                            nlist.append(r)
                            new_seq = new_seq[:insert] + r + new_seq[insert+1:]
                            oseq = oseq[:insert] + r + oseq[insert+1:]
                        i += 1
                    #Add titles describing mutations to sequences
                    if j == 0:
                        title = ''
                        i = 0
                        for site, orig, new in zip(insert_list, olist, nlist):
                            if i == len(insert_list)-1:
                                title = title + orig + str(site+1) + new 
                            else:
                                title = title + orig + str(site+1) + new + '.'
                            i +=1
                        mutseqs = '>' + title + '\n'
                        mutseqs = mutseqs + str(oseq)
                        aamuts = '>' + title + '\n'
                        aamuts = aamuts + str(Seq.translate(Seq(new_seq)))
                    else:
                        title = ''
                        i = 0
                        for site, orig, new in zip(insert_list, olist, nlist):
                            if i < j *int(self.num.GetValue()):
                                i +=1
                            else:
                                if i == len(insert_list)-1:
                                    title = title + orig + str(site+1) + new 
                                else:
                                    title = title + orig + str(site+1) + new + '.'
                                i +=1
                        mutseqs = mutseqs + '\n' +'>' +  title + '\n'
                        mutseqs= mutseqs + oseq
                        aamuts = aamuts + '\n' + '>' + title + '\n'
                        aamuts = aamuts + str(Seq.translate(Seq(new_seq)))
                    j += 1
            #Write new sequences to displays
            self.mutation_seq_disp.SetValue(mutseqs)
            self.mutation_aa_disp.SetValue(aamuts)
            #Color mutations
            self.color_lines('m', str(self.mutation_seq_disp.GetValue()), self.mutation_seq_disp, self.mutation_aa_disp, insert_list)         
            count = 0
            seq = str(new_seq)
            for base in seq: #Calculate mutant sequence gc content
                if str(base) == 'G' or base == "C":
                    count +=1
            if len(seq) > 0:
                gccontent = float(count)*100/len(seq)
            else:
                gccontent = 0
            if j > 1: #If more than one mutant sequence don't calculate GC content
                self.mutation_seq_gc_disp.SetValue('')
            else:
                self.mutation_seq_gc_disp.SetValue(str(round(gccontent, 2))) 
        else:
            dlg = wx.MessageDialog(self, 'No sequence provided', 'Error')
            dlg.ShowModal()
            dlg.Close()
             
    def seq_gc_content(self):
        #Get the percentage of G's and C's in the sequence and display
        count = 0
        seq = str(self.seq_disp.GetValue())
        for base in seq:
            if str(base) == 'G' or base == "C":
                count +=1
        if len(seq) > 0:
            gccontent = float(count)*100/len(seq)
        else:
            gccontent = 0
        self.seq_gc_disp.SetValue(str(round(gccontent, 2)))
        
    def codon_dict(self, sequence):
        #Create dictionary with codons as keys and number of appearances as values
        #Also get total number of codons for calculation of percentage
        seq = sequence
        if self.rf == 2:
            seq = seq[1:]
        elif self.rf == 3:
            seq = seq[2:]
        cdn_dict, cdn_list = {}, []
        total_cdn = 0
        for char in xrange(len(seq)):
            if char%3 == 0:
                cdn_list.append(seq[char:char+3])
                total_cdn +=1
                cdn_dict[seq[char:char+3]] = 0       
        for codon in cdn_list:
            cdn_dict[codon] +=1
        return cdn_dict, total_cdn
    
    def codon_frequency(self, event):
        #Get frequency of appearance of codons and display in table
        cdn_dict = self.codon_dict(str(self.seq_disp.GetValue()))[0]
        total_cdn = self.codon_dict(str(self.seq_disp.GetValue()))[1]
        self.dlg = CdnFreqFrame(self, -1, cdn_dict, total_cdn)
        self.dlg.Show(True)
        return cdn_dict
    
    def aa_frequency(self, event):
        #Get frequency of appearance of amino acids in translated sequence and display in table
        aas = str(self.aa_disp.GetValue())
        aa_dict = {}
        total_aa = 0
        for aa in aas:
            aa_dict[aa] = 0
        for aa in aas:
            total_aa +=1
            aa_dict[aa] +=1
        self.dlg3 = AAFreqFrame(self, -1, aa_dict, total_aa)
        self.dlg3.Show(True)
        
    def translate_and_gc(self, event):
        #Translate the sequence into amino acids and call method to calculate GC content
        current = self.seq_disp.GetInsertionPoint()
        str(self.seq_disp.SetValue(filter(lambda x: x.isalpha() and (x is 'A' or x is 'C' or x is 'G' or x is 'T' or x is 'U' or x is 'a' or x is 'c' or x is 'g' or x is 't' or x is 'u' or x is 'N' or x is 'n'), str(self.seq_disp.GetValue()))))
        self.seq_disp.SetValue(str(self.seq_disp.GetValue()).upper())
        self.seq_disp.SetInsertionPoint(current)
        self.seq_gc_content()
        if self.rf == 1:
            try:
                self.aa_disp.SetValue(str(Seq.translate(Seq(self.seq_disp.GetValue(), generic_dna))))
                self.GetParent().GetPage(1).aa_disp.SetValue(str(Seq.translate(Seq(self.seq_disp.GetValue(), generic_dna))))
            except Bio.Data.CodonTable.TranslationError: #@UndefinedVariable
                dlg = wx.MessageDialog(self, 'Invalid Codon for Translation', 'Translation Error', wx.ICON_ERROR|wx.OK)
                dlg.ShowModal()
                dlg.Destroy()
                
        elif self.rf == 2:
            self.aa_disp.SetValue(str(Seq.translate(Seq(self.seq_disp.GetValue()[1:], generic_dna))))
            self.GetParent().GetPage(1).aa_disp.SetValue(str(Seq.translate(Seq(self.seq_disp.GetValue()[1:], generic_dna))))
        elif self.rf == 3:
            self.aa_disp.SetValue(str(Seq.translate(Seq(self.seq_disp.GetValue()[2:], generic_dna))))
            self.GetParent().GetPage(1).aa_disp.SetValue(str(Seq.translate(Seq(self.seq_disp.GetValue()[2:], generic_dna))))  
        self.seq_value(self.previous_seq)  
        
    def codon_usage_retrieve(self, cdn_list, organism):
        codon_percentage = {}
        #Get dictionary of appearance frequency for list of codons in selected organism
        if self.GetParent().GetParent().GetParent().get_organism() == 'Current sequence':
            codon_percentage = self.codon_frequency()
        else:
            db = 'codon_usage.db'
            connection = sqlite3.connect(db)
            cursor = connection.cursor()
            for codon in cdn_list:
                cursor.execute('SELECT %s FROM %s' %(codon,organism))
                for row in cursor:
                    if row[0] != None:
                        codon_percentage[codon] = row[0]
        return codon_percentage
    
    def random_amino_acid_mutations(self, event):
        #Randomly change one amino acid to another
        aa_seq = self.aa_disp.GetValue()
        new_aa_seq = aa_seq
        number_mutations = self.num_aa_mutations.GetValue()
        i = 0
        while i < number_mutations: #Insert the number of specified mutations
            aa_list = ['A', 'R', 'N', 'D', 'C', 'E', 'Q', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V']
            if self.aa_left_mutation_range.GetValue() and self.aa_right_mutation_range.GetValue():
                mutation_position = random.choice(range(int(self.aa_left_mutation_range.GetValue())-1, int(self.aa_right_mutation_range.GetValue())))
            else: #If no range is specified make a random choice from a list of positions in the sequence
                try:
                    mutation_position = random.choice(range(len(str(aa_seq))))
                except IndexError:
                    dlg = wx.MessageDialog(self, 'No sequence provided', 'Error')
                    dlg.ShowModal()
                    dlg.Close()
                    mutation_position = None
            if mutation_position != None:
                aa_list.remove(aa_seq[mutation_position])
                new_aa_seq = new_aa_seq[:mutation_position] + random.choice(aa_list) + new_aa_seq[mutation_position+1:]
            i+=1
        if mutation_position != None:
            self.aa_disp.SetValue(str(new_aa_seq)) #Display mutated AA sequence
            self.reverse_mutate(event) #Display resulting nucleotide sequence
        
    def hamming_distance(self, s1, s2):
        #Calculate minimum number of changes to turn one string into another
        assert len(s1) == len(s2)
        return sum(ch1 != ch2 for ch1, ch2 in zip(s1, s2))
    
    def color_lines(self, type, text, textctrl1, textctrl2, mutation_list):
        #Method to highlight mutations in nucleotide and amino acid sequences
        aatext = str(self.mutation_aa_disp.GetValue())
        aa = str(self.aa_disp.GetValue())
        self.mutation_seq_disp.SetStyle(0, len(text), wx.TextAttr('black', 'white'))
        self.mutation_aa_disp.SetStyle(0, len(aatext), wx.TextAttr('black', 'white'))
        site_list, aa_site_list = [], []
        split = text.split('\n')
        i, sum, aasum, j = 0, 0, 0, 0
        if type == 'rm':
            for item in split:
                if i%2 == 0:
                    title_length = len(item)+1
                    sum += title_length
                    aasum += title_length
                else:
                    tmp_list = mutation_list[j]
                    for site in tmp_list:
                        site = site-1
                        site_list.append(sum+site*3)
                        aa_site_list.append(aasum+site)
                    sum += len(item)+1
                    aasum += len(aa)+1
                    j += 1
                i += 1
            for site in site_list:
                textctrl1.SetStyle(site, site+3, wx.TextAttr('red', 'white'))
            for site in aa_site_list:
                textctrl2.SetStyle(site, site+1, wx.TextAttr('red', 'white'))
        else:
            for item in split:
                if i%2 == 0:
                    title_length = len(item)+1
                    sum += title_length
                    aasum += title_length
                else:
                    if self.silent.GetValue():
                        for site in mutation_list:
                            site_list.append(sum+site)
                        sum += len(item)+1
                        j +=1
                        y = self.num_mutants.GetValue()
                        k = self.num.GetValue()
                        x = 0
                        interval = j*2
                        if y > 1 and k > 1:
                            d = 1
                            while x < len(site_list):
                                site = site_list[x]
                                textctrl1.SetStyle(site, site+3, wx.TextAttr('red', 'white'))
                                site = site_list[x+1]
                                textctrl1.SetStyle(site, site+3, wx.TextAttr('red', 'white'))
                                x = interval*d
                                x += d*2
                                d += 1
                        else:
                            for site in site_list:
                                    textctrl1.SetStyle(site, site+3, wx.TextAttr('red', 'white'))
                    else:
                        otrans = Seq.translate(Seq(str(self.seq_disp.GetValue())))
                        newtrans = Seq.translate(Seq(item))
                        for char in xrange(len(otrans)):
                            if newtrans[char] != otrans[char]:
                                aa_site_list.append(char+aasum)
                        for site in mutation_list:
                            site_list.append(sum+site)
                        sum += len(item)+1
                        aasum += len(aa)+1
                        j = self.num_mutants.GetValue()
                        k = self.num.GetValue()
                        x = 0
                        interval = j*2
                        if j > 1 and k > 1:
                            d = 1
                            while x < len(site_list):
                                site = site_list[x]
                                textctrl1.SetStyle(site, site+1, wx.TextAttr('red', 'white'))
                                site = site_list[x+1]
                                textctrl1.SetStyle(site, site+1, wx.TextAttr('red', 'white'))
                                x = interval*d
                                x += d*2
                                d += 1    
                        else:
                            for site in site_list:
                                textctrl1.SetStyle(site, site+1, wx.TextAttr('red', 'white'))
                        for site in aa_site_list:
                            textctrl2.SetStyle(site, site+1, wx.TextAttr('red', 'white'))
                i +=1
                
    def reverse_mutate(self, event):
        #Mutate Amino Acid sequence and get back resulting nucleotide sequence. Codons ares selected using selected organism's codon bias usage
        #Get Reading Frame
        if self.rf == 1:
            original_translation = str(Seq.translate(Seq(self.seq_disp.GetValue(), generic_dna)))
        elif self.rf == 2:
            original_translation = str(Seq.translate(Seq(self.seq_disp.GetValue()[1:], generic_dna)))
        elif self.rf == 3:
            original_translation = str(Seq.translate(Seq(self.seq_disp.GetValue()[2:], generic_dna)))
        AAseq = self.aa_disp.GetValue() #Get the current amino acid sequence
        back_table = codon_usage_db.db().codon_tables()[1]
        cdn_dict = self.codon_dict(str(self.seq_disp.GetValue()))[0]
        reversion = self.use_avoid_reversion() #Check to see if need to avoid reversion
        #Get current values in displays
        new_seq = str(self.seq_disp.GetValue())
        mut_seq = str(self.mutation_seq_disp.GetValue())
        aa_seq = str(self.mutation_aa_disp.GetValue())
        ilist, olist, nlist = [], [], []
        for char in xrange(len(original_translation)):
            max = 0
            maxc = ''
            if AAseq[char] != original_translation[char]:
                codon_list = back_table[AAseq[char]]
                ilist.append(char+1)
                olist.append(original_translation[char])
                nlist.append(AAseq[char])
                for codon in codon_list:
                    if codon in cdn_dict:
                        if cdn_dict[codon] > max:
                            max = cdn_dict[codon]
                            maxc = codon
                if maxc == '':
                    max = 0
                    for k, v in self.codon_usage_retrieve(codon_list, self.GetParent().GetParent().GetParent().get_organism()).iteritems():
                        if v > max:
                            max = v
                            maxc = k
                original_codon = str(self.seq_disp.GetValue())[char*3:char*3+3]
                if reversion: #Make sure old codon and new codon differ by at least two amino acids
                    u = sorted([(value,key) for (key,value) in self.codon_usage_retrieve(codon_list, self.GetParent().GetParent().GetParent().get_organism()).items()], reverse=True)
                    if self.hamming_distance(original_codon, maxc) ==1:
                        for item in xrange(len(u)):
                            if 0 < item < len(u):
                                if u[item][0] > 10 and self.hamming_distance(original_codon, u[item][1]) > 1:
                                    maxc = u[item][1]
                                    break                 
                new_seq = new_seq[:char*3] + maxc + new_seq[char*3+3:]
                self.aa_disp.SetValue(original_translation)
        #Write old and new sequences to displays with descriptions of mutations
        if mut_seq == '':
            title = ''
            i = 0
            for site, orig, new in zip(ilist, olist, nlist):
                if i == len(ilist)-1:
                    title = title + orig + str(site) + new
                else:
                    title = title + orig + str(site) + new +'.'
                i +=1
            mut_seq = '>'+title + '\n'
            mut_seq = mut_seq + new_seq
            aa_seq = '>' + title + '\n'
            aa_seq = aa_seq + str(AAseq)
        else:
            title = ''
            i = 0
            for site, orig, new in zip(ilist, olist, nlist):
                if i == len(ilist)-1:
                    title = title + orig + str(site) + new
                else:
                    title = title + orig + str(site) + new+ '.'
            mut_seq = mut_seq + '\n' +'>' +  title + '\n'
            mut_seq = mut_seq + new_seq
            aa_seq = aa_seq + '\n' + '>' + title + '\n'
            aa_seq = aa_seq + str(AAseq)
        self.mlist.append(ilist)
        self.mutation_seq_disp.SetValue(mut_seq)
        self.mutation_aa_disp.SetValue(aa_seq)
        #Color mutations
        self.color_lines('rm', str(self.mutation_seq_disp.GetValue()), self.mutation_seq_disp, self.mutation_aa_disp, self.mlist)
        count = 0
        seq = str(new_seq)
        #Calculate GC content of mutant sequence
        for base in seq:
            if str(base) == 'G' or base == "C":
                count +=1
        if len(seq) > 0:
            gccontent = float(count)*100/len(seq)
        else:
            gccontent = 0
        self.mutation_seq_gc_disp.SetValue(str(round(gccontent, 2)))
        
    def ranges_out(self, event):
        #Sets value of the end range equal to beginning range when altered initially to ensure that a value is entered for the end range
        #Sets the value of use_ranges_out to True so that the range values will be used
        self.right_range_out.SetValue(self.left_range_out.GetValue())
        
    def ranges_in(self, event):
        #Sets value of the end range equal to beginning range when altered initially to ensure that a value is entered for the end range
        #Sets the value of use_ranges_in to True so that the range values will be used
        self.right_range_in.SetValue(self.left_range_in.GetValue())
         
    def mutation_ranges(self, event):
        #Sets value of the end range equal to beginning range when altered initially to ensure that a value is entered for the end range
        #Sets the value of use_mutation_ranges to True so that the range values will be used
        self.left_mutation_range.SetValue(filter(lambda x: x.isdigit(), self.left_mutation_range.GetValue()))
        self.right_mutation_range.SetValue(self.left_mutation_range.GetValue()) 
        
    def aa_mutation_ranges(self, event):
        #Sets value of the end range equal to beginning range when altered initially to ensure that a value is entered for the end range
        #Sets the value of use_aa_mutation_ranges to True so that the range values will be used
        self.aa_left_mutation_range.SetValue(filter(lambda x: x.isdigit(), self.aa_left_mutation_range.GetValue()))
        self.aa_right_mutation_range.SetValue(self.aa_left_mutation_range.GetValue())
        
    def cutting_results(self, event, bluntdict, topdict, botdict, starts, splits, nohitlist, seq, methylation, nb):
        #Create panels for displaying the cutting results and resulting graphical interpretation ("cut drawing") and add to notebook
        #Remove Cutting Results pages from notebook if already exist
        number, num = 0, 0
        for page in nb.GetChildren():
            if hasattr(page, 'name'):
                if page.name == 'Cutting Panel':
                    num = number
            number += 1
        if num != 0 and num != 1:
            nb.DeletePage(num)
            nb.DeletePage(num)
        cutresultspanel = CuttingPanel(nb, -1, self.search, bluntdict, topdict, botdict, starts, splits, nohitlist, self.seq_disp.GetValue(), methylation)
        nb.AddPage(cutresultspanel, 'Restriction Sites')
        cutdrawingpanel = CutDrawingPanel(nb, -1, self.search, bluntdict, topdict, botdict, self.seq_disp.GetValue(), self.panel.GetSize())
        nb.AddPage(cutdrawingpanel, 'Restriction Site Graph')
        nb.SetSelection(nb.GetPageCount()-2)
        
    def fragment(self, event):
        self.frag = True
        name_list = self.enzyme_listbox.GetItems()
        pos_tuple = self.enzyme_listbox.GetSelections()
        self.selected_list = []
        frag_length = int(self.fragment_length_disp.GetValue())
        overlap = int(self.overlap_length_disp.GetValue())
        if overlap > 100:
            overlap = 100
        elif overlap < 20:
            overlap = 20
        seq_length  = len(self.seq_disp.GetValue())
        num_frags = seq_length/frag_length #Calculate number of fragments that should be created
        frag_list, best, best_sites, best_starts, bad_sites, result, starts, sites = [], [], [], [], [], [], [], []
        overhangbases = ''
        ambigs = {'N':['A','C','G','T'],'R':['A','G'], 'Y': ['C','T'], 'W':['A','T'],'S':['G','C'],'M':['A','C'], 'K':['G','T'], 'B':['C','G','T'], 'D':['A','G','T'], 'H':['A','C','T'], 'V':['A','C','G']}
        reverse_codon = {'F': ['TTT', 'TTC'],'L': ['TTA', 'TTG', 'CTT', 'CTC', 'CTA', 'CTG'], 'I': ['ATT', 'ATC', 'ATA'], 'M': ['ATG'],
                         'V': ['GTT', 'GTC', 'GTA', 'GTG'], 'S': ['TCT', 'TCC', 'TCA', 'TCG', 'AGT', 'AGC'], 'P': ['CCT', 'CCC', 'CCA', 'CCG'],
                         'T': ['ACT', 'ACC', 'ACA', 'ACG'], 'A': ['GCT', 'GCC', 'GCA', 'GCG'], 'Y': ['TAT', 'TAC'], '*': ['TAA', 'TAG', 'TGA'],
                         'H': ['CAT', 'CAC'], 'Q': ['CAA', 'CAG'], 'N': ['AAT', 'AAC'], 'K': ['AAA', 'AAG'], 'D': ['GAT', 'GAC'], 'E': ['GAA', 'GAG'],
                         'C': ['TGT', 'TGC'], 'W': ['TGG'], 'R': ['CGT', 'CGC', 'CGA', 'CGG', 'AGA', 'AGG'], 'G': ['GGT', 'GGC', 'GGA', 'GGG']}
        for num in range(num_frags): #Set best values to empty for each site
            number = num +1
            frag_list.append(number*frag_length)
            best.append(seq_length)
            best_sites.append('')
            best_starts.append('')
        for pos in pos_tuple: #Get selected enzymes
            self.selected_list.append(name_list[pos])
        if self.selected_list == []: #If list is empty use the following:
            self.selected_list = ['BglI', 'BsmBI']
        a = self.call_find_sites_out(self.seq_disp.GetValue(), self.selected_list, None, None) #Find restriction sites
        cutinfo = self.call_db_cutting_info(self.selected_list) #Get cutting information for selected enzymes
        for k, v in a[1].iteritems(): #Look at blunt cutters
            for site in xrange(len(v)):
                for frag in frag_list:
                    min = math.fabs(v[site]-frag)
                    if min < best[site]:
                        best[site] = min
                        best_sites[site] = v[site]
                        best_starts[site] = a[0][0][site]
        for k, v in a[2].iteritems(): #Look at downstream cutters
            for site in xrange(len(v)):
                for frag in frag_list:
                    min = math.fabs(site[0]-frag)
                    if min < best[site]:
                        best[site] = min
                        best_sites[site] = site[0]
                        best_starts[site] = a[5][0][site]
        for k, v in a[3].iteritems(): #Look at upstream cutters
            for site in xrange(len(v)):
                for frag in frag_list:
                    min = math.fabs(site[0]-frag)
                    if min < best[site]:
                        best[site] = min
                        best_sites[site] = site[0]
                        best_starts[site] = a[5][0][site]
        i = 0
        if best == []: #If no sites are found add entire list to sites that need restriction site
            bad_sites = frag_list
        else:
            for frag in frag_list:
                if math.fabs(best_sites[i] - frag) > 0.1 * frag_length: #If site is not further than 10% of the desired fragment length away from the desired cutting location remove from list and add to bad site list 
                    bad_sites.append(frag_list[i])
                    i -= 1
                else:
                    starts.append(best_starts[i])
                    sites.append(best_sites[i])
                i +=1
        patterns = Search.db_retrieve(self.search)[1]
        self.cf = CuttingPanel(self.nb, -1, self.search, a[1], a[2], a[3], a[0], a[5], a[4], self.seq_disp.GetValue(), a[6])
        self.nb.AddPage(self.cf, 'Cutting Sites')
        #Mutate out any extra sites
        if a[0] != [] and a[5] != []:
            result = CuttingPanel.mutate_sites(self.cf, self.selected_list, (filter(lambda x: x not in best_starts, a[0][0]) or filter(lambda x: x not in best_starts, a[8][0])), patterns)
            sequence = result[0].split('\n')[1]
        elif a[0] != []:
            result = CuttingPanel.mutate_sites(self.cf, self.selected_list, filter(lambda x: x not in best_starts, a[0][0]), patterns)
            sequence = result[0].split('\n')[1]
        elif a[5] != []:
            result = CuttingPanel.mutate_sites(self.cf, self.selected_list, filter(lambda x: x not in best_starts, a[5][0]), patterns)
            sequence = result[0].split('\n')[1]
        else:
            sequence = str(self.seq_disp.GetValue())
        self.nb.DeletePage(self.nb.GetPageCount()-1)
        ps = self.find_potential_sites(sequence, self.nb) #Get list of potential sites and potential enzymes
        potentialsites = ps[0]
        potentialenzymes = ps[1]   
        tried = []
        found = False
        while len(tried) != len(potentialsites) and found == False: #While the list of potential sites has not been exhausted and a suitable site has not been found search
            if bad_sites == []: #If there are no bad sites break out of loop
                found = True
            else:
                for site in bad_sites: #For each site that doesn't have a suitable pattern
                    bestdistance = len(sequence)
                    i = 0
                    for psite in potentialsites:
                        if psite not in tried: #If the potential site hasn't been tried already
                            distance = math.fabs(site-psite)
                            #Get the closest potential site to the desired site
                            if distance < bestdistance:
                                bestdistance = distance
                                enzyme = potentialenzymes[i]
                                if enzyme in cutinfo[2]:
                                    cut = psite + cutinfo[2][enzyme][0]
                                elif enzyme in cutinfo[1] and cutinfo[1][enzyme] != -1:
                                    cut = psite + cutinfo[1][enzyme]
                                elif enzyme in cutinfo[1] and cutinfo[1][enzyme] == -1:
                                    cut = psite + len(patterns[enzyme]) 
                                insert = ''
                                #Check to see that cut is close enough to desired location
                                if cut > site - (0.1*frag_length) and cut < site + (0.1*frag_length):
                                    sites.append(cut)
                                    bad_seq = sequence[psite:psite+len(patterns[enzyme])]
                                    ptrans = Seq.translate(Seq(patterns[enzyme]))
                                    overhang = len(bad_seq)%3
                                    if overhang != 0:
                                        overhangbases = bad_seq[-overhang:]
                                    translation = Seq.translate(Seq(bad_seq))
                                    j = 0
                                    k = 0
                                    p = psite 
                                    #Insert the restriction site pattern silently
                                    #Ensures minimal changes to the existing potential pattern
                                    #Ambiguous bases will be the same unless necessary to create correct restriction site pattern
                                    for char in translation:
                                        if char == ptrans[j]:
                                            insert += patterns[enzyme][k:k+3]
                                        else:
                                            a = patterns[enzyme][k:k+3]
                                            codons = reverse_codon[char]
                                            onepos = []
                                            twopos = []
                                            threepos = []
                                            for codon in codons:
                                                m = 0
                                                for cchar in codon:
                                                    if m == 0:
                                                        if cchar not in onepos:
                                                            onepos.append(cchar)
                                                    elif m == 1:
                                                        if cchar not in twopos:
                                                            twopos.append(cchar)
                                                    elif m == 2:
                                                        if cchar not in threepos:
                                                            threepos.append(cchar)
                                                    m +=1
                                            m = 0
                                            insert1 = ''
                                            choicelist = []
                                            for pchar in a:
                                                if m == 0:
                                                    if pchar not in ambigs:
                                                        if pchar not in onepos:
                                                            insert1 += 'X'
                                                        else:
                                                            a = filter(lambda x: x.endswith(pchar), codons)
                                                            for cdn in a:
                                                                choicelist.append(cdn)
                                                    else:
                                                        charlist = ambigs[pchar]
                                                        flag = 0
                                                        for character in charlist:
                                                            if character in onepos:
                                                                a = filter(lambda x: x.startswith(character), codons)
                                                                for cdn in a:
                                                                    choicelist.append(cdn)
                                                                flag =1
                                                        if flag == 0:
                                                            insert1 += 'X'
                                                elif m ==1:
                                                    scndchoicelist = []
                                                    if pchar not in ambigs:
                                                        if pchar not in twopos:
                                                            insert1 += 'X'
                                                        else:
                                                            a = filter(lambda x: x.endswith(pchar), choicelist)
                                                            choicelist = []
                                                            for cdn in a:
                                                                scndchoicelist.append(cdn)
                                                    else:
                                                        charlist = ambigs[pchar]
                                                        flag = 0
                                                        for character in charlist:
                                                            if character in twopos:
                                                                a = filter(lambda x: x[1] == character, choicelist)
                                                                for cdn in a:
                                                                    scndchoicelist.append(cdn)
                                                                flag =1
                                                        if flag == 0:
                                                            insert1 += 'X'
                                                elif m ==2:
                                                    thrdchoicelist = []
                                                    if pchar not in ambigs:
                                                        if pchar not in threepos:
                                                            insert1 += 'X'
                                                        else:
                                                            a = filter(lambda x: x.endswith(pchar), scndchoicelist)
                                                            choicelist = []
                                                            for cdn in a:
                                                                thrdchoicelist.append(cdn)
                                                    else:
                                                        charlist = ambigs[pchar]
                                                        flag = 0
                                                        for character in charlist:
                                                            if character in threepos:
                                                                a = filter(lambda x: x.endswith(character), scndchoicelist)
                                                                choicelist = []
                                                                for cdn in a:
                                                                    thrdchoicelist.append(cdn)
                                                                flag =1
                                                        if flag == 0:
                                                            insert1 += 'X'
                                                m +=1
                                            if 'X' not in insert1:
                                                if sequence[p:p+3] in thrdchoicelist:
                                                    insert += sequence[p:p+3]
                                                else:
                                                    insert += random.choice(thrdchoicelist)
                                            else:
                                                insert += 'X'
                                        k +=3
                                        p +=3    
                                        j += 1        
                        i +=1
                        if 'X' not in insert:
                            sequence = sequence[:psite-1] + insert + overhangbases + sequence[psite+len(patterns[enzyme]):]
                            found = True
                        else:
                            tried.append(psite)
        if result == []: #Get filename if not already provided
            dlg = wx.TextEntryDialog(self, 'Sequence Name:', 'Sequence Name')
            if dlg.ShowModal() == wx.ID_OK:
                seq_name = str(dlg.GetValue())
            dlg.Destroy()
            filename = seq_name
        else:
            filename = result[1].strip('>')
        #Write mutated sequence and resulting fragments to files
        file = open('%s-fragments.fasta' %filename, 'w')
        old_site = 0
        sites = sorted(sites)
        for site in xrange(len(sites)):
            if site == 1:
                new_site = sites[site] 
                file.write('>%s'%filename + ' Fragment %s' %str(site+1) + '\n')
                file.write(sequence[old_site:new_site+overlap] + '\n')
                old_site = new_site
            else:
                new_site = sites[site] 
                file.write('>%s'%filename + ' Fragment %s' %str(site+1) + '\n')
                file.write(sequence[old_site-overlap:new_site+overlap] + '\n')
                old_site = new_site
        file.write('>%s'%filename + ' Fragment %s' %str(site+2) + '\n')
        file.write(sequence[new_site-overlap:])
        file.close()
        file = open('%s.fasta' %filename, 'w')
        file.write('>%s'%filename + '\n')
        file.write(sequence)
        file.close()
        self.frag = False
        
    def find_pattern(self, sequence, pattern):
        #Find a pattern of amino acids using regular expressions. Ambiguous amino acids are represented by X
        aminoacids = 'FLSY*CWPHQRIMTNKSRVADEG'
        target = ''
        dictionary = {'X':'[FLSY*CWPHQRIMTNKVADEG]'}
        for char in pattern: #Build regular expression
            if char in aminoacids:
                target += char
            else:
                target += dictionary[char]   
        starts = [match.start() for match in re.finditer(target, sequence)] #Find starting position of all matches
        return starts
    
    def find_potential_sites(self, sequence, nb):
        #Find potential restriction enzyme cutting sites
        rhanger, rhangers = '', ''
        potential_sites, potential_enzymes, a = [], [], []
        self.methylation = Search().find_methylation(str(self.seq_disp.GetValue()))
        reverse_codon = {'F': ['TTT', 'TTC'],'L': ['TTA', 'TTG', 'CTT', 'CTC', 'CTA', 'CTG'], 'I': ['ATT', 'ATC', 'ATA'], 'M': ['ATG'],
                         'V': ['GTT', 'GTC', 'GTA', 'GTG'], 'S': ['TCT', 'TCC', 'TCA', 'TCG', 'AGT', 'AGC'], 'P': ['CCT', 'CCC', 'CCA', 'CCG'],
                         'T': ['ACT', 'ACC', 'ACA', 'ACG'], 'A': ['GCT', 'GCC', 'GCA', 'GCG'], 'Y': ['TAT', 'TAC'], '*': ['TAA', 'TAG', 'TGA'],
                         'H': ['CAT', 'CAC'], 'Q': ['CAA', 'CAG'], 'N': ['AAT', 'AAC'], 'K': ['AAA', 'AAG'], 'D': ['GAT', 'GAC'], 'E': ['GAA', 'GAG'],
                         'C': ['TGT', 'TGC'], 'W': ['TGG'], 'R': ['CGT', 'CGC', 'CGA', 'CGG', 'AGA', 'AGG'], 'G': ['GGT', 'GGC', 'GGA', 'GGG']}
        patterns = Search.db_retrieve(self.search)[1]
        name_list = self.enzyme_listbox.GetItems() #List of enzyme names
        select_list = self.get_selected_enzymes() #Get selected enzymes from list (is a list of numbers associated with enzyme position in list)
        for item in select_list:
            if item.isdigit():
                a.append(name_list[item]) #Associate name with number
            else:
                a.append(item)
        if a == []: #If list is empty use these enzymes
            a = ['BglI', 'BsmBI']
        enzyme_list = a
        for enzyme in enzyme_list:
            target1 = patterns[enzyme] #Target pattern
            target_length = len(target1) 
            trns1 = str(Seq.translate(Seq(target1))) #Translation of target
            if sequence == '':
                sequence = self.seq_disp.GetValue()
            seq_translation = str(Seq.translate(Seq(sequence[self.rf-1:]))) #Translate the sequence in the appropriate reading frame
            a = self.find_pattern(seq_translation, trns1) #Find pattern of translated amino acids
            if self.rf == 1: #If reading frame 1
                #Get untranslated bases
                for site in a: #Look at each site that had a match
                    if target_length%3 == 1:
                        rhanger = target1[-1]
                    elif target_length%3 == 2:
                        rhangers = target1[-2:]
                    pattern_end = site + len(trns1)
                    #Check to see if untranslated bases also occur after the match in the sequence
                    if pattern_end < len(seq_translation):
                        aa = seq_translation[pattern_end]
                        codons = reverse_codon[aa]
                        for codon in codons:
                            if rhangers != '':
                                if codon.startswith(rhangers) and site*3 not in potential_sites:
                                    potential_sites.append(site*3)
                                    potential_enzymes.append(enzyme)
                            elif rhanger != '':
                                if codon.startswith(rhanger) and site*3 not in potential_sites:
                                    potential_sites.append(site*3)
                                    potential_enzymes.append(enzyme)
                            elif site*3 not in potential_sites:
                                potential_sites.append(site*3)
                                potential_enzymes.append(enzyme)
                    else:
                        potential_sites.append(site*3)
                        potential_enzymes.append(enzyme)
            if self.rf == 2: #If reading frame 2
                #Get untranslated bases
                for site in a: #Look at each match
                    if target_length%3 == 1:
                        rhanger = target1[-1]
                    elif target_length%3 == 2:
                        rhangers = target1[-2:]
                    pattern_end = site + len(trns1)
                    #Compare untranslated bases
                    if pattern_end < len(seq_translation):
                        aa = seq_translation[pattern_end]
                        codons = reverse_codon[aa]
                        for codon in codons:
                            if rhangers != '':
                                if codon.startswith(rhangers) and site*3+1 not in potential_sites:
                                    potential_sites.append(site*3+1)
                                    potential_enzymes.append(enzyme)
                            elif rhanger != '':
                                if codon.startswith(rhanger) and site*3+1 not in potential_sites:
                                    potential_sites.append(site*3+1)
                                    potential_enzymes.append(enzyme)
                            elif site*3+1 not in potential_sites:
                                potential_sites.append(site*3+1)
                                potential_enzymes.append(enzyme)
                    else:
                        potential_sites.append(site*3+1)
                        potential_enzymes.append(enzyme)
            if self.rf == 3: #If reading frame 3
                #Get untranslated bases
                for site in a: #Look at each match
                    if target_length%3 == 1:
                        rhanger = target1[-1]
                    elif target_length%3 == 2:
                        rhangers = target1[-2:]
                    pattern_end = site + len(trns1)
                    #Compare untranslated bases
                    if pattern_end < len(seq_translation):
                        aa = seq_translation[pattern_end]
                        codons = reverse_codon[aa]
                        for codon in codons:
                            if rhangers != '':
                                if codon.startswith(rhangers) and site*3+2 not in potential_sites:
                                    potential_sites.append(site*3+2)
                                    potential_enzymes.append(enzyme)
                            elif rhanger != '':
                                if codon.startswith(rhanger) and site*3+2 not in potential_sites:
                                    potential_sites.append(site*3+2)
                                    potential_enzymes.append(enzyme)
                            elif site*3+2 not in potential_sites:
                                potential_sites.append(site*3+2)
                                potential_enzymes.append(enzyme)
                    else:
                        potential_sites.append(site*3+2)
                        potential_enzymes.append(enzyme)
        if not self.frag: #If the fragment method was not called
            #Adjust notebook pages
            num = 0
            for page in nb.GetChildren():
                if hasattr(page, 'potential'):
                    nb.DeletePage(num)
                num += 1
            #Create panel to display potential sites and add to notebook
            potentialpanel = PotentialPanel(nb, -1, potential_sites, potential_enzymes, self.methylation)
            nb.AddPage(potentialpanel, 'Potential Sites')
            nb.SetSelection(nb.GetPageCount()-1)
        #If no sites found launch message dialog to inform user
            if potential_sites == []:
                dlg = wx.MessageDialog(self, "There were no potential sites found for the selected enzymes. Perhaps you should adjust the reading frame!.", 'No Sites Found!', wx.ICON_EXCLAMATION|wx.OK)
                dlg.ShowModal()
                dlg.Destroy()
        return potential_sites, potential_enzymes
    
    def get_selected_vectors(self):
        #Get the vectors selected from the vector list
        name_list = self.vector_listbox.GetItems()
        pos_tuple = self.vector_listbox.GetSelections()
        selected_list = []
        for pos in pos_tuple:
            selected_list.append(name_list[pos])
        return selected_list
    
    def get_selected_enzymes(self):
        #Get the enzymes selected from the enzyme list
        name_list = self.enzyme_listbox.GetItems()
        pos_tuple = self.enzyme_listbox.GetSelections()
        selected_list = []
        for pos in pos_tuple:
            selected_list.append(name_list[pos])
        return selected_list
    
    def submit_event(self, event):
        #Event called upon pressing enter in sequence box
        name_list = self.enzyme_listbox.GetItems()
        selected_list = self.get_selected_enzymes()
        ranges_in, ranges_out = False, False
        if selected_list == []:
            #Launch message dialog if no enzymes selected
            dlg = wx.MessageDialog(self, "You have not selected any enzymes!", 'Alert!', wx.ICON_ERROR | wx.OK)
            dlg.ShowModal()
            dlg.Destroy()
        selected_list = sorted(selected_list) #Sort enzyme list
        seq = self.seq_disp.GetValue()
        #Get which checkboxes are selected for number of times enzymes should cut the sequence
        all, one, two, three = self.all_cutters(), self.one_cutters(), self.two_cutters(), self.three_cutters()
        # Determine the range to look for cut
        if self.left_range_in.GetValue() and self.right_range_in.GetValue():
            ranges_in = True #Only look inside of certain range
        if self.left_range_out.GetValue() and self.right_range_out.GetValue():
            ranges_out = True #Only look outside of certain range
        vector = self.vector() #Check to see if any text is in the vector box to be checked
        if vector:
            v = self.call_find_sites_out(self.vector_disp.GetValue(), selected_list, None, None) #Search vector for restriction sites against selected list of enzymes. No range is specified
            if v[0] != []:
                #If the vector is cut by one of the selected enzymes launch a dialog to inform user
                dlg = wx.MessageDialog(self, "The vector was hit by one of the selected enzymes!", 'Vector Comparision', wx.ICON_EXCLAMATION| wx.OK)
                dlg.ShowModal()
                dlg.Destroy()
                #Remove any enzymes that cut the vector from the Enzyme List Display
                if v[1] != {}:
                    for k, v in v[1].iteritems():
                        self.enzyme_listbox.Delete(name_list.index(k))
                self.enzyme_listbox.Refresh()
        else:
            if ranges_in:
                if int(self.left_range_in.GetValue()) > len(seq):
                    self.left_range_in.SetValue(str(len(seq)))
                if int(self.right_range_in.GetValue()) > len(seq):
                    self.right_range_in.SetValue(str(len(seq)))
                if int(self.left_range_in.GetValue()) > int(self.right_range_in.GetValue()):
                    self.left_range_in.SetValue(self.RRange.GetValue())
                left_range = self.left_range_in.GetValue()
                right_range = self.right_range_in.GetValue()
                m = self.call_find_sites_in(seq, selected_list, left_range, right_range) #Search for sites against selected list inside range
            if ranges_out:
                if int(self.left_range_out.GetValue()) > len(seq):
                    self.left_range_out.SetValue(str(len(seq)))
                if int(self.right_range_out.GetValue()) > len(seq):
                    self.right_range_out.SetValue(str(len(seq)))
                if int(self.left_range_out.GetValue()) > int(self.right_range_out.GetValue()):
                    self.left_range_out.SetValue(self.RRange.GetValue())
                left_range = self.left_range_out.GetValue()
                right_range = self.right_range_out.GetValue()
                m = self.call_find_sites_out(seq, selected_list, left_range, right_range) #Search for sites against selected list outside range
            else:
                m = self.call_find_sites_out(seq, selected_list, None, None) #Search for sites against selected list (no range specified)
            if all: #Get cutting results for all cutters if any enzymes cut
                if len(m[1])>0 or len(m[2]) >0 or len(m[3]) >0:
                    self.cutting_results(event, m[1], m[2], m[3], m[0], m[5], m[4], self.seq_disp.GetValue(), m[6], self.nb)
            else:
                if one and two: #One and two cutters only
                    klist = []
                    for k, v in m[1].iteritems():
                        if len(v) != 1 and len(v) != 2:
                            klist.append(k)
                    for item in klist:
                        m[1].pop(item)
                    klist = []
                    for k, v in m[2].iteritems():
                        if len(v) != 1 and len(v) != 2:
                            klist.append(k)
                    for item in klist:
                        m[2].pop(item)
                    klist = []
                    for k, v in m[3].iteritems():
                        if len(v) != 1 and len(v) != 2:
                            klist.append(k)
                    for item in klist:
                        m[3].pop(item)
                elif one and three: #One and three cutters only
                    klist = []
                    for k, v in m[1].iteritems():
                        if len(v) != 1 and len(v) != 3:
                            klist.append(k)
                    for item in klist:
                        m[1].pop(item)
                    klist = []
                    for k, v in m[2].iteritems():
                        if len(v) != 1 and len(v) != 3:
                            klist.append(k)
                    for item in klist:
                        m[2].pop(item)
                    klist = []
                    for k, v in m[3].iteritems():
                        if len(v) != 1 and len(v) != 3:
                            klist.append(k)
                    for item in klist:
                        m[3].pop(item)
                elif two and three: #Two and three cutters only
                    klist = []
                    for k, v in m[1].iteritems():
                        if len(v) != 2 and len(v) != 3:
                            klist.append(k)
                    for item in klist:
                        m[1].pop(item)
                    klist = []
                    for k, v in m[2].iteritems():
                        if len(v) != 2 and len(v) != 3:
                            klist.append(k)
                    for item in klist:
                        m[2].pop(item)
                    klist = []
                    for k, v in m[3].iteritems():
                        if len(v) != 2 and len(v) != 3:
                            klist.append(k)
                    for item in klist:
                        m[3].pop(item) 
                elif one: #One cutters only
                    klist = []
                    for k, v in m[1].iteritems():
                        if len(v) != 1:
                            klist.append(k)
                    for item in klist:
                        m[1].pop(item)
                    klist = []
                    for k, v in m[2].iteritems():
                        if len(v) != 1:
                            klist.append(k)
                    for item in klist:
                        m[2].pop(item)
                    klist = []
                    for k, v in m[3].iteritems():
                        if len(v) != 1:
                            klist.append(k)
                    for item in klist:
                        m[3].pop(item)
                elif two: #Two cutters only
                    klist = []
                    for k, v in m[1].iteritems():
                        if len(v) != 2:
                            klist.append(k)
                    for item in klist:
                        m[1].pop(item)
                    klist = []
                    for k, v in m[2].iteritems():
                        if len(v) != 2:
                            klist.append(k)
                    for item in klist:
                        m[2].pop(item)
                    klist = []
                    for k, v in m[3].iteritems():
                        if len(v) != 2:
                            klist.append(k)
                    for item in klist:
                        m[3].pop(item)
                elif three: #Three cutters only
                    klist = []
                    for k, v in m[1].iteritems():
                        if len(v) != 2:
                            klist.append(k)
                    for item in klist:
                        m[1].pop(item)
                    klist = []
                    for k, v in m[2].iteritems():
                        if len(v) != 2:
                            klist.append(k)
                    for item in klist:
                        m[2].pop(item)
                    klist = []
                    for k, v in m[3].iteritems():
                        if len(v) != 2:
                            klist.append(k)
                    for item in klist:
                        m[3].pop(item)
                self.cutting_results(event, m[1], m[2], m[3], m[0], m[5], m[4], self.seq_disp.GetValue(), m[6], self.nb)
                
    def vector(self):
        #Check to see if anything has been entered into Vector Display
        if self.vector_disp.GetValue():
            return True   
   
    def use_avoid_reversion(self):
        #Get value from Avoid Reversion Box
        if self.reversion_box.GetValue():
            return True
        
    def one_cutters(self):
        #Get value from one cutters box
        if self.onecut.GetValue():
            return True
        
    def two_cutters(self):
        #Get value from two cutters box
        if self.twocut.GetValue():
            return True
        
    def three_cutters(self):
        #Get value from Three Cutters box
        if self.threecut.GetValue():
            return True
        
    def all_cutters(self):
        #Get Value from allcutters Box
        if self.allcut.GetValue():
            return True
        
    def first_handle(self, event):
        #If onecut, twocut, or threecut selected, deselect allcut
        self.allcut.SetValue(False)   
          
    def second_handle(self, event):
        #If all cut selected, deselect other three boxes
        self.onecut.SetValue(False)
        self.twocut.SetValue(False)
        self.threecut.SetValue(False)
        
    def find_motif(self, event):
        #Finds a motif (substring) in the sequence display and highlights it
        dlg = wx.TextEntryDialog(self, 'Enter Motif:', 'Motif')
        results = []
        if dlg.ShowModal() == wx.ID_OK:
            motif = dlg.GetValue()
            self.seq_disp.SetStyle(0, len(str(self.seq_disp.GetValue()))+1, wx.TextAttr('black', 'white'))
            results = self.search.find_pattern(self.seq_disp.GetValue(), motif)
            for site in results:
                self.seq_disp.SetStyle(site, site+len(motif), wx.TextAttr('blue', 'white'))
                self.seq_disp.SetStyle(site+len(motif)+1, len(str(self.seq_disp.GetValue))+1, wx.TextAttr('black', 'white'))
        
    def find_aa_motif(self, event):
        #Finds a motif in the amino acid display and highlights it
        dlg = wx.TextEntryDialog(self, 'Enter Motif:', 'Motif')
        if dlg.ShowModal() == wx.ID_OK:
            motif = dlg.GetValue()
            self.aa_disp.SetStyle(0, len(str(self.aa_disp.GetValue()))+1, wx.TextAttr('black', 'white'))
        results = self.search.find_aa_motif(self.aa_disp.GetValue(), motif)
        for site in results:
            self.aa_disp.SetStyle(site, site+len(motif), wx.TextAttr('blue', 'white'))
            self.aa_disp.SetFocus()
            self.aa_disp.SetStyle(site+len(motif)+1, len(str(self.aa_disp.GetValue))+1, wx.TextAttr('black', 'white'))
        
    def call_find_sites_out(self, seq, enz_list, left_range, right_range):
        #Call FindSitesOut method from Search Class
        return self.search.find_sites_out(seq, enz_list, left_range, right_range)
    
    def call_find_sites_in(self, seq, enz_list, left_range, right_range):
        #Call FindSitesIn method from search class
        return self.search.find_sites_in(seq, enz_list, left_range, right_range)
    
    def call_db_cutting_info(self, the_list):
        #Calls DBCuttingInfo method from search class
        return self.search.db_cutting_info(the_list)
    
    def call_db_retrieve(self):
        #Calls DBRetrieve method from Search Class
        return self.search.db_retrieve()
    
class PotentialPanel(wx.Panel):
    #A panel which displays potential restriction sites that could be added through silent mutations
    def __init__(self, parent, id, potential_sites, potential_enzymes, methylation, title = 'Potential Restriction Enzyme Sites'):
        wx.Panel.__init__(self, parent)
        self.potential = ''
        self.potential_sites, self.potential_enzymes = potential_sites, potential_enzymes
        self.rf = self.GetParent().GetPage(0).rf
        self.cuts = self.GetParent().GetPage(0).call_db_cutting_info(self.potential_enzymes)
        self.patterns = self.GetParent().GetPage(0).call_db_retrieve()
        self.bluntlabel = wx.StaticText(self, wx.ID_ANY, 'Potential Blunt Cuts:')
        self.downlabel = wx.StaticText(self, wx.ID_ANY, 'Potential Downstream Cuts:')
        self.uplabel = wx.StaticText(self, wx.ID_ANY, 'Potential Upstream Cuts:')
        self.nocutlabel = wx.StaticText(self, wx.ID_ANY, 'No Potential Cuts:')
        self.bluntlc = wx.ListCtrl(self, -1, size = (240,300), style = wx.LC_SINGLE_SEL|wx.LC_REPORT)
        self.bluntlc.InsertColumn(0, 'Enzyme')
        self.bluntlc.InsertColumn(1, 'Cutting Sites')
        self.bluntlc.SetColumnWidth(0,80)
        self.bluntlc.SetColumnWidth(1,80)
        self.bluntlc.InsertColumn(2, 'Target Start')
        self.bluntlc.SetColumnWidth(2, 80)
        num_items_blunt = self.bluntlc.GetItemCount()
        for site, enz in zip(self.potential_sites, self.potential_enzymes): #Populate list of potential blunt cutters
            if enz not in self.cuts[2] and enz not in self.cuts[3] and self.cuts[1][enz] != -1:
                self.bluntlc.InsertStringItem(num_items_blunt, enz)
                self.bluntlc.SetStringItem(num_items_blunt, 1, str(int(site+self.cuts[1][enz])+1))
                self.bluntlc.SetStringItem(num_items_blunt, 2, str(int(site)+1))
            elif enz not in self.cuts[2] and enz not in self.cuts[3] and self.cuts[1][enz] == -1:
                self.bluntlc.InsertStringItem(num_items_blunt, enz)
                self.bluntlc.SetStringItem(num_items_blunt, 1, str(int(site+len(self.patterns[1][enz]))+1))
                self.bluntlc.SetStringItem(num_items_blunt, 2, str(int(site)+1))
        self.downlc = wx.ListCtrl(self, -1, size = (380, 300), style = wx.LC_REPORT)
        self.downlc.InsertColumn(0, 'Enzyme')
        self.downlc.SetColumnWidth(0, 80)
        self.downlc.InsertColumn(1, 'Top Strand Cuts')
        self.downlc.SetColumnWidth(1, 100)
        self.downlc.InsertColumn(2, 'Bottom Strand Cuts')
        self.downlc.SetColumnWidth(2, 120)
        self.downlc.InsertColumn(3, 'Target Start')
        self.downlc.SetColumnWidth(3, 80)
        num_items_down = self.downlc.GetItemCount()
        for site, enz in zip(self.potential_sites, self.potential_enzymes):
            if enz in self.cuts[2]: #Populate of potential split downstream cutters
                self.downlc.InsertStringItem(num_items_down, enz)
                self.downlc.SetStringItem(num_items_down, 1, str(site+int(self.cuts[2][enz][0])))
                self.downlc.SetStringItem(num_items_down, 2, str(site+int(self.cuts[2][enz][1])))
                self.downlc.SetStringItem(num_items_down, 3, str(int(site)+1))
        self.uplc = wx.ListCtrl(self, -1, size = (380, 300), style = wx.LC_REPORT)
        self.uplc.InsertColumn(0, 'Enzyme')
        self.uplc.SetColumnWidth(0, 80)
        self.uplc.InsertColumn(1, 'Top Strand Cuts')
        self.uplc.SetColumnWidth(1, 100)
        self.uplc.InsertColumn(2, 'Bottom Strand Cuts')
        self.uplc.SetColumnWidth(2, 120)
        self.uplc.InsertColumn(3, 'Target Start')
        self.uplc.SetColumnWidth(3, 80)
        num_items_up = self.uplc.GetItemCount()
        for site, enz in zip(self.potential_sites, self.potential_enzymes):
            if enz in self.cuts[3]: #Populate list of potential sites that would cut upstream (split cut between strands)
                self.uplc.InsertStringItem(num_items_up, enz)
                self.uplc.SetStringItem(num_items_up, 1, str(int(site+int(self.cuts[3][enz][0]))+1))
                self.uplc.SetStringItem(num_items_up, 2, str(int(site+int(self.cuts[3][enz][1]))+1))
                self.uplc.SetStringItem(num_items_up, 3, str(int(site)+1))
        self.nohitlc = wx.ListCtrl(self, -1, size = (100, 300), style = wx.LC_REPORT)
        self.nohitlc.InsertColumn(0, 'Enzyme')
        self.nohitlc.SetColumnWidth(0, 100)
        num_items_nohit = self.nohitlc.GetItemCount()
        for enz in self.GetParent().GetPage(0).get_selected_enzymes():
            if enz not in self.potential_enzymes:
                self.nohitlc.InsertStringItem(num_items_nohit, enz)
        self.mutation_button = wx.Button(self, -1, "Add Sites")
        self.mutation_button.Bind(wx.EVT_LEFT_DOWN, self.select_sites)
        self.original_seq_label = wx.StaticText(self, wx.ID_ANY, 'Original Sequence')
        self.new_seq_label = wx.StaticText(self, wx.ID_ANY, 'New Sequence')
        self.methylase_text = wx.StaticText(self, wx.ID_ANY, 'Potential E. coli Dam and Dcm \nmethylase patterns:')
        self.methylation_lc = wx.ListCtrl(self, -1, size = (225, 200), style = wx.LC_REPORT)
        self.methylation_lc.InsertColumn(0, 'Methylase')
        self.methylation_lc.InsertColumn(1, 'Sequence Start')
        self.methylation_lc.InsertColumn(2, 'Sequence End')
        self.methylation_lc.SetColumnWidth(0, 60)
        self.methylation_lc.SetColumnWidth(1, 85)
        self.methylation_lc.SetColumnWidth(2, 80)
        num_items_methyl = self.methylation_lc.GetItemCount()
        for key, value in sorted(methylation.iteritems(), reverse=True):
            self.methylation_lc.InsertStringItem(num_items_methyl, value)
            self.methylation_lc.SetStringItem(num_items_methyl, 1, str(key))
            if value == 'Dam':
                self.methylation_lc.SetStringItem(num_items_methyl, 2, str(int(key) + 3))
            elif value == 'Dcm':
                self.methylation_lc.SetStringItem(num_items_methyl, 2, str(int(key) + 4))
        self.OrigSeq = wx.TextCtrl(self, size = (450,200), style = wx.TE_READONLY|wx.TE_MULTILINE)
        self.NewSeq = wx.TextCtrl(self, size = (450, 200), style = wx.TE_READONLY|wx.TE_MULTILINE | wx.TE_RICH2)
        #Initialize sizers and add to panel
        self.bluntsizer = wx.BoxSizer(wx.VERTICAL)
        self.downsizer = wx.BoxSizer(wx.VERTICAL)
        self.upsizer = wx.BoxSizer(wx.VERTICAL)
        self.nosizer = wx.BoxSizer(wx.VERTICAL)
        self.lcsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.old_sizer = wx.BoxSizer(wx.VERTICAL)
        self.new_sizer = wx.BoxSizer(wx.VERTICAL)
        self.disp_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.methylase_sizer = wx.BoxSizer(wx.VERTICAL)
        self.total_sizer = wx.BoxSizer(wx.VERTICAL)
        self.bluntsizer.AddMany([(self.bluntlabel, 0, wx.TOP, 10), (self.bluntlc, 0, wx.TOP, 10)])
        self.downsizer.AddMany([(self.downlabel, 0, wx.TOP, 10), (self.downlc, 0, wx.TOP, 10)])
        self.upsizer.AddMany([(self.uplabel, 0, wx.TOP, 10), (self.uplc, 0, wx.TOP, 10)])
        self.nosizer.AddMany([(self.nocutlabel, 0, wx.TOP, 10), (self.nohitlc, 0, wx.TOP, 10)])
        self.old_sizer.AddMany([self.original_seq_label, (self.OrigSeq, 1, wx.EXPAND)])
        self.new_sizer.AddMany([self.new_seq_label, (self.NewSeq, 1, wx.EXPAND)])
        self.disp_sizer.AddMany([(self.old_sizer,1, wx.EXPAND|wx.LEFT|wx.TOP,10), (self.new_sizer,1, wx.EXPAND|wx.LEFT|wx.TOP, 10), (self.methylase_sizer, 0, wx.TOP, -15)])
        self.methylase_sizer.AddMany([(self.methylase_text, 0, wx.LEFT|wx.BOTTOM, 7), (self.methylation_lc, 0, wx.LEFT, 7)])
        self.lcsizer.AddMany([self.bluntsizer, (self.downsizer, 0, wx.LEFT, 20), (self.upsizer, 0, wx.LEFT, 20), (self.nosizer, 0, wx.LEFT, 20)])
        self.total_sizer.AddMany([self.lcsizer, (self.mutation_button, 0, wx.TOP, 10), (self.disp_sizer, 1, wx.EXPAND)])
        self.SetSizerAndFit(self.total_sizer)
       
    def select_sites(self, event):
        #Get selected sites from lists on cutting panel and then mutate out sites
        enz_list, site_list = [], []
        if self.bluntlc.GetFirstSelected() != -1: #Check to see if any are selected
            enz_list.append(str(self.bluntlc.GetItemText(self.bluntlc.GetFirstSelected())))
            site_list.append(self.bluntlc.GetItem(self.bluntlc.GetNextItem(-1, wx.LIST_NEXT_ALL, wx.LIST_STATE_SELECTED), 2).GetText())
            n =self.bluntlc.GetNextSelected(self.bluntlc.GetFirstSelected())
            while n != -1: #While there are more selected
                enz_list.append(str(self.bluntlc.GetItemText(n)))
                site_list.append(self.bluntlc.GetItem(n, 2).GetText())
                n = self.bluntlc.GetNextSelected(n)
        if self.downlc.GetFirstSelected() != -1: #Check to see if any are selected
            enz_list.append(str(self.downlc.GetItemText(self.downlc.GetFirstSelected())))
            site_list.append(self.downlc.GetItem(self.downlc.GetNextItem(-1, wx.LIST_NEXT_ALL, wx.LIST_STATE_SELECTED), 3).GetText())
            n =self.downlc.GetNextSelected(self.downlc.GetFirstSelected())
            while n != -1: #While there are more selected
                enz_list.append(str(self.bluntlc.GetItemText(n)))
                site_list.append(self.downlc.GetItem(n, 3).GetText())
                n = self.downlc.GetNextSelected(n)
        if self.uplc.GetFirstSelected() != -1: #Check to see if any are selected
            enz_list.append(str(self.uplc.GetItemText(self.uplc.GetFirstSelected())))
            site_list.append(self.uplc.GetItem(self.uplc.GetNextItem(-1, wx.LIST_NEXT_ALL, wx.LIST_STATE_SELECTED), 3).GetText())
            n =self.uplc.GetNextSelected(self.uplc.GetFirstSelected())
            while n != -1: #While there are more selected
                enz_list.append(str(self.uplc.GetItemText(n)))
                site_list.append(self.uplc.GetItem(n, 3).GetText())
        self.add_sites(enz_list, site_list)
        
    def add_sites(self, elist, slist):
        #Insert restriction enzyme sites into potential site locations
        patterns = self.GetParent().GetPage(0).call_db_retrieve()[1]
        self.seq = self.GetParent().GetPage(0).seq_disp.GetValue()
        if self.rf == 2:
            self.seq = self.seq[1:]
        elif self.rf == 3:
            self.seq = self.seq[2:]
        self.new_seq = self.seq
        insert = ''
        ambigs = {'N':['A','C','G','T'],'R':['A','G'], 'Y': ['C','T'], 'W':['A','T'],'S':['G','C'],'M':['A','C'], 'K':['G','T'], 'B':['C','G','T'], 'D':['A','G','T'], 'H':['A','C','T'], 'V':['A','C','G']}
        reverse_codon = {'F': ['TTT', 'TTC'],'L': ['TTA', 'TTG', 'CTT', 'CTC', 'CTA', 'CTG'], 'I': ['ATT', 'ATC', 'ATA'], 'M': ['ATG'],
                         'V': ['GTT', 'GTC', 'GTA', 'GTG'], 'S': ['TCT', 'TCC', 'TCA', 'TCG', 'AGT', 'AGC'], 'P': ['CCT', 'CCC', 'CCA', 'CCG'],
                         'T': ['ACT', 'ACC', 'ACA', 'ACG'], 'A': ['GCT', 'GCC', 'GCA', 'GCG'], 'Y': ['TAT', 'TAC'], '*': ['TAA', 'TAG', 'TGA'],
                         'H': ['CAT', 'CAC'], 'Q': ['CAA', 'CAG'], 'N': ['AAT', 'AAC'], 'K': ['AAA', 'AAG'], 'D': ['GAT', 'GAC'], 'E': ['GAA', 'GAG'],
                         'C': ['TGT', 'TGC'], 'W': ['TGG'], 'R': ['CGT', 'CGC', 'CGA', 'CGG', 'AGA', 'AGG'], 'G': ['GGT', 'GGC', 'GGA', 'GGG']}
        for enzyme, site in zip(elist, slist):
            overhangbases = ''
            length = len(patterns[enzyme])
            pattern = patterns[enzyme]
            site = int(site) - self.rf
            pseq = str(self.seq)[int(site):int(site)+length]
            overhang = len(pseq)%3
            if overhang != 0:
                overhangbases = pseq[-overhang:]
            j, k = 0, 0
            p = int(site)
            insert = ''
            translation = str(Seq.translate(Seq(pseq)))
            ptrans = str(Seq.translate(Seq(pattern)))
            for char in translation:
                if char == ptrans[j]:
                    insert += patterns[enzyme][k:k+3]
                else:
                    a = patterns[enzyme][k:k+3]
                    codons = reverse_codon[char]
                    onepos, twopos, threepos = [], [], []
                    for codon in codons:
                        m = 0
                        for cchar in codon:
                            if m == 0:
                                if cchar not in onepos:
                                    onepos.append(cchar)
                            elif m == 1:
                                if cchar not in twopos:
                                    twopos.append(cchar)
                            elif m == 2:
                                if cchar not in threepos:
                                    threepos.append(cchar)
                            m +=1
                    m, insert1, choicelist = 0, '', []
                    for pchar in a:
                        if m == 0:
                            if pchar not in ambigs:
                                if pchar not in onepos:
                                    insert1 += 'X'
                                else:
                                    a = filter(lambda x: x.endswith(pchar), codons)
                                    for cdn in a:
                                        choicelist.append(cdn)
                            else:
                                charlist = ambigs[pchar]
                                flag = 0
                                for character in charlist:
                                    if character in onepos:
                                        a = filter(lambda x: x.startswith(character), codons)
                                        for cdn in a:
                                            choicelist.append(cdn)
                                        flag =1
                                if flag == 0:
                                    insert1 += 'X'
                        elif m ==1:
                            scndchoicelist = []
                            if pchar not in ambigs:
                                if pchar not in twopos:
                                    insert1 += 'X'
                                else:
                                    a = filter(lambda x: x.endswith(pchar), choicelist)
                                    choicelist = []
                                    for cdn in a:
                                        scndchoicelist.append(cdn)
                            else:
                                charlist = ambigs[pchar]
                                flag = 0
                                for character in charlist:
                                    if character in twopos:
                                        a = filter(lambda x: x[1] == character, choicelist)
                                        for cdn in a:
                                            scndchoicelist.append(cdn)
                                        flag =1
                                if flag == 0:
                                    insert1 += 'X'
                        elif m ==2:
                            thrdchoicelist = []
                            if pchar not in ambigs:
                                if pchar not in threepos:
                                    insert1 += 'X'
                                else:
                                    a = filter(lambda x: x.endswith(pchar), scndchoicelist)
                                    choicelist = []
                                    for cdn in a:
                                        thrdchoicelist.append(cdn)
                            else:
                                charlist = ambigs[pchar]
                                flag = 0
                                for character in charlist:
                                    if character in threepos:
                                        a = filter(lambda x: x.endswith(character), scndchoicelist)
                                        choicelist = []
                                        for cdn in a:
                                            thrdchoicelist.append(cdn)
                                        flag =1
                                if flag == 0:
                                    insert1 += 'X'
                        m +=1
                    if 'X' not in insert1:
                        if self.seq[p:p+3] in thrdchoicelist:
                            insert += self.seq[p:p+3]
                        else:
                            insert += random.choice(thrdchoicelist)
                    else:
                        insert += 'X'
                k +=3
                p +=3    
                j += 1
            insert = insert + overhangbases
            self.new_seq = self.new_seq[:int(site)] +insert+ self.new_seq[int(site)+len(insert):]
            self.OrigSeq.SetValue(self.seq)
            self.NewSeq.SetValue(self.new_seq)
        h, color_list = 0, []
        for char in self.new_seq:
            if self.seq[h] != char:
                color_list.append(h)
            h +=1
        for num in color_list:
            self.NewSeq.SetStyle(num, num+1, wx.TextAttr('red', 'white'))
            
class OptimizationPanel(wx.Panel):
    #Frame for generating candidate vaccine strands. Options are Deoptimize codons in the sequence, Optimize codons in the sequence, and build in Attenuating mutations
    def __init__(self, parent, id, nb, mainframe):
        wx.Panel.__init__(self, parent)
        self.previous_seq = ['']
        self.left_range, self.right_range = 0, 0
        self.specific = False
        self.codon_list, self.cdn_list = [], []
        self.nb = self.GetParent()
        self.seq_disp_label = wx.StaticText(self, wx.ID_ANY,"Sequence: ")
        self.seq_disp = wx.TextCtrl(self, size = (475,200), style = wx.TE_PROCESS_ENTER|wx.TE_MULTILINE)
        self.seq_disp.Bind(wx.EVT_TEXT, lambda evt, previous = self.previous_seq: self.seq_value(previous))
        self.seq_disp.Bind(wx.EVT_KEY_UP, self.update_seq_disp)
        self.seq_disp.Bind(wx.EVT_SET_FOCUS, self.GetParent().GetParent().GetParent().on_focus)
        self.seq_disp.name = 'SeqDisp'
        self.aa_dispLabel = wx.StaticText(self, wx.ID_ANY, 'Amino Acid Sequence:')
        self.new_aa_disp_label = wx.StaticText(self, wx.ID_ANY, 'New Amino Acid Sequence:')
        self.aa_disp = wx.TextCtrl(self, size = (275,100), style = wx.TE_PROCESS_ENTER|wx.TE_MULTILINE)
        self.new_aa_disp = wx.TextCtrl(self, size = (275,100), style = wx.TE_PROCESS_ENTER|wx.TE_MULTILINE)
        self.new_seq_disp_label = wx.StaticText(self, wx.ID_ANY,"New Sequence: ")
        self.new_seq_disp = wx.TextCtrl(self, size = (475,200), style = wx.TE_PROCESS_ENTER|wx.TE_MULTILINE)
        self.new_seq_disp.Bind(wx.EVT_TEXT, self.allow_export)
        self.deoptimizer_button = wx.Button(self, -1, 'Deoptimize Codons')
        self.deoptimizer_button.Bind(wx.EVT_LEFT_DOWN, self.call_deoptimize)
        self.optimizer_button = wx.Button(self, -1, 'Optimize Codons')
        self.optimizer_button.Bind(wx.EVT_LEFT_DOWN, self.call_optimize)
        self.export_button = wx.Button(self, -1, 'Export')
        self.export_button.Bind(wx.EVT_LEFT_DOWN, self.export)
        self.export_button.Disable()
        self.reading_frame_button = wx.Button(self, -1, 'Reading Frame')
        self.reading_frame_button.Bind(wx.EVT_LEFT_DOWN, self.reading_frame)
        self.reversion_box = wx.CheckBox(self, 10,'Avoid Reversion')
        self.seq_freq = wx.CheckBox(self, 10, 'Use Sequence Codon Frequency to Optimize/Deoptimize')
        self.reversion_box.SetValue(True)
        self.seq_freq.SetValue(True)
        self.deoptimize_label = wx.StaticText(self, wx.ID_ANY, 'Deoptimization Range:')
        self.deoptimize_left = wx.TextCtrl(self, size = (40,20), style = wx.TE_PROCESS_ENTER)
        self.deoptimize_left.Bind(wx.EVT_TEXT, self.deoptimize_ranges)
        self.deoptimize_colon = wx.StaticText(self, wx.ID_ANY, ':')
        self.deoptimize_right = wx.TextCtrl(self, size = (40, 20), style = wx.TE_PROCESS_ENTER)
        self.optimize_label = wx.StaticText(self, wx.ID_ANY, 'Optimization Range:')
        self.optimize_left = wx.TextCtrl(self, size = (40,20), style = wx.TE_PROCESS_ENTER)
        self.optimize_left.Bind(wx.EVT_TEXT, self.optimize_ranges)
        self.optimize_colon = wx.StaticText(self, wx.ID_ANY, ':')
        self.optimize_right = wx.TextCtrl(self, size = (40, 20), style = wx.TE_PROCESS_ENTER)
        self.specific_text_info = wx.StaticText(self, wx.ID_ANY, '(De)Optimize specific amino acids or codons. Enter amino acids/abbreviations (1 or 3 letters) or codons separated by commas. Values can be excluded by placing an exclamation mark before the value.\n\
For example, the entry:   G, !GGT     instructs the program to optimize all of the codons for glycine except GGT.\n\
To specify a range for the optimization use the boxes above.\n\
If you do want to de(optimize) all codons click the buttons above or type ALL into the box\n\
ALL can also be used in conjunction with !, so ALL, !G optimizes codons for all amino acids except glycine.\nPress enter to submit:')
        self.specific_text = wx.TextCtrl(self, size = (795, 20), style = wx.TE_PROCESS_ENTER)
        self.specific_text.Bind(wx.EVT_TEXT_ENTER, self.specific_optimization)
        self.specific_opt_button = wx.RadioButton(self, wx.ID_ANY, 'Optimize')
        self.specific_deopt_button = wx.RadioButton(self, wx.ID_ANY, 'Deoptimize')
        self.specific_deopt_button.SetValue(1)
        self.rna_structure = wx.CheckBox(self, 11, 'RNA Secondary Structure')
        self.reset_button = wx.Button(self, -1, 'Reset')
        self.reset_button.Bind(wx.EVT_LEFT_DOWN, self.reset)
        self.pseudoknot = wx.Button(self, -1, 'Detect Pseudoknots')
        self.pseudoknot.Bind(wx.EVT_LEFT_DOWN, self.pseudoknot_detect)
        self.pseudoknot_disp = wx.TextCtrl(self, size = (500, 150), style = wx.TE_MULTILINE)
        self.pseudoknot_label = wx.StaticText(self, wx.ID_ANY, 'Pseudoknots:')
        #Create and add objects to sizers
        self.seqsizer = wx.BoxSizer(wx.VERTICAL)
        self.aasizer = wx.BoxSizer(wx.VERTICAL)
        self.new_seq_sizer = wx.BoxSizer(wx.VERTICAL)
        self.new_seq_label_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.new_aa_sizer = wx.BoxSizer(wx.VERTICAL)
        self.total_seq_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.total_aa_sizer = wx.BoxSizer(wx.VERTICAL)
        self.buttonsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.deoptimizerangesizer = wx.BoxSizer(wx.HORIZONTAL)
        self.optimizerangesizer = wx.BoxSizer(wx.HORIZONTAL)
        self.totalsizer = wx.BoxSizer(wx.VERTICAL)
        self.opt_ops_sizer = wx.BoxSizer(wx.VERTICAL)
        self.reversionsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.specific_text_sizer = wx.BoxSizer(wx.VERTICAL)
        self.specific_button_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.pseudoknot_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.specific_text_sizer.AddMany([(self.specific_text_info, 0, wx.TOP, 10), (self.specific_text, 0, wx.TOP, 10)])
        self.specific_button_sizer.AddMany([self.specific_deopt_button, self.specific_opt_button])
        self.seqsizer.AddMany([(self.seq_disp_label, 0, wx.TOP|wx.LEFT,5), (self.seq_disp, 0, wx.TOP|wx.LEFT|wx.RIGHT, 5)])
        self.aasizer.AddMany([(self.aa_dispLabel, 0, wx.TOP|wx.LEFT,5), (self.aa_disp, 0, wx.TOP|wx.LEFT, 5)])
        self.new_seq_label_sizer.AddMany([self.new_seq_disp_label, (self.export_button, 0, wx.LEFT, 5)])
        self.new_seq_sizer.AddMany([(self.new_seq_label_sizer, 0, wx.TOP|wx.LEFT, 5), (self.new_seq_disp, 0, wx.TOP|wx.LEFT, 2)])
        self.new_aa_sizer.AddMany([(self.new_aa_disp_label, 0, wx.TOP|wx.LEFT,5), (self.new_aa_disp, 0, wx.TOP|wx.LEFT, 5)])
        self.total_aa_sizer.AddMany([self.aasizer, self.new_aa_sizer, (self.reading_frame_button, 0, wx.TOP, 5)])
        self.total_seq_sizer.AddMany([self.seqsizer, self.new_seq_sizer, self.total_aa_sizer])
        self.deoptimizerangesizer.AddMany([self.deoptimize_label, (self.deoptimize_left, 0, wx.LEFT, 5), self.deoptimize_colon, self.deoptimize_right])
        self.optimizerangesizer.AddMany([self.optimize_label, (self.optimize_left, 0, wx.LEFT, 5), self.optimize_colon, self.optimize_right])
        self.buttonsizer.AddMany([(self.deoptimizer_button, 0, wx.TOP, -25), (self.optimizer_button, 0, wx.TOP, -25)]) #,(self.attenuator_button, 0 ,wx.TOP, -25)])
        self.reversionsizer.AddMany([(self.reversion_box, 0, wx.RIGHT, 10), self.seq_freq, (self.rna_structure)])
        self.pseudoknot_sizer.AddMany([self.pseudoknot, (self.pseudoknot_label, 0, wx.LEFT, 20), (self.pseudoknot_disp, 0, wx.LEFT, 10)])
        self.opt_ops_sizer.AddMany([(self.buttonsizer, 0 , wx.TOP, -25), (self.reversionsizer, 0, wx.TOP|wx.BOTTOM, 5), self.deoptimizerangesizer, (self.optimizerangesizer, 0, wx.TOP, 10)])
        self.totalsizer.AddMany([self.total_seq_sizer, (self.opt_ops_sizer, 0, wx.TOP|wx.LEFT, 5), (self.specific_text_sizer, 0, wx.TOP|wx.LEFT, 5), (self.specific_button_sizer, 0, wx.TOP|wx.LEFT, 5), (self.pseudoknot_sizer, 0, wx.TOP|wx.LEFT, 10),(self.reset_button, 0, wx.TOP, -10),])
        self.SetSizerAndFit(self.totalsizer)
        
    def reset(self, event):
        self.seq_disp.SetValue("")
        self.GetParent().GetPage(0).seq_gc_disp.SetValue("")
        self.GetParent().GetPage(0).vector_disp.SetValue("")
        self.GetParent().GetPage(0).mutation_aa_disp.SetValue("")
        self.GetParent().GetPage(0).mutation_seq_disp.SetValue("")
        self.GetParent().GetPage(0).mutation_seq_gc_disp.SetValue("")
        self.GetParent().GetPage(0).position_disp.SetValue("")
        self.GetParent().GetPage(0).enzyme_listbox.SetSelection(-1)
        self.rf = 1
        self.GetParent().GetPage(0).onecut.SetValue(True)
        self.GetParent().GetPage(0).twocut.SetValue(False)
        self.GetParent().GetPage(0).threecut.SetValue(False)
        self.GetParent().GetPage(0).allcut.SetValue(False)
        self.GetParent().GetPage(0).export_button.Disable()
        self.GetParent().GetPage(0).silent.SetValue(True)
        self.GetParent().GetPage(0).num.SetValue(1)
        self.GetParent().GetPage(0).num_mutants.SetValue(1)
        self.GetParent().GetPage(0).num_aa_mutations.SetValue(1)
        self.GetParent().GetPage(0).reversion_box.SetValue(False)
        self.GetParent().GetPage(0).vector_listbox.SetSelection(-1)
        self.GetParent().GetPage(0).aa_left_mutation_range.SetValue("")
        self.GetParent().GetPage(0).aa_right_mutation_range.SetValue("")
        #self.GetParent().GetPage(0).fragment_length_disp.SetValue("")
        #self.GetParent().GetPage(0).overlap_length_disp.SetValue("")
        self.GetParent().GetPage(0).commercial_box.SetValue(False)
        self.GetParent().GetPage(0).left_range_out.SetValue("")
        self.GetParent().GetPage(0).left_mutation_range.SetValue("")
        self.GetParent().GetPage(0).left_range_in.SetValue("")
        self.GetParent().GetPage(0).right_range_out.SetValue("")
        self.GetParent().GetPage(0).right_mutation_range.SetValue("")
        self.GetParent().GetPage(0).right_range_in.SetValue("")
        self.seq_disp.SetValue("")
        self.new_seq_disp.SetValue("")
        self.aa_disp.SetValue("")
        self.new_aa_disp.SetValue("")
        self.deoptimize_left.SetValue("")
        self.deoptimize_right.SetValue("")
        self.optimize_left.SetValue("")
        self.optimize_right.SetValue("")
        self.reversion_box.SetValue(0)
        self.seq_freq.SetValue(0)
        self.specific_text.SetValue("")
        self.specific_deopt_button.SetValue(1)
        self.export_button.Disable()
        self.GetParent().GetPage(0).rf =1
        self.GetParent().GetParent().GetParent().organisms.Check(104,1)
        
    def pseudoknot_detect(self, event):
        file = './tmp.fasta'
        with open ('tmp.fasta', 'w') as filename:
            filename.write('>\n' + str(self.seq_disp.GetValue()))
        #os.system('python KnotSeeker.py %s' %file)
        KnotSeeker.maincall(file)
        i, string = 0, ""
        with open('output.txt', 'r') as file:
            for line in file:
                if i == 0:
                    string = string + 'Pseudoknot start:' + line
                if i == 1:
                    string = string + 'Pseudoknot end:' + line
                if i == 2:
                    string = string + 'Energy:' + line
                if i == 3:
                    string = string + line + '\n'
                    i = -1
                i += 1
        self.pseudoknot_disp.SetValue(string)
        os.remove('output.txt')
        os.remove('pknotsRG_input.txt')
        os.remove('pknotsRG_output.txt')
        os.remove('guugle_output.txt')
        os.remove('hairpin_bulge.txt')
        os.remove('stem_structure.txt')
        os.remove('stems_energy.txt')
        os.remove('tmp.fasta')
        os.remove('input.fasta')
                         
    def specific_optimization(self, event):
        #Method which allows user to specify specific amino acids or codons to optimize
        self.specific = True
        string = str(self.specific_text.GetValue()).upper()
        codons = codon_usage_db.db.codon_tables(codon_usage_db.db())
        cdns= ['TTT', 'TTC', 'TTA', 'TTG', 'TCT', 'TCC', 'TCA', 'TCG', 'TAT', 'TAC', 'TAA', 'TAG', 'TGT', 'TGC', 'TGA', 'TGG',
                      'CTT', 'CTC', 'CTA', 'CTG', 'CCT', 'CCC', 'CCA', 'CCG', 'CAT', 'CAC', 'CAA', 'CAG', 'CGT', 'CGC', 'CGA', 'CGG',
                      'ATT', 'ATC', 'ATA', 'ATG', 'ACT', 'ACC', 'ACA', 'ACG', 'AAT', 'AAC', 'AAA', 'AAG', 'AGT', 'AGC', 'AGA', 'AGG',
                      'GTT', 'GTC', 'GTA', 'GTG', 'GCT', 'GCC', 'GCA', 'GCG', 'GAT', 'GAC', 'GAA', 'GAG', 'GGT', 'GGC', 'GGA', 'GGG']
        aa_list, bad_codons, self.cdn_list, self.codon_list = [], [], [], []
        values = string.split(',')
        amino_acids = {'A': 'ALANINE', 'R': 'ARGININE', 'N': 'ASPARAGINE', 'D': 'ASPARTIC ACID', 'C': 'CYSTEINE', 'E': 'GLUTAMIC ACID', 'Q': 'GLUTAMINE', 'G': 'GLYCINE', 'H': 'HISTIDINE', 'I': 'ISOLEUCINE', 'L': 'LEUCINE',
                       'K': 'LYSINE', 'M': 'METHIONINE', 'F': 'PHENYLALANINE', 'P': 'PROLINE', 'S': 'SERINE', 'T': 'THREONINE', 'W': 'TRYPTOPHAN', 'Y': 'TYROSINE', 'V': 'VALINE'}
        three_letter_abbr = {'A': 'ALA', 'R': 'ARG', 'N': 'ASN', 'D': 'ASP', 'C': 'CYS', 'E': 'GLU', 'Q': 'GLN', 'G': 'GLY', 'H': 'HIS', 'I': 'ILE', 'L': 'LEU', 'K': 'LYS', 'M': 'MET', 'F': 'PHE', 'P': 'PRO', 'S': 'SER', 'T': 'THR', 'W': 'TRP', 'Y': 'TYR', 'V': 'VAL'}
        for item in values:
            item = item.strip(' ')
            item = item.upper()
            if item not in amino_acids.keys() and item not in amino_acids.values() and item not in three_letter_abbr.values() and item not in cdns and not item.startswith('!') and item != 'ALL':
                dlg = wx.MessageDialog(self, 'Invalid Entry: %s' %item, 'Entry Error Warning', wx.ICON_EXCLAMATION, wx.OK)
                dlg.ShowModal()
                dlg.Destroy()
            elif item == 'ALL':
                self.cdn_list = cdns
            elif len(item) == 1 and item not in aa_list:
                self.cdn_list += codons[1][item]
                aa_list.append(item)
            elif len(item) == 3 and [k for k, v in three_letter_abbr.iteritems() if v == item][0] not in aa_list:
                if item in three_letter_abbr.values():
                        self.cdn_list += codons[1][([k for k, v in three_letter_abbr.iteritems() if v == item][0])]
                        aa_list.append([k for k, v in three_letter_abbr.iteritems() if v == item][0])
                else:
                    self.cdn_list.append(item)
            elif item.startswith('!'):
                item = item.strip('!').upper()
                if item not in amino_acids.keys() and item not in amino_acids.values() and item not in three_letter_abbr.values() and item not in cdns:
                    dlg = wx.MessageDialog(self, 'Invalid Entry: %s' %item, 'Entry Error Warning', wx.ICON_EXCLAMATION|wx.OK)
                    dlg.ShowModal()
                    dlg.Destroy()
                elif len(item) == 1:
                    bad_codons += codons[1][item]
                elif len(item) == 3:
                    if item in three_letter_abbr.values():
                        bad_codons += codons[1][([k for k, v in three_letter_abbr.iteritems() if v == item][0])]
                    else:
                        bad_codons += [item]
                else:
                    bad_codons += codons[1][([k for k, v in amino_acids.iteritems() if v == item][0])]
            elif [k for k, v in amino_acids.iteritems() if v == item][0] not in aa_list:
                self.cdn_list += codons[1][([k for k, v in amino_acids.iteritems() if v == item][0])]
                aa_list.append([k for k, v in amino_acids.iteritems() if v == item][0])
        for codon in self.cdn_list:
            if codon not in bad_codons:
                self.codon_list.append(codon)
        if self.specific_deopt_button.GetValue():
            self.deoptimize()
        if self.specific_opt_button.GetValue():
            self.optimize()
        
    def export(self, event):
        #Export new sequence 
        dlg = wx.TextEntryDialog(None, 'Enter a name for the file', 'Filename', '.fasta') #Get filename
        if dlg.ShowModal() == wx.ID_OK:
            filename = str(dlg.GetValue())
        dlg.Destroy()
        text = str(self.new_seq_disp.GetValue())
        if not os.path.exists(filename): #Write sequence to file
            file = open(filename, 'w')
            file.write(">"+filename+'\n')
            file.write(text)
            file.close()

    def allow_export(self, event):
        if str(self.new_seq_disp.GetValue()) != '':
            self.export_button.Enable()
            
    def update_seq_disp(self, event):
        #Updates the sequence display on the mutation panel to reflect the sequence display on the optimization panel
        current = self.seq_disp.GetInsertionPoint()
        str(self.seq_disp.SetValue(filter(lambda x: x.isalpha() and (x is 'A' or x is 'C' or x is 'G' or x is 'T' or x is 'U' or x is 'a' or x is 'c' or x is 'g' or x is 't' or x is 'u' or x is 'N' or x is 'n'), str(self.seq_disp.GetValue().upper()))))
        self.seq_disp.SetInsertionPoint(current)
        self.GetParent().GetPage(0).seq_disp.SetValue(str(self.seq_disp.GetValue()))
        
    def reading_frame(self, event):
        #Allows user to select reading frame
        self.GetParent().GetPage(0).select_reading_frame(event)
        
    def deoptimize_ranges(self, event):
        #Sets value of the end range equal to beginning range when altered initially to ensure that a value is entered for the end range
        self.deoptimize_left.SetValue(filter(lambda x: x.isdigit(), self.deoptimize_left.GetValue()))
        self.deoptimize_left.SetValue(self.deoptimize_left.GetValue())
        
    def optimize_ranges(self, event):
        #Ensures that end range is set for optimization range
        self.optimize_left.SetValue(filter(lambda x: x.isdigit(), self.optimize_left.GetValue()))
        self.optimize_left.SetValue(self.optimize_left.GetValue())
        
    def seq_value(self, previous_seq):   
    #Creates a list of previous values in sequence display for undo/redo
        seq = str(self.seq_disp.GetValue())
        length = len(previous_seq)
        if seq != '' and len(previous_seq) > 0:
            if seq != previous_seq[length-1]:    
                previous_seq.insert(0,seq)
                
    def get_organism(self):
        #Get codon usage for organism
        codon_list = ['TTT', 'TTC', 'TTA', 'TTG', 'TCT', 'TCC', 'TCA', 'TCG', 'TAT', 'TAC', 'TAA', 'TAG', 'TGT', 'TGC', 'TGA', 'TGG', 'CTT', 'CTC', 'CTA', 'CTG', 'CCT', 'CCC',
                      'CCA', 'CCG', 'CAT', 'CAC', 'CAA', 'CAG', 'CGT', 'CGC', 'CGA', 'CGG', 'ATT', 'ATC', 'ATA', 'ATG', 'ACT', 'ACC', 'ACA', 'ACG', 'AAT', 'AAC', 'AAA', 'AAG',
                      'AGT', 'AGC', 'AGA', 'AGG', 'GTT', 'GTC', 'GTA', 'GTG', 'GCT', 'GCC', 'GCA', 'GCG', 'GAT', 'GAC', 'GAA', 'GAG', 'GGT', 'GGC', 'GGA', 'GGG'] 
        organism = str(self.GetParent().GetParent().GetParent().get_organism())
        percent_table = self.GetParent().GetPage(0).codon_usage_retrieve(codon_list, organism)
        return percent_table
    
    def use_avoid_reversion(self):
        #Get value from Avoid Reversion Box
        if self.reversion_box.GetValue():
            return True
 
    def call_deoptimize(self, event):
        self.deoptimize()
        
    def deoptimize(self):
        #Replace codons with codons used least frequently by selected organism
        new_seq, new_dict = '', {}
        percentages = self.get_organism()
        cdns = ['TTT', 'TTC', 'TTA', 'TTG', 'TCT', 'TCC', 'TCA', 'TCG', 'TAT', 'TAC', 'TAA', 'TAG', 'TGT', 'TGC', 'TGA', 'TGG',
                      'CTT', 'CTC', 'CTA', 'CTG', 'CCT', 'CCC', 'CCA', 'CCG', 'CAT', 'CAC', 'CAA', 'CAG', 'CGT', 'CGC', 'CGA', 'CGG',
                      'ATT', 'ATC', 'ATA', 'ATG', 'ACT', 'ACC', 'ACA', 'ACG', 'AAT', 'AAC', 'AAA', 'AAG', 'AGT', 'AGC', 'AGA', 'AGG',
                      'GTT', 'GTC', 'GTA', 'GTG', 'GCT', 'GCC', 'GCA', 'GCG', 'GAT', 'GAC', 'GAA', 'GAG', 'GGT', 'GGC', 'GGA', 'GGG']
        if self.specific:
            cdns = self.codon_list
        seq_cdn_dict = self.GetParent().GetPage(0).codon_dict(str(self.GetParent().GetPage(0).seq_disp.GetValue()))
        for cdn, number in seq_cdn_dict[0].iteritems():
            new_dict[cdn] = float(number*100)/float(seq_cdn_dict[1])
        if self.seq_freq.GetValue():
            percentages = new_dict
        backtable = codon_usage_db.db().codon_tables()[1]
        self.rf = self.GetParent().GetPage(0).rf
        self.seq = str(self.seq_disp.GetValue())
        self.old_rna_seq = Seq.transcribe(Seq(self.seq))
        if self.rna_structure.GetValue():
            self.create_fasta('old_rna.fna', self.old_rna_seq)
            os.system('gtfold old_rna.fna')
            os.remove('./old_rna.fna')
            pairs = rfc.CT_to_DB.read_file(rfc.CT_to_DB(), 'old_rna.fna.ct')
            old_delta_g = filter(lambda x: x.isdigit() or x is '-' or x is '.', pairs[2])
            old_structure = rfc.CT_to_DB.dot_bracket(rfc.CT_to_DB(), pairs[0], pairs[1])
            paired = self.is_paired(old_structure)
        if not self.rna_structure.GetValue():
            paired = []
        reversion = self.use_avoid_reversion()
        if self.rf == 1:
            translation = Seq.translate(Seq(self.seq))
        elif self.rf == 2:
            translation = Seq.translate(Seq(self.seq[1:]))
        elif self.rf == 3:
            translation = Seq.translate(Seq(self.seq[2:]))
        if self.deoptimize_left.GetValue():
            self.left_range = int(self.deoptimize_left.GetValue())/3
            self.right_range = int(self.deoptimize_right.GetValue())/3
            if self.left_range < 0:
                self.left_range = 0
            if self.right_range < self.left_range:
                self.right_range = self.left_range
            if self.left_range > self.right_range:
                self.left_range = self.right_range
        else:
            self.left_range = 0
            self.right_range = len(self.seq)
        i = 0
        for char in translation[self.left_range:self.right_range]:
            proceed = False
            original_codon = self.seq[i:i+3]
            codon_range = range(i, i+3)
            for num in codon_range:
                if num not in paired:
                    proceed = True
                else:
                    proceed = False
                    break
            if proceed == True and original_codon in cdns:
                    value = 101
                    cdn = ''
                    codons = backtable[char]
                    if reversion:
                        for codon in codons:
                            if codon in percentages:
                                if self.GetParent().GetPage(0).hamming_distance(codon, original_codon) > 1:
                                    new_value = percentages[codon]
                                    if new_value < value:
                                        value = new_value
                                        cdn = codon
                                if cdn == '':
                                    value = 101
                                    for codon in codons:
                                        try:
                                            new_value = percentages[codon]
                                        except KeyError:
                                            pass
                                        if new_value < value:
                                            value = new_value
                                            cdn = codon
                        new_seq += cdn
                    else:
                        for codon in codons:
                            if codon in percentages:
                                try:
                                    new_value = percentages[codon]
                                except KeyError:
                                    pass
                                if new_value < value:
                                    value = new_value
                                    cdn = codon
                        new_seq += cdn
            else:
                new_seq += original_codon
            i += 3
        new_seq = self.seq[:self.left_range*3] + new_seq + self.seq[self.left_range*3+len(new_seq):]
        new_rna_seq = Seq.transcribe(Seq(new_seq))
        if 'U' in self.seq:
            new_seq = str(new_rna_seq)
        #new_rna = str(rna_folding.Nussinov(None, -1, new_seq).structure())
        self.new_seq_disp.SetValue(new_seq)
        if self.rf == 1:
            self.new_aa_disp.SetValue(str(Seq.translate(Seq(new_seq))))
        elif self.rf == 2:
            self.new_aa_disp.SetValue(str(Seq.translate(Seq(new_seq)[1:])))
        elif self.rf == 3:
            self.new_aa_disp.SetValue(str(Seq.translate(Seq(new_seq)[2:])))
        if self.rna_structure.GetValue():
            self.create_fasta('new_rna.fna', new_rna_seq)
            os.system('gtfold new_rna.fna')
            os.remove('./new_rna.fna')
            pairs = rfc.CT_to_DB.read_file(rfc.CT_to_DB(), 'new_rna.fna.ct')
            new_delta_g = filter(lambda x: x.isdigit() or x is '-' or x is '.', pairs[2])
            new_structure = rfc.CT_to_DB.dot_bracket(rfc.CT_to_DB(), pairs[0], pairs[1])
        else:
            old_structure, new_structure, old_delta_g, new_delta_g = '', '', '', ''
        number = 0
        if self.rna_structure.GetValue():
            for page in self.nb.GetChildren():
                if hasattr(page, 'name'):
                    if page.name == 'RNApanel':
                        self.nb.DeletePage(number)
                number += 1
            rna_panel = rna_folding.RNAPanel(self.nb, -1, old_structure, old_delta_g, new_structure, new_delta_g)
            self.nb.AddPage(rna_panel, 'RNA')
            self.nb.SetSelection(self.nb.GetPageCount()-1)
    
    def call_optimize(self, event):
        self.optimize()
               
    def optimize(self):
        #Replace codons in sequence with codons used most frequently by selected organism
        new_seq, paired, new_dict = '', [], {}
        percentages = self.get_organism()
        cdns = ['TTT', 'TTC', 'TTA', 'TTG', 'TCT', 'TCC', 'TCA', 'TCG', 'TAT', 'TAC', 'TAA', 'TAG', 'TGT', 'TGC', 'TGA', 'TGG',
                      'CTT', 'CTC', 'CTA', 'CTG', 'CCT', 'CCC', 'CCA', 'CCG', 'CAT', 'CAC', 'CAA', 'CAG', 'CGT', 'CGC', 'CGA', 'CGG',
                      'ATT', 'ATC', 'ATA', 'ATG', 'ACT', 'ACC', 'ACA', 'ACG', 'AAT', 'AAC', 'AAA', 'AAG', 'AGT', 'AGC', 'AGA', 'AGG',
                      'GTT', 'GTC', 'GTA', 'GTG', 'GCT', 'GCC', 'GCA', 'GCG', 'GAT', 'GAC', 'GAA', 'GAG', 'GGT', 'GGC', 'GGA', 'GGG']
        if self.specific:
            cdns = self.codon_list
        seq_cdn_dict = self.GetParent().GetPage(0).codon_dict(str(self.GetParent().GetPage(0).seq_disp.GetValue()))
        for cdn, number in seq_cdn_dict[0].iteritems():
            new_dict[cdn] = float(number*100)/float(seq_cdn_dict[1])
        if self.seq_freq.GetValue():
            percentages = new_dict
        backtable = codon_usage_db.db().codon_tables()[1]
        self.rf = self.GetParent().GetPage(0).rf
        self.seq = str(self.seq_disp.GetValue())
        self.old_rna_seq = Seq.transcribe(Seq(self.seq))
        if self.rna_structure.GetValue():
            self.create_fasta('old_rna.fna', self.old_rna_seq)
            os.system('gtfold old_rna.fna')
            os.remove('./old_rna.fna')
            pairs = rfc.CT_to_DB.read_file(rfc.CT_to_DB(), 'old_rna.fna.ct')
            old_delta_g = filter(lambda x: x.isdigit() or x is '-' or x is '.', pairs[2])
            old_structure = rfc.CT_to_DB.dot_bracket(rfc.CT_to_DB(), pairs[0], pairs[1])
            paired = self.is_paired(old_structure)
        if not self.rna_structure:
            paired = []
        reversion = self.use_avoid_reversion()
        if self.rf == 1:
            translation = Seq.translate(Seq(self.seq))
        elif self.rf == 2:
            translation = Seq.translate(Seq(self.seq[1:]))
        elif self.rf == 3:
            translation = Seq.translate(Seq(self.seq[2:]))
        if self.optimize_left.GetValue():
            self.left_range = (int(self.optimize_left.GetValue())-1)/3
            self.right_range = (int(self.optimize_right.GetValue())-1)/3
        else:
            self.left_range = 0
            self.right_range = len(self.seq)
        i = 0
        for char in translation[self.left_range:self.right_range]:
            proceed = False
            original_codon = self.seq[i:i+3]
            codon_range = range(i, i+3)
            for num in codon_range:
                if num not in paired:
                    proceed = True
                else:
                    proceed = False
                    break
            if proceed == True and original_codon in cdns:
                    value, cdn = 0, ''
                    codons = backtable[char]
                    if reversion:
                        for codon in codons:
                            if codon in percentages:
                                if self.GetParent().GetPage(0).hamming_distance(codon, original_codon) > 1:
                                    new_value = percentages[codon]
                                    if new_value < value:
                                        value = new_value
                                        cdn = codon
                                if cdn == '':
                                    value = 101
                                    for codon in codons:
                                        try:
                                            new_value = percentages[codon]
                                        except KeyError:
                                            pass
                                        if new_value < value:
                                            value = new_value
                                            cdn = codon
                        new_seq += cdn
                    else:
                        for codon in codons:
                            if codon in percentages:
                                try:
                                    new_value = percentages[codon]
                                except KeyError:
                                    pass
                                if new_value < value:
                                    value = new_value
                                    cdn = codon
                        new_seq += cdn
            else:
                new_seq += original_codon
            i += 3
        new_seq = self.seq[:self.left_range*3] + new_seq + self.seq[self.left_range*3+len(new_seq):]
        new_rna_seq = Seq.transcribe(Seq(new_seq))
        self.new_seq_disp.SetValue(new_seq)
        if self.rf == 1:
            self.new_aa_disp.SetValue(str(Seq.translate(Seq(new_seq))))
        elif self.rf == 2:
            self.new_aa_disp.SetValue(str(Seq.translate(Seq(new_seq)[1:])))
        elif self.rf == 3:
            self.new_aa_disp.SetValue(str(Seq.translate(Seq(new_seq)[2:])))
        if self.rna_structure.GetValue():
            self.create_fasta('new_rna.fna', new_rna_seq)
            os.system('gtfold new_rna.fna')
            os.remove('./new_rna.fna')
            pairs = rfc.CT_to_DB.read_file(rfc.CT_to_DB(), 'new_rna.fna.ct')
            new_delta_g = filter(lambda x: x.isdigit() or x is '-' or x is '.', pairs[2])
            new_structure = rfc.CT_to_DB.dot_bracket(rfc.CT_to_DB(), pairs[0], pairs[1])
        else:
            old_structure, new_structure, old_delta_g, new_delta_g = '', '', '', ''
        number = 0
        if self.rna_structure.GetValue():
            for page in self.nb.GetChildren():
                if hasattr(page, 'name'):
                    if page.name == 'RNApanel':
                        self.nb.DeletePage(number)
                number += 1
            rna_panel = rna_folding.RNAPanel(self.nb, -1, old_structure, old_delta_g, new_structure, new_delta_g)
            self.nb.AddPage(rna_panel, 'RNA')
            self.nb.SetSelection(self.nb.GetPageCount()-1)
        
    def create_fasta(self, filename, sequence):
        with open(filename, 'w') as file:
            file.write('>%s\n %s' %(filename, sequence))
                
    def is_paired(self, structure):
        paired = []
        for char in range(len(structure)):
            if structure[char] == '(' or structure[char] == ')':
                paired.append(char)
        return paired
    
    def hamming_distance(self, s1, s2):
        #Calculate minimum number of changes to turn one string into another
        assert len(s1) == len(s2)
        return sum(ch1 != ch2 for ch1, ch2 in zip(s1, s2))
    
class CuttingPanel(wx.Panel):
    #Frame that displays restriction enzyme cutting results in four tables: enzymes that make blunt cuts, enzymes that split their cut downstream, enzymes that split that cut strands differently upstream, and enzymes that do not cut the sequence
    #Also has an option to mutate out restriction sites which are found
    def __init__(self, parent, id, search, blunt_dict, down_dict, up_dict, starts, splits, nohitlist, seq, methylation, title = 'Restriction Enzyme Cutting Results'):
        wx.Panel.__init__(self, parent)
        self.name = 'Cutting Panel'
        self.search, self.blunt_dict, self.down_dict, self.up_dict, self.nohitlist, self.starts, self.seq, self.enzyme_list = search, blunt_dict, down_dict, up_dict, nohitlist, starts, seq, []
        self.pattern_dict = Search().db_retrieve()[1]
        self.bluntlabel = wx.StaticText(self, wx.ID_ANY, 'Symmetric Cuts:')
        self.downlabel = wx.StaticText(self, wx.ID_ANY, 'Unsymmetric Downstream Cuts:')
        self.uplabel = wx.StaticText(self, wx.ID_ANY, 'Unsymmetric Upstream Cuts:')
        self.nocutlabel = wx.StaticText(self, wx.ID_ANY, 'No Cuts:')
        #self.highlight_text = wx.StaticText(self, wx.ID_ANY, 'Highlighted sites above may be blocked by methylation')
        self.bluntlc = wx.ListCtrl(self, -1, size = (360,300), style = wx.LC_REPORT)
        self.bluntlc.InsertColumn(0, 'Enzyme')
        self.bluntlc.InsertColumn(1, 'Top Strand Cuts')
        self.bluntlc.SetColumnWidth(0,80)
        self.bluntlc.SetColumnWidth(1,95)
        self.bluntlc.InsertColumn(2, 'Bottom Strand Cuts')
        self.bluntlc.SetColumnWidth(2,110)
        self.bluntlc.InsertColumn(3, 'Target Start')
        self.bluntlc.SetColumnWidth(3, 75)
        self.original_seq_label = wx.StaticText(self, wx.ID_ANY, 'Original Sequence:')
        self.new_seq_label = wx.StaticText(self, wx.ID_ANY, 'New Sequence:')
        self.original_seq = wx.TextCtrl(self, size = (450,200), style = wx.TE_READONLY|wx.TE_MULTILINE)
        self.new_seq = wx.TextCtrl(self, size = (450, 200), style = wx.TE_READONLY|wx.TE_MULTILINE | wx.TE_RICH2)
        #Create sizers
        self.bluntsizer = wx.BoxSizer(wx.VERTICAL)
        self.downsizer = wx.BoxSizer(wx.VERTICAL)
        self.upsizer = wx.BoxSizer(wx.VERTICAL)
        self.nosizer = wx.BoxSizer(wx.VERTICAL)
        self.lcsizer = wx.BoxSizer(wx.HORIZONTAL)
        self.old_sizer = wx.BoxSizer(wx.VERTICAL)
        self.new_sizer = wx.BoxSizer(wx.VERTICAL)
        self.disp_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.methylase_sizer = wx.BoxSizer(wx.VERTICAL)
        self.highlight_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.total_sizer = wx.BoxSizer(wx.VERTICAL)
        #Get enzyme list and reading frame
        if hasattr(self.GetParent(), 'name'): 
            if self.GetParent().name == 'Mutation Panel':
                self.enz_list = self.GetParent().GetParent().GetPage(0).enzyme_list
                self.rf = self.GetParent().GetParent().GetPage(0).enzyme_list
            else:
                self.enz_list = self.GetParent().GetPage(0).enzyme_list
                self.rf = self.GetParent().GetPage(0).rf
        else:
            self.enz_list = self.GetParent().GetPage(0).enzyme_list
            self.rf = self.GetParent().GetPage(0).rf
        start_dict, split_dict = {}, {}
        for enzyme in blunt_dict.iterkeys():
            self.enzyme_list.append(enzyme)
        for enzyme in down_dict.iterkeys():
            self.enzyme_list.append(enzyme)
        for enzyme in up_dict.iterkeys():
            self.enzyme_list.append(enzyme)
        methyl = self.retrieve_methylation(self.enzyme_list)
        methylation_ranges = []
        for key, value in sorted(methylation.iteritems(), reverse=True):
            if value == 'Dam':
                methylation_range = range(int(key)-1, int(key)+3)
            elif value == 'Dcm':
                methylation_range = range(int(key)-1, int(key)+4)
            methylation_ranges.append(methylation_range)
        self.methylase_text = wx.StaticText(self, wx.ID_ANY, 'E. coli Dam and Dcm \nmethylase patterns:')
        self.methylation_lc = wx.ListCtrl(self, -1, size = (225, 200), style = wx.LC_REPORT)
        self.methylation_lc.InsertColumn(0, 'Methylase')
        self.methylation_lc.InsertColumn(1, 'Sequence Start')
        self.methylation_lc.InsertColumn(2, 'Sequence End')
        self.methylation_lc.SetColumnWidth(0, 60)
        self.methylation_lc.SetColumnWidth(1, 85)
        self.methylation_lc.SetColumnWidth(2, 80)
        num_items_methyl = self.methylation_lc.GetItemCount()
        for key, value in sorted(methylation.iteritems(), reverse=True):
            self.methylation_lc.InsertStringItem(num_items_methyl, value)
            self.methylation_lc.SetStringItem(num_items_methyl, 1, str(key))
            if value == 'Dam':
                self.methylation_lc.SetStringItem(num_items_methyl, 2, str(int(key) + 3))
            elif value == 'Dcm':
                self.methylation_lc.SetStringItem(num_items_methyl, 2, str(int(key) + 4))
        i = 0
        if len(starts) > 0: #Sort list of blunt starts
            for enz in self.enz_list:
                if enz in blunt_dict:
                    start_dict[enz] = sorted(starts[i], reverse=True)
                    i +=1
        i = 0
        if len(splits) > 0: #Sort list of split starts
            for enz in self.enz_list:
                if enz in down_dict:
                    split_dict[enz] = sorted(splits[i], reverse=True)
                    i +=1
                elif enz in up_dict:
                    split_dict[enz] = sorted(splits[i], reverse=True)
                    i +=1
        num_items_blunt = self.bluntlc.GetItemCount()
        bluntlist, klist = [], []
        #Populate blunt list
        for k in sorted(blunt_dict.iterkeys(), reverse=True):
            v = blunt_dict[k]
            v = str(v).split(',')
            for num in xrange(len(v)):
                a = filter(lambda x: x.isdigit(), v[num])
                bluntlist.append(a)
                klist.append(k)
        j = 0
        methyl_blunt = []
        if len(blunt_dict) > 0:
            for key, site in zip(klist, bluntlist):
                start = sorted(start_dict[key])
                length = len(self.pattern_dict[key]) -1
                if j >= len(start):
                    j = 0
                if key in methyl[0]:
                    for methylation_range in methylation_ranges:
                        if (methyl[1][key] == 'Dam' and len(methylation_range) == 4) or (methyl[1][key] == 'Dcm' and len(methylation_range) == 5):
                            methylation_range = set(methylation_range)
                            pattern_range = set(range(start[j], start[j]+len(methyl[0][key])))
                            if methylation_range & pattern_range != ([]):
                                if num_items_blunt not in methyl_blunt:
                                    methyl_blunt.append(num_items_blunt)
                self.bluntlc.InsertStringItem(num_items_blunt, key)
                self.bluntlc.SetStringItem(num_items_blunt, 1, str(int(site)))
                self.bluntlc.SetStringItem(num_items_blunt, 2, str((int(start[j]) + length) -(int(site)-start[j])+1))
                self.bluntlc.SetStringItem(num_items_blunt, 3, str(int(start[j])))
                j +=1
                
        #for number in methyl_blunt:
        #    self.bluntlc.SetItemTextColour(number, 'Red')
        self.downlc = wx.ListCtrl(self, -1, size = (360, 300), style = wx.LC_REPORT)
        self.downlc.InsertColumn(0, 'Enzyme')
        self.downlc.SetColumnWidth(0, 80)
        self.downlc.InsertColumn(1, 'Top Strand Cuts')
        self.downlc.SetColumnWidth(1, 95)
        self.downlc.InsertColumn(2, 'Bottom Strand Cuts')
        self.downlc.SetColumnWidth(2, 110)
        self.downlc.InsertColumn(3, 'Target Start')
        self.downlc.SetColumnWidth(3, 75)
        num_items_down = self.downlc.GetItemCount()
        klist, downlist, uplist = [], [], []
        #Populate downstream list
        for k in sorted(down_dict.iterkeys(), reverse=True):
            v = down_dict[k]
            v = str(v).split(',')
            i = 0
            for num in v:
                a = filter(lambda x: x.isdigit(), v[i])
                if i%2 == 0:
                    downlist.append(a)
                    klist.append(str(k))
                else:
                    uplist.append(a)
                i += 1
        j = 0
        downlist.reverse()
        uplist.reverse()
        methyl_down = []
        if len(down_dict) > 0:
            for k, down, up in zip(klist, downlist, uplist):
                start = split_dict[k]
                if j >= len(start):
                    j = 0
                if k in methyl[0]:
                    for methylation_range in methylation_ranges:
                        if (methyl[1][k] == 'Dam' and len(methylation_range) == 4) or (methyl[1][k] == 'Dcm' and len(methylation_range) == 5):
                            methylation_range = set(methylation_range)
                            pattern_range = set(range(start[j], start[j]+len(methyl[0][k])))
                            if methylation_range & pattern_range != ([]):
                                if num_items_down not in methyl_down:
                                    methyl_down.append(num_items_down)
                self.downlc.InsertStringItem(num_items_down, k)
                self.downlc.SetStringItem(num_items_down, 1, str(int(down)))
                self.downlc.SetStringItem(num_items_down, 2, str(int(up)))
                self.downlc.SetStringItem(num_items_down, 3, str(int(start[j])))
                j+=1
                
        self.uplc = wx.ListCtrl(self, -1, size = (360, 300), style = wx.LC_REPORT)
        self.uplc.InsertColumn(0, 'Enzyme')
        self.uplc.SetColumnWidth(0, 80)
        self.uplc.InsertColumn(1, 'Top Strand Cuts')
        self.uplc.SetColumnWidth(1, 95)
        self.uplc.InsertColumn(2, 'Bottom Strand Cuts')
        self.uplc.SetColumnWidth(2, 110)
        self.uplc.InsertColumn(3, 'Target Start')
        self.uplc.SetColumnWidth(3, 75)
        num_items_up = self.uplc.GetItemCount()
        klist, downlist, uplist = [], [], []
        #Populate upstream list
        for k in sorted(up_dict.iterkeys(), reverse=True):
            v = up_dict[k]
            v = str(v).split(',')
            i = 0
            for num in v:
                a = filter(lambda x: x.isdigit(), v[i])
                if i%2 == 0:
                    downlist.append(a)
                    klist.append(str(k))
                else:
                    uplist.append(a)
                i += 1
        j = 0
        downlist.reverse()
        uplist.reverse()
        methyl_up = []
        if len(up_dict) >0:
            for k, down, up in zip(klist, downlist, uplist):
                start = split_dict[k]
                if j >= len(start):
                    j = 0
                if k in methyl[0]:
                    for methylation_range in methylation_ranges:
                        if (methyl[1][k] == 'Dam' and len(methylation_range) == 4) or (methyl[1][k] == 'Dcm' and len(methylation_range) == 5):
                            methylation_range = set(methylation_range)
                            pattern_range = set(range(start[j], start[j]+len(methyl[0][k])))
                            if methylation_range & pattern_range != ([]):
                                if num_items_up not in methyl_up:
                                    methyl_up.append(num_items_up)
                self.uplc.InsertStringItem(num_items_up, k)
                self.uplc.SetStringItem(num_items_up, 1, int(down))
                self.uplc.SetStringItem(num_items_up, 2, int(up))
                self.uplc.SetStringItem(num_items_up, 3, str(int(start[j])))
                j+=1
                
        self.nohitlc = wx.ListCtrl(self, -1, size = (100, 300), style = wx.LC_REPORT)
        self.nohitlc.InsertColumn(0, 'Enzyme')
        self.nohitlc.SetColumnWidth(0, 100)
        num_items_nohit = self.nohitlc.GetItemCount()
        for items in sorted(nohitlist, reverse =True):
            self.nohitlc.InsertStringItem(num_items_nohit, str(items))
        self.mutation_button = wx.Button(self, -1, "Mutate out cutting sites")
        self.mutation_button.Bind(wx.EVT_LEFT_DOWN, self.select_sites)
        #Add objects to sizers
        self.bluntsizer.AddMany([(self.bluntlabel, 0, wx.TOP, 10), (self.bluntlc, 0, wx.TOP, 10)])
        self.downsizer.AddMany([(self.downlabel, 0, wx.TOP, 10), (self.downlc, 0, wx.TOP, 10)])
        self.upsizer.AddMany([(self.uplabel, 0, wx.TOP, 10), (self.uplc, 0, wx.TOP, 10)])
        self.nosizer.AddMany([(self.nocutlabel, 0, wx.TOP, 10), (self.nohitlc, 0, wx.TOP, 10)])
        self.lcsizer.AddMany([(self.bluntsizer), (self.downsizer, 0, wx.LEFT, 20), (self.upsizer, 0, wx.LEFT, 20), (self.nosizer, 0, wx.LEFT, 20)])
        self.old_sizer.AddMany([(self.original_seq_label, 0, wx.EXPAND), (self.original_seq, 1, wx.EXPAND)])
        self.new_sizer.AddMany([(self.new_seq_label, 0, wx.EXPAND), (self.new_seq, 1, wx.EXPAND)])
        self.methylase_sizer.AddMany([(self.methylase_text, 0, wx.TOP, -18), (self.methylation_lc)])
        self.highlight_sizer.AddMany([(self.mutation_button, 0, wx.TOP, 10)]) #(self.highlight_text, 0, wx.LEFT|wx.TOP, 10)])
        self.disp_sizer.AddMany([(self.old_sizer, 1, wx.EXPAND), (self.new_sizer, 1, wx.EXPAND|wx.LEFT, 10), (self.methylase_sizer, 0, wx.LEFT|wx.BOTTOM, 20)])
        self.total_sizer.AddMany([(self.lcsizer), (self.highlight_sizer), (self.disp_sizer, 1, wx.EXPAND|wx.TOP, 10)])
        self.SetSizerAndFit(self.total_sizer)
        
    def select_sites(self, event):
        #Get selected sites from lists on cutting panel and then mutate out sites
        elist, slist = [], []
        if self.bluntlc.GetFirstSelected() != -1: #Check to see if any are selected
            elist.append(str(self.bluntlc.GetItemText(self.bluntlc.GetFirstSelected())))
            slist.append(self.bluntlc.GetItem(self.bluntlc.GetNextItem(-1, wx.LIST_NEXT_ALL, wx.LIST_STATE_SELECTED), 2).GetText())
            n =self.bluntlc.GetNextSelected(self.bluntlc.GetFirstSelected())
            while n != -1: #While there are more selected
                elist.append(str(self.bluntlc.GetItemText(n)))
                slist.append(self.bluntlc.GetItem(n, 2).GetText())
                n = self.bluntlc.GetNextSelected(n)
        if self.downlc.GetFirstSelected() != -1: #Check to see if any are selected
            elist.append(str(self.downlc.GetItemText(self.downlc.GetFirstSelected())))
            slist.append(self.downlc.GetItem(self.downlc.GetNextItem(-1, wx.LIST_NEXT_ALL, wx.LIST_STATE_SELECTED), 3).GetText())
            n =self.downlc.GetNextSelected(self.downlc.GetFirstSelected())
            while n != -1: #While there are more selected
                elist.append(str(self.bluntlc.GetItemText(n)))
                slist.append(self.downlc.GetItem(n, 3).GetText())
                n = self.downlc.GetNextSelected(n)
        if self.uplc.GetFirstSelected() != -1: #Check to see if any are selected
            elist.append(str(self.uplc.GetItemText(self.uplc.GetFirstSelected())))
            slist.append(self.uplc.GetItem(self.uplc.GetNextItem(-1, wx.LIST_NEXT_ALL, wx.LIST_STATE_SELECTED), 3).GetText())
            n =self.uplc.GetNextSelected(self.uplc.GetFirstSelected())
            while n != -1: #While there are more selected
                elist.append(str(self.uplc.GetItemText(n)))
                slist.append(self.uplc.GetItem(n, 3).GetText())
        patterns = Search.db_retrieve(self.search)[1] #Get dictionary of patterns
        self.mutate_sites(elist, slist, patterns) #Mutate out sites  
    
    def retrieve_methylation(self, list):
        pattern_dict, methylation_dict = {}, {}
        connection = sqlite3.connect('re.db')
        cursor = connection.cursor()
        cursor.execute('SELECT r_enz_name, pattern, methylation FROM enzymes')
        for row in cursor:
            if row[0] in list and row[2] != "":
                pattern_dict[row[0]] = row[1]
                methylation_dict[row[0]] = row[2]
        return pattern_dict, methylation_dict
        
    def find_pattern(self, sequence, pattern):
        #Build a regular expression based off of the pattern and search the sequence for the target reg. exp. and count number of matches
        dna = 'ACGTU'
        target = ''
        dictionary = {'N':'[ACGTU]','R':'[AG]', 'Y': '[CT]', 'W':'[AT]','S':'[GC]','M':'[AC]', 'K':'[GT]', 'B':'[CGT]', 'D':'[AGT]', 'H':'[ACT]', 'V':'[ACG]'}
        for char in pattern: #Build reg. exp.
            if char in dna:
                target += char
            else:
                target += dictionary[char]   
        count = sum(1 for _ in re.finditer(target, sequence)) #Count number of matches
        return count 
    
    def mutate_sites(self, elist, slist, patterns):
        #Mutate out selected restriction sites
        color_list, segment_list = [], []
        prev_site, insert, orig_count, new_count = 0, 0, 0, 0
        new_seq = ''
        back_table = codon_usage_db.db().codon_tables()[1]
        cdn_dict = self.GetParent().GetPage(0).codon_dict(str(self.GetParent().GetPage(0).seq_disp.GetValue()))[0]
        dlg = wx.TextEntryDialog(self, 'Sequence Name:', 'Sequence Name') #Get name for sequence
        if dlg.ShowModal() == wx.ID_OK:
            seq_name = str(dlg.GetValue())
        dlg.Destroy()
        seq_name = ">" + seq_name #Format sequence name for FASTA file
        for e in elist: #Get original number of restriction sites
            orig_count = orig_count + self.find_pattern(self.seq, patterns[e])
        #Get range for mutation to alter site
        for e, s in zip(xrange(len(elist)), slist):
            change = False
            s = int(s) -1
            length = len(patterns[elist[e]]) #length of enzyme pattern
            range_list = range(int(s), int(s)+length)
            #Get Reading Frame
            if self.rf == 2:
                self.seq = self.seq[1:]
            elif self.rf == 3:
                self.seq = self.seq[2:]
            while range_list != [] and change == False: #Try until all possibilities are exhausted
                insert = int(random.choice(range_list)) #Select random position from list
                range_list.remove(insert) #Remove choice from list so it will not be selected again if it doesn't work
                max = 0
                maxc = ''
                mlist = []
                if insert%3 == 0: #Check where insert is in sequence to determine position for reading frame
                    #If insert is near end of sequence and the base will not be translated move the insert back to the last translated codon
                    if insert+1 == len(self.seq) and insert != 0:
                        insert = insert - 3
                    elif insert+2 == len(self.seq) and insert != 0:
                        insert = insert -3
                    region = self.seq[insert:insert+3] #Get codon
                    translation = Seq.translate(Seq(region, generic_dna)) #Translate the codon
                    if str(translation) != '':
                        mutation_list = back_table[str(translation)] #Get list of codons that also code for same amino acid
                        if region in mutation_list:
                            mutation_list.remove(region) #Remove original codon from list
                        for mutation in mutation_list: #Try each mutant codon
                            new_count = 0
                            test_seq = self.seq[:insert] + mutation + self.seq[insert+3:]
                            for e in elist: #Count new number of restriction sites
                                new_count = new_count + self.find_pattern(test_seq, patterns[e])
                            if new_count < orig_count: #If the new count is less than the original count add mutation to list
                                mlist.append(mutation)
                        #From list of approved mutations use the one which appears most frequently in the selected host organism
                        if mlist != []:
                            change = True
                            color_list.append(insert)
                            for codon in mlist:
                                if codon in cdn_dict:
                                    if cdn_dict[codon] > max:
                                        max = cdn_dict[codon]
                                        maxc = codon
                            if maxc == '':
                                max = 0
                                for k, v in self.GetParent().GetPage(0).codon_usage_retrieve(mutation_list, str(self.GetParent().GetParent().GetParent().get_organism())).iteritems():
                                    if v > max:
                                        max = v
                                        maxc = k
                            segment = self.seq[prev_site:insert] + maxc + self.seq[insert+3:s+length]
                            segment_list.append(segment)
                #Same procedure but insert occurs in middle of codon
                elif insert%3 == 1:
                    if insert+1 == len(self.seq) and insert != 1:
                        insert = insert - 3
                    region = self.seq[insert-1:insert+2]
                    translation = Seq.translate(Seq(region, generic_dna))
                    if str(translation) != '':
                        mutation_list = back_table[str(translation)]
                        if region in mutation_list:
                            mutation_list.remove(region)
                        for mutation in mutation_list:
                            new_count = 0
                            test_seq = self.seq[:insert-1] + mutation + self.seq[insert+2:]
                            for e in elist:
                                new_count = new_count + self.find_pattern(test_seq, patterns[e])
                            if new_count != orig_count:
                                mlist.append(mutation)
                        if mlist != []:
                            change = True
                            color_list.append(insert-1)
                            for codon in mlist:
                                if codon in cdn_dict:
                                    if cdn_dict[codon] > max:
                                        max = cdn_dict[codon]
                                        maxc = codon
                            if maxc == '':
                                max = 0
                                for k, v in self.GetParent().GetPage(0).codon_usage_retrieve(mutation_list, str(self.GetParent().GetParent().GetParent().get_organism())).iteritems():
                                    if v > max:
                                        max = v
                                        maxc = k
                            segment = self.seq[prev_site:insert-1] + maxc + self.seq[insert+2:s+length]
                            segment_list.append(segment)
                #Same procedure with insert occurring at end of a codon
                elif insert%3 == 2:
                    region = self.seq[insert-2:insert+1]
                    translation = Seq.translate(Seq(region, generic_dna))
                    if str(translation) != '':
                        mutation_list = back_table[str(translation)]
                        if region in mutation_list:
                            mutation_list.remove(region)
                        for mutation in mutation_list:
                            new_count = 0
                            test_seq = self.seq[:insert-2] + mutation + self.seq[insert+1:]
                            for e in elist:
                                new_count = new_count + self.find_pattern(test_seq, patterns[e])
                            if new_count != orig_count:
                                mlist.append(mutation)
                        if mlist != []:
                            change = True
                            color_list.append(insert-2)
                            for codon in mlist:
                                if codon in cdn_dict:
                                    if cdn_dict[codon] > max:
                                        max = cdn_dict[codon]
                                        maxc = codon
                            if maxc == '':
                                max = 0
                                for k, v in self.GetParent().GetPage(0).codon_usage_retrieve(mutation_list, str(self.GetParent().GetParent().GetParent().get_organism())).iteritems():
                                    if v > max:
                                        max = v
                                        maxc = k
                            segment = self.seq[prev_site:insert-2] + maxc + self.seq[insert+1:s+length]
                            segment_list.append(segment)
            prev_site = int(s)+length
            #If impossible to get rid of restriction site through silent mutations without creating new sites give warning message
            if range_list == []:
                dlg = wx.MessageDialog(self, 'Impossible to silently mutate out restriction site without inserting new sites', 'Warning!', wx.ICON_EXCLAMATION|wx.OK)
        for segment in segment_list:
            new_seq += segment
        new_seq += self.seq[prev_site:]
        if new_seq == '':
            new_seq = self.seq
        new_seq = seq_name +'\n'+ new_seq
        #Set Display Values
        self.original_seq.SetValue(str(self.seq))
        self.new_seq.SetValue(str(new_seq))
        self.Refresh()
        #Write new sequence to FASTA file
        if not os.path.exists('%s.fasta' %seq_name.strip('>')):
                file = open('%s.fasta' %seq_name.strip('>'), 'w')
                file.write(str(new_seq))
                file.close()
        #Highlight mutation in new sequence
        for item in color_list:
            self.new_seq.SetStyle(len(seq_name) +1 +item, len(seq_name) +1 + item+3, wx.TextAttr('red', 'white'))
        return new_seq, seq_name
    
class Grid(grd.Grid):
    #Grid which displays graphically where restriction enzymes cut the sequence
    def __init__(self, parent, seq, blunt_dict, down_dict, up_dict, size):
        grd.Grid.__init__(self, parent, -1, wx.DefaultPosition, wx.Size(size[0], size[1]))
        self.seq = str(seq)
        self.complement = Seq(seq).complement()
        attr = grd.GridCellAttr()
        attr.SetReadOnly(1) #Do not allow editing of gird
        self.CreateGrid(len(blunt_dict)+ len(down_dict) + len(up_dict)+3,len(seq)*2)
        self.EnableGridLines(0) #Turn off gridlines
        self.EnableDragGridSize(0) #Do not allow resizing of columns or rows
        self.RowLabelSize = 0
        self.ColLabelSize = 0
        for x in range(len(seq)*2): #Set grid to be twice as wide as length of sequence
            self.SetColAttr(x,attr)
            if x == 1:
                self.SetRowMinimalAcceptableHeight(5)
                self.SetRowSize(x, 20)
            if x%2 == 0: #Columns for letters in sequence
                self.SetColMinimalAcceptableWidth(5)
                self.SetColSize(x,12)
                self.SetCellOverflow(0,x,1)
            else: #Columns to display where cuts occur in between letters
                self.SetColMinimalAcceptableWidth(5)
                self.SetColSize(x,8)
        i = 0
        for char, comp_char in zip(self.seq, self.complement): #Put sequence into grid
            self.SetCellValue(0, i*2, char)
            self.SetCellValue(2, i*2, comp_char)
            i +=1
        j = 3
        blunt_list = []
        for key in blunt_dict.iterkeys():
            blunt_list.append(key)
        blunt_cuts = Search().db_cutting_info(blunt_list)[1]
        pattern_dict = Search().db_retrieve()[1]
        for key, site_list in blunt_dict.iteritems(): #Go through blunt cutters
            for value in site_list:
                if blunt_cuts[key] == -1:
                    comp = len(pattern_dict[key])
                    comp = value - comp
                else:
                    comp = blunt_cuts[key]
                    length = len(pattern_dict[key]) -1
                    comp = value + length - comp
                if comp == 0:
                    letter = self.GetCellValue(2,0)
                    self.SetCellValue(2, 0, '|%s' %letter)
                self.SetCellValue(0, value*2-1, '|')
                self.SetCellValue(1, value*2-1, '|')
                if (comp < value):
                    for spot in range(comp*2, value*2-1):
                        if spot == 0:
                            self.SetCellValue(1, spot, '|-')
                        else:
                            self.SetCellValue(1, spot, '-')
                else:
                    for spot in range(value*2, comp*2-1):
                        if spot == 0:
                            self.SetCellValue(1, spot, '|-')
                        else:
                            self.SetCellValue(1, spot, '-')
                if comp != 0:
                    self.SetCellValue(2, comp*2-1, '|')
                if comp*2 == len(seq)*2:
                    self.SetCellValue(j, comp*2-1, '|%s' %key)
                else:
                    if comp > 0:
                        self.SetCellValue(j, comp*2-1, '|')
                        self.SetCellValue(1, comp*2-1, '|')
                    self.SetCellValue(j,comp*2, key)
                    self.SetCellOverflow(2,comp*2+1,1) #Allow cell overflow
            j +=1
        for key, site_list in down_dict.iteritems(): #Go through downstream cutters
            for value in site_list:
                if value[0]*2 < len(seq)*2:
                    for num in range(j+1):
                        if num != 1:
                            if self.GetCellValue(num, value[0]*2-2) == '':
                                if value[1] >=2:
                                    if self.GetCellValue(num, value[0]*2-4) == ''  and self.GetCellValue(num , value[0]*2-1) == '':
                                        self.SetCellValue(num, value[0]*2-1, '|')
                                else:
                                    if self.GetCellValue(num , value[0]*2-1) == '':
                                        self.SetCellValue(num, value[0]*2-1, '|')
                    self.SetCellValue(0, value[0]*2-1, '|')
                    self.SetCellValue(1, value[0]*2-1, '|')
                    for spot in (set(range(value[0]*2))-set(range(value[0]*2))):
                        self.SetCellValue(1, spot, '-')
                    self.SetCellValue(1, value[0]*2-1, '|')
                    self.SetCellValue(2, value[0]*2-1, '|')
                    self.SetCellValue(j, value[0]*2, key)
                    self.SetCellOverflow(2,value[0]*2+1,1)
            j += 1
        for key, site_list in up_dict.iteritems(): #Go through upstream cutters
            for value in site_list:
                if value[0]*2 < len(seq)*2:
                    for num in range(j+1):
                        if self.GetCellValue(num, value[0]*2-2) == '':
                            if value[0] >=2:
                                if self.GetCellValue(num, value[0]*2-4) == ''  and self.GetCellValue(num , value[0]*2-1) == '':
                                    self.SetCellValue(num, value[0]*2-1, '|')
                            else:
                                if self.GetCellValue(num , value[0]*2-1) == '':
                                    self.SetCellValue(num, value[0]*2-1, '|')
                    self.SetCellValue(0, value[0]*2-1, '|')
                    self.SetCellValue(2, value[0]*2-1, '|')
                    self.SetCellValue(j,value[0]*2, key)
                    self.SetCellOverflow(2,value[0]*2+1,1)
            j += 1
        self.SetColSize(len(seq)*2-1,100)
        
class CutDrawingPanel(wx.Panel):
    #Panel which displays a grid detailing graphically where selected restriction enzymes cut the sequence
    def __init__(self, parent, id, search, blunt_dict, down_dict, up_dict, seq, size):
        wx.Panel.__init__(self, parent)
        self.sizer = wx.BoxSizer()
        self.name = 'Cut Draw'
        grid = Grid(self, seq, blunt_dict, down_dict, up_dict, size)
        grid.SetFocus()
        self.sizer.Add(grid, 1, wx.EXPAND)
        self.SetSizerAndFit(self.sizer)
        
class ReadingFramePanel(wx.Panel):
    #Panel which lets user select reading frame and displays various reading frames
    def __init__(self, parent, id, sequence):
        wx.Panel.__init__(self, parent)
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.sequence = sequence
        self.seq_label = wx.StaticText(self, wx.ID_ANY, 'Sequence:')
        self.seq = wx.StaticText(self, wx.ID_ANY, '%s...' %sequence)
        self.rf = self.GetParent().GetPage(0).rf
        n = len(self.sequence)
        if n > 300:
            n = 300
        #Display Reading Frames
        self.frame1 = wx.RadioButton(self, 1, 'Frame 1 (%s...): %s...' %(sequence[0:3],Seq.translate(Seq(sequence[:n]))))
        self.frame2 = wx.RadioButton(self, 2, 'Frame 2 (-%s...): %s...' %(sequence[1:4], Seq.translate(Seq(sequence[1:n]))))
        self.frame3 = wx.RadioButton(self, 3, 'Frame 3 (--%s...): %s...' %(sequence[2:5], Seq.translate(Seq(sequence[2:n]))))
        self.framesizer = wx.BoxSizer(wx.VERTICAL)
        if self.rf == 1:
            self.frame1.SetValue(True)
        elif self.rf == 2:
            self.frame2.SetValue(True)
        elif self.rf == 3:
            self.frame3.SetValue(True)
        self.ok_button = wx.Button(self, -1, 'OK')
        self.ok_button.Bind(wx.EVT_LEFT_DOWN, self.ok)
        self.sizer.AddMany([(self.seq_label, 0, wx.EXPAND|wx.TOP|wx.LEFT, 10), (self.seq, 0, wx.EXPAND|wx.TOP|wx.LEFT, 10), (self.frame1, 0, wx.EXPAND|wx.TOP|wx.LEFT, 10), (self.frame2, 0, wx.EXPAND|wx.TOP|wx.LEFT, 10), (self.frame3, 0, wx.EXPAND|wx.TOP|wx.LEFT, 10), (self.ok_button, 0, wx.TOP|wx.LEFT, 10)])
        self.SetSizer(self.sizer)
        
    def get_reading_frame(self):
        #Get the selected reading frame
        if self.frame1.GetValue():
            self.rf = 1
        elif self.frame2.GetValue():
            self.GetParent().GetPage(0).aa_disp.SetValue(str(Seq.translate(Seq(self.sequence[1:]))))
            self.rf = 2
        elif self.frame3.GetValue():
            self.GetParent().GetPage(0).aa_disp.SetValue(str(Seq.translate(Seq(self.sequence[2:]))))
            self.rf = 3
        return self.rf
    
    def ok(self, event):
        #Get the reading frame and close the current page upon pressing 'ok' button
        self.GetParent().SetSelection(0)
        self.GetParent().GetPage(0).rf = self.get_reading_frame()
        self.GetParent().DeletePage(self.GetParent().GetPageCount()-1)
        
class CommercialRefFrame(wx.Frame):
    #Frame with two tables: one displays companies and their REBASE abbreviations.  The other displays which companies sell which enzymes
    def __init__(self, parent, id, title = 'Commercial Availability Reference'):
        wx.Frame.__init__(self, parent, -1, title, wx.DefaultPosition)
        self.source_dict = {}
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.companies = {'B': 'Invitrogen Corporation', 'C': 'Minotech Biotechnology', 'E': 'Stratagene', 'F': 'Fermentas International Inc.', 'H': 'American Allied Biochemical, Inc.', 'I': 'SibEnzyme Ltd.',
                          'J': 'Nippon Gene Co., Ltd.', 'K': 'Takara Bio Inc.', 'M': 'Roche Applied Science', 'N': 'New England Biolabs', 'O': 'Toyobo Biochemicals', 'Q': 'Molecular Biology Resources - CHIMERx',
                          'R': 'Promega Corporation', 'S': 'Sigma Chemical Corporation', 'U': 'Bangalore Genei', 'V': 'Vivantis Technologies', 'X': 'EURx Ltd.', 'Y': 'CinnaGen Inc.'}
        self.company_list = sorted(self.companies.keys(), reverse=True)
        self.company_lc = wx.ListCtrl(self, -1, size = (360,360), style = wx.LC_REPORT)
        self.company_lc.InsertColumn(0, 'Company Key')
        self.company_lc.InsertColumn(1, 'Company Name')
        self.company_lc.SetColumnWidth(0, 100)
        self.company_lc.SetColumnWidth(1, 260)
        num_items = self.company_lc.GetItemCount()
        for key in self.company_list:
            self.company_lc.InsertStringItem(num_items, key)
            self.company_lc.SetStringItem(num_items, 1, self.companies[key])
        connection = sqlite3.connect('re.db')
        cursor = connection.cursor()
        cursor.execute('SELECT r_enz_name, commercial FROM enzymes')
        self.lc = wx.ListCtrl(self, -1, size = (360, 280), style = wx.LC_REPORT)
        self.lc.InsertColumn(0, 'Enzyme')
        self.lc.InsertColumn(1, 'Source(s)')
        self.lc.SetColumnWidth(0, 100)
        self.lc.SetColumnWidth(1, 140)
        for row in cursor:
            self.source_dict[row[0]] = row[1]
        num_items = self.lc.GetItemCount()
        enz_list = sorted(self.source_dict.keys(), reverse=True)
        for enz in enz_list:
            self.lc.InsertStringItem(num_items, enz)
            self.lc.SetStringItem(num_items, 1, str(self.source_dict[enz]))
        self.sizer.AddMany([(self.company_lc, 0, wx.LEFT, 5), (self.lc, 0, wx.LEFT, 5)])
        self.SetSizer(self.sizer)
        self.sizer.Fit(self)
        
class EnzRefFrame(wx.Frame):
    #Frame that displays enzyme and associated target pattern for user reference
    def __init__(self, parent, id, enz_dict, title = 'Enzyme Reference'):
        wx.Frame.__init__(self, parent, -1, title, wx.DefaultPosition, wx.Size(350,350))
        self.lc = wx.ListCtrl(self, -1, style=wx.LC_REPORT)
        self.lc.InsertColumn(0, 'Enzyme')
        self.lc.InsertColumn(1, 'Target')
        self.lc.SetColumnWidth(0, 140)
        self.lc.SetColumnWidth(1, 140)
        num_items = self.lc.GetItemCount()
        enz_list = sorted(enz_dict.keys(), reverse=True)
        for enz in enz_list:
            self.lc.InsertStringItem(num_items, enz)
            self.lc.SetStringItem(num_items,1, enz_dict[enz])
               
class CodonRefFrame(wx.Frame):
    #Frame that displays codons and translations for user reference purposes
    def __init__(self, parent, id, codon_list, title = 'Codon Reference'):
        wx.Frame.__init__(self, parent, -1, title, wx.DefaultPosition, wx.Size(300,300))
        self.lc = wx.ListCtrl(self, -1, style = wx.LC_REPORT)
        self.lc.InsertColumn(0, 'Codon')
        self.lc.InsertColumn(1, 'Amino Acid')
        self.lc.SetColumnWidth(0,140)
        self.lc.SetColumnWidth(1,140)
        num_items = self.lc.GetItemCount()
        for codon in sorted(codon_list, reverse=True):
            self.lc.InsertStringItem(num_items, codon)
            self.lc.SetStringItem(num_items, 1, str(Seq.translate(Seq(codon, generic_dna))))
            
class AAFreqFrame(wx.Frame):
    #Frame that displays amino acid appearance frequency in alphabetical order
    def __init__(self, parent, id, aa_dict, total_aa, title = 'Amino Acid Frequency'):
        wx.Frame.__init__(self, parent, -1, title, (1000,200), wx.Size(300,300))
        self.lc = wx.ListCtrl(self, -1, style = wx.LC_REPORT)
        self.lc.InsertColumn(0, 'Amino Acid')
        self.lc.InsertColumn(1, 'Frequency')
        self.lc.InsertColumn(2, 'Percentage')
        self.lc.SetColumnWidth(0,100)
        self.lc.SetColumnWidth(1,100)
        self.lc.SetColumnWidth(2, 100)
        num_items = self.lc.GetItemCount()
        aa_dict = sorted([(value,key) for (key,value) in aa_dict.items()])
        for item in aa_dict:
            self.lc.InsertStringItem(num_items, item[1])
            self.lc.SetStringItem(num_items, 1, str(item[0]))
            self.lc.SetStringItem(num_items, 2, str(item[0]*100/total_aa)) 
             
class CdnFreqFrame(wx.Frame):
    #Frame that displays codon appearance frequency. Codons sorted in alphabetical order
    def __init__(self, parent, id, codon_dict, total_codons, title = 'Codon Frequency'):
        wx.Frame.__init__(self, parent, -1, title, (1000,200), wx.Size(400,400))
        self.lc = wx.ListCtrl(self, -1, style = wx.LC_REPORT)
        self.lc.InsertColumn(0, 'Codon')
        self.lc.InsertColumn(1, 'Amino Acid')
        self.lc.InsertColumn(2, 'Frequency')
        self.lc.InsertColumn(3, 'Percentage')
        self.lc.SetColumnWidth(0,100)
        self.lc.SetColumnWidth(1,100)
        self.lc.SetColumnWidth(2, 100)
        self.lc.SetColumnWidth(3, 100)
        num_items = self.lc.GetItemCount()
        codon_dict = sorted([(value,key) for (key,value) in codon_dict.items()])
        for item in codon_dict:
            self.lc.InsertStringItem(num_items, item[1])
            self.lc.SetStringItem(num_items, 1, str(Seq.translate(Seq(item[1]))))
            self.lc.SetStringItem(num_items, 2, str(item[0]))
            self.lc.SetStringItem(num_items, 3, str(item[0]*100/total_codons))
        '''with open('output.txt', 'w') as f:
            f.write('Total Codons: ' + str(total_codons) + '\n')
            for item in codon_dict:
                f.write(item[1] +'\t'+ str(Seq.translate(Seq(item[1]))) +'\t' + str(item[0]) + '\n')'''
            
class OpenReadingFramePanel(wx.Panel):
    #Panel with a textbox to display open reading frames
    def __init__(self, parent, id, starts, ends, frames):
        wx.Panel.__init__(self, parent)
        self.display = wx.TextCtrl(self, style = wx.TE_MULTILINE) #Create textbox
        self.close_button = wx.Button(self, -1, 'Close Panel')
        self.close_button.Bind(wx.EVT_LEFT_DOWN, self.close_panel)
        self.add_button = wx.Button(self, -1, 'Add Reading Frame Codon Frequency to DB')
        self.add_button.Bind(wx.EVT_LEFT_DOWN, self.add_org)
        self.button_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.text = ''
        number = 1
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.orf = True
        for start, end, frame in zip(starts, ends, frames): #Add frames and labels to text for addition to text box
            self.text = self.text + 'Frame: %d ' %number +'\nStart: %s End: %s' %(start, end) +'\n' +frame + '\n' +'\n'
            number += 1
        self.display.SetValue(self.text) 
        self.button_sizer.AddMany([(self.close_button, 0, wx.LEFT|wx.TOP|wx.BOTTOM, 10), (self.add_button, 0, wx.LEFT|wx.TOP|wx.BOTTOM,10)])
        self.sizer.AddMany([(self.display, 1, wx.EXPAND), (self.button_sizer)])
        self.SetSizerAndFit(self.sizer)
        
    def close_panel(self, event):
        self.GetParent().DeletePage(self.GetParent().GetSelection())
        
    def add_org(self, event):
        self.nucleotides = self.text.split('\n')[2]
        self.GetParent().GetParent().GetParent().add_organism(event)

class MainFrame(wx.Frame):
    def __init__(self, parent, id, title, searchInstance, enzyme_list, target_list, vector_list):
        wx.Frame.__init__(self, parent, -1, title)
        self.searchInstance, self.enzyme_list, self.vector_list, self.target_list = searchInstance, enzyme_list, vector_list, target_list
        self.panel = wx.Panel(self)
        self.seq_undoredo, self.vector_undoredo, self.aaseq_undoredo = 0, 0, 0
        self.seq_undo, self.vector_undo, self.aaseq_undo, self.optimization_undo = False, False, False, False
        self.nb = wx.Notebook(self.panel, style = wx.NB_BOTTOM) #Initialize the notebook
        #Create initial pages for notebook
        self.mutation_page = MutationPanel(self.nb, -1, searchInstance, enzyme_list, vector_list, target_list, self.nb, self)
        self.optimization_page = OptimizationPanel(self.nb, -1, self.nb, self)
        #Add pages to notebook
        self.nb.AddPage(self.mutation_page, 'Mutations')
        self.nb.AddPage(self.optimization_page, 'Optimization')
        cursor = sqlite3.connect('codon_usage.db').cursor() # Connect to the dabase
        cursor.execute('''SELECT name FROM sqlite_master WHERE type='table' ORDER BY name''')
        #Create menu for Main Frame
        self.db = wx.Menu()
        self.organisms = wx.Menu() #Create databases submenu
        self.organisms.Append(ID_ADDORG, 'Add Organism')
        self.organisms.Append(ID_DELETEORG, 'Delete Organism')
        self.organisms.AppendSeparator()
        for row in cursor:
            row = str(row).split("\'")
            self.organisms.AppendRadioItem(ID_CURRENT, 'Current sequence')
            self.organisms.AppendRadioItem(ID_ECOLIK12, row[1])
        self.vectors = wx.Menu()
        self.vectors.Append(ID_ADDVECTOR, 'Add Vector')
        self.vectors.Append(ID_DELETEVECTOR, 'Delete Vector')
        self.enzymes = wx.Menu()
        self.enzymes.Append(ID_ADDENZYME, 'Add Restriction Enzyme')
        self.enzymes.Append(ID_DELETEENZYME, 'Delete Restriction Enzyme')
        self.templates = wx.Menu()
        self.templates.Append(ID_TEMPLATES, 'Template Sequence Database')
        self.templates.Append(ID_NEWTEMPLATES, 'Add New Template Sequences')
        self.db.AppendMenu(-1, 'Restriction Enzymes', self.enzymes)
        self.db.AppendMenu(-1, 'Vectors', self.vectors)
        self.db.AppendMenu(-1, 'Codon Usage', self.organisms)
        self.db.AppendMenu(-1, 'Templates', self.templates)
        self.filemenu = wx.Menu() #Create file submenu
        self.filemenu.Append(ID_UNDO, 'Undo')
        self.filemenu.Append(ID_REDO, 'Redo')
        self.filemenu.Enable(ID_REDO, False)
        self.filemenu.AppendSeparator()
        self.filemenu.Append(ID_ABOUT, 'About')
        self.filemenu.AppendSeparator()
        self.filemenu.Append(ID_EXIT, 'Exit')
        self.menu = wx.Menu() #Create Reference submenu
        self.menu.Append(ID_ENZYMEREF, "Enzyme Reference", 'Look up patterns for restriction enzymes')
        self.menu.Append(ID_CODONREF, 'Codon Table Reference', 'Look up codons and amino acids')
        self.menu.Append(ID_COMMERCIALREF, 'Commercial Availability Reference', 'Look up commmercial avaiability of restriction enzymes')
        self.menubar = wx.MenuBar() #Create menubar
        self.SetMenuBar(self.menubar)
        self.menubar.Append(self.filemenu, 'File')
        self.menubar.Append(self.menu, 'Reference')
        self.menubar.Append(self.db, 'Databases')
        self.tools = wx.Menu() #Create tools submenu
        self.tools.Append(ID_TOX, 'Check Sequence/Host Toxicity','Look for codons in sequence that are infrequent in host organism in which you would like to insert sequence')
        self.tools.Append(ID_ORF, 'Find Open Reading Frames')
        self.tools.Append(ID_HOMOLOGY,'Homology Modeling')
        self.menubar.Append(self.tools, 'Tools')
        self.help = wx.Menu()
        self.help.Append(ID_HELP, 'Help Panel', 'Launches a help panel')
        self.menubar.Append(self.help, 'Guide')
        #Add menu events
        wx.EVT_MENU(self, ID_ENZYMEREF, self.enzyme_reference)
        wx.EVT_MENU(self, ID_CODONREF, self.codon_reference)
        wx.EVT_MENU(self, ID_COMMERCIALREF, self.commercial_reference)
        wx.EVT_MENU(self, ID_TOX, self.toxicity)
        wx.EVT_MENU(self, ID_ORF, self.open_reading_frame)
        wx.EVT_MENU(self, ID_UNDO, self.undo)
        wx.EVT_MENU(self, ID_REDO, self.redo)
        wx.EVT_MENU(self, ID_ABOUT, self.on_about)
        wx.EVT_MENU(self, ID_EXIT, self.on_exit)
        wx.EVT_MENU(self, ID_ADDENZYME, self.add_enzyme)
        wx.EVT_MENU(self, ID_ADDORG, self.add_organism)
        wx.EVT_MENU(self, ID_DELETEORG, lambda evt: codon_usage_db.AddOrgPanel.delete_organism(codon_usage_db.AddOrgPanel(self.nb, -1), evt))
        wx.EVT_MENU(self, ID_ADDVECTOR, self.add_vector)
        wx.EVT_MENU(self, ID_DELETEVECTOR, lambda evt: vectors_db.VectorPanel.delete_vector(vectors_db.VectorPanel(self.nb, -1), evt))
        wx.EVT_MENU(self, ID_DELETEENZYME, lambda evt: build_re_db.AddEnzymePanel.delete_enzyme(build_re_db.AddEnzymePanel(self.nb, -1, 'Add Enzyme'), evt))
        wx.EVT_MENU(self, ID_HELP, self.launch_help)
        wx.EVT_MENU(self, ID_HOMOLOGY, self.model)
        wx.EVT_MENU(self, ID_TEMPLATES, self.template)
        wx.EVT_MENU(self, ID_NEWTEMPLATES, self.new_template)
        #Add Shortcut keys
        accel_tbl = wx.AcceleratorTable([(wx.ACCEL_CMD, ord('Z'), ID_UNDO), (wx.ACCEL_CMD, ord('Y'), ID_REDO), (wx.ACCEL_CMD, ord('T'), ID_TOX)])
        self.SetAcceleratorTable(accel_tbl)
        #Create and use sizers for main frame
        sizer = wx.BoxSizer()
        sizer.Add(self.nb, 1, wx.EXPAND)
        self.panel.SetSizer(sizer)
        sizer.Fit(self)
        self.SetClientSize(self.panel.GetSize()) #Set frame size
        #Prevent resizing
        self.SetMinSize(self.GetSize())
        self.SetMaxSize(self.GetSize())
        self.Centre() #Center frame
        
    def model(self, event):
        filters = 'FASTA files (*.fasta;*.fa;*.fna;*.seq;*.txt)|*.fasta;*.fa;*.fna;*.seq;*.txt'
        dialog = wx.FileDialog ( None, style = wx.OPEN, wildcard = filters)
        if dialog.ShowModal() == wx.ID_OK:
            fasta = dialog.GetPath()
            path = fasta.split('/')
            folder = ''
            for item in path:
                if item != path[-1]:
                    folder += '/' + item
            folder += '/'
        homology.model(fasta, folder)

    def launch_help(self, event):
        self.dlg = help.HelpWindow(self, -1)
        self.dlg.Show(True)
        
    def on_focus(self, event):
        self.mutation_panel = self.nb.GetPage(0)
        if self.nb.GetSelection() == 0:
            focus = self.mutation_panel.FindFocus().name
            if focus == 'SeqDisp':
                self.filemenu.Enable(ID_REDO, False)
                if self.seq_undo == True:
                    self.filemenu.Enable(ID_REDO, True)
            elif focus == 'VectorDisp':
                self.filemenu.Enable(ID_REDO, False)
                if self.vector_undo == True:
                    self.filemenu.Enable(ID_REDO, True)
            elif focus == 'AADisp':
                self.filemenu.Enable(ID_REDO, False)
                if self.aaseq_undo == True:
                    self.filemenu.Enable(ID_REDO, True)
        elif self.nb.GetSelection() == 1:
            self.filemenu.Enable(ID_REDO, False)
            if self.optimization_undo == True:
                self.filemenu.Enable(ID_REDO, True)
       
    def undo(self, event):
        self.mutation_panel = self.nb.GetPage(0)
        self.optimization_panel = self.nb.GetPage(1)
        if self.nb.GetSelection() == 0:
            focus = self.mutation_panel.FindFocus().name #Get textbox that is in focus
            if focus == 'SeqDisp':
                #Undo method for sequence display
                self.seq_undo = True #Show that undo has been called
                self.filemenu.Enable(ID_REDO, True)
                self.previous_seq = self.mutation_panel.previous_seq
                length = len(self.previous_seq)
                if self.seq_undoredo < length-1:
                    self.mutation_panel.seq_disp.SetValue(self.previous_seq[self.seq_undoredo+1])
                    self.seq_undoredo += 1
                    if self.seq_undoredo != length-1:
                        self.previous_seq.pop(0)
                    self.previous_seq = self.previous_seq
            elif focus == 'VectorDisp':
                #Undo method for vector display
                self.vector_undo = True #Show that undo has been called
                self.previous_vector = self.mutation_panel.previous_vector
                length = len(self.previous_vector)
                if self.vector_undoredo < length-1:
                    self.mutation_panel.vector_disp.SetValue(self.previous_vector[self.vector_undoredo+1])
                    self.vector_undoredo += 1
                    if self.vector_undoredo != length-1:
                        self.previous_vector.pop(0)
                    self.previous_vector = self.previous_vector
            elif focus == 'AADisp':
                #Undo method for AA Display
                self.aaseq_undo = True #Show that undo has been called
                self.previous_aaseq = self.mutation_panel.previous_aaseq
                length = len(self.previous_aaseq)
                if self.aaseq_undoredo < length-1:
                    self.mutation_panel.aa_disp.SetValue(self.previous_aaseq[self.aaseq_undoredo+1])
                    self.aaseq_undoredo += 1
                    if self.aaseq_undoredo != length-1:
                        self.previous_aaseq.pop(0)
                    self.previous_aaseq = self.previous_aaseq
        elif self.nb.GetSelection() == 1:
            self.optimization_undo = True #Show that undo has been called
            self.filemenu.Enable(ID_REDO, True)
            self.previous_seq = self.optimization_panel.previous_seq
            length = len(self.previous_seq)
            if self.seq_undoredo < length-1:
                self.optimization_panel.seq_disp.SetValue(self.previous_seq[self.seq_undoredo+1])
                self.seq_undoredo += 1
                if self.seq_undoredo != length-1:
                    self.previous_seq.pop(0)
                self.previous_seq = self.previous_seq
                
    def redo(self, event):
        self.mutation_panel = self.nb.GetPage(0)
        self.optimization_panel = self.nb.GetPage(1)
        if self.nb.GetSelection() == 0:
            focus = self.mutation_panel.FindFocus().name #Get textbox that is in focus
            if focus == 'SeqDisp':
                if self.seq_undo: #Check to see if undo has been called first
                    if self.seq_undoredo != 0:
                        self.mutation_panel.seq_disp.SetValue(self.previous_seq[self.seq_undoredo-1])
                        self.seq_undoredo -= 1
                        self.previous_seq.pop(0)
                        self.previous_seq = self.previous_seq
            elif focus == 'VectorDisp':
                if self.vector_undo: #Check to see if undo has been called first
                    if self.vector_undoredo != 0:
                        self.mutation_panel.vector_disp.SetValue(self.previous_vector[self.vector_undoredo-1])
                        self.vector_undoredo -= 1
                        self.previous_vector.pop(0)
                        self.previous_vector = self.previous_vector
            elif focus == 'AADisp':
                if self.aaseq_undo: #Check to see if undo has been called first
                    if self.aaseq_undoredo != 0:
                        self.mutation_panel.aa_disp.SetValue(self.previous_aaseq[self.aaseq_undoredo-1])
                        self.aaseq_undoredo -= 1
                        self.previous_aaseq.pop(0)
                        self.previous_aaseq = self.previous_aaseq
        elif self.nb.GetSelection() == 1:
            if self.optimization_undo: #Check to see if undo has been called first
                    if self.seq_undoredo != 0:
                        self.optimization_panel.seq_disp.SetValue(self.previous_seq[self.seq_undoredo-1])
                        self.seq_undoredo -= 1
                        self.previous_seq.pop(0)
                        self.previous_seq = self.previous_seq
                        
    def commercial_reference(self, event):
        #Display a table of the commercial availability of restriction enzymes
        self.dlg = CommercialRefFrame(self, -1)
        self.dlg.Show(True)
        
    def enzyme_reference(self, event):
        #Display a table of restriction enzymes and their associated target patterns
        self.dlg = EnzRefFrame(self, -1, self.mutation_page.target_list)
        self.dlg.Show(True) 
        
    def codon_reference(self, event):
        #Display a table with codons and their amino acid translations for reference
        ctable = codon_usage_db.db().codon_tables()[0]
        codon_list = []
        #Get list of codons
        for codon in ctable.keys():
            codon_list.append(codon)
        #Create and show frame
        self.dlg = CodonRefFrame(self, -1, codon_list)
        self.dlg.Show(True) 
        
    def toxicity(self, event):
        #Check sequence for codons that appear infrequently (less than 1% of total codons) in host organism.
        seq = str(self.mutation_page.seq_disp.GetValue()) #Get Sequence
        #Get Reading Frame
        if self.mutation_page.rf == 2:
            seq = seq[1:]
        elif self.mutation_page.rf == 3:
            seq = seq[2:]
        seq_codon_list = []
        #Get list of codons
        for base in xrange(len(seq)):
            if base%3 == 0:
                codon = seq[base:base+3]
                if len(codon) == 3:
                    seq_codon_list.append(codon)     
        #Get organisms in menu and get the selected organism
        organism = self.get_organism()
        #Get codon usage for organism
        cdnusage = self.mutation_page.codon_usage_retrieve(seq_codon_list, str(organism))
        toxic_list = []
        # If a codon is found rare in organism add to list.
        for k, v in cdnusage.iteritems():
            if v <10: #The database stores codon percentages as out of 1,000 so <10 is less than 1 % of total codons
                toxic_list.append(k)
        #Show warning dialog if any codons are below the threshold
        dlg = wx.MessageDialog(self, 'The following codons represent less than 1 percent of the total codons in the selected host: %s' %str(toxic_list), 'Toxicity Report', wx.ICON_EXCLAMATION| wx.OK)
        dlg.ShowModal()
        dlg.Destroy()
        
    def open_reading_frame(self, event):
        #Finds open reading frames
        self.nb = self.GetChildren()[0].GetChildren()[0]
        self.seq = self.nb.GetPage(0).seq_disp.GetValue() #Get sequence
        self.rf = self.nb.GetPage(0).rf #Get the reading frame
        rflist, start_list, end_list, frame_list = [], [], [], []
        self.min_AA = 50
        dlg = wx.TextEntryDialog(self, 'Minimum number of amino acids in betweens start and stop codons:', 'Minimum Number of Amino Acids', '50') #Ask user for the number of amino acids between start and stop codons
        if dlg.ShowModal() == wx.ID_OK:
            try:
                self.min_AA = int(dlg.GetValue())
            except ValueError: #If user doesn't enter a number use 50 as default
                self.min_AA = 50
        if self.min_AA < 1: #If user enters value less than 1, use 1
            self.min_AA = 1
        dlg.Destroy()
        self.frame_starts = [match.start() for match in re.finditer(re.escape('ATG'), self.seq)] #Find all possible starts for ORFs
        self.frame_starts1 = [match.start() for match in re.finditer(re.escape('AUG'), self.seq)]
        self.frame_starts = self.frame_starts + self.frame_starts1
        for start in self.frame_starts:
            if start != -1 and start%3 + 1 == self.rf:
                self.frame_endA = filter(lambda x: x >start+self.min_AA*3 and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('TAA'), self.seq)]) #Find all occurrences of TAA that fit the criteria
                self.frame_endA1 = filter(lambda x: x >start+self.min_AA*3 and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('UAA'), self.seq)])
                self.frame_end_a = filter(lambda x: x>start and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('TAA'), self.seq)]) #Find any other occurrences of TAA after start
                self.frame_end_a1 = filter(lambda x: x>start and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('UAA'), self.seq)])
                self.frame_end_a = self.frame_end_a + self.frame_end_a1
                self.frame_endB = filter(lambda x: x >start+self.min_AA*3 and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('TAG'), self.seq)]) #Find all occurrences of TAG that fit criteria
                self.frame_endB1 = filter(lambda x: x >start+self.min_AA*3 and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('UAG'), self.seq)])
                self.frame_end_b = filter(lambda x: x>start and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('TAG'), self.seq)]) #Find any other occurrences of TAG after start
                self.frame_end_b1 = filter(lambda x: x>start and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('UAG'), self.seq)])
                self.frame_end_b = self.frame_end_b + self.frame_end_b1
                self.frame_endC = filter(lambda x: x >start+self.min_AA*3 and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('TGA'), self.seq)]) #Find all occurrences of TGA that fit criteria
                self.frame_endC1 = filter(lambda x: x >start+self.min_AA*3 and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('UGA'), self.seq)])
                self.frame_end_c = filter(lambda x: x>start and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('TGA'), self.seq)]) #Find any other occurrences of TGA after start
                self.frame_end_c1 = filter(lambda x: x>start and x%3+1 == self.rf, [match.start() for match in re.finditer(re.escape('UGA'), self.seq)])
                self.frame_end_c = self.frame_end_c + self.frame_end_c1
                self.frame_endA = self.frame_endA + self.frame_endA1
                self.frame_endB = self.frame_endB + self.frame_endB1
                self.frame_endC = self.frame_endC + self.frame_endC1
                rflist = []
                #Get first value from list if it exists otherwise set equal to length of sequence + 1
                if self.frame_end_a != []:
                    a = self.frame_end_a[0]
                else:
                    a = len(self.seq)+1
                if self.frame_end_b != []:
                    b = self.frame_end_b[0]
                else:
                    b = len(self.seq)+1
                if self.frame_end_c != []:
                    c = self.frame_end_c[0]
                else:
                    c = len(self.seq)+1
                #Ensure that the first occurrence that meets the criteria after start is also the first occurrence of a stop codon
                if self.frame_endA != []:
                    if self.frame_endA[0] <= a and self.frame_endA[0] <= b and self.frame_endA[0] <= c:
                        rflist.append(self.frame_endA[0])
                if self.frame_endB != []:
                    if self.frame_endB[0] <= a and self.frame_endB[0] <= b and self.frame_endB[0] <= c:
                        rflist.append(self.frame_endB[0])
                if self.frame_endC != []:
                    if self.frame_endC[0] <= a and self.frame_endC[0] <= b and self.frame_endC[0] <= c:
                        rflist.append(self.frame_endC[0])
                try:
                    self.frame_end = min(rflist)+2 #Get ending point of ORF
                    start_list.append(start+1)
                    end_list.append(self.frame_end+1)
                    frame_list.append(self.seq[start:self.frame_end+1])
                except ValueError:
                    dlg = wx.MessageDialog(self, 'No uninterrupted reading frames with at least %s amino acids in between the stop and start codons were found.' %self.min_AA, 'No Suitable Open Reading Frame!', wx.OK | wx.ICON_INFORMATION)
                    dlg.ShowModal()
                    dlg.Destroy()
                    self.frame_end = -1
        num = 0
        for page in self.nb.GetChildren():
            if hasattr(page, 'orf'):
                self.nb.DeletePage(num)
            num += 1
        orf_panel = OpenReadingFramePanel(self.nb, -1,start_list, end_list, frame_list)
        self.nb.AddPage(orf_panel, 'Open Reading Frames')
        self.nb.SetSelection(self.nb.GetPageCount()-1)
        
    def on_about(self, event):
        #Display dialog with information about Genes Gene Designer
        dlg = wx.MessageDialog(self,'Gene Designer (Molecular Cloning Assistant)\n V0.1 beta \n\nCreated by Doug Crandell \nUniversity of North Carolina-Chapel Hill','About Gene Designer', wx.OK | wx.ICON_INFORMATION)
        dlg.ShowModal()
        dlg.Destroy()  
         
    def on_exit(self, event):
        #Prompt to confirm exit and then close Gene Designer
        dlg = wx.MessageDialog(self, '','Do you really wish to exit Gene Designer?', wx.YES_NO | wx.ICON_QUESTION)
        if dlg.ShowModal() == wx.ID_YES:
            dlg.Destroy()
            self.Close()
        else:
            dlg.Destroy()
            
    def add_enzyme(self, event):
        #Launch frame for adding enzyme to restriction enzyme database
        self.enzyme_page = build_re_db.AddEnzymePanel(self.nb, -1, 'Add Enzyme')
        self.nb.AddPage(self.enzyme_page, 'Add Enzyme')
        self.nb.SetSelection(self.nb.GetPageCount()-1)
        
    def add_organism(self, event):
        #Launch frame for adding organism to codon usage db
        for page in self.nb.GetChildren():
            if hasattr(page, 'nucleotides'):
                text = page.nucleotides
            else:
                text = ""
        self.organism_page = codon_usage_db.AddOrgPanel(self.nb, -1, text)
        self.nb.AddPage(self.organism_page, 'Add Organism')
        self.nb.SetSelection(self.nb.GetPageCount()-1)
    
    def add_vector(self, event):
        #Launches a panel for the user to add a vector to the vector database
        self.vector_page = vectors_db.VectorPanel(self.nb, -1)
        self.nb.AddPage(self.vector_page, 'Add Vector')
        self.nb.SetSelection(self.nb.GetPageCount()-1)
    
    def get_organism(self):
        #Get selected organism from menu
        for item in self.organisms.GetMenuItems():
            if item.IsChecked():
                organism = item.GetLabel()
        return organism
    
    def template(self, event):
        self.template_page = template_db.TemplatePanel(self.nb, -1)
        self.nb.AddPage(self.template_page, 'Template Sequences')
        self.nb.SetSelection(self.nb.GetPageCount()-1)
        
    def new_template(self, event):
        filters = 'FASTA files (*.fasta;*.fa;*.fna;*.seq;*.txt)|*.fasta;*.fa;*.fna;*.seq;*.txt'
        dialog = wx.FileDialog ( None, style = wx.OPEN, wildcard = filters)
        if dialog.ShowModal() == wx.ID_OK:
            self.fasta = dialog.GetPath()
            sequences = self.read_sequences(self.fasta)
        self.template_page = template_db.NewTemplatePanel(self.nb, -1, sequences[0], sequences[1])
        self.nb.AddPage(self.template_page, 'New Template Sequences')
        self.nb.SetSelection(self.nb.GetPageCount()-1)

    def read_sequences(self, filename):
        prev_line, seq_names, sequences = '', [], []
        with open(filename) as file:
            for line in file:
                if line.startswith('>'):
                    seq_names.append(line.split('\n')[0])
                if prev_line.startswith('>'):
                    sequences.append(line.split('\n')[0])
                prev_line = line
            return seq_names, sequences
        
if __name__ == "__main__":
    filename = os.getcwd() + '/type2.103' #File from REBASE
    if not os.path.exists('re.db'): #Create the restriction enzyme database if it doesn't exist already
        build_re_db.db.read_enzymes_from_file(build_re_db.db(filename), filename)
    if not os.path.exists('codon_usage.db'): #Create the codon usage database if it doesn't exist already
        codon_usage_db.db.create_db(codon_usage_db.db())
    if not os.path.exists('vectors.db'):
        vectors_db.db.create_db(vectors_db.db())
    if not os.path.exists('linkers.db'):
        linkers_db.db.create_db(linkers_db.db())
    if not os.path.exists('templates.db'):
        template_db.db.create_db(template_db.db())
    if len(sys.argv) == 1:
        s = Search() #Create instance of Search Class
        enz = s.db_retrieve() #Get list of enzymes and a dictionary of enzymes and their associated patterns
        app = wx.App(redirect = False) #Create Instance of wxApp
        frame = MainFrame(None, -1, 'Gene Designer', s, enz[0], enz[1], enz[2]).Show() #Create MainFrame for GUI
        app.MainLoop() #Start GUI Loop for app
    else:
        print "Usage: python genedesign.py"
