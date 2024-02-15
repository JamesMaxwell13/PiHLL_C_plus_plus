#ifndef INC_3_LAB_USERS_H
#define INC_3_LAB_USERS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "product.h"

class Product;
class ProdBase;
class UserBase;
class Moderator;
class Admin;

class User {
    friend UserBase;
    friend Moderator;
    friend Admin;
    std::string login;
    std::string password;
public:
    bool access;
    int id;
    std::string username;
    User(int ID, std::string user_login, std::string user_password, std::string user_name);
    virtual void printCatalog(ProdBase products);
    void changeLogin();
    void changePassword();
    void changeName();
    virtual void INTERFACE(ProdBase& products, UserBase& userbase);
};

class Moderator: public User {
public:
    using User::User;
    void printUserInfo(UserBase& userbase);
    virtual void deleteUser(UserBase& userbase);
    virtual void editUser(UserBase& userbase);
    void INTERFACE(ProdBase& products, UserBase& userbase) override;
};

class Editor: public Moderator {
public:
    using Moderator::Moderator;
    void printExtended(Product Item);
    void printCatalog(ProdBase products) override;
    void editProduct(ProdBase& products);
    void addProduct(ProdBase& products);
    void addUser(UserBase& userbase);
    void INTERFACE(ProdBase& products, UserBase& userbase) override;
};


class Admin: public Editor {
public:
    using Editor::Editor;
    using Editor::printCatalog;
    void deleteUser(UserBase& userbase) override;
    void editUser(UserBase& userbase) override;
    void makeModer(UserBase& userbase);
    void makeEditor(UserBase& userbase);
    void INTERFACE(ProdBase& products, UserBase& userbase) override;
};

class UserBase {
public:
    int size = 0;
    int acc = -1;
    int logIn();
    bool logOut();
    std::vector<User*> userbase;
    UserBase(std::fstream& in);
    User* operator [] (int i);
    int find(std::string fname);
    void deleteUser(int i);
    ~UserBase();
};


#endif //INC_3_LAB_USERS_H
