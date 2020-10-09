#include "Player.h"

#include <ostream>
#include <vector>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"

/**
 * Default constructor initialize the members of Player to their default values.
 */
Player::Player() {
  this->Territories = std::vector<Territory *>{};
  this->HandOfCards = new Hand();
  this->ListOfOrders = new OrderList();

  std::cout << "default constructor" << std::endl;
}

/**
 * Constructor
 */
Player::Player(std::vector<Territory *> territories, Hand handOfCards,
               OrderList listOfOrders) {
  std::cout << "regular constructor" << std::endl;
  this->Territories = territories;
  this->HandOfCards = new Hand(handOfCards);
  this->ListOfOrders = new OrderList(listOfOrders);
}

/**
 * Copy Constructor for deep copy
 */
Player::Player(const Player &p) {
  std::cout << "Copy constructor called\n";

  this->HandOfCards = new Hand(*p.HandOfCards);
  this->ListOfOrders = new OrderList(*p.ListOfOrders);

  for (auto i = p.Territories.begin(); i != p.Territories.end(); ++i) {
    auto *country = new Territory(**i);
    this->Territories.push_back(country);
  }
}

/**
 * Overloaded assignment operator for deep copy
 */
Player &Player::operator=(const Player &p) {
  std::cout << "Assignment operator called\n";
  // this->Territories = new std::vector<Territory>(p.Territories);
  this->HandOfCards = new Hand(*p.HandOfCards);
  this->ListOfOrders = new OrderList(*p.ListOfOrders);

  for (auto i = p.Territories.begin(); i != p.Territories.end(); ++i) {
    auto *country = new Territory(**i);
    this->Territories.push_back(country);
  }
  return *this;
}

/**
 * Overloaded stream operator
 */
std::ostream &operator<<(std::ostream &out, const Player &p) {
  out << "\tCountries: { ";
  for (auto i = p.Territories.begin(); i != p.Territories.end(); ++i) {
    out << "{" << **i << "}  ";
  }
  out << "\n";

  out << "\tCards: " << *p.HandOfCards;
  out << "\n";

  out << "\tOrders: " << *p.ListOfOrders;
  out << "\n";

  return out;
}

std::vector<Territory *> Player::toDefend() { return Territories; }

std::vector<Territory *> Player::toAttack() {
  // TODO: replace with actual list of countries from map class
  std::vector<Territory *> listOfCountries{};

  // sort lists to please debugger
  std::sort(listOfCountries.begin(), listOfCountries.end());
  std::sort(Territories.begin(), Territories.end());

  // The difference between the two to be computed
  std::vector<Territory *> territoriesToAttack;

  // find difference between 2 collections
  std::set_difference(
      listOfCountries.begin(), listOfCountries.end(), Territories.begin(),
      Territories.end(),
      std::inserter(territoriesToAttack, territoriesToAttack.begin()));

  return territoriesToAttack;
}

void Player::issueOrder() {
  auto *order = new Advance();
  this->ListOfOrders->addToList(order);
}

/**
 * Destructor
 */
Player::~Player() {
  for (auto &i : Territories) {
    delete i;
    i = nullptr;
  }
  //  Territories.clear();
  delete HandOfCards;
  delete ListOfOrders;
  this->HandOfCards = nullptr;
  this->ListOfOrders = nullptr;
}
