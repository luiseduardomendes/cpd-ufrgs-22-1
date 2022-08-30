#include "ternary_search_tree.hpp"


tst::Data::Data(int user_id, int sofifa_id, float rating){
    this->user_id = user_id;
    this->sofifa_id = sofifa_id;
    this->rating = rating;
}

tst::Data::Data(){
    this->user_id = -1;
    this->sofifa_id = -1;
}

tst::Node::Node(){
    this->key = '\0';
}

tst::Node::Node(Data *data, char key){
    this->key = key;
    this->data = data;
    this->next.assign(0x60, NULL);
}

tst::Tree::Tree(){
    root = new Node(NULL, '\0');
}

bool tst::Tree::isEmpty(){
    return root == NULL;
}

int to_int(char a){
    return a - 0x20;

}

void tst::Tree::insert(std::string word, Data *data){
    char ch;
    Node *node = this->root;

    for (std::string::iterator it = word.begin(); it != (word.end()); it ++){        
        ch = *it;
        int c = to_int(ch);
        if (node->next[c] == NULL){
            node->next[c] = new Node(NULL, ch);
        }
        node = node->next[c];
    }
    node->data = data; 
}

void tst::Tree::remove(std::string word){

}

int tst::Tree::search(std::string word){
    char ch;
    Node *node = this->root;
    for (std::string::iterator it = word.begin(); it != word.end(); it ++){
        ch = *it;
        int c = to_int(ch);
        if (node->next[c] == NULL)
            return -1;
        node = node->next[c];
    }
    if (node->data == NULL)
        return -1;
    else
        return node->data->sofifa_id;
}

void tst::Tree::read_csv(std::ifstream input){

}