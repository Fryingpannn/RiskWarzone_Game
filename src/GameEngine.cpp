#include "GameEngine.h"

#include <chrono>
#include <thread>
#include <algorithm>
#include <random>

GameEngine::GameEngine() { Init(); }

GameEngine::~GameEngine() {
  delete MainMap;
  delete MainFile;
  for (Player* player : ListOfPlayers) delete player;
}

void GameEngine::Init() {
  // The variable for players input
  int NumberOfPlayers;
  bool InputPlayersNotSucceed = true;
  std::string PlayerName;

  // The variable for map input
  std::string MapFileName;
  bool InputMapNotSucceed = true;

  // the variable for observer input
  std::string InputObserver;
  bool InputObserverNotSucceed = true;

  // the main menu for player to setup how many players and the map they want to
  // use :O
  std::cout << "Hey there you little filty general! Welcome to Warzone where "
               "you control armies and conquer other countries!"
            << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "Now! Now! How many person will be playing this game??"
            << std::endl;
  std::cout << "Or" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << "love to command and conquer?? and trying to end humanity??"
            << std::endl;
  std::cin >> NumberOfPlayers;
  while (InputPlayersNotSucceed) {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Please Enter a valid number between 2 and 5 =__=";
      std::cin >> NumberOfPlayers;
    } else if (NumberOfPlayers == 1) {
      std::cout << "You can't be playing alone... Please get a friend and you "
                   "need it\n";
      std::cin >> NumberOfPlayers;
    } else {
      InputPlayersNotSucceed = false;
    }
  }
  std::cout << "GOOOD!\n";
  Timer(100);
  std::cout << "So you will be playing with " << NumberOfPlayers
            << " Number of Players\n ";

  for (int i = 0; i < NumberOfPlayers; i++) {
    Timer(100);
    std::cout << ". " << std::endl;
    ListOfPlayers.push_back(new Player());
    std::cout << "Please enter player" << i << "'s name: ";
    std::cin >> PlayerName;
    ListOfPlayers.at(ListOfPlayers.size()-1)->PID = PlayerName;
  }

  std::cout << "Successfully added" << NumberOfPlayers
            << " Number of Players\n ";

  std::string MapFolderBasePath = "./maps/";

  while (InputMapNotSucceed) {
    std::cout << "Now tell me the name of the map you want to load? (must be "
                 "in the ./maps/ directory)\n ";
    std::cin >> MapFileName;
    trim(MapFileName);
    MainFile = new MapFile(MapFolderBasePath + MapFileName);
    Result<void> ReadMapFileResult = MainFile->readMapFile();
    if (ReadMapFileResult.success) {
      std::cout << "Map file successfully read: " << MainFile->map_file_name
                << std::endl;

      // Validate what was read into testMapFile
      Result<void> ValidateMapFile = MainFile->validate();
      if (ValidateMapFile.success) {
        // Valid items in testMapFile
        // Generate a Map object

        MainMap = MainFile->generateMap();

        // Display the map
        MainMap->Display();

        // only when the map is valid then it will break through the loop
        if (MainMap->Validate()) {
          std::cout << "The map is valid!\n";
          InputMapNotSucceed = false;
        } else {
          std::cout << "Deleting the garbage map...\n";
          delete MainMap;
          MapFileName.clear();
        }

      } else {
        std::cerr << "ERROR: testMapFile failed validation checks."
                  << ValidateMapFile.message << std::endl;
      }
    } else {
      std::cerr << "ERROR: Could not read map file: "
                << ReadMapFileResult.message << std::endl;
    }
  }

  bool phaseObserverToggle = true;
  bool gameStatsObserverToggle = true;

  while (InputObserverNotSucceed) {
    std::cout << std::boolalpha;
    std::cout << "1. Phase Observer: " << phaseObserverToggle << std::endl;
    std::cout << "2. Game Statistics Observer: " << gameStatsObserverToggle << std::endl;
    std::cout << "Enter your selection ('q' to quit and save your selection): ";
    std::cin >> InputObserver;


    if (InputObserver == "1") {
      phaseObserverToggle = !phaseObserverToggle;
    } else if (InputObserver == "2") {
      gameStatsObserverToggle = !gameStatsObserverToggle;
    } else if (InputObserver == "q") {
      InputObserverNotSucceed = false;
    } else {
      std::cout << "Invalid Selection" << std::endl;
    }
  }

  // TODO Create a list of observers to delete at the end of this function
  // std::list<Observer *> observerList;
  for(auto *player : ListOfPlayers) {
    if (phaseObserverToggle)
      PhaseObserver *newPhaseObserver = new PhaseObserver(player);
    if (gameStatsObserverToggle)
      GameStatisticsObserver *newGameStatsObserver = new GameStatisticsObserver(player);
  }
  
  std::cout << "now the game is ready to go! (≧▽≦)!! \n";

  // -------------------------------------------------------
  // STARTUP PHASE LOOP
  // -------------------------------------------------------
  // TODO CALL STARTUP LOOP

  startupPhase();
  // TODO update deck to include actual cards based on map
  this->DeckOfCards = new Deck(MainMap->NumOfCountries());

  // -------------------------------------------------------
  // MAIN GAME LOOP
  // -------------------------------------------------------
  // TODO CALL MAIN GAME LOOP
  // mainGameLoop();

  // TODO Delete list of observers
}

/**
 * Main game play loop constituting of reinforcement, issuer order and execution
 * phases. Decides who the winner is.
 */
void GameEngine::mainGameLoop() {
  bool gameOver{false};

  // Loop until a player owns all territories
  while (!gameOver) {
    // CHECK: Can we remove any players who have no territories?
    for (unsigned int i = 0; i < ListOfPlayers.size(); i++) {
      if (ListOfPlayers.at(i)->Territories.empty()) {
        // Remove player from game by removing him from the list
        ListOfPlayers.erase(ListOfPlayers.begin() + i);
      }
    }

    // CHECK: Do we have a winner?
    if (ListOfPlayers.size() == 1) {
      // TODO check this is in the right place
      std::cout << ListOfPlayers.at(0)->PID << " has won the game."
                << std::endl;
      gameOver = true;
      break;
    }

    // ----------------------------------
    // Proceed with game phases
    // reinforcement phase
    reinforcementPhase();
    // issue ordering phase
    issueOrdersPhase();
    // order execution phase
    executeOrdersPhase();
  }
}

/**
 * Give a number of armies to players depending on number of territories they
 * own
 */
void GameEngine::reinforcementPhase() {
  // get number of territories per player
  for (auto& player : ListOfPlayers) {
    auto territories = MainMap->ReturnListOfCountriesOwnedByPlayer(player->PID);

    // TODO check that this is rounded down properly
    int armies = int(territories.size() / 3.0);

    // TODO add + bonus per continent from mapLoader

    player->ReinforcementPool = armies;

    player->setState(State_enum::REINFORCEMENT_PHASE);
    player->Notify();

  }
}

/**
 * Players issue orders and place them in the order list
 */
void GameEngine::issueOrdersPhase() {
  // Every player gets to advance orders and play a card when this phase begins
  for (auto& player : ListOfPlayers) {
    player->AdvanceOrderDone = false;
    player->CardPlayed = false;
  }

  // Initialize the phase with everyone having orders to make
  int ordersLeft = ListOfPlayers.size();

  // TODO check logic functions as intended here
  while (ordersLeft > 0) {
    // This loop only exists when all 4 players don't have orders left on the
    // same turn
    ordersLeft = ListOfPlayers.size();
    for (auto& player : ListOfPlayers) {
      if (player->AdvanceOrderDone && player->CardPlayed) {
        // If a player no longer has any order left to make
        ordersLeft--;
      } else {
        player->issueOrder(*MainMap, *DeckOfCards);
        
        player->setState(State_enum::ISSUE_ORDERS_PHASE);
        player->Notify();
      }
    }
  }
}

/**
 * Executes orders of players from the orders list
 */
void GameEngine::executeOrdersPhase() {
  // execute the top order on the list of each player in RR fashion
  // todo call execute method implemented in part 4
  // till no more orders left
  int ordersLeft = ListOfPlayers.size();
  while (ordersLeft > 0) {
    for (auto& player : ListOfPlayers) {
      // TODO add logic

      player->setState(State_enum::EXECUTE_ORDERS_PHASE);
      player->Notify();
    }
  }
}

void GameEngine::startupPhase() {

    srand(time(NULL));
   //Shuffle the list of players 
    std::random_shuffle(ListOfPlayers.begin(), ListOfPlayers.end());
   
    //create a list of numbers from 0 to the number of countries in the map
    std::vector<int> randomizedIDs;

    for (int i = 0; i < MainMap->NumOfCountries(); i++) {

        randomizedIDs.emplace_back(i);
    }

    //randomize the list of numbers
    unsigned seed = std::chrono::system_clock::now()
        .time_since_epoch()
        .count();
    std::shuffle(std::begin(randomizedIDs), std::end(randomizedIDs), std::default_random_engine(seed));

    //now iterate through the randomized list, assign countries to players in robin round fashion 
    //The randomized list plays the role of territory indexes. each territory has a unique ID (index), so it is assigned once and only once.
    int rr = 0;
    for (int i = 0; i < MainMap->NumOfCountries(); i++) {

        ListOfPlayers.at(rr)->Territories.emplace_back(MainMap->ReturnListOfCountries().at(randomizedIDs.at(i)));
        MainMap->ReturnListOfCountries().at(randomizedIDs.at(i))->OwnedBy = ListOfPlayers.at(rr)->PID;

        ListOfPlayers.at(rr)->setState(State_enum::SETUP_PHASE);
        ListOfPlayers.at(rr)->Notify();

        rr += 1;
        if (rr == ListOfPlayers.size()) {
            rr = 0;
        }
    }
    
    //give armies to the players based on the number of players in the game
    switch (ListOfPlayers.size()) {
    case 2:
        for (int i =0; i < 2; i++) {
            ListOfPlayers.at(i)->ReinforcementPool = 40;
        }
        break;
    case 3:
        for (int i = 0; i < 3; i++) {
            ListOfPlayers.at(i)->ReinforcementPool = 35;
        }
        break;
    case 4:
        for (int i = 0; i < 4; i++) {
            ListOfPlayers.at(i)->ReinforcementPool = 30;
        }
        break;
    case 5:
        for (int i = 0; i < 5; i++) {
            ListOfPlayers.at(i)->ReinforcementPool = 25;
        }
        break;
    }

    std::cout << "PLAYERS' INFORMATION:" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (auto& i : ListOfPlayers) {
 
       std::cout << *i;
       std::cout <<std::endl;

    }

    std::cout << "TERRITORIES' INFORMATION:" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (auto& i : MainMap->ReturnListOfCountries()) {

        std::cout << *i;
        std::cout << "\tOwned By: " << i->OwnedBy << std::endl;
        std::cout << std::endl;

    }

}
