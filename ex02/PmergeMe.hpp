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
		void								setSequenceJacobsthal(int size);
		void								fillVector(void);
		void								fillDeque(void);
		void								displayBeforeAfter(void);
		void								displayTimeDelta(void);
	private:
		std::vector<int>					_vecInput;
		
		std::vector<std::pair<int, int> >	_vecPairs;
		std::vector<std::pair<int, int> >	_vecPairsSorted;
		std::vector<int>					_vecMain;	
		std::vector<int>					_vecSmalls;	
		
		std::deque<std::pair<int, int> >	_deqPairs;
		std::deque<int>						_deqSorted;
		
		std::clock_t						_t_start_vec;
		std::clock_t						_t_end_vec;
		std::clock_t						_t_start_deq;
		std::clock_t						_t_end_deq;
		
		void								_makePairsFromInput(void);
		void								_buildPairs(bool odd);
		void								_buildMainAndSmall(bool odd);
		void								_mergeSortPairs(std::vector<std::pair<int,int> >&,
															std::size_t left, std::size_t right);
		void								_mergePairs(std::vector<std::pair<int, int> >&, std::size_t left, std::size_t mid, std::size_t right);
		std::vector<int>					_vecSequenceJacobsthal;
};

#endif // !PMERGEME_HPP
