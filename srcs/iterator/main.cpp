#include "iterator.hpp"
#include "../vector/vector.hpp"

// void	print_elem() {

// }

int	main(void) {
	ft::vector<int>			vec;

	ft::vector<int>::iterator	it;
	ft::vector<int>::iterator	ite;
	
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	ft::vector<int>::iterator	it_tmp;

	it_tmp = vec.begin();
	it = vec.begin();
	ite = vec.end();

	int i = 0;
	for ( ; it != ite ; it++) {
		std::cout << vec[i] << std::endl;
		i++;
	}
	--i;
	for ( ; ite != vec.begin() ; ite--) {
		std::cout << vec[i] << std::endl;
		i--;
	}
}