#include "common.hpp"

#define TESTED_TYPE int

void	is_empty(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct)
{
	// std::cout << "--==--" << std::endl;
	std::cout << "is_empty: " << vct.empty() << std::endl;
}

int		main(void)
{
	const int start_size = 7;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(start_size, 20);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();

	for (int i = 2; i < start_size; ++i)
		it[i] = (start_size - i) * 3;
	printSize(vct, true);

	// std::cout << "1" << std::endl;
	vct.resize(10, 42);
	printSize(vct, true);

	// std::cout << "2" << std::endl;
	vct.resize(18, 43);
	printSize(vct, true);
	// std::cout << "3" << std::endl;
	vct.resize(10);
	printSize(vct, true);
	// std::cout << "4" << std::endl;
	vct.resize(23, 44);
	printSize(vct, true);
	// std::cout << "5" << std::endl;
	vct.resize(5);
	printSize(vct, true);
	// std::cout << "6" << std::endl;
	vct.reserve(5);
	vct.reserve(3);
	printSize(vct, true);
	// std::cout << "7" << std::endl;
	vct.resize(87);
	vct.resize(5);
	printSize(vct, true);


	// std::cout << "here" << std::endl;
	is_empty(vct2);
	vct2 = vct;
	is_empty(vct2);
	// std::cout << "Here capacity  : " << vct.capacity() + 1 << std::endl;
	vct.reserve(vct.capacity() + 1);
	// std::cout << "Size() : " << vct.size() << std::endl;

	printSize(vct, true);
	printSize(vct2, true);

	vct2.resize(0);
	is_empty(vct2);
	printSize(vct2, true);
	return (0);
}
