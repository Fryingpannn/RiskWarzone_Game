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
#include <unordered_set>
#include <vector>
#include <memory>

class Map;
class Hand;
class Deck;
class Player;
struct Territory;

class Order;

// list of orders used by each player
class OrderList {
 private:
  // list of orders
//  std::vector<Order*> list;
	std::vector<std::shared_ptr<Order>> list;
 public:
  // constructors
  OrderList();
  OrderList(const OrderList& copy);
  // adds an order to the list
//  bool addToList(Order* order);
  bool addToList(std::shared_ptr<Order> order);
  // removes an order from the list
  // returns: the armyNb of the order to refill reinforcement pool of player
  int remove(int position);
  // removes and returns the top priority element from list
	std::shared_ptr<Order> pop();
  // returns a copy of the next top priority element from list
	std::shared_ptr<Order> peek();
  // moves/swaps an order from an index with another in the list
  bool move(int firstIndex, int secondIndex);
  // returns size/emptyness of current list
  int size() { return list.size(); }
  bool empty() { return list.empty(); }
  // assignment operator
  OrderList& operator=(const OrderList& o);
  // insertion stream operator
  friend std::ostream& operator<<(std::ostream& out, const OrderList& orders);
  // destructor
  ~OrderList();
};

//order abstract base class. used to store the different subclasses in the OrderList vector
class Order
{
protected:
	//name of order
	std::string name{ "None" };
	//true if order is to be executed by game engine, false otherwise
	bool executed{ false };
	int armyNb{}; //the number of armies to change within order
	std::string playerID{ "uninitialized" }; //current player's ID
	Territory* src = nullptr;
	Territory* target = nullptr;
	std::vector<Territory*> adj{}; //adjacent territories of src
	Map* map = nullptr; //used to get the adjacent territories by Advance
	Player* enemy = nullptr; //used by negotiation execution to update diplomacy status
	Player* current = nullptr; //player who created this order
	Deck* deck = nullptr; //draw card from deck if new territory won from advance
public:
	//priority of order
	const int priority = 0;
	//constructors
	Order();
	Order(const Order& copy, const int& priority);
	//constructor to set name data member, used by subclass constructors
	Order(const std::string& name, const int& priority);
	//clone function for polymorphic classes used by OrderList's copy constructor
//	virtual Order* clone() = 0;
	virtual std::shared_ptr<Order> clone() const = 0;
	//executes an order if it's valid
	virtual bool execute() = 0;
	virtual bool validate() = 0;
	//setter/getter to set/get the execution status of the order
	void setExecuted(const bool& status);
	bool getExecuted();
	//setter/getter for order name
	void setName(const std::string& name);
	std::string getName();
	Territory* getTarget();
	int getArmyNb();
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
public:
	//constructors: default, copy, and to deploy armies
	Deploy();
	Deploy(const Deploy&);
	//playerID is the player who issued this order
	Deploy(const std::string& playerID, const int& armyNb, Territory* target, Player* const current);
	//clone function for polymorphic classes
//	Deploy* clone() override;
		virtual std::shared_ptr<Order> clone() const override;
	//order functions
	bool validate() override;
	bool execute() override;
	//get obj priority counter
	//assignment & stream functions
	Deploy& operator =(const Deploy& o);
	std::ostream& doprint(std::ostream& out) override;
	~Deploy();
};

// Advance order used to advance armies into friendly or enemy territory
class Advance : public Order {
 public:
  // constructors
  Advance();
  Advance(const Advance&);
  // if executed and conquered enemy territory, need to add that to the player's
  // list
  Advance(const std::string& playerID, const int& armyNb, Territory* src,
          Territory* target, Map* map, Player* const current, Deck* const deck);
  // clone function
//  Advance* clone() override;
	virtual std::shared_ptr<Order> clone() const override;
  // order functions
  bool validate();
  bool execute() override;
  // assignment & stream functions
  Advance& operator=(const Advance& adv);
  std::ostream& doprint(std::ostream& out) override;
  virtual ~Advance();
};

// Bomb order used to bomb target country making them lose half their army units
//- can only be created by playing bomb card
class Bomb : public Order {
 public:
  // constructors
  Bomb();
  Bomb(const Bomb&);
  Bomb(const std::string& playerID, Territory* target, Player* const current);
  // clone function for polymorphic classes
//  Bomb* clone() override;
		virtual std::shared_ptr<Order> clone() const override;
  // order functions
  bool validate() override;
  bool execute() override;
  // assignment & stream functions
  Bomb& operator=(const Bomb& o);
  std::ostream& doprint(std::ostream& out) override;
  ~Bomb();
};

// Blockade order used to triple a territory's army units and make it become neutral 
class Blockade : public Order {
 public:
  // constructors
  Blockade();
  Blockade(const Blockade&);
  // if executed, need to remove neutral territory from player list
  Blockade(const std::string& playerID, Territory* src);
  // clone function for polymorphic classes
//  Blockade* clone() override;
		virtual std::shared_ptr<Order> clone() const override;
  // order functions
  bool validate() override;
  bool execute() override;
  // assignment & stream functions
  Blockade& operator=(const Blockade& o);
  std::ostream& doprint(std::ostream& out) override;
  ~Blockade();
};

// Airlift order used to move any number of units from one territory to any other
class Airlift : public Order {
 public:
  // constructors
  Airlift();
  Airlift(const Airlift&);
  Airlift(const std::string& playerID, const int& armyNb, Territory* src,
          Territory* target, Player* const current, Deck* const deck);
  // clone function for polymorphic classes
//  Airlift* clone() override;
		virtual std::shared_ptr<Order> clone() const override;
  // order functions
  bool validate() override;
  bool execute() override;
  // assignment & stream functions
  Airlift& operator=(const Airlift& o);
  std::ostream& doprint(std::ostream& out) override;
  ~Airlift();
};

// Negotiate order used to prevent attacks between current and another player
// until end of turn ------------- Enables 'diplomatic status' between two
// players.
class Negotiate : public Order {
 public:
  // default constructors
  Negotiate();
  Negotiate(const Negotiate&);
  // the set contains players with whom playerID cannot attack this turn
  Negotiate(Player* const current, Player* const enemy);
  // clone function for polymorphic class
//  Negotiate* clone() override;
		virtual std::shared_ptr<Order> clone() const override;
  // order functions
  bool validate() override;
  bool execute() override;
  // assignment and stream functions
  Negotiate& operator=(const Negotiate&);
  std::ostream& doprint(std::ostream& out) override;
  ~Negotiate();
};

// Reinforcement order comes from playing the reiforcement card
//just adds 5 army unit to the player's reinforcement pool
class Reinforcement : public Order {
public:
	// constructors
	Reinforcement();
	Reinforcement(Player* const current);
	Reinforcement(const Reinforcement&);
//	Reinforcement* clone() override;
		virtual std::shared_ptr<Order> clone() const override;
	// order functions
	bool validate() override;
	bool execute() override;
	// assignment and stream functions
	Reinforcement& operator=(const Reinforcement&);
	std::ostream& doprint(std::ostream& out) override;
	~Reinforcement();
};