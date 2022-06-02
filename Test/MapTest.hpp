#pragma once
#include <Test.hpp>
#include "../Container/map.hpp"
#include <map>
#include <sstream>

class MapTest : doc::Test
{
private:
public:
	MapTest(){
	}
	~MapTest(){

	}
	
	void test_iterator(){
		this->title("Iterator");
		{
			std::map<int, int>	std_list;
			ft::map<int, int>			ft_list;
			std::stringstream					std_buffer;
			std::stringstream					ft_buffer;

			//ft
			ft_list[1] = 10309;
			ft_list[32] = 1321;
			ft_list[34] = 1;
			ft_list[0] = 1234;
			ft_list[22] = 1134;
			//std
			std_list[1] = 10309;
			std_list[32] = 1321;
			std_list[34] = 1;
			std_list[0] = 1234;
			std_list[22] = 1134;
			for (std::map<int, int>::iterator i = std_list.begin(); i != std_list.end(); i++)
				std_buffer << i->first << i->second;
			for (ft::map<int, int>::iterator i = ft_list.begin(); i != ft_list.end(); i++)
				ft_buffer << i->first << i->second;
			this->name("Testando iterator")
				->assertEqual(std_buffer.str(), ft_buffer.str());
		}

		{
			std::map<std::string, int>	std_list;
			ft::map<std::string, int>			ft_list;
			std::stringstream					std_buffer;
			std::stringstream					ft_buffer;

			//ft
			ft_list["1"] = 10309;
			ft_list["32"] = 1321;
			ft_list["34"] = 1;
			ft_list["0"] = 1234;
			ft_list["22"] = 1134;
			//std
			std_list["1"] = 10309;
			std_list["32"] = 1321;
			std_list["34"] = 1;
			std_list["0"] = 1234;
			std_list["22"] = 1134;
			for (std::map<int, int>::iterator i = std_list.begin(); i != std_list.end(); i++)
				std_buffer << i->first << i->second;
			for (ft::map<int, int>::iterator i = ft_list.begin(); i != ft_list.end(); i++)
				ft_buffer << i->first << i->second;
			this->name("Testando iterator")
				->assertEqual(std_buffer.str(), ft_buffer.str());
		}
	}

};
