//-----------------------------------------------------------------------------
//	File:	Queue.h
//
//	Class:	Queue
//-----------------------------------------------------------------------------
#ifndef CQUEUE_H
#define CQUEUE_H

#include "List.h"
//-----------------------------------------------------------------------------
//	Class: Queue
//	Title: Queue Class
//	
//	Description: This file contains the class definition for Queue Class
//				 Queue is like a list but follows FIFO(first in first out)
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
//	class list:
//		Properties:
//			 unsigned m_size -- number of elements in the list
//
//		public:
//			Queue() { CDLList<datatype>(); } -- default constructor
//			Queue(size_t n_elements, datatype datum) -- with size and data
//			Queue(const CDLList& myList) -- copy constructor
//			Queue(iterator begin, iterator end) -- constructor with iterators
//			virtual ~Queue() -- destructor
//			bool empty() -- check if queue is empty
//			void release() -- empties out queue
//			unsigned getSize() const -- get the size of the queue
//			iterator begin() const -- points to head of the queue
//			iterator end() const -- points to tail of the queue
//			void push(datatype datum)  -- push data from the back
//			datatype& pop() -- pop data from the front
//-----------------------------------------------------------------------------
using namespace HJ_ADT;

namespace HJ_QUEUE
{
	template<typename datatype>
	class Queue : virtual protected CDLList<datatype>
	{
	public:
		Queue() { CDLList<datatype>(); }
		Queue(size_t n_elements, datatype datum) { CDLList<datatype>
			(n_elements, datum); };
		Queue(const CDLList& myList) { CDLList<datatype>(myList); };
		Queue(iterator begin, iterator end) { 
			CDLList<datatype>(begin, end); };
		virtual ~Queue() { release(); }
		bool empty() { return CDLList<datatype>::empty(); }
		void release() { while (!empty()) { pop(); } }
		unsigned getSize() const { return m_size; }
		iterator begin() const { return head; }
		iterator end() const { return tail; }
		void push(datatype datum) { 
			CDLList<datatype>::push_back(datum); m_size++; }
		datatype& pop() { m_size--; return CDLList<datatype>::pop_front(); }
	private:
		unsigned m_size;	
	};
	//------------------------------------------------------------------------
	//		method:			operator<<(ostream& sout, const 
	//							Queue<datatype>& myList)
	//		description:	returns contents of the queue to the ostream
	//		calls:			end()
	//						begin()
	//		called by:		main()
	//						
	//		parameters:		ostream& sout -- stream to write to 
	//						const Queue<datatype>& myList -- List of data
	//		returns:		ostream&
	//		History Log:
	//						5/21/2017 HJ completed version 1.0
	// -----------------------------------------------------------------------
	template<typename datatype>
	ostream& operator<<(ostream& sout, const Queue<datatype>& myList) {
		CDLList<datatype>::iterator p = myList.begin();
		if (p == nullptr)
			sout << "()";
		else {
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
		}
		return sout;
	}
	
}
#endif