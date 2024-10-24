#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() 
{
	std::ifstream file("data.csv");
	if (!file.is_open())
	{
		std::cerr << "Error: file not found" << std::endl;
		exit(1);
	}
	std::string line;
	std::string date;
	std::string value;
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::getline(ss, date, ',');
		std::getline(ss, value, ',');
		_data[date] = value;
	}
	file.close();
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &obj) 
{
	*this = obj;
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const &rhs) 
{
	if (this != &rhs)
	{
		_data = rhs._data;
	}
	return *this;
}

void BitcoinExchange::execute(std::string const &filename) 
{
	std::string line;
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: file not found" << std::endl;
		exit(1);
	}

	if (file.peek() == std::ifstream::traits_type::eof())
	{
		std::cerr << "Error: file is empty" << std::endl;
		exit(1);
	}

	if (!std::getline(file, line) || line != "date | value")
	{
		std::cerr << "Error: file is not valid" << std::endl;
		exit(1);
	}
	std::string date;
	std::string value;
	while (std::getline(file, line))
	{
		size_t pos = line.find(" | ");
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		date = line.substr(0, pos);
		value = line.substr(pos + 3);

		if (date.empty() || value.empty())
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (!check_date(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		if (!is_validate_number(value))
			continue;

		std::map<std::string, std::string>::iterator it = _data.find(date);
		std::string previousdate = date;

		while (it == _data.end())
		{
			std::string newdate = previousdate;
			previousdate = this->previousdate(previousdate);
			it = _data.find(previousdate);
		}

		std::cout << date << " => " << value << " = " << ft_stod(it->second) * ft_stod(value) << std::endl;
	}
}

int BitcoinExchange::ft_stoi(std::string const &str) 
{
	int value;
	std::istringstream ss(str);
	ss >> value;
	return value;
}

double BitcoinExchange::ft_stod(std::string const &str) 
{
	double value;
	std::istringstream ss(str);
	ss >> value;
	return value;
}

std::string BitcoinExchange::ft_itoa(int value) 
{
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

std::string BitcoinExchange::previousdate(std::string const &date) 
{
	std::string year = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8, 2);

	int y = ft_stoi(year);
	int m = ft_stoi(month);
	int d = ft_stoi(day);

	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
	if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
		days[1] = 29;

	if (d == 1)
	{
		if (m == 1)
		{
			m = 12;
			y--;
		}
		else
			m--;
		d = days[m - 1];
	}
	else
		d--;

	std::string newdate = ft_itoa(y) + "-";
	if (m < 10)
		newdate += "0";
	newdate += ft_itoa(m) + "-";
	if (d < 10)
		newdate += "0";
	newdate += ft_itoa(d);
	return newdate;
}

std::string BitcoinExchange::cutspaces(std::string const &str) 
{
	size_t start = str.find_first_not_of(" ");
	size_t end = str.find_last_not_of(" ");
	if (start == std::string::npos)
		return str;
	return str.substr(start, end - start + 1);
}

bool BitcoinExchange::is_validate_number(std::string const &str) 
{
	if (str.empty())
	{
		std::cerr << "Error: bad input => " << str << std::endl;
		return false;
	}
	if (str[0] == '-')
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (str.find_first_not_of("0123456789.") != std::string::npos)
	{
		std::cerr << "Error: bad input => " << str << std::endl;
		return false;
	}
	if (str.find('.') != str.find_last_of('.'))
	{
		std::cerr << "Error: bad input => " << str << std::endl;
		return false;
	}
	double value = ft_stod(str);
	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000.0)
	{
		std::cerr << "Error: too large number." << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::check_nums(std::string const &str, int (*isDigit)(int)) 
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isDigit(str[i]))
			return false;
	}
	return true;
}

bool BitcoinExchange::check_date(std::string const &date) 
{
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	
	std::string year = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8, 2);

	if (!check_nums(year, isdigit) || !check_nums(month, isdigit) || !check_nums(day, isdigit))
		return false;

	int y = ft_stoi(year);
	int m = ft_stoi(month);
	int d = ft_stoi(day);

	if (y == 2009 && m == 1 && d < 2)
		return false;
	if (y < 2009 || y > 2022 || m < 1 || m > 12 || d < 1 || d > 31)
		return false;

	if (m == 2)
	{
		if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
		{
			if (d > 29)
				return false;
		}
		else if (d > 28)
			return false;
	}
	if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
		return false;
	
	return true;
}
