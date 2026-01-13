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
};
#endif // !BITCOINEXCHANGE_HPP
