/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 04:32:33 by ssghioua          #+#    #+#             */
/*   Updated: 2026/01/25 04:32:35 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN&	RPN::operator=(const RPN& other) {
	if (this != &other)
		_stack = other._stack;
	return (*this);
}

int	RPN::processRpn(const std::string& input) {
	std::istringstream	iSs(input);
	std::string			tok;
	
	while(!_stack.empty())
		_stack.pop();
	while (iSs >> tok)
	{
		if (tok.size() == 1 && (tok[0] >= '0' && tok[0] <= '9'))
			_stack.push(tok[0] - '0');
		else if (!_isOperator(tok) || _stack.size() < 2 || !_calculate(tok[0]))
			return (_error());
	}
	if (_stack.size() != 1)
		return (_error());
	std::cout << _stack.top() << "\n";
	return (0);
}

int	RPN::_error(void) {
	std::cerr << "Error\n";
	return (1);
}

bool	RPN::_isOperator(const std::string& c) const {
	return (c.size() == 1 && (c[0] == '+' || c[0] == '-' || c[0] == '*' || c[0] == '/'));
}

bool	RPN::_calculate(char op) {
	int	right;
	int	left;	
	int	res;
	
	if (_stack.size() < 2)
		return (false);
	right = _stack.top();
	_stack.pop();
	left = _stack.top();
	_stack.pop();
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
		if (right == 0)
			return (false);
		res = left / right;
		break;
	default:
		return (false);
	}
	_stack.push(res);
	return (true);
}
