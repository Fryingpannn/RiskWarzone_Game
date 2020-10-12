/////////////////////////////////////////////
// Filename:        Player.h
//
// Description:     Header file for Implementation of Part 3 - Player
//
// Author:          Sandra Buchen
//
// Group:           Sandra Buchen
//                  Le Cherng Lee
//                  Zahra Nikbakht
//                  Matthew Pan
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#pragma once
#include <ostream>
#include <vector>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"
/**
 * A class for the object Player which managers territories, cards and orders
 * owned by a player.
 */
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




