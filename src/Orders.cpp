/////////////////////////////////////////////
// Filename:        Orders.cpp
//
// Description:     Implementation of Part 4 - Orders List
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

#include "Orders.h"

/*---------------------------------- OrderList class
 * ----------------------------------*/

/*---------------------------------- OrderList class
 * ----------------------------------*/

// default constructor
OrderList::OrderList() { this->list = std::vector<Order*>{}; }

// copy constructor for OrderList
OrderList::OrderList(const OrderList& copy) {
  this->list.resize(
      copy.list.size());  // resizing new list's vector to same size as copy
  for (int i = 0; i < copy.list.size(); ++i) {
    this->list[i] = copy.list[i]->clone();
  }
  std::cout << "OrderList copy constructor done." << std::endl;
}

// add order to list
bool OrderList::addToList(Order* order) {
  this->list.push_back(order);
  std::cout << "-> New order added!" << std::endl;
  return true;
}

// remove from list
bool OrderList::remove(int position) {
  auto it = this->list.begin() + position;
  delete *it;
  this->list.erase(it);
  std::cout << "-> Order " << position << " has been removed." << std::endl;
  return true;
}

// returns: nullptr if list is empty, otherwise a copy of the pointer to next priority element
Order* OrderList::peek() {
    //if list is empty, return null
    if (list.empty())
        return nullptr;

    //return 1st Deploy if available
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->priority == 1)
            return (*it)->clone();
    }
    //return 1st Airlift if available
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->priority == 2) 
            return (*it)->clone();
        }
        //return 1st Blockade if available
        for (auto it = list.begin(); it != list.end(); ++it) {
            if ((*it)->priority == 3)
                return (*it)->clone();
        }
        //return in FIFO order if no priority orders available
        return (*list.begin())->clone();
}

// pops top priority element from the list; Deploy -> Airlift -> Blockade -> Others
//
// returns: nullptr if list is empty (be careful when dereferencing!),
//          otherwise returns a pointer which needs to be explicitly deleted
Order* OrderList::pop() {
    //if list is empty, return null
    if (list.empty())
        return nullptr;

    //return Deploy if available
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->priority == 1) {
            Order* popped = *it;
            list.erase(it);
            return popped;
        }
    }
    //return Airlift if available
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->priority == 2) {
            Order* popped = *it;
            list.erase(it);
            return popped;
        }
    }
    //return Blockade if available
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->priority == 3) {
            Order* popped = *it;
            list.erase(it);
            return popped;
        }
    }
    //return in FIFO order if no priority orders available
    Order* popped = *list.begin();
    list.erase(list.begin());
    return popped;
}

// implements operator overloading for the Order's priority comparison
//bool CompareOrder::operator()(Order* const& o1, Order* const& o2){
//      // return "true" if "o1" is ordered before "o2"
//    if (o1->priority < o2->priority)
//        return true;
//    else if (o1->getCount() > o2->getCount())
//        return true;
//    else
//        return false;
//}

// move (swap) orders around in the list
bool OrderList::move(int first, int second) {
  auto it1 = this->list.begin() + first;
  auto it2 = this->list.begin() + second;

  Order* temp = *it2;
  *it2 = *it1;
  *it1 = temp;
  std::cout << "-> Swapped orders " << first << " and " << second << " <-"
            << std::endl;
  return true;
}

// assignment operator overload
OrderList& OrderList::operator=(const OrderList& o) {
  this->list.resize(o.list.size());
  for (int i = 0; i < o.list.size(); ++i) {
    this->list[i] = o.list[i]->clone();
  }
  std::cout << "OrderList assignment operator done." << std::endl;

  return *this;
}

// insertion stream operator overload
std::ostream& operator<<(std::ostream& out, const OrderList& o) {
  if (!o.list.empty()) {
    out << "----- Your current orders -----" << std::endl;
    for (int i = 0; i < o.list.size(); ++i)
      out << "\t[" << i << "]. " << o.list[i]->getName() << std::endl;
  } else
    out << "Order list is empty.\n";

  out << std::endl;
  return out;
}

// destructor for OrderList: deletes and clears all pointers in vector list.
// the receiving function does not have to delete pointers inside the vector.
OrderList::~OrderList() {
  for (int i = 0; i < this->list.size(); ++i) {
    delete list[i];
    list[i] = nullptr;
  }
  this->list.clear();
  std::cout << "------ Order List has been cleared -----" << std::endl;
}

/*---------------------------------- Order class
 * ----------------------------------*/

int Order::getCount() { return 0; };

// default constructor
Order::Order() {
  std::cout << "Orders' default constructor called" << std::endl;
}

// param constructor to set the name variable of Order from subclasses
Order::Order(const std::string& name, const int& priority) : priority(priority){ setName(name); }

// assignment operator
Order& Order::operator=(const Order& o) {
  std::cout << "Order assignment operator done." << std::endl;
  return *this;
}

// insertion stream operator, calls a separate function to allow polymorphic
// printing
std::ostream& operator<<(std::ostream& out, Order& o) { return o.doprint(out); }

// accessor for name
std::string Order::getName() { return this->name; }

// mutator for name
void Order::setName(std::string name) { this->name = name; }

// executes the order and sets the execution status of the order; inherited by
// all subclasses
void Order::setExecuted(const bool& status) { this->executed = status; }

// gets the execution status of the order
bool Order::getExecuted() { return this->executed; }

// virtual destructor
Order::~Order() { std::cout << "Cleaning up..." << std::endl; }

/*---------------------------------- Deploy class
 * ----------------------------------*/

//static variable incrementing keeps track of obj count used for list priority
int Deploy::incrCount;

// default constructor
Deploy::Deploy() : Order("- Deploy armies -", 1), counter(incrCount++) { };

// deploy copy constructor
Deploy::Deploy(const Deploy& deploy) : counter(incrCount++) {
  setName("- Deploy armies -");
  std::cout << "Created a copy of Deploy." << std::endl;
}

// clone function for Deploy
Deploy* Deploy::clone() { return new Deploy(*this); }

// validates order
bool Deploy::validate() {
  std::cout << " Validating order..." << std::endl;
  /*validation here, can user deploy units?*/
  if (true) {
    return true;
  } else
    return false;
}

// executes deploy if valid
void Deploy::execute() {
  if (validate()) {
    // implementation of deploy
    setExecuted(true);
  } else {
    // order failed
    std::cout << "[Deploy] Cannot deploy armies. Deploy order not executed."
              << std::endl;
    setExecuted(false);
  }
}

// assignment operator
Deploy& Deploy::operator=(const Deploy& o) {
  setName("- Deploy armies -");
  std::cout << "Deploy Assignment Operator done." << std::endl;

  return *this;
}

// function called by insertion stream operator to print order
std::ostream& Deploy::doprint(std::ostream& out) {
  out << "- Deploy armies -";

  // if order has been executed, also print out effect of order
  if (getExecuted())
    out << " [Deploy] Armies have been deployed successfully." << std::endl;

  return out;
}

// destructor
Deploy::~Deploy() { std::cout << "Destroying deploy order." << std::endl; }

/*----------------------------------- Advance class
 * ----------------------------------*/

int Advance::incrCount;

// default constructor
Advance::Advance() : Order("- Advance armies -", 0), counter(incrCount++) {}

// copy constructor
Advance::Advance(const Advance& adv) : counter(incrCount++) {
  setName("- Advance armies -");
  std::cout << "Created a copy of Advance." << std::endl;
}

// clone function for Advance
Advance* Advance::clone() { return new Advance(*this); }

// validates the Advance order
bool Advance::validate() {
  std::cout << " Validating order..." << std::endl;
  /*validation here, can user advance units to this territory? attack/move*/
  if (true) {
    return true;
  } else
    return false;
}

// executes the Advance order
void Advance::execute() {
  if (validate()) {
    if (true /*if territory belong to current player*/) {
      // move armies
    } else {
      // attack armies
    }
    setExecuted(true);
  } else {
    // order failed
    std::cout << "[Advance] Armies cannot be moved. Advance order not executed."
              << std::endl;
    setExecuted(false);
  }
}

// assignment operator function
Advance& Advance::operator=(const Advance& adv) {
  setName("- Advance armies -");
  std::cout << "Advance assignment operator done." << std::endl;
  return *this;
}

// stream function to print Advance
std::ostream& Advance::doprint(std::ostream& out) {
  out << "- Advance armies -";

  // if order has been executed, also print out effect of order
  if (getExecuted()) {
    if (true /*if territory belong to current player*/)
      out << " [Advance] Armies have been moved." << std::endl;
    else
      out << " [Advance] Armies are now attacking enemy territory."
          << std::endl;
  }

  return out;
}

// virtual destructor
Advance::~Advance() { std::cout << "Destroying advance order." << std::endl; }

/*------------------------------------ Bomb class
 * ------------------------------------*/

int Bomb::incrCount;

// default constructor
Bomb::Bomb() : Order("- Bomb target country -", 0), counter(incrCount++) {};

// copy constructor
Bomb::Bomb(const Bomb& deploy) : counter(incrCount++) {
  setName("- Bomb target country -");
  std::cout << "Created a copy of Bomb." << std::endl;
}

// clone function
Bomb* Bomb::clone() { return new Bomb(*this); }

// validates order
bool Bomb::validate() {
  std::cout << " Validating order..." << std::endl;
  /*validation here, can user use bomb card?*/
  if (true) {
    return true;
  } else
    return false;
}

// executes Bomb order if valid
void Bomb::execute() {
  if (validate()) {
    // implementation of bomb
    setExecuted(true);
  } else {
    // order failed
    std::cout << " [Bomb] Cannot bomb target country. Bomb order not executed."
              << std::endl;
    setExecuted(false);
  }
}

// assignment operator
Bomb& Bomb::operator=(const Bomb& o) {
  setName("- Bomb target country -");
  std::cout << "Bomb Assignment Operator done." << std::endl;
  return *this;
}

// function called by insertion stream operator to print order
std::ostream& Bomb::doprint(std::ostream& out) {
  out << "- Bomb target country -";

  // if order has been executed, also print out effect of order
  if (getExecuted())
    out << " [Bomb] Target country bombed successfully, they have lost half "
           "their army units."
        << std::endl;

  return out;
}

// virtual destructor
Bomb::~Bomb() { std::cout << "Destroying bomb order." << std::endl; }

/*------------------------------------ Blockade class
 * ------------------------------------*/

// default constructor
Blockade::Blockade() : Order("- Blockade target country -", 3){};

// copy constructor
Blockade::Blockade(const Blockade& deploy) {
  setName("- Blockade target country -");
  std::cout << "Created a copy of Blockade." << std::endl;
}

// clone function
Blockade* Blockade::clone() { return new Blockade(*this); }

// validates order
bool Blockade::validate() {
  std::cout << " Validating order..." << std::endl;
  /*validation here, can user use blockade card?*/
  if (true) {
    return true;
  } else
    return false;
}

// executes Blockade order if valid
void Blockade::execute() {
  if (validate()) {
    // implementation of Blockade
    setExecuted(true);
  } else {
    // order failed
    std::cout << "[Blockade] Cannot blockade target territory. Blockade order "
                 "not executed."
              << std::endl;
    setExecuted(false);
  }
}

// assignment operator
Blockade& Blockade::operator=(const Blockade& o) {
  setName("- Blockade target country -");
  std::cout << "Blockade Assignment Operator done." << std::endl;
  return *this;
}

// function called by insertion stream operator to print order
std::ostream& Blockade::doprint(std::ostream& out) {
  out << "- Blockade target country -";

  // if order has been executed, also print out effect of order
  if (getExecuted())
    out << " [Blockade] Blockade Successful. Target territory's army units "
           "count has tripled and became neutral."
        << std::endl;

  return out;
}

// virtual destructor
Blockade::~Blockade() {
  std::cout << "Destroying blockade order." << std::endl;
}

/*------------------------------------ Airlift class
 * ------------------------------------*/

// default constructor
Airlift::Airlift() : Order("- Airlift to target country -", 2){};

// copy constructor
Airlift::Airlift(const Airlift& deploy) {
  setName("- Airlift to target country -");
  std::cout << "Created a copy of Airlift." << std::endl;
}

// clone function
Airlift* Airlift::clone() { return new Airlift(*this); }

// validates order
bool Airlift::validate() {
  std::cout << " Validating order..." << std::endl;
  /*validation here, can user use Airlift card?*/
  if (true) {
    return true;
  } else
    return false;
}

// executes Airlift order if valid
void Airlift::execute() {
  if (validate()) {
    // implementation of Airlift
    setExecuted(true);
  } else {
    // order failed
    std::cout << "[Airlift] Cannot airlift army. Airlift order not executed."
              << std::endl;
    setExecuted(false);
  }
}

// assignment operator
Airlift& Airlift::operator=(const Airlift& o) {
  setName("- Airlift to target country -");
  std::cout << "Airlift Assignment Operator done." << std::endl;

  return *this;
}

// function called by insertion stream operator to print order
std::ostream& Airlift::doprint(std::ostream& out) {
  out << "- Airlift to target country -";

  // if order has been executed, also print out effect of order
  if (getExecuted())
    out << " [Airlift] Airlift successful. Friendly army units have been moved "
           "to new territory."
        << std::endl;

  return out;
}

// virtual destructor
Airlift::~Airlift() { std::cout << "Destroying airlift order." << std::endl; }

/*------------------------------------ Negotiate class
 * ------------------------------------*/

// default constructor
Negotiate::Negotiate() : Order("- Negotiate with target player -", 0) {}

// copy constructor
Negotiate::Negotiate(const Negotiate& n) {
  setName("- Negotiate with target player -");
  std::cout << "Created a copy of Negotiate." << std::endl;
}

// clone function
Negotiate* Negotiate::clone() { return new Negotiate(*this); }

// validates order
bool Negotiate::validate() {
  std::cout << " Validating order...";
  // validation here, can user use Negotiate card?
  if (true) {
    return true;
  } else {
    return false;
  }
}

// executes Negotiate order if valid
void Negotiate::execute() {
  if (validate()) {
    // implement negotiate
    setExecuted(true);
  } else {
    std::cout
        << "[Negotiate] Negotiation failed. Negotiation order not executed."
        << std::endl;
    setExecuted(false);
  }
}

// assignment operator function
Negotiate& Negotiate::operator=(const Negotiate& n) {
  setName("- Negotiate with target player -");
  std::cout << "Negotiation assignment operator done." << std::endl;
  return *this;
}

// function called by insertion stream operator to print order
std::ostream& Negotiate::doprint(std::ostream& out) {
  out << "- Negotiate with target player -";

  // if order has been executed, also print out effect of order
  if (getExecuted())
    out << " [Negotiate] Negotiation successful. No attacks will be made "
           "between two players until end of turn."
        << std::endl;

  return out;
}

// virtual destructor
Negotiate::~Negotiate() {
  std::cout << "Destroying negotiate order." << std::endl;
}