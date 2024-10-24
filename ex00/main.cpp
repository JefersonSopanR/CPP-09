#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: Invalid number of arguments." << std::endl;
		return 1;
	}
	BitcoinExchange exchange;
	exchange.execute(av[1]);
	return 0;
}