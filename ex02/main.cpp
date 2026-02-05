#include <algorithm>
#include <cstddef>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

int	main(int argc, char **argv) {
	if (argc == 1)
	{
		std::cerr << "Error\n";
		return (1);
	}
	std::vector<int>	vec;
	std::deque<int>		deq;

	for (int i = 1; i < argc; i++)
	{
		std::istringstream	ss(argv[i]);
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
		deq.push_back(static_cast<int>(nl));
	}
	std::cout << "Before: ";
	for (std::size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << "\n";
	std::sort(vec.begin(), vec.end());
	std::cout << "After: ";
	for (std::size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << "\n";
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
