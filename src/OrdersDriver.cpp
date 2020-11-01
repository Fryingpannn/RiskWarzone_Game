/////////////////////////////////////////////
// Filename:        OrdersDriver.cpp
//
// Description:     Driver for Implementation of Part 4 - Orders List
//
// Author:          Matthew Pan - 40135588
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#include "OrdersDriver.h"
#include "Orders.h"
#include <queue> ////////
#include <vector> //////////

//This driver file tests the functionalities from the Orders.h/Orders.cpp files.
void main() {
	std::cout << "-------- OrderList driver program: Let's create some orders! -------\n" << std::endl;

	//creating new OrderList
	OrderList oList;




	//testing priority queue -------------------------------------------
	Deploy* test1 = new Deploy();
	Advance* test2 = new Advance();
	Airlift* test3 = new Airlift();
	Bomb* test4 = new Bomb();
	Blockade* test5 = new Blockade();

	//test list
	OrderList testL;
	testL.addToList(test2);
	testL.addToList(test4);
	testL.addToList(test5);
	testL.addToList(test3);
	testL.addToList(test1);

	Order* top = testL.peek();
	std::cout << "TOP: " << *top << std::endl;
	delete top;

	//std::priority_queue<Order*, std::vector<Order*>, CompareOrder> list;

	//list.push(test4);
	//list.push(test2);
	////list.push(test5);
	////list.push(test3);
	//list.push(test1);

	//while(!list.empty()) {
	//	std::cout << list.size() << std::endl;
	//	std::cout << *list.top() << std::endl;
	//	list.pop();
	//}

	///Conclusion: works for the top priorities but missing the other elements... also, would have to rewrite all since queue doesn't support iterators




	//adding orders to the list
	oList.addToList(new Deploy());
	oList.addToList(new Advance());
	oList.addToList(new Bomb());
	oList.addToList(new Blockade());
	oList.addToList(new Negotiate());
	oList.addToList(new Airlift());

	//displaying list
	std::cout << std::endl << oList;

	//making a copy of the previous list (copy constructor)
	std::cout << "----- Copying previous list with Copy Constructor: Constructor chain -----" << std::endl;
	OrderList listCopy = oList;
	std::cout << std::endl;

	//moving the orders in the list & displaying list again
	oList.move(0, 2);
	std::cout << oList << std::endl;

	//displaying previously copied list
	std::cout << "Displaying previously copied list, which has not changed." << std::endl;
	std::cout << listCopy << std::endl;

	//removing item 1 from the list & displaying list again
	std::cout << "-> Removing item 1 from the list <-" << std::endl;
	oList.remove(1);
	std::cout << oList << std::endl;

	//Displaying an order without executing it
	std::cout << "Displaying an order before it has been executed:" << std::endl;
	Deploy obj;
	std::cout << obj << std::endl << std::endl;

	//Displaying an order when its been executed
	std::cout << "Displaying an order after it has been executed:" << std::endl;
	obj.execute();
	std::cout << obj << std::endl;

	//making a copy of the list with assignment operator and displaying it
	std::cout << "----- Copying previous list with assignment operator: Constructor chain -----" << std::endl;
	OrderList assignCopy;
	assignCopy = oList;
	std::cout << std::endl << "Copied list:" << std::endl << assignCopy << std::endl;

	std::cout << "----- Destructor call stack below -----" << std::endl;
}