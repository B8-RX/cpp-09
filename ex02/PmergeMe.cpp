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
	_vecInput.clear();
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
		_vecInput.push_back(static_cast<int>(nl));
	}
	_odd = _vecInput.size() % 2;
}

void	FordJohnson::displayBeforeAfter(void) const {
	std::cout << "Before: ";
	std::size_t	i;
	std::size_t placeHolderLen = 20;
	for (i = 0; i < _vecInput.size(); ++i)
	{
		if (i > placeHolderLen)
		{
			std::cout << "[...]";
			break;
		}
		std::cout << _vecInput[i] << " ";
	}
	std::cout << "\n";
	std::cout << "After: ";
	for (i = 0; i < _vMain.size(); ++i)
	{
		if (i > placeHolderLen)
		{
			std::cout << "[...]";
			break;
		}
		std::cout << _vMain[i] << " ";
	}
	std::cout << "\n";
}

template<class Container>
std::size_t	FordJohnson::_lowerBound(Container& c, std::size_t right, int x, std::size_t& count) const {
	if (c.empty())
		return (0);
	if (right > c.size())
		right = c.size();
	std::size_t left = 0;
	while (left < right)
	{
		count++;
		std::size_t mid = left + (right - left) / 2;
		if (c[mid] < x)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

std::vector<std::size_t>	FordJohnson::_setInsertionList(std::size_t n) {
	std::vector<std::size_t>	orderList;
	std::vector<bool>	used(n, false);
	if (n == 0)
		return (orderList);
	for (std::size_t i = 0; i < n && i < 2; ++i)
	{
		orderList.push_back(i);
		used[i] = true;
	}
	for (std::size_t s = 3; s < _jacobList.size() && _jacobList[s] < n; ++s)
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

template<class C_main, class C_pends>
std::size_t	FordJohnson::_insertPendJacobsthal(C_main& main, C_pends& pends) {
	std::vector<std::size_t>	order = _setInsertionList(pends.size());
	_jacobCompCount = 0;
	for (std::size_t i = 0; i < order.size(); ++i)
	{
		int big = pends[order[i]].second;
		int small = pends[order[i]].first;
		std::size_t posBig = _lowerBound(main, main.size(), big, _jacobCompCount);
		std::size_t bound = (big == std::numeric_limits<int>::max()) ? main.size() : (posBig + 1);
		std::size_t posIns = _lowerBound(main, bound, small, _jacobCompCount);
		main.insert(main.begin() + posIns, small);
	}
	return (_jacobCompCount);
}

void	FordJohnson::displayTimeDelta(void) const {
	std::cout << "Time to process a range of " << _vMain.size() << " elements with std::vector : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_vec - _t_start_vec) / CLOCKS_PER_SEC) << " ms\n";
	std::cout << "Time to process a range of " << _dMain.size() << " elements with std::deque : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_deq - _t_start_deq) / CLOCKS_PER_SEC) << " ms\n";
	// uncomment output below and in fillVector() to test comparaison count between linear insertion and Jacobsthal order insertion 
	// std::cout << "Time to process a range of " << _dMain.size() << " elements with std::vec [test] : " << std::fixed << std::setprecision(4) << 1000 * (static_cast<double>(_t_end_vecSimp - _t_start_vecSimp) / CLOCKS_PER_SEC) << " ms\n";
	// std::cout << "SIMPLE ORDER: comparaison count = " << _simpleCompCount << "\n";
	// std::cout << "JACOB ORDER: comparaison count = " << _jacobCompCount << "\n";
}

void	FordJohnson::fillDeque(void) {
	_t_start_deq = std::clock();
	_makePairsFromInput(_dPairs);
	if (_dPairs.size() > 1)
		_mergeSortPairs(_dPairs, 0, _dPairs.size() - 1);
	_buildMainAndPend(_dPairs, _dMain, _dPend);
	_insertPendJacobsthal(_dMain, _dPend);
	_t_end_deq = std::clock();
}

void	FordJohnson::fillVector(void) {
	_t_start_vec = std::clock();
	_makePairsFromInput(_vPairs);
	if (_vPairs.size() > 1)
		_mergeSortPairs(_vPairs, 0, _vPairs.size() -1);
	_buildMainAndPend(_vPairs, _vMain, _vPend);
	_jacobCompCount = _insertPendJacobsthal(_vMain, _vPend);
	_t_end_vec = std::clock();
	// uncomment to test comparaison count between linear insertion and Jacobsthal order insertion 
	// _vPairs.clear();
	// _vMain.clear();
	// _vPend.clear();
	//
	// _t_start_vecSimp = std::clock();
	// _makePairsFromInput(_vPairs);
	// if (_vPairs.size() > 1)
	// 	_mergeSortPairs(_vPairs, 0, _vPairs.size() -1);
	// _buildMainAndPend(_vPairs, _vMain, _vPend);
	// _simpleCompCount = _insertPendSimple();
	// _t_end_vecSimp = std::clock();
}

//
// std::size_t	FordJohnson::_insertPendSimple(void) {
// 	std::size_t i;
// 	_simpleCompCount = 0;
// 	for (i = 0; i < _vPend.size(); ++i)
// 	{
// 		int	small = _vPend[i].first;
// 		int	big = _vPend[i].second;
// 		std::size_t posBig = _lowerBound(_vMain, _vMain.size(), big, _simpleCompCount);
// 		std::size_t bound = (big == std::numeric_limits<int>::max()) ? _vMain.size() : (posBig + 1);
// 		std::size_t posIns = _lowerBound(_vMain, bound, small, _simpleCompCount);
// 		_vMain.insert(_vMain.begin() + posIns, small);
// 	}
// 	return (_simpleCompCount);
// }

template<class Container>
void	FordJohnson::_mergePairs(Container& c, std::size_t left, std::size_t mid, std::size_t right) {
	if (c.empty() || right >= c.size())
		return ;
	Container cTmp;
	std::size_t	i = left;
	std::size_t j = mid + 1;

	while (i <= mid && j <= right)
	{
		if (c[i].first <= c[j].first)
		{
			cTmp.push_back(c[i]);
			i++;
		}
		else 
		{
			cTmp.push_back(c[j]);
			j++;
		}
	}
	for (; i <= mid; ++i)
		cTmp.push_back(c[i]);
	for (; j <= right; ++j)
		cTmp.push_back(c[j]);
	for (std::size_t k = 0; k < cTmp.size(); ++k)
		c[left + k] = cTmp[k];
}

template<class Container>
void	FordJohnson::_mergeSortPairs(Container& c, std::size_t left, std::size_t right) {
	if (c.size() < 2 || left >= right)
		return ;
	if (right >= c.size())
		return ;
	std::size_t	mid = left + (right - left) / 2;
	FordJohnson::_mergeSortPairs(c, left, mid);
	FordJohnson::_mergeSortPairs(c, mid + 1, right);
	FordJohnson::_mergePairs(c, left, mid, right);
}

template<class C_pairs, class C_main, class C_pends> 
void	FordJohnson::_buildMainAndPend(C_pairs& vp, C_main& main, C_pends& pends) {
	std::size_t i;
	std::pair<int, int> currPend;
	main.clear();
	pends.clear();
	for (i = 0; i < vp.size(); ++i) {
		main.push_back(vp[i].first);
		currPend.first = vp[i].second;
		currPend.second = vp[i].first;
		pends.push_back(currPend); 
	}
	if (_odd)
	{
		currPend.first = _vecInput[_vecInput.size() -1];
		currPend.second = std::numeric_limits<int>::max();
		pends.push_back(currPend); 
	}
	_setSequenceJacobsthal(pends.size());
}

template<class Container> 
void	FordJohnson::_makePairsFromInput(Container& c) {
	if (_vecInput.empty())
		throw (FordJohnson::ErrorException());
	c.clear();
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
	if (!_jacobList.empty())
		_jacobList.clear();
	_jacobList.push_back(0);
	_jacobList.push_back(1);
	for (i = 2; i < size; ++i) {
		curr = _jacobList[i - 1] + _jacobList[i - 2] * 2;
		_jacobList.push_back(curr);
	}
}
