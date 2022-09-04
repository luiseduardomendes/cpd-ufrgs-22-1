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

namespace ht{
    class Data{
    private:
    public:
        int data;
        std::vector<string> player_position;
        std::string name;
        float rating;
        int count;
        Data(string name, string player_position);
        Data();
        void append_rating(float rating);
        void append_positions(string positions);
        void operator>> (std::ostream &output);
    };

    class Node{
    public:
        int key;
        int sofifa_id;
        Data data;
        Node();
        Node(int key, int sofifa_id, Data data);
    };

    class HashTable{
    private:
        vector<vector<Node>> table;
        int size;
        int hash(int sofifa_id);
    public:
        HashTable(int size);
        void read_csv(std::ifstream &input);
        void insert(int sofifa_id, Data data);
        void remove(int sofifa_id);
        Node search(int sofifa_id);
        void operator>>(std::ostream &file);
    };
}