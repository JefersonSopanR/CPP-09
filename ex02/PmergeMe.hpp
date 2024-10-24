#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <ostream>

template <typename Container>

bool is_duplicate(Container const &c, int value) {
	return std::find(c.begin(), c.end(), value) != c.end();
}

template <typename Container>
void mergeInsertionSort(Container &values)
{
	// base case
	if (values.size() <= 1)
		return;
	// split the container into two halves
	Container left(values.begin(), values.begin() + values.size() / 2);
	Container right(values.begin() + values.size() / 2, values.end());
	// sort the two halves
	mergeInsertionSort(left);
	mergeInsertionSort(right);

	// merge the two halves
	Container result;
	typename Container::const_iterator leftIt = left.begin();
	typename Container::const_iterator rightIt = right.begin();
	while (leftIt != left.end() && rightIt != right.end())
	{
		if (*leftIt < *rightIt)
		{
			result.push_back(*leftIt);
			++leftIt;
		}
		else
		{
			result.push_back(*rightIt);
			++rightIt;
		}
	}
	// copy the remaining elements
	while (leftIt != left.end())
	{
		result.push_back(*leftIt);
		++leftIt;
	}
	while (rightIt != right.end())
	{
		result.push_back(*rightIt);
		++rightIt;
	}
	values = result;
}

template <typename Container>
Container fill_container(const char **str) 
{
	Container c;
	int i = 0;
	while (str[i])
	{
		int value;
		std::stringstream ss;
		ss << str[i];
		ss >> value;
		if (is_duplicate(c, value) || value < 0)
		{
			throw 1;
		}
		else if (ss.fail())
		{
			throw 2;
		}
		c.push_back(value);
		i++;
	}
	return c;
}

std::ostream &operator<<(std::ostream &os, std::deque<int> const &l);

std::ostream &operator<<(std::ostream &os, std::vector<int> const &v);

#endif
