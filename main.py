from time import time
from traceback import print_tb
from lib.shell_sort import shellsort, shellsort_file_write
import numpy as np

def read_input(data : str) -> list :
    a = data.split()
    a = a[1:]
    a = [int(i) for i in a]
    return a

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

filename = files[0]


open('saida1.txt', 'w').close()
with open(filename) as f:
    for line in f:
        array = read_input(line)
        for sequence in sequences:
            sorted_array = shellsort_file_write(array[:], sequence, 'saida1.txt')
    f.close()


filename = files[1]
output_file = 'saida2.txt'

f_out = open(output_file, 'w')
with open(filename) as f:
    for line in f:
        array = read_input(line)
        for sequence in sequences:
            begin = time()
            sorted_array = shellsort(np.array(array[:]), sequence)
            end = time()
            execution_time = end - begin
            f_out.write(f'{sequence},{len(array)},{execution_time}\n')
    f.close() 