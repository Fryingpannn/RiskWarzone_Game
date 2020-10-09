#pragma once
#include <ostream>
#include <vector>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"

class Player {
 public:
  std::vector<Territory *> Territories;
  Hand *HandOfCards;
  OrderList *ListOfOrders;

  Player();
  Player(std::vector<Territory *> territories, Hand hand,
         OrderList orderList);
  Player(const Player &p);
  Player &operator=(const Player &p);
  std::vector<Territory *> toDefend();
  std::vector<Territory *> toAttack();
  void issueOrder();
  friend std::ostream &operator<<(std::ostream &out, const Player &p);
  ~Player();
};
