'''
Created on Sep 8, 2010

@author: virushunter2
'''
import wx
import wx.html as html

class HelpWindow(wx.Frame):
    def __init__(self, parent, id):
        wx.Frame.__init__(self, parent, id)
        self.panel = wx.Panel(self, -1)
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        help = html.HtmlWindow(self.panel, -1, style=wx.NO_BORDER)
        help.LoadFile('help.html')
        self.sizer.Add(help, 1, wx.EXPAND)
        self.panel.SetSizer(self.sizer)
        self.Show(True)





        
        
    
    