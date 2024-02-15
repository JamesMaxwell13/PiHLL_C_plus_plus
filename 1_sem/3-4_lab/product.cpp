#include "product.h"

void Product::printPrivate() {
    std::cout << "\n | EXTRA INFORMATION: | ID: " << std::setfill(' ') << std::setw(32) << std::setfill('0') << std::setw(8) << std::right << ID; //28+36
    std::cout << " | Quantity of products: " << std::setfill(' ') << std::setw(8) << quantity << " |" << std::endl; //25+8+2
}

Product::Product(int newID, int newquantity, std::string newtype, std::string newname, float newprice) {
        quantity = newquantity;
        ID = newID;
        if(quantity > 0)
            in_stock = true;
        else
            in_stock = false;
        type = newtype;
        name = newname;
        price = newprice;
    }

void Product::print() {
    std::cout << std::setfill('_') << std::setw(110) << std::endl;
    std::cout << "\n| Type: " << std::setfill(' ') << std::setw(15) << type; //9+15
    std::cout << " | Name of product: " << std::setw(20) << name; //20+20
    std::cout << " | Price: " << std::setw(8) << price; //10+8
    std::cout << " | In stock: " << std::boolalpha << std::setw(5) << in_stock << " |"; //13+5+2
}

bool Product::buy(int num) {
    if (in_stock && (quantity - num) >= 0) {
        quantity -= num;
        if (quantity == 0)
            in_stock = false;
    }
    else
        std::cout << "Not possible to buy this product." << std::endl;
    return in_stock;
}

ProdBase::ProdBase(std::fstream& in) {
        in.seekg(0, std::ios_base::beg);
        int buff_id;
        int buff_quantity;
        std::string buff_type;
        std::string buff_name;
        float buff_price;
        do
        {
            in >> buff_id;
            in >> buff_quantity;
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(in, buff_type);
            getline(in, buff_name);
            in >> buff_price;
            Product buff(buff_id, buff_quantity, buff_type, buff_name, buff_price);
            database.push_back(buff);
            //database[size].print();
            size++;
            in.get();
        }
        while(!in.eof());
}

bool ProdBase::empty() {
        if(database.empty())
            return true;
        else
            return false;
    }

int ProdBase::find(std::string fname) {
    for(int i = 0; i < size; i++)
        if(database[i].name == fname)
            return i;
    return -1;
}

Product& ProdBase::operator[](int i) {
    return database[i];
}

bool changeType(Product prod1, Product prod2) {
    return prod1.type < prod2.type;
}

bool changeName(Product prod1, Product prod2) {
    return prod1.name < prod2.name;
}

bool changePrice(Product prod1, Product prod2) {
    return prod1.price < prod2.price;
}

std::vector<Product> ProdBase::sortType() {
    sort(database.begin(), database.end(), changeType);
    return database;
}
std::vector<Product> ProdBase::sortName() {
    sort(database.begin(), database.end(), changeName);
    return database;
}
std::vector<Product> ProdBase::sortPrice() {
    sort(database.begin(), database.end(), changePrice);
    return database;
}
