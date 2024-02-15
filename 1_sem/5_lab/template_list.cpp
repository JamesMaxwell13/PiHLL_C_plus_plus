#include "template_list.h"
#include "MyString.h"


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
T forward_list<T>::back() { return back_node->value; }

template<Toutput T>
void forward_list<T>::push_back(T data) {
    auto *temp = new struct node<T>(data, nullptr);
    if(!is_empty()) {
        back_node->next = temp;
    }
    else {
        front_node = temp;
    }
    back_node = temp;
    size++;
}

template<Toutput T>
void forward_list<T>::push_front(T data) {
    auto *temp = new struct node<T>(data, nullptr);
    if(!is_empty()) {
        temp->next = front_node;
    }
    else {
        back_node = temp;
    }
    front_node = temp;
    size++;
}

template<Toutput T>
void forward_list<T>::push_node_back(struct node<T>* temp) {
    if(!is_empty()) {
        back_node->next = temp;
    }
    else {
        front_node = temp;
    }
    back_node = temp;
    size++;
}

template<Toutput T>
void forward_list<T>::push_node_front(struct node<T>* temp) {
    if(!is_empty()) {
        temp->next = front_node;
    }
    else {
        back_node = temp;
    }
    front_node = temp;
    size++;
}

template<Toutput T>
void forward_list<T>::pop_back() {
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
}

template<Toutput T>
void forward_list<T>::pop_front() {
    if(!is_empty()) {
        auto *temp = front_node;
        front_node = front_node->next;
        delete temp;
        size--;
    }
}

template<Toutput T>
T forward_list<T>::operator[] (int N) {
    auto *temp = front_node;
    for(int i = 0; i < N; i++)
        temp = temp->next;
    return temp->value;
} // 0 <= N < size catch

// extra methods, dont recommend to use
template<Toutput T>
struct node<T>* forward_list<T>::get_Nth(int N) {
    if(N >= size || size == 0 || N < 0)
        return nullptr;
    auto *temp = front_node;
    for(int i = 0; i < N; i++)
        temp = temp->next;
    return temp;
}

template<Toutput T>
struct node<T>* forward_list<T>::find(T data) {
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
}

//only for nums and std::string, MyString

//find_char
//template<Toutput T> requires std::is_same<T, char*>::value
//struct node<T>* find_char(forward_list<T> list, T data) {
//    if(list.is_empty())
//        return nullptr;
//    else {
//        auto *temp = list.front_node;
//        while(temp) {
//            if(strcmp(temp->value, data) == 0)
//                return temp;
//            temp = temp->next;
//        }
//        return nullptr;
//    }
//}

template class forward_list<char>;
template class forward_list<int>;
template class forward_list<double>;
template class forward_list<std::string>;
template class forward_list<MyString>;

//template<> std::ostream& operator << <char> (std::ostream &, struct node<char>*);
//template<> std::ostream& operator << <int> (std::ostream &, struct node<int>*);
//template<> std::ostream& operator << <double> (std::ostream &, struct node<double>*);
//template<> std::ostream& operator << <std::string> (std::ostream &, struct node<std::string>*);
//template<> std::ostream& operator << <MyString> (std::ostream &, struct node<MyString>*);

//template<> std::ostream& operator << <char> (std::ostream &, struct node<char>*);
//template<> std::ostream& operator << <int> (std::ostream &, struct node<int>*);
//template<> std::ostream& operator << <double> (std::ostream &, struct node<double>*);
//template<> std::ostream& operator << <std::string> (std::ostream &, struct node<std::string>*);
//template<> std::ostream& operator << <MyString> (std::ostream &, struct node<MyString>*);

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