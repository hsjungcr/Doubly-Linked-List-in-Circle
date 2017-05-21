//-----------------------------------------------------------------------------
//	File:	List.h
//
//	Class:	List
//-----------------------------------------------------------------------------
#ifndef CDLIST_H
#define CDLIST_H

#include <iostream>
#include <cassert>
#include <exception>
#include <cstdlib>
#include <iterator>
#define CATCH_CONFIG_MAIN
#include "Catch.hpp"
//-----------------------------------------------------------------------------
//	Class: List
//	Title: List Class
//	
//	Description: This file contains the class definition for List Class
//
//	Programmer: Paul Bladek
//				Han Jung
//
//	Date: 5/4/2017
//	Version: 1.0
//	Enviornment: Intel i5-6600
//	SoftWare: MS Window 10 Enterprise 64-bit(10.0, Build 14393)
//	Compiles under Microsoft Visual C++.Net 2015
//	
//
//   class list:
//
//     Properties:
//       listelem *head -- front end of list
//       listelem *tail -- back end of list
//       unsigned m_size -- number of elements in the list
//
//     Methods:
// 
//       inline: 
//         list() -- construct the empty list
//         list(size_t n_elements, datatype datum) -- create a list of a specific size, all elements the same
//         ~list() { release(); } -- destructor
//         unsigned getSize()const  -- accessor, returns m_size
//         iterator begin()const -- returns address of first element
//         iterator end()const -- returns address of last element
//         datatype& front()const  -- returns first element data
//         datatype& back()const -- returns last element data
//         bool empty()const -- true if no elements
//
//       non-inline:
//         list(const list& x); -- copy constructor
//         list(iterator b, iterator e) -- constructor using iterators
//         void push_front(datatype datum) -- insert element at front of list
//         datatype pop_front(); -- removes front element and returns the data from that element
//         void push_back(datatype datum) -- insert element at back of list 
//         datatype pop_back() -- removes back element and returns the data from that element
//         void release() -- removes all items from list
//         list operator=(const list & rlist) -- returns a copy of rlist
//         datatype& operator[](int index) -- for l-value
//         const datatype& operator[](int index)const -- for r-value
//
//    Public Nested Structures:
//
//      struct listelem -- list cell
//
//        properties:
//          datatype data -- the actual datum
//          listelem *next -- forward link
//          listelem *prev -- backward link
//        constructor:
//          listelem(datatype c, listelem* p, listelem* n, listelem* p) -- struct constructor
//
//     class iterator
//        Public Methods
// 
//           inline: 
//            listelem* operator->() -- same as for pointer
//            datatype& operator*() -- same as for pointer
//            operator listelem*() -- conversion
//            iterator(listelem* p = nullptr) -- constructor
// 
//           non-inline: 
//            iterator operator++() -- pre-increment
//            iterator operator--() -- pre-decrement
//            iterator operator++(int) -- post-increment
//            iterator operator--(int) -- post-decrement
// 
//        Private Properties
//            listelem* ptr -- current listelem or NULL
//
//   History Log:
//     summer, 1996 original  IP completed version 1.0 
//     May 11, 2000,  PB  completed version 1.01 
//     March 8, 2002, PB  completed version 1.02 
//     April 10, 2003, PB  completed version 1.03 
//     April 30, 2003, PB  completed version 1.04 
//     May 10, 2005, PB  completed version 1.05 
//     April 15, 2008, PB  completed version 1.06
//     April 20, 2010, PB completed version 1.07 
//     April 15, 2011, PB completed version 1.09 
//	   May 4, 2017, HJ completed version 1.10
//-----------------------------------------------------------------------------
using namespace std;
namespace HJ_ADT
{
	typedef int datatype;

	template <typename T> 
	class CDLList
	{
	public:
		struct listelem;
		class iterator;
		// constructors
		CDLList() : head(nullptr), tail(nullptr), m_size(0) {}
		CDLList(size_t n_elements, datatype datum);
		CDLList(const CDLList& myList);
		CDLList(iterator begin, iterator end);
		// destructor
		~CDLList() { release(); }
		// functions
		virtual unsigned getSize() const { return m_size; }
		virtual iterator begin() const { return head; }
		virtual iterator end() const { return tail; }
		void push_front(datatype datum);
		datatype pop_front();
		void push_back(datatype datum);
		datatype pop_back();
		datatype& front() const { return head->data; }
		datatype& back() const { return tail->data; }
		bool empty()const { return head == nullptr || tail == nullptr; }
		void release();
		//overloaded operator
		CDLList operator=(const CDLList & rlist);
		datatype& operator[](int index);
		const datatype& operator[](int index) const;
	private:
		listelem *head;
		listelem *tail;
		unsigned m_size; // number of elements in the list 
	public:
		struct listelem // list cell
		{
			datatype data;
			listelem *next;
			listelem *prev;
			listelem(datatype datum, listelem* p, listelem* n) 
				: data(datum), prev(p), next(n) {} // struct constructor
		};
		// scoped within class list !
		class iterator
		{
		public:
			iterator(listelem* p = nullptr) : ptr(p) {}
			iterator operator++();
			iterator operator--();
			iterator operator++(int);
			iterator operator--(int);
			listelem* operator->() const { return ptr; }
			datatype& operator*() const { return ptr->data; }
			operator listelem*() const { return ptr; }
		private:
			listelem* ptr; //current listelem or nullptr
		};
	};
	ostream& operator<<(ostream& sout, const CDLList<class T>& x);
	//-----------------------------------------------------------------------------
	// constructor
	//-----------------------------------------------------------------------------
	template<typename T>
	CDLList<T>::CDLList(size_t n_elements, datatype datum)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		if (n_elements <= 0)
			throw out_of_range("Empty list");
		for (size_t i = 0; i < n_elements; ++i)
			push_front(datum);
	}
	//-----------------------------------------------------------------------------
	// copy constructor
	//-----------------------------------------------------------------------------
	template<typename T>
	CDLList<T>::CDLList(const CDLList& myList)
		: m_size(0), head(nullptr), tail(nullptr)
	{
		CDLList<T>::iterator r_it = myList.begin();
		while (r_it != nullptr)
			push_front(*r_it++);
	}
	//-----------------------------------------------------------------------------
	// constructor using iterators, copies from b to one before e
	//-----------------------------------------------------------------------------
	template<typename T>
	CDLList<T>::CDLList(iterator begin, iterator end)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		while (begin != end)
			push_front(*begin++);
	}
	//-----------------------------------------------------------------------------
	// empties the list
	//-----------------------------------------------------------------------------
	template<typename T>
	void CDLList<T>::release()
	{
		while (head != nullptr)
			pop_front();
	}

	//-----------------------------------------------------------------------------
	// insert element at front of list
	//-----------------------------------------------------------------------------
	template<typename T>
	void CDLList<T>::push_front(datatype datum)
	{
		listelem* temp = new listelem(datum, tail, head);
		m_size++;
		if (!empty())
		{ // was a nonempty list
			head->prev = temp;
			head = temp;
			tail->next = head;
		}
		else
			head = tail = temp;
	}
	//-----------------------------------------------------------------------------
	// removes front element and returns the data from that element
	//-----------------------------------------------------------------------------
	template<typename T>
	datatype CDLList<T>::pop_front()
	{
		if (head == nullptr)
			throw runtime_error("empty list");
		m_size--;
		datatype data = head->data;
		iterator temp = begin();
		temp++;
		delete head;
		head = temp;
		if (!empty()) {
			head->prev = tail;
			tail->next = head;
		}
		else
			tail = nullptr; // empty at both ends
		return data;
	}
	//-----------------------------------------------------------------------------
	// insert element at end of list
	//-----------------------------------------------------------------------------
	template<typename T>
	void CDLList<T>::push_back(datatype datum)
	{
		
			listelem* temp = new listelem(datum, tail, head); // takes data prev - tail
			m_size++;										  // next - head
			if (!empty())
			{ // was a nonempty list
				tail->next = temp;   // current tail's next is temp
				head->prev = temp;	 // current head's prev is temp for circuly
				tail = temp;
			}
			else
				head = tail = temp;
	}
	//-----------------------------------------------------------------------------
	// removes end element and returns the data from that element
	//-----------------------------------------------------------------------------
	template<typename T>
	datatype CDLList<T>::pop_back()
	{//convert from front to back!
		if (head == nullptr)
			throw runtime_error("empty list");
		m_size--;
		datatype data = tail->data; //save tail's data
		iterator temp = end(); //temp = tail
		temp--; //set iterator to previous
		delete tail;
		tail = temp; // tail is now n-1
		if (!empty()) {
			head->prev = tail; //before head is tail
			tail->next = head; //after tail is head
		}
		else
			tail = nullptr; // empty at both ends
		return data;
	}

	//-----------------------------------------------------------------------------
	// prints out a list
	//-----------------------------------------------------------------------------
	template<typename T>
	ostream& operator<<(ostream& sout, const CDLList<T>& myList)
	{
		list::iterator p = myList.begin();
		sout << "(";
		while (p != nullptr)
		{
			sout << *p;
			if (p != myList.end())
				sout << ",";
			++p; // advances iterator using next
		}
		sout << ")\n";
		return sout;
	}
	//-----------------------------------------------------------------------------
	// returns a copy of rlist
	//-----------------------------------------------------------------------------
	template<typename T>
	CDLList<T> CDLList<T>::operator=(const CDLList & rlist)
	{
		if (&rlist != this)
		{
			CDLList::iterator r_it = rlist.begin();
			release();
			while (r_it != 0)
				push_front(*r_it++);
		}
		return *this;
	}
	//-----------------------------------------------------------------------------
	// pre-increment
	//-----------------------------------------------------------------------------
	template<typename T>
	typename CDLList<T>::iterator CDLList<T>::iterator::operator++()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->next;
		return *this;
	}
	//-----------------------------------------------------------------------------
	// post-increment
	//-----------------------------------------------------------------------------
	template<typename T>
	typename CDLList<T>::iterator CDLList<T>::iterator::operator++(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->next;
		return temp;
	}
	//-----------------------------------------------------------------------------
	// pre-decrement
	//-----------------------------------------------------------------------------
	template<typename T>
	typename CDLList<T>::iterator CDLList<T>::iterator::operator--()
	{
		// replace the dummy code below with your own
		iterator temp = nullptr;
		return temp;
	}
	//-----------------------------------------------------------------------------
	// post-decrement
	//-----------------------------------------------------------------------------
	template<typename T>
	typename CDLList<T>::iterator CDLList<T>::iterator::operator--(int)
	{
		// replace the dummy code below with your own
		iterator temp = nullptr;
		return temp;
	}
	//-----------------------------------------------------------------------------
	// [] operator -- l-value
	//-----------------------------------------------------------------------------
	template<typename T>
	datatype& CDLList<T>::operator[](int index)
	{
		iterator it;
		if (index >= 0)
		{
			if (index >= static_cast<int>(getsize()))
				throw out_of_range("index out-of-range");
			it = begin();
			for (int i = 0; i < index; i++)
				it++;
		}
		else
		{
			if (index < -(static_cast<int>(getsize())))
				throw out_of_range("index out-of-range");
			it = end();
			for (int i = -1; i > index; i--)
				it--;
		}
		return *it;
	}
	//-----------------------------------------------------------------------------
	// [] operator -- r-value
	//-----------------------------------------------------------------------------

	template<typename T>
	const datatype& CDLList<T>::operator[](int index)const
	{
		iterator it;
		if (index >= 0)
		{
			if (index >= static_cast<int>(getsize()))
				throw out_of_range("index out-of-range");
			it = begin();
			for (int i = 0; i < index; i++)
				it++;
		}
		else
		{
			if (index < -(static_cast<int>(getsize())))
				//throw out_of_range("index out-of-range");
				it = end();
			for (int i = -1; i > index; i--)
				it--;
		}
		return *it;
	}
}

#endif