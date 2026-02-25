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

#include <ctime>
#include <exception>
#include <iostream>
#include "PmergeMe.hpp"

int	main(int argc, char **argv) {
	if (argc == 1)
	{
		std::cerr << "Error\n";
		return (1);
	}
	try {
		FordJohnson	pmergeMe;
		pmergeMe.parseInput(argv, argc);
		pmergeMe.fillVector();
		pmergeMe.fillDeque();
		pmergeMe.displayBeforeAfter();
		pmergeMe.displayTimeDelta();
	} catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		return (1);
	}
	return (0);
}
