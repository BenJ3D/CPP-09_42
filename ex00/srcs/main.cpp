/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:59:03 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/18 02:17:11 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int main(int ac, char **av)
{
	try
	{
		if (av[1])
			BitcoinExchange btc(av[1]);
		else
			std::cerr << COLOR_RED
				<< "Error: could not open file" << std::endl;
	}
	catch(std::exception const& e) {std::cerr << e.what() << std::endl;}

	return 0;
}
