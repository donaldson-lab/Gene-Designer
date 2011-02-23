import os
import sys
from modeller.automodel import *

def main(alnfile, knowns, sequence):
    alnfile = alnfile
    knowns = knowns
    sequence = sequence
    env = environ()

    env.io.atom_files_directory = './:../atom_files'

    a = automodel(env, alnfile = alnfile, knowns = knowns, sequence = sequence, assess_methods=(assess.DOPE))

    a.starting_model = 1
    a.ending_model = 1

    a.md_level = None
    a.make()

if __name__ == "__main__":
    main(*sys.argv[1:])
