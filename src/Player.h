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
#include <unordered_set>
#include <vector>

#include "Cards.h"
#include "GameObservers.hpp"
#include "Map.h"
#include "Orders.h"
#include "PlayerStrategy.h"

struct Territory;
class Map;
class Deck;
class PlayerStrategy;

/**
 * A class for the object Player which manages territories, cards and orders
 * owned by a player.
 */
class Player : public Subject {
 public:
  // -----------------------------------
  // Members
  // -----------------------------------
  std::vector<Territory *> Territories;
  Hand *HandOfCards;
  OrderList *ListOfOrders;
  std::string PID;
  int ReinforcementPool = 0;
  bool AdvanceOrderDone = true;
  bool CardPlayed = true;
  std::vector<Player *> ListOfPlayers;
  Map *MainMap;
  Deck *DeckOfCards;
  int ReinforcementsDeployed;
  bool cardNotGiven = true;
  // set of players with whom playerID cannot attack or be attacked by
  std::unordered_set<std::string> set;
  // Strategy pattern
  PlayerStrategy *Strategy;

  // -----------------------------------
  // Constructors/Destructors
  // -----------------------------------
  Player();
  Player(std::vector<Territory *> territories, Hand hand, OrderList orderList,
         std::string pID);
  Player(const Player &p);
  ~Player();

  // -----------------------------------
  // Operators
  // -----------------------------------
  Player &operator=(const Player &p);
  friend std::ostream &operator<<(std::ostream &out, const Player &p);

  // -----------------------------------
  // Functions
  // -----------------------------------
  void bindGameElements(std::vector<Player *> &inPlayers, Map *mapIn,
                        Deck *deckIn);
  void initIssueOrder();
  void removeTerritory(Territory &t);

  std::vector<Territory *> toDefend();
  std::vector<Territory *> toAttack();
  void issueOrder();

  // Strategy pattern functions
  void setStrategy(PlayerStrategy *strategy);
};
