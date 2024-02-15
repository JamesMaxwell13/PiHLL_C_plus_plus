#include "template_list.h"
#include "MyString.h"
#include <vector>

template<Toutput T>
void menu(forward_list<T> list) {
    while(1) {
        std::cout << "=========================================\n"
                     "Choose the action with list\n"
                     "(list was initialized, but it is empty):\n"
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
                     " 0 - exit the program.\n\n";
        unsigned int choose;
        std::cin >> choose;
        switch (choose) {
            case 1: {
                std::cin >> list;
                break;
            }
            case 2: {
                T buff;
                std::cin >> buff;
                list.push_back(buff);
                break;
            }
            case 3: {
                T buff;
                std::cin >> buff;
                list.push_front(buff);
                break;
            }
            case 4: {
                auto* temp = new struct node<T>(nullptr);
                std::cout << "Enter the node value: " << std::endl;
                std::cin >> temp;
                std::cout << "Push front(1) or back(0)? ";
                int push = 0;
                while(push != 0 || push != 1) {
                    std::cin >> push;
                    if (push == 1)
                        list.push_node_front(temp);
                    else if (push == 0)
                        list.push_node_back(temp);
                    else
                        std::cout << "Wrong input" << std::endl;
                }
                break;
            }
            case 5: {
                list.pop_back();
                break;
            }
            case 6: {
                list.pop_front();
                break;
            }
            case 7: {
                std::cout << list << std::endl;
                break;
            }
            case 8: {
                int N;
                std::cout << "Enter N: ";
                std::cin >> N;
                if(list.get_Nth(N) != nullptr)
                    std::cout << list.get_Nth(N);
                else
                    std::cout << "No such element..." << std::endl;
                break;
            }
            case 9: {
                T buff;
                std::cout << "Enter the value to search: ";
                std::cin >> buff;
                struct node<T> *search;
//                if(std::is_same<T,char*>::value)
//                    search = find_char(list, buff);
//                else
                    search = list.find(buff);
                std::cout << "Node: " << search << " next: " << search->next << std::endl;
                break;
            }
            case 10: {
                std::cout << "Do you want get front(1) or back(0): ";
                int get = -1;
                while(get != 0 || get != 1) {
                    std::cin >> get;
                    if (get == 1)
                        std::cout << list.front();
                    else if (get == 0)
                        std::cout << list.back();
                    else
                        std::cout << "Wrong input" << std::endl;
                }
                break;
            }
            case 0: {
                std::cout << "\nExit program..." << std::endl;
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
                 "Choose the type of data int list:\n"
                 " 1 - char,\n"
                 " 2 - int,\n"
                 " 3 - double,\n"
                 " 4 - std::string,\n"
                 " 5 - MyString.\n\n";
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