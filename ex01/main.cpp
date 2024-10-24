#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./ex01 \"expression\"" << std::endl;
		return 1;
	}
	try
	{
		std::cout << RPN::calculate(av[1]) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}