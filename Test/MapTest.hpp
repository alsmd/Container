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

	void test_normal(){
		this->title("Normal");
		{
			ft::map<std::string, int> ft_list;
			std::map<std::string, int> std_list;

			ft_list["batata"] = 10;
			ft_list["mala"] = 55;
			ft_list["minhaso"] = 01523;
			ft_list["asdo"] = -123;
			ft_list["SAOKDO"] = 121;
			std_list["batata"] = 10;
			std_list["mala"] = 55;
			std_list["minhaso"] = 01523;
			std_list["asdo"] = -123;
			std_list["SAOKDO"] = 121;
			this->name("Content of ft::map must be the same as std::map")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
	}

	void test_reverse(){
		this->title("Reverse");
		{
			ft::map<std::string, int> ft_list;
			std::map<std::string, int> std_list;

			ft_list["batata"] = 10;
			ft_list["mala"] = 55;
			ft_list["minhaso"] = 01523;
			ft_list["asdo"] = -123;
			ft_list["SAOKDO"] = 121;
			std_list["batata"] = 10;
			std_list["mala"] = 55;
			std_list["minhaso"] = 01523;
			std_list["asdo"] = -123;
			std_list["SAOKDO"] = 121;
			this->name("Reverse Content of ft::map must be the same as std::map")
				->assertEqual(getReverseContent(ft_list), getReverseContent(std_list));
		}
	}
	
	void test_empty(){
		this->title("Empty");
		{
			ft::map<std::string, int> ft_list;

			this->name("empty list must return true")
				->assertEqual(ft_list.empty(), true);	
		}
		{
			ft::map<std::string, int> ft_list;

			ft_list["haha"] = 123;
			this->name("empty list must return false")
				->assertEqual(ft_list.empty(), false);	
		}
	}

	void test_size(){
		this->title("Size");
		{
			ft::map<int, int> ft_list;
			this->name("size must be 0")
				->assertEqual(ft_list.size(), 0);	
		}
		{
			ft::map<int, int> ft_list;
			for (int i = 0; i < 100; i++)
				ft_list[i] = i;
			this->name("size must be 100")
				->assertEqual(ft_list.size(), 100);	
		}
	}


	template<typename Key, typename T>
	std::string	getContent(ft::map<Key, T> list){
		std::stringstream	s;

		for (auto i : list)
			s << "{" << i.first << ":"<< i.second << "},";
		return (s.str());
	}

	template<typename Key, typename T>
	std::string	getReverseContent(ft::map<Key, T> list){
		std::stringstream	s;

		for (auto i = list.rbegin(); i != list.rend(); i++)
			s << "{" << i->first << ":"<< i->second << "},";
		return (s.str());
	}

	template<typename Key, typename T>
	std::string	getContent(std::map<Key, T> list){
		std::stringstream	s;

		for (auto i : list)
			s << "{" << i.first << ":"<< i.second << "},";
		return (s.str());
	}

	template<typename Key, typename T>
	std::string	getReverseContent(std::map<Key, T> list){
		std::stringstream	s;

		for (auto i = list.rbegin(); i != list.rend(); i++)
			s << "{" << i->first << ":"<< i->second << "},";
		return (s.str());
	}

};
