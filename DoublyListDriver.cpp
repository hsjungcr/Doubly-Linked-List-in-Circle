//----------------------------------------------------------------------------
//	File:		DateTimeDriver.cpp
//
//	Function:	main()
//----------------------------------------------------------------------------
#include <iomanip>
#include <string>
#include "Queue.h"
using namespace HJ_QUEUE;
//----------------------------------------------------------------------------
//
//	Function:		main()
//	Title:			Doubly Circular Linked List Driver
//	Description:	This file contains function main()
//					which tests the Doubly Circular Linked List class
//					and Queue class
//	Programmer:		Han Jung 
//	Date:			5/21/2017
//	Version:		1.0
//	Environment:	Hardware: Dell Inspirion
//					Software: MS Windows 10
//					Compiles under Microsoft Visual C++.Net 2017
//	Input:			Doubly Circular LinkedList class and Queue class
//	Output:			Linked list and queue list
//	Calls:			CDLList() and its member functions
//					Queue() and its member functions
//	Called By:		n/a
//	Parameters:		None
//	Returns:		EXIT_SUCCESS upon successful termination
//	History Log:
//			
//			5/21/17 HJ Completed 1.0
//----------------------------------------------------------------------------
int main()
{
	cout << "CS133 Circular Doubly Linked List Project\nby Han S. Jung";
	cout << "\n\n";
	short testSize = 4;
	short testListSize = 10;
	short i = 0; //counter
	short j = 0; //counter
	const short increment = 3;
	int testDatum = 20;
	int temp = 0; //temporary datatype storing variable
	try
	{
		//create arrays of doubly lists
		CDLList<int>** testList = nullptr;
		testList = new CDLList<int>*[testSize];
		for (i = 0; i < testSize; i++)
		{
			//testList[i] = new CDLList<int>; Both works
			testList[i] = new CDLList<int>();
		}
		//push back testDatum
		cout << "Push back test"<<endl;
		for (i = 0; i < testSize; i++)
		{
			for (j = 0; j < testListSize; j++)
			{
				testList[i]->push_back(testDatum);
				//for non-linear data for better test result
				testDatum += increment;
			}
		}
		for (i = 0; i < testSize; i++)
		{
			cout << "Test list [" << i << "]" << endl;
			cout << *testList[i];
			cout << endl;
		}
		cout << endl;

		//push front test Datum
		cout << "Push front test" <<endl ;
		for (i = 0; i < testSize; i++)
		{
			for (j = 0; j < testListSize; j++)
			{
				testList[i]->push_front(testDatum);
				testDatum += increment;
			}
		}
		//iterate through updated list with previous element
		for (i = 0; i < testSize; i++)
		{
			cout << "Test list [" << i << "]" << endl;
			cout << *testList[i];
			cout << endl;
		}
		cout << endl;
		//pop_front print head then pop_back then print tail
		cout << "Pop test" << endl;
		for (i = 0; i < testSize; i++)
		{
			testListSize = testList[i]->getSize();
			cout << "testList[" << i << "]" << endl;
			cout << "size:" << testListSize << " front: ";
			cout << testList[i]->front();
			cout << " back: " << testList[i]->back() << endl;
			while (testList[i]->front() != testList[i]->back()) {
				cout << "After Pop Front: ";
				testList[i]->pop_front();
				testListSize = testList[i]->getSize();
				cout << "size:" << testListSize << " front: ";
				cout << testList[i]->front();
				cout << " back: " << testList[i]->back() << endl;
				cout << *testList[i];
				//Break out of the loop if there are nothing else to pop;
				if (testList[i]->front() == testList[i]->back())
					break;
				cout << "After Pop Back : ";
				testList[i]->pop_back();
				testListSize = testList[i]->getSize();
				cout << "size:" << testListSize << " front: ";
				cout << testList[i]->front();
				cout << " back: " << testList[i]->back() << endl;
				cout << *testList[i];
			}
			cout << endl;
		}
		cout << "Queue test with string\n";
		Queue<string>* testQueue = nullptr;
		testQueue = new Queue<string>();
		cout << "pushing string \"Saffron\", \"Anise\", \"Cinnamon\",";
		cout <<"\"Thyme\"\n";
		testQueue->push("Saffron");
		cout << *testQueue;
		testQueue->push("Anise");
		cout << *testQueue;
		testQueue->push("Cinnamon");
		cout << *testQueue;
		testQueue->push("Thyme");
		cout << *testQueue << endl;
		cout << "Popping out list"<<endl;
		testQueue->pop();
		cout << *testQueue;
		testQueue->pop();
		cout << *testQueue;
		testQueue->pop();
		cout << *testQueue;
		testQueue->pop();
		cout << *testQueue;
		
		for (i = 0; i < testSize; i++)
		{
			testList[i]->release();
		}
		delete testList;
		testQueue ->release();
	}
	catch (bad_cast& e) {
		cout << e.what() << endl;
	}
	catch (bad_array_new_length& e) {
		cout << e.what() << endl;
	}
	catch (bad_alloc& e) {
		cout << e.what() << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}


	cin.ignore();
	return EXIT_SUCCESS;
}