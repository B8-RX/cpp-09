#include "PmergeMe.hpp"
#include <cstddef>
#include <iterator>
#include <limits>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

FordJohnson::FordJohnson(char** input, int argc) {
	FordJohnson::parseInput(input, argc);
	FordJohnson::_setSequenceJacobsthal(_vecInput.size()/2); // add one if input(n) is odd ?
	FordJohnson::fillVector();
	FordJohnson::fillDeque();
	FordJohnson::displayBeforeAfter();
	FordJohnson::displayTimeDelta();
}

FordJohnson::~FordJohnson(void) {}

void	FordJohnson::parseInput(char** input, int argc) {
	for (int i = 1; i < argc; i++)
	{
		std::istringstream	ss(input[i]);
		long				nl;
		char				extra;
		if (!(ss >> nl))
			throw FordJohnson::ErrorException();
		if (ss >> extra)
			throw FordJohnson::ErrorException();
		if (nl <= 0 || nl > std::numeric_limits<int>::max())
			throw FordJohnson::ErrorException();
		for (std::size_t j = 0; j < _vecInput.size(); ++j)
		{
			if (_vecInput[j] == (int)nl)
				throw FordJohnson::ErrorException();
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
	std::cout << "No displayed yet \n";
	
	std::cout << "Pair->firsts: ";
	for (std::size_t i = 0; i < _vecPairs.size(); ++i)
		std::cout << _vecPairs[i].first << " ";
	std::cout << "\n";
	std::cout << "Main:   ";
	for (std::size_t i = 0; i < _vecMain.size(); ++i)
		std::cout << _vecMain[i] << "    ";
	std::cout << "\n";
	std::cout << "Smalls: ";
	for (std::size_t i = 0; i < _vecSmalls.size(); ++i)
		std::cout << _vecSmalls[i] << "    ";
	std::cout << "\n";
}

void	FordJohnson::fillVector(void) {
	if (!_vecPairs.empty())
	{
		_vecPairs.clear();
		_vecMain.clear();
		_vecSmalls.clear();
	}
	_t_start_vec = std::clock();
	_makePairsFromInput();
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
	std::cout << "Time to process a range of " << _vecMain.size() << " elements with std::vector : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_vec - _t_start_vec) / CLOCKS_PER_SEC) << " ms\n";
	std::cout << "Time to process a range of " << _deqSorted.size() << " elements with std::deque : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_deq - _t_start_deq) / CLOCKS_PER_SEC) << " ms\n";
}

void	FordJohnson::_makePairsFromInput(void) {
	int					big;
	int					small;
	std::size_t			isOdd;
	std::pair<int, int> curr;
	std::size_t			i;
	std::size_t			vecInputLen;
	std::size_t			vecPairsLen;

	if (_vecInput.empty())
		throw (FordJohnson::ErrorException());
	vecInputLen = _vecInput.size();
	_vecPairs.reserve(_vecInput.size()/2);
	isOdd = vecInputLen % 2;

	for (i = 0; i < vecInputLen - isOdd; i += 2) 
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
		curr.first = big;
		curr.second = small;
		_vecPairs.push_back(curr);
	}

	vecPairsLen = _vecPairs.size();
	for (std::size_t i = 0; i < vecPairsLen; ++i) {
		_vecMain.push_back(_vecPairs[i].first);
		_vecSmalls.push_back(_vecPairs[i].second);
	}
	if (isOdd)
		_vecSmalls.push_back(_vecInput[vecInputLen -1]);
}


void	FordJohnson::_setSequenceJacobsthal(std::size_t size) {
	std::size_t	startIndex;
	int			curr;
	_vecSequenceJacobsthal.push_back(0);
	_vecSequenceJacobsthal.push_back(1);
	for (startIndex = 2; startIndex < size; ++startIndex) {
		curr = _vecSequenceJacobsthal[startIndex - 1] + _vecSequenceJacobsthal[startIndex - 2] * 2;
		_vecSequenceJacobsthal.push_back(curr);
	}
}
