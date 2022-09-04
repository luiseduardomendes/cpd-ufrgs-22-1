#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "ternary_search_tree.hpp"
#include "hash_table.hpp"

using namespace std;

void coutVector(std::vector<std::string> vec){
    int i = 1;
    for (vector<string>::iterator it = vec.begin(); it != vec.end(); it ++){
        cout << i << ".\t";
        cout << *it << endl;
        i ++;
    }
}

int main(int argv, char **argc){
    tst::Tree tree;

    std::ifstream input(argc[1]);
    tree.read_csv(input);
    input.close();

    input.open(argc[2]);
    ht::HashTable table(tree.size);

    table.read_csv(input);
    input.close();
    std::ofstream output("out_.txt");

    table >> output;
    output.close();

    std::string user_input;
    std::cout << "Search  by a player: " << endl;
    std::cin >> user_input;
    while (user_input != string("exit")){
        std::vector<int> ids;
        int selected;
        std::vector<std::string> temp = tree.search_by_radix(user_input, &ids);
        if (temp.size() > 1){
            std::cout << std::endl << "First 20 search results:" << std::endl;
            coutVector(temp);
            std::cout << "Write the number of the player you wanna search" << std::endl;
            std::cin >> selected;
            int id = ids[selected - 1];
            ht::Node node = table.search(id);
            node.data >> std::cout;
        }
        else if (temp.size() == 1){
            int id = ids[0];
            ht::Node node = table.search(id);
            node.data >> std::cout;
        }
        else{
            std::cout << "There's no result to your search!" << std::endl;
        }
        std::cout << std::endl << "Search by a player: " << std::endl;
        std::cin >> user_input;
    }
    
    return 0;
}