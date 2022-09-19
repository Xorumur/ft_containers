#include "vector.hpp"
#include "iterator.hpp"
#include <vector>


void	print_vector(ft::vector<int> vec) {
	for (int i = 0; i < (int)vec.size(); i++) {
		std::cout << vec[i] << std::endl;
	}
	std::cout << "=-=-=-=" << std::endl;
}

int	main(void) {
	ft::vector<int>	og;
	ft::vector<int>	test;
	
	for (int i = 0; i < 10 ; i++)
		og.push_back(i);
	test.assign(og.begin(), og.end());
	std::cout << "Size after assign in range : " << test.size() << std::endl;
	print_vector(test);
	test.erase(test.begin());
	// test.assign(2, 4);
	std::cout << "Size after assign in fill : " << test.size() << std::endl;
	print_vector(test);
	std::cout << test.at(1) << std::endl;
	
}