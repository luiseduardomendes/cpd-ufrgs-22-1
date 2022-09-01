#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "ternary_search_tree.hpp"

using namespace std;

void coutVector(std::vector<std::string> vec){
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); it ++)
        cout << *it << endl;
}

int main(int argv, char **argc){
    tst::Tree tree;

    std::ifstream input(argc[1]);
    tree.read_csv(input);

    std::string user_input;
    std::cout << "Search  by a player: " << endl;
    std::cin >> user_input;
    while (user_input != string("exit")){
        std::cout << std::endl << "Soluções da busca:" << std::endl;
        coutVector(tree.search_by_radix(user_input));
        std::cout << std::endl << "Search by a player: " << std::endl;
        std::cin >> user_input;
    }
    
    return 0;
}