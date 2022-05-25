#include <iostream>
// #include <memory>
// #include <vector>
// #include "./Container/vector.hpp"
#include "./Container/map.hpp"
#include <string>
#include <map>
#include <iostream>


int main(){
	/* ft::map<int, int> ftMap;

    ftMap[5] = 50;
    ftMap[3] = 30;
    ftMap[1] = 10;
    ftMap[8] = 80;
    ftMap[9] = 90;
    ftMap[7] = 70;
    ftMap[4] = 40;
    ftMap[6] = 60;
    ftMap[0] = 0;
    ftMap[2] = 20;

    ft::map<int, int>::iterator itft = ftMap.begin();
    std::cout <<"----------------" << std::endl;
    std::cout <<"  initial list" << std::endl;
    std::cout <<"----------------" << std::endl;

    for(; itft != ftMap.end(); itft++){
        std::cout << itft->first <<" "<< itft->second << std::endl;
    }        
    std::cout <<"----------------" << std::endl;
    std::cout <<"   erase (key)" << std::endl;
    std::cout <<"----------------" << std::endl;

    ft::pair<const int, int> val(22, 22);
    ftMap.erase(7);
    std::cout <<"|   erase (7)  |" << std::endl;

    std::cout <<"----------------" << std::endl;
    std::cout <<"     result" << std::endl;
    std::cout <<"----------------" << std::endl;
    itft = ftMap.begin();
    for(; itft != ftMap.end(); itft++){
        std::cout << itft->first <<" "<< itft->second << std::endl;
    } */
    ft::map<int, int> map;
    
    map[1] = 10;
    map[2] = 20;
    map[3] = 30;
    /* for (ft::map<int, int>::iterator i = map.begin(); i != map.end(); i++){
        std::cout << i->first << "\n";
    } */
    map.clear();
   /*  std::cout << map[1] << "\n";
    std::cout << map[2] << "\n";
    std::cout << map[3] << "\n"; */
	return 0;
}