/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:00:34 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/21 02:30:42 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# define CUT_SETTING 500
# include <iostream>
# include <iomanip>
# include <iostream>
# include <string>
# include <string>
# include <limits>
# include <climits>
# include <time.h>
# include <sstream>
# include <cstdlib>
# include <stdexcept>
# include <sys/time.h> 
# include <list>
# include <vector>
# include <cstdarg>
# include <algorithm>

class PmergeMe
{

	public:

		PmergeMe(int ac, char **av);
		~PmergeMe();

		PmergeMe &		operator=( PmergeMe const & rhs );
		
		class Error : public std::exception
		{public: virtual const char *what() const throw()
		{	return "\033[0;31mError\033[0;37m";}};

	private:
		std::vector<int>	_vec;
		std::list<int>		_lst;
		int					_nbrElements;
		clock_t				_vecSortTimeStart;
		clock_t				_vecSortTimeEnd;
		clock_t				_lstSortTimeStart;
		clock_t				_lstSortTimeEnd;


		PmergeMe();
		PmergeMe( PmergeMe const & src );

		void vecInsertionSort(std::vector<int> &vec);
		void vecMerge(std::vector<int>::iterator left, std::vector<int>::iterator mid, std::vector<int>::iterator right);
		void vecMergeInsertSort(std::vector<int> &vec, std::vector<int>::iterator left, std::vector<int>::iterator right, int k);

		void lstInsertionSort(std::list<int> &lst);
		void lstMerge(std::list<int>::iterator left, std::list<int>::iterator mid, std::list<int>::iterator right);
		void lstMergeInsertSort(std::list<int> &lst, std::list<int>::iterator left, std::list<int>::iterator right, int k);

};

#endif /* ******************************************************** PMERGEME_H */