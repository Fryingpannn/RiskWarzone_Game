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
#include <map>
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

  this->PID = pid; //<=========== HERE
  // Declare those territories as belonging to this player
  for (auto &i : territories) {
    i->OwnedBy = this->PID;
  }

  this->Territories = territories;
  this->HandOfCards = new Hand(handOfCards);
  this->ListOfOrders = new OrderList(listOfOrders);
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

void Player::bindGameElements(Map *mapIn, Deck *deckIn) {
  this->MainMap = mapIn;
  this->DeckOfCards = deckIn;
}

void Player::initIssueOrder() {
  this->AdvanceOrderDone = false;
  this->CardPlayed = false;
}

/**
 * A function that determines the territories a player can defend.
 *
 * @return A list of territories.
 */
std::map<int, Territory *> Player::toDefend() {
  std::map<int, Territory *> toDefendMap;
  for (auto &t : Territories) {
    toDefendMap.insert(std::pair<int, Territory *>(t->TerritoryID, t));
  }

  return toDefendMap;
}

/**
 *  A function that determines the list of territories a player can attack.
 *  @param map Map object that contains all the territory data of the game
 *  @return A list of territories.
 */
std::map<int, Territory *> Player::toAttack() {
  std::map<int, Territory *> toAttackMap;
  auto ownedTerritories = this->toDefend();
  for (auto &elem : ownedTerritories) {
    // Get list of adjacent territories of a single territory
    // that the player owns
    auto computeAdjacentResult =
        this->MainMap->ReturnListOfAdjacentCountriesByID(elem.first);

    // Keep only territories that a player does not already own.
    for (auto &t : computeAdjacentResult) {
      if (ownedTerritories.find(t->TerritoryID) == ownedTerritories.end()) {
        toAttackMap.insert(std::pair<int, Territory *>(t->TerritoryID, t));
      }
    }
  }

  return toAttackMap;
}

/**
 * A function that manages the order issuing phase for a player's
 * turn. It place an order in the player's order's list.
 *
 */
void Player::issueOrder() {
  // Deploy armies until nothing left in pool
  if (this->ReinforcementPool > 0) {
    std::cout << "Reinforcement\n";
    reinforce();

    // Perform an advance order that either attacks or transfers
  } else if (!AdvanceOrderDone) {
    std::cout << "Advance: Attack/Transfer\n";

    bool validInput{false};
    std::string input{"x"};

    while (!validInput) {
      std::cout << "Would you like to transfer [t] armies or attack [a] a "
                   "neighboring enemy?\n";
      std::cin >> input;
      if (std::cin.fail()) {
        std::cin.clear();
        std::string discard;
        getline(std::cin, discard);
        std::cout << "Enter an INTEGER value\n";
      } else {
        if (input != "a" && input != "t") {
          std::cout << "The input " << input << " is not valid. Try again.\n";
        } else {
          validInput = true;
        }
      }
    }

    if (input == "a") {
      advanceAttack();
    } else {
      advanceTransfer();
    }
    this->AdvanceOrderDone = true;

    // Play a card
  } else if (!CardPlayed) {
    std::cout << "Play Card\n";
    playCard();
    this->CardPlayed = true;

  } else {
    std::cout << "No orders left to make" << std::endl;
  }
}

/**
 * Helper function for issuing orders related to deploying reinforcements.
 */
void Player::reinforce() {
  auto toDefendMap = this->toDefend();
  // Print territories that can be defended
  for (auto &t : toDefendMap) {
    std::cout << "[" << t.first << "]: " << t.second->Name << std::endl;
  }

  // Ask player to chose where to deploy armies
  int indexToReinforce{-1};
  bool validInput{false};
  while (!validInput) {
    std::cout << "Pick the index of the territory you wish to reinforce\n";
    std::cin >> indexToReinforce;
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (indexToReinforce < 0 ||
          toDefendMap.find(indexToReinforce) == toDefendMap.end()) {
        std::cout << indexToReinforce
                  << " is not an acceptable input. Try again.";
      } else {
        validInput = true;
      }
    }
  }

  // Ask player how many armies he wants to deploy
  validInput = false;
  int armies{0};
  while (!validInput) {
    std::cout << "You have " << ReinforcementPool
              << " armies left to deploy.\n";
    std::cout << "Pick the number of armies to reinforce "
              << toDefendMap.at(indexToReinforce)->Name << " with.\n";
    std::cin >> armies;
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (armies < 1 || armies > ReinforcementPool) {
        std::cout << "The number of armies (" << armies
                  << ") is not a valid input. \n";
      } else {
        validInput = true;
      }
    }
  }

  // Perform the deploy order
  // TODO change logic to deploy on list of territories from to defend
  auto *order = new Deploy();
  this->ListOfOrders->addToList(order);
  this->ReinforcementPool -= armies;

  std::cout << "Player " << this->PID << " - issued deploy on "
            << toDefendMap.at(indexToReinforce)->Name << " of " << armies
            << " armies.\n";
}

/**
 * Helper function of issuing orders related to creating the advance
 * order for attacking neighboring enemies.
 */
void Player::advanceAttack() {
  auto toAttackMap = this->toAttack();
  std::cout << "These are the territories you can attack:\n";
  for (auto &t : toAttackMap) {
    std::cout << "[" << t.first << "]: " << t.second->Name << std::endl;
  }
  int indexToAttack{-1};
  bool validInput{false};
  while (!validInput) {
    std::cout << "Pick the index of the territory you wish to attack\n";
    std::cin >> indexToAttack;
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (indexToAttack < 0 ||
          toAttackMap.find(indexToAttack) == toAttackMap.end()) {
        std::cout << indexToAttack << " is not an acceptable input. Try again.";
      } else {
        validInput = true;
      }
    }
  }

  std::map<int, Territory *> territoriesThatCanAttack;

  auto adjacentOfToAttack = this->MainMap->ReturnListOfAdjacentCountriesByID(
      toAttackMap.at(indexToAttack)->TerritoryID);
  auto toDefendMap = this->toDefend();
  for (auto &t : adjacentOfToAttack) {
    if (toDefendMap.find(t->TerritoryID) != toDefendMap.end()) {
      territoriesThatCanAttack.insert(
          std::pair<int, Territory *>(t->TerritoryID, t));
    }
  }

  std::cout << "These are the territories you can attack with: \n";
  for (auto &t : territoriesThatCanAttack) {
    std::cout << "[" << t.first << "]: " << t.second->Name
              << " Armies: " << t.second->Armies << std::endl;
  }

  int indexToAttackWith{-1};
  validInput = false;
  while (!validInput) {
    std::cout << "Pick the index of the territory you wish to attack with\n";
    std::cin >> indexToAttackWith;
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (indexToAttackWith < 0 ||
          territoriesThatCanAttack.find(indexToAttackWith) ==
              territoriesThatCanAttack.end()) {
        std::cout << indexToAttackWith
                  << " is not an acceptable input. Try again.";
      } else {
        validInput = true;
      }
    }
  }

  // TODO finalize order
  auto *order = new Advance();
  this->ListOfOrders->addToList(order);
}

/**
 * Helper function of issuing orders related to creating the advance
 * order for transferring armies to neighbors.
 */
void Player::advanceTransfer() {
  auto toDefendMap = this->toDefend();
  std::cout << "These are the territories you defend:\n";
  for (auto &t : toDefendMap) {
    std::cout << "[" << t.first << "]: " << t.second->Name << std::endl;
  }

  int indexToTransferTo{-1};
  bool validInput{false};
  while (!validInput) {
    std::cout << "Pick the index of the territory you wish to transfer "
                 "armies to\n";
    std::cin >> indexToTransferTo;
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (indexToTransferTo < 0 ||
          toDefendMap.find(indexToTransferTo) == toDefendMap.end()) {
        std::cout << indexToTransferTo
                  << " is not an acceptable input. Try again.";
      } else {
        validInput = true;
      }
    }
  }

  std::map<int, Territory *> territoriesThatCanGiveArmies;

  auto adjacentOfTransfer = this->MainMap->ReturnListOfAdjacentCountriesByID(
      toDefendMap.at(indexToTransferTo)->TerritoryID);

  for (auto &t : adjacentOfTransfer) {
    if (toDefendMap.find(t->TerritoryID) != toDefendMap.end()) {
      territoriesThatCanGiveArmies.insert(
          std::pair<int, Territory *>(t->TerritoryID, t));
    }
  }

  std::cout << "These are the territories you can transfer armies from: \n";
  for (auto &t : territoriesThatCanGiveArmies) {
    std::cout << "[" << t.first << "]: " << t.second->Name
              << " Armies: " << t.second->Armies << std::endl;
  }
  int indexToTransferFrom{-1};
  validInput = false;
  while (!validInput) {
    std::cout << "Pick the index of the territory you wish to attack with\n";
    std::cin >> indexToTransferFrom;
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (indexToTransferFrom < 0 ||
          territoriesThatCanGiveArmies.find(indexToTransferFrom) ==
              territoriesThatCanGiveArmies.end()) {
        std::cout << indexToTransferFrom
                  << " is not an acceptable input. Try again.";
      } else {
        validInput = true;
      }
    }
  }

  // todo logic of reinforcing new territory
  auto *order = new Advance();
  this->ListOfOrders->addToList(order);
}

/**
 * Helper function for issuing orders that plays a card.
 */
void Player::playCard() {
  // Display the cards in a player's hand.
  std::cout << "These are the card in your hand:\n";
  std::cout << *this->HandOfCards << std::endl;
  std::cout << "Pick the card you wish to play starting from position, where 0 "
               "is leftmost card.\n";

  // Ask the player to chose a card to play.
  bool validInput{false};
  int input{-1};
  while (!validInput) {
    std::cin >> input;
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (input < 0 || input > this->HandOfCards->size()) {
        std::cout << "The input " << input << " is not valid. Try again.\n";
      } else {
        validInput = true;
      }
    }
  }
  auto cardToPlay = this->HandOfCards->returnByPos(input);
  // Method inside cards class creates the order and adds it to the list
  cardToPlay.Play(*this->HandOfCards, *this->ListOfOrders, *this->DeckOfCards);
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
