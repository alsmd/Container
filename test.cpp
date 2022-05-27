#include <map>
#include <iostream>
#include "./Container/map.hpp"

int main(){
    ft::map<int, int> list;

    list[9] = 9;
    list[8] = 8;

    ft::map<int, int>::reverse_iterator i = list.rend();

    std::cout << i->first << std::endl;
    std::cout << i.base()->first << std::endl;

}