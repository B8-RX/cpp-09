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
		void							spaceTrim(std::string& str) const;
		void							processInput(const std::string&) const;
		bool							isValidDate(const std::string& date) const;
		bool							isValidDay(int month, int day) const;
		bool							isLeap(int year) const;
	private:
		std::map<std::string, double>	_mapDataPairs;
};
#endif // !BITCOINEXCHANGE_HPP
