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

#include <exception>
#include <ctime>
#include <vector>
#include <deque>
#include <utility>

class	FordJohnson {
	public:
		FordJohnson(void);
		~FordJohnson(void);
		
		void	parseInput(char **input, int argc);
		class	inputErrorException : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ("Error");
				}
		};
		void								fillVector(void);
		void								fillDeque(void);
		void								displayBeforeAfter(void);
		void								displayTimeDelta(void);
	private:
		std::vector<int>					_vecInput;
		std::vector<std::pair<int, int> >	_vecPairs;
		std::deque<std::pair<int, int> >	_deqPairs;
		std::vector<int>					_vecSorted;	
		std::deque<int>						_deqSorted;
		std::clock_t						_t_start_vec;
		std::clock_t						_t_end_vec;
		std::clock_t						_t_start_deq;
		std::clock_t						_t_end_deq;
		void								_makeVecPairs(void);
};

#endif // !PMERGEME_HPP
	   
	   // vecInput
	   
	   // vecPairs
	   // deqPairs
	   //
	   //
	   // copy input in vecInput
	   // call vecPairs and deqPairs
	   // create pairs
	   //	sort bigs/small
	   //	if input is odd 
	   //		store strugler if found
	   // sort pairs by their bigs
