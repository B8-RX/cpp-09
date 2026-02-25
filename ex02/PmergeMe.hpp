/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 01:38:45 by ssghioua          #+#    #+#             */
/*   Updated: 2026/02/13 01:38:50 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <cstddef>
#include <exception>
#include <ctime>
#include <vector>
#include <deque>
#include <utility>

class	FordJohnson {
	public:
		FordJohnson(void);
		~FordJohnson(void);
		
		class	ErrorException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error");
				}
		};
		
		
		void								parseInput(char **input, int argc);
		void								fillVector(void);
		void								fillDeque(void);
		void								displayBeforeAfter(void) const;
		void								displayTimeDelta(void) const;
	private:
		
		bool								_odd;		
		std::vector<int>					_vecInput;

		std::vector<std::pair<int, int> >	_vPairs;
		std::vector<std::pair<int, int> >	_vPend;
		std::vector<int>					_vMain;	
		
		std::deque<std::pair<int, int> >	_dPairs;
		std::deque<int>						_dMain;
		std::deque<std::pair<int, int> >	_dPend;
		
		std::clock_t						_t_start_vec;
		std::clock_t						_t_end_vec;
		std::clock_t						_t_start_deq;
		std::clock_t						_t_end_deq;
	
		template<class Container>
		void								_makePairsFromInput(Container&);
		void								_buildMainAndPend(void);
		std::size_t							_lowerBound(const std::vector<int>&,
														std::size_t bound, int x) const;
		void								_insertPendSimple(void);
		void								_insertPendJacobsthal(void);
		std::vector<std::size_t>			_setInsertionList(std::size_t n);
		void								_mergeSortPairs(std::vector<std::pair<int,int> >&,
															std::size_t left,
															std::size_t right);
		void								_mergePairs(std::vector<std::pair<int, int> >&,
														std::size_t left,
														std::size_t mid,
														std::size_t right);
		void										_setSequenceJacobsthal(std::size_t size);
		std::vector<std::size_t>					_jacobList;
};

#endif // !PMERGEME_HPP
