#include <iostream>
#include <vector>

using namespace std;

template<typename Comparable>

vector<Comparable> shellsort (vector<Comparable> & array){
    int x, N;

    N = array.size()
    
    x = 2;
    while h < int(N / 2)
        h = 2*h;
    
    while (h >= 1){
        for (i = h; i < N; i ++){
            t = array[i];
            j = i;
            while (j >= h && t < array[j - h]){ 
                array[j] = array[j-h];
                array[j-h] = t;
                j -= h;
            }
        }
        h = int(h / x);
    }
}