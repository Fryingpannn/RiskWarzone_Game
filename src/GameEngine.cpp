#include "GameEngine.h"

#include <algorithm>
#include <chrono>
#include <iomanip>  // For std::setprecision()
#include <random>
#include <thread>

#define Timer(i) std::this_thread::sleep_for(std::chrono::milliseconds(i));

GameEngine::GameEngine() { Init(); }

GameEngine::~GameEngine() {
  delete this->DeckOfCards;
  this->DeckOfCards = nullptr;

  if (MainMap != nullptr) {
    delete MainMap;
    MainMap = nullptr;
  }

	switch (map_choice) {
  	case '1':
			delete MainFile;
			MainFile = nullptr;
  		break;
  	case '2':
  		delete ConquestMainFile;
  		ConquestMainFile = nullptr;
  		break;
	}



  for (Player *player : ListOfPlayers) {
    if (player != nullptr) {
      delete player;
      player = nullptr;
    }
  }
  this->ListOfValidPlayers.clear();
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
    } else if (NumberOfPlayers < 2 || NumberOfPlayers > 5) {
      std::cout << "Invalid number of players.  Please enter a valid number "
                   "between 2 and 5.\n";
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
    auto *player = new Player();
    // For game loop to keep track of who is left in the game
    ListOfValidPlayers.push_back(player);

    // List of all the players at the start of the game
    ListOfPlayers.push_back(player);
    std::cout << "Please enter player" << i << "'s name: ";
    std::cin >> PlayerName;
    ListOfValidPlayers.at(ListOfValidPlayers.size() - 1)->PID = PlayerName;
  }

  std::cout << "Successfully added" << NumberOfPlayers
            << " Number of Players\n ";

  std::string MapFolderBasePath = "./maps/";
  std::string CmapFolderBasePath = "./cmaps/";
	bool map_type_choice_made = false;
  while (InputMapNotSucceed) {
  	while (!map_type_choice_made) {
			std::cout << "1. Load a Warzone map" << std::endl;
			std::cout << "2. Load a Conquest map" << std::endl;
			std::cout << "Please enter your choice: ";
			std::cin >> map_choice;
			if (map_choice == '1' || map_choice == '2') {
				map_type_choice_made = true;
			} else {
				std::cout << "Invalid choice.  Please try again." << std::endl;
			}
  	}

		Result<void> ReadMapFileResult;
		switch (map_choice) {
  		case '1':
				std::cout << "Now tell me the name of the map you want to load? (must be "
										 "in the ./maps/ directory)\n ";

				std::cin >> MapFileName;

				trim(MapFileName);
				MainFile = new MapFile(MapFolderBasePath + MapFileName);
				ReadMapFileResult = MainFile->readMapFile();
  			break;
  		case '2':
				std::cout << "Now tell me the name of the map you want to load? (must be "
										 "in the ./cmaps/ directory)\n ";

				std::cin >> MapFileName;

				trim(MapFileName);
				ConquestMainFile = new ConquestFileReaderAdapter(CmapFolderBasePath + MapFileName);
				ReadMapFileResult = ConquestMainFile->readMapFile();
  			break;
		}


    if (ReadMapFileResult.success) {

			Result<void> ValidateMapFile;
			switch (map_choice) {
				case '1':
					std::cout << "Map file successfully read: " << MainFile->map_file_name
										<< std::endl;

					// Validate what was read into testMapFile
					ValidateMapFile = MainFile->validate();
					break;
				case '2':
					std::cout << "Map file successfully read: " << ConquestMainFile->map_file_name
										<< std::endl;

					// Validate what was read into testMapFile
					ValidateMapFile = ConquestMainFile->validate();
					break;
			}

      if (ValidateMapFile.success) {
        // Valid items in testMapFile
        // Generate a Map object
				switch (map_choice) {
					case '1':
						MainMap = MainFile->generateMap();
						break;
					case '2':
						MainMap = ConquestMainFile->generateMap();
						break;
				}


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

    //    InputObserver = '1';
    std::cin >> InputObserver;
    //    InputObserver = 'q';
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

  std::list<Observer *> observerList;
  for (auto *player : ListOfValidPlayers) {
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
  for (auto &player : ListOfValidPlayers) {
    player->bindGameElements(this->ListOfValidPlayers, this->MainMap,
                             this->DeckOfCards);
  }

  std::cout << "[GAME START] The following players were created: \n";

  for (auto &p : ListOfValidPlayers) {
    std::cout << "\t" << *p << "\n";
    // TODO implement correct strategies
    // TODO strategy delete is currently handled in player deconstructor
    p->setStrategy(new HumanStrategy());
  }

  std::cout << "[GAME START] The deck of cards has "
            << this->DeckOfCards->GetSize() << " cards\n";
  std::cout << "\nNow the game is ready to go! (≧▽≦)!! \n";

  // -------------------------------------------------------
  // STARTUP PHASE LOOP
  // -------------------------------------------------------
  startupPhase();

  // -------------------------------------------------------
  // MAIN GAME LOOP
  // -------------------------------------------------------
  mainGameLoop();

  // Delete observers
  for (auto &o : observerList) {
    delete o;
    o = nullptr;
  }
}

/**
 * The startup phase initializes the order the players will play in.
 * It also randomly assigns all territories evenly to each player.
 * Each player receives an initial amounts of reinforcements.
 */
void GameEngine::startupPhase() {
  srand(time(NULL));
  // Shuffle the list of players
  std::random_shuffle(ListOfValidPlayers.begin(), ListOfValidPlayers.end());

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
    ListOfValidPlayers.at(rr)->Territories.emplace_back(territory);
    territory->PlayerOwned = ListOfValidPlayers.at(rr);
    territory->OwnedBy = ListOfValidPlayers.at(rr)->PID;

    State new_state;
    new_state.current_state = State_enum::SETUP_PHASE_RECEIVE_TERRITORY;
    ListOfValidPlayers.at(rr)->setState(new_state);
    ListOfValidPlayers.at(rr)->Notify();

    MainMap->ReturnListOfCountries()
        .at(randomizedIDs.at(i))
        ->setState(new_state);
    MainMap->ReturnListOfCountries().at(randomizedIDs.at(i))->Notify();

    rr += 1;
    if (rr == ListOfValidPlayers.size()) {
      rr = 0;
    }
  }

  // give armies to the players based on the number of players in the game
  switch (ListOfValidPlayers.size()) {
    case 2:
      for (int i = 0; i < 2; i++) {
        ListOfValidPlayers.at(i)->ReinforcementPool = 40;
        State new_state;
        new_state.current_state =
            State_enum::SETUP_PHASE_RECEIVE_REINFORCEMENTS;
        new_state.newReinforcements = 40;
        ListOfValidPlayers.at(i)->setState(new_state);
        ListOfValidPlayers.at(i)->Notify();
      }
      break;
    case 3:
      for (int i = 0; i < 3; i++) {
        ListOfValidPlayers.at(i)->ReinforcementPool = 35;
        State new_state;
        new_state.current_state =
            State_enum::SETUP_PHASE_RECEIVE_REINFORCEMENTS;
        new_state.newReinforcements = 35;
        ListOfValidPlayers.at(i)->setState(new_state);
        ListOfValidPlayers.at(i)->Notify();
      }
      break;
    case 4:
      for (int i = 0; i < 4; i++) {
        ListOfValidPlayers.at(i)->ReinforcementPool = 30;
        State new_state;
        new_state.current_state =
            State_enum::SETUP_PHASE_RECEIVE_REINFORCEMENTS;
        new_state.newReinforcements = 30;
        ListOfValidPlayers.at(i)->setState(new_state);
        ListOfValidPlayers.at(i)->Notify();
      }
      break;
    case 5:
      for (int i = 0; i < 5; i++) {
        ListOfValidPlayers.at(i)->ReinforcementPool = 25;
        State new_state;
        new_state.current_state =
            State_enum::SETUP_PHASE_RECEIVE_REINFORCEMENTS;
        new_state.newReinforcements = 25;
        ListOfValidPlayers.at(i)->setState(new_state);
        ListOfValidPlayers.at(i)->Notify();
      }
      break;
  }

  std::cout << "PLAYERS' INFORMATION:" << std::endl;
  std::cout << "----------------------------------------------------"
            << std::endl;

  for (auto &i : ListOfValidPlayers) {
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
  for (int i = 0; i < ListOfValidPlayers.size(); i++) {
    sumOfPlayerOwnedTerritories += ListOfValidPlayers.at(i)->Territories.size();
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
  // DEMO VARIABLE will end game after 10 turns
  bool simulateGameEnd{true};
  bool gameOver{false};

  unsigned long long int round_counter = 0;
  // Loop until a player owns all territories (aka wins the game)
  while (!gameOver) {
    // CHECK: Can we remove any players who have no territories?
    for (unsigned int i = 0; i < ListOfValidPlayers.size(); i++) {
      if (ListOfValidPlayers.at(i)->Territories.empty()) {
        State new_state;
        new_state.current_state = State_enum::PLAYER_ELIMINATED;
        new_state.player_name = ListOfValidPlayers.at(i)->PID;
        // Remove player from game by removing him from the list
        ListOfValidPlayers.erase(ListOfValidPlayers.begin() + i);

        this->setState(new_state);
        this->Notify();
      } else if (simulateGameEnd && round_counter == 30) {
        for (unsigned int i = 0; i < ListOfValidPlayers.size(); i++) {
          ListOfValidPlayers.erase(ListOfValidPlayers.begin() + i);
        }
        auto *playerLeft = ListOfValidPlayers.at(0);
        for (auto &t : this->MainMap->ReturnListOfCountries()) {
          if (t->OwnedBy != playerLeft->PID) {
            t->OwnedBy = playerLeft->PID;
            t->PlayerOwned = playerLeft;
          }
        }
      }
    }

    // CHECK: Do we have a winner?
    if (ListOfValidPlayers.size() == 1) {
      // TODO check this is in the right place
      std::cout << ListOfValidPlayers.at(0)->PID << " has won the game."
                << std::endl;

      gameOver = true;

      State new_state;
      new_state.current_state = State_enum::PLAYER_OWNS_ALL_TERRITORIES;
      new_state.player_name = ListOfValidPlayers.at(0)->PID;

      this->setState(new_state);
      this->Notify();

      break;
    }

    // ----------------------------------
    // GAME PHASES
    // ----------------------------------
    reinforcementPhase();
    issueOrdersPhase();
    executeOrdersPhase();

    round_counter++;
    std::cout << "Finished round: " << round_counter << std::endl;
  }
  std::cout << "Game Finished after " << round_counter << " rounds."
            << std::endl;
}

/**
 * Give a number of armies to players depending on number of territories they
 * own
 */
void GameEngine::reinforcementPhase() {
  std::cout << "\n\n--------------------------\n"
            << "BEGIN REINFORCEMENT PHASE\n\n";
  std::vector<ContinentData *> ListOfContinents =
      MainMap->getListOfContinents();

  for (auto &player : ListOfValidPlayers) {
    int armies = 0;

    // Give armies related to number of territories owned
    auto territories = MainMap->ReturnListOfCountriesOwnedByPlayer(player->PID);
    armies += static_cast<int>(territories.size() / static_cast<long>(3));

    // Give bonus if a player owns a continent
    for (auto *continent : ListOfContinents) {
      if (MainMap->IfPlayerOwnContinent(player->PID, continent->Name)) {
        armies += continent->BonusValue;
      }
    }

    player->ReinforcementPool += armies;

    State new_state;
    new_state.current_state = State_enum::REINFORCEMENT_PHASE;
    new_state.newReinforcements = armies;
    player->setState(new_state);
    player->Notify();
  }

  for (auto &p : ListOfValidPlayers) {
    std::cout << "\t" << p->PID << " now has " << p->ReinforcementPool
              << " armies in his pool\n";
  }

  std::cout << "END OF REINFORCEMENT PHASE\n"
            << "--------------------------\n";
}

/**
 * Players issue orders and place them in their own order list.
 */
void GameEngine::issueOrdersPhase() {
  std::cout << "\n\n--------------------------\n"
            << "BEGIN ORDER ISSUING PHASE\n\n";
  // Initialize issue order phase for each player with helpful flags
  for (auto &player : ListOfValidPlayers) {
    player->initIssueOrder();
  }

  // Initialize each turn with everyone having orders to make
  auto ordersLeft = ListOfValidPlayers.size();

  // Loop until no orders left for each player in same turn
  while (ordersLeft > 0) {
    ordersLeft = ListOfValidPlayers.size();
    for (auto &player : ListOfValidPlayers) {
      if (player->AdvanceOrderDone && player->CardPlayed) {
        // If a player no longer has any order left to make
        ordersLeft--;
      } else {
        std::cout << "\n\t" << player->PID << " issuing order...\n";
        player->issueOrder();

        if (!player->AdvanceOrderDone ||
            (player->AdvanceOrderDone && !player->CardPlayed) ||
            (player->AdvanceOrderDone && player->HandOfCards->size() > 0)) {
          State new_state;
          new_state.current_state = State_enum::ISSUE_ORDERS_PHASE;
          player->setState(new_state);
          player->Notify();
        }
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
  std::cout << "\n\n--------------------------\n"
            << "BEGIN ORDER EXECUTION PHASE\n\n";

  // -- peak() returns nullptr if ListOfOrders is empty --

  // Execute only deploy orders first
  auto ordersLeft = ListOfValidPlayers.size();
  while (ordersLeft > 0) {
    ordersLeft = ListOfValidPlayers.size();
    for (auto &player : ListOfValidPlayers) {
        if (player->ListOfOrders->peek()->getName() == "DEPLOY") {
            State new_phase_state;
            new_phase_state.current_state = State_enum::EXECUTE_ORDERS_PHASE;
            new_phase_state.executed_order_name =
                player->ListOfOrders->peek()->getName();
            std::cout << "\n\t" << player->PID << " executing DEPLOY order\n";
            const bool success = player->ListOfOrders->pop()->execute();
            new_phase_state.execute_order_success = success;

            player->setState(new_phase_state);
            player->Notify();
        }
     else {
        ordersLeft--;
      }
    }
  }

  std::cout << "All deploy orders are finished.\n";

  // Execute other orders by priority
  ordersLeft = ListOfValidPlayers.size();
  while (ordersLeft > 0) {
    ordersLeft = ListOfValidPlayers.size();
    for (auto &player : ListOfValidPlayers) {
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
        std::cout << "\n\t" << player->PID << " executing order\n";
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
      } else {
        ordersLeft--;
      }
    }
  }
  // reset negotiated player list and card given status
  for (auto *player : ListOfValidPlayers) {
    player->set.clear();
    player->cardNotGiven = true;
  }
  std::cout << "END OF ORDER EXECUTION PHASE\n"
            << "--------------------------\n";
}

void GameEngine::displayStatistics() {
  int total_territories = MainMap->NumOfCountries();

  std::cout << "\nGame Statistics: " << std::endl;
  std::cout << "==================================" << std::endl;
  std::cout << "Map Name: " << MainMap->GetMapName() << std::endl;
  std::cout << "Total Territories: " << total_territories << std::endl;
  std::cout << "--------------------------" << std::endl;
  for (auto *player : ListOfValidPlayers) {
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