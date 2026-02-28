/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 09:35:24 by ssghioua          #+#    #+#             */
/*   Updated: 2026/01/13 09:35:25 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class	BitcoinExchange {
	public:
		BitcoinExchange(void);
		~BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange&);
		BitcoinExchange&				operator=(const BitcoinExchange&);
		void							loadDataBase(const std::string&);
		void							processInput(const std::string&) const;
	private:
		std::map<std::string, double>	_mapDataPairs;
		void							_spaceTrim(std::string& str) const;
		bool							_isValidInputFileHeader(std::ifstream& inStream) const;
		bool							_isValidDate(const std::string& date, const std::string& line) const;
		bool							_isValidDay(int month, int day, int year) const;
		bool							_isLeap(int year) const;
		bool							_isValidPrice(const std::string& priceInput, double& price, const std::string& line) const;
		bool							_searchAndCalculate(const std::string& date, double price) const;
};
#endif // !BITCOINEXCHANGE_HPP
