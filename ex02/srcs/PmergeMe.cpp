/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:00:34 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/21 03:06:12 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

PmergeMe::PmergeMe(int ac, char **av)
{
	for (int i = 1; i < ac; i++)
	{
		std::string	str = av[i];
		for(std::size_t i = 0; i < str.length(); ++i)
		{
			if (!std::isdigit(str[i]))
				throw Error();
		}
		long nb = std::atol(av[i]);
		if (nb < 0 || nb > INT_MAX)
			throw Error();
		_vec.push_back(static_cast<int>(nb));
		_lst.push_back(static_cast<int>(nb));
	}
	// Afficher le contenu de vector "Before"
	std::cout << "\033[0;33mBefore: \033[0;35m";
	for (std::vector<int>::iterator it =  _vec.begin(); it != _vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	_nbrElements = _vec.size();
	int cut = _nbrElements / 10;
	timeval start_vec, end_vec, start_lst, end_lst;
	gettimeofday(&start_vec, NULL);
	vecMergeInsertSort(_vec, _vec.begin(), _vec.end(), cut);
	gettimeofday(&end_vec, NULL);
	long elapsed_time_vec = (end_vec.tv_sec - start_vec.tv_sec) * 1000000 + (end_vec.tv_usec - start_vec.tv_usec);
	gettimeofday(&start_lst, NULL);
	lstMergeInsertSort(_lst, _lst.begin(), _lst.end(), cut);
	gettimeofday(&end_lst, NULL);
	long elapsed_time_lst = (end_lst.tv_sec - start_lst.tv_sec) * 1000000 + (end_lst.tv_usec - start_lst.tv_usec);

	// Afficher le contenu de vector "After"
	std::cout << "\033[0;33mAfter: \033[0;32m";
	for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << COLOR_NONE << std::endl;
	std::cout << "Time to process a range of "<< _nbrElements << " elements with std::vector<int>	: " << std::setw(12) << std::right << elapsed_time_vec << " us" << std::endl;
	std::cout << "Time to process a range of "<< _nbrElements << " elements with std::list<int>	: " << std::setw(12) << std::right << elapsed_time_lst << " us" << std::endl;
}



PmergeMe::PmergeMe(){}
PmergeMe::PmergeMe( const PmergeMe & src ){ *this = src; }
/* -------------------------------- DESTRUCTOR -------------------------------*/
PmergeMe::~PmergeMe(){}
/* --------------------------------- OVERLOAD --------------------------------*/

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs)
{
	if (this != &rhs)
	{
		this->_lst = rhs._lst;
		this->_vec = rhs._vec;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*--------------------------------- LIST -------------------------------------*/
void PmergeMe::lstInsertionSort(std::list<int> &lst)
{
	for (std::list<int>::iterator it = ++lst.begin(); it != lst.end(); ++it)
	{
		int key = *it;
		std::list<int>::iterator jt = it;
		--jt;

		while (jt != lst.begin() && *jt > key)
		{
			std::list<int>::iterator prev = jt;
			--prev;
			std::swap(*jt, *prev);
			jt = prev;
		}
		if (*jt > key)
			std::swap(*jt, *it);
	}
}

void PmergeMe::lstMerge(std::list<int>::iterator left,
					std::list<int>::iterator mid, std::list<int>::iterator right)
{
	std::list<int> L(left, mid);
	std::list<int> R(mid, right);

	std::list<int>::iterator itL = L.begin(), itR = R.begin();

	for (std::list<int>::iterator it = left; it != right; ++it)
	{
		if (itL != L.end() && (itR == R.end() || *itL <= *itR))
		{
			*it = *itL;
			++itL;
		}
		else if (itR != R.end())
		{
			*it = *itR;
			++itR;
		}
	}
}

void PmergeMe::lstMergeInsertSort(std::list<int> &lst,
			std::list<int>::iterator left, std::list<int>::iterator right, int k)
{
	if (std::distance(left, right) <= 1)
		return;

	if (std::distance(left, right) <= k)
	{
		lstInsertionSort(lst);
		return;
	}

	std::list<int>::iterator mid = left;
	std::advance(mid, std::distance(left, right) / 2);

	lstMergeInsertSort(lst, left, mid, k);
	lstMergeInsertSort(lst, mid, right, k);
	lstMerge(left, mid, right);
}

/*------------------------------- VECTOR -------------------------------------*/
void PmergeMe::vecInsertionSort(std::vector<int> &vec)
{
	std::vector<int>::iterator size = vec.end();
	for (std::vector<int>::iterator i = vec.begin() + 1; i != size; ++i)
	{
		int key = *i;
		std::vector<int>::iterator j = i - 1;

		while (j >= vec.begin() && *j > key)
		{
			*(j + 1) = *j;
			--j;
		}
		*(j + 1) = key;
	}
}

void PmergeMe::vecMerge(std::vector<int>::iterator left, 
				std::vector<int>::iterator mid, std::vector<int>::iterator right)
{
	std::vector<int> L(left, mid);
	std::vector<int> R(mid, right);
	std::vector<int>::iterator itL = L.begin(), itR = R.begin();

	for (std::vector<int>::iterator it = left; it != right; ++it)
	{
		if (itL != L.end() && (itR == R.end() || *itL <= *itR))
		{
			*it = *itL;
			++itL;
		}
		else if (itR != R.end())
		{
			*it = *itR;
			++itR;
		}
	}
}

void PmergeMe::vecMergeInsertSort(std::vector<int> &vec, 
	std::vector<int>::iterator left, std::vector<int>::iterator right, int k)
{
	if (right <= left)
		return;

	if (std::distance(left, right) <= k)
	{
		vecInsertionSort(vec);
		return;
	}

	std::vector<int>::iterator mid = left + (right - left) / 2;
	vecMergeInsertSort(vec, left, mid, k);
	vecMergeInsertSort(vec, mid + 1, right, k);
	vecMerge(left, mid, right);
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */