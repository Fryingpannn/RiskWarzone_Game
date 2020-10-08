#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"

//default constructor
OrderList::OrderList() {}

//copy constructor for OrderList /////////////////////this and assignment operator SUS
OrderList::OrderList(const OrderList& copy) {
	for (int i = 0; i < copy.list.size(); ++i) {
		*this->list[i] = *copy.list[i]; ////not sure......
	}
}

//add order to list
bool OrderList::addToList(Order* order) {
	this->list.push_back(order);
	std::cout << "New order added!" << std::endl;
	return true;
}

//remove from list
bool OrderList::remove(int position) {
	auto it = this->list.begin() + position-1;
	this->list.erase(it);
	std::cout << "Order has been removed" << std::endl;
	return true;
}

//move (swap) orders around in the list
bool OrderList::move(int first, int second) {
	auto it1 = this->list.begin() + first;
	auto it2 = this->list.begin() + second;

	Order* temp = *it2;
	*it2 = *it1;
	*it1 = temp;
	std::cout << "Orders have been swapped." << std::endl;
	return true;
}

//assignment operator overload
OrderList& OrderList::operator =(const OrderList& o) {
	for (int i = 0; i < o.list.size(); ++i) {
		*this->list[i] = *o.list[i];
	}
}

//insertion stream operator overload
std::ostream& operator <<(std::ostream& out, const OrderList& o) {
	for (int i = 0; i < o.list.size(); ++i)
		out << "[" << i << "]. " << o.list[i] << std::endl;
}

/* Order class below */

//default constructor
Order::Order() { this->name = "none"; }

//copy constructor
Order::Order(const Order& copy) {
	std::cout << "Created a copy of the order." << std::endl;
	this->name = copy.name;
}

//validates orders during execution
bool Order::validate() {}

//executes an order if valid
bool Order::execute() {
	if (validate()) {
		std::cout << "Order has been executed" << std::endl;
		//implementation of order here
		return true;
	}
	else
		return false;
}

//assignment operator
Order& Order::operator =(const Order& o) {
	this->name = o.name;
}

//insertion stream operator
std::ostream& operator <<(std::ostream& out, Order& o) {
	out << o.getName() << std::endl;
}

//accessor for name
std::string Order::getName() {
	return this->name;
}

//mutator for name
void Order::setName(std::string name) {
	this->name = name;
}

/* Deploy class below */

//default constructor
Deploy::Deploy() {
	setName("Deploy");
};

//validates order
bool Deploy::validate() {
	//validation code depending on implementation
}

//executes deploy if valid
bool Deploy::execute() {
	if (validate()) {
		//implementation of deploy
		return true;
	}
	else
		return false;
}


