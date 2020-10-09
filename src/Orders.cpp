#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"

/* OrderList */

//default constructor
OrderList::OrderList() {}

//copy constructor for OrderList /////////////////////this and assignment operator SUS
OrderList::OrderList(const OrderList& copy) {
	this->list.resize(copy.list.size());//resizing new list's vector to same size as copy
	for (int i = 0; i < copy.list.size(); ++i) {
		this->list[i] = copy.list[i]->clone();       //new Order(*copy.list[i]); ////ree
	}
	std::cout << "OrderList copy constructor done." << std::endl;
}

//add order to list
bool OrderList::addToList(Order* order) {
	this->list.push_back(order);
	std::cout << "-> New order added!" << std::endl;
	return true;
}

//remove from list
bool OrderList::remove(int position) {
	auto it = this->list.begin() + position;
	(**it).execute();	//executes order before removing (it is a pointer pointing to Order*)
	delete *it;
	this->list.erase(it);
	std::cout << "-> Order " << position << " has been removed." << std::endl;
	return true;
}

//move (swap) orders around in the list
bool OrderList::move(int first, int second) {
	auto it1 = this->list.begin() + first;
	auto it2 = this->list.begin() + second;

	Order* temp = *it2;
	*it2 = *it1;
	*it1 = temp;
	std::cout << "-> Orders have been swapped." << std::endl;
	return true;
}

//assignment operator overload
OrderList& OrderList::operator =(const OrderList& o) {
	for (int i = 0; i < o.list.size(); ++i) {
		this->list[i] = new Order(*o.list[i]);
	}
	std::cout << "OrderList assignment operator done." << std::endl;

	return *this;
}

//insertion stream operator overload
std::ostream& operator <<(std::ostream& out, const OrderList& o) {
	if (!o.list.empty()) {
		for (int i = 0; i < o.list.size(); ++i)
			out << "[" << i << "]. " << *o.list[i] << std::endl;
	}
	else
		out << "Order list is empty." << std::endl;
	
	return out;
}

//destructor for OrderList
OrderList::~OrderList() {
	for (int i = 1; i < this->list.size(); ++i) {
		delete this->list[i];
	}
	this->list.clear();
}

/* Order class below */
  
//default constructor
Order::Order() { /*this->name = "none";*/ }

//copy constructor
Order::Order(const Order& copy) {
	std::cout << "Created a copy of General Order" << std::endl;
}

//clone function for class polymorphism (for vector)
Order* Order::clone() {
	return new Order(*this);
}

//validates orders during execution
bool Order::validate() {
	std::cout << "Order validated." << std::endl;
	return true;
}

//executes an order if valid
bool Order::execute() {
	if (validate()) {
		std::cout << "Order has been executed." << std::endl;
		//implementation of order here
		return true;
	}
	else
		return false;
}

//assignment operator
Order& Order::operator =(const Order& o) {
	std::cout << "Order assignment operator done." << std::endl;
	return *this;
}

//insertion stream operator, calls a separate function to allow polymorphic printing
std::ostream& operator <<(std::ostream& out, const Order& o) {
	//out << o.getName() << std::endl;
	return o.doprint(out);
}

//function called by insertion stream operator to print order
std::ostream& Order::doprint(std::ostream& out) const {
	return out << "Order: General";
}

//accessor for name
//std::string Order::getName() {
//	return this->name;
//}

//mutator for name
//void Order::setName(std::string name) {
//	this->name = name;
//}


/* Deploy class below */


//default constructor
Deploy::Deploy() {
	//setName("Deploy");
};

//deploy copy constructor
Deploy::Deploy(const Deploy& deploy) {
	std::cout << "Created a copy of Deploy." << std::endl;
}

//clone function for Deploy
Deploy* Deploy::clone() {
	return new Deploy(*this);
}

//validates order
bool Deploy::validate() {
	std::cout << "Validating..." << std::endl;
	/*validation here, can user deploy units?*/
	if (true) {
		return true;
	}
	else
		return false;
}

//executes deploy if valid
bool Deploy::execute() {
	if (validate()) {
		//implementation of deploy
		std::cout << "Units have been deployed successfully." << std::endl;
		return true;
	}
	else {
		std::cout << "Cannot deploy units. Deploy order not executed." << std::endl;
		return false;
	}
}

//assignment operator
Deploy& Deploy::operator =(const Deploy& o) {
	std::cout << "Deploy Assignment Operator done." << std::endl;
	
	return *this;
}

//function called by insertion stream operator to print order
std::ostream& Deploy::doprint(std::ostream& out) const {
	return out << "Order: Deploy";
}


