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
//        Protected Properties
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
	template <typename datatype>
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
		unsigned getSize() const { return m_size; }
		iterator begin() const { return head; }
		iterator end() const { return tail; }
		void push_front(datatype datum);
		datatype pop_front();
		void push_back(datatype datum);
		datatype pop_back();
		datatype& front() const { return head->data; }
		datatype& back() const { return tail->data; }
		virtual bool empty()const { return head == nullptr || tail == nullptr; }
		virtual void release();
		//overloaded operator
		CDLList operator=(const CDLList & rlist);
		datatype& operator[](int index);
		const datatype& operator[](int index) const;
	protected:
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
		protected:
			listelem* ptr; //current listelem or nullptr
		};
	};
	template<typename datatype>
	ostream& operator<<(ostream& sout, const CDLList<datatype>& myList);
	//------------------------------------------------------------------------
	//		class:			CDLList
	//		method:			CDLList(size_t n_elements, datatype datum)
	//		description:	Constructor that initializes class with size of
	//						n_element and with datum for each element
	//		calls:			push_front()
	//		called by:		main()
	//		parameters:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	CDLList<datatype>::CDLList(size_t n_elements, datatype datum)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		if (n_elements <= 0)
			throw out_of_range("Empty list");
		for (size_t i = 0; i < n_elements; ++i)
			push_front(datum);
	}
	//------------------------------------------------------------------------
	//		class:			CDLList
	//		method:			CDLList(const CDLList& myList)
	//		description:	Copy Constructor to copy to new class
	//		calls:			push_front()
	//		called by:		n/a
	//		parameters:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	CDLList<datatype>::CDLList(const CDLList& myList)
		: m_size(0), head(nullptr), tail(nullptr)
	{
		CDLList<datatype>::iterator r_it = myList.begin();
		while (r_it != nullptr)
			push_front(*r_it++);
	}
	//------------------------------------------------------------------------
	//		class:			CDLList
	//		method:			CDLList(iterator begin, iterator end)
	//		description:	Constructor using iterator
	//		calls:			push_front()
	//		called by:		n/a
	//		parameters:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	CDLList<datatype>::CDLList(iterator begin, iterator end)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		while (begin != end)
			push_front(*begin++);
	}
	//------------------------------------------------------------------------
	//		class:			CDLList
	//		method:			release()
	//		description:	release all contents of the list
	//		calls:			pop_front()
	//		called by:		~CDLList()
	//						main()
	//		parameters:		n/a
	//		returns:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	void CDLList<datatype>::release()
	{
		listelem* current = tail;
		listelem* temp;
		head = nullptr;
		while (current != nullptr) {
			current = tail;
			pop_front();
			temp = current;
			delete temp;
		}
	}
	//------------------------------------------------------------------------
	//		class:			CDLList
	//		method:			push_front(datatype datum)
	//		description:	pushes data in front of the list
	//		calls:			empty()
	//		called by:		constructor
	//						main()
	//						operator=()
	//		parameters:		datatype datum -- data to be put in
	//		returns:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	void CDLList<datatype>::push_front(datatype datum)
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
	//------------------------------------------------------------------------
	//		class:			CDLList
	//		method:			pop_front()
	//		description:	remove front most data from the list
	//		calls:			empty()
	//						begin()
	//		called by:		release()
	//						main()
	//
	//		parameters:		n/a
	//		returns:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	datatype CDLList<datatype>::pop_front()
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
		else {
			head = tail = nullptr; // empty at both ends
		}
		return data;
	}
	//------------------------------------------------------------------------
	//		class:			CDLList
	//		method:			push_back(datatype datum)
	//		description:	pushes data in back of the list
	//		calls:			empty()
	//		called by:		main()
	//						
	//		parameters:		datatype datum -- data to be put in
	//		returns:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	void CDLList<datatype>::push_back(datatype datum)
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
	//------------------------------------------------------------------------
	//		class:			CDLList
	//		method:			pop_back()
	//		description:	remove the last data of the list
	//		calls:			empty()
	//		called by:		main()
	//						
	//		parameters:		n/a
	//		returns:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	datatype CDLList<datatype>::pop_back()
	{//convert from front to back!
		if (tail == nullptr)
			throw runtime_error("empty list");
		m_size--;
		datatype data = tail->data; //save tail's data
		iterator temp = end(); //temp = tail
		temp--;//set iterator to previous
		delete tail;
		tail = temp; // tail is now n-1
		if (!empty()) {
			head->prev = tail; //before head is tail
			tail->next = head; //after tail is head
		}
		else {
			head = tail = nullptr; // empty at both ends
		}
		return data;
	}
	//------------------------------------------------------------------------
	//		method:			operator<<(ostream& sout, const 
	//							CDLList<datatype>& myList)
	//		description:	returns contents of the list to the ostream
	//		calls:			end()
	//						begin()
	//		called by:		main()
	//						
	//		parameters:		ostream& sout -- stream to write to 
	//						const CDLList<datatype>& myList -- List of data
	//		returns:		ostream&
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	ostream& operator<<(ostream& sout, const CDLList<datatype>& myList)
	{
		CDLList<datatype>::iterator p = myList.begin();

		sout << "(";
		while (p != myList.end())
		{
			sout << *p;
			if (p != myList.end())
				sout << ",";
			++p; // advances iterator using next
		}
		sout << *myList.end();
		sout << ")\n";

		return sout;
	}
	//------------------------------------------------------------------------
	//		class:			CDLList
	//		method:			operator=(const CDLList & rlist)
	//		description:	Override assignment operator for CDLList
	//		calls:			push_front()
	//		called by:		main()
	//						operator <<()
	//		parameters:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	CDLList<datatype> CDLList<datatype>::operator=(const CDLList & rlist)
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
	//------------------------------------------------------------------------
	//		class:			CDLList::iterator
	//		method:			operator++()
	//		description:	pre increment the iterator by 1
	//		calls:			n/a
	//		called by:		constructor
	//						push_front()
	//						pop_front()
	//						push_back()
	//						operator=()
	//						operator[]()
	//						main()
	//						operator <<()
	//		parameters:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	typename CDLList<datatype>::iterator CDLList<datatype>::iterator::operator++()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->next;
		return *this;
	}
	//------------------------------------------------------------------------
	//		class:			CDLList::iterator
	//		method:			operator++(int)
	//		description:	post increment the iterator by 1
	//		calls:			n/a
	//		called by:		push_front()
	//						pop_front()
	//						push_back()
	//						operator=()
	//						operator[]()
	//						main()
	//						operator <<()
	//		parameters:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	typename CDLList<datatype>::iterator CDLList<datatype>::iterator::operator++(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->next;
		return temp;
	}
	//------------------------------------------------------------------------
	//		class:			CDLList::iterator
	//		method:			operator--()
	//		description:	pre decrement the iterator by 1
	//		calls:			n/a
	//		called by:		constructor
	//						pop_front()
	//						pop_back()
	//						operator[]()
	//						main()
	//		parameters:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	typename CDLList<datatype>::iterator CDLList<datatype>::iterator::operator--()
	{
		// dummy code has been replaced
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->prev;
		return *this;
	}
	//------------------------------------------------------------------------
	//		class:			CDLList::iterator
	//		method:			operator--(int)
	//		description:	post decrement the iterator by 1
	//		calls:			n/a
	//		called by:		constructor
	//						pop_front()
	//						pop_back()
	//						operator[]()
	//						main()
	//		parameters:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	typename CDLList<datatype>::iterator CDLList<datatype>::iterator::operator--(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->prev;
		return temp;
	}
	//------------------------------------------------------------------------
	//		class:			CDLList::iterator
	//		method:			operator[](int index)
	//		description:	get the element at index l-value
	//		calls:			end()
	//						begin()
	//		called by:		main()
	//		parameters:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	datatype& CDLList<datatype>::operator[](int index)
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
	//------------------------------------------------------------------------
	//		class:			CDLList::iterator
	//		method:			operator[](int index)
	//		description:	get the element at index r-value
	//		calls:			end()
	//						begin()
	//		called by:		main()
	//		parameters:		n/a
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------

	template<typename datatype>
	const datatype& CDLList<datatype>::operator[](int index)const
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