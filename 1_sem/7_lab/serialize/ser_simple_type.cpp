#include <iostream>
#include <string>
#include <forward_list>
#include <fstream>
#include <vector>


void serialize(std::forward_list<int>& list, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if(!ofs.is_open())
        throw std::runtime_error("error file opening...\n");
    char sep = '\n';
    for(const auto& itr : list) {
        int buff = itr;
        ofs.write(reinterpret_cast<char*>(&buff), sizeof(int));
        ofs.write(reinterpret_cast<char*>(&sep), sizeof(char));
    }
    ofs.close();
}

bool read_file(std::ifstream& ifs, std::string& str){
    char buff;
    str.clear();
    while(ifs.read(reinterpret_cast<char*>(&buff), sizeof(char))) {
        if (buff == '\n')
            return true;
        str += buff;
    }
    return false;
}

void edit_element(int id, int value,const std::string& filename) {
    std::ifstream ifs{filename, std::ios::binary |  std::ios::in | std::ios::out};
    if(!ifs.is_open())
        throw std::runtime_error("error file opening...\n");

    int buff;
    std::streampos pos;
    int i = 0;
    if(id == 0)
        pos = 0;
    else
        while(ifs.read(reinterpret_cast<char*>(&buff), sizeof(int))) {
            ifs.seekg(1, std::ios::cur);
            if(i == id - 1) {
                pos = ifs.tellg();
                break;
            }
            i++;
        }
    ifs.close();

    std::ofstream ofs(filename, std::ios::binary | std::ios::in);
    if(!ofs.is_open())
        throw std::runtime_error("error file opening...\n");

    ofs.seekp(pos);
    char sep = '\n';
    ofs.write(reinterpret_cast<char*>(&value), sizeof(int));
    ofs.write(reinterpret_cast<char*>(&sep), sizeof(char));
    ofs.close();
}

void deserialize(std::forward_list<int>& list, const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary | std::ios::out);
    if(!ifs.is_open())
        throw std::runtime_error("error file opening...\n");

    ifs.seekg(0, std::ios::beg);
    int buff;
    std::vector<int> data;
    while(ifs.read(reinterpret_cast<char*>(&buff), sizeof(int))) {
        data.push_back(buff);
        ifs.seekg(1, std::ios::cur);
    }
    list.clear();
    while(!data.empty()) {
        list.push_front(data.back());
        data.pop_back();
    }
    ifs.close();
}

int main() {
    std::string filename{"list_int.txt"};
    std::forward_list<int> list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    try {
        serialize(list, filename);
        int id, new_value;

        std::cout << "Enter the number of record and new value:\n";
        std::cin >> id >> new_value;
        edit_element(id, new_value, filename);
        deserialize(list, filename);


        std::cout << "\nFrom file:\n\n";
        for(const auto& itr : list)
            std::cout << itr << std::endl;
    }
    catch (const std::runtime_error& ex) {
        std::cout << "error: " << ex.what() << std::endl;
    }
    return 0;
}
