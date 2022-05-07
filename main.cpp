// /* #include "vector.hpp"
// #include <vector>

// int main()
// {
// 	/* ft::vector<int>		list1(4, -1);
// 	// ft::vector<int>		list2(4, 9);
	
// 	list1.erase(list1.begin(), --(list1.end()));
// 	for (auto i = list1.begin(); i != list1.end(); i++)
// 	{
// 		std::cout << *i << std::endl;
// 	}
// 	std::cout << "------------------\n";
// 	std::cout << list1.capacity() << "\n";
// 	std::cout << list1.size() << "\n"; */
	
// 	/* list1.resize(8);
// 	for (auto i = list1.begin(); i != list1.end(); i++)
// 	{
// 		std::cout << *i << std::endl;
// 	}
// 	std::cout << "------------------\n";
// 	std::cout << list1.capacity() << "\n";
// 	std::cout << list1.size() << "\n"; */
// 	// list1.reserve(15);
// 	/* auto i = list1.begin();
// 	list1.insert(i, list2.begin(), (list2.end()));

// 	for (auto i = list1.begin(); i != list1.end(); i++)
// 	{
// 		std::cout << *i << std::endl;
// 	}

//  */

// 	/* try{
// 		list.insert(list.begin() + 10, 1);

// 	}catch(std::exception e){
// 		std::cout << e.what() << std::endl;
// 	} */

// 	/* auto i = list.begin();
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	list.insert(i, 5, 6);
// 	for (auto i = list.begin(); i != list.end(); i++)
// 	{
// 		std::cout << *i << std::endl;
// 	} */
// 	/* value = -1;
// 	for (auto i = lista.begin(); i != lista.end(); i++)
// 	{
// 		std::cout << *i << std::endl;
// 	} */
// 	/* lista.reserve(11);
// 	for (ft::vector<int>::iterator i = lista.begin(); i != lista.end(); i++)
// 	{
// 		std::cout << *i << std::endl;
// 	}
// 	std::cout << "size: \n" << lista.size();
// 	std::cout << "capacity: \n" << lista.capacity();
// 	lista.insert(lista.begin(), -1);
// 	std::cout << "---------------------\n";
// 	for (ft::vector<int>::iterator i = lista.begin(); i != lista.end(); i++)
// 	{
// 		std::cout << *i << std::endl;
// 	}
// 	ft::vector<int>::iterator i = lista.end();
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	i++;
// 	lista.insert(i, -1);
// 	std::cout << "size: \n" << lista.size();
// 	std::cout << "capacity: \n" << lista.capacity();
// 	std::cout << "---------------------\n";
// 	for (ft::vector<int>::iterator i = lista.begin(); i != lista.end(); i++)
// 	{
// 		std::cout << *i << std::endl;
// 	}
// 	std::cout << "size: \n" << lista.size();
// 	std::cout << "capacity: \n" << lista.capacity(); */
// 	/* std::cout << "content: \n";
// 	std::cout << "size: \n";
// 	std::cout << lista.size() << std::endl;
// 	std::cout << "capacity: \n";
// 	std::cout << lista.capacity() << std::endl;

// 	lista.reserve(20);

// 	std::cout << "content: \n";
// 	for (ft::vector<int>::iterator i = lista.begin(); i != lista.end(); i++)
// 	{
// 		std::cout << *i << std::endl;
// 	}
// 	std::cout << "size: \n";
// 	std::cout << lista.size() << std::endl;
// 	std::cout << "capacity: \n";
// 	std::cout << lista.capacity() << std::endl; */
// 	// std::cout << lista.capacity() << std::endl;
// /* 	std::vector<int>::iterator i = ha.end();
// 	i++;
// 	ha.insert(i, 1);*/
// /* 	std::cout << ha.capacity()<< "\n";
// 	ha.reserve(10);
// 	std::cout << ha.capacity()<< "\n";
// 	for (auto i : ha)
// 		std::cout << i << "\n";  */
// 		// ha.max_size()
// } */


#include <catch2/catch_test_macros.hpp>

unsigned int Factorial( unsigned int number ) {
	return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
	REQUIRE( Factorial(1) == 1 );
	REQUIRE( Factorial(2) == 2 );
	REQUIRE( Factorial(3) == 6 );
	REQUIRE( Factorial(10) == 3628800 );
}

