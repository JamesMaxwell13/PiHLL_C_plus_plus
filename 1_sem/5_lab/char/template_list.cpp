#include "template_list.h"



template<Toutput T>
forward_list<T>::forward_list(T data) {
    auto* buff = new struct node<T>(data, nullptr);
    front_node = buff;
    back_node = buff;
    size = 1;
}

template<Toutput T>
forward_list<T>::~forward_list() {
    while(size != 0)
        pop_front();
}

template<Toutput T>
int forward_list<T>::length() { return size; }

template<Toutput T>
bool forward_list<T>::is_empty() {
    if (size == 0)
        return true;
    else
        return false;
}

template<Toutput T>
T forward_list<T>::front() { return front_node->value; }

template<Toutput T>
T forward_list<T>::back() { return back_node->value; };

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




template<Toutput T>
std::istream& operator >> (std::istream &in, forward_list<T>& temp_list) {
    T buff;
    int size = 0;
    std::cout << "enter the number of elements: ";
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
std::ostream& operator << (std::ostream &out, forward_list<T> temp_list)
{
    if(temp_list.is_empty())
        out << "list if empty";
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

template<Toutput T> requires std::is_same<T, char*>::value
struct node<T>* find_char(forward_list<T> list, T data) {
    if(list.is_empty())
        return nullptr;
    else {
        auto *temp = list.front_node;
        while(temp) {
            if(strcmp(temp->value, data) == 0)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }
}

//template<Toutput T>
//std::istream& operator >> (std::istream &in, forward_list<T>& temp_list) {
//    T buff;
//    in >> buff;
//    temp_list.push_back(buff);
//    return in;
//}

//template<>
//class forward_list_char : public forward_list<char*> {
//public:
//    struct node<char*>* find(char *data) override {
//        if (is_empty())
//            return nullptr;
//        else {
//            auto *temp = front_node;
//            while (temp) {
//                if (strcmp(temp->value, data) == 0)
//                    return temp;
//                temp = temp->next;
//            }
//            return nullptr;
//        }
//    };
//};