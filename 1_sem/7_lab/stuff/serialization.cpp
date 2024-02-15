#include <iostream>
#include <forward_list>
#include <vector>
#include <fstream>
#include "template_list.h"

void serialize(forward_list<std::string>& list, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if(!ofs.is_open())
        throw std::runtime_error("error file opening...\n");
    char sep = '\n';
    for(const auto& itr : list) {
        const char *c_str = itr.c_str();
        ofs.write(c_str, static_cast<unsigned int>(sizeof(char)*itr.size()));
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

void edit_element(int id, const std::string& value,const std::string& filename) {
    std::ifstream ifs{filename, std::ios::binary |  std::ios::in | std::ios::out};
    if(!ifs.is_open())
        throw std::runtime_error("error file opening...\n");

    std::string buff_str;
    std::streampos pos;
    int i = 0;
    if(id == 0)
        pos = 0;
    else
        while(read_file(ifs, buff_str)) {
            pos = ifs.tellg();
            if(i == id - 1) {
                break;
            }
            i++;
        }

    std::vector<std::string> appendix;
    while(read_file(ifs, buff_str)) {
        appendix.push_back(buff_str);
    }
    ifs.close();

    std::ofstream ofs(filename, std::ios::binary | std::ios::in);
    if(!ofs.is_open())
        throw std::runtime_error("error file opening...\n");

    ofs.seekp(pos);
    char sep = '\n';
    const char* str = value.c_str();
    ofs.write(str, static_cast<unsigned int>(sizeof(char)*value.size()));
    ofs.write(reinterpret_cast<char*>(&sep), sizeof(char));
    for(const auto& itr : appendix) {
        const char *buff = itr.c_str();
        ofs.write(buff, static_cast<unsigned int>(sizeof(char)*itr.size()));
        ofs.write(reinterpret_cast<char*>(&sep), sizeof(char));
    }
    ofs.close();
}

void deserialize(forward_list<std::string>& list, const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary | std::ios::out);
    if(!ifs.is_open())
        throw std::runtime_error("error file opening...\n");

    ifs.seekg(0, std::ios::beg);
    std::string str;
    std::vector<std::string> data;
    while(read_file(ifs, str))
        data.push_back(str);
    list.clear();
    while(!data.empty()) {
        list.push_front(data.back());
        data.pop_back();
    }
    ifs.close();
}

int main() {
    std::string filename{"list.txt"};
    forward_list<std::string> list;


    try {
        serialize(list, filename);
        int id;
        std::string new_value;
        std::cin >> id >> new_value;
        edit_element(id, new_value, filename);
        deserialize(list, filename);

        for(const auto& itr : list)
            std::cout << itr << std::endl;
    }
    catch (const std::runtime_error& ex) {
        std::cout << "error: " << ex.what() << std::endl;
    }
    return 0;
}