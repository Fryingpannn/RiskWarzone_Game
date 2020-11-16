#include "GameEngine.h"

#include <algorithm>
#include <chrono>
#include <iomanip>  // For std::setprecision()
#include <random>
#include <thread>

GameEngine::GameEngine() { Init(); }

GameEngine::~GameEngine() {
  delete MainMap;
  delete MainFile;
  for (Player *player : ListOfPlayers) delete player;
}

/**
 * Initializes the game with a given map and number of players.
 * Each player starts with an empty hand of cards. The territories are evenly
 * distributed among the players. Once this is done, the main game loop runs
 * until a winner is declared.
 */
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

  /// DEBUG code creates 3 players automatically
  /// set to false to create your own players!!!
  bool debugMainLoop{true};

  if (!debugMainLoop) {
    // the main menu for player to setup how many players and the map they want
    // to use :O
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
        std::cout
            << "You can't be playing alone... Please get a friend and you "
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
      ListOfPlayers.at(ListOfPlayers.size() - 1)->PID = PlayerName;
    }
  } else {
    /// DEBUG CODE TO DELETE
    /// creates 3 players and chooses map
    NumberOfPlayers = 3;
    MapFileName = "europe.map";
    auto *player1 = new Player();
    player1->PID = "Sandra";
    ListOfPlayers.push_back(player1);
    auto *player2 = new Player();
    player2->PID = "Dog";
    ListOfPlayers.push_back(player2);
    auto *player3 = new Player();
    player3->PID = "Kuro";
    ListOfPlayers.push_back(player3);
    /// DEBUG CODE TO DELETE
  }

  std::cout << "Successfully added" << NumberOfPlayers
            << " Number of Players\n ";

  std::string MapFolderBasePath = "./maps/";

  while (InputMapNotSucceed) {
    std::cout << "Now tell me the name of the map you want to load? (must be "
                 "in the ./maps/ directory)\n ";

    ///  DEBUG CODE choses map already for us
    if (!debugMainLoop) {
      std::cin >> MapFileName;
    }

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

  phaseObserverToggle = true;
  gameStatsObserverToggle = true;

  while (InputObserverNotSucceed) {
    std::cout << std::boolalpha;
    std::cout << "1. Phase Observer: " << phaseObserverToggle << std::endl;
    std::cout << "2. Game Statistics Observer: " << gameStatsObserverToggle
              << std::endl;
    std::cout << "Enter your selection ('q' to quit and save your selection): ";

    InputObserver = '1';
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
  std::list<Observer *> observerList;
  for (auto *player : ListOfPlayers) {
    if (phaseObserverToggle) {
      auto *newPhaseObserver = new PhaseObserver(player);
      observerList.push_back(newPhaseObserver);
    }
    if (gameStatsObserverToggle) {
      auto *newGameStatsObserver = new GameStatisticsObserver(player);
      observerList.push_back(newGameStatsObserver);
    }
  }

  // Add GameEngine observers
  if (phaseObserverToggle) {
    auto *newPhaseObserver = new PhaseObserver(this);
    observerList.push_back(newPhaseObserver);
  }
  if (gameStatsObserverToggle) {
    auto *newGameStatsObserver = new GameStatisticsObserver(this);
    observerList.push_back(newGameStatsObserver);
  }

  for (auto *territory : MainMap->ReturnListOfCountries()) {
    if (phaseObserverToggle) {
      auto *newPhaseObserver = new PhaseObserver(territory);
      observerList.push_back(newPhaseObserver);
    }
    if (gameStatsObserverToggle) {
      auto *newGameStatsObserver = new GameStatisticsObserver(territory);
      observerList.push_back(newGameStatsObserver);
    }
  }

  // Init deck from main map
  this->DeckOfCards = new Deck(MainMap->NumOfCountries());

  // Bind map and deck elements to each player object
  for (auto &player : ListOfPlayers) {
    player->bindGameElements(this->ListOfPlayers, this->MainMap,
                             this->DeckOfCards);
  }

  std::cout << "now the game is ready to go! (≧▽≦)!! \n";

  // -------------------------------------------------------
  // STARTUP PHASE LOOP
  // -------------------------------------------------------

  startupPhase();

  // -------------------------------------------------------
  // MAIN GAME LOOP
  // -------------------------------------------------------
  // TODO CALL MAIN GAME LOOP
  mainGameLoop();

  // TODO Delete all observers in observerList
}

/**
 * The startup phase initializes the order the players will play in.
 * It also randomly assigns all territories evenly to each player.
 * Each player receives an initial amounts of reinforcements.
 */
void GameEngine::startupPhase() {
  srand(time(NULL));
  // Shuffle the list of players
  std::random_shuffle(ListOfPlayers.begin(), ListOfPlayers.end());

  // create a list of numbers from 0 to the number of countries in the map
  std::vector<int> randomizedIDs;

  for (int i = 0; i < MainMap->NumOfCountries(); i++) {
    randomizedIDs.emplace_back(i);
  }

  // randomize the list of numbers
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(std::begin(randomizedIDs), std::end(randomizedIDs),
               std::default_random_engine(seed));

  // now iterate through the randomized list, assign countries to players in
  // robin round fashion The randomized list plays the role of territory
  // indexes. each territory has a unique ID (index), so it is assigned once and
  // only once.
  int rr = 0;
  for (int i = 0; i < MainMap->NumOfCountries(); i++) {
    auto *territory = MainMap->ReturnListOfCountries().at(randomizedIDs.at(i));
    ListOfPlayers.at(rr)->Territories.emplace_back(territory);
    territory->PlayerOwned = ListOfPlayers.at(rr);
    territory->OwnedBy = ListOfPlayers.at(rr)->PID;

    State new_state;
    new_state.current_state = State_enum::SETUP_PHASE_RECEIVE_TERRITORY;
    ListOfPlayers.at(rr)->setState(new_state);
    ListOfPlayers.at(rr)->Notify();

    MainMap->ReturnListOfCountries()
        .at(randomizedIDs.at(i))
        ->setState(new_state);
    MainMap->ReturnListOfCountries().at(randomizedIDs.at(i))->Notify();

    rr += 1;
    if (rr == ListOfPlayers.size()) {
      rr = 0;
    }
  }

  // give armies to the players based on the number of players in the game
  switch (ListOfPlayers.size()) {
    case 2:
      for (int i = 0; i < 2; i++) {
        ListOfPlayers.at(i)->ReinforcementPool = 40;
        State new_state;
        new_state.current_state =
            State_enum::SETUP_PHASE_RECEIVE_REINFORCEMENTS;
        new_state.newReinforcements = 40;
        ListOfPlayers.at(i)->setState(new_state);
        ListOfPlayers.at(i)->Notify();
      }
      break;
    case 3:
      for (int i = 0; i < 3; i++) {
        ListOfPlayers.at(i)->ReinforcementPool = 35;
        State new_state;
        new_state.current_state =
            State_enum::SETUP_PHASE_RECEIVE_REINFORCEMENTS;
        new_state.newReinforcements = 35;
        ListOfPlayers.at(i)->setState(new_state);
        ListOfPlayers.at(i)->Notify();
      }
      break;
    case 4:
      for (int i = 0; i < 4; i++) {
        ListOfPlayers.at(i)->ReinforcementPool = 30;
        State new_state;
        new_state.current_state =
            State_enum::SETUP_PHASE_RECEIVE_REINFORCEMENTS;
        new_state.newReinforcements = 30;
        ListOfPlayers.at(i)->setState(new_state);
        ListOfPlayers.at(i)->Notify();
      }
      break;
    case 5:
      for (int i = 0; i < 5; i++) {
        ListOfPlayers.at(i)->ReinforcementPool = 25;
        State new_state;
        new_state.current_state =
            State_enum::SETUP_PHASE_RECEIVE_REINFORCEMENTS;
        new_state.newReinforcements = 25;
        ListOfPlayers.at(i)->setState(new_state);
        ListOfPlayers.at(i)->Notify();
      }
      break;
  }

  std::cout << "PLAYERS' INFORMATION:" << std::endl;
  std::cout << "----------------------------------------------------"
            << std::endl;

  for (auto &i : ListOfPlayers) {
    std::cout << *i;
    std::cout << std::endl;
  }

  std::cout << "TERRITORIES' INFORMATION:" << std::endl;
  std::cout << "----------------------------------------------------"
            << std::endl;

  for (auto &i : MainMap->ReturnListOfCountries()) {
    std::cout << *i;
    std::cout << "\tOwned By: " << i->OwnedBy << std::endl;
    std::cout << std::endl;
  }

  // to show that there are no duplicates, we compare the number of territories
  // owned by all the players to number of territories in the map
  int sumOfPlayerOwnedTerritories = 0;
  for (int i = 0; i < ListOfPlayers.size(); i++) {
    sumOfPlayerOwnedTerritories += ListOfPlayers.at(i)->Territories.size();
  }

  std::cout << "\tPlayers own " << sumOfPlayerOwnedTerritories
            << " territories altogether" << std::endl;
  std::cout << "\tThere are " << MainMap->NumOfCountries()
            << " territories in the map in total." << std::endl;
}

/**
 * Main game play loop constituting of reinforcement, issue order and execution
 * phases. Decides who the winner is.
 */
void GameEngine::mainGameLoop() {
  bool gameOver{false};

  // Loop until a player owns all territories
  while (!gameOver) {
    // CHECK: Can we remove any players who have no territories?
    for (unsigned int i = 0; i < ListOfPlayers.size(); i++) {
      if (ListOfPlayers.at(i)->Territories.empty()) {
        State new_state;
        new_state.current_state = State_enum::PLAYER_ELIMINATED;
        new_state.player_name = ListOfPlayers.at(i)->PID;
        // Remove player from game by removing him from the list
        ListOfPlayers.erase(ListOfPlayers.begin() + i);

        this->setState(new_state);
        this->Notify();
      }
    }

    // CHECK: Do we have a winner?
    if (ListOfPlayers.size() == 1) {
      // TODO check this is in the right place
      std::cout << ListOfPlayers.at(0)->PID << " has won the game."
                << std::endl;

      gameOver = true;

      State new_state;
      new_state.current_state = State_enum::PLAYER_OWNS_ALL_TERRITORIES;
      new_state.player_name = ListOfPlayers.at(0)->PID;

      this->setState(new_state);
      this->Notify();

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

  for (auto &player : ListOfPlayers) {
    // TODO add + bonus per continent from mapLoader
    auto territories = MainMap->ReturnListOfCountriesOwnedByPlayer(player->PID);
    auto armies = static_cast<int>(territories.size() / 3.0);
    player->ReinforcementPool += armies;

    State new_state;
    new_state.current_state = State_enum::REINFORCEMENT_PHASE;
    new_state.newReinforcements = armies;
    player->setState(new_state);
    player->Notify();
  }
}

/**
 * Players issue orders and place them in their own order list.
 */
void GameEngine::issueOrdersPhase() {
  std::cout << "--------------------------\n"
            << "BEGIN ORDER ISSUING PHASE\n";
  // Initialize issue order phase for each player
  for (auto &player : ListOfPlayers) {
    player->initIssueOrder();
  }

  // Initialize the phase with everyone having orders to make
  auto ordersLeft = ListOfPlayers.size();

  // Loop until no orders left for each player in same turn
  while (ordersLeft > 0) {
    ordersLeft = ListOfPlayers.size();
    for (auto &player : ListOfPlayers) {
      std::cout << "\n----- Player " << player->PID << "'s turn: ----- ";
      if (player->AdvanceOrderDone && player->CardPlayed) {
        std::cout << "No orders left\n";
        // If a player no longer has any order left to make
        ordersLeft--;
      } else {
        std::cout << "Performing order ->";
        player->issueOrder();

        State new_state;
        new_state.current_state = State_enum::ISSUE_ORDERS_PHASE;
        player->setState(new_state);
        player->Notify();
      }
    }
  }
  std::cout << "END OF ORDER ISSUING PHASE\n"
            << "--------------------------\n";
}

/**
 * Executes orders of players from their orders list.
 */
void GameEngine::executeOrdersPhase() {
  std::cout << "--------------------------\n"
            << "BEGIN ORDER EXECUTION PHASE\n";

  // Execute only deploy orders first
  auto ordersLeft = ListOfPlayers.size();
  while (ordersLeft > 0) {
    ordersLeft = ListOfPlayers.size();
    for (auto &player : ListOfPlayers) {
      // TODO how to properly check for deploy orders
      if (player->ListOfOrders->peek()->getName() == "DEPLOY") {
        Territory *target = player->ListOfOrders->peek()->getTarget();

        State new_phase_state;
        new_phase_state.current_state = State_enum::EXECUTE_ORDERS_PHASE;
        new_phase_state.executed_order_name =
            player->ListOfOrders->peek()->getName();

        // State new_game_stats_state;
        // new_game_stats_state.current_state = State_enum::TERRITORY_CONQUERED;
        // new_game_stats_state.executed_order_name =
        // player->ListOfOrders->peek()->getName();

        bool success = player->ListOfOrders->pop()->execute();

        new_phase_state.execute_order_success = success;

        player->setState(new_phase_state);
        player->Notify();

        // if (success) {
        // 	target->setState(new_game_stats_state);
        // 	target->Notify();
        // }
      } else {
        ordersLeft--;
      }
    }
  }

  // todo change logic
  auto reinforcementsDone{ListOfPlayers.size()};

  for (auto *player : ListOfPlayers) {
    reinforcementsDone--;
  }
  // perform other orders only if we have 0 reinforments left to commit
  if (reinforcementsDone == 0) {
    // Execute other orders by priority
    ordersLeft = ListOfPlayers.size();
    while (ordersLeft > 0) {
      ordersLeft = ListOfPlayers.size();
      for (auto &player : ListOfPlayers) {
        if (!player->ListOfOrders->empty()) {
          Territory *target = player->ListOfOrders->peek()->getTarget();

          State new_phase_state;
          new_phase_state.current_state = State_enum::EXECUTE_ORDERS_PHASE;
          new_phase_state.executed_order_name =
              player->ListOfOrders->peek()->getName();

          State new_game_stats_state;
          new_game_stats_state.current_state = State_enum::TERRITORY_CONQUERED;
          new_game_stats_state.executed_order_name =
              player->ListOfOrders->peek()->getName();

          bool success = player->ListOfOrders->pop()->execute();

          new_phase_state.execute_order_success = success;
          new_game_stats_state.execute_order_success = success;

          player->setState(new_phase_state);
          player->Notify();
          if (target != nullptr) {
            target->setState(new_game_stats_state);
            target->Notify();
          }

          this->setState(new_game_stats_state);
          this->Notify();
          // TODO is this the right place for this?
          player->cardNotGiven = true;
        } else {
          ordersLeft--;
        }
      }
    }
  }
  //reset negotiated player list and card given status
  for (auto* player : ListOfPlayers) {
      player->set.clear();
      player->cardNotGiven = true;
  }
  std::cout << "END OF ORDER EXECUTION PHASE\n"
            << "--------------------------\n";
}

void GameEngine::displayStatistics() {
  int total_territories = MainMap->NumOfCountries();

  std::cout << "Game Statistics: " << std::endl;
  std::cout << "==================================" << std::endl;
  std::cout << "Map Name: " << MainMap->GetMapName() << std::endl;
  std::cout << "Total Territories: " << total_territories << std::endl;
  std::cout << "--------------------------" << std::endl;
  for (auto *player : ListOfPlayers) {
    // int player_territories = player->Territories.size();
    int player_territories;
    player_territories =
        MainMap->ReturnListOfCountriesOwnedByPlayer(player->PID).size();
    std::cout << "Name: " << player->PID << std::endl;
    std::cout << std::fixed << std::showpoint << std::setprecision(2);
    std::cout << "\tOwned Territories: " << player_territories << " ( "
              << static_cast<double>(player_territories) / total_territories *
                     100
              << "% of total)" << std::endl;
    std::cout << "--------------------------" << std::endl;
  }
}