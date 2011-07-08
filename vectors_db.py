'''
Created on Jul 30, 2010
@author: Doug Crandell
'''
'''
A module which sets up a database for the storage of common vector sequences. Also contains class for vector addition panel
'''
import sqlite3
import wx

class db():
    def __init__(self):
        self = self
        
    def create_db(self):
        connection = sqlite3.connect('vectors.db')
        cursor = connection.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS vectors (id integer primary key, vector_name, vector_sequence)''')
        connection.commit()
        
class VectorPanel(wx.Panel):
    def __init__(self, parent, id):
        wx.Panel.__init__(self, parent)
        self.vector = 'Vector'
        self.nb = parent
        self.vector_name = wx.TextCtrl(self, size = (300, 20), style = wx.TE_PROCESS_ENTER)
        self.vector_name_label = wx.StaticText(self, wx.ID_ANY, 'Vector Name:')
        self.seq_disp = wx.TextCtrl(self, size = (500,200), style = wx.TE_PROCESS_ENTER|wx.TE_MULTILINE)
        self.seq_disp_label = wx.StaticText(self, wx.ID_ANY, 'Vector Sequence:')
        self.seq_disp.SetValue(str(self.GetParent().GetPage(0).vector_disp.GetValue()))
        self.submit_button = wx.Button(self, -1, 'Submit Vector')
        self.submit_button.Bind(wx.EVT_LEFT_DOWN, self.submit)
        self.file_button = wx.Button(self, -1, 'Add From File...')
        self.file_button.Bind(wx.EVT_LEFT_DOWN, self.add_from_file)
        self.close_button = wx.Button(self, -1, 'Close Panel')
        self.close_button.Bind(wx.EVT_LEFT_DOWN, self.close_panel)
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.button_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.vector_name_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.seq_disp_sizer = wx.BoxSizer(wx.VERTICAL)
        self.vector_name_sizer.AddMany([self.vector_name_label, (self.vector_name, 0, wx.EXPAND|wx.LEFT, 5)])
        self.seq_disp_sizer.AddMany([self.seq_disp_label, (self.seq_disp, 0, wx.EXPAND|wx.LEFT, 5)])
        self.button_sizer.AddMany([self.file_button, (self.submit_button, 0, wx.LEFT, 5)])
        self.sizer.AddMany([(self.vector_name_sizer, 0, wx.EXPAND|wx.LEFT|wx.TOP, 10), (self.seq_disp_sizer, 0, wx.EXPAND|wx.LEFT|wx.TOP, 10), (self.button_sizer, 0, wx.LEFT|wx.TOP, 10), (self.close_button, 0, wx.TOP, 325)])
        self.SetSizerAndFit(self.sizer)
        
    def close_panel(self, event):
        self.nb.DeletePage(self.nb.GetSelection())
    
    def add_from_file(self, event):
        filters = 'FASTA files (*.fasta;*.fa;*.fna;*.seq;*.txt)|*.fasta;*.fa;*.fna;*.seq;*.txt'
        dlg = wx.FileDialog(None, message = 'Submit vector in fasta format', wildcard = filters, style = wx.OPEN)
        if dlg.ShowModal() == wx.ID_OK:
            with open(str(dlg.GetPath())) as file:
                title = file.readline()
                self.vector_name.SetValue(title.strip('>'))
                sequence = file.readline().upper()
                self.seq_disp.SetValue(filter(lambda x: x.isalpha(), str(sequence)))
    
    def submit(self, event):
        connection = sqlite3.connect('vectors.db')
        cursor = connection.cursor()
        name = str(self.vector_name.GetValue())
        seq = str(self.seq_disp.GetValue())
        self.vector_list = []
        flag = False
        t = name, seq #Tuple of values to add to database
        if name and seq:
            cursor.execute('''SELECT vector_name FROM vectors''')
            for row in cursor:
                if row[0] == name:
                    flag = True
                    dlg = wx.MessageDialog(self, 'A vector is already in the database under that name!\nPlease try again.', 'Name Error!', wx.ICON_ERROR|wx.OK)
                    dlg.ShowModal()
                    dlg.Destroy()
                self.vector_list.append(row[0])
            if flag is not True:
                cursor.execute('''INSERT INTO vectors (id, vector_name, vector_sequence) VALUES (NULL, ?, ?)''', t) #Add values to database
                connection.commit()
                dlg = wx.MessageDialog(self, 'Thank you for your entry into the vector database', 'Successful Addition!', wx.ICON_EXCLAMATION|wx.OK)
                dlg.ShowModal()
                dlg.Destroy()
                insert = len(filter(lambda x: x < name, (self.GetParent().GetPage(0).vector_listbox.GetItems())))
                self.GetParent().GetPage(0).vector_listbox.Insert(name, insert)
        else:
            dlg = wx.MessageDialog(self, 'One or more fields is empty!', 'Error!', wx.ICON_ERROR|wx.OK)
            dlg.ShowModal()
            dlg.Destroy()
        count = 0
        for page in self.GetParent().GetChildren():
            if hasattr(page, 'vector'):
                self.GetParent().DeletePage(self.GetParent().GetPageCount()-1)
            count += 1
    
    def delete_vector(self, event):
        #Removes vector from vector database permanently
        connection = sqlite3.connect('vectors.db')
        cursor = connection.cursor()
        vector_names = self.GetParent().GetPage(0).get_selected_vectors()
        cursor.execute('''SELECT id, vector_name FROM vectors''')
        if vector_names != []:
            for row in cursor:
                if row[1] in vector_names:
                    cursor.execute('''DELETE FROM vectors WHERE id = %d''' %row[0])
            connection.commit()
            for item in self.GetParent().GetPage(0).vector_listbox.GetSelections():
                self.GetParent().GetPage(0).vector_listbox.Delete(item)
        else:
            dlg = wx.MessageDialog(self, 'No vectors were selected from the list to delete', 'Warning!', wx.ICON_EXCLAMATION)
            dlg.ShowModal()
            dlg.Destroy()
        self.GetParent().AddPage(self, 'Add Vector')
        self.GetParent().DeletePage(self.GetParent().GetPageCount()-1)