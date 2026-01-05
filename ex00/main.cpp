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

#include <iostream>

int	main(int argc, char **argv) {
	
	if (argc < 2)
		return (std::cerr << "Error: could not open file.\n", 1);
	try {
		// 0- create the class BitcoinExchange
		//		create one private associative arrays (_rates)
		//1- check file input
		//	if good
		//		open
		//	else
		//		throw exception (could not open file)  
		//2- clone the csv database in the containers (std::map)
		//3- iterate through input file (std::ifstream and std::getline ?), and for each line check :
		//		if invalid date format
		//			throw exception (bad input)
		//		else check if invalid value
		//			throw exception (not positive number/ too large number)
		//		else
		//			iterate on the container which contains the csv databases to find the date of the current
		//			date iteration or if not found, take the closest lower date.
		//4- print the date with the value multiplied by the exchange rate. 
		std::cout << argv[1] << "\n";	

	}
	catch (const std::exception& e) {
		std::cout << e.what() << "\n";	
	}
	return (0);
}
