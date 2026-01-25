/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 23:41:11 by ssghioua          #+#    #+#             */
/*   Updated: 2026/01/23 23:41:12 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>
#include <sstream>

bool	isOperator(char* token) {
	if (token[0] != '+' && token[0] != '-' && token[0] != '*' && token[0] != '/')
		return (false);
	return (true);
}

int	main(int argc, char **argv) {
	if (argc != 2)
	{
		std::cout << "Error: need one argument.\n";
		return (1);
	}
	char*	input = argv[1];
	char* tok = std::strtok(input, " ");
	while (tok)
	{
		std::istringstream	iSs(tok);
		double	n;
		if (!isOperator(tok) && !(iSs >> n))
		{
			std::cerr << "Error\n";
			return (1);
		}
		std::cout << "token: " << tok << "\n";
		tok = std::strtok(NULL, " ");
	}
	// take an string input 
	// contains mumbers and operators separate by spaces
	// less than 10 numbers
	// support +-*/ operators
	// loop on the string until EOF
	//	if the current element is 
	//		- number => push on stack
	//		- space => skip
	//		- operators => 
	//				check if there is two number stored before
	//					if yes
	//						process the operation with the two previous numbers( maybe: calc(operator, stack.pop_back(), stack.pop_back()))
	//					if no
	//						print error and exit
	//			push the result on a the stack 
	//		- not a number/space/operators
	//			print error and exit
	// output the result

	return (0);
}

