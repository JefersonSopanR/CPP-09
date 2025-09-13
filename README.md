# CPP-09

This repository contains solutions for C++ Module 09 exercises, typically found in 42 school curriculum. The module focuses on advanced C++ topics such as containers, algorithms, and custom class implementations.

## Project Structure

- `ex00/` - Bitcoin Exchange
  - Implements a program to process Bitcoin exchange rates from a CSV file and calculate values based on user input.
  - **Files:**
    - `BitcoinExchange.cpp`, `BitcoinExchange.hpp`: Main class for exchange logic
    - `data.csv`: Historical Bitcoin rates
    - `input.txt`: Example input file
    - `main.cpp`: Entry point
    - `Makefile`: Build instructions

- `ex01/` - Reverse Polish Notation (RPN)
  - Implements a calculator using Reverse Polish Notation.
  - **Files:**
    - `RPN.cpp`, `RPN.hpp`: RPN logic
    - `main.cpp`: Entry point
    - `Makefile`: Build instructions

- `ex02/` - PmergeMe
  - Implements a merge-insert sort algorithm using C++ containers.
  - **Files:**
    - `PmergeMe.cpp`, `PmergeMe.hpp`: Sorting logic
    - `main.cpp`: Entry point
    - `Makefile`: Build instructions

## How to Build

Each exercise folder contains its own `Makefile`. To build a specific exercise:

```bash
cd ex00  # or ex01, ex02
make
```

## How to Run

After building, run the executable generated in each folder. Example for `ex00`:

```bash
./bitcoinExchange input.txt
```

## Requirements

- C++98 standard
- No external libraries (unless specified)

## Author

Jeferson Sopan R

---

Feel free to explore each exercise folder for more details and source code.
