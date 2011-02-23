'''
Created on Sep 10, 2010

@author: virushunter2
'''
import sqlite3
import wx
import genedesign
import re

class db():
    def __init__(self):
        self = self
        
    def create_db(self):
        connection = sqlite3.connect('linkers.db')
        cursor = connection.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS linkers (id integer primary key, linker_name, linker_sequence, associated_enz)''')
        connection.commit()
        
class LinkerPanel(wx.Panel):
    def __init__(self, parent, id, linker_list, sequence):
        wx.Panel.__init__(self, parent)
        self.linker_list = linker_list
        self.nb = parent
        self.five_linker_name = wx.TextCtrl(self, size = (300, 20), style=wx.TE_PROCESS_ENTER)
        self.five_linker_name_label = wx.StaticText(self, wx.ID_ANY, '5\' Linker Name:')
        self.five_linker_seq_disp = wx.TextCtrl(self, size = (500, 20), style=wx.TE_PROCESS_ENTER)
        self.five_linker_seq_disp_label = wx.StaticText(self, wx.ID_ANY, '5\' Linker Sequence:')
        self.five_enz_disp = wx.TextCtrl(self, size = (300, 20), style = wx.TE_PROCESS_ENTER)
        self.five_enz_label = wx.StaticText(self, wx.ID_ANY, 'Enzyme Associated with 5\' Linker:')
        self.three_linker_name = wx.TextCtrl(self, size = (300, 20), style=wx.TE_PROCESS_ENTER)
        self.three_linker_name_label = wx.StaticText(self, wx.ID_ANY, '3\' Linker Name:')
        self.three_linker_seq_disp = wx.TextCtrl(self, size = (500, 20), style=wx.TE_PROCESS_ENTER)
        self.three_linker_seq_disp_label = wx.StaticText(self, wx.ID_ANY, '3\' Linker Sequence:')
        self.three_enz_disp = wx.TextCtrl(self, size = (300, 20), style = wx.TE_PROCESS_ENTER)
        self.three_enz_label = wx.StaticText(self, wx.ID_ANY, 'Enzyme Associated with 3\' Linker:')
        self.seq_disp = wx.TextCtrl(self, size = (500, 200), style=wx.TE_PROCESS_ENTER)
        self.seq_disp.SetValue(sequence)
        self.linker_box = wx.ListBox(self, wx.ID_ANY, wx.DefaultPosition, (125, 250), sorted(linker_list))
        self.linker_box.Bind(wx.EVT_LISTBOX, self.fill_form)
        self.linker_box_label = wx.StaticText(self, wx.ID_ANY, 'Linkers:')
        self.five_choice = wx.RadioButton(self, wx.ID_ANY, '5 Prime')
        self.five_choice.SetValue(True)
        self.three_choice = wx.RadioButton(self, wx.ID_ANY, '3 Prime')
        self.radio_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.seq_label = wx.StaticText(self, wx.ID_ANY, 'Sequence:')
        self.submit_button = wx.Button(self, -1, 'Submit')
        self.submit_button.Bind(wx.EVT_LEFT_DOWN, self.submit)
        self.close_button = wx.Button(self, -1, "Close Panel")
        self.close_button.Bind(wx.EVT_LEFT_DOWN, self.close_panel)
        self.linker_sizer = wx.BoxSizer(wx.VERTICAL)
        self.linker_box_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.hbox = wx.BoxSizer(wx.HORIZONTAL)
        self.five_linker_seq_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.three_linker_seq_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.five_enz_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.three_enz_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.five_name_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.three_name_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.seq_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.seq_disp.SetValue(str(self.GetParent().GetPage(0).seq_disp.GetValue()))
        self.radio_sizer.AddMany([(self.five_choice), (self.three_choice, 0, wx.LEFT, 3)])
        self.five_name_sizer.AddMany([self.five_linker_name_label, (self.five_linker_name, 0, wx.LEFT, 5)])
        self.three_name_sizer.AddMany([self.three_linker_name_label, (self.three_linker_name, 0, wx.LEFT, 5)])
        self.five_linker_seq_sizer.AddMany([self.five_linker_seq_disp_label, (self.five_linker_seq_disp, 0, wx.LEFT, 5)])
        self.three_linker_seq_sizer.AddMany([self.three_linker_seq_disp_label, (self.three_linker_seq_disp, 0, wx.LEFT, 5)])
        self.five_enz_sizer.AddMany([self.five_enz_label, (self.five_enz_disp, 0, wx.LEFT, 5)])
        self.three_enz_sizer.AddMany([self.three_enz_label, (self.three_enz_disp, 0, wx.LEFT, 5)])
        self.seq_sizer.AddMany([self.seq_label, (self.seq_disp, 0, wx.LEFT, 5)])
        self.linker_box_sizer.AddMany([(self.linker_box_label, 0, wx.TOP, 5), (self.linker_box, 0, wx.TOP, 5), (self.radio_sizer, 0, wx.TOP| wx.LEFT, 5)])
        self.hbox.AddMany([self.linker_sizer, (self.linker_box_sizer, 0, wx.LEFT, 30)])
        self.linker_sizer.AddMany([(self.five_name_sizer, 0, wx.TOP, 10), (self.five_linker_seq_sizer, 0, wx.TOP, 10), (self.five_enz_sizer, 0, wx.TOP, 10), (self.three_name_sizer, 0, wx.TOP, 10), (self.three_linker_seq_sizer, 0, wx.TOP, 10), (self.three_enz_sizer, 0, wx.TOP, 10)])
        self.sizer.AddMany([self.hbox, (self.seq_sizer, 0, wx.TOP, -60), (self.submit_button, 0, wx.TOP, 10), (self.close_button, 0, wx.TOP, 190)])
        self.SetSizerAndFit(self.sizer)
        
    def submit(self, event):
        self.original_seq = str(self.GetParent().GetPage(0).seq_disp.GetValue())
        self.five = self.check_five(self.original_seq)
        self.three = self.check_three(self.original_seq)
        self.five_link = str(self.five_linker_seq_disp.GetValue().upper())
        self.three_link = str(self.three_linker_seq_disp.GetValue().upper())
        self.seq = str(self.seq_disp.GetValue())
        if self.three == False:
            self.seq_disp.SetValue(str(self.five_link + self.seq))
        elif self.five == False:
            self.seq_disp.SetValue(str(self.seq + self.three_link))
        else:
            self.seq_disp.SetValue(str(self.five_link + self.seq + self.three_link))
        self.GetParent().GetPage(0).seq_disp.SetValue(str(self.seq_disp.GetValue()))
        self.GetParent().GetPage(0).mutation_seq_disp.SetValue(self.GetParent().GetPage(0).mutation_aa_disp.GetValue().split('\n')[0] + '\n' +str(self.seq_disp.GetValue()))
        self.nb.DeletePage(self.nb.GetSelection())
        
    def check_five(self, seq):
        self.patterns = genedesign.Search.db_retrieve(genedesign.Search())[1]
        self.five_enz = str(self.five_enz_disp.GetValue())
        if self.five_enz != '':
            try:
                enz_pattern = self.patterns[self.five_enz]
                if self.enz_pattern_match(enz_pattern, seq):
                    self.db_addition(self.linker_list, str(self.five_linker_name.GetValue()), str(self.five_linker_seq_disp.GetValue()), self.five_enz)
                else:
                    self.GetParent().GetPage(0).seq_disp.SetValue(seq)
                    self.seq_disp.SetValue(str(self.seq_disp.GetValue()))
                return True
            except KeyError:
                dlg = wx.MessageDialog(self, 'The provided enzyme, %s, is not in the database' %self.five_enz, 'Enzyme Error!', wx.ICON_EXCLAMATION | wx.OK)
                dlg.ShowModal()
                dlg.Destroy()
                return False
        
    def check_three(self, seq):
        self.patterns = genedesign.Search.db_retrieve(genedesign.Search())[1]
        self.three_enz = str(self.three_enz_disp.GetValue())
        if self.three_enz != '':
            try:
                enz_pattern = self.patterns[self.three_enz]
                if self.enz_pattern_match(enz_pattern, seq):
                    self.db_addition(self.linker_list, str(self.three_linker_name.GetValue()), str(self.three_linker_seq_disp.GetValue()), self.three_enz)
                    return True
                else:
                    self.GetParent().GetPage(0).seq_disp.SetValue(seq)
                    self.seq_disp.SetValue(str(self.seq_disp.GetValue()))
            except KeyError:
                dlg = wx.MessageDialog(self, 'The provided enzyme, %s, is not in the database' %self.three_enz, 'Enzyme Error!', wx.ICON_EXCLAMATION | wx.OK)
                dlg.ShowModal()
                dlg.Destroy()
                return False
            
    def enz_pattern_match(self, enz_pattern, seq):
        if re.search(enz_pattern, seq) != None:
            dlg = wx.MessageDialog(self, 'The associated enzyme\'s restriction pattern appears in the sequence!', 'Warning!', wx.ICON_EXCLAMATION | wx.OK | wx.CANCEL)
            if dlg.ShowModal() == wx.ID_OK:
                return True
            else:
                return False
            dlg.Destroy()
        else:
            return True
        
    def db_addition(self, linker_list, linker_name, linker_seq, enz):
        connection = sqlite3.connect('linkers.db')
        cursor = connection.cursor()
        cursor.execute('''SELECT linker_name FROM linkers''')
        if linker_name not in linker_list:
            dlg = wx.MessageDialog(self, 'The linker sequence %s is not currently in the database. Would you like to add this sequence?' %linker_name, 'Linker Database Addition', wx.YES_NO)
            if dlg.ShowModal() == wx.ID_YES:
                t = linker_name, linker_seq, enz
                cursor.execute('''INSERT INTO linkers (id, linker_name, linker_sequence, associated_enz) VALUES (NULL, ?, ?, ?)''', t) #Add values to database
                insert = len(filter(lambda x: x < linker_name, (self.linker_box.GetItems())))
                self.linker_box.Insert(linker_name, insert)
                linker_list.append(linker_name)
            dlg.Destroy()
        connection.commit()
        
    def fill_form(self, event):
        self.name = ''
        self.sequence = ''
        self.enz = ''
        name_list = self.linker_box.GetItems()
        pos_tuple = self.linker_box.GetSelections()
        selected = ''
        for pos in pos_tuple:
            selected = name_list[pos]
        connection = sqlite3.connect('linkers.db')
        cursor = connection.cursor()
        cursor.execute('''SELECT linker_name, linker_sequence, associated_enz FROM linkers''')
        for row in cursor:
            if row[0] == selected:
                self.name = str(row[0])
                self.sequence = str(row[1])
                self.enz = str(row[2])
        if self.five_choice.GetValue():
            self.five_linker_name.SetValue(self.name)
            self.five_linker_seq_disp.SetValue(self.sequence)
            self.five_enz_disp.SetValue(self.enz)
        elif self.three_choice.GetValue():
            self.three_linker_name.SetValue(self.name)
            self.three_linker_seq_disp.SetValue(self.sequence)
            self.three_enz_disp.SetValue(self.enz)
            
    def close_panel(self, event):
        self.nb.DeletePage(self.nb.GetSelection())