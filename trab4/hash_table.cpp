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
    vector<int> linkedListStats(){
        int used = 0;
        int empty = 0;
        for (int i = 0; i < this->size; i ++) {
            if (table[i].size() != 0)
                used ++;
            if (table[i].size() == 0)
                empty ++;   
        }
        vector<int> ret = {used, empty};
        return ret;
    }

    vector<int> statsLists(){
        int min = table[0].size();
        int max = 0;
        float mean = 0;
        for (int i = 0; i < this->size; i ++){
            mean += table[i].size();
            if (table[i].size() < min)
                min = table[i].size();
            if (table[i].size() > max)
                max = table[i].size();
        }
        vector<float> ret = {(float)mean/this->size, min, max};
        return ret;
    }  

    void showStatistics(ofstream output){
        vector<int> temp = this->linkedListStats();
        int usedEntries = temp[0];
        int emptyEntries = temp[1];
        float ocupation = (float)usedEntries/(emptyEntries+usedEntries);
        temp = this->statsLists();
        float meanList = temp[0];
        int minList = (int)temp[1];
        int maxList = (int)temp[2];

        output << setw(20) << setfill('.') << left << "entradas usadas:" << usedEntries << endl;
        output << setw(20) << setfill('.') << left << "entradas vazias:" << emptyEntries << endl;
        output << setw(20) << setfill('.') << left << "taxa de ocupacao:" << ocupation << endl;
        output << setw(20) << setfill('.') << left << "lista minima:" << minList << endl;
        output << setw(20) << setfill('.') << left << "lista maxima:" << maxList << endl;
        output << setw(20) << setfill('.') << left << "lista media:" << meanList << endl;
    }
    void showStatisticsSearches(ofstream output, vector<string> searches){
        int min = INT64_MAX, max = 0, mean = 0, found = 0; 
        for (vector<string>::iterator search = output.begin(); 
        search != output.end(); search ++){
            int temp = this->search_statistics(*search);
            if (temp == -1)
                output << search << " MISS" << endl;
            else{
                output << search << " HIT " << temp << endl;
                if (temp < min)
                    min = temp;
                if (temp > max)
                    max = temp;
                mean += temp
                found += 1;
            }
        }
        mean = (float)mean / found;
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

void parsing_searches(string filename, vector<string> &list){
    ifstream file(filename.c_str());
    if(!file.is_open())
        return;
    string line;

    while (!file.eof()){
        file >> line;
        list.push_back(line);
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

    vector<int> experiments = {503, 2503, 5003, 7507};
    /*HashTable hashTable(filesize);
    ofstream output(filename.substr(0, filename.find_last_of('.'))+"_output" + filename.substr(filename.find_last_of('.'), filename.size()));
    
    parsing(filename, hashTable);
    hashTable >> output;
    hashTable.showStatistics();*/

    for (vector<int>::iterator it = experiments.begin();
                    it != experiments.end(); it ++){
        tableSize = *it;
        HashTable hashTable = new HashTable(tableSize);
        ofstream output("Experimento"+string("%d", tableSize)+".txt");

        parsing(filename, hashTable);
        hashTable.showStatistics(output);
        vector<string> searches;
        parsing_searches(argc[2], searches);
        hashTable.showStatisticsSearches(output, searches);

        output.close();
    }
    

    

    

    return 0;
}