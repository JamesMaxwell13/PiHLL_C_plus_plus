#include "dir.h"

int main() {
    std::string dirpath = "/", struct_path;
    std::cout << "Enter the path to directory to work with it:\n";
    do {
        getline(std::cin, dirpath);
        if(dirpath.find('/') != std::string::npos)
            std::cout << "Wrong input...\n";
    }
    while(dirpath.find('/') != std::string::npos);
    Dir dir(dirpath);
    if(dir.is_wrong()) {
        exit(0);
    }

    while(true) {
        int choose;
        std::cout << "===================================================================\n\n"
                     "Choose the action with directory:\n"
                     " 1 - print directory contents,\n"
                     " 2 - rename path,\n"
                     " 3 - delete path,\n"
                     " 4 - create path,\n"
                     " 0 - exit the program.\n"
                     "Your choice:";
        std::cin >> choose;
        std::cout << std::endl;
        std::cout << "===================================================================\n";
        switch(choose) {
            case 1: {
                dir.get_content();
                break;
            }
            case 2: {
                std::string new_path;
                bool way = false;
                std::cout << "Do you want to change the path\n"
                             "by number or by name(1-num, 0-name):";
                std::cin >> way;

                if(way) {
                    int num;
                    std::cout << "Enter the number of entry:";
                    std::cin >> num;
                    std::cout << "Enter new path:\ns";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(std::cin, new_path);
                    dir.rename_entry(num, new_path);
                    break;
                }

                std::string old_path;
                std::cout << "Enter the old path:\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(std::cin, old_path);
                std::cout << "Enter new path:\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(std::cin, new_path);
                dir.rename_entry(old_path, new_path);
                break;
            }
            case 3: {
                std::string path;
                bool way = false;
                std::cout << "Do you want to delete the path\n"
                             "by number or by name(1-num, 0-name):";
                std::cin >> way;

                if(way) {
                    int num;
                    std::cout << "Enter the number of entry:";
                    std::cin >> num;
                    dir.delete_entry(num);
                    break;
                }

                std::cout << "Enter deleting path:\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(std::cin, path);
                dir.delete_entry(path);
                break;
            }
            case 4: {
                std::string new_path;
                std::cout << "Enter creating path(new file or dir):\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(std::cin, new_path);
                dir.create_entry(new_path);
                break;
            }
            
            case 0: {
                std::cout << "Exit program..." << std::endl;
                exit(0);
                break;
            }
            default: {
                std::cout << "Wrong number of action..." << std::endl;
                std::cin.get();
                break;
            }
        }
    }
    return 0;
}


//    Dir dir("D:\\BSUIR\\folder");
//    dir.display_contents();
//    dir.rename_entry(4,"file.txt");
//    dir.delete_entry("folder2");
//    dir.create_entry("folder11\\aboba");


//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


//Создать необходимые классы для работы с файлами. Перегрузить операторы ввода и вывода для
//работы с файлами. Использовать ранее созданные классы. В начале программы заполняем
//динамическую структуру данных и записываем после заполнения данные в файл. Далее дать
//возможность изменить любой элемент по его id/индексу/свойству в самом файле. Далее по варианту,
//указанному ниже.

//Создание и управление директориями. Создать программу, позволяющую просматривать
//содержимое директорий, изменять названия файлов/директорий, удалять файлы и директории. При
//удалении директории удалять и все файлы внутри нее.