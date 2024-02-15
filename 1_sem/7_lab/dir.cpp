#include "dir.h"

bool this_directory(const std::string& dir_path, const std::string& path) {
    auto slash{[](const std::string &str)->int {
        int i = 0;
        while (str.find('/') != std::string::npos)
            i++;
        return i;
    }
    };
    if(slash(dir_path) == slash(path))
        return true;
    return false;
}


bool Dir::is_wrong() const {
    if (fs::exists(a_path) && fs::is_directory(a_path))
        return false;
    return true;
}

void Dir::reload_content() {
    content.clear();
    for (const auto &i_file: fs::directory_iterator(a_path)) {
        content.push_back(i_file.path().string());
    }
}

void Dir::get_content() const {
    if (!is_wrong()) {
        std::cout << "Contents of " << a_path << ":\n";
        int i = 1;
        for (const auto &i_file: fs::directory_iterator(a_path)) {
            if(i_file.is_directory())
                std::cout << "[" << i << "] " << i_file.path() << " - [dir]" << std::endl;
            else
                std::cout << "[" << i << "] " << i_file.path() << std::endl;
            i++;
        }
    }
    else {
        std::cout << "no such file or directory..." << std::endl;
    }
}

void Dir::rename_entry(const std::string& old_name, const std::string& new_name) {
    try {
        fs::path old_path = a_path / old_name;
        if((fs::is_directory(old_path) && new_name.find('.') == std::string::npos) ||  !fs::is_directory(old_path)) {
            fs::path new_path = a_path / new_name;
            fs::rename(old_path, new_path);
        }
        else
            std::cout << "wrong name..." << std::endl;
        reload_content();
    } catch (fs::filesystem_error& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void Dir::rename_entry(const int num, const std::string& new_name) {
    try {
        std::string old_path = content[num - 1];
        if((fs::is_directory(old_path) && new_name.find('.') == std::string::npos) ||  !fs::is_directory(old_path)) {
            fs::path new_path = a_path / new_name;
            fs::rename(old_path, new_path);
        }
        else
            std::cout << "wrong name of dir..." << std::endl;
        reload_content();
    } catch (fs::filesystem_error& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void Dir::delete_entry(const std::string& name) {
    try {
        fs::path entry_path = a_path / name;
        fs::remove_all(entry_path);
        reload_content();
    } catch (fs::filesystem_error& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void Dir::delete_entry(const int num) {
    try {
        std::string entry_path = content[num - 1];
        fs::remove_all(entry_path);
        reload_content();
    } catch (fs::filesystem_error& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void Dir::create_entry(const std::string& name) {
    try {
        fs::path new_dirs = a_path / name;
        if(name.find('.') != std::string::npos) {
            fs::create_directories(new_dirs.parent_path());
            std::ofstream ofs(new_dirs.string());
            ofs.close();
        }
        else
            fs::create_directories(new_dirs);
        reload_content();
    } catch (fs::filesystem_error& ex) {
        std::cout << ex.what() << std::endl;
    }
}