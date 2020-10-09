#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"

/*---------------------------------- OrderList class ----------------------------------*/

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

/*---------------------------------- Order class ----------------------------------*/
  
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


/*---------------------------------- Deploy class ----------------------------------*/


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
	std::cout << "Validating order..." << std::endl;
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
		std::cout << "[Deploy] Armies have been deployed successfully." << std::endl;
		return true;
	}
	else {
		std::cout << "[Deploy] Cannot deploy armies. Deploy order not executed." << std::endl;
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
	return out << "Deploy armies";
}


/*----------------------------------- Advance class ----------------------------------*/

//default constructor
Advance::Advance() {}

//copy constructor
Advance::Advance(const Advance& adv) {
	std::cout << "Created a copy of Advance." << std::endl;
}

//clone function for Advance
Advance* Advance::clone() {
	return new Advance(*this);
}

//validates the Advance order
bool Advance::validate() {
	std::cout << "Validating order..." << std::endl;
	/*validation here, can user advance units to this territory? attack/move*/
	if (true) {
		return true;
	}
	else
		return false;
}

//executes the Advance order
bool Advance::execute() {
	if (validate()) {
		if (true/*if territory belong to current player*/) {
			std::cout << "Armies have been moved." << std::endl;
			return true;
		}
		else {
			std::cout << "[Advance] Armies are now attacking enemy territory." << std::endl;
			return true;
		}
	}
	else {
		std::cout << "[Advance] Armies cannot be moved. Advance order not executed." << std::endl;
		return false;
	}
}

//assignment operator function
Advance& Advance::operator =(const Advance& adv) {
	std::cout << "Advance assignment operator done." << std::endl;
	return *this;
}

//stream function to print Advance
std::ostream& Advance::doprint(std::ostream& out) const {
	return out << "Advance armies" << std::endl;
}


/*------------------------------------ Bomb class ------------------------------------*/


//default constructor
Bomb::Bomb() {};

//copy constructor
Bomb::Bomb(const Bomb& deploy) {
	std::cout << "Created a copy of Bomb." << std::endl;
}

//clone function
Bomb* Bomb::clone() {
	return new Bomb(*this);
}

//validates order
bool Bomb::validate() {
	std::cout << "Validating order..." << std::endl;
	/*validation here, can user use bomb card?*/
	if (true) {
		return true;
	}
	else
		return false;
}

//executes Bomb order if valid
bool Bomb::execute() {
	if (validate()) {
		//implementation of bomb
		std::cout << "[Bomb] Target country bombed successfully, they have lost half their army units." << std::endl;
		return true;
	}
	else {
		std::cout << "[Bomb] Cannot bomb target country. Bomb order not executed." << std::endl;
		return false;
	}
}

//assignment operator
Bomb& Bomb::operator =(const Bomb& o) {
	std::cout << "Bomb Assignment Operator done." << std::endl;

	return *this;
}

//function called by insertion stream operator to print order
std::ostream& Bomb::doprint(std::ostream& out) const {
	return out << "Bomb target country";
}


/*------------------------------------ Blockade class ------------------------------------*/


//default constructor
Blockade::Blockade() {};

//copy constructor
Blockade::Blockade(const Blockade& deploy) {
	std::cout << "Created a copy of Blockade." << std::endl;
}

//clone function
Blockade* Blockade::clone() {
	return new Blockade(*this);
}

//validates order
bool Blockade::validate() {
	std::cout << "Validating order..." << std::endl;
	/*validation here, can user use blockade card?*/
	if (true) {
		return true;
	}
	else
		return false;
}

//executes Blockade order if valid
bool Blockade::execute() {
	if (validate()) {
		//implementation of Blockade
		std::cout << "[Blockade] Blockade Successful. Target territory's army units count has tripled and became neutral." << std::endl;
		return true;
	}
	else {
		std::cout << "[Blockade] Cannot blockade target territory. Blockade order not executed." << std::endl;
		return false;
	}
}

//assignment operator
Blockade& Blockade::operator =(const Blockade& o) {
	std::cout << "Blockade Assignment Operator done." << std::endl;

	return *this;
}

//function called by insertion stream operator to print order
std::ostream& Blockade::doprint(std::ostream& out) const {
	return out << "Blockade target territory";
} 


/*------------------------------------ Airlift class ------------------------------------*/


//default constructor
Airlift::Airlift() {};

//copy constructor
Airlift::Airlift(const Airlift& deploy) {
	std::cout << "Created a copy of Airlift." << std::endl;
}

//clone function
Airlift* Airlift::clone() {
	return new Airlift(*this);
}

//validates order
bool Airlift::validate() {
	std::cout << "Validating order..." << std::endl;
	/*validation here, can user use Airlift card?*/
	if (true) {
		return true;
	}
	else
		return false;
}

//executes Airlift order if valid
bool Airlift::execute() {
	if (validate()) {
		//implementation of Airlift
		std::cout << "[Airlift] Airlift successful. Friendly army units have been moved to new territory." << std::endl;
		return true;
	}
	else {
		std::cout << "[Airlift] Cannot airlift army. Airlift order not executed." << std::endl;
		return false;
	}
}

//assignment operator
Airlift& Airlift::operator =(const Airlift& o) {
	std::cout << "Airlift Assignment Operator done." << std::endl;

	return *this;
}

//function called by insertion stream operator to print order
std::ostream& Airlift::doprint(std::ostream& out) const {
	return out << "Airlift target country";
}


/*------------------------------------ Negotiate class ------------------------------------*/


//default constructor
Negotiate::Negotiate() {}

//copy constructor
Negotiate::Negotiate(const Negotiate& n) {
	std::cout << "Created a copy of Negotiate.";
}

//clone function
Negotiate* Negotiate::clone() {
	return new Negotiate(*this);
}

//validates order
bool Negotiate::validate() {
	std::cout << "Validating order...";
	//validation here, can user use Negotiate card?
	if (true) {
		return true;
	}
	else {
		return false;
	}
}

//executes Negotiate order if valid
bool Negotiate::execute() {
	if (validate()) {
		std::cout << "[Negotiate] Negotiation successful. No attacks will be made between two players until end of turn." << std::endl;
		return true;
	}
	else {
		std::cout << "[Negotiate] Negotiation failed. Negotiation order not executed." << std::endl;
		return false;
	}
}

//assignment operator function
Negotiate& Negotiate::operator =(const Negotiate& n) {
	std::cout << "Negotiation assignment operator done." << std::endl;
	return *this;
}

//function called by insertion stream operator to print order
std::ostream& Negotiate::doprint(std::ostream& out) const {
	return out << "Negotiate with target player" << std::endl;
}

