/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:59:03 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/18 23:53:29 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
		{
			BitcoinExchange btc(av[1]);

			
			// std::cout << "\n\nFT COMPLEMENTAIRES\n" << std::endl;
			// std::cout << "BTC price at 2015-01-01 = " << btc.getBitcoinPrice("2015-01-01") << std::endl;
			// std::cout	<< "BTC price at ATH("<< btc.getAthBitcoinDate() 
			// 			<< ") = " << btc.getBitcoinPrice(btc.getAthBitcoinDate()) << std::endl;
		}
		else
			std::cerr << COLOR_RED
				<< "Error: could not open file." << std::endl;

	}
	catch(std::exception const& e) 
	{std::cerr << e.what() << std::endl;}

	return 0;
}
