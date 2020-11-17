#pragma once
#include "Cards.h"
#include "MapLoader.hpp"
#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include "GameObservers.hpp"



// Look at how all the members are public, other programmers can access to the
// component they want easily :)
class GameEngine : public Subject {
 public:
  // members of the GameEngine
  MapFile* MainFile;

  Map* MainMap;
  Deck* DeckOfCards;

  // List of all the players at the start of the game
  std::vector<Player*> ListOfPlayers;

  // For game loop to keep track of who is left in the game
  std::vector<Player*> ListOfValidPlayers;

  bool ObserverOn;
  bool phaseObserverToggle;
  bool gameStatsObserverToggle;

  // Constructor
  GameEngine();

  // destructor
  ~GameEngine();

  // function
  void Init();

  void mainGameLoop();
  void startupPhase();
  void reinforcementPhase();
  void issueOrdersPhase();
  void executeOrdersPhase();

  void displayStatistics();
};
