'''
Created on Aug 16, 2010

@author: virushunter2
'''

class CT_to_DB():
    
    def __init__self(self, filename = []):
        self.filename = filename
    
    def read_file(self, filename):
        first = []
        second = []
        with open(filename) as file:
            delta_g = file.readline().split('\t')[1].strip(' ')
            for line in file:
                line = line.split('\t')
                first.append(line[0])
                second.append(line[4])
        return first, second, delta_g
    
    def dot_bracket(self, first, second):
        paired = []
        string = '.'*len(first)
        for number in first:
            number = int(number) -1
            if int(second[number]) -1 != -1:
                paired.append(number)
                if int(second[number]) -1 not in paired:
                    string = string[:number] + '(' + string[number+1:]
                    string = string[:int(second[number])-1] + ')' +string[int(second[number]):]
        return string
            
                