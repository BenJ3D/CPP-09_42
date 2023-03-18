/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:59:03 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/19 00:11:33 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac == 2)
		{
			
		}
		else
			throw RPN::RPN::Error();

	}
	catch(std::exception const& e) 
	{std::cerr << e.what() << std::endl;}

	return 0;
}
