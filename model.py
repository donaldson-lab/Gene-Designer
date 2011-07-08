import os #@UnusedImport
import sys
import modeller.automodel #@UnresolvedImport
from modeller.automodel import *

def main(alnfile, knowns, sequence):
    alnfile = alnfile
    knowns = knowns
    sequence = sequence
    env = environ() #@UndefinedVariable
    env.io.atom_files_directory = './:../atom_files'
    a = modeller.automodel(env, alnfile = alnfile, knowns = knowns, sequence = sequence, assess_methods=(assess.DOPE)) #@UndefinedVariable
    a.starting_model, a.ending_model = 1, 1
    a.md_level = None
    a.make()

if __name__ == "__main__":
    main(*sys.argv[1:])
