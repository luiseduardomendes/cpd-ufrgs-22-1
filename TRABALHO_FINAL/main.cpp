#include <iostream>
#include <vector>
#include <string>
#include "ternary_search_tree.hpp"

using namespace std;

int main(int argv, char **argc){
    
    tst::Tree tree;

    vector<string> names = {
        {"Carlos Menin"},
        {"Eduardo Bolson"},
        {"Heloisa Marques"},
        {"Luis Mendes"},
        {"Vinicius Alves"}
    };

    string name;
    int count = 0;

    for (vector<string>::iterator it = names.begin(); it != names.end(); it ++){
        name = *it;
        count ++;
        tree.insert(name, new tst::Data(count, count*2, 1.5));
    }

    cout << tree.search("Carlos Menin") << endl;
    cout << tree.search("Luis Mendes") << endl;
    cout << tree.search("Carlos Eduardo Menin") << endl;
    
    return 0;
}