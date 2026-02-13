#include "PmergeMe.hpp"
#include <iterator>
#include <limits>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

FordJohnson::FordJohnson(void) {}

FordJohnson::~FordJohnson(void) {}

void	FordJohnson::parseInput(char** input, int argc) {
	for (int i = 1; i < argc; i++)
	{
		std::istringstream	ss(input[i]);
		long				nl;
		char				extra;
		if (!(ss >> nl))
			throw FordJohnson::inputErrorException();
		if (ss >> extra)
			throw FordJohnson::inputErrorException();
		if (nl <= 0 || nl > std::numeric_limits<int>::max())
			throw FordJohnson::inputErrorException();
		for (std::size_t j = 0; j < _vecInput.size(); ++j)
		{
			if (_vecInput[j] == (int)nl)
				throw FordJohnson::inputErrorException();
		}
		_vecInput.push_back(static_cast<int>(nl));
	}
}

void	FordJohnson::displayBeforeAfter(void) {
	std::cout << "Before: ";
	for (std::size_t i = 0; i < _vecInput.size(); ++i)
		std::cout << _vecInput[i] << " ";
	std::cout << "\n";
	std::cout << "After: ";
	for (std::size_t i = 0; i < _vecSorted.size(); ++i)
		std::cout << _vecSorted[i] << " ";
	std::cout << "\n";
}

void	FordJohnson::fillVector(void) {
	if (!_vecSorted.empty())
		_vecSorted.clear();
	_t_start_vec = std::clock();
	// _makeVecPairs();	
	for (std::size_t i = 0; i < _vecInput.size(); i++)
		_vecSorted.push_back(_vecInput[i]);
	std::sort(_vecSorted.begin(), _vecSorted.end());
	_t_end_vec = std::clock();
}

void	FordJohnson::fillDeque(void) {
	if (!_deqSorted.empty())
		_deqSorted.clear();
	_t_start_deq = std::clock();
	for (std::size_t i = 0; i < _vecInput.size(); i++)
		_deqSorted.push_back(_vecInput[i]);
	std::sort(_deqSorted.begin(), _deqSorted.end());
	_t_end_deq = std::clock();
}

void	FordJohnson::displayTimeDelta(void) {
	std::cout << "Time to process a range of " << _vecSorted.size() << " elements with std::vector : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_vec - _t_start_vec) / CLOCKS_PER_SEC) << " ms\n";
	std::cout << "Time to process a range of " << _deqSorted.size() << " elements with std::deque : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_deq - _t_start_deq) / CLOCKS_PER_SEC) << " ms\n";
}

void	FordJohnson::_makeVecPairs(void) {
		int	big;
		int small;
		for (std::size_t i = 0; i + 1 < _vecInput.size(); ++i) 
		{
			if (_vecInput[i] > _vecInput[i + 1])
			{
				big = _vecInput[i];
				small = _vecInput[i + 1];
			}
			else
			{
				big = _vecInput[i + 1];
				small = _vecInput[i];
			}
			_vecPairs[i].first = big;
			_vecPairs[i].second = small;
		}
		for (std::size_t i = 0; i < _vecPairs.size(); ++i)
		{
			std::cout << "big = " << _vecPairs[i].first << "\n";
			std::cout << "small = " << _vecPairs[i].second << "\n";
		}
}
