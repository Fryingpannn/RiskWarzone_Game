#include "PlayerStrategy.h"

#include <ctime>
#include <map>

//-----------------------------------------------------------------
// HUMAN PLAYER
//-----------------------------------------------------------------
HumanStrategy::HumanStrategy() {
  std::cout << "\t[UPDATE] - I am a HUMAN PLAYER\n";
}

std::string HumanStrategy::iAm() { return "Human Player"; }

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
  return toAttack;
}

std::vector<Territory *> HumanStrategy::toDefend(Player &p) {
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
    std::cout << "\tIssuing Advance: Attack OR Transfer order...\n";
    this->askForAdvanceOrder(p);
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
  std::cout << "Your territories are: \n";
  this->displayVector(ownedTerritories);

  std::string message_index =
      "Pick the index of the territory you wish to reinforce: ";
  const int territoryID =
      askUserForInt(message_index, 0, p.MainMap->NumOfCountries());
  auto *territoryToDeploy = findById(ownedTerritories, territoryID);

  std::string message_armies =
      "Chose a number of armies to reinforce " + territoryToDeploy->Name +
      " with.\n You have " +
      std::to_string(p.ReinforcementPool - p.ReinforcementsDeployed) +
      " reinforcements left:";
  const int armies = askUserForInt(
      message_armies, 1, p.ReinforcementPool - p.ReinforcementsDeployed);

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
  std::cout << "You can attack with these territories: \n";
  this->displayVector(ownedTerritories);

  std::cout << "You can attack these territories: \n";
  this->displayVector(toAttackTerritories);

  std::string msg_src =
      "From your defense pool, pick a territory to attack with: ";
  const int src_id =
      this->askUserForInt(msg_src, 0, p.MainMap->NumOfCountries());
  auto *src = this->findById(ownedTerritories, src_id);

  auto adjacentTerritories =
      p.MainMap->ReturnListOfAdjacentCountriesByIDAndNotPlayer(src->TerritoryID,
                                                               p.PID);

  std::cout << "You can attack these neighbors: \n";
  this->displayVector(adjacentTerritories);

  std::string msg_target =
      "From your attack pool, pick a territory to attack: ";
  const int target_id =
      this->askUserForInt(msg_target, 0, p.MainMap->NumOfCountries());
  auto *target = this->findById(adjacentTerritories, target_id);

  int armies = 0;
  if (src->Armies != 0) {
    std::string msg_armies =
        "How many armies do you want to attack with out of " +
        std::to_string(src->Armies) + "? ";
    armies = askUserForInt(msg_armies, 1, src->Armies);
  } else {
    std::cout << "\tNo armies on that territory!";
  }

  auto *order =
      new Advance(p.PID, armies, src, target, p.MainMap, &p, p.DeckOfCards);

  std::cout << "\t" << p.PID << " attacks " << target->Name << " - "
            << target->Armies << " owned by " << target->OwnedBy << " with "
            << src->Name << " - " << src->Armies << " armies " << '\n';

  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::advanceTransfer(Player &p) {
  auto ownedTerritories = p.toDefend();
  std::cout << "You can transfer armies between these territories: \n";
  this->displayVector(ownedTerritories);

  std::string msg_src =
      "From your defense pool, pick a territory to transfer armies from: ";
  const int src_id =
      this->askUserForInt(msg_src, 0, p.MainMap->NumOfCountries());
  auto *src = this->findById(ownedTerritories, src_id);

  auto adjacentTerritories =
      p.MainMap->ReturnListOfAdjacentCountriesByID(src->TerritoryID);

  std::cout << "You can transfer armies to it's neighbors: \n";
  this->displayVector(adjacentTerritories);

  std::string msg_target =
      "From your adjacent territories, pick a territory to transfer to: ";
  const int target_id =
      this->askUserForInt(msg_target, 0, p.MainMap->NumOfCountries());
  auto *target = this->findById(adjacentTerritories, target_id);

  int armies = 0;
  if (src->Armies != 0) {
    std::string msg_armies =
        "How many armies do you want to transfer with out of " +
        std::to_string(src->Armies) + "? ";
    armies = askUserForInt(msg_armies, 1, src->Armies);
  } else {
    std::cout << "\tNo armies on that territory!";
  }

  auto *order =
      new Advance(p.PID, armies, src, target, p.MainMap, &p, p.DeckOfCards);

  std::cout << "\t" << p.PID << " transfers " << armies << " armies to "
            << target->Name << " - " << target->Armies << " from " << src->Name
            << " - " << src->Armies << " total armies " << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::playCard(Player &p) {
  if (p.HandOfCards->size() == 0) {
    std::cout << "\tYou have no cards in your hand.\n";
  } else {
    // Display the cards in a player's hand.
    std::cout << "These are the card in your hand:\n";
    std::cout << *p.HandOfCards << std::endl;
    std::string msg = "Pick the card you wish to play: ";
    const int card_index = askUserForInt(msg, 0, p.HandOfCards->size());
    auto cardToPlay = p.HandOfCards->returnByPos(card_index);
    // Method inside cards class calls the correct player creation order
    // function
    std::cout << "Playing card: " << cardToPlay << "\n";
    cardToPlay.Play(p, *p.HandOfCards, *p.DeckOfCards);
  }
};

void HumanStrategy::createBomb(Player &p) {
  auto allTerritories = p.MainMap->ReturnListOfCountries();
  std::cout << "These are all the territories in the game: \n";
  this->displayVector(allTerritories);

  std::string msg = "Choose any territories that you don't own to bomb: ";
  const auto target_index = askUserForInt(msg, 0, p.MainMap->NumOfCountries());
  auto *target = findById(allTerritories, target_index);

  auto *order = new Bomb(p.PID, target, &p);

  std::cout << "\t" << p.PID << " bombs " << target->Name << " - "
            << target->Armies << " owned by " << target->OwnedBy << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::createAirlift(Player &p) {
  auto ownedTerritories = p.toDefend();
  std::cout << "These are the territories you can airlift from:\n";
  displayVector(ownedTerritories);

  std::string msg_src = "Choose a source territory to airlift armies from: ";
  const int src_index = askUserForInt(msg_src, 0, p.MainMap->NumOfCountries());
  auto *src = findById(ownedTerritories, src_index);

  auto allTerritories = p.MainMap->ReturnListOfCountries();
  std::cout << "These are all the territories in the game: \n";
  this->displayVector(allTerritories);

  std::string msg_target = "Choose a target territory to airlift to: ";
  const int target_id =
      this->askUserForInt(msg_target, 0, p.MainMap->NumOfCountries());
  auto *target = this->findById(allTerritories, target_id);

  int armies = 0;
  if (src->Armies != 0) {
    std::string msg_armies =
        "How many armies do you want to airlift with out of " +
        std::to_string(src->Armies) + "? ";
    armies = askUserForInt(msg_armies, 1, src->Armies);
  } else {
    std::cout << "\tNo armies on that territory!";
  }

  auto *order = new Airlift(p.PID, armies, src, target, &p, p.DeckOfCards);
  std::cout << "\t" << p.PID << " airlifts " << armies << " armies to "
            << target->Name << " - " << target->Armies << " owned by "
            << target->OwnedBy << " from " << src->Name << " - " << src->Armies
            << " armies " << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::createBlockade(Player &p) {
  std::cout << "These are the territories you can blockade:\n";
  auto ownedTerritories = p.toDefend();
  displayVector(ownedTerritories);

  std::string msg_src = "Choose a territory to blockade: ";
  const int src_id =
      this->askUserForInt(msg_src, 0, p.MainMap->NumOfCountries());
  auto *src = this->findById(ownedTerritories, src_id);

  auto *order = new Blockade(p.PID, src);
  std::cout << "\t" << p.PID << " blockades " << src->Name << " - "
            << src->Armies << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
};

void HumanStrategy::createNegotiate(Player &p) {
  std::cout << "These are the players in the game: ";
  for (auto &player : p.ListOfPlayers) {
    std::cout << player->PID << "\n";
  }

  Player *enemy = nullptr;

  bool validInput{false};
  std::string input{"x"};
  while (!validInput) {
    std::cout << "Pick a player name to negotiate with: ";
    std::cin >> input;
    std::cout << "\n";
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter a string value\n";
    } else {
      for (auto &player : p.ListOfPlayers) {
        if (player->PID == input) {
          validInput = true;
          enemy = player;
        }
      }
      std::cout << "That was not a valid input try again.\n";
    }
  }

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

Territory *HumanStrategy::findById(std::vector<Territory *> &list, int id) {
  for (auto &t : list) {
    if (t->TerritoryID == id) {
      return t;
    }
  }
  return nullptr;
}

int HumanStrategy::askUserForInt(std::string &message, int min, int max) const {
  int input{min - 1};
  while (true) {
    std::cout << message;
    std::cin >> input;
    std::cout << "\n";
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (input < min || input > max) {
        std::cout << input << " is not an acceptable input. Try again.";
      } else {
        return input;
      }
    }
  }
}

void HumanStrategy::askForAdvanceOrder(Player &p) {
  bool validInput{false};
  std::string input{"x"};

  while (!validInput) {
    std::cout << "Pick [t] to transfer armies or [a] to attack: ";
    std::cin >> input;
    std::cout << "\n";
    if (std::cin.fail()) {
      std::cin.clear();
      std::string discard;
      getline(std::cin, discard);
      std::cout << "Enter an INTEGER value\n";
    } else {
      if (input != "a" && input != "t") {
        std::cout << "The input " << input << " is not valid. Try again.\n";
      } else {
        validInput = true;
      }
    }
  }

  if (input == "a") {
    this->advanceAttack(p);
  } else {
    this->advanceTransfer(p);
  }
}

void HumanStrategy::displayVector(std::vector<Territory *> &list) {
  for (auto &t : list) {
    std::cout << "\t\t[" << t->TerritoryID << "]: " << t->Name
              << " - Armies: " << t->Armies << " - Owner: " << t->OwnedBy
              << std::endl;
  }
}

//-----------------------------------------------------------------
// AGGRESSIVE PLAYER
//-----------------------------------------------------------------
AggressivePlayerStrategy::AggressivePlayerStrategy() {
  std::cout << "\t[UPDATE] - I am an AGGRESSIVE PLAYER\n";
}
std::string AggressivePlayerStrategy::iAm() { return "Aggressive Player"; }

std::vector<Territory *> AggressivePlayerStrategy::toAttack(Player &p) {
  // Using a map to ensure unique values of territories
  std::map<int, Territory *> toAttackMap;
  auto ownedTerritories = p.toDefend();

  std::vector<Territory *> toAttack =
      p.MainMap->ReturnListOfAdjacentCountriesByIDAndNotPlayer(
          ownedTerritories.at(0)->TerritoryID, p.PID);

  return toAttack;
}

std::vector<Territory *> AggressivePlayerStrategy::toDefend(Player &p) {
  int maxArmiesInATerritory = 0;
  int StrongestTerritoryIndex = 0;
  std::vector<Territory *> toDefend = p.Territories;

  for (int j = 0; j < p.Territories.size(); j++) {
    StrongestTerritoryIndex = j;

    for (int i = j; i < p.Territories.size(); i++) {
      if (toDefend.at(i)->Armies > maxArmiesInATerritory) {
        StrongestTerritoryIndex = i;
        maxArmiesInATerritory = toDefend.at(i)->Armies;
      }
    }
    auto *temp = toDefend.at(j);
    toDefend.at(j) = toDefend.at(StrongestTerritoryIndex);
    toDefend.at(StrongestTerritoryIndex) = temp;
    maxArmiesInATerritory = 0;
  }

  return toDefend;
}

void AggressivePlayerStrategy::issueOrder(Player &p) {
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
    if (toAttack(p).size() == 0) {
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
}

void AggressivePlayerStrategy::createDeploy(Player &p) {
  auto ownedTerritories = p.toDefend();
  auto *territoryToDeploy = ownedTerritories.at(0);

  int armies = 0;
  if (p.ReinforcementPool - p.ReinforcementsDeployed > 0) {
    armies = p.ReinforcementPool;
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
}

void AggressivePlayerStrategy::advanceAttack(Player &p) {
  auto ownedTerritories = p.toDefend();
  auto PossibleTargets = p.toAttack();

  auto *target = PossibleTargets.at(rand() % (PossibleTargets.size()));
  auto *src = ownedTerritories.at(0);

  const int armies = src->Armies;

  if (armies == 0) {
    std::cout << "\tNo armies on that territory!";
  }

  auto *order =
      new Advance(p.PID, armies, src, target, p.MainMap, &p, p.DeckOfCards);

  std::cout << "\t" << p.PID << " attacks " << target->Name << " - "
            << target->Armies << " owned by " << target->OwnedBy << " with "
            << src->Name << " - " << src->Armies << " armies " << '\n';

  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

void AggressivePlayerStrategy::advanceTransfer(Player &p) {
  auto ownedTerritories = p.toDefend();
  auto *src = ownedTerritories.at(0);
  auto ListofAdj = p.MainMap->ReturnListOfAdjacentCountriesByIDAndByPlayer(
      src->TerritoryID, p.PID);

  // pick a random adjacent territory
  auto *target = ListofAdj.at(rand() % (ListofAdj.size()));

  // if possible, find an adjacent territory that has enemy adjacent territory
  for (auto &i : ListofAdj) {
    if (p.MainMap
            ->ReturnListOfAdjacentCountriesByIDAndNotPlayer(i->TerritoryID,
                                                            p.PID)
            .size() > 0) {
      target = i;
    };
  }
  int armies = 0;
  if (src->Armies > 0) {
    armies = src->Armies;
  }

  auto *order =
      new Advance(p.PID, armies, src, target, p.MainMap, &p, p.DeckOfCards);

  std::cout << "\t" << p.PID << " transfers " << armies << " armies to "
            << target->Name << " - " << target->Armies << " from " << src->Name
            << " - " << src->Armies << " total armies " << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

void AggressivePlayerStrategy::playCard(Player &p) {
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
}

void AggressivePlayerStrategy::createBomb(Player &p) {
  auto ListofAdj = p.MainMap->ReturnListOfAdjacentCountriesByIDAndNotPlayer(
      p.Territories.at(rand() % (p.Territories.size()))->TerritoryID, p.PID);
  if (ListofAdj.size() > 0) {
    auto *target = ListofAdj.at(rand() % (ListofAdj.size()));

    auto *order = new Bomb(p.PID, target, &p);

    std::cout << "\t" << p.PID << " bombs " << target->Name << " - "
              << target->Armies << " owned by " << target->OwnedBy << '\n';
    p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
  } else {
    std::cout << "No adjacent territory to bomb" << std::endl;
  }
};

void AggressivePlayerStrategy::createAirlift(Player &p) {
  auto ownedTerritories = p.toDefend();
  auto *src = ownedTerritories.at(0);

  int player_pos = 0;
  for (int i = 0; i < p.ListOfPlayers.size(); i++) {
    if (p.ListOfPlayers.at(i)->PID == p.PID) {
      player_pos = i;
    }
  }

  auto enemy_pos = rand() % p.ListOfPlayers.size();
  // making sure the player himself is not chosen
  if (enemy_pos == player_pos) {
    if (player_pos == 0) {
      enemy_pos += 1;
    } else {
      enemy_pos -= 1;
    }
  }

  auto listOfTargets = p.ListOfPlayers.at(enemy_pos)->Territories;
  const auto pos = rand() % listOfTargets.size();
  auto *target = listOfTargets.at(pos);

  int armies = 0;
  if (src->Armies > 0) {
    armies = src->Armies;
  }

  auto *order = new Airlift(p.PID, armies, src, target, &p, p.DeckOfCards);
  std::cout << "\t" << p.PID << " airlifts " << armies << " armies to "
            << target->Name << " - " << target->Armies << " owned by "
            << target->OwnedBy << " from " << src->Name << " - " << src->Armies
            << " armies " << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

void AggressivePlayerStrategy::createBlockade(Player &p) {
  auto *src = p.Territories.at(rand() % (p.Territories.size()));

  auto *order = new Blockade(p.PID, src);
  std::cout << "\t" << p.PID << " blockades " << src->Name << " - "
            << src->Armies << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

void AggressivePlayerStrategy::createNegotiate(Player &p) {
  int player_pos = 0;
  for (int i = 0; i < p.ListOfPlayers.size(); i++) {
    if (p.ListOfPlayers.at(i)->PID == p.PID) {
      player_pos = i;
    }
  }

  auto enemy_pos = rand() % p.ListOfPlayers.size();
  // making sure the player himself is not chosen
  if (enemy_pos == player_pos) {
    if (player_pos == 0) {
      enemy_pos += 1;
    } else {
      enemy_pos -= 1;
    }
  }
  Player *enemy = p.ListOfPlayers.at(enemy_pos);
  auto *order = new Negotiate(&p, enemy);
  std::cout << "\t" << p.PID << " negotiates with " << enemy->PID << " - "
            << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

void AggressivePlayerStrategy::createReinforcement(Player &p) {
  std::cout << "\t" << p.PID << " reinforces his pool\n";
  p.ListOfOrders->addToList(
      static_cast<std::shared_ptr<Order>>(new Reinforcement(&p)));
}

//-----------------------------------------------------------------
// BENEVOLENT PLAYER
//-----------------------------------------------------------------
BenevolentPlayerStrategy::BenevolentPlayerStrategy() {
  std::cout << "\t[UPDATE] - I am a BENEVOLENT PLAYER\n";
}

std::string BenevolentPlayerStrategy::iAm() { return "Benevolent Player"; }

std::vector<Territory *> BenevolentPlayerStrategy::toAttack(Player &p) {
  // Using a map to ensure unique values of territories
  std::map<int, Territory *> toAttackMap;
  auto ownedTerritories = p.toDefend();

  std::vector<Territory *> toAttack =
      p.MainMap->ReturnListOfAdjacentCountriesByIDAndNotPlayer(
          ownedTerritories.at(0)->TerritoryID, p.PID);

  return toAttack;
}

std::vector<Territory *> BenevolentPlayerStrategy::toDefend(Player &p) {
  std::cout << "DEBUG: DISPLAY ALL PLAYER TERRITORY\n";
  displayVector(p.Territories);

  if (weakestCountry(p) != nullptr) {
    std::cout << "DEBUG: THERE IS WEAKEST COUNTRY AND ID = "
              << weakestCountry(p)->TerritoryID << "\n";
    std::cout << "DEBUG: AND ITS ADJACENT TERRITORY\n";
    std::vector<Territory *> toDefend =
        p.MainMap->ReturnListOfAdjacentCountriesByID(
            weakestCountry(p)->TerritoryID);

    displayVector(toDefend);
  }
  std::vector<Territory *> toDefend =
      p.MainMap->ReturnListOfAdjacentCountriesByIDAndByPlayer(
          weakestCountry(p)->TerritoryID, p.PID);

  std::cout << "DEBUG: DISPLAY DEFEND LIST\n";
  displayVector(toDefend);
  return toDefend;
}

void BenevolentPlayerStrategy::issueOrder(Player &p) {
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
    this->advanceTransfer(p);

    p.AdvanceOrderDone = true;
    // Play a card
  } else if (!p.CardPlayed) {
    std::cout << "\t" << p.PID << " already did deploy/advance order\n"
              << "\tChoosing card\n";
    this->playCard(p);
    p.CardPlayed = true;
  }
}

void BenevolentPlayerStrategy::createDeploy(Player &p) {
  auto ownedTerritories = p.toDefend();
  auto *territoryToDeploy = weakestCountry(p);

  int armies = 0;
  if (p.ReinforcementPool - p.ReinforcementsDeployed > 0) {
    armies = p.ReinforcementPool;
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
}

void BenevolentPlayerStrategy::advanceAttack(Player &p) {
  std::cout
      << "Benevolent Player decides to stay in defensive mode and not attack"
      << std::endl;
}

void BenevolentPlayerStrategy::advanceTransfer(Player &p) {
  auto ownedTerritories = p.toDefend();
  std::cout << "DEBUG: PASSED toDEFEND()\n";
  // if the adjacent countries doesn't have a country belong to player, nothing
  // will be done
  if (ownedTerritories.size() == 0) {
    std::cout << "There is no adjacent countries for weakest country\n";
    std::cout << "The transfer was cancelled\n";
    return;
  }
  Territory *src = p.toDefend().at(0);
  std::cout << "DEBUG: PASSED OwnedTerritory.at(0)\n";
  // finding the strongest country among the adjacent country

  for (Territory *strongest : ownedTerritories) {
    if (src->Armies > strongest->Armies) src = strongest;
  }

  auto ListofAdj = p.MainMap->ReturnListOfAdjacentCountriesByIDAndByPlayer(
      src->TerritoryID, p.PID);

  // pick the weakest territory
  auto *target = this->weakestCountry(p);

  int armies = 0;
  if (src->Armies > 1) {
    armies = src->Armies / 2;
  }

  auto *order =
      new Advance(p.PID, armies, src, target, p.MainMap, &p, p.DeckOfCards);

  std::cout << "\t" << p.PID << " transfers " << armies << " armies to "
            << target->Name << " - " << target->Armies << " from " << src->Name
            << " - " << src->Armies << " total armies " << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

void BenevolentPlayerStrategy::playCard(Player &p) {
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
}

void BenevolentPlayerStrategy::createBomb(Player &p) {
  auto ListofAdj = p.MainMap->ReturnListOfAdjacentCountriesByIDAndNotPlayer(
      p.Territories.at(rand() % (p.Territories.size()))->TerritoryID, p.PID);
  if (ListofAdj.size() > 0) {
    auto *target = ListofAdj.at(rand() % (ListofAdj.size()));

    auto *order = new Bomb(p.PID, target, &p);

    std::cout << "\t" << p.PID << " bombs " << target->Name << " - "
              << target->Armies << " owned by " << target->OwnedBy << '\n';
    p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
  } else {
    std::cout << "No adjacent territory to bomb" << std::endl;
  }
}

void BenevolentPlayerStrategy::createAirlift(Player &p) {
  auto *src = strongestCountry(p);

  auto *target = weakestCountry(p);

  int armies = 0;
  if (src->Armies > 1) {
    armies = src->Armies / 2;
  }

  auto *order = new Airlift(p.PID, armies, src, target, &p, p.DeckOfCards);
  std::cout << "\t" << p.PID << " airlifts " << armies << " armies to "
            << target->Name << " - " << target->Armies << " owned by "
            << target->OwnedBy << " from " << src->Name << " - " << src->Armies
            << " armies " << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

void BenevolentPlayerStrategy::createBlockade(Player &p) {
  auto *src = p.Territories.at(rand() % (p.Territories.size()));

  auto *order = new Blockade(p.PID, src);
  std::cout << "\t" << p.PID << " blockades " << src->Name << " - "
            << src->Armies << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

void BenevolentPlayerStrategy::createNegotiate(Player &p) {
  int player_pos = 0;
  for (int i = 0; i < p.ListOfPlayers.size(); i++) {
    if (p.ListOfPlayers.at(i)->PID == p.PID) {
      player_pos = i;
    }
  }

  auto enemy_pos = rand() % p.ListOfPlayers.size();
  // making sure the player himself is not chosen
  if (enemy_pos == player_pos) {
    if (player_pos == 0) {
      enemy_pos += 1;
    } else {
      enemy_pos -= 1;
    }
  }
  Player *enemy = p.ListOfPlayers.at(enemy_pos);
  auto *order = new Negotiate(&p, enemy);
  std::cout << "\t" << p.PID << " negotiates with " << enemy->PID << " - "
            << '\n';
  p.ListOfOrders->addToList(static_cast<std::shared_ptr<Order>>(order));
}

void BenevolentPlayerStrategy::createReinforcement(Player &p) {
  std::cout << "\t" << p.PID << " reinforces his pool\n";
  p.ListOfOrders->addToList(
      static_cast<std::shared_ptr<Order>>(new Reinforcement(&p)));
}

void BenevolentPlayerStrategy::displayVector(std::vector<Territory *> &list) {
  for (auto &t : list) {
    std::cout << "\t\t[" << t->TerritoryID << "]: " << t->Name
              << " - Armies: " << t->Armies << " - Owner: " << t->OwnedBy
              << std::endl;
  }
}

// iterate through the territories
// compare each army
// assign the first territory to the pointer
Territory *BenevolentPlayerStrategy::weakestCountry(Player &p) {
  Territory *returnTerritory = p.Territories.at(0);
  for (auto *territory : p.Territories) {
    if (territory->Armies < returnTerritory->Armies)
      returnTerritory = territory;
  }
  return returnTerritory;
}

Territory *BenevolentPlayerStrategy::strongestCountry(Player &p) {
  Territory *returnTerritory = p.Territories.at(0);
  for (auto *territory : p.Territories) {
    if (territory->Armies > returnTerritory->Armies)
      returnTerritory = territory;
  }
  return returnTerritory;
}

//-----------------------------------------------------------------
// NEUTRAL PLAYER
//-----------------------------------------------------------------

NeutralPlayerStrategy::NeutralPlayerStrategy() {
  std::cout << "\t[UPDATE] - I am a NEUTRAL PLAYER\n";
}

std::string NeutralPlayerStrategy::iAm() { return "Neutral Player"; }

/*no orders issued for neutral player*/
void NeutralPlayerStrategy::issueOrder(Player &p) {
  p.AdvanceOrderDone = true;
  p.CardPlayed = true;
  std::cout << "\n\t" << p.PID << " is a neutral player. No orders to be issued.\n" << std::endl;
}

/*no territories need to be returned for neutral player*/
std::vector<Territory *> NeutralPlayerStrategy::toAttack(Player &p) {
    return {};
}

/*no territories need to be returned for neutral player*/
std::vector<Territory *> NeutralPlayerStrategy::toDefend(Player &p) {
    return {};
}

/*no bombs will be issued for neutral player*/
void NeutralPlayerStrategy::createBomb(Player &p) {}

/*no airlifts will be issued for neutral player*/
void NeutralPlayerStrategy::createAirlift(Player &p) {}

/*no blockades will be issued for neutral player*/
void NeutralPlayerStrategy::createBlockade(Player &p) {}

/*no negotiation will be issued for neutral player*/
void NeutralPlayerStrategy::createNegotiate(Player &p) {}

/*no reinforcements will be issued for neutral player*/
void NeutralPlayerStrategy::createReinforcement(Player &p) {}

