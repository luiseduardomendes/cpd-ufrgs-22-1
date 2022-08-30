#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace tst{
    class Data{
    public:
        int user_id;
        int sofifa_id;
        float rating;
        Data(int user_id, int sofifa_id, float rating);
        Data();
    };
    
    class Node{
    public:
        Data* data;
        std::vector<Node*> next;
        char key;    
        Node();
        Node(Data *data, char key);
    };

    class Tree{
        private:
            Node *root;
        public:
            Tree();
            bool isEmpty();
            void insert(std::string word, Data *data);
            void remove(std::string word);
            int search(std::string word);

            void read_csv(std::ifstream input);
            void operator>>(std::ofstream output);

    };
}