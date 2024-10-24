#include "PmergeMe.hpp"

std::ostream &operator<<(std::ostream &os, std::vector<int> const &v)
{
	for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
	{
		os << *it << " ";
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, std::deque<int> const &l)
{
	for (std::deque<int>::const_iterator it = l.begin(); it != l.end(); ++it)
	{
		os << *it << " ";
	}
	return os;
}