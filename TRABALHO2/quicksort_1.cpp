#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>

using namespace std;

enum cod{LOMUTO, HOARE};
enum part{RAND, MED3};

void quicksort(vector<int> & array, int t_part, int t_cod);
void quicksort_recursive(vector<int> & array, int beg, int end, int t_part, int t_cod);
int partition(vector<int> & array, int beg, int end, int t_part, int t_cod);
int random_partition(vector<int> & array, int beg, int end);
int median_partition(vector<int> & array, int beg, int end);
void exchange(vector<int> & array, int a, int b);
int median(int a, int b, int c);
int median3(vector<int> array, int beg, int end);
vector<int> splitLine(const string& text, char sep);

void quicksort(vector<int> & array, int t_part, int t_cod)
{
    quicksort_recursive(array, 0, array.size()-1, t_part, t_cod);
}

void quicksort_recursive(vector<int> & array, int beg, int end, int t_part, int t_cod)
{
    int part;

    if (beg < end)
    {
        part = partition(array, beg, end, t_part, t_cod);
        quicksort_recursive(array, beg, part-1, t_part, t_cod);
        quicksort_recursive(array, part+1, end, t_part, t_cod);
    }
}

int partition(vector<int> & array, int beg, int end, int t_part, int t_cod)
{
    int pivot = array[beg];
    int part = beg;

    switch(t_part){
    case MED3:
        swap(array[beg], array[median3(array, beg, end)]);
    case RAND:
        swap(array[beg], array[beg + (rand() % (end - beg))]);
    }

    switch (t_cod)
    {
    case HOARE:
        int cp = array[beg];
        bool esq = true;
        while(beg < end)
        {
            if (esq)
            {
                if (cp >= array[end])
                {
                    array[beg] = array[end];
                    end ++;
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
    case LOMUTO:
        for (int j = beg+1; j <= end; j++)
        {
            if (array[j] <= pivot)
            {
                part++;
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
    if (a < b)
    {
        if (a < c)
            if (b < c)
                return 2;
            else
                return 3;
        else
            return 1;
    }
    else
    {
        if (a < c)
            return 1;
        else if (b < c)
            return 3;
        else
            return 2;
    }

}

int median3(vector<int> array, int beg, int end)
{
    int median_value = median(array[beg], array[end], array[(int)(beg+end)/2]);
    int median_index;

    switch (median_value)
    {
    case 1:
        median_index = beg;
        break;
    case 2:
        median_index = (int)(beg+end)/2;
        break;
    case 3:
        median_index = end;
        break;
    }
    return median_index;
}

bool isSorted(vector<int> array)
{
    for (int i = 0; i < array.size(); i ++)
        for (int j = i; j < array.size(); j ++)
            if (array[i] > array[j])
                return false;
    return true;
}

vector<int> splitLine(const string& text, char sep)
{
    vector<string> tokens;
    vector<int> array;
    size_t start = 0, end = 0;

    while ((end = text.find(sep, start)) != string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }

    tokens.push_back(text.substr(start));

    for (int i = 0; i < tokens.size(); i ++)
    {
        array.push_back(atoi(tokens[i].c_str()));
    }
    array.erase(0);

    return array;
}

int main(int argc, char** argv)
{
    vector<int> array;
    int max = 100000, loop = 0, max_loops = 1;
    int randmax = 100;
    bool is_sorted = 1;
    srand(time(0));
    clock_t end, begin;
    int i, j;
    fstream file_input;
    file_input.open(argv[1], ios::in);

    for (int line_index = 0; line_index; line_index ++){
        string line = file_input.getline();
        for(i = LOMUTO; i <= HOARE; i++)
        {
            for(j = RAND; j <= MED3; j++)
            {
                array = splitLine(line, ' ');
                do
                {
                    array.clear();
    
                    for (int i = 0; i < max; i++)
                    {
                        array[i] = (rand() % randmax);
                    }
    
                    quicksort(array, i, j);
    
                    loop++;
                    is_sorted = isSorted(array);
                }
                while(is_sorted && loop < max_loops);
    
                if(!is_sorted)
                {
                    printf("FOMO DE BASE!\n");
                    printf("%d\n", loop);
                }
                else
                    printf("FOI PORRA!\n");
            }
        }
    }
    //printf("exec time: %lf\n", (double)(end-begin)/CLOCKS_PER_SEC);
    return 0;
}
