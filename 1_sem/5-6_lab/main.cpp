#include "template_list.h"
#include "MyString.h"

template<Toutput T>
void menu(forward_list<T> list) {
    while(1) {
        std::cout //<< "len: " << list.length()
                  << "\n=========================================\n"
                     "Choose the action with list\n"
                     " 1 - enter full list,\n"
                     " 2 - push back,\n"
                     " 3 - push front,\n"
                     " 4 - enter and push node,\n"
                     " 5 - pop back,\n"
                     " 6 - pop front,\n"
                     " 7 - print full list,\n"
                     " 8 - print Nth node,\n"
                     " 9 - find node in list,\n"
                     " 10 - get back/front,\n"
                     " 0 - exit the program.\n\n"
                     "Your choice: ";
        unsigned int choose;
        std::cin >> choose;
        switch (choose) {
            case 1: {
                try {
                    std::cin >> list;
                }
                catch(const std::istream::failure& error) {
                    std::cout << "error: " << error.what() << std::endl;
                }
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 2: {
                T buff;
                std::cout << "Enter the node value: " << std::endl;
                try {
                    std::cin >> buff;
                }
                catch(const std::istream::failure& error) {
                    std::cout << "error: " << error.what() << std::endl;
                }
                list.push_back(buff);
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 3: {
                T buff;
                std::cout << "Enter the node value: " << std::endl;
                try {
                    std::cin >> buff;
                }
                catch(const std::istream::failure& error) {
                    std::cout << "error: " << error.what() << std::endl;
                }
                list.push_front(buff);
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 4: {
                auto* temp = new struct node<T>(nullptr);
                std::cout << "Enter the node value: " << std::endl;
                try {
                    std::cin >> temp;
                }
                catch(const std::istream::failure& error) {
                    std::cout << "error: " << error.what() << std::endl;
                }
                std::cout << "Push front(1) or back(0)? ";
                int push = -1;
                while(push != 0 && push != 1) {
                    std::cin >> push;
                    if (push == 1)
                        list.push_node_front(temp);
                    else
                        if (push == 0)
                            list.push_node_back(temp);
                        else
                            std::cout << "Wrong input" << std::endl;
                }
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 5: {
                try {
                    list.pop_back();
                }
                catch(const std::string& error) {
                    std::cout << "error: " << error << std::endl;
                }
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 6: {
                try {
                    list.pop_front();
                }
                catch(const std::string& error) {
                    std::cout << "error: " << error << std::endl;
                }                                                                       //pop empty
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 7: {
                try {
                    std::cout << list << std::endl;
                }
                catch(const std::string& error) {
                    std::cout << "error: " << error << std::endl;
                }
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 8: {
                int N;
                std::cout << "Enter N:\t";
                std::cin >> N;
                try {
                    std::cout << list[N] << std::endl;
                }
                catch(const std::string& error) {
                    std::cout << "error: " << error << std::endl;
                }
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 9: {
                T buff;
                std::cout << "Enter the value to search: ";
                try {
                    std::cin >> buff;
                }
                catch(const std::istream::failure& error) {
                    std::cout << "error: " << error.what() << std::endl;
                }
                struct node<T> *search;
                search = list.find(buff);
                try {
                    if(search->next != nullptr)
                        std::cout << "Node: " << search << " next: " << search->next << std::endl;
                    else
                        std::cout << "Node: " << search << std::endl;
                }
                catch(const std::string& error) {
                    std::cout << "error: " << error << std::endl;
                }
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 10: {
                std::cout << "Do you want get front(1) or back(0): ";
                int get = -1;
                while(get != 0 && get != 1) {
                    std::cin >> get;
                    if (get == 1)
                        try {
                            std::cout << list.front();
                        }
                        catch(const std::string& error) {
                            std::cout << "error: " << error << std::endl;
                        }
                    else if (get == 0)
                        try {
                            std::cout << list.back();
                        }
                        catch(const std::string& error) {
                            std::cout << "error: " << error << std::endl;
                        }
                    else
                        std::cout << "wrong input...\n" << std::endl;
                }
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 0: {
                std::cout << "\nExit program..." << std::endl;
                std::cout << "Press enter to continue...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                exit(0);
            }
            default: {
                std::cout << "Wrong input..." << std::endl;
                break;
            }
        }
    }
}

int main() {
    int type;
    std::cout << "=========================================\n"
                 "Choose the type of data in list:\n"
                 " 1 - char,\n"
                 " 2 - int,\n"
                 " 3 - double,\n"
                 " 4 - std::string,\n"
                 " 5 - MyString.\n\n"
                 "Your choice: ";
    std::cin >> type;
    switch(type) {
        case 1: {
            forward_list<char> list;
            menu(list);
            break;
        }
        case 2: {
            forward_list<int> list;
            menu(list);
            break;
        }
        case 3: {
            forward_list<double> list;
            menu(list);
            break;
        }
        case 4: {
            forward_list<std::string> list;
            menu(list);
            break;
        }
        case 5: {
            forward_list<MyString> list;
            menu(list);
            break;
        }
        default: {
            std::cout << "Wrong input, run program again..." << std::endl;
            break;
        }
    }
    return 0;
}

//Реализовать соответствующую варианту динамическую структуру данных с
//использованием шаблонов. При этом предусмотреть перегрузку операторов ввода и вывода
//элемента структуры и всей структуры. Использовать классы, реализованные во второй
//лабораторной для демонстрации работы. Ограничить использование типов данных
//(не все типы могут использоваться в шаблоне).

//Однонаправленный список

//Условие задано тут: https://www.codewars.com/kata/5679d5a3f2272011d700000d
//Дополнительным усложнением является возможность указать размер квадратного поля
//от 5 до 10.

//исключения: ввод/вывод, обращение по неправильному индексу,
//поп пустого списка, обращение к пустому списку front/back