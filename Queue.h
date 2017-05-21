#ifndef CQUEUE_H
#define CQUEUE_H

#include "List.h"

using namespace HJ_ADT;

namespace HJ_QUEUE
{
	template<typename T>
	class Queue : virtual protected CDLList<T>
	{
	public:
		Queue() : head(nullptr), tail(nullptr), m_size(0), CDLList<T>() {}
		Queue(size_t n_elements, datatype datum);
		Queue(const CDLList& myList);
		Queue(iterator begin, iterator end);
		~Queue() { release(); }
	private:
		unsigned getSize() const { return m_size; }
		iterator begin() const { return head; }
		iterator end() const { return tail; }
		void push(T & datum) { CDLList<datatype>::push_back(datum); m_size++; }
		datatype & pop() { m_size--; return CDLL<datatype>::pop_front(); }
		listelem* head() { return CDLL<datatype>::head(); }
		listelem* tail() { return CDLL<datatype>::tail(); }

		unsigned m_size;
	};
	template<typename T>
	Queue<T>::Queue(size_t n_elements, datatype datum) {}

	template<typename T>
	Queue<T>::Queue(const CDLList& myList) {}
	template<typename T>
	Queue<T>::Queue(iterator begin, iterator end) {}
}


#endif