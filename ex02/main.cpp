/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 04:05:53 by ssghioua          #+#    #+#             */
/*   Updated: 2026/02/09 04:05:54 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <ctime>
#include <deque>
#include <exception>
#include <iomanip>
#include <iostream>
#include "PmergeMe.hpp"

int	main(int argc, char **argv) {
	if (argc == 1)
	{
		std::cerr << "Error\n";
		return (1);
	}
	try {
		FordJohnson	pmergeMe(argv, argc);
	} catch (const std::exception& e) {
		std::cout << e.what() << "\n";
		return (1);
	}
	return (0);
}

//  input : ./PmergeMe <...numbers>
//  output: 
//			- before: (unsorted input)
//			- after: (sorted input)
//			- time taken for container 1
//			- time taken for container 2
// errors:
//			empty input, negative number, INTMAX, non numeric, duplicates
