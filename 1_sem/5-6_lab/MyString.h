#ifndef INC_2_LAB_MYSTRING_H
#define INC_2_LAB_MYSTRING_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <memory>
#include <windows.h>

char* mystrcat(char* string, const char* buff, int spos, int bpos, int bsize);
int cin_int();
int cin_pos_int();

class MyString {
private:
    char* string;
    int size;
public:
    MyString();
    [[maybe_unused]] explicit MyString(char *buff);
    [[maybe_unused]] MyString(const MyString &obj);
    ~MyString();
    void* operator new(size_t newsize);
    void operator delete(void* str);
    void* operator new[](size_t newsize);
    void operator delete[](void* ptr);
    MyString operator += (MyString& opnd);
    MyString operator -= (MyString& opnd);
    MyString operator *= (unsigned int n);
    MyString& operator = (const MyString& opnd);
    char operator [] (size_t i);
    operator char* ();
    char* value();
    int length() const;
    char* set_console(int memsize);
    char* set_file(int memsize, std::ifstream& fin);
    char* edit(char *buff);
    char* insert(char *buff, int pos, int bsize);
    char* erase(int pos, int len);
    int* find(const char* pattern, int n);
};

MyString operator + (MyString& opnd1, MyString& opnd2);
MyString operator - (MyString& opnd1, MyString& opnd2);
MyString operator * (MyString& factor, unsigned int n);
bool operator > (MyString& opnd1, MyString& opnd2);
bool operator >= (MyString& opnd1, MyString& opnd2);
bool operator == (MyString& opnd1, MyString& opnd2);
bool operator <= (MyString& opnd1, MyString& opnd2);
bool operator < (MyString& opnd1, MyString& opnd2);
std::ostream& operator << (std::ostream &out, MyString& opnd);
std::istream& operator>>(std::istream &in, MyString& opnd);


#endif //INC_2_LAB_MYSTRING_H
