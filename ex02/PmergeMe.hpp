#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <ostream>
#include <stdexcept>
#include <ctime>

template <typename Container>
bool is_duplicate(Container const &c, int value) 
{
    return std::find(c.begin(), c.end(), value) != c.end();
}

template <typename Container>
void fillJacobsthalIndices(Container &indices, int size) 
{
    Container jacob;
    jacob.push_back(0);
    jacob.push_back(1);

    int j = 2;
    while (true) 
	{
        int next = jacob[j - 1] + 2 * jacob[j - 2];
        if (next >= size)
            break;
        jacob.push_back(next);
        ++j;
    }

    if (size > 0)
        indices.push_back(0);

    for (int i = static_cast<int>(jacob.size()) - 1; i > 0; --i) 
	{
        int start = jacob[i];
        int end = (i + 1 < static_cast<int>(jacob.size())) ? jacob[i + 1] : size;
        for (int k = start; k < end && k < size; ++k)
            indices.push_back(k);
    }
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
        if (ss.fail())
            throw std::invalid_argument("Non-integer input");
        if (is_duplicate(c, value) || value < 0)
            throw std::runtime_error("Negative or duplicate value");
        c.push_back(value);
        i++;
    }
    return c;
}

class PmergeMe 
{
	private:
		std::vector<int> _vector;
		std::deque<int> _deque;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void fill(const char **av);
		void sortAndDisplay();

	private:
		void mergeInsertionSortVector(std::vector<int> &values);
		void mergeInsertionSortDeque(std::deque<int> &values);
		std::vector<int> generateJacobsthalIndicesVector(int size);
		std::deque<int> generateJacobsthalIndicesDeque(int size);
};

std::ostream &operator<<(std::ostream &os, std::vector<int> const &v);
std::ostream &operator<<(std::ostream &os, std::deque<int> const &d);

#endif
