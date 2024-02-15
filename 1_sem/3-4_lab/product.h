#ifndef INC_3_LAB_PRODUCT_H
#define INC_3_LAB_PRODUCT_H

#include "users.h"

class Editor;

class Product {
public:
    int ID;
    int quantity;
    void printPrivate();
    bool in_stock ;
    std::string type;
    std::string name;
    float price;
    Product(int newID, int newquantity, std::string newtype, std::string newname, float newprice);
    void print();
    bool buy(int num);
};


class ProdBase {
public:
    int size = 0;
    std::vector<Product> database;
    ProdBase(std::fstream& in);
    bool empty();
    int find(std::string name);
    Product& operator[](int i);
    std::vector<Product> sortType();
    std::vector<Product> sortName();
    std::vector<Product> sortPrice();

};


#endif //INC_3_LAB_PRODUCT_H
