/////////////////////////////////////////////
// Filename:        Player.cpp
//
// Description:     Implementation of Part 3 - Player
//
// Author:          Sandra Buchen - 26317987
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#include "Player.h"

#include <algorithm>
#include <ostream>
#include <vector>

/**
 * Default constructor initialize the members of Player to their default values.
 */
Player::Player() {
  this->Territories = std::vector<Territory *>{};
  this->HandOfCards = new Hand();
  this->ListOfOrders = new OrderList();
  this->PID = "";
  std::cout << "Default Player constructor" << std::endl;
}

/**
 * Constructor with given parameters.
 *
 * @param territories A list of territory objects the player owns.
 * @param handOfCards A hand of cards the player owns.
 * @param listOfOrders A list of orders the player owns.
 */
Player::Player(std::vector<Territory *> territories, Hand handOfCards,
               OrderList listOfOrders, std::string pid) {
  std::cout << "Regular Player constructor" << std::endl;

  // Declare those territories as belonging to this player
  for (auto &i : territories) {
    i->OwnedBy = this->PID;
  }

  this->Territories = territories;
  this->HandOfCards = new Hand(handOfCards);
  this->ListOfOrders = new OrderList(listOfOrders);
  this->PID = pid;
}

/**
 * Copy constructor that creates a deep copy of a player object.
 *
 * @param p The object to copy.
 */
Player::Player(const Player &p) {
  std::cout << "Player Copy constructor\n";

  this->HandOfCards = new Hand(*p.HandOfCards);
  this->ListOfOrders = new OrderList(*p.ListOfOrders);
  this->PID = p.PID;
  this->ReinforcementPool = p.ReinforcementPool;

  for (auto i = p.Territories.begin(); i != p.Territories.end(); ++i) {
    auto *country = new Territory(**i);
    this->Territories.push_back(country);
  }
}

/**
 * Overloaded assignment operator that create a deep copy of a player object.
 *
 * @param p The object to equate.
 */
Player &Player::operator=(const Player &p) {
  // clear original reference
  if (!this->Territories.empty()) {
    for (auto &i : Territories) {
      delete i;
      i = nullptr;
    }
  }
  delete this->HandOfCards;
  delete this->ListOfOrders;

  std::cout << "Player = operator\n";
  this->HandOfCards = new Hand(*p.HandOfCards);
  this->ListOfOrders = new OrderList(*p.ListOfOrders);
  this->PID = p.PID;
  this->ReinforcementPool = p.ReinforcementPool;

  for (auto i = p.Territories.begin(); i != p.Territories.end(); ++i) {
    auto *country = new Territory(**i);
    this->Territories.push_back(country);
  }

  return *this;
}

/**
 * Overloaded stream operator for player
 *
 * @param out The stream object.
 * @param p The player object to print.
 */
std::ostream &operator<<(std::ostream &out, const Player &p) {
  out << p.PID << "\n";
  out << "\tCountries: \n";
  for (auto i = p.Territories.begin(); i != p.Territories.end(); ++i) {
    out << "\t----------\n";
    out << **i << "\n";
  }
  out << "\n";

  out << "\tCards: " << *p.HandOfCards;
  out << "\n\n";

  out << "\tOrders: " << *p.ListOfOrders;
  out << "\n";

  out << "\tReinforcement Pool: " << p.ReinforcementPool;
  out << "\n";

  return out;
}

/**
 * A function that determines the territories a player can defend.
 *
 * @return A list of territories.
 */
std::vector<Territory *> Player::toDefend() { return Territories; }

/**
 *  A function that determines the list of territories a player can attack.
 *  @param map Map object that contains all the territory data of the game
 *  @return A list of territories.
 */
std::vector<Territory *> Player::toAttack(Map &map) {
  std::vector<Territory *> territoriesToAttack;
  for (auto &territory : this->Territories) {
    // Get list of adjacent territories of a single territory
    auto adjacentTerritory =
        map.ReturnListOfAdjacentCountriesByID(territory->TerritoryID);

    // Add them to the list of player's territories that can be attacked
    territoriesToAttack.insert(territoriesToAttack.end(),
                               adjacentTerritory.begin(),
                               adjacentTerritory.end());
  }
  return territoriesToAttack;
}

/**
 * A function that creates a method object and adds it to the player's list of
 * orders.
 *
 */
void Player::issueOrder(Map &map, Deck &deckOfCards) { 

  auto toAttack = this->toAttack(map);
  auto toDefend = this->toDefend();

  // Deploy armies until nothing left in pool
  // TODO change logic to deploy on list of territories from to defend
  if (this->ReinforcementPool > 0) {
    auto *order = new Deploy();
    this->ListOfOrders->addToList(order);
    this->ReinforcementPool--;
  } else if(!AdvanceOrderDone) {
    // TODO change logic to include toAttack OR toDefend
    auto *order = new Advance();
    this->ListOfOrders->addToList(order);
    this->AdvanceOrderDone = true;
  } else if(!CardPlayed) {
    // TODO how do we decide which card to pick?
    this->HandOfCards->returnByPos(0).Play(*HandOfCards, *ListOfOrders,
                                             deckOfCards);
    this->CardPlayed = true;
  } else {
    std::cout << "No orders left to make" << std::endl;
  }
 
}

/**
 * Destructor of the player object.
 */
Player::~Player() {
  // Delete list of territory pointers if they exist.
  if (!this->Territories.empty()) {
    for (auto &i : Territories) {
      delete i;
      i = nullptr;
    }
  }
  // Delete the members that are pointers.
  delete this->HandOfCards;
  delete this->ListOfOrders;
  this->HandOfCards = nullptr;
  this->ListOfOrders = nullptr;
}
