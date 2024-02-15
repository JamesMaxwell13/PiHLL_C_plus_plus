#include "users.h"
#include "product.h"



//class User
User::User(int ID, std::string user_login, std::string user_password, std::string user_name) {
    id = ID;
    access = false;
    login = user_login;
    password = user_password;
    username = user_name;
}

void User::printCatalog(ProdBase products) {
    if (!products.empty()) {
        for(auto itr : products.database) {
            itr.print();
        }
        std::cout << "\n\n";
    }
    else
        std::cout << "Something gets wrong... Database is empty..." << std::endl;
}

void User::changeLogin() {
    std::string user_login;
    std::cout << "Enter new login: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, user_login);
    login = user_login;
}

void User::changePassword() {
    std::string user_password;
    std::cout << "Enter new password: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, user_password);
    password = user_password;
}

void User::changeName() {
    std::string user_name;
    std::cout << "Enter new name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, user_name);
    username = user_name;
}

void User::INTERFACE(ProdBase& products, UserBase& userbase) {
    int choose = 0;
    std::cout << std::setfill('=') << std::setw(105) << std::endl;
    if (access) {
        while (choose != 5) {
            std::cout << "Enter the action:\n"
                         "[1] - print the catalog of products,\n"
                         "[2] - buy product in catalog,\n"
                         "[3] - sort catalog,\n"
                         "[4] - change your credentials,\n"
                         "[5] - log out your account.\n"
                         "Your choice: ";
            std::cin >> choose;
            switch (choose) {
                case 1: {
                    printCatalog(products);
                    break;
                }
                case 2: {
                    std::cout << "Enter the name of product: ";
                    std::string fname;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(std::cin, fname);
                    std::cout << "Enter the number of buying products: ";
                    int pr_num;
                    std::cin >> pr_num;
                    int i_buy = products.find(fname);
                    if (i_buy != -1)
                        if (products[i_buy].buy(pr_num))
                            std::cout << "Purchase was successful!" << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter the style of sorting:\n"
                                 "[1] - by types of products,\n"
                                 "[2] - by names of products,\n"
                                 "[3] - by prices." << std::endl;
                    int sort_type;
                    std::cin >> sort_type;
                    switch (sort_type) {
                        case 1: {
                            products.sortType();
                            printCatalog(products);
                            break;
                        }
                        case 2: {
                            products.sortName();
                            printCatalog(products);
                            break;
                        }
                        case 3: {
                            products.sortPrice();
                            printCatalog(products);
                            break;
                        }
                        default: {
                            std::cout << "Wrong input..." << std::endl;
                            break;
                        }
                        break;
                    }
                }
                case 4: {
                    std::cout << "Enter the number of credential to edit:\n"
                                 "[1] - login,\n"
                                 "[2] - password,\n"
                                 "[3] - username.\n"
                                 "Your choice: ";
                    int creds;
                    std::cin >> creds;
                    switch (creds) {
                        case 1: {
                            changeLogin();
                            break;
                        }
                        case 2: {
                            changeName();
                            break;
                        }
                        case 3: {
                            changePassword();
                            break;
                        }
                        default: {
                            std::cout << "Wrong input..." << std::endl;
                            break;
                        }
                        break;
                    }
                }
                case 5: {
                    userbase.logOut();
                    break;
                }
                default: {
                    std::cout << "Wrong input..." << std::endl;
                    break;
                }
            }
            std::cin.get();
        }
    }
    else
        std::cout << "Please, log in to your account..." << std::endl;
}




//class Moderator
void Moderator::printUserInfo(UserBase& userbase) {
    std::cout << "Enter the username of watching user: ";
    std::string fname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, fname);
    int i = userbase.find(fname);
    std::cout << std::setfill('_') << std::setw(120) << std::endl;
    std::cout << "\n | User ID: " << std::setfill(' ') << std::setw(8) << userbase[i]->id;
    std::cout << " | Login: " << std::setw(20) << userbase[i]->login;
    std::cout << " | Password: " << std::setw(20) << userbase[i]->password;
    std::cout << " | Username: " << std::setw(20) << userbase[i]->username << " |\n" << std::endl;
}

void Moderator::deleteUser(UserBase& userbase) {
    std::cout << "Enter the username of deleting user: ";
    std::string fname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, fname);
    int i = userbase.find(fname);
    if (i != -1)
        if(userbase[i]->id > 10000000 && userbase[i]->id < 20000000)
            userbase.deleteUser(i);
        else
            std::cout << "You can't delete this user" << std::endl;
    else
        std::cout << "No such user in userbase..." << std::endl;
}

void Moderator::editUser(UserBase& userbase) {
    std::cout << "Enter the username of editing user: ";
    std::string fname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, fname);
    int i = userbase.find(fname);
    if (i != -1 && userbase[i]->id > 10000000 && userbase[i]->id < 20000000) {
        int buff_id;
        std::string buff_login;
        std::string buff_password;
        std::string buff_name;

        std::cout << "Enter the new user ID (or 0 to don't change): ";
        std::cin >> buff_id;
        do {
            std::cin >> buff_id;
            if(buff_id < 10000000 || buff_id > 20000000)
                std::cout << "Wrong input" << std::endl;
            if(buff_id == 0)
                break;
        } while(buff_id < 10000000 || buff_id > 20000000);
        if (buff_id != 0) {
            userbase[i]->id = buff_id;
        }

        std::cout << "Enter the new login (or 0 to don't change): ";
        getline(std::cin, buff_login);
        if(buff_login != "0")
            userbase[i]->login = buff_login;

        std::cout << "Enter the new password (or 0 to don't change): ";
        getline(std::cin, buff_password);
        if(buff_password != "0")
            userbase[i]->password = buff_password;

        std::cout << "Enter the new username(or 0 to don't change): ";
        getline(std::cin, buff_name);
        if(buff_name != "0")
            userbase[i]->username = buff_name;

        std::cout << "Credentials was changed:" << std::endl;
        std::cout << std::setfill('_') << std::setw(105) << std::endl;
        std::cout << " | User ID: " << std::setw(8) << id;
        std::cout << " | Login: " << std::setw(20) << login;
        std::cout << " | Password: " << std::setw(20) << password;
        std::cout << " | Username: " << std::setw(20) << username << " |\n" << std::endl;
    }
    else
        if(userbase[i]->id < 10000000 || userbase[i]->id > 20000000)
            std::cout << "You can't edit this user" << std::endl;
        else
            std::cout << "No such user..." << std::endl;
}

void Moderator::INTERFACE(ProdBase& products, UserBase& userbase) {
    int choose = 0;
    std::cout << std::setfill('=') << std::setw(105) << std::endl;
    if (access) {
        while (choose != 5) {
            std::cout << "Enter the action:\n"
                         "[1] - print the catalog of products,\n"
                         "[2] - buy product in catalog,\n"
                         "[3] - sort catalog,\n"
                         "[4] - change your credentials,\n"
                         "[5] - log out your account,\n"
                         "[6] - print information about ny user,\n"
                         "[7] - delete user,\n"
                         "[8] - edit user.\n"
                         "Your choice: ";
            std::cin >> choose;
            switch (choose) {
                case 1: {
                    printCatalog(products);
                    break;
                }
                case 2: {
                    std::cout << "Enter the name of product: ";
                    std::string fname;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(std::cin, fname);
                    std::cout << "Enter the number of buying products: ";
                    int pr_num;
                    std::cin >> pr_num;
                    int i_buy = products.find(fname);
                    if (i_buy != -1)
                        if (products[i_buy].buy(pr_num))
                            std::cout << "Purchase was successful!" << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter the style of sorting:\n"
                                 "[1] - by types of products,\n"
                                 "[2] - by names of products,\n"
                                 "[3] - by prices." << std::endl;
                    int sort_type;
                    std::cin >> sort_type;
                    switch (sort_type) {
                        case 1: {
                            products.sortType();
                            printCatalog(products);
                            break;
                        }
                        case 2: {
                            products.sortName();
                            printCatalog(products);
                            break;
                        }
                        case 3: {
                            products.sortPrice();
                            printCatalog(products);
                            break;
                        }
                        default: {
                            std::cout << "Wrong input..." << std::endl;
                            break;
                        }
                            break;
                    }
                }
                case 4: {
                    std::cout << "Enter the number of credential to edit:\n"
                                 "[1] - login,\n"
                                 "[2] - password,\n"
                                 "[3] - username.\n"
                                 "Your choice: ";
                    int creds;
                    std::cin >> creds;
                    switch (creds) {
                        case 1: {
                            changeLogin();
                            break;
                        }
                        case 2: {
                            changeName();
                            break;
                        }
                        case 3: {
                            changePassword();
                            break;
                        }
                        default: {
                            std::cout << "Wrong input..." << std::endl;
                            break;
                        }
                            break;
                    }
                }
                case 5: {
                    userbase.logOut();
                    break;
                }
                case 6: {
                    printUserInfo(userbase);
                    break;
                }
                case 7: {
                    deleteUser(userbase);
                    break;
                }
                case 8: {
                    editUser(userbase);
                    break;
                }
                default: {
                    std::cout << "Wrong input..." << std::endl;
                    break;
                }
            }
            std::cin.get();
        }
    }
    else
        std::cout << "Please, log in to your account..." << std::endl;
}




//class Editor
void Editor::printExtended(Product Item) {
    Item.print();
    Item.printPrivate();
}

void Editor::printCatalog(ProdBase products) {
    if (!products.empty()) {
        for(auto itr : products.database) {
            printExtended(itr);
        }
    }
    else
        std::cout << "Something gets wrong... Database is empty..." << std::endl;
}

void Editor::editProduct(ProdBase& products) {
    std::cout << "Enter the username of editing user: ";
    std::string fname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, fname);
    int i = products.find(fname);
    if(i != -1) {
        int buff_id;
        int buff_quantity;
        std::string buff_type;
        std::string buff_name;
        float buff_price;
        std::cout << " Enter product ID (or 0 to don't change): ";
        std::cin >> buff_id;
        if (buff_id != 0)
            products[i].ID = buff_id;
        std::cout << " Enter product quantity (or 0 to don't change): ";
        std::cin >> buff_quantity;
        if (buff_quantity != 0)
            products[i].quantity = buff_quantity;
        std::cout << " Enter type of product (or 0 to don't change): ";
        getline(std::cin, buff_type);
        if (buff_type != "0")
            products[i].type = buff_type;
        std::cout << " Enter product name (or 0 to don't change): ";
        getline(std::cin, buff_name);
        if (buff_name != "0")
            products[i].type = buff_name;
        std::cout << " Enter product price (or 0 to don't change): ";
        std::cin >> buff_price;
        if (buff_price != 0)
            products[i].price = buff_price;
    }
    else
        std::cout << "No such product..." << std::endl;
}

void Editor::addProduct(ProdBase& products) {
    int buff_id;
    int buff_quantity;
    std::string buff_type;
    std::string buff_name;
    float buff_price;
    std::cout << " Enter product ID: ";
    std::cin >> buff_id;
    std::cout << " Enter product quantity: ";
    std::cin >> buff_quantity;
    std::cout << " Enter type of product: ";
    getline(std::cin, buff_type);
    std::cout << " Enter product name: ";
    getline(std::cin, buff_name);
    std::cout << " Enter product price: ";
    std::cin >> buff_price;
    Product buff(buff_id, buff_quantity, buff_type, buff_name, buff_price);
    products.database.push_back(buff);
    products.size++;

}

void Editor::addUser(UserBase& userbase) {
    int buff_id;
    std::string buff_login;
    std::string buff_password;
    std::string buff_username;
    std::cout << " Enter user ID: ";
    do {
        std::cin >> buff_id;
        if(buff_id < 10000000 || buff_id > 20000000)
            std::cout << "Wrong input" << std::endl;
    } while(buff_id < 10000000 || buff_id > 20000000);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << " Enter user login: ";
    getline(std::cin, buff_login);
    std::cout << " Enter user password: ";
    getline(std::cin, buff_password);
    std::cout << " Enter username: ";
    getline(std::cin, buff_username);
    User* buff_user = new User(buff_id, buff_login, buff_password, buff_username);
    userbase.userbase.push_back(buff_user);
    userbase.size++;
}

void Editor::INTERFACE(ProdBase& products, UserBase& userbase) {
    int choose = 0;
    std::cout << std::setfill('=') << std::setw(105) << std::endl;
    if (access) {
        while (choose != 5) {
            std::cout << "Enter the action:\n"
                         "[1] - print the catalog of products,\n"
                         "[2] - buy product in catalog,\n"
                         "[3] - sort catalog,\n"
                         "[4] - change your credentials,\n"
                         "[5] - log out your account,\n"
                         "[6] - print information about ny user,\n"
                         "[7] - delete user,\n"
                         "[8] - edit user,\n"
                         "[9] - edit product,\n"
                         "[10] - add product,\n"
                         "[11] - add user.\n"
                         "Your choice: ";
            std::cin >> choose;
            switch (choose) {
                case 1: {
                    printCatalog(products);
                    break;
                }
                case 2: {
                    std::cout << "Enter the name of product: ";
                    std::string fname;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(std::cin, fname);
                    std::cout << "Enter the number of buying products: ";
                    int pr_num;
                    std::cin >> pr_num;
                    int i_buy = products.find(fname);
                    if (i_buy != -1)
                        if (products[i_buy].buy(pr_num))
                            std::cout << "Purchase was successful!" << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter the style of sorting:\n"
                                 "[1] - by types of products,\n"
                                 "[2] - by names of products,\n"
                                 "[3] - by prices." << std::endl;
                    int sort_type;
                    std::cin >> sort_type;
                    switch (sort_type) {
                        case 1: {
                            products.sortType();
                            printCatalog(products);
                            break;
                        }
                        case 2: {
                            products.sortName();
                            printCatalog(products);
                            break;
                        }
                        case 3: {
                            products.sortPrice();
                            printCatalog(products);
                            break;
                        }
                        default: {
                            std::cout << "Wrong input..." << std::endl;
                            break;
                        }
                            break;
                    }
                }
                case 4: {
                    std::cout << "Enter the number of credential to edit:\n"
                                 "[1] - login,\n"
                                 "[2] - password,\n"
                                 "[3] - username.\n"
                                 "Your choice: ";
                    int creds;
                    std::cin >> creds;
                    switch (creds) {
                        case 1: {
                            changeLogin();
                            break;
                        }
                        case 2: {
                            changeName();
                            break;
                        }
                        case 3: {
                            changePassword();
                            break;
                        }
                        default: {
                            std::cout << "Wrong input..." << std::endl;
                            break;
                        }
                            break;
                    }
                }
                case 5: {
                    userbase.logOut();
                    break;
                }
                case 6: {
                    printUserInfo(userbase);
                    break;
                }
                case 7: {
                    deleteUser(userbase);
                    break;
                }
                case 8: {
                    editUser(userbase);
                    break;
                }
                case 9: {
                    editProduct(products);
                    break;
                }
                case 10: {
                    addProduct(products);
                    break;
                }
                case 11: {
                    addUser(userbase);
                    break;
                }
                default: {
                    std::cout << "Wrong input..." << std::endl;
                    break;
                }
            }
            std::cin.get();
        }
    }
    else
        std::cout << "Please, log in to your account..." << std::endl;
}




//class Admin
/////////////////////////////////////////////////////////////
void Admin::deleteUser(UserBase& userbase) {
    std::cout << "Enter the username of deleting user: ";
    std::string fname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, fname);
    int i = userbase.find(fname);
    if (i != -1)
        userbase.deleteUser(i);
    else
        std::cout << "No such user in userbase..." << std::endl;
}

void Admin::editUser(UserBase& userbase) {
    std::cout << "Enter the username of editing user: ";
    std::string fname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, fname);
    int i = userbase.find(fname);
    if (i != -1) {
        int buff_id;
        std::string buff_login;
        std::string buff_password;
        std::string buff_name;

        std::cout << "Enter the new user ID (or 0 to don't change): ";
        std::cin >> buff_id;
        do {
            std::cin >> buff_id;
            if(buff_id < 10000 || buff_id > 20000000)
                std::cout << "Wrong input" << std::endl;
            if(buff_id == 0)
                break;
        } while(buff_id < 10000 || buff_id > 20000000);
        if(buff_id != 0)
            userbase[i]->id = buff_id;

        std::cout << "Enter the new login (or 0 to don't change): ";
        getline(std::cin, buff_login);
        if(buff_login != "0")
            userbase[i]->login = buff_login;

        std::cout << "Enter the new password (or 0 to don't change): ";
        getline(std::cin, buff_password);
        if(buff_password != "0")
            userbase[i]->password = buff_password;

        std::cout << "Enter the new username(or 0 to don't change): ";
        getline(std::cin, buff_name);
        if(buff_name != "0")
            userbase[i]->username = buff_name;

        std::cout << "Credentials was changed:" << std::endl;
        std::cout << std::setfill('_') << std::setw(105) << std::endl;
        std::cout << " | User ID: " << std::setw(8) << id;
        std::cout << " | Login: " << std::setw(20) << login;
        std::cout << " | Password: " << std::setw(20) << password;
        std::cout << " | Username: " << std::setw(20) << username << " |\n" << std::endl;
    }
    else
        std::cout << "No such user..." << std::endl;
}

void Admin::makeModer(UserBase& userbase) {
    std::cout << "Enter the username of editing user: ";
    std::string fname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, fname);
    int i = userbase.find(fname);
    if (i != -1) {
        Moderator* new_moder = new Moderator((userbase[i]->id)%10000 + 1000000, userbase[i]->login, userbase[i]->password, userbase[i]->username);
        userbase.deleteUser(i);
        userbase.userbase.push_back(new_moder);
    }
}

void Admin::makeEditor(UserBase& userbase) {
    std::cout << "Enter the username of editing user: ";
    std::string fname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, fname);
    int i = userbase.find(fname);
    if (i != -1) {
        Editor* new_editor = new Editor((userbase[i]->id)%10000 + 100000, userbase[i]->login, userbase[i]->password, userbase[i]->username);
        userbase.deleteUser(i);
        userbase.userbase.push_back(new_editor);
    }
}

void Admin::INTERFACE(ProdBase& products, UserBase& userbase) {
    int choose = 0;
    std::cout << std::setfill('=') << std::setw(105) << std::endl;
    if (access) {
        while (choose != 5) {
            std::cout << "Enter the action:\n"
                         "[1] - print the catalog of products,\n"
                         "[2] - buy product in catalog,\n"
                         "[3] - sort catalog,\n"
                         "[4] - change your credentials,\n"
                         "[5] - log out your account,\n"
                         "[6] - print information about ny user,\n"
                         "[7] - delete user,\n"
                         "[8] - edit user,\n"
                         "[9] - edit product,\n"
                         "[10] - add product,\n"
                         "[11] - add user,\n"
                         "[12] - make moderator,\n"
                         "[13] - make editor.\n"
                         "Your choice: ";
            std::cin >> choose;
            switch (choose) {
                case 1: {
                    printCatalog(products);
                    break;
                }
                case 2: {
                    std::cout << "Enter the name of product: ";
                    std::string fname;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(std::cin, fname);
                    std::cout << "Enter the number of buying products: ";
                    int pr_num;
                    std::cin >> pr_num;
                    int i_buy = products.find(fname);
                    if (i_buy != -1)
                        if (products[i_buy].buy(pr_num))
                            std::cout << "Purchase was successful!" << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter the style of sorting:\n"
                                 "[1] - by types of products,\n"
                                 "[2] - by names of products,\n"
                                 "[3] - by prices." << std::endl;
                    int sort_type;
                    std::cin >> sort_type;
                    switch (sort_type) {
                        case 1: {
                            products.sortType();
                            printCatalog(products);
                            break;
                        }
                        case 2: {
                            products.sortName();
                            printCatalog(products);
                            break;
                        }
                        case 3: {
                            products.sortPrice();
                            printCatalog(products);
                            break;
                        }
                        default: {
                            std::cout << "Wrong input..." << std::endl;
                            break;
                        }
                            break;
                    }
                }
                case 4: {
                    std::cout << "Enter the number of credential to edit:\n"
                                 "[1] - login,\n"
                                 "[2] - password,\n"
                                 "[3] - username.\n"
                                 "Your choice: ";
                    int creds;
                    std::cin >> creds;
                    switch (creds) {
                        case 1: {
                            changeLogin();
                            break;
                        }
                        case 2: {
                            changeName();
                            break;
                        }
                        case 3: {
                            changePassword();
                            break;
                        }
                        default: {
                            std::cout << "Wrong input..." << std::endl;
                            break;
                        }
                            break;
                    }
                }
                case 5: {
                    userbase.logOut();
                    break;
                }
                case 6: {
                    printUserInfo(userbase);
                    break;
                }
                case 7: {
                    deleteUser(userbase);
                    break;
                }
                case 8: {
                    editUser(userbase);
                    break;
                }
                case 9: {
                    editProduct(products);
                    break;
                }
                case 10: {
                    addProduct(products);
                    break;
                }
                case 11: {
                    addUser(userbase);
                    break;
                }
                case 12: {
                    makeModer(userbase);
                    break;
                }
                case 13: {
                    makeEditor(userbase);
                    break;
                }
                default: {
                    std::cout << "Wrong input..." << std::endl;
                    break;
                }
            }
            std::cin.get();
        }
    }
    else
        std::cout << "Please, log in to your account..." << std::endl;
}


//class UserBase
UserBase::UserBase(std::fstream &in) {
    in.seekg(0, std::ios_base::beg);
    int buff_id;
    std::string buff_login;
    std::string buff_password;
    std::string buff_username;
    do
    {
        in >> buff_id;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(in, buff_login);
        getline(in, buff_password);
        getline(in, buff_username);
        if (buff_id > 10000000 && buff_id < 20000000) {
            User* user_ptr = new User(buff_id, buff_login, buff_password, buff_username);
            userbase.push_back(user_ptr);
            size++;
        }
        if (buff_id > 01000000 && buff_id < 2000000) {
            Moderator* moder_ptr = new Moderator(buff_id, buff_login, buff_password, buff_username);
            userbase.push_back(moder_ptr);
            size++;
        }
        if (buff_id > 00100000 && buff_id < 200000) {
            Editor* edit_ptr = new Editor(buff_id, buff_login, buff_password, buff_username);
            userbase.push_back(edit_ptr);
            size++;
        }
        if (buff_id > 00010000 && buff_id < 20000) {
            Admin* admin_ptr = new Admin(buff_id, buff_login, buff_password, buff_username);
            userbase.push_back(admin_ptr);
            size++;
        }
        in.get();
    } while(!in.eof());
}

int UserBase::logIn() {
    std::string buff_login;
    std::string buff_password;
    std::cout << "Enter the your login: ";
    getline(std::cin, buff_login);
    std::cout << "Enter the your password: ";
    getline(std::cin, buff_password);

    for (int i = 0; i < size; i++)
        if (userbase[i]->login == buff_login && userbase[i]->password == buff_password) {
            userbase[i]->access = true;
            std::cout << "You log in successfully!" << std::endl;
            std::cout << "Your username: " << userbase[i]->username << std::endl;
            acc = i;
            break;
        }
    if(acc == -1)
        std::cout << "Log out from this account or check your credentials..." << std::endl;
    return acc;
}

bool UserBase::logOut() {
    if (userbase[acc]->access) {
        userbase[acc]->access = false;
        std::cout << "Log out was successful..." << std::endl;
    } else
        std::cout << "Log in to new account to log out from it..." << std::endl;
    acc = -1;
    return userbase[acc]->access;
}

int UserBase::find(std::string fname) {
    for (int i = 0; i < size; i++)
        if (userbase[i]->username == fname)
            return i;
    return -1;
}

User* UserBase::operator[](int i) {
    return userbase[i];
}

void UserBase::deleteUser(int i) {
    userbase.erase(userbase.begin() + i);
}

UserBase::~UserBase() {
    for(auto& itr : userbase)
        delete[] itr;
}