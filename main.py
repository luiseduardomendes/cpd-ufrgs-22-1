from fileinput import filename
from time import time
from lib.shell_sort import shellsort, shellsort_file_write

def read_input(data : str) -> list :
    a = data.split()
    a = a[1:]
    a = [int(i) for i in a]
    return a;

files = (
    'data_input/entrada1.txt',
    'data_input/entrada2.txt',
    'data_input/entrada3.txt'
)

sequences = (
    'SHELL',
    'KNUTH',
    'CIURA'
)

'''
filename = files[3]
with open(filename) as f:
    for line in f:
        array = read_input(line)
        for sequence in sequences:
            sorted_array = shellsort_file_write(array[:], sequence, 'saida3.txt')
    f.close()
'''

filename = files[1]
output_file = 'saida2.txt'

f_out = open(output_file, 'w')
with open(filename) as f:
    for line in f:
        array = read_input(line)
        for sequence in sequences:
            __begin__ = time()
            sorted_array = shellsort(array[:], sequence)
            __end__ = time()
            execution_time = __end__ - __begin__
            f_out.write(f'{sequence},{len(array)},{execution_time}\n')

    f.close()

