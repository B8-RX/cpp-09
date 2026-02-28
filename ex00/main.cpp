/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:51:37 by ssghioua          #+#    #+#             */
/*   Updated: 2026/01/05 01:51:38 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int	main(int argc, char **argv) {
	
	if (argc != 2)
		return (std::cerr << "Error: could not open file.\n", 1);
	try {
		BitcoinExchange	btc;
		btc.loadDataBase("./data.csv");
		btc.processInput(argv[1]);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << "\n";	
	}
	return (0);
}
