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
		_spaceTrim(date);
		if (!_isValidDate(date, line))
			continue;
		
		std::string rateStr = line.substr(commaPos + 1);
		_spaceTrim(rateStr);
	
		std::istringstream	iSs(rateStr);
		double	rate;
		char	extra;
		if (!(iSs >> rate) || (iSs >> extra))
			continue;
		_mapDataPairs[date] = rate;
	}
	if (_mapDataPairs.empty())
		throw (std::runtime_error("Error: empty dataBase."));
}

void	BitcoinExchange::_spaceTrim(std::string& str) const {
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
	if (!_isValidInputFileHeader(inStream))
		throw (std::runtime_error("Error: bad header."));
	std::size_t	posLine;
	std::string	line;
	while (std::getline(inStream, line))
	{
		posLine = line.find("|");
		if (posLine == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << "\n";
			continue;	
		}

		std::string	dateInput = line.substr(0, posLine);
		_spaceTrim(dateInput);
		if (!_isValidDate(dateInput, line))
			continue;

		std::string	priceInput = line.substr(posLine + 1); 
		_spaceTrim(priceInput);
		double price;
		if (!_isValidPrice(priceInput, price, line))
			continue;
		
		if (!_searchAndCalculate(dateInput, price))
			continue;
	}
}

bool	BitcoinExchange::_isValidInputFileHeader(std::ifstream& inStream) const {
	std::string	header;
	std::getline(inStream, header);
	
	std::size_t	posLine;
	posLine = header.find("|");
	if (posLine == std::string::npos)
		return (false);
	
	std::string	left;
	left = header.substr(0, posLine);
	_spaceTrim(left);
	
	std::string	right;
	right = header.substr(posLine + 1);
	_spaceTrim(right);
	return (left == "date" && right == "value");
}

bool	BitcoinExchange::_isValidDay(int month, int day, int year) const {
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);
	if (day < 1 || day > 31)
		return (false);
	if ((month) == 2)
	{
		if (_isLeap(year))
		{
			if (day > 29)
				return (false);
		}
		else if (day > 28)
			return (false);
	}
	return (true); 
}

bool	BitcoinExchange::_isLeap(int year) const {
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

bool	BitcoinExchange::_isValidDate(const std::string& date, const std::string& line) const {
	bool	valid = true;
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (std::cout << "Error: bad input => " << line << "\n", false);
	std::string	yStr, mStr, dStr;
	yStr = date.substr(0, 4);
	mStr = date.substr(5, 2);
	dStr = date.substr(8, 2);

	std::istringstream	iSy(yStr), iSm(mStr), iSd(dStr);
	int y, m, d;
	char c;

	if (!(iSy >> y) || (iSy >> c)) valid = false;
	if (!(iSm >> m) || (iSm >> c)) valid = false;
	if (!(iSd >> d) || (iSd >> c)) valid = false;
	
	if (m < 1 || m > 12)
		valid = false;

	if (!_isValidDay(m, d, y))
		valid = false;

	if (!valid)
	{
		std::cout << "Error: bad input => " << line << "\n";
		return (false);
	}	
	return (valid);
}
bool	BitcoinExchange::_isValidPrice(const std::string& priceInput, double& price, const std::string& line) const {

	std::istringstream	iSs(priceInput);
	char	c;

	if (!(iSs >> price) || (iSs >> c))
	{
		std::cout << "Error: bad input => " << line << "\n";
		return (false);
	}

	if (price < 0 || price > 1000)
	{
		if (price < 0)
			std::cout << "Error: not a positive number.\n";
		else
			std::cout << "Error: too large a number.\n";
		return (false);
	}
	return (true);
}

bool	BitcoinExchange::_searchAndCalculate(const std::string& date, double price) const {
	std::map<std::string, double>::const_iterator	it = _mapDataPairs.lower_bound(date);
	double	result;
	if (it == _mapDataPairs.end() || it->first != date)
	{
		if (it == _mapDataPairs.begin())
		{
			std::cout << "Error: could not find data for the date " << date << "\n";
			return (false);
		}
		it--;
	}
	result = it->second * price;
	std::cout << date << " => " << price << " = " << result << "\n";
	return (true);
}
