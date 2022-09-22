#include "common.hpp"

#define TESTED_TYPE std::string

void	checkErase(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct,
					TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	std::cout << "1 : " << std::endl;
	checkErase(vct, vct.erase(vct.begin() + 2));

	std::cout << "2 : " << std::endl;
	checkErase(vct, vct.erase(vct.begin()));

	std::cout << "3 : " << std::endl;
	checkErase(vct, vct.erase(vct.end() - 1));

	std::cout << "4 : " << std::endl;
	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));

	std::cout << "5 : " << std::endl;
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	std::cout << "6 : " << std::endl;
	printSize(vct);
	std::cout << "7 : " << std::endl;
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	std::cout << "8 : " << std::endl;
	printSize(vct);

	std::cout << "9 : " << std::endl;
	checkErase(vct, vct.erase(vct.begin(), vct.end()));

	return (0);
}
