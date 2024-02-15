
#include "MyString.h"

//input & my string.h funcs
char* mystrcat(char* string, char* buff, int spos, int bpos, int bsize) {
    for(int i = spos, j = bpos; j < bsize; i++, j++) {
        string[i] = buff[j];
    }

    int ssize = spos + bsize - bpos;
    if((string + ssize) != nullptr)
        string[ssize] = '\0';
    else
        string[ssize - 1] = '\0';

    return string;
}

int cinInt() {
    int num;
    std::cin >> num;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //максимальный размер потока ввода или \n
        std::cout << "Wrong input\n";
        std::cin >> num;
    }
    return num;
}

int cinPosInt() {
    int num;
    std::cin >> num;
    while(std::cin.fail() || num < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //максимальный размер потока ввода или \n
        std::cout << "Wrong input\n";
        std::cin >> num;
    }
    return num;
}


//MyString class methods
MyString::MyString() {                        //null argument constructor
    string = nullptr;
    size = 0;
}

[[maybe_unused]] MyString::MyString(char *buff) {     //argument constructor
    if(buff == nullptr) {
        string = new char[1];

        string[0] = '\0';
        size = 0;
    }
    else {
        size = (int) strlen(buff);
        string = new char[size + 1];

        strncpy(string, buff, size);
        string[size] = '\0';
    }
}

[[maybe_unused]] MyString::MyString(const MyString &obj) {     //copy constructor
    size = obj.size;
    string = new char[obj.size + 1];

    strncpy(string, obj.string, size);
    string[size] = '\0';
}

MyString::~MyString() {
    delete [] string;
    size = 0;
}

char* MyString::value() {
    return string;
}

int MyString::length() {
    return size;
}

char* MyString::getConsole(int bsize) {
    delete [] string;
    string = new char[bsize + 1];

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(string, bsize + 1, '\n');

    size = (int) strlen(string);
    //size = bsize;
    return string;
}

char* MyString::getFile(int maxsize, std::ifstream& fin) {
    if(fin.is_open()) {
        delete [] string;
        string = new char[maxsize + 1];
        std::cout << "Enter the number of string in file (counting from 0):\n";
        int index = cinPosInt();

        for(int i = 0; i < index; i++) {
            fin.getline(string, maxsize + 1, '\n');

            if(fin.fail() || fin.eof()) {
                fin.clear();
                fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                size = 0;
                return nullptr;
            }
        }
        size = (int)strlen(string);
    }
    else {
        size = 0;
        return nullptr;
    }
    return string;
}

char* MyString::edit(char *buff) {
        delete[] string;
        string = new char[strlen(buff) + 1];
        size = (int)strlen(buff);

        strncpy(string, buff, size);
        string[strlen(buff)] = '\0';
    return string;
}

char* MyString::insert(char *buff, int pos, int bsize) {
    if(pos <= size) {
        char *newstr = new char[size + bsize + 1];

        strncpy(newstr, string, pos);
        // strncat(newstr, buff, bsize);        doesn't work
        // strncat(newstr, string + pos, size - pos - 1);   doesn't work too    wtf!!!
        newstr = mystrcat(newstr, buff, pos, 0, bsize);
        newstr = mystrcat(newstr, string, pos + bsize, pos, size);

        size = size + bsize;
        newstr[size] = '\0';

        delete[] string;
        string = newstr;
    }
    else
        std::cout << "Wrong input" << std::endl;
    return string;
}

char* MyString::erase(int pos, int len) {
    if((len + pos) < size) {
        char *newstr = new char[size - len + 1];

        strncpy(newstr, string, pos + 1);
        newstr = mystrcat(newstr, string, pos, pos + len, size);
        //newstr = strncat(newstr, (string + pos + len), size - pos - len - 1);     fuck doesn't work

        size = size - len;
        newstr[size] = '\0';

        delete[] string;
        string = newstr;
    }
    else
        std::cout << "Wrong input" << std::endl;
    return string;
}

int MyString::find(const char* pattern, int n) {      //Morris Pratt's Knuth algorithm
    if (*pattern == '\0' || n == 0)
        std::cout << ("Null pattern string\n");

    if (*string == '\0' || n > size)
        printf("Base string is null or too short\n");

    //next[i] сохраняет индекс следующего лучшего частичного совпадения
    int next[n + 1];
    for (int i = 0; i < n + 1; i++)
        next[i] = 0;
    for (int i = 1; i < n; i++) {
        int j = next[i];

        while (j > 0 && pattern[j] != pattern[i])
            j = next[j];

        if (j > 0 || pattern[j] == pattern[i])
            next[i + 1] = j + 1;
    }

    int noccur = 0;
    for (int i = 0, j = 0; i < size; i++) {
        if (*(string + i) == *(pattern + j)) {
            if (++j == n) {
                std::cout << "The pattern occurs with shift " << i - j + 1 << std::endl;
                noccur++;
            }
        }
        else if (j > 0) {
            j = next[j];
            i--;
        }
    }
    return noccur;
}
