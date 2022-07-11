def shellsort (arr, engine : str = 'CIURA') -> list:
    N = len(arr)

    if engine == 'CIURA':
        ciura = [1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711]
        
        i = 0
        while ciura[i] < N:
            i += 1
        i -= 1    
        
        ciura.reverse()

    
        for h in ciura:
            for i in range(h, N):
                t = arr[i]
                j = i
                while j >= h and t < arr[j - h]: 
                    arr[j] = arr[j-h]
                    arr[j-h] = t
                    j -= h

    else:
        h = 1
        if engine == 'KNUTH':
            x = 3
            while h < N // 3:
                h = 3*h + 1
        elif engine == 'SHELL':
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
            h //= x

    return arr
