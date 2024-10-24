#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(RPN const &obj) 
{
	*this = obj;
}

RPN & RPN::operator=(RPN const &rhs) 
{
	if (this != &rhs)
	{
		(void)rhs;
	}
	return *this;
}

void RPN::calculateOperation(std::stack<int> &stack, char const op)
{
	if (stack.size() < 2)
		throw InvalidExpression();
	int a = stack.top();
	stack.pop();
	int b = stack.top();
	stack.pop();
	switch (op)
	{
		case '+':
			stack.push(b + a);
			break;
		case '-':
			stack.push(b - a);
			break;
		case '*':
			stack.push(b * a);
			break;
		case '/':
			if (a == 0)
				throw InvalidValue();
			stack.push(b / a);
			break;
		case '%':
			if (a == 0)
				throw InvalidValue();
			stack.push(b % a);
			break;
	}
}

int RPN::calculate(std::string expression)
{
	std::string str = "0123456789+-*/% ";
	std::stack<int> stack;
	std::string::iterator it = expression.begin();

	while (it != expression.end())
	{
		if (str.find(*it) == std::string::npos)
			throw InvalidExpression();
		if (*it != ' ')
		{
			if (isdigit(*it) || (*it == '-' && isdigit(*(it + 1))))
				stack.push(atoi(&(*it)));
			else if (*it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '%')
				calculateOperation(stack, *it);
			else
				throw InvalidExpression();
		}
		it++;
	}
	if (stack.size() != 1)
		throw InvalidExpression();
	return stack.top();
}

const char *RPN::InvalidExpression::what() const throw()
{
	return "ERROR: Invalid expression";
}

const char *RPN::InvalidValue::what() const throw()
{
	return "ERROR: Invalid value";
}