/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 09:35:24 by ssghioua          #+#    #+#             */
/*   Updated: 2026/01/13 09:35:25 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./BitcoinExchange.hpp"
#include <cstdio>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

BitcoinExchange::BitcoinExchange(void) {}
BitcoinExchange::~BitcoinExchange(void) {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _mapDataPairs(other._mapDataPairs) {}
BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		_mapDataPairs = other._mapDataPairs;
	return (*this);
}

void	BitcoinExchange::loadDataBase(const std::string& dataCsv) {
	std::ifstream	fileCsv(dataCsv.c_str());
	if (!fileCsv)
		throw (std::runtime_error("Error: could not open file."));
	std::string line;
	if (!std::getline(fileCsv, line))
		throw (std::runtime_error("Error: could not open file."));
	while (std::getline(fileCsv, line))
	{
		std::size_t	commaPos = line.find(",");
		if (commaPos == std::string::npos)
			continue;
		std::string date = line.substr(0, commaPos);
		std::string rateStr = line.substr(commaPos + 1); 
		std::istringstream	iSs(rateStr);
		double	rate;
		if (!(iSs >> rate))
			continue;
		_mapDataPairs[date] = rate;
	}
	if (_mapDataPairs.empty())
		throw (std::runtime_error("Error: empty dataBase."));
}

void	BitcoinExchange::processInput(const std::string& input) const {
	// open the file
	std::ifstream	inStream(input.c_str());
	
	if (!inStream)
		throw (std::runtime_error("Error: could not open file."));
	std::string	line;
	
	std::getline(inStream, line);

	std::size_t	pos;
	while (std::getline(inStream, line))
	{
		std::string	dateInput;
		std::string	priceInput;
		pos = line.find("|");
		if (pos == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << "\n";
			continue;	
		}
		dateInput = line.substr(0, pos);
		// check IF VALID DATE (FORMAT, EXIST)
		// if (invalid) print error and continue (skip code below)
		priceInput = line.substr(++pos); 
		std::istringstream	iSs(priceInput);
		float	price;

		if (!(iSs >> price))
			continue;
		// check IF VALID NUM (POSITIV, BETWEEN 0-1000)
				// if (invalid) print error message and continue (skip code below)
				// 
		// find the closest date in the container
		// _mapDataPairs.lower_bound(dateInput);
		std::map<std::string, double>::const_iterator	it = _mapDataPairs.lower_bound(dateInput);
		std::cout << "found lower bound: " << it->first << "\n";
	}
}
