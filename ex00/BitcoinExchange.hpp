#ifndef BitcoinExchange_HPP
#define BitcoinExchange_HPP

#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
	private:
		std::string previousdate(std::string const &date);
		std::string cutspaces(std::string const &str);
		std::map<std::string, std::string> _data;
		int ft_stoi(std::string const &str);
		double ft_stod(std::string const &str);
		std::string ft_itoa(int value);
		bool is_validate_number(std::string const &str);
		bool check_date(std::string const &date);
		bool check_nums(std::string const &str, int (*isDigit)(int));
	
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &obj);
		BitcoinExchange & operator=(BitcoinExchange const &rhs);

		void execute(std::string const &filename);
};

#endif