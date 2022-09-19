#include "vector.hpp"
#include "../iterator/iterator.hpp"
#include <vector>


void	print_vector(ft::vector<int> vec) {
	for (int i = 0; i < (int)vec.size(); i++) {
		std::cout << vec[i] << std::endl;
	}
}

// void	print_vector(std::vector<int> vec) {
// 	if (vec.size() == 0) {
// 		std::cout << "There is nothing in htis vector" << std::endl;
// 		return ;
// 	}
// 	for (int i = 0; i < (int)vec.size(); i++) {
// 		std::cout << "Here ? " << std::endl;
// 		std::cout << vec[i] << std::endl;
// 	}
// }

int	main(void) {
	ft::vector<int>	test;

	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	test.push_back(6);
	test.push_back(7);
	test.push_back(8);

	ft::vector<int>::iterator it = test.end();
	test.insert(it, 55);
	std::cout << "test vitesse" << std::endl;
	print_vector(test);
	std::cout << "=1=" << std::endl;
	test.insert(test.begin(), 5, 2);
	std::cout << "test assgin range" << std::endl;
	test.assign(10, 3);
	print_vector(test);
	std::cout << "Fin test" << std::endl;
	std::cout << "=2=" << std::endl;
	ft::vector<int>	r;

	r.assign(test.begin(), test.end());
	print_vector(r);
	std::cout << "=test erase range=" << std::endl; 


	r.erase(r.begin(), r.end());
	std::cout << "=3=" << std::endl;
	// test.insert(it, 55);
	// print_vector(test);
	print_vector(r);
}