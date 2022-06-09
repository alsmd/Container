#pragma once
#include <Test.hpp>
#include "../Container/vector.hpp"
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
			this->name("Size must be 5 when list inicializes with 5 elements")->assertEqual(ft_list.size(), 5);
		}
		{
			ft::vector<int> ft_list(10);
			this->name("Size must be 10 when list inicializes with 10 elements")->assertEqual(ft_list.size(), 10);
		}
		{
			ft::vector<int> ft_list;
			this->name("Size must be 0 when list inicializes with 0 elements")->assertEqual(ft_list.size(), 0);
		}
	}

	void	test_constroctor(){
		this->title("Constructor and Equal ");

		{
			ft::vector<int>	ft_list;
			bool			res = (ft_list.capacity() == 0 && ft_list.size() == 0);
			this->name("Empty Constructor size and capacity must be 0")->assertEqual(res, true);
		}

		{
			ft::vector<int>	ft_list(5, 3);
			this->name("Constructor list(5, 3) the list must to have 5 elements with value 3")
				->assertEqual(this->getContent(ft_list), std::string("33333"));
		}

		{
			ft::vector<int>	other_list(3, 9);
			ft::vector<int>	ft_list(other_list.begin(), other_list.end());
			this->name("Constructor list = (other.begin(), other.end()) the list's content must be 999")
				->assertEqual(this->getContent(ft_list), std::string("999"));
		}

		{
			ft::vector<int>	other_list(2, 9);
			ft::vector<int>	ft_list(other_list);
			this->name("Constructor list(other(2,9)) list must contain 99")
				->assertEqual(this->getContent(ft_list), std::string("99"));
		}

		{
			ft::vector<int>	other_list(6, 2);
			ft::vector<int>	ft_list;
			
			ft_list = other_list;
			this->name("Constructor list = other_list(6,3) list must contain 222222")
				->assertEqual(this->getContent(ft_list), std::string("222222"));
		}
	}
	
	void	test_iterator(){
		this->title("Iterator");

		{
			std::stringstream ft_buffer;	
			std::stringstream std_buffer;	
			int size = 5;
			int array[] = {1, 2, 3, 4, 5};
			ft::vector<int> ft_list(array, array + 5);
			for (auto i : ft_list){
				ft_buffer << i ;
			}
			std::vector<int> std_list(array, array + 5);
			for (auto i : std_list){
				std_buffer << i ;
			}
			this->name("Iterator vector{1,2,3,4,5} output has to be 12345")
				->assertEqual(ft_buffer.str(), std_buffer.str());
		}
		{
			int size = 3;
			char *array[] = {"flavio", "banana", "maça"};
			ft::vector<std::string> ft_list(array, array + size);
			std::vector<std::string> std_list(array, array + size);
			this->name("Iterator vector{'flavio','banana','maça'} output has to be flaviobananamaça")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
	}


	void	test_resize(){
		//considerações:
		//dobra a capacidade e ve se o novo numero de elementos cabe nela
		//caso o dobro da capacidade não for suficiente ele ira ter como capacidade o novo numero de elementos
		//todos novos elementos serão inicializados com val
		//caso o novo valor seja menor do que o tamanho atual, os elementos excedentes serão apagados mas a capacidade se mantem
		this->title("Resize");
		{
			ft::vector<int>	list;

			list.resize(5);
			this->name("Resizes 5 in a empty list new size has to be 5")->assertEqual(list.size(), 5);
		}
		{
			ft::vector<int>	list;

			list.resize(5);
			this->name("Resizes 5 in a empty list new capacity has to be 5")->assertEqual(list.capacity(), 5);
		}
		{
			ft::vector<int>	list(9, -1);

			list.resize(5);
			this->name("Resizes 5 in a list with 9 elements new size has to be 5")->assertEqual(list.size(), 5);
		}
		{
			ft::vector<int>	list(9, -1);

			list.resize(5);
			this->name("Resizes 5 in a list with 9 elements new capacity has to keep been 9")->assertEqual(list.capacity(), 9);
		}
		{
			std::stringstream	buffer;
			ft::vector<int>		list(9, 2);

			list.resize(5);
			for (ft::vector<int>::iterator i = list.begin(); i != list.end(); i++)
				buffer << *i;
			this->name("Resizes 5 in a list with 9 the the leftover elements has to keep the same")->assertEqual(std::string(buffer.str()), std::string("22222"));
		}
		{
			std::stringstream	buffer;
			ft::vector<int>		list(5, 2);

			list.resize(9, 1);
			for (ft::vector<int>::iterator i = list.begin(); i != list.end(); i++)
				buffer << *i;
			this->name("Resizes 9 in a list with 5 the the surplus elements has to be initialized as the value passed as second parameter")->assertEqual(std::string(buffer.str()), std::string("222221111"));
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
				std_buffer << *(i.base() - 1);
			for (ft::vector<int>::reverse_iterator i = ft_list.rbegin(); i != ft_list.rend(); i++)
				ft_buffer << *(i.base() - 1);
			this->name("Reverse iterator ft::vector output has to be equal std::vector output list 0 1 2 3 4")->assertEqual(std_buffer.str(), ft_buffer.str());
		}

		{
			std::stringstream		std_buffer;
			std::stringstream		ft_buffer;
			ft::vector<int>			ft_list(5, 2);
			std::vector<int>		std_list(5, 2);

			ft_list.insert(ft_list.begin() + 2, 1);
			std_list.insert(std_list.begin() + 2, 1);
			for (std::vector<int>::reverse_iterator i = std_list.rbegin(); i != std_list.rend(); i++){
				std_buffer << *(i.base() - 1);
			}
			for (ft::vector<int>::reverse_iterator i = ft_list.rbegin(); i != ft_list.rend(); i++)
				ft_buffer << *(i.base() - 1);
			
			this->name("Reverse iterator ft::vector output has to be equal std::vector output list 2 2 5 2 2 2")->assertEqual(std_buffer.str(), ft_buffer.str());
		}

		{
			std::stringstream		std_buffer;
			std::stringstream		ft_buffer;
			ft::vector<int>			ft_list(5, 2);
			std::vector<int>		std_list(5, 2);

			ft_list.insert(ft_list.begin() + 2, 1);
			std_list.insert(std_list.begin() + 2, 1);
			std::vector<int>::reverse_iterator std_i = std_list.rbegin();
			for (int index = 0; index < 5; index++){
				std_buffer << std_i[index];
			}
			ft::vector<int>::reverse_iterator ft_i = ft_list.rbegin();
			for (int index = 0; index < 5; index++){
				ft_buffer << ft_i[index];
			}
			
			this->name("Reverse iterator testing with index: ft_list[] == std_list[]")->assertEqual(std_buffer.str(), ft_buffer.str());
		}
	}


	void test_operator_keys(){
		this->title("Operator []");
		{
			char *array[] = {"flavio", "banana", "maça"};
			int	size = 3;
			ft::vector<std::string> ft_list(array, array + size);
			this->name("Vector {'flavio', 'banana', 'maça'} [2] must return maça")
				->assertEqual(ft_list[2], "maça");
		}

		{
			int array[] = {1, 55, 2};
			int	size = 3;
			ft::vector<int> ft_list(array, array + size);
			this->name("Vector {1, 55, 2} [0] must return 1")
				->assertEqual(ft_list[0], 1);
		}
	}


	void test_at(){
		this->title("At");
		{
			char *array[] = {"flavio", "banana", "maça"};
			int	size = 3;
			ft::vector<std::string> ft_list(array, array + size);
			this->name("Vector {'flavio', 'banana', 'maça'} [2] must return maça")
				->assertEqual(ft_list.at(2), "maça");
		}

		{
			int array[] = {1, 55, 2};
			int	size = 3;
			ft::vector<int> ft_list(array, array + size);
			this->name("Vector {1, 55, 2} at(0) must return 1")
				->assertEqual(ft_list.at(0), 1);
		}
	}


	void test_front(){
		this->title("Front");
		{
			int array[] = {1, 55, 2};
			int	size = 3;
			ft::vector<int> ft_list(array, array + size);
			this->name("Vector {1, 55, 2} front must return 1")
				->assertEqual(ft_list.front(), 1);
		}
	}

	void test_back(){
		this->title("Back");
		{
			int array[] = {1, 55, 2};
			int	size = 3;
			ft::vector<int> ft_list(array, array + size);
			this->name("Vector {1, 55, 2} back must return 2")
				->assertEqual(ft_list.back(), 2);
		}
	}

	void test_data(){
		this->title("Data");
		{
			int array[] = {1, 55, 2};
			int	size = 3;
			ft::vector<int> ft_list(array, array + size);
			this->name("Vector {1, 55, 2} data must return &begin")
				->assertEqual(ft_list.data(), &(*ft_list.begin()));
		}
	}

	void test_assign(){
		this->title("Assign");
		{
			int array[] = {1, 55, 2};
			int	size = 3;
			ft::vector<int> ft_list(array, array + size);
			std::vector<int> std_list(array, array + size);
			ft_list.assign(55, -157);
			std_list.assign(55, -157);
			this->name("test assign(55, -157), content has to be the same as the original")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}

		{
			int array[] = {1, 55, 2};
			int array2[] = {157, 123, 12309 , 123,0 ,1023,01 ,3012,300124, 123};
			int	size = 3;
			int	size2 = 10;
			ft::vector<int> ft_list(array, array + size);
			std::vector<int> std_list(array, array + size);
			ft_list.assign(array2, array2 + 10);
			std_list.assign(array2, array2 + 10);
			this->name("test assign(iterator, iterator), content has to be the same as the original")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
	}


	void test_push_back(){
		this->title("Push Back");
		{
			ft::vector<std::string> ft_list;
			std::vector<std::string> std_list;
			ft_list.push_back("ola");
			ft_list.push_back("flavio");
			ft_list.push_back("como");
			ft_list.push_back("estais");
			ft_list.push_back("portugal");
			ft_list.push_back("espanha");
			ft_list.push_back("amarecia");
			ft_list.push_back("super");
			ft_list.push_back("the");
			ft_list.push_back("boys");
			std_list.push_back("ola");
			std_list.push_back("flavio");
			std_list.push_back("como");
			std_list.push_back("estais");
			std_list.push_back("portugal");
			std_list.push_back("espanha");
			std_list.push_back("amarecia");
			std_list.push_back("super");
			std_list.push_back("the");
			std_list.push_back("boys");
			this->name("push_back function has to be similar to original")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
	}

	void test_pop_back(){
		this->title("Pop Back");
		{
			ft::vector<int> ft_list;
			std::vector<int> std_list;
			for (int i =0; i < 100; i++){
				ft_list.push_back(i * 32);
				std_list.push_back(i * 32);
			}
			for (int i =0; i < 5; i++){
				ft_list.pop_back();
				std_list.pop_back();
			}
			this->name("pop_back function has to be similar to original")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
	}


	void test_insert(){
		this->title("Insert");
		//insert(iterator, value)
		{
			ft::vector<int> ft_list(2, -1);
			std::vector<int> std_list(2, -1);
			ft_list.insert(ft_list.begin(), -144);
			std_list.insert(std_list.begin(), -144);
			this->name("insert(iterator, value) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
		{
			ft::vector<int> ft_list(5, -1);
			std::vector<int> std_list(5, -1);
			ft_list.insert(ft_list.begin() + 2, -192);
			std_list.insert(std_list.begin() + 2, -192);
			this->name("insert(iterator, value) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
		{
			ft::vector<int> ft_list(5, -1);
			std::vector<int> std_list(5, -1);
			ft_list.insert(ft_list.end(), -192);
			std_list.insert(std_list.end(), -192);
			this->name("insert(iterator, value) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
		//insert(iterator, count, value)
		{
			ft::vector<int> ft_list(2, -1);
			std::vector<int> std_list(2, -1);
			ft_list.insert(ft_list.begin(), 22, -144);
			std_list.insert(std_list.begin(), 22, -144);
			this->name("insert(iterator, count, value) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
		{
			ft::vector<int> ft_list(5, -1);
			std::vector<int> std_list(5, -1);
			ft_list.insert(ft_list.begin() + 2, 66, -192);
			std_list.insert(std_list.begin() + 2, 66, -192);
			this->name("insert(iterator, count,value) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
		{
			ft::vector<int> ft_list(5, -1);
			std::vector<int> std_list(5, -1);
			ft_list.insert(ft_list.end(), 11, -192);
			std_list.insert(std_list.end(), 11,-192);
			this->name("insert(iterator, count, value) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
		//insert(pos, first, end)
		{
			int array[] = {157, 123, 12309 , 123,0 ,1023,01 ,3012,300124, 123};
			int size = 10;
			ft::vector<int> ft_list(5, -1);
			std::vector<int> std_list(5, -1);
			ft_list.insert(ft_list.begin(), array,array + size);
			std_list.insert(std_list.begin(), array,array + size);
			this->name("insert(pos, first, end) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}

		{
			int array[] = {157, 123, 12309 , 123,0 ,1023,01 ,3012,300124, 123};
			int size = 10;
			ft::vector<int> ft_list(5, -1);
			std::vector<int> std_list(5, -1);
			ft_list.insert(ft_list.end(), array,array + size);
			std_list.insert(std_list.end(), array,array + size);
			this->name("insert(pos, first, end) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}

		{
			int array[] = {157, 123, 12309 , 123,0 ,1023,01 ,3012,300124, 123};
			int size = 10;
			ft::vector<int> ft_list(5, -1);
			std::vector<int> std_list(5, -1);
			ft_list.insert(ft_list.begin() + 3, array,array + size);
			std_list.insert(std_list.begin() + 3, array,array + size);
			this->name("insert(pos, first, end) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
	}

	void test_erase(){
		this->title("Erase");
		{
			ft::vector<int> ft_list(5, -1);
			std::vector<int> std_list(5, -1);
			ft_list.erase(ft_list.begin());
			std_list.erase(std_list.begin());
			this->name("erase(pos) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
		{
			ft::vector<int> ft_list(100, -1);
			std::vector<int> std_list(100, -1);
			ft_list.erase(ft_list.begin() + 50);
			std_list.erase(std_list.begin() + 50);
			this->name("erase(pos) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
		{
			ft::vector<int> ft_list(100, -1);
			std::vector<int> std_list(100, -1);
			ft_list.erase(ft_list.begin(), ft_list.end());
			std_list.erase(std_list.begin(), std_list.end());
			this->name("erase(iterator, iterator) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}

		{
			ft::vector<int> ft_list(100, -1);
			std::vector<int> std_list(100, -1);
			ft_list.erase(ft_list.begin(), ft_list.begin() + 25);
			std_list.erase(std_list.begin(), std_list.begin() + 25);
			this->name("erase(iterator, iterator) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}

		{
			ft::vector<int> ft_list(100, -1);
			std::vector<int> std_list(100, -1);
			ft_list.erase(ft_list.begin() + 25, ft_list.begin() + 50);
			std_list.erase(std_list.begin() + 25, std_list.begin() + 50);
			this->name("erase(iterator, iterator) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
		}
	}

	void test_swap(){
		this->title("Swap");
		{
			int array[] = {157, 123, 12309 , 123,0 ,1023,01 ,3012,300124, 123};
			int size = 10;
			ft::vector<int> ft_list(5, -1);
			ft::vector<int> ft_list2(array, array + size);
			std::vector<int> std_list(5, -1);
			std::vector<int> std_list2(array, array + size);

			ft_list.swap(ft_list2);
			std_list.swap(std_list2);
			this->name("swap(&vector) has to be similar to std function")
				->assertEqual(getContent(ft_list), getContent(std_list));
			this->name("swap(&vector) has to be similar to std function")
				->assertEqual(getContent(ft_list2), getContent(std_list2));
		}
	}


	void test_clear(){
		this->title("Clear");
		{
			ft::vector<int> ft_list(5, -1);

			ft_list.clear();
			this->name("clear must empty all elements")
				->assertEqual(getContent(ft_list), "");
		}
		{
			ft::vector<int> ft_list(5, -1);

			ft_list.clear();
			this->name("clear must 'set' size to 0")
				->assertEqual(ft_list.size(), 0);
		}
	}
	template<typename T>
	std::string	getContent(ft::vector<T> list){
		std::stringstream	s;

		for (auto i : list)
			s << i;
		return (s.str());
	}

	template<typename T>
	std::string	getContent(std::vector<T> list){
		std::stringstream	s;

		for (auto i : list)
			s << i;
		return (s.str());
	}


};
