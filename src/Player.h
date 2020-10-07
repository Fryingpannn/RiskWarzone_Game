#pragma once
#include <ostream>
#include <vector>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"

class Player {
 public:
  std::vector<Country> *Countries;
  Hand *Cards;
  Orders *OrdersList;

  Player();
  Player(std::vector<Country> countries, Hand cards, Orders orderList);
  Player(const Player &copy);
  Player &operator=(const Player &p);
  std::vector<Country> toDefend();
  int toAttack();
  void issueOrder();
  friend std::ostream &operator<<(std::ostream &out, const Player &p);
  ~Player();
};
