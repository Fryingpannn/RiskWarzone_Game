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
//private:
	//name of order
	//const std::string name = "General Order";
public:
	//constructors
	Order();
	Order(const Order& copy);
	//clone function for polymorphic classes used by OrderList's copy constructor
	virtual Order* clone();
	//checks if an order is valid
	virtual bool validate();
	//executes an order if it's valid
	virtual bool execute();

	//accessor
	std::string getName();

	//assignment operator
	Order& operator =(const Order& o);
	//insertion stream operator, also used by all subclasses
	friend std::ostream& operator <<(std::ostream& out, const Order& order);
	//print function called by insertion stream operator to allow polymorphic printing
	virtual std::ostream& doprint(std::ostream& out) const;
};

//Deploy order used to deploy armies onto player territory -------------
class Deploy : public Order
{
public: 
	//constructors
	Deploy();
	Deploy(const Deploy& deploy);
	//clone function for polymorphic classes
	Deploy* clone() override;
	//order functions
	bool validate() override;
	bool execute() override;
	//assignment & stream functions
	Deploy& operator =(const Deploy& o);
	std::ostream& doprint(std::ostream& out) const override;
};

//Advance order used to advance armies into friendly or enemy territory -------------
class Advance : public Order
{
public:
	//constructors
	Advance();
	Advance(const Advance& adv);
	//clone function
	Advance* clone() override;
	//order functions
	bool validate() override;
	bool execute() override;
	//assignment & stream functions
	Advance& operator =(const Advance& adv);
	std::ostream& doprint(std::ostream& out) const override;
};

//Bomb order used to bomb target country making them lose half their army units -------------
class Bomb : public Order
{
public:
	//constructors
	Bomb();
	Bomb(const Bomb& deploy);
	//clone function for polymorphic classes
	Bomb* clone() override;
	//order functions
	bool validate() override;
	bool execute() override;
	//assignment & stream functions
	Bomb& operator =(const Bomb& o);
	std::ostream& doprint(std::ostream& out) const override;
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
	bool execute() override;
	//assignment & stream functions
	Blockade& operator =(const Blockade& o);
	std::ostream& doprint(std::ostream& out) const override;
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
	bool execute() override;
	//assignment & stream functions
	Airlift& operator =(const Airlift& o);
	std::ostream& doprint(std::ostream& out) const override;
};

//Negotiate order used to prevent attacks between current and another player until end of turn -------------
class Negotiate : public Order {
	//default constructors
	Negotiate();
	Negotiate(const Negotiate&);
	//clone function for polymorphic class
	Negotiate* clone() override;
	//order functions
	bool validate() override;
	bool execute() override;
	//assignment and stream functions
	Negotiate& operator =(const Negotiate&);
	std::ostream& doprint(std::ostream& out) const override;
};

