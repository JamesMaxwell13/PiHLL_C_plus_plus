#include <iostream>
#include <forward_list>
#include <vector>
#include <fstream>
#include "template_list.h"

std::ifstream& operator >> (std::ifstream& ifs, forward_list<std::string>& list) {
    if(!ifs.is_open())
        throw std::runtime_error("error file opening...\n");
    ifs.seekg(0, std::ios::beg);
    std::string str;
    while(read_file(ifs, str))
        list.push_back(str);
}

std::ofstream& operator << (std::ofstream& ofs, forward_list<std::string>& list) {
    if(!ofs.is_open())
        throw std::runtime_error("error file opening...\n");
    ofs.seekp(0, std::ios::beg);
    char sep = '\n';
    int N = list.length();
    for(int i = 0; i < N; i++) {
        const char *c_str = list[i].c_str();
        ofs.write(c_str, static_cast<unsigned int>(sizeof(char)*list[i].size()));
        ofs.write(reinterpret_cast<char*>(&sep), sizeof(char));
    }
}

int main() {
    std::string filename{"list.txt"};
    forward_list<std::string> list;
    list.push_back("abchihba");
    list.push_back("vlad is love");
    list.push_back("ptuir");
    list.push_back("yyyy");
    list.push_back("kekekek");
    list.push_back("dhfkkshfjhd");
    list.push_back("fjhgdfkg");
    try {
//        std::ofstream ofs(filename, std::ios::binary);
//        ofs << list;
//        ofs.close();
        serialize(list, filename);

        int id;
        std::string new_value;
        std::cout << "Enter the number of record and new value:\n";
        std::cin >> id >> new_value;
        edit_element(id, new_value, filename);
        forward_list<std::string> new_list;

        deserialize(new_list, filename);
//        std::ifstream ifs(filename, std::ios::binary);
//        ifs >> new_list;
//        ifs.close();

        std::cout << "\nFrom file:\n\n";
        for(int i = 0; i < new_list.length(); i++)
            std::cout << new_list[i] << std::endl;
    }
    catch (const std::runtime_error& ex) {
        std::cout << "error: " << ex.what() << std::endl;
    }
    return 0;
}



//std::ifstream& operator >> (std::ifstream& ifs, std::forward_list<std::string>& list) {
//    if(!ifs.is_open())
//        throw std::runtime_error("error file opening...\n");
//    ifs.seekg(0, std::ios::beg);
//    std::string str;
//    std::vector<std::string> data;
//    while(read_file(ifs, str))
//        data.push_back(str);
//    list.clear();
//    while(!data.empty()) {
//        list.push_front(data.back());
//        data.pop_back();
//    }
//}
//
//std::ofstream& operator << (std::ofstream& ofs, const std::forward_list<std::string>& list) {
//    if(!ofs.is_open())
//        throw std::runtime_error("error file opening...\n");
//    ofs.seekp(0, std::ios::beg);
//    char sep = '\n';
//    for(const auto& itr : list) {
//        const char *buff = itr.c_str();
//        ofs.write(buff, static_cast<unsigned int>(sizeof(char)*itr.size()));
//        ofs.write(reinterpret_cast<char*>(&sep), sizeof(char));
//    }
//}