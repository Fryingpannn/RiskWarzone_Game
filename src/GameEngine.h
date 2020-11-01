#pragma once
#include "Cards.h"
#include "MapLoader.hpp"
#include "Orders.h"
#include "Player.h"
#include "Map.h"

#ifdef _DEBUG
#define Log(x) std::cout << x << std::endl;
#define Timer(i)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#define FindMemoryLeak() \
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define Timer(i) std::this_thread::sleep_for(std::chrono::milliseconds(i));
#define FindMemoryLeak() ;
#define Log(x)
#endif

// Look at how all the members are public, other programmers can access to the
// component they want easily :)
class GameEngine {
 public:
  // members of the GameEngine
  MapFile* MainFile;

  Map* MainMap;
  Deck* DeckOfCards;
  // Player has deck class, order class :O
  std::vector<Player*> ListOfPlayers;

  bool ObserverOn;

  // Constructor
  GameEngine();

  // destructor
  ~GameEngine();

  // function
  void Init();

  void mainGameLoop();

  void reinforcementPhase();
  void issueOrdersPhase();
  void executeOrdersPhase();
};
