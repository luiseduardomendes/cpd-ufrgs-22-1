#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Data{
private:
public:
    Data(int i){
    }
    Data(){
    }
};

class Node{
public:
    int key;
    Data data;
    Node(){
        key = -1;
    }
    Node(int __key, Data __data){
        key = __key;
        data = __data;
    }
};

class HashTable{
private:
    vector<vector<Node>> table;
    int hash(int key){
        return key % (table.size()/10);
    }
public:
    HashTable(int size){
        for (int i = 0; i < size/10; i ++){
            vector<Node> v;
            v.clear();
            table.push_back(v);
        }
    }

    void insert(int key, Data data){
        table[hash(key)].push_back(Node(key, data));
    }

    void remove(int key){
        vector<Node> list = table[hash(key)];
        for (vector<Node>::iterator it = list.begin(); it != list.end(); it ++){
            if (it->key == key){
                list.erase(it);
            }
        }
    }

    Node search(int key){
        vector<Node> list = table[hash(key)];
        for (vector<Node>::iterator it = list.begin(); it != list.end(); it ++){
            if (it->key == key){
                return *it;
            }
        }
        return Node();
    }

    int search_statistics(int key){
        vector<Node> list = table[hash(key)];
        int cont = 0;
        for (vector<Node>::iterator it = list.begin(); it != list.end(); it ++){
            cont ++;
            if (it->key == key){
                break;
            }
        }
        return cont;
    }

    void print(){
        for (vector<vector<Node>>::iterator it1 = table.begin(); it1 !=  table.end(); it1 ++){
            vector<Node> list = *it1;
            if (list.size() != 0){
                for (vector<Node>::iterator it2 = list.begin(); it2 != list.end(); it2 ++){
                    cout << it2->key << "\t";
                }
                cout << endl;
            }
        }
    }
};

int main(){
    srand(time(0));
    int n = 1000, randmax = 50000;
    HashTable table(n);

    for(int i = 0; i < n; i ++){
        table.insert(rand() % randmax, Data(0));
    }
    table.print();
    
    return 0;
}