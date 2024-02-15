#ifndef INC_7_LAB_DIR_H
#define INC_7_LAB_DIR_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

bool this_directory(const std::string& dir_path, const std::string& path);

class Dir {
public:
    explicit Dir(const std::string& path) : a_path(path) {
        if (!is_wrong()) {
            for (const auto &i_file: fs::directory_iterator(a_path)) {
                content.push_back(i_file.path().string());
            }
        }
        else {
            std::cout << "no such file or directory..." << std::endl;
        }
    }

    ~Dir() { a_path.clear();}

    bool is_wrong() const;

    void reload_content();

    void get_content() const;

    void rename_entry(const std::string& old_name, const std::string& new_name);

    void rename_entry(int num, const std::string& new_name);

    void delete_entry(const std::string& name);

    void delete_entry(int num);

    void create_entry(const std::string& name);

private:
    fs::path a_path;
    std::vector<std::string> content;
};


#endif //INC_7_LAB_DIR_H
