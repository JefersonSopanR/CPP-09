#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vector(other._vector), _deque(other._deque) 
{}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) 
{
    if (this != &other) 
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::fill(const char **av) 
{
    _vector = fill_container<std::vector<int> >(av);
    _deque = fill_container<std::deque<int> >(av);
}

void PmergeMe::sortAndDisplay() 
{
    int size = _vector.size();

    std::cout << "Before: ";
    for (std::size_t i = 0; i < _vector.size(); ++i)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;

    std::clock_t start = std::clock();
    mergeInsertionSortVector(_vector);
    std::clock_t end = std::clock();
    double vectorTime = 1000000.0 * (end - start) / CLOCKS_PER_SEC;

    std::cout << "After: ";
    for (std::size_t i = 0; i < _vector.size(); ++i)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;

    start = std::clock();
    mergeInsertionSortDeque(_deque);
    end = std::clock();
    double dequeTime = 1000000.0 * (end - start) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << size << " elements with std::vector: "
              << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << size << " elements with std::deque: "
              << dequeTime << " us" << std::endl;
}

std::vector<int> PmergeMe::generateJacobsthalIndicesVector(int size) 
{
    std::vector<int> indices;
    fillJacobsthalIndices(indices, size);
    return indices;
}

std::deque<int> PmergeMe::generateJacobsthalIndicesDeque(int size) 
{
    std::deque<int> indices;
    fillJacobsthalIndices(indices, size);
    return indices;
}

void PmergeMe::mergeInsertionSortVector(std::vector<int> &values) 
{
    if (values.size() <= 1)
        return;

    std::vector<std::pair<int, int> > pairs;
    std::vector<int> pendings;

    std::vector<int>::iterator it = values.begin();
    while (it != values.end()) 
	{
        int a = *it++;
        if (it == values.end()) 
		{
            pendings.push_back(a);
            break;
        }

        int b = *it++;
        if (a > b)
            pairs.push_back(std::make_pair(a, b));
        else
            pairs.push_back(std::make_pair(b, a));
    }

    std::sort(pairs.begin(), pairs.end(), std::greater<std::pair<int, int> >());

    std::vector<int> main_chain;
    for (std::size_t i = 0; i < pairs.size(); ++i) 
	{
        main_chain.push_back(pairs[i].first);
        pendings.push_back(pairs[i].second);
    }

    std::vector<int> result;
    for (std::vector<int>::iterator it2 = main_chain.begin(); it2 != main_chain.end(); ++it2) 
	{
        std::vector<int>::iterator insertPos = std::lower_bound(result.begin(), result.end(), *it2);
        result.insert(insertPos, *it2);
    }

    std::vector<int> jacobIndices = generateJacobsthalIndicesVector(pendings.size());
    std::vector<bool> inserted(pendings.size(), false);

    for (std::size_t i = 0; i < jacobIndices.size(); ++i) 
	{
        int index = jacobIndices[i];
        if (index >= static_cast<int>(pendings.size()))
            continue;

        int insertVal = pendings[index];
        std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), insertVal);
        result.insert(pos, insertVal);
        inserted[index] = true;
    }

    for (std::size_t i = 0; i < pendings.size(); ++i) 
	{
        if (inserted[i])
            continue;
        int insertVal = pendings[i];
        std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), insertVal);
        result.insert(pos, insertVal);
    }

    values = result;
}

void PmergeMe::mergeInsertionSortDeque(std::deque<int> &values) {
    if (values.size() <= 1)
        return;

    std::vector<std::pair<int, int> > pairs;
    std::deque<int> pendings;

    std::deque<int>::iterator it = values.begin();
    while (it != values.end()) 
	{
        int a = *it++;
        if (it == values.end()) 
		{
            pendings.push_back(a);
            break;
        }

        int b = *it++;
        if (a > b)
            pairs.push_back(std::make_pair(a, b));
        else
            pairs.push_back(std::make_pair(b, a));
    }

    std::sort(pairs.begin(), pairs.end(), std::greater<std::pair<int, int> >());

    std::deque<int> main_chain;
    for (std::size_t i = 0; i < pairs.size(); ++i) 
	{
        main_chain.push_back(pairs[i].first);
        pendings.push_back(pairs[i].second);
    }

    std::deque<int> result;
    for (std::deque<int>::iterator it2 = main_chain.begin(); it2 != main_chain.end(); ++it2) 
	{
        std::deque<int>::iterator insertPos = std::lower_bound(result.begin(), result.end(), *it2);
        result.insert(insertPos, *it2);
    }

    std::deque<int> jacobIndices = generateJacobsthalIndicesDeque(pendings.size());
    std::vector<bool> inserted(pendings.size(), false);

    for (std::size_t i = 0; i < jacobIndices.size(); ++i) 
	{
        int index = jacobIndices[i];
        if (index >= static_cast<int>(pendings.size()))
            continue;

        int insertVal = pendings[index];
        std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), insertVal);
        result.insert(pos, insertVal);
        inserted[index] = true;
    }

    for (std::size_t i = 0; i < pendings.size(); ++i) 
	{
        if (inserted[i])
            continue;
        int insertVal = pendings[i];
        std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), insertVal);
        result.insert(pos, insertVal);
    }

    values = result;
}

std::ostream &operator<<(std::ostream &os, std::vector<int> const &v) {
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        os << *it << " ";
    return os;
}

std::ostream &operator<<(std::ostream &os, std::deque<int> const &d) {
    for (std::deque<int>::const_iterator it = d.begin(); it != d.end(); ++it)
        os << *it << " ";
    return os;
}
