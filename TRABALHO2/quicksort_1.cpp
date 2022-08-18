#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <string.h>

using namespace std;

enum enum_part{LOMUTO, HOARE};
enum enum_swap{RAND, MED3};

int g_swaps = 0;
int g_recurs = 0;

void quicksort(vector<int>&array, int t_part, int t_swap);
void quicksort_recursive(vector<int>&array, int beg, int end, int t_part, int t_swap);
int partition(vector<int>&array, int beg, int end, int t_part, int t_swap);
int median(int a, int b, int c);
int median3(vector<int>&array, int beg, int end);
bool isSorted(vector<int>&array, int size);
vector<int> splitLine(const string& text, int array[], int size, char sep);

void swap_2(int* a, int* b){
    int buffer = *a;
    *a = *b;
    *b = buffer;
}

void remove_line_break(string &str){
    if (str[str.size()-1] == '\n')
        str.erase(str.end()-1);
}

void cout_array(vector<int> array){
    for(int i = 0; i < array.size(); i++)
        cout << array[i] << " ";
    cout << endl;
}

void quicksort(vector<int>&array, int t_part, int t_swap)
{
    quicksort_recursive(array, 0, array.size()-1, t_part, t_swap);
}

void quicksort_recursive(vector<int> &array, int beg, int end, int t_part, int t_swap)
{
    g_recurs ++;
    
    int part;

    if (beg < end)
    {
        part = partition(array, beg, end, t_part, t_swap);
        quicksort_recursive(array, beg, part-1, t_part, t_swap);
        quicksort_recursive(array, part+1, end, t_part, t_swap);
    }
}

int partition(vector<int>&array, int beg, int end, int t_part, int t_swap)
{
    int part = beg;

    switch(t_swap){
    case MED3:
        swap(array[beg], array[median3(array, beg, end)]);
        break;
    case RAND:
        swap(array[beg], array[beg + (rand() % (end - beg))]);
        break;
    }

    int pivot = array[beg];

    switch (t_part)
    {
    case HOARE:{
        int cp = array[beg];
        bool esq = true;
        while(beg < end)
        {
            if (esq)
            {
                if (cp >= array[end])
                {
                    g_swaps++;
                    array[beg] = array[end];
                    beg ++;
                    esq = false;
                }
                else
                {
                    end --;
                }
            }
            else
            {
                if (cp < array[beg])
                {
                    g_swaps++;
                    array[end] = array[beg];
                    end --;
                    esq = true;
                }
                else
                {
                    beg ++;
                }
            }
        }
        array[beg] = cp;
        return beg;
        break;
        }
    case LOMUTO:
        for (int j = beg+1; j <= end; j++)
        {
            if (array[j] <= pivot)
            {
                part++;
                g_swaps++;
                swap(array[part], array[j]);
            }
        }
        break;
    }
    swap(array[part], array[beg]);
    return part;
}

int median(int a, int b, int c)
{
    if (((a < b) && (a > c)) || ((a > b) && (a < c))) 
        return 1;
    else if (((b < a) && (b > c)) || ((b > a) && (b < c))) 
        return 2;
    else
        return 3;

}

int median3(vector<int>&array, int beg, int end)
{
    int median_value = median(array[beg], array[end], array[(int)(beg+end)/2]);
    int median_index;
    
    switch (median_value)
    {
    case 1:
        median_index = beg;
        break;
    case 2:
        median_index = (int)((beg+end)/2);
        break;
    case 3:
        median_index = end;
        break;
    }
    return median_index;
}

bool isSorted(vector<int>&array, int size)
{
    for (int i = 0; i < size; i ++)
        for (int j = i; j < size; j ++)
            if (array[i] > array[j])
                return false;
    return true;
}

vector<int> splitLine(string &text, int *size, char sep)
{
    vector<string> tokens;
    vector<int> array;
    size_t start = 0, end = 0;

    while (text[text.size()-1] < '0' || text[text.size()-1] > '9')
        text.erase(text.end()-1);

    while ((end = text.find(sep, start)) != string::npos){
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }

    tokens.push_back(text.substr(start));

    *size = atoi(tokens[0].c_str());
    for (int i = 1; i < tokens.size(); i ++)
        array.push_back(atoi(tokens[i].c_str()));

    return array;
}

void create_filename(string &filename, string partitioning, string swapping){
    
    filename.clear();
    filename.append("stats-");
    filename.append(partitioning);
    filename.append("-");
    filename.append(swapping);
    filename.append(".txt");
}

int main(int argc, char** argv)
{
    vector<int> array, temp_arr;
    vector<string> partitioning = {
        "lomuto",
        "hoare"
    };
    vector<string> swapping = {
        "aleatorio",
        "mediana"
    };

    clock_t end, begin;
    int i, j;
    int size;
    string line, filename;
    fstream file_input, file_out;
 
    file_input.open(argv[1], ios::in);

    for(i = LOMUTO; i <= HOARE; i++) {
        for(j = RAND; j <= MED3; j++) {
            create_filename(filename, partitioning[i], swapping[j]);
            file_out.open(filename, ios::out);
            while (!file_input.eof()){
                getline(file_input, line);
                array.clear();
                array = splitLine(line, &size, ' ');
                temp_arr.assign(array.size(), 0);
                
                copy(array.begin(), array.end(), temp_arr.begin());
                
                g_recurs = 0;
                g_swaps = 0;

                begin = clock();
                quicksort(temp_arr, i, j);
                end = clock();
                
                file_out << "TAMANHO ENTRADA " <<  temp_arr.size() << endl;
                file_out << "SWAPS " <<  g_swaps << endl;
                file_out << "RECURSOES " <<  g_recurs << endl;
                file_out << "TEMPO " <<  (double)(end-begin)/CLOCKS_PER_SEC << endl;
                
            }
            file_out.close();
            file_input.seekg(0);  
        }
    }
    
    file_input.close();
    return 0;
}
