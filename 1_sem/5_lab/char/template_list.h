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
    void push_back(T data) {
        auto *temp = new struct node<T>(data, nullptr);
        if(!is_empty()) {
            back_node->next = temp;
        }
        else {
            front_node = temp;
        }
        back_node = temp;
        size++;
    };
    void push_front(T data) {
        auto *temp = new struct node<T>(data, nullptr);
        if(!is_empty()) {
            temp->next = front_node;
        }
        else {
            back_node = temp;
        }
        front_node = temp;
        size++;
    };
    void push_node_back(struct node<T>* temp) {
        if(!is_empty()) {
            back_node->next = temp;
        }
        else {
            front_node = temp;
        }
        back_node = temp;
        size++;
    };
    void push_node_front(struct node<T>* temp) {
        if(!is_empty()) {
            temp->next = front_node;
        }
        else {
            back_node = temp;
        }
        front_node = temp;
        size++;
    };
    void pop_back() {
        if(!is_empty()) {
            if(size == 1) {
                pop_front();
                return;
            }
            auto *temp = front_node;
            while (temp->next != back_node)
                temp = temp->next;
            delete back_node;
            back_node = temp;
            back_node->next = nullptr;
            size--;
        }
    };
    void pop_front() {
        if(!is_empty()) {
            auto *temp = front_node;
            front_node = front_node->next;
            delete temp;
            size--;
        }
    };
    T operator[] (int N) {
        auto *temp = front_node;
        for(int i = 0; i < N; i++)
            temp = temp->next;
        return temp->value;
    }; // 0 <= N < size catch

    // extra methods, dont recommend to use
    struct node<T>* get_Nth(int N) {
        if(N >= size || size == 0)
            return nullptr;
        auto *temp = front_node;
        for(int i = 0; i < N; i++)
            temp = temp->next;
        return temp;
    };
    struct node<T>* find(T data) {
        if(is_empty())
            return nullptr;
        else {
            auto *temp = front_node;
            while(temp) {
                if(temp->value == data)
                    return temp;
                temp = temp->next;
            }
            return nullptr;
        }
    }  //only for nums and std::string, MyString
};

template<Toutput T>
std::istream& operator >> (std::istream &in, forward_list<T>& temp_list);

template<Toutput T>
std::istream& operator >> (std::istream &in, struct node<T>* node);

template<Toutput T>
std::ostream& operator << (std::ostream &out, forward_list<T> temp_list);

template<Toutput T>
std::ostream& operator << (std::ostream &out, struct node<T>* node);

template<Toutput T> requires std::is_same<T, char*>::value
struct node<T>* find_char(forward_list<T> list, T data);

#endif //INC_5_LAB_TEMPLATE_LIST_H
