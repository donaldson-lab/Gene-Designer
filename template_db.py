'''
Created on Nov 8, 2010

@author: virushunter2
'''
import sqlite3
import wx

class db():
    def __init__(self): 
        #Initialize the class
        self = self
            
    def create_db(self):
        connection = sqlite3.connect('templates.db')
        cursor = connection.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS templates (id integer primary key, template_name, template_sequence)''')
        connection.commit()
                    
class NewTemplatePanel(wx.Panel):
    def __init__(self, parent, id, sequence_names, sequences):
        wx.Panel.__init__(self, parent)
        self.nb = parent
        self.sequence_listbox = wx.ListBox(self, -1, wx.DefaultPosition, wx.DefaultSize, sequence_names)
        self.rename_button = wx.Button(self, -1, 'Rename Sequence')
        self.rename_button.Bind(wx.EVT_LEFT_DOWN, self.rename)
        self.submit_button = wx.Button(self, -1, 'Submit Sequences to Database')
        self.submit_button.Bind(wx.EVT_LEFT_DOWN, lambda evt, sequences = sequences: self.submit(sequences))
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.sizer.AddMany([self.sequence_listbox, (self.rename_button, 0, wx.TOP, 10), (self.submit_button, 0, wx.TOP, 10)])
        self.SetSizerAndFit(self.sizer)
        self.SetClientSize(self.GetSize())
        
    def rename(self, event):
        item = self.sequence_listbox.GetSelections()[0]
        name_list = self.sequence_listbox.GetItems()
        dlg = wx.TextEntryDialog(self, 'Sequence Name:', 'Rename Sequence', defaultValue=name_list[item]) #Get name for sequence
        if dlg.ShowModal() == wx.ID_OK:
            seq_name = str(dlg.GetValue())
        dlg.Destroy()
        self.sequence_listbox.Delete(item)
        self.sequence_listbox.Insert(seq_name, item)
        
    def submit(self, sequences):  
        connection = sqlite3.connect('templates.db')
        cursor = connection.cursor()
        name_list = self.sequence_listbox.GetItems()
        for name, seq in zip(name_list, sequences):
            t = name, seq.upper()
            cursor.execute('''INSERT INTO templates (id, template_name, template_sequence) VALUES (NULL, ?, ?)''', t) #Add values to database
            connection.commit()
        self.nb.DeletePage(self.nb.GetPageCount()-1)

class TemplatePanel(wx.Panel):
    def __init__(self, parent, id):
        wx.Panel.__init__(self, parent)
        self.nb = parent
        connection = sqlite3.connect('templates.db')
        cursor = connection.cursor()
        cursor.execute('''SELECT template_name FROM templates''')
        sequence_names = []
        for row in cursor:
            sequence_names.append(row[0])
        self.text = wx.StaticText(self, wx.ID_ANY, 'Sequences:')
        self.sequence_list = wx.ListBox(self, -1, wx.DefaultPosition, wx.DefaultSize, sequence_names)
        self.load_button = wx.Button(self, -1, 'Load Sequence')
        self.load_button.Bind(wx.EVT_LEFT_DOWN, self.load)
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.sizer.AddMany([self.text, (self.sequence_list, 0, wx.TOP, 10), (self.load_button, 0, wx.TOP,  10)])
        self.SetSizerAndFit(self.sizer)
        self.SetClientSize(self.GetSize())
        
    def load(self, event):
        connection = sqlite3.connect('templates.db')
        cursor = connection.cursor()
        cursor.execute('''SELECT template_name, template_sequence FROM templates''')
        template_name = self.get_selected_template()[0]
        for row in cursor:
            if row[0] == template_name:
                self.nb.GetPage(0).seq_disp.SetValue(row[1])
                self.nb.GetPage(1).seq_disp.SetValue(row[1])
        self.nb.DeletePage(self.nb.GetPageCount()-1)
            
    def get_selected_template(self):
        #Get the vectors selected from the vector list
        name_list = self.sequence_list.GetItems()
        pos_tuple = self.sequence_list.GetSelections()
        selected_list = []
        for pos in pos_tuple:
            selected_list.append(name_list[pos])
        return selected_list