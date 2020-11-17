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

#include "GameObservers.hpp"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

struct Territory;
class Map;
class Deck;

/**
 * A class for the object Player which manages territories, cards and orders
 * owned by a player.
 */
class Player : public Subject {
 public:
  std::vector<Territory *> Territories;
  Hand *HandOfCards;
  OrderList *ListOfOrders;
  std::string PID;
  int ReinforcementPool = 0;
  bool AdvanceOrderDone = true;
  bool CardPlayed = true;
  // set of players with whom playerID cannot attack or be attacked by this
  // turn; this set is used by Negotiation order's execute function.
  std::unordered_set<std::string> set;
  // a player can only receive one new card each turn. reset this value to true
  // at the end of every turn. this is used by Advance order's execute function.
  bool cardNotGiven = true;

  // Game knowledge members
  std::vector<Player *> ListOfPlayers;
  Map *MainMap;
  Deck *DeckOfCards;
  int ReinforcementsDeployed;

  Player();
  Player(std::vector<Territory *> territories, Hand hand, OrderList orderList,
         std::string pID);
  Player(const Player &p);
  Player &operator=(const Player &p);

  // Helper function for game engine
  void bindGameElements(std::vector<Player *> &inPlayers, Map *mapIn,
                        Deck *deckIn);
  void initIssueOrder();
  void removeTerritory(Territory &t);

  std::vector<Territory *> toDefend();
  std::vector<Territory *> toAttack();
  void issueOrder();

  // Helper functions of issue order
  void createDeploy();
  void advanceAttack();
  void advanceTransfer();
  void playCard();

  // Wrapper functions for orders from cards
  void createBomb();
  void createAirlift();
  void createBlockade();
  void createNegotiate();
  void createReinforcement();

  friend std::ostream &operator<<(std::ostream &out, const Player &p);
  ~Player();
};
