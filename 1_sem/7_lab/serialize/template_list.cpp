#include "template_list.h"
#include "MyString.h"


void serialize(forward_list<std::string>& list, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if(!ofs.is_open())
        throw std::runtime_error("error file opening...\n");
    char sep = '\n';
    for(int i = 0; i < list.length(); i++) {
        const char *c_str = list[i].c_str();
        ofs.write(c_str, static_cast<unsigned int>(sizeof(char)*list[i].size()));
        ofs.write(reinterpret_cast<char*>(&sep), sizeof(char));
    }
    ofs.close();
}

bool read_file(std::ifstream& ifs, std::string& str){
    char buff;
    str.clear();
    while(ifs.read(reinterpret_cast<char*>(&buff), sizeof(char))) {
        if (buff == '\n')
            return true;
        str += buff;
    }
    return false;
}

void edit_element(int id, const std::string& value,const std::string& filename) {
    std::ifstream ifs{filename, std::ios::binary |  std::ios::in | std::ios::out};
    if(!ifs.is_open())
        throw std::runtime_error("error file opening...\n");

    std::string buff_str;
    std::streampos pos;
    int i = 0;
    if(id == 0)
        pos = 0;
    else
        while(read_file(ifs, buff_str)) {
            pos = ifs.tellg();
            if(i == id - 1) {
                break;
            }
            i++;
        }

    std::vector<std::string> appendix;
    while(read_file(ifs, buff_str)) {
        appendix.push_back(buff_str);
    }
    ifs.close();

    std::ofstream ofs(filename, std::ios::binary | std::ios::in);
    if(!ofs.is_open())
        throw std::runtime_error("error file opening...\n");

    ofs.seekp(pos);
    char sep = '\n';
    const char* str = value.c_str();
    ofs.write(str, static_cast<unsigned int>(sizeof(char)*value.size()));
    ofs.write(reinterpret_cast<char*>(&sep), sizeof(char));
    for(const auto& itr : appendix) {
        const char *buff = itr.c_str();
        ofs.write(buff, static_cast<unsigned int>(sizeof(char)*itr.size()));
        ofs.write(reinterpret_cast<char*>(&sep), sizeof(char));
    }
    ofs.close();
}

void deserialize(forward_list<std::string>& list, const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary | std::ios::out);
    if(!ifs.is_open())
        throw std::runtime_error("error file opening...\n");

    ifs.seekg(0, std::ios::beg);
    std::string str;
    std::vector<std::string> data;
    while(read_file(ifs, str))
        list.push_back(str);
    ifs.close();
}


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
    return false;
}

template<Toutput T>
T forward_list<T>::front() {
    if(is_empty())
        throw std::string("list is empty");
    return front_node->value;
}

template<Toutput T>
T forward_list<T>::back() {
    if(is_empty())
        throw std::string("list is empty");
    return back_node->value;
}

template<Toutput T>
void forward_list<T>::push_back(T data) {
    auto back = &back_node;
    auto front = &front_node;
    auto temp = new struct node<T>(data, nullptr);
    if(!is_empty()) {
        (*back)->next = temp;
    }
    else {
        *front = temp;
    }
    *back = temp;
    size++;
}

template<Toutput T>
void forward_list<T>::push_front(T data) {
    auto back = &back_node;
    auto front = &front_node;
    auto temp = new struct node<T>(data, nullptr);
    if(!is_empty()) {
        temp->next = *front;
    }
    else {
        *back = temp;
    }
    *front = temp;
    size++;
}

template<Toutput T>
void forward_list<T>::push_node_back(struct node<T>* temp) {
    auto back = &back_node;
    if(!is_empty()) {
        (*back)->next = temp;
    }
    else {
        auto front = &front_node;
        *front = temp;
    }
    *back = temp;
    size++;
}

template<Toutput T>
void forward_list<T>::push_node_front(struct node<T>* temp) {
    auto front = &front_node;
    if(!is_empty()) {
        temp->next = *front;
    }
    else {
        auto back = &back_node;
        *back = temp;
    }
    *front = temp;
    size++;
}

template<Toutput T>
void forward_list<T>::pop_back() {
    if(is_empty())
        throw std::string("list is empty");
    if(size == 1) {
        pop_front();
        return;
    }
    auto temp = front_node;
    while (temp->next != back_node)
        temp = temp->next;
    delete back_node;
    back_node = temp;
    back_node->next = nullptr;
    size--;
}

template<Toutput T>
void forward_list<T>::pop_front() {
    if(is_empty())
        throw std::string("list is empty");
    auto front = &front_node;
    auto temp = front_node;
    *front = (*front)->next;
    delete temp;
    size--;
}

template<Toutput T>
T& forward_list<T>::operator[] (int N) {
    if(is_empty() || N >= size || N < 0) {
        throw std::string("access error");
    }
    auto temp = front_node;
    for(int i = 0; i < N; i++)
        temp = temp->next;
    return temp->value;
}

// extra methods, dont recommend to use
template<Toutput T>
struct node<T>* forward_list<T>::get_Nth(int N) {
    if(is_empty() || N >= size || N < 0) {
        throw std::string("access error");
    }
    auto temp = front_node;
    for(int i = 0; i < N; i++)
        temp = temp->next;
    return temp;
}

template<Toutput T>
struct node<T>* forward_list<T>::find(T data) {
    if(is_empty()) {
        throw std::string("list is empty");
    }
    else {
        auto temp = front_node;
        while(temp) {
            if(temp->value == data)
                return temp;
            temp = temp->next;
        }
        throw std::string("no such element");
    }
}

template class forward_list<char>;
template class forward_list<int>;
template class forward_list<double>;
template class forward_list<std::string>;
template class forward_list<MyString>;

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