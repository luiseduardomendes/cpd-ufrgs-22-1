def insertion_sort(sort_array : list):
    for i in range(len(sort_array)):
        key = sort_array[i]
        j = i-1
        while j >= 0 and sort_array[j] > key:
            sort_array[j+1] = sort_array[j]
            j = j-1
        sort_array[j+1] = key
    return sort_array

def shell_sort(sort_array : list, seq : str = 'SHELL'):
    N = len(sort_array)
    
    if seq == 'KNUTH':
        x = 3
        while h < N // 3:
            h = 3*h + 1
    elif seq == 'CIURA':
        ciura = (1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711)
        for i in ciura:
            pass
    else:
        x = 2
        while h < N // 2:
            h = 2*h

    while h >= 1:
        for i in range(h, N):
            t = sort_array[i]
            j = i
            while j >= h and t < sort_array[j - h]: 
                sort_array[j] = sort_array[j-h]
                sort_array[j-h] = t
                j -= h
        h //= x

from random import randint

size = 10
max = 500
arr = [randint(0, max) for i in range(size)]

print(arr)

shell_sort(arr)

print(arr)