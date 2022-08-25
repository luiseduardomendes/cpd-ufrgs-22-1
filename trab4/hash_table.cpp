#include <iostream>
#include <vector>
#include <string>
#include <ctime>

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
    Node print(){
        cout << this->key << ":\t" << this->data.data << "\t" << this->tag << endl;
    }
};

class HashTable{
private:
    vector<vector<Node>> table;
    int size;
    int hash(string tag){
        return (
            (int)*(tag.begin()) * 
            (int)*(tag.begin()) +
            2 * (int)*(tag.end() - 1) 
        ) % (size);
    }
public:
    HashTable(int size){
        this->size = size;
        for (int i = 0; i < size; i ++){
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
        return cont;
    }

    void print(){
        cout << "Chave   Pontos  Equipe" << endl << endl;
        for (vector<vector<Node>>::iterator it1 = table.begin(); it1 !=  table.end(); it1 ++){
            vector<Node> list = *it1;
            if (list.size() != 0){
                for (vector<Node>::iterator it2 = list.begin(); it2 != list.end(); it2 ++){
                    cout << it2->key << ":\t" << it2->data.data << "\t" << it2->tag << endl;
                }
            }
        }
    }
};

int main(){
    srand(time(0));
    int n = 10, randmax = 50000;
    HashTable table(n);
    vector<string> tags = {
        "Liberty",
        "Netshoes Miners",
        "Rensga eSports",
        "LOUD",
        "FURIA eSports",
        "Flamengo eSports",
        "RED Canids",
        "Kabum eSports",
        "INTZ eSports",
        "paiN Gaming"
    };
    vector<int> points = {
        8, 8, 1, 12, 15, 6, 13, 11, 4, 12
    };
    

    for(int i = 0; i < n; i ++){
        table.insert(tags[i], points[i]);
    }
    table.print();

    Node node;
    node = table.search("paiN Gaming");

    node.print();
    
    return 0;
}