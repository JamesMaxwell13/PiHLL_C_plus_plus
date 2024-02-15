//Во всех вариантах предусмотреть возможность автоматического добавления данных, должна
//быть возможность изменить поле объекта(методом), удалить, добавить объект в
//массив или список. Все классы должны быть разделены на файлы '.h' и '.cpp'
//Меню должно быть, даже если не указано явно. Использовать только С++.


//Класс для работы со строками. Поля ? строка, размер. Среди методов реализовать
//поиск в строке (по регулярному выражению или по введенной части строки), добавление
//текста, удаление (указав начало и конец).


//Перегрузить операторы +, -, *, +=, -=, *=, =, new, delete, сравнения, [].

#include "MyString.h"
#include "MyString.cpp"

int main() {
    SetConsoleCP(866);
    SetConsoleOutputCP(866);

    std::cout << "Enter the number of elements in array of strings: ";// << std::endl;
    int n = cin_pos_int();
    //std::shared_ptr<MyString> object(new MyString[n]);

    MyString *object;
    try
    {
        object = new MyString[n];
        std::cout <<"//memory allocated successfully\n" << std::endl;
    }
    catch (std::bad_alloc error)
    {
        std::cout << "//allocating error\n" << std::endl;
        return 2;
    }

    std::ifstream fin("../string.txt");
    int choose;
    do {
        std::cout << "===================================================================\n"
                     "Choose the action with class:\n"
                     "In actions 3-8 program use overloaded iostream and operator <[..]> \n"
                     " 1 - enter the array of strings,\n"
                     " 2 - auto-adding data from file,\n"
                     " 3 - printing the array,\n"
                     " 4 - addition the objects (with +=),\n"
                     " 5 - subtraction the strings (with -=),\n"
                     " 6 - strings multiplying (with *=),\n"
                     " 7 - assignment string to string,\n"
                     " 8 - comparing strings,\n"
                     " 0 - exit the program.\n\n";
        choose = cin_pos_int();
        std::cout << std::endl;
        std::cout << "===================================================================\n";
        switch(choose)
        {
            case 1: {
                for(int i = 0; i < n; i++) {
                    //::cout << "\nEnter the size of string:";     // << std::endl;
                    //int size = cin_pos_int();
                    std::cout << "Enter the string:";               // << std::endl;
                    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    //object[i].set_console(size);
                    std::cin >> object[i];
                    std::cin.get();
                }
                break;
            }
            case 2: {
                for(int i = 0; i < n; i++)
                    object[i].set_file(256, fin);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 3: {
                std::cout << "Array of <MyString>:" << std::endl;
                for(int i = 0; i < n; i++) {
                    std::cout << "string[" << i + 1 << "] = " << object[i] << std::endl;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 4: {
                int i, j;
                do {
                    std::cout << "Enter the number of first operand and second:" << std::endl;
                    i = cin_pos_int() - 1;
                    j = cin_pos_int() - 1;
                } while(i > n || j > n);
                
                if(object[i].value() != nullptr && object[j].value() != nullptr) {
                    MyString buff(object[i] + object[j]);
                    std::cout << object[i] << " + " << object[j] << " = " << buff << std::endl;
                    object[i] += object[j];
                    std::cout << "\nstring[i] += string[j]\nstring[i] = " << object[i] << std::endl;
                }
                else
                    std::cout << "Error, fill this strings with data" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 5: {
                int i, j;
                do {
                    std::cout << "Enter the number of first operand and second:" << std::endl;
                    i = cin_pos_int() - 1;
                    j = cin_pos_int() - 1;
                } while(i > n || j > n);

                if(object[i].value() != nullptr && object[j].value() != nullptr) {
                    MyString buff(object[i] - object[j]);
                    std::cout << object[i] << " - " << object[j] << " = " << buff << std::endl;
                    object[i] -= object[j];
                    std::cout << "\nstring[i] -= string[j]\nstring[i] = " << object[i] << std::endl;
                }
                else
                    std::cout << "Error, fill this strings with data" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 6: {
                int i, x;
                do {
                    std::cout << "Enter the number of first operand:" << std::endl;
                    i = cin_pos_int() - 1;
                } while(i > n);

                std::cout << "Enter the second operand (int):" << std::endl;
                x = cin_pos_int();
                if(object[i].value() != nullptr) {
                    MyString buff(object[i] * x);
                    std::cout << object[i] << " * " << x << " = " << buff << std::endl;
                    object[i] *= x;
                    std::cout << "\nstring[i] *= string[j]\nstring[i] = " << object[i] << std::endl;
                }
                else
                    std::cout << "Error, fill this strings with data" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 7: {
                int i, j;
                do {
                    std::cout << "Enter the number of assigned(before =)\nand parent string(after =):" << std::endl;
                    i = cin_pos_int() - 1;
                    j = cin_pos_int() - 1;
                } while(i > n || j > n);

                if(object[i].value() != nullptr && object[j].value() != nullptr) {
                    object[i] = object[j];
                    std::cout << "\nstring[i] = " << object[i] << std::endl;
                }
                else
                    std::cout << "Error, fill this strings with data" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 8: {
                int i, j;
                do {
                    std::cout << "Enter the number of first operand and second:" << std::endl;
                    i = cin_pos_int() - 1;
                    j = cin_pos_int() - 1;
                } while(i > n || j > n);
                if(object[i].value() != nullptr && object[j].value() != nullptr) {
                    std::cout << object[i] << " > " << object[j] << " = " << std::boolalpha << (object[i] > object[j]) << std::endl;
                    std::cout << object[i] << " < " << object[j] << " = " << std::boolalpha << (object[i] < object[j]) << std::endl;
                    std::cout << object[i] << " == " << object[j] << " = " << std::boolalpha << (object[i] == object[j]) << std::endl;
                    std::cout << object[i] << " >= " << object[j] << " = " << std::boolalpha << (object[i] >= object[j]) << std::endl;
                    std::cout << object[i] << " <= " << object[j] << " = " << std::boolalpha << (object[i] <= object[j]) << std::endl;
                }
                else
                    std::cout << "Error, fill this strings with data" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 0: { break; }
            default: {
                std::cout << "Something gets wrong..." << std::endl;
                std::cin.get();
                break;
            }
        }
        //system("CLS");
    } while(choose != 0);
    delete [] object;
    fin.close();
    return 0;
}