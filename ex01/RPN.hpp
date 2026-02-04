/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssghioua <ssghioua@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 04:28:56 by ssghioua          #+#    #+#             */
/*   Updated: 2026/01/25 04:28:57 by ssghioua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <stack>
#include <list>

class RPN {
	public:
		RPN(void);
		~RPN(void);
		RPN(const RPN&);
		RPN&			operator=(const RPN&);
		int				processRpn(const std::string& input);
	private:
		std::stack<int, std::list<int> >	_stack;
		bool			_calculate(char op);
		bool			_isOperator(const std::string& c) const;
		int				_error(void);
};

#endif // !RPN_HPP
