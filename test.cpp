#include <map>
#include <iostream>
#include "./Container/map.hpp"
#include <ctime>
#include <sstream>
#include <sys/time.h>

int main(){
   /* {
        struct timeval time_now{};   
        gettimeofday(&time_now, nullptr);   
        time_t start = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
        
        std::stringstream buf;
        // std::time_t start = std::time(nullptr);


        std::map<int, int> ftMap;

        std::srand(893360402);
        for (unsigned int i = 1; i < 1000000 ; i++){
            ftMap[i] = i * 3; 
        }


        for (std::map<int, int>::reverse_iterator std_itMap = ftMap.rbegin(); std_itMap != ftMap.rend(); std_itMap++)
            std_itMap->first;
        gettimeofday(&time_now, nullptr);   
        time_t finish = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);

        std::cout << start << "\n" << finish << std::endl;
        std::cout <<"std: "<<  finish - start << std::endl;
    } */

    {
        struct timeval time_now{};   
        gettimeofday(&time_now, nullptr);   
        time_t start = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
        
        ft::map<int, int> ftMap;
        for (unsigned int i = 1; i < 100 ; i++){
            ftMap[i] = i * 3; 
        }
        ft::map<int, int>::iterator std_itMap = ftMap.end();
        for (; std_itMap != ftMap.begin(); std_itMap--){
            if (std_itMap != ftMap.end())
                std::cout << std_itMap->first << "\n";
        }
        gettimeofday(&time_now, nullptr);   
        time_t finish = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);

        std::cout << start << "\n" << finish << std::endl;
        std::cout <<"ft: "<<  finish - start << std::endl;
    }

   /*  list[9] = 9;
    list[8] = 8; */

   /*  ft::map<int, int>::reverse_iterator i = list.rrbegin();

    std::cout << i->first << std::endl;
    i++;

    std::cout << i->first << std::endl;

    i++;
    std::cout << i->first << std::endl; */
    /* i++;
    std::cout << i->first << std::endl;
     i++;
    std::cout << i->first << std::endl;
     i++;
    std::cout << i->first << std::endl;
     i++;
    std::cout << i->first << std::endl;
     i++;
    std::cout << i->first << std::endl;
     i++;
    std::cout << i->first << std::endl; */

/* 
    ft::map<int, int> ftlist;

    ftlist[9] = 9;
    ftlist[8] = 8;

    ft::map<int, int>::reverse_iterator ft_i = ftlist.rrbegin();
    std::cout << ft_i->first << std::endl; */

}