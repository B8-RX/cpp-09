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

