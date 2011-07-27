"""
This is a setup.py script generated by py2applet

Usage:
    python setup.py py2app
"""
from setuptools import setup

APP = ['genedesign.py']
DATA_FILES = ['type2.103', 'add_linkers.html', 'codon_ref.html', 'comm_ref.html', 'enz_ref.html', 'mutation_display.html', 'mutations.html', 'optimize_options.html', 'restrict.html', 'specific.html', 'codon_usage.html', 'help.html', 'linkers.html', \
              'load_template.html', 'menu.html', 'new_template.html', 'optimization.html', 'vector_hit.html', 'vectors.html', 'aa_mutation.png', 'add_linkers.png', 'codon_ref.png', 'codon_usage.png', 'comm_ref.png', 'enz_ref.png', 'linkers.png', \
              'load_template.png', 'menu_image.png', 'mutation.png', 'mutation_display.png', 'new_template.png', 'options.png', 'restriction.png', 'sequence_boxes.png', 'specific.png', 'table_thumb.png', 'vector.png', 'vector_hit.png', 'KnotSeeker.py', \
              'guugle/guugle', 'ViennaRNA-1.8.4/Progs/RNAeval', 'pknotsRG-1.3/src/pknotsRG']
OPTIONS = {'argv_emulation': True, 'iconfile':'dna.icns'}

setup(
    app=APP,
    data_files=DATA_FILES,
    options={'py2app': OPTIONS},
    setup_requires=['py2app'],
)
