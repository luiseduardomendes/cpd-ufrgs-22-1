#include <iostream>
#include <iomanip>
#include <ios>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <stdint.h>

using namespace std;

class Data{
private:
public:
    int data;
    Data(int i){
        data = i;
    }
    Data(){
    }
};

class Node{
public:
    int key;
    string tag;
    Data data;
    Node(){
        key = -1;
        tag = "";
    }
    Node(int key, string tag, Data data){
        this->key = key;
        this->data = data;
        this->tag = tag;
    }
    void operator<< (ofstream &file){
        file << '|' << 
            setw(10) << setfill('.') << right << this->key << '|' << 
            setw(10) << setfill('.') << right << this->data.data << '|' << 
            setw(30) << setfill('.') << right << this->tag << '|' << endl;
    }
};

class HashTable{
private:
    vector<vector<Node>> table;
    int size;
    int hash(string tag){
        int tagSize = tag.size();
        int a = (int)*(tag.begin());
        int b = (int)*(tag.end()-1);
        int c = (int)*(tag.end()-tagSize/2);
        int d = (int)*(tag.begin()+tagSize/4);
        int e = (int)*(tag.begin()+3*tagSize/4);
        int f = (a*a + b*e + a*e + c*c + e*c + a*c);

        return f % this->size;
    }
public:
    HashTable(int size){
        this->size = size;
        for (int i = 0; i < this->size; i ++){
            vector<Node> v;
            v.clear();
            table.push_back(v);
        }
    }

    void insert(string tag, Data data){
        int key = hash(tag);
        table[key].push_back(Node(key, tag, data));
    }

    void remove(string tag){
        int key = hash(tag);
        vector<Node> list = table[key];
        for (vector<Node>::iterator it = list.begin(); it != list.end(); it ++){
            if (it->tag == tag){
                list.erase(it);
            }
        }
    }

    Node search(string tag){
        int key = hash(tag);
        vector<Node> list = table[key];
        for (vector<Node>::iterator it = list.begin(); it != list.end(); it ++){
            if (it->tag == tag){
                return *it;
            }
        }
        return Node();
    }

    int search_statistics(string tag){
        int key = hash(tag);
        vector<Node> list = table[key];
        int cont = 0;
        for (vector<Node>::iterator it = list.begin(); it != list.end(); it ++){
            cont ++;
            if (it->tag == tag){
                break;
            }
        }
        if (cont == 0)
            cont = -1;
        return cont;
    }

    void operator>> (ofstream &file) {
        file << setw(55) << setfill('_') << right << ' ' << endl;
        file << '|' << setw(10) << setfill(' ') << right << "Chave" << '|' << 
            setw(10) << setfill(' ') << right << "Dados" << '|' << 
            setw(30) << setfill(' ') << right << "Nome" << '|' << endl;
        file << '+' << setw(11) << setfill('-') << right << '+' << 
            setw(11) << setfill('-') << right << '+' <<
            setw(31) << setfill('-') << right << '+' << endl;
        for (vector<vector<Node>>::iterator it1 = table.begin(); it1 !=  table.end(); it1 ++){
            vector<Node> list = *it1;
            if (list.size() != 0){
                for (vector<Node>::iterator it2 = list.begin(); it2 != list.end(); it2 ++){
                    file << '|' << 
                        setw(10) << setfill('.') << right << it2->key << '|' << 
                        setw(10) << setfill('.') << right << it2->data.data << '|' << 
                        setw(30) << setfill('.') << right << it2->tag << '|' << endl;
                }
            }
        }
    }
    int usedEntries(){
        int used = 0;
        for (int i = 0; i < this->size; i ++) {
            if (table[i].size() != 0){
                used ++;
            }
        }
        return used;
    }
    int emptyEntries(){
        int empty = 0;
        for (int i = 0; i < this->size; i ++) {
            if (table[i].size() == 0){
                empty ++;
            }
        }
        return empty;
    }
    int minList(){
        int min = table[0].size();
        for (int i = 0; i < this->size; i ++){
            if (table[i].size() < min){
                min = table[i].size();
            }
        }
        return min;
    }  
    int meanList(){
        float mean = 0;
        for (int i = 0; i < this->size; i ++){
            mean += table[i].size();
        }
        return mean/this->size;
    }  
    int maxList(){
        int max = 0;
        for (int i = 0; i < this->size; i ++){
            if (table[i].size() > max){
                max = table[i].size();
            }
        }
        return max;
    }  

    void showStatistics(){
        int usedEntries = this->usedEntries();
        int emptyEntries = this->emptyEntries();
        float ocupation = (float)usedEntries/(emptyEntries+usedEntries);

        cout << setw(20) << setfill('.') << left << "entradas usadas:" << usedEntries << endl;
        cout << setw(20) << setfill('.') << left << "entradas vazias:" << emptyEntries << endl;
        cout << setw(20) << setfill('.') << left << "taxa de ocupacao:" << ocupation << endl;
        cout << setw(20) << setfill('.') << left << "lista minima:" << minList() << endl;
        cout << setw(20) << setfill('.') << left << "lista maxima:" << maxList() << endl;
        cout << setw(20) << setfill('.') << left << "lista media:" << meanList() << endl;
    }
};


void parsing(string filename, HashTable& hashTable){
    ifstream file(filename.c_str());
    if(!file.is_open())
        return;
    string line;

    while (!file.eof()){
        file >> line;
        hashTable.insert(line, 0);
    }
        

    file.close();
}

int fileLineNumber(string filename){
    ifstream file(filename);
    int lineNumber = 0;
    string line;
    
    while (!file.eof()){
        file >> line;
        lineNumber ++;
    }
    return lineNumber;
}


int main(int argv, char **argc){
    string filename = argc[1];
    int filesize = fileLineNumber(filename);
    HashTable hashTable(filesize);
    ofstream output(filename.substr(0, filename.find_last_of('.'))+"_output" + filename.substr(filename.find_last_of('.'), filename.size()));

    parsing(filename, hashTable);
    
    hashTable >> output;
    
    hashTable.showStatistics();
    

    return 0;
}