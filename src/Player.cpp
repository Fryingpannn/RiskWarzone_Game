#include "Player.h"

#include <algorithm>
#include <iostream>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"

/**
 * Empty constructor
 */
Player::Player()
    : Countries(new std::vector<Country>()),
      Cards(new Hand()),
      OrdersList(new Orders) {
  std::cout << "default constructor" << std::endl;
}

/**
 * Constructor
 */
Player::Player(std::vector<Country> countries, Hand cards, Orders orderList) {
  std::cout << "regular constructor" << std::endl;
  this->Countries = new std::vector<Country>(countries);
  this->Cards = new Hand(cards);
  this->OrdersList = new Orders(orderList);
}

/**
 * Copy Constructor for deep copy
 */
Player::Player(const Player &p) {
  std::cout << "Copy constructor called\n";
  this->Countries = new std::vector<Country>(*p.Countries);
  this->Cards = new Hand(*p.Cards);
  this->OrdersList = new Orders(*p.OrdersList);
}

/**
 * Overloaded assignment operator for deep copy
 */
Player &Player::operator=(const Player &p) {
  std::cout << "Assignment operator called\n";
  this->Countries = new std::vector<Country>(*p.Countries);
  this->Cards = new Hand(*p.Cards);
  this->OrdersList = new Orders(*p.OrdersList);
  return *this;
}

/**
 * Overloaded stream operator
 */
std::ostream &operator<<(std::ostream &out, const Player &p) {
  out << "  Countries: ";
  for (auto i = p.Countries->begin(); i != p.Countries->end(); ++i) {
    out << "temp " << ' ';
  }
  out << "\n";

  out << "  Cards: temp ";
  out << p.Cards;
  out << "\n";

  out << "  Orders: temp ";
  out << p.OrdersList;
  out << "\n";

  return out;
}

std::vector<Country> Player::toDefend() { return *Countries; }

int Player::toAttack() {

  //std::vector<int> v1 = Available Territories;
  //std::vector<int> v2 = *Countries; // territories player owns
  //std::vector<int> territoriesToAttack;
  // find difference between 2 collections
  //std::set_difference(
  //    v1.begin(), v1.end(), v2.begin(), v2.end(),
  //    std::inserter(territoriesToAttack, territoriesToAttack.begin()));

  return 0;
}

void Player::issueOrder() {
  // todo create object to add to list of orders
}

/**
 * Destructor
 */
Player::~Player() {
  Countries = NULL;
  Cards = NULL;
  delete Countries;
  delete Cards;
}
