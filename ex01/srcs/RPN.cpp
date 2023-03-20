/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 00:03:53 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/20 17:54:44 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RPN::RPN()
{
}

RPN::RPN( const RPN & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

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
			if (_stack.empty())
				throw Error();
			op = *it;
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();
			int ret = 0;
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
				ret = a / b;
				break;
			default:
				break;
			}
			_stack.push(ret);
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

RPN::~RPN()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

RPN &				RPN::operator=( RPN const & rhs )
{
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