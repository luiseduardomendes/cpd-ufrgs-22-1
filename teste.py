def shellsort (arr : list, engine : str = 'KNUTH', filename: str = 'saida1.txt') -> list:
    N = len(arr)

    file = open(filename, 'a')


    if engine == 'CIURA':
        ciura = [1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711]

        for i in arr[:-1]:
            file.write(f'{i}, ')
        file.write(f'{arr[-1]} SEQ=CIURA\n')
        
        i = 0
        while ciura[i] < N:
            i += 1

        ciura = ciura[:i]
        ciura.reverse()

        for h in ciura:
            for i in range(h, N):
                t = arr[i]
                j = i
                while j >= h and t < arr[j - h]: 
                    arr[j] = arr[j-h]
                    arr[j-h] = t
                    j -= h
            for i in arr[:-1]:
                file.write(f'{i}, ')
            file.write(f'{arr[-1]} INCR={h}\n')
            
    else:
        h = 1
        if engine == 'KNUTH':
            for i in arr[:-1]:
                file.write(f'{i}, ')
            file.write(f'{arr[-1]} SEQ=KNUTH\n')
            x = 3
            while h < N // 3:
                h = 3*h + 1
        elif engine == 'SHELL':
            for i in arr[:-1]:
                file.write(f'{i}, ')
            file.write(f'{arr[-1]} SEQ=SHELL\n')
            x = 2
            while h < N // 2:
                h = 2*h

        while h >= 1:
            for i in range(h, N):
                t = arr[i]
                j = i
                while j >= h and t < arr[j - h]: 
                    arr[j] = arr[j-h]
                    arr[j-h] = t
                    j -= h
            for i in arr[:-1]:
                file.write(f'{i}, ')
            file.write(f'{arr[-1]} INCR={h}\n')
            h //= x

    file.close()

    return arr

filename ='entrada3.txt'
outname = 'saida3.txt'

with open(outname, 'w') as f:
    f.close()

keys = ('SHELL', 'KNUTH', 'CIURA')

with open(filename) as f:
    for line in f:
        arr = line
        if arr.endswith('\n'):
            arr = arr[:-1]
        arr = arr.split(sep=' ')

        for i, e in enumerate(arr):
            arr[i] = int(e)

        arr.pop(0)
        for key in keys:
            a = shellsort(arr[:], key, outname)
            #print(key, a)





        