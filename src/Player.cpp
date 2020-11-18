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
std::vector<Territory *> Player::toDefend() { return this->Territories; }

/**
 *  A function that determines the list of territories a player can attack.
 *  @return A list of territories.
 */
std::vector<Territory *> Player::toAttack() {
  // Using a map to ensure unique values of territories
  std::map<int, Territory *> toAttackMap;
  auto ownedTerritories = this->toDefend();

  for (auto &elem : ownedTerritories) {
    // Get list of adjacent territories of a single territory
    // that the player owns
    auto computeAdjacentResult =
        this->MainMap->ReturnListOfAdjacentCountriesByID(elem->TerritoryID);
    std::cout << "adjacent of " << elem->Name << "\n";

    for (auto &t : computeAdjacentResult) {
      std::cout << "\t\t" << t->Name << " [Owned by " << t->OwnedBy
                << " PlayerOwned" << t->PlayerOwned->PID << "]"
                << " Armies " << t->Armies << "\n";
    }
    // Keep only territories that a player does not already own.
    for (auto &t : computeAdjacentResult) {
      auto it = std::find(ownedTerritories.begin(), ownedTerritories.end(), t);
      if (it == ownedTerritories.end()) {
        toAttackMap.insert(std::pair<int, Territory *>(t->TerritoryID, t));
      }
    }
  }

  // Convert map to a vector
  std::vector<Territory *> toAttack;
  for (auto &t : toAttackMap) {
    toAttack.push_back(t.second);
  }
  return toAttack;
}

/**
 * A function that manages the order issuing phase for a player's
 * turn. It place an order in the player's order's list.
 *
 */
void Player::issueOrder() {
  // Deploy armies until nothing left in pool
  if (this->ReinforcementPool - this->ReinforcementsDeployed > 0) {
    createDeploy();

    // Perform an advance order that either attacks or transfers
  } else if (!AdvanceOrderDone) {
    srand(time(NULL));

    // Make players more likely to attack than transfer to end game faster
    if ((rand() % 100) > 99) {
      advanceTransfer();
    } else {
      advanceAttack();
    }
    this->AdvanceOrderDone = true;
    // Play a card
  } else if (!CardPlayed) {
    playCard();
    this->CardPlayed = true;
  }
  // Else no orders left
}

/**
 * Helper function for issuing orders related to deploying reinforcements.
 */
void Player::createDeploy() {
  auto ownedTerritories = this->toDefend();

  // Chooses a random place to deploy a random amount of armies
  srand(time(NULL));
  auto *territoryToDeploy =
      ownedTerritories.at(rand() % (ownedTerritories.size()));

  int armies = 0;
  if (this->ReinforcementPool - this->ReinforcementsDeployed > 0) {
    armies =
        1 + rand() % (this->ReinforcementPool - this->ReinforcementsDeployed);
  }

  // Perform the deploy order
  auto *order = new Deploy(this->PID, armies, territoryToDeploy, this);
  std::cout << this->PID << " deploy " << armies << " from "
            << this->ReinforcementPool << " - " << this->ReinforcementsDeployed;
  this->ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
  this->ReinforcementsDeployed += armies;
}

/**
 * Helper function of issuing orders related to creating the advance
 * order for attacking neighboring enemies.
 */
void Player::advanceAttack() {
  auto toAttackTerritories = this->toAttack();
  auto ownedTerritories = this->toDefend();

  srand(time(NULL));

  // Chose a territory as a source of attack
  Territory *src = ownedTerritories.at(rand() % (ownedTerritories.size()));

  // Chose any target from to attack pool even if not a neighbor, orders will
  // validate
  auto *target = toAttackTerritories.at(rand() % (toAttackTerritories.size()));

  // Attack with all armies in that territory to speed up game play
  auto *order = new Advance(this->PID, src->Armies, src, target, this->MainMap,
                            this, this->DeckOfCards);
  this->ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

/**
 * Helper function of issuing orders related to creating the advance
 * order for transferring armies to neighbors.
 */
void Player::advanceTransfer() {
  auto ownedTerritories = this->toDefend();

  srand(time(NULL));
  auto *src = ownedTerritories.at(rand() % (ownedTerritories.size()));
  auto *target = ownedTerritories.at(rand() % (ownedTerritories.size()));
  int armies = 0;
  if (src->Armies > 0) {
    armies = 1 + rand() % src->Armies;
  }

  auto *order = new Advance(this->PID, armies, src, target, this->MainMap, this,
                            this->DeckOfCards);
  this->ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

/**
 * Helper function for issuing orders that plays a card.
 */
void Player::playCard() {
  srand(time(NULL));

  if (this->HandOfCards->size() == 0) {
    std::cout << "You have no cards in your hand.\n";
  } else {
    // Display the cards in a player's hand.
    std::cout << "These are the card in your hand:\n";
    std::cout << *this->HandOfCards << std::endl;
    auto cardToPlay =
        this->HandOfCards->returnByPos(rand() % (this->HandOfCards->size()));
    // Method inside cards class calls the correct player creation order
    // function
    cardToPlay.Play(*this, *this->HandOfCards, *this->DeckOfCards);
  }
}

/**
 * Wrapper function of card BOMB that issues the respective order.
 */
void Player::createBomb() {
  srand(time(NULL));

  auto toBomb = this->toAttack();
  auto *target = toBomb.at(rand() % toBomb.size());

  auto *order = new Bomb(this->PID, target, this);
  this->ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

/**
 * Wrapper function of card AIRLIFT that issues the respective order.
 */
void Player::createAirlift() {
  srand(time(NULL));

  auto ownedTerritories = this->toDefend();
  auto *src = ownedTerritories.at(rand() % (ownedTerritories.size()));

  const auto pos = rand() % this->MainMap->NumOfCountries();
  auto *target = this->MainMap->ReturnListOfCountries().at(pos);

  int armies = 0;
  if (src->Armies > 0) {
    armies = 1 + rand() % src->Armies;
  }

  auto *order =
      new Airlift(this->PID, armies, src, target, this, this->DeckOfCards);
  this->ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

/**
 * Wrapper function of card BLOCKADE that issues the respective order.
 */
void Player::createBlockade() {
  srand(time(NULL));

  auto ownedTerritories = this->toDefend();

  auto *src = ownedTerritories.at(rand() % (ownedTerritories.size()));

  auto *order = new Blockade(this->PID, src);
  this->ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

/**
 * Wrapper function of card NEGOTIATE that issues the respective order.
 */
void Player::createNegotiate() {
  srand(time(NULL));

  Player *enemy = this->ListOfPlayers.at(rand() % (this->ListOfPlayers.size()));
  auto *order = new Negotiate(this, enemy);
  this->ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

/**
 * Wrapper function of card REINFORCEMENT that issues the respective order.
 */
void Player::createReinforcement() {
  this->ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(new Reinforcement(this)));
}

/**
 * Destructor of the player object.
 */
Player::~Player() {
  // Delete list of territory pointers if they exist.
  if (!this->Territories.empty()) {
    for (auto &i : Territories) {
      if (i != nullptr) {
        delete i;
        i = nullptr;
      }
    }
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
}
