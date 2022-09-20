#include "vector.hpp"
#include "iterator.hpp"
#include <vector>


void	print_vector(ft::vector<int> vec) {
	// std::cout << "f" << std::endl;
	std::cout << "_Used : " << vec.size() << std::endl << "-=-=-=-" << std::endl;
	for (int i = 0, max = (int)vec.size(); i < max; i++) {
		std::cout << vec[i] << std::endl;
	}
	// std::cout << "f" << std::endl;
	// std::cout << vec.size() << std::endl << "=-=-=-=" << std::endl;

	// ft::vector<int>::iterator	it = vec.begin();
	// ft::vector<int>::iterator	ite = vec.end();
	// for ( ; it != ite; it++)
	// 	std::cout << *it << std::endl;
}

int	main(void) {
	ft::vector<int>	og;
	ft::vector<int>	test;
	
	for (int i = 0; i < 10 ; i++)
		og.push_back(i);
	test.assign(og.begin(), og.end());
	std::cout << "Capacity after assign : " << test.capacity() << std::endl;
	std::cout << "Size after assign in range : " << test.size() << std::endl;
	test.insert(test.end(), 42);
	print_vector(test);
	test.insert(test.begin(), 3, 99);
	// std::cout << "Size after insert in begin() : " << test.size() << " Capacity after insert in begin() : " << test.capacity() << std::endl;
	// std::cout << "Size after erase in range to begin() to end(): " << test.size() << std::endl;
	// test.erase(test.begin() + 5, test.end());
	std::cout << "Used : " << test.size() << " " << test.capacity() << std::endl;
	print_vector(test);	
}