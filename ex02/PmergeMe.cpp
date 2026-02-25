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
	for (i = 0; i < _vMain.size(); ++i)
		std::cout << _vMain[i] << " ";
	
	std::cout << "\n";
	std::cout << "Jacobsthal seq: ";
	for (i = 0; i < _jacobList.size(); ++i)
		std::cout << _jacobList[i] << " ";
	
	std::cout << "\n";
	std::cout << "Pair->first:  ";
	for (i = 0; i < _vPairs.size(); ++i)
		std::cout << _vPairs[i].first << " ";
	std::cout << "\n";
	std::cout << "Pair->second: ";
	for (i = 0; i < _vPairs.size(); ++i)
		std::cout << _vPairs[i].second << " ";
	std::cout << "\n";
	
	std::cout << "Main:   ";
	for (i = 0; i < _vMain.size(); ++i)
		std::cout << _vMain[i] << "    ";
	std::cout << "\n";
	std::cout << "Smalls: ";
	for (i = 0; i < _vPend.size(); ++i)
		std::cout << _vPend[i].first << "    ";
	std::cout << "\n";
}

void	FordJohnson::_insertPendSimple(void) {
	std::size_t i;
	for (i = 0; i < _vPend.size(); ++i)
	{
		int	small = _vPend[i].first;
		int	big = _vPend[i].second;
		std::size_t posBig = _lowerBound(_vMain, _vMain.size(), big);
		std::size_t bound = (big == std::numeric_limits<int>::max()) ? _vMain.size() : (posBig + 1);
		std::size_t posIns = _lowerBound(_vMain, bound, small);
		_vMain.insert(_vMain.begin() + posIns, small);
	}
}

std::vector<std::size_t>	FordJohnson::_setInsertionList(std::size_t n) {
	std::vector<std::size_t>	orderList;
	std::vector<bool>	used(n, false);
	if (n == 0)
		return (orderList);
	for (std::size_t i = 0; i <= n && i < 2; ++i)
	{
		orderList.push_back(i);
		used[i] = true;
	}
	for (std::size_t s = 2; _jacobList[s] < _vPend.size(); ++s)
	{
		std::size_t j = _jacobList[s];
		if (j >= n)
			break;
		std::size_t prev = _jacobList[s - 1];
		for (std::size_t k = j + 1; k-- > prev + 1;)
		{
			if (!used[k])
			{
				orderList.push_back(k);
				used[k] = true;
			}
		}
	}
	for (std::size_t k = 0; k < n; ++k)
	{
		if (!used[k])
		{
			orderList.push_back(k);
			used[k] = true;
		}		
	}
	return (orderList);
}

void	FordJohnson::_insertPendJacobsthal(void) {
	std::vector<std::size_t>	order = _setInsertionList(_vPend.size());
	for (std::size_t i = 0; i < _vPend.size(); ++i)
	{
		int big = _vPend[i].second;
		int small = _vPend[i].first;
		std::size_t posBig = _lowerBound(_vMain, _vMain.size(), big);
		std::size_t bound = big == std::numeric_limits<int>::max() ? _vMain.size() : posBig;
		std::size_t posIns = _lowerBound(_vMain, bound, small);
		_vMain.insert(_vMain.begin() + posIns, small);
	}

}

void	FordJohnson::displayTimeDelta(void) const {
	std::cout << "Time to process a range of " << _vMain.size() << " elements with std::vector : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_vec - _t_start_vec) / CLOCKS_PER_SEC) << " ms\n";
	std::cout << "Time to process a range of " << _dMain.size() << " elements with std::deque : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_deq - _t_start_deq) / CLOCKS_PER_SEC) << " ms\n";
}


void	FordJohnson::fillVector(void) {
	if (!_vPairs.empty())
	{
		_vPairs.clear();
		_vMain.clear();
		_vPend.clear();
	}
	_t_start_vec = std::clock();
	_makePairsFromInput(_vPairs);
	if (_vPairs.size() > 1)
		_mergeSortPairs(_vPairs, 0, _vPairs.size() -1);
	_buildMainAndPend();
	// _insertPendSimple();
	_insertPendJacobsthal();
	_t_end_vec = std::clock();
}

void	FordJohnson::fillDeque(void) {
	if (!_dPairs.empty())
	{
		_dPairs.clear();	
		_dMain.clear();
		_dPend.clear();
	}
	_t_start_deq = std::clock();
	// _makePairsFromInput(_dPairs);
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

void	FordJohnson::_buildMainAndPend(void) {
	if (!_vPend.empty() || !_vMain.empty())
	{
		_vPend.clear();
		_vMain.clear();
	}
	std::size_t	sizePend = _vPairs.size() + (_odd ? 1 : 0); 
	_vPend.reserve(sizePend);
	std::size_t i;
	std::pair<int, int> currPend;
	for (i = 0; i < _vPairs.size(); ++i) {
		_vMain.push_back(_vPairs[i].first);
		currPend.first = _vPairs[i].second;
		currPend.second = _vPairs[i].first;
		_vPend.push_back(currPend); 
	}
	if (_odd)
	{
		currPend.first = _vecInput[_vecInput.size() -1];
		currPend.second = std::numeric_limits<int>::max();
		_vPend.push_back(currPend); 
	}
	_setSequenceJacobsthal(_vPend.size());
}

template<class Container> 
void	FordJohnson::_makePairsFromInput(Container& c) {
	if (_vecInput.empty())
		throw (FordJohnson::ErrorException());
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
		c.push_back(curr);
	}
}


void	FordJohnson::_setSequenceJacobsthal(std::size_t size) {
	std::size_t	i;
	std::size_t	curr;
	_jacobList.push_back(0);
	_jacobList.push_back(1);
	for (i = 2; i < size; ++i) {
		curr = _jacobList[i - 1] + _jacobList[i - 2] * 2;
		_jacobList.push_back(curr);
	}
}
