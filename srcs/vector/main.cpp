#include "vector.hpp"
#include "../iterator/iterator.hpp"
#include <vector>


void	print_vector(ft::vector<int> vec) {
	// std::cout << vec.size() << std::endl;
	for (int i = 0; i < (int)vec.size(); i++)
		std::cout << vec[i] << std::endl;
}

void	print_vector(std::vector<int> vec) {
	for (int i = 0; i < (int)vec.size(); i++)
		std::cout << vec[i] << std::endl;
}

int	main(void) {
	ft::vector<int>	test;
	// std::vector<int> tt;

	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	test.push_back(6);
	test.push_back(7);
	test.push_back(8);

	// tt.push_back(5);
	// tt.push_back(10);
	// tt.push_back(15);
	// tt.push_back(20);
	// tt.push_back(25);
	// tt.push_back(30);
	// tt.push_back(35);
	// tt.push_back(40);

	// std::vector<int>::iterator ite;

	// ite = tt.insert(tt.begin(), 99);
	// tt.insert(ite, 30);
	// tt.insert(ite, 34);
	// print_vector(tt);
	// std::cout << "===" << std::endl;
	ft::vector<int>::iterator it = test.end();
	// ft::vector<int>::iterator ite;
	// print_vector(test);
	// std::cout << "===" << std::endl;
	// std::cout << test.size() << std::endl;
	// it = test.insert(test.begin(), 99);
	
	// test.insert(it, 98);
	// ite = test.erase(it);
	test.insert(it, 55);
	print_vector(test);
	// test.erase(test.begin(), test.end());
	// test.insert(ite, 55);
	std::cout << "1" << std::endl;
	// test.insert(it, test.begin(), test.end());
	// print_vector(test);
	// std::cout << "===" << std::endl;
	test.push_back(1);
	test.insert(test.begin(), 5, 2);
	// test.assign(10, 3);
	std::cout << "2" << std::endl;
	ft::vector<int>	r;

	r.assign(test.begin(), test.end());
	std::cout << "3" << std::endl;
	// test.insert(it, 55);
	// print_vector(test);
	print_vector(r);
}