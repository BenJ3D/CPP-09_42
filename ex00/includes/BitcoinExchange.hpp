/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 02:49:09 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/16 03:14:30 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <map>

class BitcoinExchange
{

	public:

		BitcoinExchange(std::string filePath);
		~BitcoinExchange();

		BitcoinExchange &		operator=( BitcoinExchange const & rhs );

	private:
		BitcoinExchange();
		BitcoinExchange( BitcoinExchange const & src );

		void	parsingDb(std::string const &path);
		void	parsingInput(std::string const &path);

		void	dateParsing(std::string const &str);
		void	quantityParsing(std::string const &value);

		void	importDbPrice(std::string const &path);


		std::map<std::string, double> _map;

};

std::ostream &			operator<<( std::ostream & o, BitcoinExchange const & i );

#endif /* ************************************************* BITCOINEXCHANGE_H */