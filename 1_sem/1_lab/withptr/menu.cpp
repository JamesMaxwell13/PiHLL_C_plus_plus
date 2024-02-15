#include "MyString.h"

void menu(std::shared_ptr<MyString> object, std::ifstream& fin) {
    int choose;
    do {
        std::cout << "Choose the method (action) of class:\n"
                     " 1 - make class object (string),\n"
                     " 2 - auto-adding data from file,\n"
                     " 3 - editing object,\n"
                     " 4 - delete part (full) of string,\n"
                     " 5 - insert substring,\n"
                     " 6 - find substring (number of occurrences and shifts)\n"
                     " 7 - print data field of object\n"
                     " 0 - exit the program.\n\n";
        choose = cinPosInt();
        switch(choose)
        {
            case 1: {
                std::cout << "\nEnter the size of string:" << std::endl;
                int size = cinPosInt();
                std::cout << "Enter the string:" << std::endl;
                object->getConsole(size);
                std::cin.get();
                break;
            }
            case 2: {
                std::cout << "\nEnter the max size string and after that\nstring will be loaded from file:" << std::endl;
                int maxsize = cinPosInt();
                object->getFile(maxsize, fin);
                std::cin.get();
                break;
            }
            case 3: {
                std::cout << "\nEnter the size of new string:" << std::endl;
                int bsize = cinPosInt();

                char *buff = new char[bsize + 1];
                std::cout << "Enter the new string:" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.getline(buff, bsize + 1);

                object->edit(buff);
                delete [] buff;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 4: {
                if(object->value() != nullptr) {
                    std::cout << "\nEnter the begin of deleting substring:" << std::endl;
                    int erbegin = cinPosInt();
                    while(erbegin >= object->length()) {
                        std::cout << "Wrong input, try again" << std::endl;
                        erbegin = cinPosInt();
                    }
                    std::cout << "Enter the length of deleting substring:" << std::endl;
                    int ersize = cinPosInt();

                    object->erase(erbegin, ersize);
                }
                else
                    std::cout << "The string is empty, make new string..." << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 5: {
                if(object->value() != nullptr) {
                    std::cout << "\nEnter the size of inserting string:" << std::endl;
                    int bsize = cinPosInt();

                    char* buff = new char[bsize + 1];
                    std::cout << "Enter the string:" << std::endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.getline(buff, bsize + 1);

                    std::cout << "Enter the position to insert this string:" << std::endl;
                    int begin = cinPosInt();

                    object->insert(buff, begin, bsize);
                    delete [] buff;
                }
                else
                    std::cout << "The string is empty, make new string..." << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 6: {
                if(object->value() != nullptr) {
                    std::cout << "\nEnter the size of pattern string:" << std::endl;
                    int psize = cinPosInt();

                    char* pattern = new char[psize + 1];
                    std::cout << "Enter the pattern string itself:" << std::endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.getline(pattern, psize + 1, '\n');

                    object->find(pattern, psize);
                    delete [] pattern;
                }
                else
                    std::cout << "The string is empty, make new string..." << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 7: {
                if(object->value() != nullptr) {
                    std::cout << "\nString:\n" << object->value() << "\nSize: " << object->length() << '\n' << std::endl;
                }
                else
                    std::cout << "The string is empty, make new string..." << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 0: {}
            default: {
                std::cout << "Something gets wrong..." << std::endl;
                std::cin.get();
                break;
            }
        }
        //system("CLS");
    } while(choose != 0);
}
