/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:00:34 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/20 23:43:20 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# define CUT_SETTING 3
# include <iostream>
# include <iomanip>
# include <string>
# include <string>
# include <time.h>
# include <sstream>
# include <cstdlib>
# include <stdexcept>
# include <list>
# include <vector>
# include <cstdarg>

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
		void vecMerge(std::vector<int> &vec, int left, int mid, int right);
		void vecMergeInsertSort(std::vector<int> &vec, int left, int right, int k);

		void lstInsertionSort(std::list<int> &lst);
		void lstMerge(std::list<int> &lst, int left, int mid, int right);
		void lstMergeInsertSort(std::list<int> &lst, int left, int right, int k);
};

std::ostream &			operator<<( std::ostream & o, PmergeMe const & i );

#endif /* ******************************************************** PMERGEME_H */