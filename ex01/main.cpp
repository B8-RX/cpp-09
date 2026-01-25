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
#include <queue>
#include <sstream>
#include <stack>

bool	isOperator(char* token) {
	if (token[0] != '+' && token[0] != '-' && token[0] != '*' && token[0] != '/')
		return (false);
	return (true);
}

int	errorExit(void) {
	std::cerr << "Error\n";
	return (1);
}

void	calc(char op, std::stack<double>& stack) {

	// guard for division by 0
	double	right;
	double	left;	
	double	res;

	right = stack.top();
	stack.pop();
	left = stack.top();
	stack.pop();
	switch (op) {
	case '+':
		res = left + right;
		break;
	case '-':
		res = left - right;
		break;
	case '*':
		res = left * right;
		break;
	case '/':
		res = left / right;
		break;
	default:
		break;
	}
	stack.push(res);
}

int	main(int argc, char **argv) {
	if (argc != 2)
	{
		std::cout << "Error: need one argument.\n";
		return (1);
	}
	char*	input = argv[1];
	char* tok = std::strtok(input, " ");
	std::stack<double>	stck;
	while (tok)
	{
		std::istringstream	iSs(tok);
		double	n;
		if (iSs >> n)
			stck.push(n);
		else if (!isOperator(tok))
			return (errorExit());
		else 
		{
			std::cout << "try to process operation\n";
			if (stck.size() < 2)
				return (errorExit());
			calc(tok[0], stck);
		}
		std::cout << "token: " << stck.top() << "\n";
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

