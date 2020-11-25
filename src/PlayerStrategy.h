#pragma once
#include <ostream>
#include <unordered_set>
#include <vector>

#include "Cards.h"
#include "GameObservers.hpp"
#include "Map.h"
#include "Orders.h"
#include "Player.h"

struct Territory;
class Deck;
class Map;
class Player;

// ------------------------------------
// Base strategy class
// ------------------------------------
class PlayerStrategy {
 public:
  virtual std::vector<Territory *> toAttack(Player &p)=0;
  virtual void issueOrder(Player &p)=0;
  virtual std::vector<Territory *> toDefend(Player &p)=0;
  // Wrapper functions for orders from cards
  virtual void createBomb(Player &p)=0;
  virtual void createAirlift(Player &p)=0;
  virtual void createBlockade(Player &p)=0;
  virtual void createNegotiate(Player &p)=0;
  virtual void createReinforcement(Player &p)=0;
};

// ------------------------------------
// Concrete strategy classes
// ------------------------------------
class HumanStrategy : public PlayerStrategy {
 public:
  std::vector<Territory *> toAttack(Player &p);
  void issueOrder(Player &p);
  std::vector<Territory *> toDefend(Player &p);
  void createDeploy(Player &p);
  void advanceAttack(Player &p);
  void advanceTransfer(Player &p);
  void playCard(Player &p);
  void createBomb(Player &p);
  void createAirlift(Player &p);
  void createBlockade(Player &p);
  void createNegotiate(Player &p);
  void createReinforcement(Player &p);
};

class AggresivePlayerStrategy : public PlayerStrategy {
 public:
  std::vector<Territory *> toAttack(Player &p);
  void issueOrder(Player &p);
  std::vector<Territory *> toDefend(Player &p);
  void createDeploy(Player &p);
  void advanceAttack(Player &p);
  void advanceTransfer(Player &p);
  void playCard(Player &p);
  void createBomb(Player &p);
  void createAirlift(Player &p);
  void createBlockade(Player &p);
  void createNegotiate(Player &p);
  void createReinforcement(Player &p);
};

class BenevolentPlayerStrategy : public PlayerStrategy {
 public:
  std::vector<Territory *> toAttack(Player &p);
  void issueOrder(Player &p);
  std::vector<Territory *> toDefend(Player &p);
  void createDeploy(Player &p);
  void advanceAttack(Player &p);
  void advanceTransfer(Player &p);
  void playCard(Player &p);
  void createBomb(Player &p);
  void createAirlift(Player &p);
  void createBlockade(Player &p);
  void createNegotiate(Player &p);
  void createReinforcement(Player &p);
};

// neutral player doesn't issue any order
class NeutralPlayerStrategy : public PlayerStrategy {
 public:
  void issueOrder(Player &p);
};
