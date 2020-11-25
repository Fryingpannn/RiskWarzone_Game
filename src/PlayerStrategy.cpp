#include "PlayerStrategy.h"
#include <map>
#include <ctime>


std::vector<Territory *> HumanStrategy::toAttack(Player &p) {
  // Using a map to ensure unique values of territories
  std::map<int, Territory *> toAttackMap;
  auto ownedTerritories = p.toDefend();

  for (auto &elem : ownedTerritories) {
    // Get list of adjacent territories of a single territory
    // that the player owns
    auto computeAdjacentResult =
        p.MainMap->ReturnListOfAdjacentCountriesByID(elem->TerritoryID);

    // Keep only territories that a player does not already own.
    for (auto &t : computeAdjacentResult) {
      auto it = std::find(ownedTerritories.begin(), ownedTerritories.end(), t);
      if (it == ownedTerritories.end()) {
        toAttackMap.insert(std::pair<int, Territory *>(t->TerritoryID, t));
      }
    }
  }

  // Convert map to a vector
  std::vector<Territory *> toAttack;
  for (auto &t : toAttackMap) {
    toAttack.push_back(t.second);
  }
  std::cout << "\tCan attack:\n";
  for (auto &t : toAttack) {
    std::cout << "\t\t" << t->Name << " armies: " << t->Armies << "\n";
  }
  return toAttack;
}

std::vector<Territory *> HumanStrategy::toDefend(Player &p) {
  std::cout << "\tDefending\n";

  for (auto &t : p.Territories) {
    std::cout << "\t\t" << t->Name << " armies: " << t->Armies << "\n";
  }

  return p.Territories;
}

void HumanStrategy::issueOrder(Player &p) {
  // Deploy armies until nothing left in pool
  if (p.ReinforcementPool - p.ReinforcementsDeployed > 0) {
    std::cout << "\t" << p.PID << " has "
              << p.ReinforcementPool - p.ReinforcementsDeployed
              << " armies left to deploy.\n";
    this->createDeploy(p);

    // Perform an advance order that either attacks or transfers
  } else if (!p.AdvanceOrderDone) {
    std::cout << "\t" << p.PID << " has no more armies left to deploy: "
              << p.ReinforcementPool - p.ReinforcementsDeployed << " armies\n";
    srand(time(NULL));
    std::cout << "\tIssuing advance order...\n";
    // Make players more likely to attack than transfer to end game faster
    if ((rand() % 100) > 70) {
      this->advanceTransfer(p);
    } else {
      this->advanceAttack(p);
    }
    p.AdvanceOrderDone = true;
    // Play a card
  } else if (!p.CardPlayed) {
    std::cout << "\t" << p.PID << " already did deploy/advance order\n"
              << "\tChoosing card\n";
    this->playCard(p);
    p.CardPlayed = true;
  }
  // Else no orders left
}

void HumanStrategy::createDeploy(Player &p) {
  auto ownedTerritories = p.toDefend();

  // Chooses a random place to deploy a random amount of armies
  srand(time(NULL));
  auto *territoryToDeploy =
      ownedTerritories.at(rand() % (ownedTerritories.size()));

  int armies = 0;
  if (p.ReinforcementPool - p.ReinforcementsDeployed > 0) {
    armies =
        1 + rand() % (p.ReinforcementPool - p.ReinforcementsDeployed);
  }

  // Perform the deploy order
  auto *order = new Deploy(p.PID, armies, territoryToDeploy, &p);
  std::cout << "\t" << p.PID << " deploy " << armies << " from ["
            << p.ReinforcementPool - p.ReinforcementsDeployed
            << "] reinforcement pool "
            << "to " << territoryToDeploy->Name << "["
            << territoryToDeploy->Armies << "]\n";
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
  p.ReinforcementsDeployed += armies;
};

void HumanStrategy::advanceAttack(Player &p) {
  auto toAttackTerritories = p.toAttack();
  auto ownedTerritories = p.toDefend();

  srand(time(NULL));

  // Chose a territory as a source of attack
  Territory *src = ownedTerritories.at(rand() % (ownedTerritories.size()));

  // Chose any target from to attack pool even if not a neighbor, orders will
  // validate
  auto *target = toAttackTerritories.at(rand() % (toAttackTerritories.size()));

  // Attack with all armies in that territory to speed up game play
  auto *order = new Advance(p.PID, src->Armies, src, target, p.MainMap,
                            &p, p.DeckOfCards);

  std::cout << "\t" << p.PID << " attacks " << target->Name << " - "
            << target->Armies << " owned by " << target->OwnedBy << " with "
            << src->Name << " - " << src->Armies << " armies " << '\n';

  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::advanceTransfer(Player &p) {
  auto ownedTerritories = p.toDefend();

  srand(time(NULL));
  auto *src = ownedTerritories.at(rand() % (ownedTerritories.size()));
  auto *target = ownedTerritories.at(rand() % (ownedTerritories.size()));
  int armies = 0;
  if (src->Armies > 0) {
    armies = 1 + rand() % src->Armies;
  }

  auto *order = new Advance(p.PID, armies, src, target, p.MainMap, &p,
                            p.DeckOfCards);

  std::cout << "\t" << p.PID << " transfers " << armies << " armies to "
            << target->Name << " - " << target->Armies << " from " << src->Name
            << " - " << src->Armies << " total armies " << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::playCard(Player &p) {
  srand(time(NULL));

  if (p.HandOfCards->size() == 0) {
    std::cout << "\tYou have no cards in your hand.\n";
  } else {
    // Display the cards in a player's hand.
    std::cout << "These are the card in your hand:\n";
    std::cout << *p.HandOfCards << std::endl;

    auto cardToPlay =
        p.HandOfCards->returnByPos(rand() % (p.HandOfCards->size()));
    // Method inside cards class calls the correct player creation order
    // function
    std::cout << "Playing card: " << cardToPlay << "\n";
    cardToPlay.Play(p, *p.HandOfCards, *p.DeckOfCards);
  }
};

void HumanStrategy::createBomb(Player &p) {
  srand(time(NULL));

  const auto pos = rand() % p.MainMap->NumOfCountries();
  auto *target = p.MainMap->ReturnListOfCountries().at(pos);

  auto *order = new Bomb(p.PID, target, &p);

  std::cout << "\t" << p.PID << " bombs " << target->Name << " - "
            << target->Armies << " owned by " << target->OwnedBy << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::createAirlift(Player &p) {
  srand(time(NULL));

  auto ownedTerritories = p.toDefend();
  auto *src = ownedTerritories.at(rand() % (ownedTerritories.size()));

  const auto pos = rand() % p.MainMap->NumOfCountries();
  auto *target = p.MainMap->ReturnListOfCountries().at(pos);

  int armies = 0;
  if (src->Armies > 0) {
    armies = 1 + rand() % src->Armies;
  }

  auto *order =
      new Airlift(p.PID, armies, src, target, &p, p.DeckOfCards);
  std::cout << "\t" << p.PID << " airlifts " << armies << " armies to "
            << target->Name << " - " << target->Armies << " owned by "
            << target->OwnedBy << " from " << src->Name << " - " << src->Armies
            << " armies " << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::createBlockade(Player &p) {
  srand(time(NULL));

  auto ownedTerritories = p.toDefend();

  auto *src = ownedTerritories.at(rand() % (ownedTerritories.size()));

  auto *order = new Blockade(p.PID, src);
  std::cout << "\t" << p.PID << " blockades " << src->Name << " - "
            << src->Armies << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::createNegotiate(Player &p) {
  srand(time(NULL));

  Player *enemy = p.ListOfPlayers.at(rand() % (p.ListOfPlayers.size()));
  auto *order = new Negotiate(&p, enemy);
  std::cout << "\t" << p.PID << " negotiates with " << enemy->PID << " - "
            << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::createReinforcement(Player &p) {
  std::cout << "\t" << p.PID << " reinforces his pool\n";
  p.ListOfOrders->addToList(
      static_cast<std::shared_ptr<Order>>(new Reinforcement(&p)));
};

std::vector<Territory *> AggresivePlayerStrategy::toAttack(Player &p) {
  return std::vector<Territory *>{};
}
std::vector<Territory *> AggresivePlayerStrategy::toDefend(Player &p) {
  return std::vector<Territory *>{};
}
void AggresivePlayerStrategy::issueOrder(Player &p) {}
void AggresivePlayerStrategy::createDeploy(Player &p) {}
void AggresivePlayerStrategy::advanceAttack(Player &p) {}
void AggresivePlayerStrategy::advanceTransfer(Player &p) {}
void AggresivePlayerStrategy::playCard(Player &p) {}
void AggresivePlayerStrategy::createBomb(Player &p) {}
void AggresivePlayerStrategy::createAirlift(Player &p) {}
void AggresivePlayerStrategy::createBlockade(Player &p) {}
void AggresivePlayerStrategy::createNegotiate(Player &p) {}
void AggresivePlayerStrategy::createReinforcement(Player &p){}

std::vector<Territory *> BenevolentPlayerStrategy::toAttack(Player &p) {
  return std::vector<Territory *>{};
}
std::vector<Territory *> BenevolentPlayerStrategy::toDefend(Player &p) {
  return std::vector<Territory *>{};
}
void BenevolentPlayerStrategy::issueOrder(Player &p) {}
void BenevolentPlayerStrategy::createDeploy(Player &p){}
void BenevolentPlayerStrategy::advanceAttack(Player &p) {}
void BenevolentPlayerStrategy::advanceTransfer(Player &p) {}
void BenevolentPlayerStrategy::playCard(Player &p) {}
void BenevolentPlayerStrategy::createBomb(Player &p){}
void BenevolentPlayerStrategy::createAirlift(Player &p){}
void BenevolentPlayerStrategy::createBlockade(Player &p){}
void BenevolentPlayerStrategy::createNegotiate(Player &p){}
void BenevolentPlayerStrategy::createReinforcement(Player &p){}

/*no orders issued for neutral player*/
void NeutralPlayerStrategy::issueOrder(Player& p) { std::cout << "[Neutral Player] No orders issued." << std::endl; }

