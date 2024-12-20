from sys import argv
# Куда относить Y?
VOWELS = 'аеёиоуыэюяaeiouy'
CONSONANTS = 'йцкнгшщзхфвпрлджчсмтбqwrtpsdfghjklzxcvbnm'
HEADER = \
'''/**
  * Table of Unicode codepoints of English and Russian {}
  * This file is generated by Task_2/generate_table.py.
  */'''


vowel_codepoints = []
with open(argv[1], 'w') as f:
    print(HEADER.format('vowels'), file=f)
    for v in VOWELS:
        print(f'case 0x{ord(v):04x}: // {v}', file=f)
        print(f'case 0x{ord(v.upper()):04x}: // {v.upper()}', file=f)

with open(argv[2], 'w') as f:
    print(HEADER.format('consonants'), file=f)
    for v in CONSONANTS:
        print(f'case 0x{ord(v):04x}: // {v}', file=f)
        print(f'case 0x{ord(v.upper()):04x}: // {v.upper()}', file=f)
