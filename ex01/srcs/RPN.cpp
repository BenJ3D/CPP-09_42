/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 00:03:53 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/22 00:40:04 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RPN::RPN(){}

RPN::RPN( const RPN & src ){*this = src;}

RPN::RPN(std::string &exp)
{
	
	std::string::const_iterator it = exp.begin();
	
	for (; std::isspace(*it); it++);
	if (!std::isdigit(*it))
		throw Error();
	for(; it != exp.end(); it++)
	{
		char	op = '\0';
		for (; std::isspace(*it); it++);
		if (isOperator(*it))
		{
			if(_stack.size() < 2)
				throw Error();
			long a = 0;
			long b = 0;
			if (_stack.empty())
				throw Error();
			op = *it;
			if (!_stack.empty())
			{
				b = _stack.top();
				_stack.pop();
			}
			if (!_stack.empty())
			{
				a = _stack.top();
				_stack.pop();
			}
			long ret = 0;
			switch (op)
			{
			case '+':
				ret = a + b;
				break;
			case '-':
				ret = a - b;
				break;
			case '*':
				ret = a * b;
				break;
			case '/':
			{
				if (b != 0)
					ret = a / b;
				else
					throw	std::runtime_error("Error: no possible divide by 0");
				break;
			}
			default:
				break;
			}
			if (ret > INT_MAX)
				throw	std::runtime_error("Error: the result is greater than an int max");
			_stack.push(static_cast<int>(ret));
			a = 0; b = 0;
		}
		else if (!std::isdigit(*it))
			throw Error();
		else
		{
			int	n = *it - '0';
			_stack.push(n);
		}
	}
	if (_stack.size() != 1 )
		throw Error();
	std::cout << _stack.top() << std::endl;
	_stack.pop();
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

RPN::~RPN(){}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

RPN &				RPN::operator=( RPN const & rhs )
{
	this->_stack = rhs._stack;
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

bool RPN::isOperator(char c)
{
	std::string op = "+-*/";
	return op.find(c) != std::string::npos;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */