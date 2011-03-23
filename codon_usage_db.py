'''
Created on Jun 23, 2010
Author: Doug Crandell
University of North Carolina at Chapel Hill
'''
'''
A module that sets up a database for the storage of organism codon bias data
'''

import sqlite3
from Bio.Data import CodonTable
import wx

class db():
    
    def __init__(self):
        self = self
    
    def codon_tables(self):
        #Create dictionary of codons to amino acids and vice versa
        forward_table = CodonTable.unambiguous_dna_by_id[11].forward_table #Get dictionary of codons (key) and translations (value)
        back_table = {}
        #Add three stop codons to dictionary
        forward_table['TAA'] = '*'
        forward_table['TAG'] = '*'
        forward_table['TGA'] = '*'
        #Create a reverse dictionary where amino acids are keys and possible codons are the associated values
        for key, value in forward_table.iteritems():
            try:
                back_table[value].append(key)
            except KeyError:
                back_table[value]=[key]
        return forward_table, back_table
    
    def create_db(self):
        #Create and fill the database
        codons = self.codon_tables()[0] #The forward table
        connection = sqlite3.connect('codon_usage.db') #Connect to codon usage database
        cursor = connection.cursor() #Create cursor for database
        #Populate database with E.coli K-12 data.  This is the default for use in the program
        ecolik12usage = {'TTT': 19.7, 'TTC': 15.0, 'TTA': 15.2, 'TTG': 11.9, 'TCT': 5.7, 'TCC': 5.5, 'TCA': 7.8, 'TCG': 8.0, 'TAT': 16.8, 'TAC': 14.6, 'TAA': 1.8, 'TAG': 0.0, 'TGT': 5.9, 'TGC': 8.0, 'TGA': 1.0, 'TGG': 10.7,
                         'CTT': 11.9, 'CTC': 10.5, 'CTA': 5.3, 'CTG': 46.9, 'CCT': 8.4, 'CCC': 6.4, 'CCA': 6.6, 'CCG': 26.7, 'CAT': 15.8, 'CAC': 13.1, 'CAA': 12.1, 'CAG': 27.7, 'CGT': 21.1, 'CGC': 26.0, 'CGA': 4.3, 'CGG': 4.1,
                         'ATT': 30.5, 'ATC': 18.2, 'ATA': 3.7, 'ATG': 24.8, 'ACT': 8.0, 'ACC': 22.8, 'ACA': 6.4, 'ACG': 11.5, 'AAT': 21.9, 'AAC': 24.4, 'AAA': 33.2, 'AAG': 12.1, 'AGT': 7.2, 'AGC': 16.6, 'AGA': 1.4, 'AGG': 1.6,
                         'GTT': 16.8, 'GTC': 11.7, 'GTA': 11.5, 'GTG': 26.4, 'GCT': 10.7, 'GCC': 31.6, 'GCA': 21.1, 'GCG': 38.5, 'GAT': 37.9, 'GAC': 20.5, 'GAA': 43.7, 'GAG': 18.4, 'GGT': 21.3, 'GGC': 33.4, 'GGA': 9.2, 'GGG': 8.6}
        cursor.execute('''CREATE TABLE IF NOT EXISTS EcoliK12 (id integer primary key)''') #Create table in database for E.coli K-12
        for key in codons.keys():
            cursor.execute("ALTER TABLE EcoliK12 ADD %s INT" %key) #Create column in table for each codon
            sql = 'INSERT INTO EcoliK12 (id, %s)' #Set up sqlite statement
            sql = sql %key #Substitue variable (codon name) into sqlite statement
            cursor.execute(sql + "VALUES(NULL, ?)", [ecolik12usage[key]]) #Add values to table
        connection.commit() #Commit changes to database

class AddOrgPanel(wx.Panel):
    #Frame set up with fields for getting data on organism codon usage
    def __init__(self, parent, id, text):
        wx.Panel.__init__(self, parent)
        self.addorg = 'Add Org'
        self.nb = parent
        self.organism_label = wx.StaticText(self, wx.ID_ANY, 'Organism:')
        self.organism = wx.TextCtrl(self)
        self.seq_entry = wx.TextCtrl(self, size = (600,300), style = wx.TE_PROCESS_ENTER|wx.TE_MULTILINE)
        self.seq_entry.SetValue(text)
        self.seq_entry.Bind(wx.EVT_TEXT, self.remove_invalid_chars)
        self.seq_entry_info = wx.StaticText(self, wx.ID_ANY, 'Enter a sequence in the box below and the organism will be added to the database using computed codon frequencies.\nAlternatively you may enter the codon frequencies yourself as percentages out of 1000')
        self.TTTlabel = wx.StaticText(self, wx.ID_ANY, 'TTT')
        self.TTT = wx.TextCtrl(self)
        self.TTClabel = wx.StaticText(self, wx.ID_ANY, 'TTC')
        self.TTC = wx.TextCtrl(self)
        self.TTAlabel = wx.StaticText(self, wx.ID_ANY, 'TTA')
        self.TTA = wx.TextCtrl(self)
        self.TTGlabel = wx.StaticText(self, wx.ID_ANY, 'TTG')
        self.TTG = wx.TextCtrl(self)
        self.TCTlabel = wx.StaticText(self, wx.ID_ANY, 'TCT')
        self.TCT = wx.TextCtrl(self)
        self.TCClabel = wx.StaticText(self, wx.ID_ANY, 'TCC')
        self.TCC = wx.TextCtrl(self)
        self.TCAlabel = wx.StaticText(self, wx.ID_ANY, 'TCA')
        self.TCA = wx.TextCtrl(self)
        self.TCGlabel = wx.StaticText(self, wx.ID_ANY, 'TCG')
        self.TCG = wx.TextCtrl(self)
        self.TATlabel = wx.StaticText(self, wx.ID_ANY, 'TAT')
        self.TAT = wx.TextCtrl(self)
        self.TAClabel = wx.StaticText(self, wx.ID_ANY, 'TAC')
        self.TAC = wx.TextCtrl(self)
        self.TAAlabel = wx.StaticText(self, wx.ID_ANY, 'TAA')
        self.TAA = wx.TextCtrl(self)
        self.TAGlabel = wx.StaticText(self, wx.ID_ANY, 'TAG')
        self.TAG = wx.TextCtrl(self)
        self.TGTlabel = wx.StaticText(self, wx.ID_ANY, 'TGT')
        self.TGT = wx.TextCtrl(self)
        self.TGClabel = wx.StaticText(self, wx.ID_ANY, 'TGC')
        self.TGC = wx.TextCtrl(self)
        self.TGAlabel = wx.StaticText(self, wx.ID_ANY, 'TGA')
        self.TGA = wx.TextCtrl(self)
        self.TGGlabel = wx.StaticText(self, wx.ID_ANY, 'TGG')
        self.TGG = wx.TextCtrl(self)
        self.CTTlabel = wx.StaticText(self, wx.ID_ANY, 'TTT')
        self.CTT = wx.TextCtrl(self)
        self.CTClabel = wx.StaticText(self, wx.ID_ANY, 'CTC')
        self.CTC = wx.TextCtrl(self)
        self.CTAlabel = wx.StaticText(self, wx.ID_ANY, 'CTA')
        self.CTA = wx.TextCtrl(self)
        self.CTGlabel = wx.StaticText(self, wx.ID_ANY, 'CTG')
        self.CTG = wx.TextCtrl(self)
        self.CCTlabel = wx.StaticText(self, wx.ID_ANY, 'CCT')
        self.CCT = wx.TextCtrl(self)
        self.CCClabel = wx.StaticText(self, wx.ID_ANY, 'CCC')
        self.CCC = wx.TextCtrl(self)
        self.CCAlabel = wx.StaticText(self, wx.ID_ANY, 'CCA')
        self.CCA = wx.TextCtrl(self)
        self.CCGlabel = wx.StaticText(self, wx.ID_ANY, 'CCG')
        self.CCG = wx.TextCtrl(self)
        self.CATlabel = wx.StaticText(self, wx.ID_ANY, 'CAT')
        self.CAT = wx.TextCtrl(self)
        self.CAClabel = wx.StaticText(self, wx.ID_ANY, 'CAC')
        self.CAC = wx.TextCtrl(self)
        self.CAAlabel = wx.StaticText(self, wx.ID_ANY, 'CAA')
        self.CAA = wx.TextCtrl(self)
        self.CAGlabel = wx.StaticText(self, wx.ID_ANY, 'CAG')
        self.CAG = wx.TextCtrl(self)
        self.CGTlabel = wx.StaticText(self, wx.ID_ANY, 'CGT')
        self.CGT = wx.TextCtrl(self)
        self.CGClabel = wx.StaticText(self, wx.ID_ANY, 'CGC')
        self.CGC = wx.TextCtrl(self)
        self.CGAlabel = wx.StaticText(self, wx.ID_ANY, 'CGA')
        self.CGA = wx.TextCtrl(self)
        self.CGGlabel = wx.StaticText(self, wx.ID_ANY, 'CGG')
        self.CGG = wx.TextCtrl(self)
        self.ATTlabel = wx.StaticText(self, wx.ID_ANY, 'ATT')
        self.ATT = wx.TextCtrl(self)
        self.ATClabel = wx.StaticText(self, wx.ID_ANY, 'ATC')
        self.ATC = wx.TextCtrl(self)
        self.ATAlabel = wx.StaticText(self, wx.ID_ANY, 'ATA')
        self.ATA = wx.TextCtrl(self)
        self.ATGlabel = wx.StaticText(self, wx.ID_ANY, 'ATG')
        self.ATG = wx.TextCtrl(self)
        self.ACTlabel = wx.StaticText(self, wx.ID_ANY, 'ACT')
        self.ACT = wx.TextCtrl(self)
        self.ACClabel = wx.StaticText(self, wx.ID_ANY, 'ACC')
        self.ACC = wx.TextCtrl(self)
        self.ACAlabel = wx.StaticText(self, wx.ID_ANY, 'ACA')
        self.ACA = wx.TextCtrl(self)
        self.ACGlabel = wx.StaticText(self, wx.ID_ANY, 'ACG')
        self.ACG = wx.TextCtrl(self)
        self.AATlabel = wx.StaticText(self, wx.ID_ANY, 'AAT')
        self.AAT = wx.TextCtrl(self)
        self.AAClabel = wx.StaticText(self, wx.ID_ANY, 'AAC')
        self.AAC = wx.TextCtrl(self)
        self.AAAlabel = wx.StaticText(self, wx.ID_ANY, 'AAA')
        self.AAA = wx.TextCtrl(self)
        self.AAGlabel = wx.StaticText(self, wx.ID_ANY, 'AAG')
        self.AAG = wx.TextCtrl(self)
        self.AGTlabel = wx.StaticText(self, wx.ID_ANY, 'AGT')
        self.AGT = wx.TextCtrl(self)
        self.AGClabel = wx.StaticText(self, wx.ID_ANY, 'AGC')
        self.AGC = wx.TextCtrl(self)
        self.AGAlabel = wx.StaticText(self, wx.ID_ANY, 'AGA')
        self.AGA = wx.TextCtrl(self)
        self.AGGlabel = wx.StaticText(self, wx.ID_ANY, 'AGG')
        self.AGG = wx.TextCtrl(self)
        self.GTTlabel = wx.StaticText(self, wx.ID_ANY, 'GTT')
        self.GTT = wx.TextCtrl(self)
        self.GTClabel = wx.StaticText(self, wx.ID_ANY, 'GTC')
        self.GTC = wx.TextCtrl(self)
        self.GTAlabel = wx.StaticText(self, wx.ID_ANY, 'GTA')
        self.GTA = wx.TextCtrl(self)
        self.GTGlabel = wx.StaticText(self, wx.ID_ANY, 'GTG')
        self.GTG = wx.TextCtrl(self)
        self.GCTlabel = wx.StaticText(self, wx.ID_ANY, 'GCT')
        self.GCT = wx.TextCtrl(self)
        self.GCClabel = wx.StaticText(self, wx.ID_ANY, 'GCC')
        self.GCC = wx.TextCtrl(self)
        self.GCAlabel = wx.StaticText(self, wx.ID_ANY, 'GCA')
        self.GCA = wx.TextCtrl(self)
        self.GCGlabel = wx.StaticText(self, wx.ID_ANY, 'GCG')
        self.GCG = wx.TextCtrl(self)
        self.GATlabel = wx.StaticText(self, wx.ID_ANY, 'GAT')
        self.GAT = wx.TextCtrl(self)
        self.GAClabel = wx.StaticText(self, wx.ID_ANY, 'GAC')
        self.GAC = wx.TextCtrl(self)
        self.GAAlabel = wx.StaticText(self, wx.ID_ANY, 'GAA')
        self.GAA = wx.TextCtrl(self)
        self.GAGlabel = wx.StaticText(self, wx.ID_ANY, 'GAG')
        self.GAG = wx.TextCtrl(self)
        self.GGTlabel = wx.StaticText(self, wx.ID_ANY, 'GGT')
        self.GGT = wx.TextCtrl(self)
        self.GGClabel = wx.StaticText(self, wx.ID_ANY, 'GGC')
        self.GGC = wx.TextCtrl(self)
        self.GGAlabel = wx.StaticText(self, wx.ID_ANY, 'GGA')
        self.GGA = wx.TextCtrl(self)
        self.GGGlabel = wx.StaticText(self, wx.ID_ANY, 'GGG')
        self.GGG = wx.TextCtrl(self)
        self.submit_button = wx.Button(self, -1, 'Submit')
        self.submit_button.Bind(wx.EVT_LEFT_DOWN, self.add_organism)
        self.close_button = wx.Button(self, -1, 'Close Panel')
        self.close_button.Bind(wx.EVT_LEFT_DOWN, self.close_panel)
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.name_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.grid_sizer = wx.FlexGridSizer(8,16,5,5)
        self.name_sizer.AddMany([self.organism_label, (self.organism, 1, wx.LEFT, 5), (self.submit_button, 0, wx.LEFT|wx.BOTTOM, 10)])
        self.grid_sizer.AddMany([self.TTTlabel, self.TTT, self.TTClabel, self.TTC, self.TTAlabel, self.TTA, self.TTGlabel, self.TTG, self.TCTlabel, self.TCT, self.TCClabel, self.TCC, self.TCAlabel, self.TCA, self.TCGlabel, self.TCG,
                                self.TATlabel, self.TAT, self.TAClabel, self.TAC, self.TAAlabel, self.TAA, self.TAGlabel, self.TAG, self.TGTlabel, self.TGT, self.TGClabel, self.TGC, self.TGAlabel, self.TGA, self.TGGlabel, self.TGG,
                                self.CTTlabel, self.CTT, self.CTClabel, self.CTC, self.CTAlabel, self.CTA, self.CTGlabel, self.CTG, self.CCTlabel, self.CCT, self.CCClabel, self.CCC, self.CCAlabel, self.CCA, self.CCGlabel, self.CCG,
                                self.CATlabel, self.CAT, self.CAClabel, self.CAC, self.CAAlabel, self.CAA, self.CAGlabel, self.CAG, self.CGTlabel, self.CGT, self.CGClabel, self.CGC, self.CGAlabel, self.CGA, self.CGGlabel, self.CGG,
                                self.ATTlabel, self.ATT, self.ATClabel, self.ATC, self.ATAlabel, self.ATA, self.ATGlabel, self.ATG, self.ACTlabel, self.ACT, self.ACClabel, self.ACC, self.ACAlabel, self.ACA, self.ACGlabel, self.ACG,
                                self.AATlabel, self.AAT, self.AAClabel, self.AAC, self.AAAlabel, self.AAA, self.AAGlabel, self.AAG, self.AGTlabel, self.AGT, self.AGClabel, self.AGC, self.AGAlabel, self.AGA, self.AGGlabel, self.AGG,
                                self.GTTlabel, self.GTT, self.GTClabel, self.GTC, self.GTAlabel, self.GTA, self.GTGlabel, self.GTG, self.GCTlabel, self.GCT, self.GCClabel, self.GCC, self.GCAlabel, self.GCA, self.GCGlabel, self.GCG,
                                self.GATlabel, self.GAT, self.GAClabel, self.GAC, self.GAAlabel, self.GAA, self.GAGlabel, self.GAG, self.GGTlabel, self.GGT, self.GGClabel, self.GGC, self.GGAlabel, self.GGA, self.GGGlabel, self.GGG])
        self.sizer.AddMany([(self.seq_entry_info, 0, wx.TOP, 10), (self.name_sizer, 0, wx.TOP, 10), (self.seq_entry, 0, wx.EXPAND|wx.TOP|wx.LEFT|wx.BOTTOM, 10), (self.grid_sizer, 0, wx.LEFT|wx.BOTTOM, 10), (self.close_button, 0)])
        self.SetSizer(self.sizer)
        self.sizer.Fit(self)
        self.SetMinSize(self.GetSize())
        self.SetMaxSize(self.GetSize())
        self.Centre()
        
    def close_panel(self, event):
        self.nb.DeletePage(self.nb.GetSelection())
        
    def remove_invalid_chars(self, event):
        self.seq_entry.SetValue(filter(lambda x: x.isalpha(), self.seq_entry.GetValue()))
        
    def add_organism(self, event):
        #Get percentages from fields and add them to database
        table = CodonTable.unambiguous_dna_by_id[11].forward_table
        table['TAA'] = '*'
        table['TAG'] = '*'
        table['TGA'] = '*'
        database = 'codon_usage.db'
        connection = sqlite3.connect(database) #Connect to database
        cursor = connection.cursor()
        org = str(self.organism.GetValue())
        org_usage = {}
        codon_list = []
        flag = False
        codon_list.extend([self.TTT, self.TTC, self.TTA, self.TTG, self.TCT, self.TCC, self.TCA, self.TCG, self.TAT, self.TAC, self.TAA, self.TAG, self. TGT, self.TGC, self.TGA, self.TGG, self.CTT, self.CTC, self.CTA, self.CTG, self.CCT,
                          self.CCC, self.CCA, self.CCG, self.CAT, self.CAC, self.CAA, self.CAG, self.CGT, self.CGC, self.CGA, self.CGG, self.ATT, self.ATC, self.ATA, self.ATG, self.ACT, self.ACC, self.ACA, self.ACG, self.AAT, self.AAC,
                          self.AAA, self.AAG, self.AGT, self.AGC, self.AGA, self.AGG, self.GTT, self.GTC, self.GTA, self.GTG, self.GCT, self.GCC, self.CGA, self.GCG, self.GAT, self.GAC, self.GAA, self.GAG, self.GGT, self.GGC, self.GGA, self.GGG])
        for char in org:
            if not char.isdigit() and not char.isalpha(): #Allow only digits and letters in organism name
                org = org.replace(char, '')
        empty = False
        for field in codon_list: #Make sure no fields are empty
            if field.GetValue() == '':
                empty = True
        cursor.execute('''SELECT name FROM sqlite_master WHERE type='table' ''')
        for row in cursor:
            if org == row[0]:
                flag = True
        if not flag:
            if self.seq_entry.GetValue():
                self.sequence = str(self.seq_entry.GetValue())
                self.sequence = str(self.sequence.replace('\n', ''))
                cdn_dict = self.GetParent().GetPage(0).codon_dict(self.sequence)
                self.GetParent().GetParent().GetParent().organisms.AppendRadioItem(wx.ID_ANY, org)
                self.GetParent().GetParent().GetParent().organisms.UpdateUI()
                cursor.execute('''CREATE TABLE IF NOT EXISTS %s (id integer primary key)''' %org)
                for key in table.keys():
                    cursor.execute("ALTER TABLE %s ADD %s INT" %(org, key))
                    sql = 'INSERT INTO %s (id, %s)' #Prepare sql statement
                    sql = sql %(org,key) #Insert variables into sql statement
                    if key in cdn_dict[0].keys():
                        value = round(float(cdn_dict[0][key])/cdn_dict[1]*1000,2)
                        cursor.execute(sql + "VALUES(NULL, ?)", [str(value)])
                    else:
                        value = 0
                        cursor.execute(sql + "VALUES(NULL, ?)", [str(value)])
                connection.commit()
            elif empty ==True:
                #Launch warning message if fields are empty
                dlg = wx.MessageDialog(self, 'One or more fields are empty!', 'Empty Field Error', wx.ICON_EXCLAMATION|wx.OK)
                dlg.ShowModal()
                dlg.Destroy()
            else:
                #Get values for fields (round to two decimals)
                org_usage['TTT'] = round(float(self.TTT.GetValue()),2)
                org_usage['TTC'] = round(float(self.TTC.GetValue()),2)
                org_usage['TTA'] = round(float(self.TTA.GetValue()),2)
                org_usage['TTG'] = round(float(self.TTG.GetValue()),2)
                org_usage['TCT'] = round(float(self.TCT.GetValue()),2)
                org_usage['TCC'] = round(float(self.TCC.GetValue()),2)
                org_usage['TCA'] = round(float(self.TCA.GetValue()),2)
                org_usage['TCG'] = round(float(self.TCG.GetValue()),2)
                org_usage['TAT'] = round(float(self.TAT.GetValue()),2)
                org_usage['TAC'] = round(float(self.TAC.GetValue()),2)
                org_usage['TAA'] = round(float(self.TAA.GetValue()),2)
                org_usage['TAG'] = round(float(self.TAG.GetValue()),2)
                org_usage['TGT'] = round(float(self.TGT.GetValue()),2)
                org_usage['TGC'] = round(float(self.TGC.GetValue()),2)
                org_usage['TGA'] = round(float(self.TGA.GetValue()),2)
                org_usage['TGG'] = round(float(self.TGG.GetValue()),2)
                org_usage['CTT'] = round(float(self.CTT.GetValue()),2)
                org_usage['CTC'] = round(float(self.CTC.GetValue()),2)
                org_usage['CTA'] = round(float(self.CTA.GetValue()),2)
                org_usage['CTG'] = round(float(self.CTG.GetValue()),2)
                org_usage['CCT'] = round(float(self.CCT.GetValue()),2)
                org_usage['CCC'] = round(float(self.CCC.GetValue()),2)
                org_usage['CCA'] = round(float(self.CCA.GetValue()),2)
                org_usage['CCG'] = round(float(self.CCG.GetValue()),2)
                org_usage['CAT'] = round(float(self.CAT.GetValue()),2)
                org_usage['CAC'] = round(float(self.CAC.GetValue()),2)
                org_usage['CAA'] = round(float(self.CAA.GetValue()),2)
                org_usage['CAG'] = round(float(self.CAG.GetValue()),2)
                org_usage['CGT'] = round(float(self.CGT.GetValue()),2)
                org_usage['CGC'] = round(float(self.CGC.GetValue()),2)
                org_usage['CGA'] = round(float(self.CGA.GetValue()),2)
                org_usage['CGG'] = round(float(self.CGG.GetValue()),2)
                org_usage['ATT'] = round(float(self.ATT.GetValue()),2)
                org_usage['ATC'] = round(float(self.ATC.GetValue()),2)
                org_usage['ATA'] = round(float(self.ATA.GetValue()),2)
                org_usage['ATG'] = round(float(self.ATG.GetValue()),2)
                org_usage['ACT'] = round(float(self.ACT.GetValue()),2)
                org_usage['ACC'] = round(float(self.ACC.GetValue()),2)
                org_usage['ACA'] = round(float(self.ACA.GetValue()),2)
                org_usage['ACG'] = round(float(self.ACG.GetValue()),2)
                org_usage['AAT'] = round(float(self.AAT.GetValue()),2)
                org_usage['AAC'] = round(float(self.AAC.GetValue()),2)
                org_usage['AAA'] = round(float(self.AAA.GetValue()),2)
                org_usage['AAG'] = round(float(self.AAG.GetValue()),2)
                org_usage['AGT'] = round(float(self.AGT.GetValue()),2)
                org_usage['AGC'] = round(float(self.AGC.GetValue()),2)
                org_usage['AGA'] = round(float(self.AGA.GetValue()),2)
                org_usage['AGG'] = round(float(self.AGG.GetValue()),2)
                org_usage['GTT'] = round(float(self.GTT.GetValue()),2)
                org_usage['GTC'] = round(float(self.GTC.GetValue()),2)
                org_usage['GTA'] = round(float(self.GTA.GetValue()),2)
                org_usage['GTG'] = round(float(self.GTG.GetValue()),2)
                org_usage['GCT'] = round(float(self.GCT.GetValue()),2)
                org_usage['GCC'] = round(float(self.GCC.GetValue()),2)
                org_usage['GCA'] = round(float(self.GCA.GetValue()),2)
                org_usage['GCG'] = round(float(self.GCG.GetValue()),2)
                org_usage['GAT'] = round(float(self.GAT.GetValue()),2)
                org_usage['GAC'] = round(float(self.GAC.GetValue()),2)
                org_usage['GAA'] = round(float(self.GAA.GetValue()),2)
                org_usage['GAG'] = round(float(self.GAG.GetValue()),2)
                org_usage['GGT'] = round(float(self.GGT.GetValue()),2)
                org_usage['GGC'] = round(float(self.GGC.GetValue()),2)
                org_usage['GGA'] = round(float(self.GGA.GetValue()),2)
                org_usage['GGG'] = round(float(self.GGG.GetValue()),2)
                if not flag:
                    cursor.execute('''CREATE TABLE IF NOT EXISTS %s (id integer primary key)''' %org)
                    empty = False
                    for key in table.keys():
                        #Add values to db
                        cursor.execute("ALTER TABLE %s ADD %s INT" %(org, key))
                        sql = 'INSERT INTO %s (id, %s)' #Prepare sql statement
                        sql = sql %(org,key) #Insert variables into sql statement
                        cursor.execute(sql + "VALUES(NULL, ?)", [org_usage[key]])
                    connection.commit()
                    self.GetParent().GetParent().GetParent().organisms.AppendCheckItem(wx.ID_ANY, org)
                    self.GetParent().GetParent().GetParent().organisms.UpdateUI()
            count = 0
            for page in self.GetParent().GetChildren():
                if hasattr(page, 'addorg'):
                    self.GetParent().DeletePage(self.GetParent().GetPageCount()-1)
                count += 1
        else:
            dlg = wx.MessageDialog(self, 'The organism is already in the database', 'Organism Entry Error', wx.ICON_EXCLAMATION|wx.OK)
            dlg.ShowModal()
            dlg.Destroy()
            
    def delete_organism(self, event):
        #Delete organism from codon usage database permanently
        org = self.GetParent().GetParent().GetParent().get_organism()
        connection = sqlite3.connect('codon_usage.db') #Establish connection to database
        cursor = connection.cursor()
        if org != 'EcoliK12': #E.coli K-12 can't be removed from db
            cursor.execute('''DROP TABLE IF EXISTS %s''' %org) 
        else: #Give warning message if user tries to delete E.coli K-12
            self.dlg2 = wx.MessageDialog(self, 'E. coli K-12 cannot be deleted!', 'Warning', wx.ICON_EXCLAMATION|wx.OK)
            self.dlg2.ShowModal()
            self.dlg2.Destroy()
        connection.commit() #Commit changes to database
        self.GetParent().AddPage(self, 'Add Organism')
        self.GetParent().DeletePage(self.GetParent().GetPageCount()-1)
        
    
              

            