import os
import sys
import re

def main(pdb_file, aln_file):
    aln = str(aln_file)
    pdb = str(pdb_file)
    aminoacids = {'ALA': 'A', 'ARG': 'R', 'ASN': 'N',
                         'ASP': 'D', 'CYS': 'C', 'GLU': 'E',
                         'GLN': 'Q', 'GLY': 'G', 'HIS': 'H',
                         'ILE': 'I', 'LEU': 'L', 'LYS': 'K',
                         'MET': 'M', 'PHE': 'F', 'PRO': 'P',
                         'SER': 'S', 'THR': 'T', 'TRP': 'W',
                         'TYR': 'Y', 'VAL': 'V'}

    with open(aln) as aln:
        name1 = aln.readline()
        info1 = aln.readline()
        sequence = aln.readline()
        name2 = aln.readline()
        info2 = aln.readline()
        sequence2 = aln.readline()
    
    with open(pdb) as pdb:
        prev_res_num = -100
        pdb_seq = ''
        residue_list = []
        for line in pdb:
            if line.startswith('ATOM'):
                res_name = line[17:20].replace(' ', '')
                res_num = line[22:26].replace(' ', '')
                if (res_num != prev_res_num):
                    pdb_seq = pdb_seq + aminoacids[res_name]
                    residue_list.append(res_num)
                prev_res_num = res_num
            elif line.startswith('HETATM'):
                res_num = line[22:26].replace(' ', '')
                if (res_num != prev_res_num):
                    pdb_seq = pdb_seq + '-'
                    residue_list.append(res_num)
                prev_res_num = res_num
    index = 0;
    start = re.search(sequence[:5], pdb_seq).start()
    for char in sequence:
        print sequence
        print char
        if char == '-':
            pdb_seq = pdb_seq[:index+start] +'-' +pdb_seq[index+start:]
        elif char == '*':
            pdb_seq = pdb_seq[:index] + '*' + '\n'
        index += 1
        print pdb_seq
    pdb_seq = pdb_seq[start:] + sequence[-start:]
    
    tmp = open('tmp.txt', 'w')
    tmp.write(name1)
    tmp.write(info1)
    tmp.write(pdb_seq)
    tmp.write(name2)
    tmp.write(info2)
    tmp.write(sequence2)
    tmp.close()
    os.remove(aln_file)
    os.rename('tmp.txt', aln_file)
            
if __name__ == "__main__":
    main(*sys.argv[1:])