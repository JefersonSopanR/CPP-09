#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <algorithm>
#include <sstream>

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(RPN const &obj);
		RPN & operator=(RPN const &rhs);

		static int calculate(std::string expression);

		class InvalidExpression : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		
		class InvalidValue : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
	
	private:

		static void calculateOperation(std::stack<int> &, char const );

};

#endif