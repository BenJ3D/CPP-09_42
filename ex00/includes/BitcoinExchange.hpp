/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 02:49:09 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/18 19:29:12 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <cctype>
# include <stdexcept>
# include <limits>
# include <map>
# define CSV_PATH "./data.csv"
# define ITMAP std::map<std::string, double>::iterator


class BitcoinExchange
{

	public:
		class FailToOpen : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "\033[0;31mError: could not open file\033[0;37m";}
		};

		class DataBaseFirstLine : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "\033[0;31mError: first line in data.csv is not \"date,exchange_rate\\n\"""\033[0;35mdata.csv\033[0;37m";}
		};
		class InputFirstLine : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "\033[0;31mError: first line in data.csv is not \"date,exchange_rate\\n\"""\033[0;35mdata.csv\033[0;37m";}
		};
		class NegativeNumber : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "Error: not a positive number";}
		};
		class TooLargeNumber : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "Error: too large a number";}
		};
		class BadInput : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "Error: bad input => ";}
		};

		BitcoinExchange(char const *filePath);
		~BitcoinExchange();

		float	getBitcoinPrice(std::string const& date);



	private:
		BitcoinExchange( void );
		BitcoinExchange( BitcoinExchange const & src );
		BitcoinExchange &		operator=( BitcoinExchange const & rhs );

		void	openAndParseDataBase( void );
		void	parsingInput( char const *path );

		bool	isDateFormatValid(std::string const& dateString);
		bool	isValueValid(std::string const &value);
		bool	isPriceValid(std::string const &price);



		std::map<std::string, double>	_map;
		std::string						_pathDB;
		std::string						_err;
		std::string						_errDay;
		std::ifstream					_fileInput;
};

std::ostream &			operator<<( std::ostream & o, BitcoinExchange const & i );

# define COLOR_BLACK	"\033[0;30m"
# define COLOR_RED		"\033[0;31m"
# define COLOR_GREEN	"\033[0;32m"
# define COLOR_YELLOW	"\033[0;33m"
# define COLOR_BLUE		"\033[0;34m"
# define COLOR_PURPLE	"\033[0;35m"
# define COLOR_CYAN		"\033[0;36m"
# define COLOR_NONE		"\033[0;37m"

#endif /* ************************************************* BITCOINEXCHANGE_H */