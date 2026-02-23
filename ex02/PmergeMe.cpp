#include "PmergeMe.hpp"
#include <cstddef>
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
	_odd = _vecInput.size() % 2;
}

void	FordJohnson::displayBeforeAfter(void) const {
	std::cout << "Before: ";
	std::size_t	i;
	for (i = 0; i < _vecInput.size(); ++i)
		std::cout << _vecInput[i] << " ";
	std::cout << "\n";
	std::cout << "After: ";
	for (i = 0; i < _vecMain.size(); ++i)
		std::cout << _vecMain[i] << " ";
	
	std::cout << "\n";
	std::cout << "Jacobsthal seq: ";
	for (i = 0; i < _vecSequenceJacobsthal.size(); ++i)
		std::cout << _vecSequenceJacobsthal[i] << " ";
	
	std::cout << "\n";
	std::cout << "Pair->first:  ";
	for (i = 0; i < _vecPairs.size(); ++i)
		std::cout << _vecPairs[i].first << " ";
	std::cout << "\n";
	std::cout << "Pair->second: ";
	for (i = 0; i < _vecPairs.size(); ++i)
		std::cout << _vecPairs[i].second << " ";
	std::cout << "\n";
	
	std::cout << "Main:   ";
	for (i = 0; i < _vecMain.size(); ++i)
		std::cout << _vecMain[i] << "    ";
	std::cout << "\n";
	std::cout << "Smalls: ";
	for (i = 0; i < _vecPairsPend.size(); ++i)
		std::cout << _vecPairsPend[i].first << "    ";
	std::cout << "\n";
}

void	FordJohnson::fillVector(void) {
	if (!_vecPairs.empty())
	{
		_vecPairs.clear();
		_vecMain.clear();
		_vecPairsPend.clear();
	}
	_t_start_vec = std::clock();
	_makePairsFromInput();
	if (_vecPairs.size() > 1)
		_mergeSortPairs(_vecPairs, 0, _vecPairs.size() -1);
	_buildMainAndSmall();
	// _insertSmallSimple();
	_insertSmallJacobsthal();
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

std::size_t	FordJohnson::_lowerBound(const std::vector<int>& v, std::size_t right, int x) const {
	if (v.empty())
		return (0);
	if (right > v.size())
		right = v.size();
	std::size_t left = 0;
	while (left < right)
	{
		std::size_t mid = left + (right - left) / 2;
		if (v[mid] < x)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

void	FordJohnson::_insertSmallSimple(void) {
	std::size_t i;
	for (i = 0; i < _vecPairsPend.size(); ++i)
	{
		int	small = _vecPairsPend[i].first;
		int	big = _vecPairsPend[i].second;
		std::size_t posBig = _lowerBound(_vecMain, _vecMain.size(), big);
		std::size_t bound = (big == std::numeric_limits<int>::max()) ? _vecMain.size() : (posBig + 1);
		std::size_t posIns = _lowerBound(_vecMain, bound, small);
		_vecMain.insert(_vecMain.begin() + posIns, small);
	}
}

void	FordJohnson::_insertSmallJacobsthal(void) {
	std::cout << "work in _insertSmallJacobsthal function\n";
}

void	FordJohnson::displayTimeDelta(void) const {
	std::cout << "Time to process a range of " << _vecMain.size() << " elements with std::vector : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_vec - _t_start_vec) / CLOCKS_PER_SEC) << " ms\n";
	std::cout << "Time to process a range of " << _deqSorted.size() << " elements with std::deque : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_deq - _t_start_deq) / CLOCKS_PER_SEC) << " ms\n";
}

void	FordJohnson::_mergePairs(std::vector<std::pair<int, int> >& vp, std::size_t left, std::size_t mid, std::size_t right) {
	if (vp.empty() || right >= vp.size())
		throw FordJohnson::ErrorException();
	std::vector<std::pair<int, int> > vpTmp;
	std::size_t	i = left;
	std::size_t j = mid + 1;

	vpTmp.reserve(right - left + 1);
	while (i <= mid && j <= right)
	{
		if (vp[i].first <= vp[j].first)
		{
			vpTmp.push_back(vp[i]);
			i++;
		}
		else 
		{
			vpTmp.push_back(vp[j]);
			j++;
		}
	}
	for (; i <= mid; ++i)
		vpTmp.push_back(vp[i]);
	for (; j <= right; ++j)
		vpTmp.push_back(vp[j]);
	for (std::size_t k = 0; k < vpTmp.size(); ++k)
		vp[left + k] = vpTmp[k];
}

void	FordJohnson::_mergeSortPairs(std::vector<std::pair<int, int> >& vp, std::size_t left, std::size_t right) {
	if (vp.empty() || left >= vp.size() || right >= vp.size())
		throw FordJohnson::ErrorException();
	if (left >= right)
		return ;
	std::size_t	mid = left + (right - left) / 2;
	FordJohnson::_mergeSortPairs(vp, left, mid);
	FordJohnson::_mergeSortPairs(vp, mid + 1, right);
	FordJohnson::_mergePairs(vp, left, mid, right);
}

void	FordJohnson::_buildMainAndSmall() {
	if (!_vecPairsPend.empty() || !_vecMain.empty())
	{
		_vecPairsPend.clear();
		_vecMain.clear();
	}
	std::size_t	sizePend = _vecPairs.size() + (_odd ? 1 : 0); 
	_vecPairsPend.reserve(sizePend);
	std::size_t i;
	std::pair<int, int> currPend;
	for (i = 0; i < _vecPairs.size(); ++i) {
		_vecMain.push_back(_vecPairs[i].first);
		currPend.first = _vecPairs[i].second;
		currPend.second = _vecPairs[i].first;
		_vecPairsPend.push_back(currPend); 
	}
	if (_odd)
	{
		currPend.first = _vecInput[_vecInput.size() -1];
		currPend.second = std::numeric_limits<int>::max();
		_vecPairsPend.push_back(currPend); 
	}
}

void	FordJohnson::_buildPairs() {
	std::pair<int, int> curr;
	std::size_t			i;

	for (i = 0; i < _vecInput.size() - _odd; i += 2) 
	{
		int a = _vecInput[i];
		int b = _vecInput[i + 1];
		if (a < b)
		{
			curr.first = b;
			curr.second = a;
		}
		else
		{
			curr.first = a;
			curr.second = b;
		}
		_vecPairs.push_back(curr);
	}
	_setSequenceJacobsthal(_vecPairs.size());
}

void	FordJohnson::_makePairsFromInput(void) {
	if (_vecInput.empty())
		throw (FordJohnson::ErrorException());
	_vecPairs.clear();
	_vecMain.clear();
	_vecPairsPend.clear();
	_vecPairs.reserve(_vecInput.size()/2);
	_buildPairs();
}


void	FordJohnson::_setSequenceJacobsthal(std::size_t size) {
	std::size_t	i;
	std::size_t	curr;
	_vecSequenceJacobsthal.push_back(0);
	_vecSequenceJacobsthal.push_back(1);
	for (i = 2; i < size; ++i) {
		curr = _vecSequenceJacobsthal[i - 1] + _vecSequenceJacobsthal[i - 2] * 2;
		_vecSequenceJacobsthal.push_back(curr);
	}
}
