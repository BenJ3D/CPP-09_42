/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 02:49:09 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/18 22:44:22 by bducrocq         ###   ########lyon.fr   */
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


typedef enum 
{
	ERR_BAD_INPUT,
	ERR_BAD_FIRSTLINE_INPUT,
	ERR_BAD_FIRSTLINE_DATABASE,
	ERR_NUMBER_NEGATIVE,
	ERR_NUMBER_TOO_LARGE,
	ERR_FAIL_TO_OPEN_DATA,
	ERR_FAIL_TO_OPEN_INPUT
} e_error;

class BitcoinExchange
{

	public:
		class FailToOpen : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "\033[0;31mError: could not open file\033[0;37m";}
		};

		class ErrDataBaseFirstLine : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "\033[0;31mError: first line in data.csv is not \"date,exchange_rate\\n\"""\033[0;35mdata.csv\033[0;37m";}
		};
		class ErrInputFirstLine : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "\033[0;31mError: first line in your input file is not \"date | value\" \033[0;37m";}
		};
		class ErrNegativeNumber : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "Error: not a positive number";}
		};
		class ErrTooLargeNumber : public std::exception
		{ public: 
			virtual const char* what() const throw() 
			{return "Error: too large a number";}
		};
		class ErrBadInput : public std::exception
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
		std::ifstream					_fileInput;
		std::string						_err;
		std::string						_errDay;

		e_error							_errorType;

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