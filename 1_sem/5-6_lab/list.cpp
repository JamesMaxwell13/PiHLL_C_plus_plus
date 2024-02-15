#include <iostream>


struct node {
    int value;
    node* next;
    node(struct node* next_node) : next(next_node) {};
    node(int data, struct node* next_node)
        : value(data), next(next_node) {};
};

class List {
public:
    int size;
    node* front_node;
    node* back_node;
    List() {
        size = 0;
        front_node = nullptr;
        back_node = nullptr;
    }
    void push_back(int data) {
        auto back = &back_node;
        auto front = &front_node;
        auto temp = new struct node(data, nullptr);
        if(size != 0)
            (*back)->next = temp;
        else
            *front = temp;
        *back = temp;
        size++;
    };
    void push_front(int data) {
        auto back = &back_node;
        auto front = &front_node;
        auto temp = new struct node(data, nullptr);
        if(size != 0)
            temp->next = *front;
        else
            *back = temp;
        *front = temp;
        size++;
    };
    void pop_front() {
        if(size != 0) {
            auto front = &front_node;
            auto temp = *front;
            *front = (*front)->next;
            delete temp;
            size--;
        }
    };
    void pop_back() {
        if(size != 0) {
            if(size == 1) {
                pop_front();
                return;
            }
            auto temp = front_node;
            while(temp->next != back_node)
                temp = temp->next;
            delete back_node;
            back_node = temp;
            back_node->next = nullptr;
            size--;
        }
    };
    int operator[] (int N) {
        if(N >= 0 && N < size) {
            auto temp = front_node;
            for(int i = 0; i < N; i++)
                temp = temp->next;
            return temp->value;
        }
        return -1;
    }
};


int main() {
    List list;
    list.push_back(2);
    list.push_back(3);
    list.push_front(1);
    list.push_back(4);
    list.push_back(5);
    list.push_front(0);
    list.push_back(6);
    list.push_back(7);
    list.push_back(8);
    for(int i = 0; i < list.size; i++)
        std::cout << list[i] << std::endl;
    list.pop_back();
    list.pop_front();
    for(int i = 0; i < list.size; i++)
        std::cout << list[i] << std::endl;
    return 0;
}