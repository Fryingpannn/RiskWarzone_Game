#include <iostream>
#include <vector>
#include "Orders.h"

//default constructor
OrderList::OrderList() {}

//add order to list
bool OrderList::addToList(Order* order) {
	this->list.push_back(order);
	return true;
}

//remove from list
bool OrderList::remove(int position) {
	//this->list.erase(position);
	return true;
}

