/////////////////////////////////////////////
// Filename:        Player.h
//
// Description:     Header file for Implementation of Part 3 - Player
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

#pragma once
#include <ostream>
#include <vector>

#include "Cards.h"
#include "Orders.h"
#ifndef H_MAP
#define H_MAP
class Territory;
#endif
/**
 * A class for the object Player which managers territories, cards and orders
 * owned by a player.
 */
class Player {
 public:
  std::vector<Territory *> Territories;
  Hand *HandOfCards;
  OrderList *ListOfOrders;
  std::string PID;

  Player();
  Player(std::vector<Territory *> territories, Hand hand, OrderList orderList,
         std::string pID);
  Player(const Player &p);
  Player &operator=(const Player &p);
  std::vector<Territory *> toDefend();
  std::vector<Territory *> toAttack(std::vector<Territory *> listOfCountries);
  void issueOrder();
  friend std::ostream &operator<<(std::ostream &out, const Player &p);
  ~Player();
};
