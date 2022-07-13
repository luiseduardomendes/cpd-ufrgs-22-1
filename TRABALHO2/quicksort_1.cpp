#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>

using namespace std;

void quicksort(vector<int> & array);
void quicksort_recursive(vector<int> & array, int beg, int end);
int partition(vector<int> & array, int beg, int end);
int random_partition(vector<int> & array, int beg, int end);
int median_partition(vector<int> & array, int beg, int end);
void exchange(vector<int> & array, int a, int b);
int median(int a, int b, int c);

void quicksort(vector<int> & array){
    quicksort_recursive(array, 0, array.size()-1);
}

void quicksort_recursive(vector<int> & array, int beg, int end) {
    int part;
    
    if (beg < end) {
        part = median_partition(array, beg, end);
        quicksort_recursive(array, beg, part-1);
        quicksort_recursive(array, part+1, end);
    }
}

void exchange(vector<int> & array, int a, int b) {
    int temp;
    temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

int partition(vector<int> & array, int beg, int end) {
    int pivot = array[beg];
    int part = beg;
    
    for (int j = beg+1; j <= end; j++) {
        if (array[j] <= pivot){
            part++;
            exchange(array, part, j);
        }
    }
    exchange(array, part, beg);
    return part;
}

int median(int a, int b, int c){
    if (a < b){
        if (a < c)
            if (b < c)
                return 2;
            else
                return 3;
        else    
            return 1;
    }
    else{
        if (a < c)
            return 1;
        else
            if (b < c)
                return 3;
            else
                return 2;
    }

}

int random_partition(vector<int> & array, int beg, int end) {
    int pivot;
    int part = beg;

    int random_value = beg + (rand() % (end - beg));
    exchange(array, beg, random_value);
    pivot = array[beg];
    
    for (int j = beg+1; j <= end; j++) {
        if (array[j] <= pivot){
            part++;
            exchange(array, part, j);
        }
    }
    exchange(array, part, beg);
    return part;
}

int median_partition(vector<int> & array, int beg, int end) {
    int pivot;
    int part = beg;

    int median_value = median(array[beg], array[end], array[(int)(beg+end)/2]);
    int median_index;

    switch (median_value){
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
    exchange(array, beg, median_index);
    pivot = array[beg];
    
    for (int j = beg+1; j <= end; j++) {
        if (array[j] <= pivot){
            part++;
            exchange(array, part, j);
        }
    }
    exchange(array, part, beg);
    return part;
}

bool isSorted(vector<int> array){
    for (int i = 0; i < array.size(); i ++)
        for (int j = i; j < array.size(); j ++)
            if (array[i] > array[j])
                return false;
    return true;
}

int main(){
    vector<int> array;
    int max = 100000, loop = 0, max_loops = 1;
    int randmax = 100;
    bool is_sorted = 1;
    srand(time(0));
    clock_t end, begin;

    begin = clock();
    do{
        array.clear();

        for (int i = 0; i < max; i++){
            array.push_back(rand() % randmax);
        }

        quicksort(array);
        
        loop++;
        is_sorted = isSorted(array);

    }while(is_sorted && loop < max_loops);

    end = clock();
    
    if(is_sorted)
    {
        printf("FOI PORRA!!!!!!!!!!!\n");
    }
    else{
        printf("fomo de beise nao tankamo foi nothing\n");
        printf("%d\n", loop);
    }

    printf("exec time: %lf\n", (double)(end-begin)/CLOCKS_PER_SEC);
    return 0;
}