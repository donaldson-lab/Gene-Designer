''''
Created on Jun 23, 2010
Author: Doug Crandell
University of North Carolina at Chapel Hill
'''
'''
A module that sets up a database for the storage of data concerning restriction enzymes.  Data stored includes the enzyme name, where the enzyme cuts (upstream, downstream), whether the enzyme cuts the
sequence and its complement in the same place or at different locations, the pattern that the restriction enzyme recognizes, enzyme methylation data, and information on whether the enzyme is commercially available.
Enzyme data comes from the Rebase database.  This code in this module is based on an example given by Mitchell L. Model in Bioinformatics Programming using Python
'''

import sqlite3
import wx


class db():
    
    def __init__(self, filename): 
        #Initialize the class
        self.filename = filename  
          
    def read_enzymes_from_file(self, filename):
        with open(filename) as file:
            self.skip_intro(file)
            return self.get_enzymes(file)
        
    def skip_intro(self, file): 
        #Skip documentation at beginning of file. Position at first line of the first enzyme
        line = ''
        while not line.startswith('<1>'):
            line = file.readline()
        while not line.startswith(' '):
            line = file.readline()
        while len(line) > 1:
            line = file.readline()
        return line
    
    def get_enzymes(self,src):
        #Create a dictionary with enzyme data
        enzymes =  {}
        enzyme = self.next_enzyme(src)
        while enzyme:
            enzymes[enzyme[0]] = enzyme #Dictionary key is enzyme's name
            enzyme = self.next_enzyme(src)
        return enzymes
    
    def read_field(self, file):
        #Read enzyme name 
        return file.readline()[3:-1]
    
    def read_other_fields(self, file):
        #Read remaining fields after enzyme name and store as a 6-tupe
        return [self.read_field(file) for n in range(6)] #Read 6 fields 
    
    def next_enzyme(self, file):
        #Read the data from the next enzyme and add the data to the database.
        name = self.read_field(file)
        connection = sqlite3.connect('re.db')
        cursor = connection.cursor()
        '''
        Create a table of enzymes in the database with the following columns: renzname, downtop, downbottom, uptop, upbottom, k, pattern, methylation, commercial.  The data stored in each column is as follows:
        renzname = enzyme name; downtop = location of downstream cut; downbottom = location of downstream cut on complementary sequence; uptop = upstream cut (if any) on sequence
        upbottom = upstream cut on complementary sequence; k = location of ^ in restriction sequence pattern (-1 if none); pattern = sequence recognized by restriction enzyme;
        methylation = methylation data for restriction enzyme; commercial = commercial availability of enzyme
        '''
        cursor.execute('''CREATE TABLE IF NOT EXISTS enzymes (id integer primary key, r_enz_name, downstream_top, downstream_bottom, upstream_top, upstream_bottom, blunt, pattern, methylation, commercial)''')
        if name:
            fields = [name] + self.read_other_fields(file)
            blunt = fields[2].find('^') #Get location of ^ (if any)
            if blunt != -1:
                a = fields[2].split('^')[0]
                b = fields[2].split('^')[1]
                if len(a) != len(b):
                    blunt = -2
                    downstream_top = fields[2].find('^')
                    downstream_bottom = len(fields[2]) - fields[2].find('^') -1
            fields[6] = filter(lambda x: x.isalpha(), fields[2]) #Get the pattern that is recognized (only letters)
            # Parse the fields for cutting information and add to tuple
            tmp = fields[2].split('/')
            if blunt != -2:
                downstream_top = filter(lambda x: x is '-' or x.isdigit(), tmp[0])
            if len(tmp) == 3:
                tmp1 = tmp[1].find(')')
                tmp2 = tmp[1].find('(')
                tmp3 = tmp[1][:tmp1] + "/" + tmp[1][tmp2+1:]
                tmp3 = tmp3.split('/')
                upstream_top = filter(lambda x: x is '-' or x.isdigit(), tmp[0])
                upstream_bottom = tmp3[0]
                downstream_top = tmp3[1]
                downstream_bottom = tmp[2][:-1]
            elif len(tmp) == 2:
                downstream_bottom = filter(lambda x: x is '-' or x.isdigit(), tmp[1])
                if blunt == -2:
                    upstream_top = upstream_bottom = ""
                else:
                    downstream_bottom = upstream_top = upstream_bottom = ""
            else:
                if blunt == -2:
                    upstream_top = upstream_bottom = ""
                else:
                    downstream_bottom = upstream_top = upstream_bottom = ""
            fields[0] = fields[0].replace('.','') #Remove '.' from enzyme names
            fields[0] = fields[0].replace('-','') #Remove '-' from enzyme names
            methylase = ''
            if fields[3] != '':
                methylation = filter(lambda x: x.isdigit(), fields[3].split('(')[1].split(',')[0])
                if int(methylation) == 6:
                    methylase = 'Dam'
                elif int(methylation) == 5 or int(methylation) == 4:
                    methylase = 'Dcm'
                else:
                    methylase = ''
            t = fields[0], downstream_top, downstream_bottom, upstream_top, upstream_bottom, blunt, fields[6], methylase, fields[4] #Store information in tuple
            cursor.execute("INSERT INTO enzymes (id, r_enz_name, downstream_top, downstream_bottom, upstream_top, upstream_bottom, blunt, pattern, methylation, commercial) VALUES (NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?)", t) #Add information to database
            connection.commit() #Commit changes to database
            return fields
        
class AddEnzymePanel(wx.Panel):
    #Frame with fields to enter new enzyme information
    def __init__(self, parent, id, title):
        wx.Panel.__init__(self, parent)
        self.nb = parent
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.name_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.restriction_seq_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.enz_name = wx.StaticText(self, wx.ID_ANY, 'Enzyme Name:')
        self.enz_name_field = wx.TextCtrl(self)
        self.restriction_seq = wx.StaticText(self, wx.ID_ANY, 'Restriction Sequence:')
        self.restriction_seq_field = wx.TextCtrl(self)
        self.methylation = wx.StaticText(self, wx.ID_ANY, 'Methylation:')
        self.methylation_field = wx.TextCtrl(self)
        self.methylation_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.commercial = wx.StaticText(self, wx.ID_ANY, 'Commercial Availability:')
        self.commercial_field = wx.TextCtrl(self)
        self.commercial_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.name_sizer.AddMany([self.enz_name, (self.enz_name_field, 1, wx.LEFT, 5)])
        self.restriction_seq_sizer.AddMany([self.restriction_seq, (self.restriction_seq_field, 1, wx.LEFT, 5)])
        self.methylation_sizer.AddMany([self.methylation, (self.methylation_field, 0, wx.LEFT, 5)])
        self.commercial_sizer.AddMany([self.commercial, (self.commercial_field, 0, wx.LEFT, 5)])
        self.restrict_seq_info = wx.StaticText(self, wx.ID_ANY, 'Restriction sequences should be entered in the same format as the Rebase databases:\nhttp://rebase.neb.com/rebase')
        self.add_button = wx.Button(self, -1, 'Add Enzyme')
        self.add_button.Bind(wx.EVT_LEFT_DOWN, self.add_enzyme)
        self.close_button = wx.Button(self, -1, 'Close Panel')
        self.close_button.Bind(wx.EVT_LEFT_DOWN, self.close_panel)
        self.sizer.AddMany([(self.name_sizer, 0, wx.TOP|wx.LEFT, 10), (self.restriction_seq_sizer, 0, wx.TOP|wx.LEFT, 10), (self.methylation_sizer, 0, wx.TOP|wx.LEFT, 10), (self.commercial_sizer, 0, wx.TOP|wx.LEFT, 10),
                            (self.add_button, 0, wx.LEFT, 5), (self.restrict_seq_info, 1, wx.TOP|wx.LEFT, 10), (self.close_button, 1, wx.TOP, 225)])
        self.SetSizerAndFit(self.sizer)
        self.SetClientSize(self.GetSize())
        
    def close_panel(self, event):
        self.nb.DeletePage(self.nb.GetSelection())
        
    def add_enzyme(self, event):
        self.add_enz = 'Add Enzyme'
        #Add enzyme to restriction enzyme database
        database = 're.db' #Restriction enzyme db
        connection = sqlite3.connect(database) #Establish connection to db
        cursor = connection.cursor()
        #Parse data and ad to db
        if self.enz_name_field.GetValue() != '' and self.restriction_seq_field.GetValue() != '':
            cursor.execute('SELECT r_enz_name FROM enzymes')
            name = self.enz_name_field.GetValue()
            restriction_sequence = self.restriction_seq_field.GetValue()
            pattern = filter(lambda x: x.isalpha(), restriction_sequence)
            methylation = str(self.methylation_field.GetValue())
            methylation = filter(lambda x: x is '-' or x.isdigit(), methylation)
            commercial = str(self.commercial_field.GetValue())
            i = 0
            blunt = -1
            downstream_top = ''
            downstream_bottom = ''
            upstream_top = ''
            upstream_bottom = '' 
            for char in restriction_sequence:
                if char == '^':
                    blunt = i
                i += 1
            tmp = restriction_sequence.split('/')
            downstream_top = filter(lambda x: x is '-' or x.isdigit(), tmp[0])
            if len(tmp) == 3:
                tmp1 = tmp[1].find(')')
                tmp2 = tmp[1].find('(')
                tmp3 = tmp[1][:tmp1] + "/" + tmp[1][tmp2+1:]
                tmp3 = tmp3.split('/')
                upstream_top = filter(lambda x: x is '-' or x.isdigit(), tmp[0])
                upstream_bottom = tmp3[0]
                downstream_top = tmp3[1]
                downstream_bottom = tmp[2][:-1]
            elif len(tmp) == 2:
                downstream_bottom = filter(lambda x: x is '-' or x.isdigit(), tmp[1])
                upstream_top = upstream_bottom = ""
            else:
                downstream_bottom = upstream_top = upstream_bottom = ""
            t = name, downstream_top, downstream_bottom, upstream_top, upstream_bottom, blunt, pattern, methylation, commercial #Store values as tuple
            cursor.execute("INSERT INTO enzymes (id, r_enz_name, downstream_top, downstream_bottom, upstream_top, upstream_bottom, blunt, pattern, methylation, commercial) VALUES (NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?)", t) #Add values to db
            connection.commit() #Commit changes to db
            insert = len(filter(lambda x: x < name, (self.GetParent().GetPage(0).enzyme_listbox.GetItems())))
            self.GetParent().GetPage(0).enzyme_listbox.Insert(name, insert)
            self.GetParent().GetParent().GetParent().target_list[name] = pattern
            self.nb.DeletePage(self.nb.GetSelection())
                
    def delete_enzyme(self, event):
        #Deletes a restriction enzyme permanently from the database
        connection = sqlite3.connect('re.db')
        cursor = connection.cursor()
        enzymes = self.nb.GetPage(0).get_selected_enzymes()
        cursor.execute('''SELECT id, r_enz_name FROM enzymes''')
        if enzymes != []:
            for row in cursor:
                if row[1] in enzymes:
                    cursor.execute('''DELETE FROM enzymes WHERE id = %d'''%row[0])
            connection.commit()
            for item in self.nb.GetPage(0).enzyme_listbox.GetSelections():
                self.nb.GetPage(0).enzyme_listbox.Delete(item)
        else:
            dlg = wx.MessageDialog(self, 'Warning: no enzymes were selected!', 'Enzyme Selection Warning', wx.ICON_EXCLAMATION|wx.OK)
            dlg.ShowModal()
            dlg.Destroy()
        self.GetParent().AddPage(self, 'Add Enzyme')
        self.GetParent().DeletePage(self.GetParent().GetPageCount()-1)