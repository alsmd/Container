#pragma once
#include <Test.hpp>
#include "vector.hpp"
#include <vector>
#include <sstream>

class VectorTest : doc::Test
{
private:
public:
	VectorTest(){
	}
	~VectorTest(){

	}

	void	test_size(){
		this->title("Size");
		{
			ft::vector<int> ft_list(5);
			this->name("Size must return 5 when list inicializes with 5")->assertEqual(ft_list.size(), 5);
		}
		{
			ft::vector<int> ft_list(10);
			this->name("Size must return 10 when list inicializes with 10")->assertEqual(ft_list.size(), 10);
		}
	}

	void	test_capacity(){
		this->title("Capacity");
		{
			ft::vector<int> ft_list(60);
			this->name("Capaciy must return 60 when list iniciales with 60 elements")->assertEqual(ft_list.capacity(), 60);
		}
	}

	void test_reserve(){
		this->title("Reserve");
		{
			ft::vector<int> ft_list;
			ft_list.reserve(30);
			this->name("Empty list reserving 30 must have a capacity of 30")->assertEqual(ft_list.capacity(), 30);
		}
		{
			ft::vector<int> ft_list(20);
			ft_list.reserve(10);
			this->name("list with 20 slots reserving 10 must have a capacity of 20")->assertEqual(ft_list.capacity(), 20);
		}
	}

	void test_empty(){
		this->title("Empty");
		{
			ft::vector<int> ft_list;
			this->name("Empty List must return true")->assertEqual(ft_list.empty(), true);
		}
		{
			ft::vector<int> ft_list(1);
			this->name("List with elements must return false")->assertEqual(ft_list.empty(), false);
		}
	}

	void test_clear(){
		this->title("Clear");
		{
			ft::vector<int> ft_list(30, 2);
			ft_list.clear();
			this->name("List with elements after clear size must be 0")->assertEqual(ft_list.size(), 0);
		}
	}

	void test_reverse_iterator(){
		this->title("Reverse Iterator");
		{
			std::stringstream		std_buffer;
			std::stringstream		ft_buffer;
			ft::vector<int>			ft_list(5, 2);
			std::vector<int>		std_list(5, 2);


			int value = 0;
			for (std::vector<int>::iterator i = std_list.begin(); i != std_list.end(); i++, value++)
				*i = value;
			value = 0;
			for (ft::vector<int>::iterator i = ft_list.begin(); i != ft_list.end(); i++, value++)
				*i = value;

			for (std::vector<int>::reverse_iterator i = std_list.rbegin(); i != std_list.rend(); i++)
				std_buffer << *(i.base());
			for (ft::vector<int>::reverse_iterator i = ft_list.rbegin(); i != ft_list.rend(); i++)
				ft_buffer << *(i.base());
			this->name("Reverse iterator ft::vector output has to be equal std::vector output list 0 1 2 3 4")->assertEqual(std_buffer.str(), ft_buffer.str());
			std_buffer.str(std::string());
			ft_buffer.str(std::string());
		}

		{
			std::stringstream		std_buffer;
			std::stringstream		ft_buffer;
			ft::vector<int>			ft_list(5, 2);
			std::vector<int>		std_list(5, 2);

			ft_list.insert(ft_list.begin() + 2, 1);
			std_list.insert(std_list.begin() + 2, 1);
			for (std::vector<int>::reverse_iterator i = std_list.rbegin(); i != std_list.rend(); i++){
				std::cout << *(i.base()) << "\n";
				std_buffer << *(i.base());
			}
			std::cout << "\n";
			for (ft::vector<int>::reverse_iterator i = ft_list.rbegin(); i != ft_list.rend(); i++)
				ft_buffer << *(i.base());
			
			std::cout << std_buffer.str() << "\n";
			// this->name("Reverse iterator ft::vector output has to be equal std::vector output list 0 1 2 3 4")->assertEqual(std_buffer.str(), ft_buffer.str());
		}
	}
};
