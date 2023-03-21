/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 00:03:53 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/20 17:52:04 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <cstdlib>
# include <stdexcept>
# include <climits>
# include <stack>

class RPN
{

	public:

		RPN(std::string & expression);
		~RPN();

		class Error : public std::exception
		{ public: virtual const char *what() const throw() {return "\033[0;31mError\033[0;37m";}};

		RPN &		operator=( RPN const & rhs );


	private:
		RPN();
		RPN( RPN const & src );

		bool	isOperator( char c );

		std::stack<int>	_stack;

};

# define COLOR_BLACK	"\033[0;30m"
# define COLOR_RED		"\033[0;31m"
# define COLOR_GREEN	"\033[0;32m"
# define COLOR_YELLOW	"\033[0;33m"
# define COLOR_BLUE		"\033[0;34m"
# define COLOR_PURPLE	"\033[0;35m"
# define COLOR_CYAN		"\033[0;36m"
# define COLOR_NONE		"\033[0;37m"

#endif /* ************************************************************* RPN_H */