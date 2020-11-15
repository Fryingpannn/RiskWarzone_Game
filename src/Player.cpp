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

  this->PID = pid;  //<=========== HERE
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

void Player::bindGameElements(std::vector<Player *> &Players, Map *mapIn,
                              Deck *deckIn) {
  this->MainMap = mapIn;
  this->DeckOfCards = deckIn;
}

void Player::initIssueOrder() {
  this->AdvanceOrderDone = false;
  this->CardPlayed = false;
  this->ReinforcementsDeployed = 0;
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
  if (this->ReinforcementPool-this->ReinforcementsDeployed > 0) {
    std::cout << "Reinforcement\n";
    createDeploy();

    // Perform an advance order that either attacks or transfers
  } else if (!AdvanceOrderDone) {
    std::cout << "Advance: Attack/Transfer\n";

    bool validInput{false};
    std::string input{"x"};

    while (!validInput) {
      std::cout << "Pick [t] to transfer armies or [a] to attack: ";
      std::cin >> input;
      std::cout << "\n";
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
void Player::createDeploy() {
  auto toDefendMap = this->toDefend();
  // Print territories that can be defended
  for (auto &t : toDefendMap) {
    std::cout << "[" << t.first << "]: " << t.second->Name
              << " - Armies: " << t.second->Armies << std::endl;
  }

  // Ask player to chose where to deploy armies
  int indexToReinforce{-1};
  bool validInput{false};
  while (!validInput) {
    std::cout << "Pick the index of the territory you wish to reinforce: ";
    std::cin >> indexToReinforce;
    std::cout << "\n";
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
    std::cout << "Pick the number of armies to reinforce "
              << toDefendMap.at(indexToReinforce)->Name << " with.\n"
              << "You have " << ReinforcementPool-ReinforcementsDeployed
              << " armies left to deploy.\nNumber of armies: ";
    std::cin >> armies;
    std::cout << "\n";
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (armies < 1 || armies > ReinforcementPool - ReinforcementsDeployed) {
        std::cout << "The number of armies (" << armies
                  << ") is not a valid input. \n";
      } else {
        validInput = true;
      }
    }
  }

  // Perform the deploy order
  auto *order =
      new Deploy(this->PID, armies, toDefendMap.at(indexToReinforce), this);
  this->ListOfOrders->addToList(order);
  this->ReinforcementsDeployed += armies;
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
    std::cout << "Pick the index of the territory you wish to attack:";
    std::cin >> indexToAttack;
    std::cout << "\n";

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
    std::cout << "Pick the index of the territory you wish to attack with: ";
    std::cin >> indexToAttackWith;
    std::cout << "\n";

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

  int nbArmies{-1};
  validInput = false;
  while (!validInput) {
    std::cout
        << "How many armies do you wish to attack with? You can choose up to "
        << territoriesThatCanAttack.at(indexToAttackWith)->Armies
        << "\nNumber of armies: ";
    std::cin >> nbArmies;
    std::cout << "\n";

    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (nbArmies < 0 ||
          nbArmies > territoriesThatCanAttack.at(indexToAttackWith)->Armies) {
        std::cout << nbArmies << " is not an acceptable input. Try again.";
      } else {
        validInput = true;
      }
    }
  }

  auto *order = new Advance(
      this->PID, nbArmies, territoriesThatCanAttack.at(indexToAttackWith),
      toAttackMap.at(indexToAttack), this->MainMap, this, this->DeckOfCards);
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
                 "armies to: ";
    std::cin >> indexToTransferTo;
    std::cout << "\n";

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
    std::cout << "Pick the index of the territory you wish to attack with: ";
    std::cin >> indexToTransferFrom;
    std::cout << "\n";

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

  int nbArmies{-1};
  validInput = false;
  while (!validInput) {
    std::cout
        << "How many armies do you wish to transfer? You can choose up to "
        << territoriesThatCanGiveArmies.at(indexToTransferFrom)->Armies
        << "\nNumber of armies: ";
    std::cin >> nbArmies;
    std::cout << "\n";

    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (nbArmies < 0 ||
          nbArmies >
              territoriesThatCanGiveArmies.at(indexToTransferFrom)->Armies) {
        std::cout << nbArmies << " is not an acceptable input. Try again.";
      } else {
        validInput = true;
      }
    }
  }

  auto *order = new Advance(
      this->PID, nbArmies, territoriesThatCanGiveArmies.at(indexToTransferFrom),
      toDefendMap.at(indexToTransferTo), this->MainMap, this,
      this->DeckOfCards);
  this->ListOfOrders->addToList(order);
}

/**
 * Helper function for issuing orders that plays a card.
 */
void Player::playCard() {
  if (this->HandOfCards->size() == 0) {
    std::cout << "You have no cards in your hand.\n";
  } else {
    // Display the cards in a player's hand.
    std::cout << "These are the card in your hand:\n";
    std::cout << *this->HandOfCards << std::endl;

    // Ask the player to chose a card to play.
    bool validInput{false};
    int input{-1};
    while (!validInput) {
      std::cout
          << "Pick the card you wish to play starting from position, where 0 "
             "is leftmost card.\nCard picked: ";
      std::cin >> input;
      std::cout << "\n";

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
    cardToPlay.Play(*this, *this->HandOfCards, *this->DeckOfCards);
  }
}

void Player::createBomb() {
  // TODO show list of territories that can be bombed

  bool validInput{false};
  int input{-1};
  while (!validInput) {
    std::cout << "Pick a territory ID to bomb.\nTerritory ID: ";
    std::cin >> input;
    std::cout << "\n";

    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (input < 0 || input > this->MainMap->NumOfCountries()) {
        std::cout << "The input " << input << " is not valid. Try again.\n";
      } else {
        validInput = true;
      }
    }
  }

  for (auto &t : this->MainMap->ReturnListOfCountries()) {
    if (t->TerritoryID == input) {
      auto *order = new Bomb(this->PID, t, this);
      this->ListOfOrders->addToList(order);
      break;
    }
  }
}
void Player::createAirlift() {
  auto toDefendMap = this->toDefend();
  std::cout << "These are the territories you defend:\n";
  for (auto &t : toDefendMap) {
    std::cout << "[" << t.first << "]: " << t.second->Name << std::endl;
  }

  bool validInput{false};
  int inputAirliftTo{-1};
  while (!validInput) {
    std::cout << "Pick a territory ID to airlift armies to.\nTerritory ID: ";
    std::cin >> inputAirliftTo;
    std::cout << "\n";

    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (inputAirliftTo < 0 ||
          inputAirliftTo > this->MainMap->NumOfCountries()) {
        std::cout << "The input " << inputAirliftTo
                  << " is not valid. Try again.\n";
      } else {
        validInput = true;
      }
    }
  }

  validInput = false;
  int inputAirliftFrom{-1};
  while (!validInput) {
    std::cout << "Pick a territory ID to airlift armies from.\nTerritory ID: ";
    std::cin >> inputAirliftFrom;
    std::cout << "\n";

    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (inputAirliftFrom < 0 ||
          inputAirliftFrom > this->MainMap->NumOfCountries()) {
        std::cout << "The input " << inputAirliftFrom
                  << " is not valid. Try again.\n";
      } else {
        validInput = true;
      }
    }
  }

  int nbArmies{-1};
  validInput = false;
  while (!validInput) {
    std::cout
        << "How many armies do you wish to transfer? You can choose up to "
        << toDefendMap.at(inputAirliftFrom)->Armies << "\nNumber of armies: ";
    std::cin >> nbArmies;
    std::cout << "\n";

    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (nbArmies < 0 || nbArmies > toDefendMap.at(inputAirliftFrom)->Armies) {
        std::cout << nbArmies << " is not an acceptable input. Try again.";
      } else {
        validInput = true;
      }
    }
  }

  auto *order =
      new Airlift(this->PID, nbArmies, toDefendMap.at(inputAirliftFrom),
                  toDefendMap.at(inputAirliftTo), this, this->DeckOfCards);
  this->ListOfOrders->addToList(order);
}
void Player::createBlockade() {
  auto toDefendMap = this->toDefend();
  std::cout << "These are the territories you defend:\n";
  for (auto &t : toDefendMap) {
    std::cout << "[" << t.first << "]: " << t.second->Name << std::endl;
  }

  bool validInput{false};
  int input{-1};
  while (!validInput) {
    std::cout << "Pick a territory ID to blockade.\nTerritory ID: ";
    std::cin >> input;
    std::cout << "\n";

    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (input < 0 || input > this->MainMap->NumOfCountries()) {
        std::cout << "The input " << input << " is not valid. Try again.\n";
      } else {
        validInput = true;
      }
    }
  }

  auto *order = new Blockade(this->PID, toDefendMap.at(input));
  this->ListOfOrders->addToList(order);
}
void Player::createNegotiate() {
  std::cout << "Your opponents are: \n";
  for (auto &p : this->ListOfPlayers) {
    if (p->PID != this->PID) {
      std::cout << "\t" << p->PID << "\n";
    }
  }

  bool validInput{false};
  std::string input{" "};
  Order *order = nullptr;
  while (!validInput) {
    std::cout << "Pick an enemy to negotiate with.\nEnemy ID: ";
    std::cin >> input;
    std::cout << "\n";

    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter a STRING value\n";
    } else {
      for (auto &p : this->ListOfPlayers) {
        if (p->PID != this->PID && p->PID == input) {
          order = new Negotiate(this, p);
        }
      }
      if (order == nullptr) {
        std::cout << "That is not a valid enemy ID.\n";
      } else {
        validInput = true;
      }
    }
  }
  this->ListOfOrders->addToList(order);
}

void Player::createReinforcement() {

    this->ListOfOrders->addToList(new Reinforcement(this));

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
  delete this->MainMap;
  this->MainMap = nullptr;
  delete this->DeckOfCards;
  this->DeckOfCards = nullptr;
}
