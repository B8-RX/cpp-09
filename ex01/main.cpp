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
		char	c;

		if ((iSs >> n))
		{
			if (iSs >> c || n >= 10)
				return (errorExit());
			stck.push(n);
		}
		else if (!isOperator(tok) || stck.size() < 2)
			return (errorExit());
		else 
			calc(tok[0], stck);
		tok = std::strtok(NULL, " ");
	}
	if (stck.size() != 1)
		return (errorExit());
	std::cout << "token: " << stck.top() << "\n";
	// take an string input OK 
	// contains mumbers and operators separate by spaces OK
	// input numbers less than 10 OK 
	// support +-*/ operators OK
	// loop on the string until EOF OK
	//	if the current element is 
	//		- number => push on stack
	//		- operators => 
	//				check if there is two number stored before
	//					if yes
	//						process the operation with the two previous numbers( maybe: calc(operator, stack.pop_back(), stack.pop_back()))
	//					if no
	//						print error and exit
	//			push the result on a the stack 
	//		- not a number/operators/stack size < 2
	//			print error and exit
	// when the loop ends
	//	check the stack size
	//		if stack size != 1
	//			print error and exit
	// output the result OK

	return (0);
}

