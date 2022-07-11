from pprint import pprint

def get_unsortness(array):
    unsortness = 0
    for i, e in enumerate(array):
        for j in array[i:]:
            if (e > j):
                unsortness += 1
    return unsortness

def _read_input():
    
    a = input()
    input()
    a = input()
    M, N = a.split()
    M = int(M)
    N = int(N)

    arr = []
    for line in range(N):
        arr.append(input())
    
    return arr


def insertion_sort(sort_array, arr2):
    for i in range(len(sort_array)):
        key = sort_array[i]
        temp = arr2[i]
        j = i-1
        while j >= 0 and sort_array[j] > key:
            arr2[j+1] = arr2[j]
            sort_array[j+1] = sort_array[j]
            j = j-1
        arr2[j+1] = temp
        sort_array[j+1] = key
    return sort_array

def sort_data_sets(ds):
    unsortness = []
    for set in ds:
        unsortness.append(get_unsortness(set))

    insertion_sort(unsortness, ds)
    return ds

ds = _read_input()
a = sort_data_sets(ds[:])
print()
for i in a:
    print(i)