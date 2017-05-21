#include "Queue.h"
#define CATCH_CONFIG_MAIN
#include "Catch.hpp"
using namespace HJ_QUEUE;


int main()
{
	cout << "CS133 Circular Doubly Linked List Project\nby Han S. Jung";
	cout << "\n\n";

	CDLList<int> *testList1 = nullptr;
	testList1 = new CDLList<int>(2, 'h');
	
	testList1->push_back('x');
	testList1->push_back('2');
	CDLList<int>::iterator it;
	


	cin.ignore();
	return EXIT_SUCCESS;
}
TEST_CASE("Main") {
	main();
}