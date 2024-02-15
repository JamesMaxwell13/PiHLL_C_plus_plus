#include <iostream>
#include <vector>

template <typename T>
concept Toutput = requires (T test) {
{ std::cout << test } -> std::convertible_to<std::ostream&>;
};

template <Toutput T>
class A {
public:
    T data;
    A(T buff) {
        data = buff;
    };
    void print() {
        std::cout << data;
    }
};

template<> void A<int>::print() {
    std::cout << "int  " << data;
}

int main() {
    char* str = new char[256];
    std::cin.getline(str, 256);

    return 0;
}


//forward_list mylist(99);
//mylist.push_front(11);
//mylist.push_back(48);
//std::cout << mylist << std::endl;
//mylist.pop_front();
//auto* temp = mylist.find(99);
//std::cout << temp << " next - " << temp->next << std::endl;
//for(int i = 0; i < 6; i++)
//mylist.pop_back();
//std::cout << mylist;