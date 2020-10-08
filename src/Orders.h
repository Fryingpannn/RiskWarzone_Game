#pragma once

#include <iostream>
#include <string>
#include <vector>

class Order;

//list of orders used by each player
class OrderList
{
private:
	//list of orders
	std::vector<Order*> list;
public:
	//constructors
	OrderList();
	OrderList(const OrderList& copy);
	//adds an order to the list
	bool addToList(Order* order);
	//removes an order from the list
	bool remove(int position);
	//moves/swaps an order from an index with another in the list
	bool move(int firstIndex, int secondIndex);
	//assignment operator
	OrderList& operator=(const OrderList& o);
	//insertion stream operator
	friend std::ostream& operator <<(std::ostream& out, const OrderList &orders);
	//destructor
	~OrderList();
};

//order base class, to be stored in order list
class Order
{
private:
	//name of order
	std::string name;
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
};

class Deploy : public Order
{
public: 
	//constructors
	Deploy();
	//order functions
	bool validate() override;
	bool execute() override;
	//assignment & stream insertion operators
	Deploy& operator =(const Deploy& o);
	friend std::ostream& operator<<(std::ostream& out, const Deploy& order);
};