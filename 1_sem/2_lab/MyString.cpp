#include "MyString.h"

//input & my string.h funcs
char* mystrcat(char* string, char* buff, int spos, int bpos, int bsize) {
    for(int i = spos, j = bpos; j < bsize; i++, j++) {
        string[i] = buff[j];
    }
    int ssize = spos + bsize - bpos;
    if(string + ssize != nullptr)
        string[ssize] = '\0';
    else
        string[ssize - 1] = '\0';

    return string;
}
int cin_int() {
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
int cin_pos_int() {
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

//MyString class methods and other overloaded
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
    size = 0;
    delete [] string;
}

void* MyString::operator new(size_t newsize) {
    void * ptr;
    ptr = malloc(newsize);
    if (!ptr)
    {
        std::bad_alloc error;
        throw error;
    }
    //std::cout << "\n//memory for " << newsize << " bytes allocated successfully\n" << std::endl;
    return ptr;
    //return ::operator new(newsize);
}
void MyString::operator delete(void* ptr) {
    free(ptr);
    std::cout << "\n//memory deallocated\n" << std::endl;
    //return ::operator delete(p);
}
void* MyString::operator new[](size_t newsize) {
    void * ptr;
    ptr = malloc(newsize);
    if (!ptr)
    {
        std::bad_alloc error;
        throw error;
    }
    //std::cout << "\n//memory for " << newsize << " elements allocated successfully\n" << std::endl;
    return ptr;
    //return ::operator new[](newsize);
}
void MyString::operator delete[](void* ptr) {
    free(ptr);
    std::cout << "\n//memory deallocated\n" << std::endl;
    //return ::operator delete[](ptr);
}
//try
//{
//  p = new Class[n]();
//}
//catch (bad_alloc error)
//{
//  cout<<"Error allocate!"<<::endl;
//}

MyString::operator char* () {
    return string;
}
char* MyString::value() {
    return string;
}
int MyString::length() {
    return size;
}

MyString operator + (MyString& opnd1, MyString& opnd2) {
    char *newstr = new char[opnd1.length() + opnd2.length() + 1];
    strncpy(newstr, opnd1.value(), opnd1.length());
    mystrcat(newstr, opnd2.value(), opnd1.length(), 0, opnd2.length());
    MyString sum(newstr);
    delete [] newstr;
    return sum;
}
MyString MyString::operator += (MyString& opnd) {
    *this = *this + opnd;
    return *this;
}
MyString operator - (MyString& opnd1, MyString& opnd2) {
    MyString diff = opnd1;
    int* entries = opnd1.find(opnd2.value(), opnd2.length());
    int i = 0;
    while(entries[i] != 0)
        std::cout << entries[i++] << std::endl;
    if(entries[0] != 0) {
        diff.erase(entries[0], opnd2.length());
    }
    delete [] entries;
    return diff;
}
MyString MyString::operator -= (MyString& opnd) {
    *this = *this - opnd;
    return *this;
}
MyString operator * (MyString& factor, unsigned int n) {
    if(n == 0) {
        MyString answer(nullptr);
        return answer;
    }
    MyString answer = factor;
    for(int i = 1; i < n; i++) {
        answer = (answer + factor);
    }
    return answer;
}
MyString operator * (unsigned int n, MyString& factor) {
    return factor * n;
}
MyString MyString::operator *= (unsigned int n) {
    *this = *this * n;
    return *this;
}
MyString& MyString::operator = (const MyString& opnd) {
    this->edit(opnd.string);
    return *this;
}

bool operator > (MyString& opnd1, MyString& opnd2) {
    if(strcmp(opnd1.value(), opnd2.value()) > 0)
        return true;
    return false;
}
bool operator >= (MyString& opnd1, MyString& opnd2) {
    if(strcmp(opnd1.value(), opnd2.value()) >= 0)
        return true;
    return false;
}
bool operator == (MyString& opnd1, MyString& opnd2) {
    if(strcmp(opnd1.value(), opnd2.value()) == 0)
        return true;
    return false;
}
bool operator <= (MyString& opnd1, MyString& opnd2) {
    if(strcmp(opnd1.value(), opnd2.value()) <= 0)
        return true;
    return false;
}
bool operator < (MyString& opnd1, MyString& opnd2) {
    if(strcmp(opnd1.value(), opnd2.value()) < 0)
        return true;
    return false;
}

char MyString::operator [] (size_t i) {
    return this->value()[i];
}
std::ostream& operator << (std::ostream &out, MyString& opnd) {
    return out << opnd.value(); //<< " (size:" << opnd.length() << ")";
}
std::istream& operator >> (std::istream &in, MyString& opnd)
{
    int bufsize = 1024;
    char* string = new char[1024];
    //in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    in.getline(string, bufsize + 1, '\n');
    opnd.edit(string);
    return in;
}

char* MyString::set_console(int bsize) {
    delete [] string;
    string = new char[bsize + 1];

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(string, bsize + 1, '\n');

    size = (int) strlen(string);
    return string;
}
char* MyString::set_file(int maxsize, std::ifstream& fin) {
    if(fin.is_open()) {
        delete [] string;
        string = new char[maxsize + 1];
        std::cout << "Enter the number of string in file:";
        int index = cin_pos_int();

        for(int i = 0; i < index; i++) {
            fin.getline(string, maxsize + 1, '\n');

            if(fin.fail() || fin.eof()) {
                fin.clear();
                fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                size = 0;
                return nullptr;
            }
        }
        size = (int) strlen(string);
    }
    else {
        size = 0;
        return nullptr;
    }
    fin.seekg(0, std::ios::beg);
    return string;
}
char* MyString::edit(char *buff) {
    delete[] string;
    string = new char[strlen(buff) + 1];
    size = strlen(buff);

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
int* MyString::find(char* pattern, int n) {      //Morris Pratt's Knuth algorithm
    //if (pattern[0] == '\0' || n == 0) {}
        //std::cout << ("Null pattern string\n");

    //if (string[0] == '\0' || n > size) {}
        //printf("Base string is null or too short\n");

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

    int* entries = new int[size];
    int l = 0;
    for (int i = 0, j = 0; i < size; i++) {
        if (string[i] == pattern[j]) {
            if (++j == n) {
                entries[l++] = i - j + 1;
                // std::cout << "The pattern occurs with shift " << i - j + 1 << std::endl;
            }
        }
        else if (j > 0) {
            j = next[j];
            i--;
        }
    }
    entries[l] = 0;
    return entries;
}
