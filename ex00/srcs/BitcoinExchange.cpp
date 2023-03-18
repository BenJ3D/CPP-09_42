/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 02:49:08 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/18 23:47:40 by bducrocq         ###   ########lyon.fr   */
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
	std::cout << COLOR_NONE;
	openAndParseDataBase();
	parsingInput(filePath);
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/


BitcoinExchange::~BitcoinExchange()
{
	_map.clear();
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
		throw ErrDataBaseFirstLine();
	while(std::getline(input, line))
	{
		std::istringstream	lineStream(line);
		std::string			date;
		std::string			strPrice;

		if (getline(lineStream, date, ',') && lineStream >> strPrice)
		{
			if(!isDateFormatValid(date))
				throw std::runtime_error("Error: bad date format for one entry in data.csv.");
			if (!isPriceValid(strPrice))
				throw std::runtime_error("Error: bad price format for one entry in data.csv.");
			double price = std::strtod(strPrice.c_str(), NULL);
			ITMAP itFind = _map.find(date);
			if (itFind == _map.end())
				_map[date] = price;
			else
				throw std::runtime_error("Error: duplicate date in data.csv.");
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
	std::string::iterator ite = line.end();
	ite--;
	for (; *ite == ' '|| *ite == '\n'; ite--)
		line.erase(ite);
	if (line.compare("date | value"))
		throw ErrInputFirstLine();
	while (std::getline(input, line))
	{
		std::istringstream lineStream(line);
		std::string date;
		std::string value;
		try
		{
			if (getline(lineStream, date, '|'))
			{
				lineStream >> value;
				if (value.empty() || !isDateFormatValid(date) || !isValueValid(value))
				{
					_errDay = date;
					throw ErrBadInput();
				}
				float quantity = std::strtod(value.c_str(), NULL);
				std::cout << date << " => " << value << " = " << (getBitcoinPrice(date) * quantity) << std::endl;
			}
		}
		catch (ErrBadInput const &e)
		{
			std::cout << e.what() << _errDay << COLOR_NONE << std::endl;
		}
		catch (std::exception const &e)
		{
			std::cout << e.what() << std::endl;
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
		if (i == 2)
			if (buffer[buffer.size() - 1] == ' ')
				buffer.erase(buffer.size() - 1);
		for(std::string::iterator it = buffer.begin(); it != buffer.end(); it++)
			if (std::isdigit(*it) == 0)
				return false;
		if (i != 0)
			if (buffer.length() != 2)
				return false;

		value[i++] = std::atoi(buffer.c_str());
		if (i == 3)
			break ;
	}
	if (std::getline(stream, buffer, '-'))
		return false; 
	if (value[0] < 0 || value[1] < 0 || value[2] < 0) 
		return false; 
	if (value[0] == 0 || value[1] == 0 || value[2] == 0)
		return false;
	if (value[1] > 12)
		return false;
	if (value[2] > 31)
		return false;
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
		{
			if (*it == '-')
				throw ErrNegativeNumber();
			else
				return false;
		}
	for (std::string::iterator it = subNbr.begin(); it != subNbr.end(); it++)
		if (std::isdigit(*it) == 0)
			throw ErrBadInput();
	float ret = std::strtof(value.c_str(), NULL);
	if (ret >= 1000.0)
		throw ErrTooLargeNumber();
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
	if (it == _map.begin())
		return 0.0;
	return (static_cast<float>(it->second));
}

float BitcoinExchange::getAthBitcoinPrice(void)
{
	double priceMax = 0.0;
	for(ITMAP it = _map.begin(); it != _map.end(); it++)
		if (it->second > priceMax)
			priceMax = it->second;
	return static_cast<float>(priceMax);
}

std::string		BitcoinExchange::getAthBitcoinDate(void)
{
	std::string dateATH;
	float		priceMax = getAthBitcoinPrice();
	for(ITMAP it = _map.begin(); it != _map.end(); it++)
		if (it->second == priceMax)
			dateATH = it->first;
	return dateATH;
}

/* ************************************************************************** */