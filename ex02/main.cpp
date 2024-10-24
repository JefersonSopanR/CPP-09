#include "PmergeMe.hpp"
#include <ctime>

int main(int ac, const char *av[])
{
	if (ac < 2)
	{
		std::cerr << "Error: no arguments" << std::endl;
		return 1;
	}

	std::vector<int> v;
	std::deque<int> l;

	try
	{
		v = fill_container<std::vector<int> >(&av[1]);
	}
	catch (int e)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	std::clock_t start;
	std::clock_t end;

	std::cout << "Before: " << v << std::endl;
	mergeInsertionSort(v);
	std::cout << "After: " << v << std::endl;
	
	start = std::clock();
	fill_container<std::vector<int> >(&av[1]);
	mergeInsertionSort(v);
	end = std::clock();
	double timer = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << v.size() << " elements with std::vector: " << timer << " us" << std::endl;

	start = std::clock();
	fill_container<std::deque<int> >(&av[1]);
	mergeInsertionSort(l);
	end = std::clock();
	timer = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << v.size() << " elements with std::deque: "<< timer << " us" << std::endl;

}
