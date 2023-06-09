/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:59:03 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/20 18:00:58 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac == 2)
		{
			std::string		expstr(av[1]);
			RPN				exp(expstr);
		}
		else
			throw RPN::RPN::Error();

	}
	catch(std::exception const& e) 
	{std::cerr << e.what() << std::endl;}

	return 0;
}
