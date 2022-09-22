#include "common.hpp"

/*
single element (1)
	iterator insert (iterator position, const value_type& val);

fill (2)
    void insert (iterator position, size_type n, const value_type& val);

range (3)
	template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last);
*/

#define TESTED_TYPE int

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	std::cout << "1 : " << std::endl;
	printSize(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	std::cout << "2 : " << std::endl;
	printSize(vct2);

	vct2.insert(vct2.end() - 2, 42);
	std::cout << "3 : " << std::endl;
	printSize(vct2);

	vct2.insert(vct2.end(), 2, 84);
	std::cout << "4 : " << std::endl;
	printSize(vct2);

	vct2.resize(4);
	std::cout << "5 : " << std::endl;
	printSize(vct2);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	std::cout << "6 : " << std::endl;
	printSize(vct2);

	std::cout << "7 : " << std::endl;
	printSize(vct);

	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), i);
	vct3.insert(vct3.begin() + 1, 2, 111);
	std::cout << "8 : " << std::endl;
	printSize(vct3);

	return (0);
}
