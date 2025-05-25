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
    std::istringstream iss(expression);
    std::string token;
    std::stack<int> stack;

    while (iss >> token)
    {
        bool isNumber = true;
        size_t i = 0;

        if (token.empty())
            throw InvalidExpression();
        if (token[0] == '-')
            i = 1;
        if (i == token.length())
            isNumber = false;

        while (i < token.length())
        {
            if (!isdigit(token[i]))
            {
                isNumber = false;
                break;
            }
            ++i;
        }
        if (isNumber)
            stack.push(atoi(token.c_str()));
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%")
        {
            if (stack.size() < 2)
                throw InvalidExpression();
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();

            int result;

            switch (token[0])
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0)
                        throw InvalidExpression();
                    result = a / b;
                    break;
                case '%':
                    if (b == 0)
                        throw InvalidExpression();
                    result = a % b;
                    break;
                default:
                    throw InvalidExpression();
            }

            stack.push(result);
        }
        else
            throw InvalidExpression();
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