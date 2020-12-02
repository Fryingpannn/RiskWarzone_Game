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
#include <cstdlib>
#include <ctime>
#include <map>
#include <ostream>
#include <utility>
#include <vector>

/**
 * Default constructor initialize the members of Player to their default values.
 */
Player::Player() {
  this->Territories = std::vector<Territory *>{};
  this->HandOfCards = new Hand();
  this->ListOfOrders = new OrderList();
  this->PID = "";
  this->ReinforcementPool = 0;
  this->ReinforcementsDeployed = 0;
  this->AdvanceOrderDone = true;
  this->CardPlayed = true;
  this->cardNotGiven = true;
  this->set = std::unordered_set<std::string>{};
  this->ListOfPlayers = std::vector<Player *>{};
  this->MainMap = nullptr;
  this->DeckOfCards = nullptr;
  this->Strategy = nullptr;
}

/**
 * Constructor with given parameters.
 *
 * @param territories A list of territory objects the player owns.
 * @param handOfCards A hand of cards the player owns.
 * @param listOfOrders A list of orders the player owns.
 * @param pID The name of the player
 */
Player::Player(std::vector<Territory *> territories, Hand handOfCards,
               OrderList listOfOrders, std::string pID) {
  this->PID = std::move(pID);
  // Declare those territories as belonging to this player
  for (auto &i : territories) {
    i->OwnedBy = this->PID;
    i->PlayerOwned = this;
  }

  this->Territories = territories;
  this->HandOfCards = new Hand(handOfCards);
  this->ListOfOrders = new OrderList(listOfOrders);
  this->ReinforcementPool = 0;
  this->ReinforcementsDeployed = 0;
  this->AdvanceOrderDone = true;
  this->CardPlayed = true;
  this->cardNotGiven = true;
  this->set = std::unordered_set<std::string>{};
  this->ListOfPlayers = std::vector<Player *>{};
  this->MainMap = nullptr;
  this->DeckOfCards = nullptr;
  this->Strategy = nullptr;
}

/**
 * Copy constructor that creates a deep copy of a player object.
 *
 * @param p The object to copy.
 */
Player::Player(const Player &p) {
  this->HandOfCards = new Hand(*p.HandOfCards);
  this->ListOfOrders = new OrderList(*p.ListOfOrders);
  this->PID = p.PID;
  this->ReinforcementPool = p.ReinforcementPool;
  this->ReinforcementsDeployed = p.ReinforcementsDeployed;
  this->AdvanceOrderDone = p.AdvanceOrderDone;
  this->CardPlayed = p.CardPlayed;
  this->cardNotGiven = p.cardNotGiven;
  this->set = p.set;
  this->ListOfPlayers = p.ListOfPlayers;
  // Not deep copies since we want to use same map and deck.
  this->MainMap = p.MainMap;
  this->DeckOfCards = p.DeckOfCards;
  this->Strategy = p.Strategy;

  for (auto i = p.Territories.begin(); i != p.Territories.end(); ++i) {
    auto *country = new Territory(**i);
    this->Territories.push_back(country);
  }
}

/**
 * Destructor of the player object.
 */
Player::~Player() {
  // Delete list of territory pointers if they exist.
  if (!this->Territories.empty()) {
    for (auto &i : Territories) {
      if (i != nullptr) {
        i = nullptr;
      }
    }
    this->Territories.clear();
  }

  delete this->HandOfCards;
  this->HandOfCards = nullptr;

  delete this->ListOfOrders;
  this->ListOfOrders = nullptr;

  // These pointers are deleted by game engine
  if (this->MainMap != nullptr) {
    this->MainMap = nullptr;
  }

  if (this->DeckOfCards != nullptr) {
    this->DeckOfCards = nullptr;
  }

  if (this->Strategy != nullptr) {
    delete this->Strategy;
    this->Strategy = nullptr;
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

  this->HandOfCards = new Hand(*p.HandOfCards);
  this->ListOfOrders = new OrderList(*p.ListOfOrders);
  this->PID = p.PID;
  this->ReinforcementPool = p.ReinforcementPool;
  this->ReinforcementsDeployed = p.ReinforcementsDeployed;
  this->AdvanceOrderDone = p.AdvanceOrderDone;
  this->CardPlayed = p.CardPlayed;
  this->cardNotGiven = p.cardNotGiven;
  this->set = p.set;
  this->ListOfPlayers = p.ListOfPlayers;
  // Not deep copies since we want to use same map and deck.
  this->MainMap = p.MainMap;
  this->DeckOfCards = p.DeckOfCards;
  this->Strategy = p.Strategy;

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

  out << "\tReinforcement Pool: " << p.ReinforcementPool;
  out << "\n";

  out << "\tOrders: " << *p.ListOfOrders;
  out << "\n";

  out << "\tCards: " << *p.HandOfCards;
  out << "\n";

  return out;
}

void Player::bindGameElements(std::vector<Player *> &inPlayers, Map *mapIn,
                              Deck *deckIn) {
  this->MainMap = mapIn;
  this->DeckOfCards = deckIn;
  this->ListOfPlayers = inPlayers;
}

void Player::initIssueOrder() {
  this->AdvanceOrderDone = false;
  this->CardPlayed = false;
  this->ReinforcementsDeployed = 0;
}

void Player::removeTerritory(Territory &t) {
  int pos = 0;
  for (auto *owned : this->Territories) {
    if (owned->TerritoryID == t.TerritoryID) {
      break;
    }
    pos++;
  }
  this->Territories.erase(this->Territories.begin() + pos);
};

/**
 * A function that determines the territories a player can defend.
 *
 * @return A list of territories.
 */
std::vector<Territory *> Player::toDefend() {
  return this->Strategy->toDefend(*this);
}

/**
 *  A function that determines the list of territories a player can attack.
 *  @return A list of territories.
 */
std::vector<Territory *> Player::toAttack() {
  return this->Strategy->toAttack(*this);
}

/**
 * A function that manages the order issuing phase for a player's
 * turn. It place an order in the player's order's list.
 *
 */
void Player::issueOrder() { this->Strategy->issueOrder(*this); }

void Player::setStrategy(PlayerStrategy *strategy) {
	delete this->Strategy;
  this->Strategy = strategy;
}
