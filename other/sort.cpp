#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include<time.h>
#include <fstream>

using namespace std;

template<typename Comparable>
vector<int> shellsort (vector<int> & array, string engine);
vector<vector<int>> read_file(string filename);

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

        for (int k = 0; k < ciura.size(); k ++){
            h = ciura[k];
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

// split function was get from internet
vector<int> split(const string& text, char sep){
    vector<string> tokens;
    vector<int> array;
    size_t start = 0, end = 0;

    while ((end = text.find(sep, start)) != string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }

    tokens.push_back(text.substr(start));
    
    for (int i = 0; i < tokens.size(); i ++){
        array.push_back(atoi(tokens[i].c_str()));
    }
    
    return array;
}

vector<vector<int>> read_file(string filename){
    vector<vector<int>> buffer;
    fstream file;
    file.open(filename, ios::in);

    if(file.is_open()){
        string tp;
        while(getline(file, tp)){
            buffer.push_back(split(tp, ' '));
        }
    }
    file.close();
    return buffer;

}

int main(){
    time_t __begin, __end;
    vector<vector<int>> mult_dim_arr;
    vector<string> sequences = {"SHELL","KNUTH","CIURA"};    

    for (int j = 0; j < sequences.size(); j ++){
        mult_dim_arr = read_file("data_input/entrada2.txt");
        for (int i = 0 ; i < mult_dim_arr.size(); i ++){
            
            __begin = clock();
            int n = mult_dim_arr[i][0];
            mult_dim_arr[i].erase(mult_dim_arr[i].begin());
            shellsort(mult_dim_arr[i], sequences[j]);
            __end = clock();
            printf("%s, %d: %.8lfs\n", sequences[j].c_str(), n, (double)(__end - __begin)/CLOCKS_PER_SEC);
        }
    }
    return 0;
}