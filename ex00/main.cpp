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

		// # the program take an input (a file)
		// # the program use a database in csv format (provided in the subject)
		// # the program must outputs values of bitcoins
		//
		// 0- create the class BitcoinExchange
		//		create one private associative arrays (_rates)
		// 
		// 1 - clone the csv database in an associative container (std::map/set/multiset/multimap ?)
		//		
		// 2 - check file input
		//	if good
		//		open
		//	else
		//		throw exception (could not open file) 
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
		//			valid_line(line) => return bool 
		//			valid_date(line) => return bool 
		//			valid_value(line) => return bool
		//
		// 5 - implement handle_input_line(input) 
		//		
		//   print the date with the value multiplied by the exchange rate. 
		//
		//
		std::cout << argv[1] << "\n";	

	}
	catch (const std::exception& e) {
		std::cout << e.what() << "\n";	
	}
	return (0);
}
