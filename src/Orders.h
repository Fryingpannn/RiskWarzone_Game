#pragma once

#include <iostream>
#include <string>

//list of orders used by each player
class OrderList
{
private:
	//list of orders
	std::vector<Order*> list;
public:
	//constructors
	OrderList();
	OrderList(int size);
	//adds an order to the list
	addToList(Order* order);
	//removes an order from the list
	remove(Order* order);
	//moves an order from an index to another in the list
	move(int position, int newPosition);
	//copy constructor
	OrderList(OrderList* copy);
	//assignment operator
	virtual OrderList& operator=(const& OrderList o);
	//insertion stream operator
	virtual friend std::ostream& operator <<(ostream& out, const OrderList &orders);
};

//order base class, to be stored in order list
class Order
{
private:
	//name of order
	const std::string* name;
public:
	//constructors
	Order();
	Order(Order& copy);
	//checks if an order is valid
	virtual boolean validate();
	//executes an order if it's valid
	virtual execute();
	//accessor & mutator
	string getName();
	//assignment operator
	Order& operator =(const& Order o);
	//insertion stream operator
	friend std::ostream& operator <<(ostream& out, const Order& order);
	//destructor
	~Order();
};

class Deploy : public Order
{
public: 
	//constructors
	Deploy() : Order();
	Deploy(std::string name) : Order(name);
	//order functions
	override boolean validate();
	override execute();
	//assignment & stream insertion operators
	override Deploy& operator =(const Deploy& o);
	override friend std::ostream& operator<<(ostream& out, const Deploy& order);
};