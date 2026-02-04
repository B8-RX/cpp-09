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

#include <iostream>
#include "RPN.hpp"

int	main(int argc, char **argv) {
	if (argc != 2)
	{
		std::cerr << "Error\n";
		return (1);
	}
	RPN	rpn;
	return (rpn.processRpn(argv[1]));	
}
