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
  virtual std::vector<Territory *> toAttack(Player &p) = 0;
  virtual void issueOrder(Player &p) = 0;
  virtual std::vector<Territory *> toDefend(Player &p) = 0;
  // Wrapper functions for orders from cards
  virtual void createBomb(Player &p) = 0;
  virtual void createAirlift(Player &p) = 0;
  virtual void createBlockade(Player &p) = 0;
  virtual void createNegotiate(Player &p) = 0;
  virtual void createReinforcement(Player &p) = 0;
  virtual std::string iAm() = 0;

  virtual ~PlayerStrategy() = default;
};

// ------------------------------------
// Concrete strategy classes
// ------------------------------------
class HumanStrategy : public PlayerStrategy {
 public:
  HumanStrategy();
  std::vector<Territory *> toAttack(Player &p) override;
  void issueOrder(Player &p) override;
  std::vector<Territory *> toDefend(Player &p) override;
  void createDeploy(Player &p);
  void advanceAttack(Player &p);
  void advanceTransfer(Player &p);
  void playCard(Player &p);
  void createBomb(Player &p) override;
  void createAirlift(Player &p) override;
  void createBlockade(Player &p) override;
  void createNegotiate(Player &p) override;
  void createReinforcement(Player &p) override;
  Territory *findById(std::vector<Territory *> &list, int id);
  int askUserForInt(std::string &message, int min, int max) const;
  void askForAdvanceOrder(Player &p);
  void displayVector(std::vector<Territory *> &list);
  std::string iAm() override;
};

class AggressivePlayerStrategy : public PlayerStrategy {
 public:
  AggressivePlayerStrategy();
  std::vector<Territory *> toAttack(Player &p) override;
  void issueOrder(Player &p) override;
  std::vector<Territory *> toDefend(Player &p) override;
  void createDeploy(Player &p);
  void advanceAttack(Player &p);
  void advanceTransfer(Player &p);
  void playCard(Player &p);
  void createBomb(Player &p) override;
  void createAirlift(Player &p) override;
  void createBlockade(Player &p) override;
  void createNegotiate(Player &p) override;
  void createReinforcement(Player &p) override;
  std::string iAm() override;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
 public:
  BenevolentPlayerStrategy();
  std::vector<Territory *> toAttack(Player &p) override;
  void issueOrder(Player &p) override;
  std::vector<Territory *> toDefend(Player &p) override;
  void createDeploy(Player &p);
  void advanceAttack(Player &p);
  void advanceTransfer(Player &p);
  void playCard(Player &p);
  void createBomb(Player &p) override;
  void createAirlift(Player &p) override;
  void createBlockade(Player &p) override;
  void createNegotiate(Player &p) override;
  void createReinforcement(Player &p) override;
  void displayVector(std::vector<Territory *> &list);
  Territory *weakestCountry(Player &p);
  Territory *strongestCountry(Player &p);
  std::string iAm() override;
};

// neutral player doesn't issue any order
class NeutralPlayerStrategy : public PlayerStrategy {
 public:
  NeutralPlayerStrategy();
  std::vector<Territory *> toAttack(Player &p) override;
  void issueOrder(Player &p) override;
  std::vector<Territory *> toDefend(Player &p) override;
  void createBomb(Player &p) override;
  void createAirlift(Player &p) override;
  void createBlockade(Player &p) override;
  void createNegotiate(Player &p) override;
  void createReinforcement(Player &p) override;
  std::string iAm() override;
};
