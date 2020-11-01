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
#include "Map.h"
#include <random>

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
int OrderList::remove(int position) {
  auto it = this->list.begin() + position;
  int reArmyNb = (*it)->getArmyNb();
  delete *it;
  this->list.erase(it);
  std::cout << "-> Order " << position << " has been removed." << std::endl;
  return reArmyNb;
}

// returns: nullptr if list is empty, otherwise returns a pointer to a copy
//          of the next priority element (needs to be explicitly deleted)
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

// returns: nullptr if list is empty, otherwise returns a pointer to a copy
//          of the next priority element (needs to be explicitly deleted)
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
//          otherwise returns a pointer (needs to be explicitly deleted)
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

// default constructor
Order::Order() : armyNb(0) {
  std::cout << "Orders' default constructor called" << std::endl;
}

// param constructor to set the name variable of Order from subclasses
Order::Order(const std::string& name, const int& priority) : priority(priority) { setName(name); }

// assignment operator
Order& Order::operator=(const Order& o) {
  std::cout << "Order assignment operator done." << std::endl;
  return *this;
}

// insertion stream operator, calls a separate function to allow polymorphic
// printing
std::ostream& operator<<(std::ostream& out, Order& o) { return o.doprint(out); }

// getter/setter for name
std::string Order::getName() { return this->name; }
void Order::setName(const std::string& name) { this->name = name; }

//getter for armyNb
int Order::getArmyNb() { return armyNb; }

// getter/setter for executed status
void Order::setExecuted(const bool& status) { this->executed = status; }
bool Order::getExecuted() { return this->executed; }

// virtual destructor
Order::~Order() { std::cout << "Cleaning up..." << std::endl; }

/*---------------------------------- Deploy class
 * ----------------------------------*/

// default constructor
Deploy::Deploy() : Order("- Deploy armies -", 1) { };

// deploy copy constructor
Deploy::Deploy(const Deploy& deploy) {
  setName("- Deploy armies -");
  std::cout << "Created a copy of Deploy." << std::endl;
}

/* -constructor to deploy armies to target territory (note: territory passed is a pointer).
 * -playerID is the player who issued this order
 * -armyNb needs to be deducted from player's own reinf. pool
 * -the armyNb is only returned if remove() is used on the order.
 */
Deploy::Deploy(const std::string& playerID, const int& armyNb, Territory* target) {
    this->armyNb = armyNb;
    this->target = target;
    this->playerID = playerID;
}

// clone function for Deploy
Deploy* Deploy::clone() { return new Deploy(*this); }

// validates deploy; returns true if target territory belongs to player
bool Deploy::validate() {
  std::cout << " Validating order..." << std::endl;
  if (target == nullptr || target->OwnedBy.compare(playerID) != 0 || armyNb <= 0)
      return false;
  else
      return true;
}

// executes deploy if valid
// the army count in reinforcement pool must be deducted in Player class
void Deploy::execute() {
    //add the armies to target territory if it belongs to the player
    if (validate()) {
        target->Armies += armyNb;
        std::cout << "[Valid] 1 Deploy order executed." << std::endl;
    }
    else
        std::cout << "[Invalid] 1 Deploy order not executed." << std::endl;
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

// default constructor
Advance::Advance() : Order("- Advance armies -", 0) {}

// copy constructor
Advance::Advance(const Advance& adv) {
  setName("- Advance armies -");
  std::cout << "Created a copy of Advance." << std::endl;
}

/* constructor to advance armies from source territory to target territory.
*  - armyNb is only returned if remove() is used on the order.
*  - if an enemy territory is successfully conquered, its OwnedBy will be updated, but it then 
*     needs to be added to the player's list.
* 
* parameters:
*   playerID: current player's PID
 *  armyNb  : number of armies to advance
 *  src     : starting point
 *  target  : the target territory to advance to
 *  map     : pointer to current map, used to get adjacent territories to src
 *  deck    : pointer to deck of the game, used to give a card to player
 */
Advance::Advance(const std::string& playerID, const int& armyNb, Territory* src,
    Territory* target, Map* map, Player* const current, Deck* const deck) {
    this->playerID = playerID;
    this->armyNb = armyNb;
    this->src = src;
    this->target = target;
    this->map = map;
    this->current = current;
    this->deck = deck;
    // subtract sent armies from original
    src->Armies -= armyNb;
}

// clone function for Advance
Advance* Advance::clone() { return new Advance(*this); }

// validates the Advance order
bool Advance::validate() {
  std::cout << " Validating order..." << std::endl;
  //return false if src doesn't belong to player
  if (src == nullptr || armyNb <= 0 || src->OwnedBy.compare(playerID) != 0)
      return false;
  
  //return false if target territory's owner and current owner are on diplomatic status (negotiation)
  if (enemy->set->find(target->OwnedBy) != enemy->set->end())
      return false;

  //adj: list of territories adjacent to source
  adj = map->ReturnListOfAdjacentCountriesByID(src->TerritoryID);

  //checks if target is an adjacent territory of source
  bool isAdjacent = false;
  for (int i = 0; i < adj.size(); i++) {
      if (adj[i]->TerritoryID == target->TerritoryID) {
          return true;
      }
  }
  //returns false if src and target aren't adjacent territories
  return false;
}

// executes the Advance order
void Advance::execute() {
  if (validate()) {
     //if target territory is also owned by user, simply move armies there
    if (target->OwnedBy.compare(playerID) == 0) {
        target->Armies += armyNb;
        std::cout << "[Valid] 1 Advance order executed. Armies moved to new territory." << std::endl;
    }
    //if target territory not owned by user, attack initiated
    else {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, 100);

        while (target->Armies > 0 || src->Armies > 0) {
            int targetArmies = target->Armies;
            //each attacking army has 60% chance of killing
            for (int i = 0; i < armyNb; i++) {
                int result = distribution(generator);
                if (result <= 60)
                    target->Armies -= 1;
            }
            //each defending army has 70% chance of killing
            for (int i = 0; i < targetArmies; i++) {
                int result = distribution(generator);
                if (result <= 70)
                    armyNb -= 1;
            }
        }
        //possible results from the attack
        if (target->Armies <= 0 && armyNb <= 0) {
            //if both lost all their armies during the attack
            target->Armies = 0;
            armyNb = 0;
            target->OwnedBy = playerID;
            //give new card to player if not given yet this turn
            if (current->cardNotGiven) {
                deck->draw(*current->HandOfCards);
                current->cardNotGiven = false;
            }
            std::cout << "[Valid] 1 Advance order executed. Both territories lost their armies. Target"
                << " territory captured." << std::endl;
        }
        else if (target->Armies <= 0) {
            //if attacker won
            target->Armies = armyNb;
            target->OwnedBy = playerID;
            //give new card to player if not given yet this turn
            if (current->cardNotGiven) {
                deck->draw(*current->HandOfCards);
                current->cardNotGiven = false;
            }
            std::cout << "[Valid] 1 Advance order executed. Target territory captured." << std::endl;
        }
        else if (armyNb <= 0) {
            //if defender won
            armyNb = 0; 
            std::cout << "[Valid] 1 Advance order executed. Failed to capture target territory." << std::endl;
        }
    }
    setExecuted(true);
  } else {
    // order failed
    std::cout << "[Invalid] 1 Advance order not executed." << std::endl;
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

// default constructor
Bomb::Bomb() : Order("- Bomb target country -", 0) {};

// copy constructor
Bomb::Bomb(const Bomb& deploy) {
  setName("- Bomb target country -");
  std::cout << "Created a copy of Bomb." << std::endl;
}

// constructor to bomb half the armies in target territory.
// playerID and current correspond to the player who issued this order
Bomb::Bomb(const std::string& playerID, Territory* target, Player* const current) {
    this->playerID = playerID;
    this->target = target;
    this->current = current;
}

// clone function
Bomb* Bomb::clone() { return new Bomb(*this); }

// validates order
bool Bomb::validate() {
  std::cout << " Validating order..." << std::endl;
  //don't bomb if target territory belongs to current player or if diplomacy status exists with target player.
  if (target == nullptr || target->OwnedBy.compare(playerID) == 0 || 
      current->set->find(target->OwnedBy) != current->set->end())
      return false;
  else
      return true;
}

// executes Bomb order if valid; target territory's armies are halved
void Bomb::execute() {
  if (validate()) {
      target->Armies /= 2;
      std::cout << "[Valid] 1 Bomb order executed." << std::endl;
    setExecuted(true);
  } else {
    // order failed
    std::cout << " [Invalid] 1 Bomb order not executed."
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

// constructor; double friendly territory and transform it to neutral
// - playerID is the player who issued this order. Can only be played with the blockade card.
// - after execution, the territory need to be removed from the player's list as it's now neutral.
Blockade::Blockade(const std::string& playerID, Territory* src) {
    this->playerID = playerID;
    this->src = src;
}

// clone function
Blockade* Blockade::clone() { return new Blockade(*this); }

// validates order
bool Blockade::validate() {
  std::cout << " Validating order..." << std::endl;
  if (src == nullptr || src->OwnedBy.compare(playerID) != 0)
      return false;
  else
      return true;
}

// executes Blockade order if valid
void Blockade::execute() {
  if (validate()) {
    src->Armies *= 2;
    src->OwnedBy = "neutral";
    std::cout << "[Valid] 1 Blockade order executed" << std::endl;
    setExecuted(true);
  } 
  else {
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

/* constructor; airlifts a number of armies to target territory (initiate attack if enemy territory)
 * - playerID is the player who issued the order
 * - if an enemy territory is successfully conquered, its OwnedBy will be updated, but it then 
     needs to be added to the player's list.
   - the armyNb is only returned if remove() is used on the order.
 */
Airlift::Airlift(const std::string& playerID, const int& armyNb, Territory* src, Territory* target) {
    this->playerID = playerID;
    this->armyNb = armyNb;
    this->src = src;
    this->target = target;
    // subtract sent armies from source territory
    src->Armies -= armyNb;
}

// clone function
Airlift* Airlift::clone() { return new Airlift(*this); }

// validates order; returns true if src and target are owned by the player
bool Airlift::validate() {
  std::cout << " Validating order..." << std::endl;
  if (src == nullptr || target == nullptr || src->OwnedBy.compare(playerID) != 0 ||
      target->OwnedBy.compare(playerID) != 0)
      return false;
  else
      return true;
}

// executes Airlift order if valid
void Airlift::execute() {
    if (validate()) {
       //if target territory is owned by user, simply move armies there
       target->Armies += armyNb;
       std::cout << "[Valid] 1 Airlift order executed." << std::endl;
       setExecuted(true);
    }
    else {
        // order failed
        std::cout << "[Invalid] 1 Airlift order not executed." << std::endl;
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

/* constructor; prevent further attacks between two players for the turn.
*  Negotiation can only be created with diplomacy card.
 * - current:  the current player who created this order
 * - player:   the enemy player to negotiate with
 */
Negotiate::Negotiate(Player* const current, Player* const enemy) {
    this->playerID = current->PID;
    this->current = current;
    this->enemy = enemy;
}

// clone function
Negotiate* Negotiate::clone() { return new Negotiate(*this); }

// validates order; return true if target player is not self
bool Negotiate::validate() {
  std::cout << " Validating order...";
  if (enemy == nullptr || enemy->PID.compare(playerID) == 0)
      return false;
  else
      return true;
}

// executes Negotiate order if valid
void Negotiate::execute() {
  if (validate()) {
    //insert the current player ID into diplomacy set of enemy player
    enemy->set->insert(playerID);
    //insert the enemy ID into diplomacy set of current player
    current->set->insert(enemy->PID);
    std::cout << "[Valid] 1 Negotiate order executed." << std::endl;
    setExecuted(true);
  } else {
    std::cout
        << "[Invalid] 1 Negotiate/Diplomacy order not executed."
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