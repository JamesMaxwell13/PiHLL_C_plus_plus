#ifndef INC_1_LAB_MYSTRING_H
#define INC_1_LAB_MYSTRING_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <memory>
#include <windows.h>

class MyString {
private:
    char* string;
    int size;
public:
    MyString();
    [[maybe_unused]] explicit MyString(char *buff);
    [[maybe_unused]] MyString(const MyString &obj);
    ~MyString();
    char* value();
    int length();
    char* getConsole(int memsize);
    char* getFile(int memsize, std::ifstream& fin);
    char* edit(char *buff);
    char* insert(char *buff, int pos, int bsize);
    char* erase(int pos, int len);
    int find(const char* pattern, int n);
};

char*  mystrcat(char*  string, char* buff, int spos, int bpos, int bsize);

int cinInt();

int cinPosInt();

void menu(std::shared_ptr<MyString> object, std::ifstream& fin);

#endif //INC_1_LAB_MYSTRING_H
