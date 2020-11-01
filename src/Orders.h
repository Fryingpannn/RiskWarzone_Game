/////////////////////////////////////////////
// Filename:        Orders.h
//
// Description:     Header file for Implementation of Part 4 - Orders List
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
	//removes and returns the top priority element from list
	Order* pop();
	//returns a copy of the next top priority element from list
	Order* peek();
	//moves/swaps an order from an index with another in the list
	bool move(int firstIndex, int secondIndex);
	//returns size/emptyness of current list
	int size() { return list.size(); }
	bool empty() { return list.empty(); }
	//assignment operator
	OrderList& operator=(const OrderList& o);
	//insertion stream operator
	friend std::ostream& operator <<(std::ostream& out, const OrderList &orders);
	//destructor
	~OrderList();
};

// operator overloading for the Orders' priority comparisons
//struct CompareOrder {
//	bool operator()(Order* const& o1, Order* const& o2);
//};

//order abstract base class. used to store the different subclasses in the OrderList vector
class Order
{
protected:
	//name of order
	std::string name{ "None" };
	//true if order has been executed, false otherwise
	bool executed{ false };
public:
	//priority of order
	const int priority = 0;
	//constructors
	Order();
	//constructor to set name data member, used by subclass constructors
	Order(const std::string& name, const int& priority);
	//clone function for polymorphic classes used by OrderList's copy constructor
	virtual Order* clone() = 0;
	//checks if an order is valid
	virtual bool validate() = 0;
	//executes an order if it's valid
	virtual void execute() = 0;
	//setter/getter to set/get the execution status of the order
	void setExecuted(const bool& status);
	bool getExecuted();
	virtual int getCount();
	//setter/getter for order name
	void setName(std::string name);
	std::string getName();
	//assignment operator
	Order& operator =(const Order& o);
	//insertion stream operator, also used by all subclasses
	friend std::ostream& operator <<(std::ostream& out, Order& order);
	//print function called by insertion stream operator to allow polymorphic printing
	virtual std::ostream& doprint(std::ostream& out) = 0;
	virtual ~Order();
};

//Deploy order used to deploy armies onto player territory -------------
class Deploy : public Order
{
private:
	
public:
	//time counter for priority comparison
	static int incrCount;
	const int counter;
	int getCount() { return counter; }
	//constructors
	Deploy();
	Deploy(const Deploy& deploy);
	//clone function for polymorphic classes
	Deploy* clone() override;
	//order functions
	bool validate() override;
	void execute() override;
	//get obj priority counter
	//assignment & stream functions
	Deploy& operator =(const Deploy& o);
	std::ostream& doprint(std::ostream& out) override;
	~Deploy();
};

//Advance order used to advance armies into friendly or enemy territory -------------
class Advance : public Order
{
public:
	//time counter for priority comparison
	static int incrCount;
	const int counter;
	int getCount() { return counter; }
	//constructors
	Advance();
	Advance(const Advance& adv);
	//clone function
	Advance* clone() override;
	//order functions
	bool validate() override;
	void execute() override;
	//assignment & stream functions
	Advance& operator =(const Advance& adv);
	std::ostream& doprint(std::ostream& out) override;
	~Advance();
};

//Bomb order used to bomb target country making them lose half their army units -------------
class Bomb : public Order
{
public:
	//time counter for priority comparison
	static int incrCount;
	const int counter;
	int getCount() { return counter; }
	//constructors
	Bomb();
	Bomb(const Bomb& deploy);
	//clone function for polymorphic classes
	Bomb* clone() override;
	//order functions
	bool validate() override;
	void execute() override;
	//assignment & stream functions
	Bomb& operator =(const Bomb& o);
	std::ostream& doprint(std::ostream& out) override;
	~Bomb();
};

//Blockade order used to triple a territory's army units and make it become neutral -------------
class Blockade : public Order
{
public:
	//constructors
	Blockade();
	Blockade(const Blockade& deploy);
	//clone function for polymorphic classes
	Blockade* clone() override;
	//order functions
	bool validate() override;
	void execute() override;
	//assignment & stream functions
	Blockade& operator =(const Blockade& o);
	std::ostream& doprint(std::ostream& out) override;
	~Blockade();
};

//Airlift order used to move any number of units from one territory to any other -------------
class Airlift : public Order
{
public:
	//constructors
	Airlift();
	Airlift(const Airlift& deploy);
	//clone function for polymorphic classes
	Airlift* clone() override;
	//order functions
	bool validate() override;
	void execute() override;
	//assignment & stream functions
	Airlift& operator =(const Airlift& o);
	std::ostream& doprint(std::ostream& out) override;
	~Airlift();
};

//Negotiate order used to prevent attacks between current and another player until end of turn -------------
class Negotiate : public Order {
public:
	//default constructors
	Negotiate();
	Negotiate(const Negotiate&);
	//clone function for polymorphic class
	Negotiate* clone() override;
	//order functions
	bool validate() override;
	void execute() override;
	//assignment and stream functions
	Negotiate& operator =(const Negotiate&);
	std::ostream& doprint(std::ostream& out) override;
	~Negotiate();
};

