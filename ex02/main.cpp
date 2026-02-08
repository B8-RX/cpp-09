#include <algorithm>
#include <cstddef>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

int	process_vec(std::vector<int>& vec, char** input, int argc) {
	for (int i = 1; i < argc; i++)
	{
		std::istringstream	ss(input[i]);
		long				nl;
		char				extra;
		if (!(ss >> nl))
			return (std::cerr << "Error\n", 1);
		if (ss >> extra)
			return (std::cerr << "Error\n", 1);
		if (nl <= 0 || nl > std::numeric_limits<int>::max())
			return (std::cerr << "Error\n", 1);
		for (std::size_t i = 0; i < vec.size(); ++i)
		{
			if (vec[i] == (int)nl)
				return (std::cerr << "Error\n", 1);
		}
		vec.push_back(static_cast<int>(nl));
	}
	return (0);
}

int	process_deq(std::deque<int>& deq, char** input, int argc) {
	for (int i = 1; i < argc; i++)
	{
		std::istringstream	ss(input[i]);
		long				nl;
		char				extra;
		if (!(ss >> nl))
			return (std::cerr << "Error\n", 1);
		if (ss >> extra)
			return (std::cerr << "Error\n", 1);
		if (nl <= 0 || nl > std::numeric_limits<int>::max())
			return (std::cerr << "Error\n", 1);
		for (std::size_t i = 0; i < deq.size(); ++i)
		{
			if (deq[i] == (int)nl)
				return (std::cerr << "Error\n", 1);
		}
		deq.push_back(static_cast<int>(nl));
	}
	return (0);
}

int	main(int argc, char **argv) {
	if (argc == 1)
	{
		std::cerr << "Error\n";
		return (1);
	}
	std::vector<int>	vec;
	std::deque<int>		deq;
	std::clock_t	t_start_vec = std::clock();
	if (process_vec(vec, argv, argc))
		return (1);
	std::clock_t	t_end_vec = std::clock();
	std::clock_t	t_start_deq = std::clock();
	if (process_deq(deq, argv, argc))
		return (1);
	std::clock_t	t_end_deq = std::clock();

	std::cout << "vec Before: ";
	for (std::size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << "\n";
	std::sort(vec.begin(), vec.end());
	std::cout << "After: ";
	for (std::size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << "\n";
	

	std::cout << "deq Before: ";
	for (std::size_t i = 0; i < deq.size(); ++i)
		std::cout << deq[i] << " ";
	std::cout << "\n";
	std::sort(deq.begin(), deq.end());
	std::cout << "After: ";
	for (std::size_t i = 0; i < deq.size(); ++i)
		std::cout << deq[i] << " ";
	std::cout << "\n";

	std::cout << "vec processing time: " << std::fixed << std::setprecision(2) << 1000.0 * (t_end_vec - t_start_vec) / CLOCKS_PER_SEC << "\n";
	std::cout << "deq processing time: " << std::fixed << std::setprecision(2) << 1000.0 * (t_end_deq - t_start_deq) / CLOCKS_PER_SEC << "\n";
	return (0);
}

//  input : ./PmergeMe <...numbers>
//  output: 
//			- before: (unsorted input)
//			- after: (sorted input)
//			- time taken for container 1
//			- time taken for container 2
// errors:
//			empty input, negative number, INTMAX, non numeric, duplicates
