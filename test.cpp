#include <map>
#include <iostream>
#include "./Container/map.hpp"
#include <ctime>
#include <sstream>
#include <sys/time.h>

int main(){
   ft::map<int, int> list;


   list[1] = 1;
   list[2] = 2;
   list[3] = 3;
   list[4] = 4;
   list[5] = 5;
   list[6] = 6;
   list[7] = 7;
   auto i  = list.end();
   i--;
   list.erase(1);
   list.erase(2);
   list.erase(3);
   list.erase(4);
   list.erase(5);
   list.erase(6);
   std::cout << i->first << " " << i->second << "\n";
}