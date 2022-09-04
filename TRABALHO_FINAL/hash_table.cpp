#include "hash_table.hpp"
#include "parser.hpp"

ht::Data::Data(std::string name, std::string player_position){
    this->count = 0;
    this->name = name;
    this->rating = 0;
    append_positions(player_position);
}

ht::Data::Data(){}

void ht::Data::operator>>(std::ostream &output){
    
    output << std::setw(39) << std::left << this->name << '|';
    output << setw(15) << std::right;
    for (std::vector<std::string>::iterator it = this->player_position.begin(); it != this->player_position.end(); it ++)
        output << *it << ", ";
    output << '|' << std::setw(10) << std::right << this->rating << '|';
}

void ht::Data::append_positions(std::string positions){
    size_t start = 0, end = 0;

    while ((end = positions.find(',', start)) != string::npos){
        this->player_position.push_back(positions.substr(start, end - start));
        start = end + 1;
    }

    this->player_position.push_back(positions.substr(start));
}

void ht::Data::append_rating(float rating){
    this->rating = ((this->rating * this->count) + rating) / (this->count + 1);
    this->count ++;
}

ht::Node::Node(int key, int sofifa_id, ht::Data data){
    this->key = key;
    this->data = data;
    this->sofifa_id = sofifa_id;
}

ht::Node::Node(){
    this->key = -1;
}

ht::Node ht::HashTable::search(int sofifa_id){
    int key = hash(sofifa_id);
    vector<ht::Node> list = table[key];
    for (vector<Node>::iterator it = list.begin(); it != list.end(); it ++){
        if (it->sofifa_id == sofifa_id){
            return *it;
        }
    }
    return ht::Node();
}
void ht::HashTable::remove(int sofifa_id){
    int key = hash(sofifa_id);
    vector<Node> list = table[key];
    for (vector<Node>::iterator it = list.begin(); it != list.end(); it ++){
        if (it->sofifa_id == sofifa_id){
            list.erase(it);
        }
    }
}

void ht::HashTable::insert(int sofifa_id, Data data){
    int key = hash(sofifa_id);
    table[key].push_back(Node(key, sofifa_id, data));
}

int ht::HashTable::hash(int sofifa_id){
    return sofifa_id % this->size;
}

void ht::HashTable::read_csv(std::ifstream &input){
    std::vector<std::string> names;
    aria::csv::CsvParser parser(input);
    bool gambiarra = false;
    for (auto& row : parser) {
        int i = 0;
        std::string name;
        std::string player_position;
        int sofifaId;
        
        for (auto& field : row) {
            switch (i) {
            case 0:
                sofifaId = atoi(field.c_str());
                break;
            case 1:
                name = field;
                break;
            case 2: 
                player_position = field;
                break;
            }
            
            i ++;
        }
        if (gambiarra)
            insert(sofifaId, ht::Data(name, player_position));
        else
            gambiarra = true;
    } 
}

ht::HashTable::HashTable(int size){
    this->size = size;
    for (int i = 0; i < this->size; i ++){
        vector<Node> v;
        v.clear();
        table.push_back(v);
    }
}


void ht::HashTable::operator>>(ostream &file) {
    for (vector<vector<Node>>::iterator it1 = table.begin(); it1 !=  table.end(); it1 ++){
        vector<Node> list = *it1;
        if (list.size() != 0){
            for (vector<Node>::iterator it2 = list.begin(); it2 != list.end(); it2 ++){
                file << 
                    std::setw(10) << std::setfill('.') << right << it2->key << '|' << 
                    std::setw(10) << std::setfill('.') << right << it2->sofifa_id;
                    it2->data >> file;
                    file << endl;
            }
        }
    }
}