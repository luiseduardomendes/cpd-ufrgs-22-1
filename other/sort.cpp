#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include<time.h>

using namespace std;

template<typename Comparable>

vector<int> shellsort (vector<int> & array, string engine){
    int x, N, h, t, i, j;

    N = array.size();
    if (!engine.compare("CIURA")) {
        vector<int> _ciura = {1,4,10,23,57,132,301,701,1577,3548,7983,17961,40412,90927,204585,460316,1035711};
        vector<int> ciura;
            
        i = 0;
        while (_ciura[i] < N){
            i += 1;
            if (_ciura[i] < N)
                ciura.push_back(_ciura[i]);
        }
            
        reverse(ciura.begin(), ciura.end());

        for (h = 0; h < ciura.size(); h ++){
            for (i = h; i < N; i ++){
                t = array[i];
                j = i;
                while (j >= h && t < array[j - h]){
                    array[j] = array[j-h];
                    array[j-h] = t;
                    j -= h;
                }
            }
        }
        
    }
    else{
        h = 1;
        if (!engine.compare("SHELL")){    
            x = 2;
            while (h < (int)(N / 2))
                h = 2*h;
        }
        else if (!engine.compare("KNUTH")){    
            x = 2;
            while (h < int(N / 2))
                h = 2*h;
        }
        
        while (h >= 1){
            for (int i = h; i < N; i ++){
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
    return array;
}

int main(){
    vector<int> array;
    int max = 100;

    srand(time(0));

    for (int i = 0; i < max; i ++){
        array.push_back(rand() % 10);
    }

    for (int i = 0; i < max; i ++){
        printf("%d ", array[i]);
    }

    //shellsort(array, string("KNUTH"));

    for (int i = 0; i < max; i ++){
        printf("%d ", array[i]);
    }

    return 0;
}