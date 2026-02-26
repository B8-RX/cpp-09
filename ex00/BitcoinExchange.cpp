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
#include <ctime>
#include <iomanip>
#include <locale>
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
		spaceTrim(date);
		spaceTrim(rateStr);
		std::istringstream	iSs(rateStr);
		double	rate;
		if (!(iSs >> rate))
			continue;
		_mapDataPairs[date] = rate;
	}
	if (_mapDataPairs.empty())
		throw (std::runtime_error("Error: empty dataBase."));
}

void	BitcoinExchange::spaceTrim(std::string& str) const {
	std::string	tmp = str;
	std::string	spaces = " \f\n\r\t\v";
	std::size_t	posStart = str.find_first_not_of(spaces);
	if (posStart == std::string::npos)
	{
		str.clear();
		return;
	}
	if (posStart != std::string::npos)
		tmp = str.substr(posStart);
	std::size_t	posEnd = tmp.find_last_not_of(spaces);
	if (posEnd != std::string::npos)
		tmp = tmp.substr(0, posEnd + 1);
	str = tmp; 
} 

void	BitcoinExchange::processInput(const std::string& input) const {
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
		priceInput = line.substr(pos + 1); 
		spaceTrim(dateInput);
		spaceTrim(priceInput);
		if (!isValidDate(dateInput))
		{
			std::cout << "Error: bad input => " << line << "\n";
			continue;
		}
		std::istringstream	iSs(priceInput);
		double	price;
		char	c;

		if (!(iSs >> price) || (iSs >> c))
		{
			std::cout << "Error: bad input => " << line << "\n";
			continue;
		}
		if (price < 0 || price > 1000)
		{
			if (price < 0) std::cout << "Error: not a positive number.\n";
			else if (price > 1000) std::cout << "Error: too large a number.\n";
			continue;
		}
		std::map<std::string, double>::const_iterator	it = _mapDataPairs.lower_bound(dateInput);
		double	result;
		if (it == _mapDataPairs.end() || it->first != dateInput)
		{
			if (it == _mapDataPairs.begin())
			{
				std::cout << "Error: could not find data for the date " << dateInput << "\n";
				continue;
			}
			it--;
		}
		result = it->second * price;
		std::cout << dateInput << " => " << price << " = " << result << "\n";
	}
}

bool	BitcoinExchange::isValidDay(int month, int day) const {
	bool	isValid = true;
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		isValid = false;
	if (day < 1 || day > 31)
		isValid = false;
	return (isValid); 
}

bool	BitcoinExchange::isValidDate(const std::string& date) const {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	std::string	yStr, mStr, dStr;
	yStr = date.substr(0, 4);
	mStr = date.substr(5, 2);
	dStr = date.substr(8, 2);

	std::istringstream	iSy(yStr), iSm(mStr), iSd(dStr);
	int y, m, d;
	char c;

	if (!(iSy >> y) || (iSy >> c)) return (false);
	if (!(iSm >> m) || (iSm >> c)) return (false);
	if (!(iSd >> d) || (iSd >> c)) return (false);

	if (m < 1 || m > 12)
		return (false);
	if (!isValidDay(m, d))
		return (false);
	if ((m) == 2)
	{
		if (isLeap(y))
		{
			if (d > 29)
				return (false);
		}
		else if (d > 28)
			return (false);
	}
	return (true);
}

bool	BitcoinExchange::isLeap(int year) const {
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

