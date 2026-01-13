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
	
	if (argc < 2)
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


		// # the program take an input (a file)
		// # the program use a database in csv format (provided in the subject)
		// # the program must outputs values of bitcoins
		//
		// 0- create the class BitcoinExchange DONE
		//		create:
		//			private associative arrays:  std::map<std::string, double>
		//			public fonctions:
		//				to load csc database: loadDataBase()  
		//				to process input.txt: processInput()
		//
		// 1 - clone the csv database DONE
		//	if !is_open()
		//		throw exception (Error: could not open file) 
		//	if empty
		//		throw exception (Error: could not open file) 
		//  loop on the csv database:
		//		for each line:
		//			store key (date) and value (rate) in the private container.
		//		at the end if container is empty:
		//			throw exception (Error: empty database)
		//
		// 2 - verify file input
		//	if !is_open()
		//		throw exception (Error: could not open file) 
		//  loop on the file.txt:
		//		for each line check:
		//			if  valid line format ("Date | value") 
		//				&& valid date(format "YEAR-MONTH-DAY" and based on calendar ?)
		//				&& valid value (INT or Float && between 0 and 1000) 
		//					handle_input_line(line);
		//			else
		//				display "Error: bad input" + input; 
		// 
		// 4 - implement helpers
		//			valid_line() => return bool 
		//			valid_date() => return bool 
		//			valid_value() => return bool
		//
		//   print the date with the value multiplied by the exchange rate. 
		//
		//


