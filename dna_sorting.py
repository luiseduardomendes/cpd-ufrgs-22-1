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
    return arr2

num_sets = int(input())

for h in range(num_sets):
    input()
    k = input()
    str_size, num_str = k.split()
    str_size = int(str_size)
    num_str = int(num_str)

    ds = []
    for line in range(num_str):
        ds.append(input())

    unsortness = []
    for set in ds:
        u = 0
        for i, e in enumerate(set):
            for j in set[i:]:
                if (e > j):
                    u += 1
        unsortness.append(u)

    
    a = insertion_sort(unsortness, ds[:])
    
    for j in a:
        print(j)
    if (h + 1) != num_sets:
        print()
    