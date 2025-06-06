#include "PmergeMe.hpp"
#include <iostream>

int main(int ac, const char* av[]) 
{
    if (ac < 2) 
    {
        std::cerr << "Error: no arguments" << std::endl;
        return 1;
    }

    PmergeMe sorter;
    try 
    {
        sorter.fill(&av[1]);
        sorter.sortAndDisplay();
    } 
    catch (const std::exception &e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } 
    catch (...) 
    {
        std::cerr << "Error: invalid input" << std::endl;
        return 1;
    }

    return 0;
}
