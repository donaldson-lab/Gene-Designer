'''
Created on Aug 6, 2010

@author: virushunter2
'''
import wx
from Bio.Seq import Seq
import numpy
import math
import thermodynamic_data as td

class Nussinov():
    def __init__(self, parent, id, sequence):
        self.sequence = str(sequence)
        self.rna_sequence = Seq.transcribe(Seq(self.sequence))
        numpy.set_printoptions(threshold=numpy.nan)
        
    def base_pairing(self, a, b):
        if a == 'G' and b == 'U':
            return 1
        elif a == 'U' and b == 'G':
            return 1
        elif a == 'A' and b == 'U':
            return 1
        elif a == 'U' and b == 'A':
            return 1
        elif a == 'G' and b == 'C':
            return 1
        elif a == 'C' and b == 'G':
            return 1
        else:
            return 0
        
    def hydrogen_bonds(self, a, b):
        if a == 'G' and b == 'U':
            return 1
        elif a == 'U' and b == 'G':
            return 1
        elif a == 'A' and b == 'U':
            return 2
        elif a == 'U' and b == 'A':
            return 2
        elif a == 'G' and b == 'C':
            return 3
        elif a == 'C' and b == 'G':
            return 3
        else:
            return 0
        
    def fill_matrix(self, sequence):
        length = len(sequence)
        w = numpy.zeros((length,length)) #Setup the matrix
        for n in xrange(1,length):
            for j in xrange(n,length):
                i=j-n;
                case1=w[i+1,j-1]+self.hydrogen_bonds(sequence[i],sequence[j]);
                case2=w[i+1,j];
                case3=w[i,j-1];
                if math.fabs(j-i) < 4:
                    w[i,j] = 0
                elif i+3<=j:
                    tmp=[];
                    for k in xrange(i+1,j):
                        tmp.append(w[i,k]+w[k+1,j]);
                    case4=max(tmp);
                    w[i,j]=max(case1,case2,case3,case4);
                else:
                    w[i,j]=max(case1,case2,case3);
        print w
        return w
    
    def fill_matrix1(self, sequence):
        length = len(sequence)
        w = numpy.zeros((length, length))
        v = numpy.zeros((length, length))
        casev1 = numpy.Infinity
        casev2 = numpy.Infinity
        casev3 = numpy.Infinity
        casev4 = numpy.Infinity
        casew1 = numpy.Infinity
        casew2 = numpy.Infinity
        casew3 = numpy.Infinity
        casew4 = numpy.Infinity
        for i in xrange(length):
            for j in xrange(length):
                w[i,j] = numpy.Infinity
                v[i,j] = numpy.Infinity
        for n in xrange(1,length):
            for j in xrange(n, length):
                i = j-n
                try:
                    casev1 = td.Data.loop_energies(td.Data())[0][j-i]
                except IndexError:
                    casev1 = td.Data.loop_energies(td.Data())[0][29] + .615*math.log1p(j-i/30)
                casev2 = v[i+1, j-1] + td.Data.stacking_energies(td.Data(), [sequence[i], sequence[j]], [sequence[i+1], sequence[j-1]])
                tmp = []
                for k1 in xrange(i+1, j):
                    for k2 in xrange(k1, j):
                        try:
                            tmp.append(v[k1,k2] + td.Data.loop_energies(td.Data())[2][k1-i])
                        except IndexError:
                            tmp.append(v[k1, k2] + td.Data.loop_energies(td.Data())[2][29] + .615*math.log1p(j-i/30))
                        casev3 = min(tmp)
                tmp = []
                for k in xrange(i+1, j-1):
                    tmp.append(w[i+1, k] + w[k+1, j-1])
                    casev4 = min(tmp)
                v[i,j] = min(casev1, casev2, casev3, casev4)
        for n in xrange(1, length):
            for j in xrange(n, length):
                i = j- n
                if j - i > 3:
                    casew1 = w[i+1, j]
                    casew2 = w[i, j-1]
                    casew3 = v[i,j]
                    w[i,j] = min(casew1, casew2, casew3)
                else:
                    tmp = []
                    for k in xrange(i+1, j):
                        tmp.append(w[i,k] + w[k+1, j])
                        casew4 = min(tmp)
                        w[i,j] = min(casew1, casew2, casew3, casew4)
        print w
        return w, v
    
    def traceback(self, w, sequence, i, j, pair):
        if i < j:
            print 'i: %s, j: %s' %(i,j)
            if w[i,j] == w[i+1, j]:
                self.traceback(w, sequence, i+1, j, pair)
            elif w[i, j] == w[i, j-1]:
                self.traceback(w, sequence, i, j-1, pair)
            elif w[i, j] == w[i+1, j-1] + self.hydrogen_bonds(sequence[i], sequence[j]):
                pair.append([i,j, str(sequence[i]), str(sequence[j])])
                self.traceback(w, sequence, i+1, j-1, pair)
            else:
                for k in xrange(i+1, j):
                    if w[i, j] == w[i, k] + w[k+1, j]:
                        self.traceback(w, sequence, i, k, pair)
                        self.traceback(w, sequence, k+1, j, pair)
                        break;
        return pair
    
    def traceback1(self, w, v, sequence, i, j, pair):
        if i < j:
            if w[i,j] != numpy.Infinity:
                #print 'i: %s, j: %s' %(i,j)
                if self.base_pairing(sequence[i], sequence[j]) == 0:
                    if w[i,j] == w[i+1, j] and self.base_pairing(sequence[i+1], sequence[j]) != 0:
                        self.traceback1(w, v, sequence, i+1, j, pair)
                    elif w[i, j] == w[i, j-1] and self.base_pairing(sequence[i], sequence[j-1]) != 0:
                        self.traceback1(w, v, sequence, i, j-1, pair)
                    else:
                        #print 'i: %s, j: %s' %(i,j)
                        for k in xrange(i+1, j):
                            if w[i, j] == w[i, k] + w[k+1, j]:
                                self.traceback(w, sequence, i, k, pair)
                                self.traceback(w, sequence, k+1, j, pair)
                                break;
                else:
                    pair.append([i,j, str(sequence[i]), str(sequence[j])])
                    self.traceback1(w, v, sequence, i+1, j-1, pair)
        return pair
    
    def structure(self):
        string = '.'*len(self.rna_sequence)
        pair = self.traceback1(self.fill_matrix1(self.rna_sequence)[0], self.fill_matrix1(self.rna_sequence)[1], self.rna_sequence, 0, len(self.rna_sequence)-1, [])
        #pair= self.traceback(self.fill_matrix(self.rna_sequence),self.rna_sequence,0,len(self.rna_sequence)-1,[])
        print "max # of folding pairs: ",len(pair);
        for x in xrange(0,len(pair)):
            print '%d %d %s==%s' % (pair[x][0]+1,pair[x][1]+1,pair[x][2],pair[x][3]);
            string = string[:pair[x][0]] + '(' + string[pair[x][0]+1:]
        for x in xrange(1, len(pair)+1):
            string = string[:pair[-x][1]] + ')' + string[pair[-x][1]+1:]
        print string
        return string

class RNAPanel(wx.Panel):
    def __init__(self, parent, id, old_rna, old_delta_g, new_rna, new_delta_g):
        wx.Panel.__init__(self, parent)
        self.name = 'RNApanel'
        self.old_text = wx.StaticText(self, wx.ID_ANY, 'Predicted RNA Structure:')
        self.new_text = wx.StaticText(self, wx.ID_ANY, 'New Predicted RNA Structure:')
        self.old_delta_g_text = wx.StaticText(self, wx.ID_ANY, 'Delta G (kcal/mol):')
        self.new_delta_g_text = wx.StaticText(self, wx.ID_ANY, 'Delta G (kcal/mol):')
        self.old_delta_g_disp = wx.TextCtrl(self, size = (100, 20))
        self.new_delta_g_disp = wx.TextCtrl(self, size = (100, 20))
        self.old_display = wx.TextCtrl(self, size = (500, 20))
        self.new_display = wx.TextCtrl(self, size = (500, 20))
        self.old_display.SetValue(str(old_rna))
        self.new_display.SetValue(str(new_rna))
        self.old_delta_g_disp.SetValue(str(old_delta_g))
        self.new_delta_g_disp.SetValue(str(new_delta_g))
        self.old_structure_sizer = wx.BoxSizer(wx.VERTICAL)
        self.new_structure_sizer = wx.BoxSizer(wx.VERTICAL)
        self.old_delta_sizer = wx.BoxSizer(wx.VERTICAL)
        self.new_delta_sizer = wx.BoxSizer(wx.VERTICAL)
        self.old_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.new_sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.sizer = wx.BoxSizer(wx.VERTICAL)
        self.old_structure_sizer.AddMany([self.old_text, (self.old_display, 0, wx.TOP, 5)])
        self.new_structure_sizer.AddMany([self.new_text, (self.new_display, 0, wx.TOP, 5)])
        self.old_delta_sizer.AddMany([self.old_delta_g_text, (self.old_delta_g_disp, 0, wx.TOP, 5)])
        self.new_delta_sizer.AddMany([self.new_delta_g_text, (self.new_delta_g_disp, 0, wx.TOP, 5)])
        self.old_sizer.AddMany([self.old_structure_sizer, (self.old_delta_sizer, 0, wx.LEFT, 10)])
        self.new_sizer.AddMany([self.new_structure_sizer, (self.new_delta_sizer, 0, wx.LEFT, 10)])
        self.sizer.AddMany([self.old_sizer, (self.new_sizer, 0, wx.TOP, 10)])
        self.SetSizerAndFit(self.sizer)