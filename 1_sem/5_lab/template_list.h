#ifndef INC_5_LAB_TEMPLATE_LIST_H
#define INC_5_LAB_TEMPLATE_LIST_H

#include <iostream>
#include <cstring>
#include <limits>

template<typename T>
concept Toutput = requires (T test) {
    { std::cout << test } -> std::convertible_to<std::ostream&>;
};

template <Toutput T>
struct node{
    T value;
    node* next;
    node(struct node* next_node) : next(next_node) {};
    node(T data, struct node* next_node)
            : value(data), next(next_node) {};
};

template<Toutput T>
class forward_list {
    int size;
    struct node<T>* front_node;
    struct node<T>* back_node;
public:
    forward_list() : front_node(nullptr),
        back_node(nullptr), size(0) {};
    explicit forward_list(T data);
    ~forward_list();
    int length();
    bool is_empty();
    T front();
    T back();
    void push_back(T data);
    void push_front(T data);
    void push_node_back(struct node<T>* temp);
    void push_node_front(struct node<T>* temp) ;
    void pop_back();
    void pop_front();
    T operator[] (int N); // 0 <= N < size catch

    // extra methods, dont recommend to use
    struct node<T>* get_Nth(int N);
    struct node<T>* find(T data);  //only for nums and std::string, MyString
};

template<Toutput T>
std::istream& operator >> (std::istream &in, forward_list<T>& temp_list) {
    T buff;
    int size = 0;
    std::cout << "Enter the number of elements: ";
    std::cin >> size;
    for(int i = 0; i < size; i++) {
        in >> buff;
        temp_list.push_back(buff);
    }
    return in;
}

template<Toutput T>
std::istream& operator >> (std::istream &in, struct node<T>* node) {
    T buff;
    in >> buff;
    node->value = buff;
    return in;
}

template<Toutput T>
std::ostream& operator << (std::ostream &out, forward_list<T> temp_list) {
    if(temp_list.is_empty())
        out << "List if empty";
    else {
        int i = 0;
        while(i < temp_list.length()) {
            out << temp_list[i] << ' ';
            i++;
        }
    }
    return out;
}

template<Toutput T>
std::ostream& operator << (std::ostream &out, struct node<T>* node)
{
    if(node != nullptr)
        out << node->value;
    return out;
}

//template<Toutput T> requires std::is_same<T, char*>::value
//struct node<T>* find_char(forward_list<T> list, T data);

#endif //INC_5_LAB_TEMPLATE_LIST_H
