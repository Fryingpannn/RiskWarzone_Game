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
#include <unordered_set>

#include "Cards.h"
#include "Orders.h"
#include "Map.h"

#ifndef H_MAP
#define H_MAP
struct Territory;
class Map;
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
  int ReinforcementPool = 0;
  bool AdvanceOrderDone = true;
  bool CardPlayed = true;
  //set of players with whom playerID cannot attack or be attacked by this turn; used by Negotiation
  std::unordered_set<std::string>* set;

  Player();
  Player(std::vector<Territory *> territories, Hand hand, OrderList orderList,
         std::string pID);
  Player(const Player &p);
  Player &operator=(const Player &p);
  std::vector<Territory *> toDefend();
  std::vector<Territory *> toAttack(Map &map);
  void issueOrder(Map &map, Deck &deckOfCards);
  friend std::ostream &operator<<(std::ostream &out, const Player &p);
  ~Player();
};
