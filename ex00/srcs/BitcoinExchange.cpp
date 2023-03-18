/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 02:49:08 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/18 19:41:33 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"
#include "BitcoinExchange.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(char const *filePath) : _pathDB(CSV_PATH)
{
	openAndParseDataBase();
	parsingInput(filePath);
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/


BitcoinExchange::~BitcoinExchange()
{
}
/*
** --------------------------------- OVERLOAD ---------------------------------
*/

BitcoinExchange &				BitcoinExchange::operator=( BitcoinExchange const & rhs )
{
	if ( this != &rhs )
	{
		this->_map = rhs._map;
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, BitcoinExchange const & i )
{

	// o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void BitcoinExchange::openAndParseDataBase()
{
	std::ifstream		input(_pathDB.c_str(), std::ifstream::in);
	std::string			line;

	if (!input.is_open())
		throw FailToOpen();
	std::getline(input, line);
	if (!line.compare("date,exchange_rate\n"))
		throw DataBaseFirstLine();
	while(std::getline(input, line))
	{
		std::istringstream	lineStream(line);
		std::string			date;
		std::string			strPrice;

		if (getline(lineStream, date, ',') && lineStream >> strPrice)
		{
			if(!isDateFormatValid(date))
				throw std::runtime_error("Error: bad date format for one entry in data.csv");
			if (!isPriceValid(strPrice))
				throw std::runtime_error("Error: bad price format for one entry in data.csv");
			double price = std::strtod(strPrice.c_str(), NULL);
			ITMAP itFind = _map.find(date);
			if (itFind == _map.end())
				_map[date] = price;
			else
				throw std::runtime_error("Error: duplicate date in data.csv");
		}
	}
	input.close();
}

void BitcoinExchange::parsingInput(char const *path)
{
	std::ifstream		input(path, std::ifstream::in);
	std::string			line;

	if (!input.is_open())
		throw FailToOpen();
	std::getline(input, line);
	if (!line.compare("date | value\n"))
		throw InputFirstLine();
	while (std::getline(input, line))
	{
		std::istringstream lineStream(line);
		std::string date;
		std::string value;

		if (getline(lineStream, date, '|') && lineStream >> value)
		{
			try
			{
				if (!isValueValid(value))
				{
					_errDay = date;
					throw BadInput();
				}
				float quantity = std::strtod(value.c_str(), NULL);
				std::cout << date << " => " << value << " = " << (getBitcoinPrice(date) * quantity) << std::endl;
			}
			catch (BadInput const &e)
			{
				std::cout << e.what() << _errDay << std::endl;
			}
			catch (std::exception const &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
	input.close();
}

bool BitcoinExchange::isDateFormatValid(std::string const &dateString)
{
	std::istringstream	stream(dateString);
	std::string			buffer;
	int					value[3];
	
	int	i = 0;
	while(std::getline(stream, buffer, '-'))
	{
		// std::cerr << COLOR_BLUE << buffer << COLOR_NONE << std::endl;
		for(std::string::iterator it = buffer.begin(); it != buffer.end(); it++)
			if (std::isdigit(*it) == 0) {
				_err = "Error: date has not digit"; return false; }
		if (i != 0)
			if (buffer.length() != 2){  //TODO: gerer les 1 et 01 etc ?
				_err = "Error: bad date input"; return false; }

		value[i++] = std::atoi(buffer.c_str());
		if (i == 3)
			break ;
	}
	if (std::getline(stream, buffer, '-')){ 
		_err = "Error: date format"; return false; }
	if (value[0] < 0 || value[1] < 0 || value[2] < 0) {
		_err = "Error: not a positive number"; return false; }
	if (value[0] == 0 || value[1] == 0 || value[2] == 0) {
		_err = "Error: bad date input"; return false; }
	if (value[1] > 12) {
		_err = "Error: only 12 months in a year"; return false; }
	if (value[2] > 31) {
		_err = "Error: No month has more than 31 days"; return false; }
	return true;
}

bool	BitcoinExchange::isValueValid(std::string const &value)
{
	std::istringstream	fnbr(value);
	std::string			nbr;
	std::string			subNbr;

	std::getline(fnbr, nbr, '.');
	fnbr >> subNbr;

	for (std::string::iterator it = nbr.begin(); it != nbr.end(); it++)
		if (std::isdigit(*it) == 0)
			return false;
	for (std::string::iterator it = subNbr.begin(); it != subNbr.end(); it++)
		if (std::isdigit(*it) == 0)
			return false;
	float	ret = std::strtof(value.c_str(), NULL);
	if (ret < 0.0)
		throw NegativeNumber();
	else if (ret >= 1000.0)
		throw TooLargeNumber();
	else
		return true;
}

bool	BitcoinExchange::isPriceValid(std::string const &price)
{
	std::istringstream	fnbr(price);
	std::string			nbr;
	std::string			subNbr;

	std::getline(fnbr, nbr, '.');
	fnbr >> subNbr;

	for (std::string::iterator it = nbr.begin(); it != nbr.end(); it++)
		if (std::isdigit(*it) == 0)
			return false;
	for (std::string::iterator it = subNbr.begin(); it != subNbr.end(); it++)
		if (std::isdigit(*it) == 0)
			return false;
	return true;
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

float	BitcoinExchange::getBitcoinPrice(std::string const &date)
{
	ITMAP it = _map.find(date);
	if (it == _map.end())
	{
		it = _map.lower_bound(date);
		it--;
	}
	// FIXME: std::cerr << std::endl << "DATE FIND: " << it->first << " | Date SEARCH: " << date << std::endl;
	if (it == _map.begin())
		return 0.0;
	return (static_cast<float>(it->second));
}


/* ************************************************************************** */