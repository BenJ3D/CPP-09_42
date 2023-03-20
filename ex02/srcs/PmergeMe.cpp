/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:00:34 by bducrocq          #+#    #+#             */
/*   Updated: 2023/03/21 00:26:46 by bducrocq         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

PmergeMe::PmergeMe(int ac, char **av)
{
	std::cout << "Before: ";
	for (int i = 1; i < ac; i++)
	{
		_vec.push_back(std::atoi(av[i]));
		_lst.push_back(std::atoi(av[i]));
		std::cout << std::atoi(av[i]) << " ";
	}
	std::cout << std::endl;

	_nbrElements = _vec.size();

	int cut = CUT_SETTING;
	_vecSortTimeStart = clock();
	vecMergeInsertSort(_vec, 0, _vec.size() - 1, cut);
	_vecSortTimeEnd = clock();

	// _lstSortTimeStart = clock();
	// lstMergeInsertSort(_lst, 0, _lst.size() - 1, cut);
	// _lstSortTimeEnd = clock();


	std::cout << std::endl << "After: ";
	for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	double cpu_time_used = ((double) (_vecSortTimeEnd - _vecSortTimeStart)) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of "<< _nbrElements << " elements with std::vector :	" << std::fixed << cpu_time_used << " us" << std::endl;
}



PmergeMe::PmergeMe(){}
PmergeMe::PmergeMe( const PmergeMe & src ){ *this = src; }
/* -------------------------------- DESTRUCTOR -------------------------------*/
PmergeMe::~PmergeMe(){}
/* --------------------------------- OVERLOAD --------------------------------*/

PmergeMe &				PmergeMe::operator=( PmergeMe const & rhs )
{
	if ( this != &rhs )
	{
		this->_lst = rhs._lst;
		this->_vec = rhs._vec;
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, PmergeMe const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


void PmergeMe::lstInsertionSort(std::list<int> &lst)
{

	if (lst.empty())
		return;

	for (std::list<int>::iterator it = ++lst.begin(); it != lst.end(); ++it)
	{
		int key = *it;
		std::list<int>::iterator jt = it;
		--jt;

		while (jt != lst.begin() && *jt > key)
		{
			std::advance(jt, 1);
			*jt = *(jt);
			std::advance(jt, -1);
		}

		if (*jt > key)
		{
			std::advance(jt, 1);
		}
		*jt = key;
	}
}

void PmergeMe::lstMerge(std::list<int> &lst, int left, int mid, int right)
{
	std::list<int> L, R;

	std::list<int>::iterator it = lst.begin();
	std::advance(it, left);

	for (int i = 0; i < mid - left + 1; ++i)
	{
		L.push_back(*it);
		++it;
	}

	for (int i = 0; i < right - mid; ++i)
	{
		R.push_back(*it);
		++it;
	}

	it = lst.begin();
	std::advance(it, left);

	std::list<int>::iterator left_it = L.begin();
	std::list<int>::iterator right_it = R.begin();

	while (left_it != L.end() && right_it != R.end())
	{
		if (*left_it <= *right_it)
		{
			*it = *left_it;
			++left_it;
		}
		else
		{
			*it = *right_it;
			++right_it;
		}
		++it;
	}

	while (left_it != L.end())
	{
		*it = *left_it;
		++left_it;
		++it;
	}

	while (right_it != R.end())
	{
		*it = *right_it;
		++right_it;
		++it;
	}
}

void PmergeMe::lstMergeInsertSort(std::list<int> &lst, int left, int right, int k)
{
	if (right <= left)
		return;

	if (right - left + 1 <= k)
	{
		lstInsertionSort(lst);
		return;
	}

	int mid = left + (right - left) / 2;
	lstMergeInsertSort(lst, left, mid, k);
	lstMergeInsertSort(lst, mid + 1, right, k);
	lstMerge(lst, left, mid, right);
}







void PmergeMe::vecInsertionSort(std::vector<int> &vec)
{
	int size = vec.size();
	for (int i = 1; i < size; ++i)
	{
		int key = vec[i];
		int j = i - 1;

		while (j >= 0 && vec[j] > key)
		{
			vec[j + 1] = vec[j];
			--j;
		}
		vec[j + 1] = key;
	}
}

void PmergeMe::vecMerge(std::vector<int> &vec, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<int> L(n1), R(n2);

	for (int i = 0; i < n1; ++i)
		L[i] = vec[left + i];
	for (int j = 0; j < n2; ++j)
		R[j] = vec[mid + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			vec[k] = L[i];
			++i;
		}
		else
		{
			vec[k] = R[j];
			++j;
		}
		++k;
	}

	while (i < n1)
	{
		vec[k] = L[i];
		++i;
		++k;
	}

	while (j < n2)
	{
		vec[k] = R[j];
		++j;
		++k;
	}
}

void PmergeMe::vecMergeInsertSort(std::vector<int> &vec, int left, int right, int k)
{
	if (right <= left)
		return;

	if (right - left + 1 <= k)
	{
		vecInsertionSort(vec);
		return;
	}

	int mid = left + (right - left) / 2;
	vecMergeInsertSort(vec, left, mid, k);
	vecMergeInsertSort(vec, mid + 1, right, k);
	vecMerge(vec, left, mid, right);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */