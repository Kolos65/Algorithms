
/**
*
* @file heap_sort.hpp
* @author tekda
* Heapsort
*
*/

#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include "heap.hpp"

/**
*
* Kupaccal rendező eljárás
*
* @param v rendezendő vektor
*
*/


template <class T>
void heapSort(std::vector<T>& v)
{
	Heap<T> heap(v);

	for (std::size_t i = 0; i < v.size(); ++i) {
		v[v.size() - i - 1] = heap.top();
		heap.pop();
	}
}

#endif // HEAP_SORT_HPP
