'''
Created on Aug 9, 2010

@author: virushunter2
'''
import numpy
class Data():
    def __init__(self):
        self = self
    
    def loop_energies(self):
        self.internal = [0, 4.10, 5,10, 4.90, 5.30, 5.70, 5.90, 6.00, 6.10, 6.30, 6.40, 6.40, 6.50, 6.60, 6.70, 6.80, 6.80, 6.90, 7.0, 7.10, 7.10, 7.10, 7.20, 7.20, 7.30, 7.30, 7.40, 7.40, 7.40]
        self.bulge = [3.90, 3.10, 3.50, 4.20, 4.80, 5.00, 5.20, 5.30, 5.40, 5.50, 5.70, 5.70, 5.80, 5.90, 6.00, 6.10, 6.10, 6.20, 6.20, 6.30, 6.30, 6.40, 6.40, 6.50, 6.50, 6.50, 6.60, 6.70, 6.70, 6.70]
        self.hairpin = [0, 0, 4.10, 4.90, 4.40, 4.70, 5.00, 5.10, 5.20, 5.30, 5.40, 5.50, 5.60, 5.70, 5.80, 5.80, 5.90, 5.90, 6.00, 6.10, 6.10, 6.20, 6.20, 6.30, 6.30, 6.30, 6.40, 6.40, 6.50, 6.50]
        return self.hairpin, self.internal, self.bulge
        
    def stacking_energies(self, pair1, pair2):
        if pair1[0] == 'A' and pair1[1] == 'U' and pair2[0] == 'A' and pair2[1] == 'U':
            return -0.90
        elif pair1[0] == 'A' and pair1[1] == 'U' and pair2[0] == 'U' and pair2[1] == 'A':
            return -0.90
        elif pair1[0] == 'A' and pair1[1] == 'U' and pair2[0] == 'G' and pair2[1] == 'C':
            return -2.10
        elif pair1[0] == 'A' and pair1[1] == 'U' and pair2[0] == 'G' and pair2[1] == 'U':
            return -1.00
        elif pair1[0] == 'A' and pair1[1] == 'U' and pair2[0] == 'C' and pair2[1] == 'G':
            return -1.70
        elif pair1[0] == 'A' and pair1[1] == 'U' and pair2[0] == 'U' and pair2[1] == 'G':
            return -.50
        
        elif pair1[0] == 'U' and pair1[1] =='A' and pair2[0] == 'A' and pair2[1] == 'U':
            return -.90
        elif pair1[0] == 'U' and pair1[1] == 'A' and pair2[0] == 'U' and pair2[1] == 'A':
            return -1.10
        elif pair1[0] == 'U' and pair1[1] == 'A' and pair2[0] == 'G' and pair2[1] == 'C':
            return -2.30
        elif pair1[0] == 'U' and pair1[1] == 'A' and pair2[0] == 'G' and pair2[1] == 'U':
            return -1.10
        elif pair1[0] == 'U' and pair1[1] == 'A' and pair2[0] == 'C' and pair2[1] == 'G':
            return -1.80
        elif pair1[0] == 'U' and pair1[1] == 'A' and pair2[0] == 'U' and pair2[1] == 'G':
            return -.80
        
        elif pair1[0] == 'G' and pair1[1] == 'C' and pair2[0] == 'A' and pair2[1] == 'U':
            return -2.10
        elif pair1[0] == 'G' and pair1[1] == 'C' and pair2[0] == 'U' and pair2[1] == 'A':
            return -2.30
        elif pair1[0] == 'G' and pair1[1] == 'C' and pair2[0] == 'G' and pair2[1] == 'C':
            return -3.40
        elif pair1[0] == 'G' and pair1[1] == 'C' and pair2[0] == 'G' and pair2[1] == 'U':
            return -2.10
        elif pair1[0] == 'G' and pair1[1] == 'C' and pair2[0] == 'C' and pair2[1] == 'G':
            return -2.90
        elif pair1[0] == 'G' and pair1[1] == 'C' and pair2[0] == 'U' and pair2[1] == 'G':
            return -1.40
        
        elif pair1[0] == 'C' and pair1[1] == 'G' and pair2[0] == 'A' and pair2[1] == 'U':
            return -1.70 
        elif pair1[0] == 'C' and pair1[1] == 'G' and pair2[0] == 'U' and pair2[1] == 'A':
            return -1.80
        elif pair1[0] == 'C' and pair1[1] == 'G' and pair2[0] == 'G' and pair2[1] == 'C':
            return -2.90
        elif pair1[0] == 'C' and pair1[1] == 'G' and pair2[0] == 'G' and pair2[1] == 'U':
            return -1.90
        elif pair1[0] == 'C' and pair1[1] == 'G' and pair2[0] == 'C' and pair2[1] == 'G':
            return -2.00
        elif pair1[0] == 'C' and pair1[1] == 'G' and pair2[0] == 'U' and pair2[1] == 'G':
            return -1.20
        
        elif pair1[0] == 'G' and pair1[1] == 'U' and pair2[0] == 'A' and pair2[1] == 'U':
            return -1.00
        elif pair1[0] == 'G' and pair1[1] == 'U' and pair2[0] == 'U' and pair2[1] == 'A':
            return -1.10
        elif pair1[0] == 'G' and pair1[1] == 'U' and pair2[0] == 'G' and pair2[1] == 'C':
            return -2.10
        elif pair1[0] == 'G' and pair1[1] == 'U' and pair2[0] == 'G' and pair2[1] == 'U':
            return -1.50
        elif pair1[0] == 'G' and pair1[1] == 'U' and pair2[0] == 'C' and pair2[1] == 'G':
            return -1.90
        elif pair1[0] == 'G' and pair1[1] == 'U' and pair2[0] == 'U' and pair2[1] == 'G':
            return -.40
        
        elif pair1[0] == 'U' and pair1[1] == 'G' and pair2[0] == 'A' and pair2[1] == 'U':
            return -.50
        elif pair1[0] == 'U' and pair1[1] == 'G' and pair2[0] == 'U' and pair2[1] == 'A':
            return -0.80
        elif pair1[0] == 'U' and pair1[1] == 'G' and pair2[0] == 'G' and pair2[1] == 'C':
            return -1.40
        elif pair1[0] == 'U' and pair1[1] == 'G' and pair2[0] == 'G' and pair2[1] == 'U':
            return -.20
        elif pair1[0] == 'U' and pair1[1] == 'G' and pair2[0] == 'C' and pair2[1] == 'G':
            return -1.20
        elif pair1[0] == 'U' and pair1[1] == 'G' and pair2[0] == 'U' and pair2[1] == 'G':
            return -.40
        else:
            return numpy.Infinity