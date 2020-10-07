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
	bool addToList(Order* order);
	//removes an order from the list
	bool remove(Order* order);
	//moves an order from an index to another in the list
	bool move(int position, int newPosition);
	//copy constructor
	OrderList(OrderList* copy);
	//assignment operator
	virtual OrderList& operator=(const OrderList& o);
	//insertion stream operator
	virtual friend std::ostream& operator <<(std::ostream& out, const OrderList &orders);
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
	virtual bool validate();
	//executes an order if it's valid
	virtual bool execute();
	//accessor & mutator
	std::string getName();
	//assignment operator
	Order& operator =(const Order& o);
	//insertion stream operator
	friend std::ostream& operator <<(std::ostream& out, const Order& order);
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
	override bool validate();
	override execute();
	//assignment & stream insertion operators
	override Deploy& operator =(const Deploy& o);
	override friend std::ostream& operator<<(ostream& out, const Deploy& order);
};