#include "GameEngine.h"
#include <thread>
#include <chrono>



GameEngine::GameEngine()
{
	Init();
}

GameEngine::~GameEngine()
{
	delete MainMap;
	delete MainFile;
	for (Player* player : ListOfPlayers)
		delete player;
}

void GameEngine::Init()
{
	//The variable for players input
	int NumberOfPlayers;
	bool InputPlayersNotSucceed = true;
	std::string PlayerName;

	//The variable for map input
	std::string MapFileName;
	bool InputMapNotSucceed = true;

	//the variable for observer input
	std::string InputObserver;
	bool InputObserverNotSucceed = true;

	//the main menu for player to setup how many players and the map they want to use :O
	std::cout << "Hey there you little filty general! Welcome to Warzone where you control armies and conquer other countries!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "Now! Now! How many person will be playing this game??"<<std::endl; 
	std::cout << "Or" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout<<	"love to command and conquer?? and trying to end humanity??" << std::endl;
	std::cin >> NumberOfPlayers;
	while (InputPlayersNotSucceed) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please Enter a valid number between 2 and 5 =__=";
			std::cin >> NumberOfPlayers;
		}
		else if (NumberOfPlayers == 1)
		{
			std::cout << "You can't be playing alone... Please get a friend and you need it\n";
			std::cin >> NumberOfPlayers;
		}
		else {
			InputPlayersNotSucceed = false;
		}

	}
	std::cout << "GOOOD!\n";
	Timer(100);
	std::cout << "So you will be playing with "<< NumberOfPlayers<<" Number of Players\n ";
	
	for (int i = 0; i < NumberOfPlayers; i++) {
		Timer(100);
		std::cout << ". " << std::endl;
		ListOfPlayers.push_back(new Player());
		std::cout << "Please enter player" << i << "'s name: ";
		std::cin >> PlayerName;
		ListOfPlayers.at(0)->PID = PlayerName;
	}

	std::cout << "Successfully added" << NumberOfPlayers << " Number of Players\n ";

	
	std::string MapFolderBasePath = "./maps/";
	
	while (InputMapNotSucceed) {
		std::cout << "Now tell me the name of the map you want to load? (must be in the ./maps/ directory)\n ";
		std::cin >> MapFileName;
		trim(MapFileName);
		MainFile = new MapFile(MapFolderBasePath + MapFileName);
		Result<void> ReadMapFileResult = MainFile->readMapFile();
		if (ReadMapFileResult.success) {

			std::cout << "Map file successfully read: " << MainFile->map_file_name << std::endl;

			// Validate what was read into testMapFile
			Result<void> ValidateMapFile = MainFile->validate();
			if (ValidateMapFile.success) {

				// Valid items in testMapFile
				// Generate a Map object

				
				MainMap = MainFile->generateMap();

				// Display the map
				MainMap->Display();

				//only when the map is valid then it will break through the loop
				if (MainMap->Validate()) {
					std::cout << "The map is valid!\n";
					InputMapNotSucceed = false;
				}else {
					std::cout << "Deleting the garbage map...\n";
					delete MainMap;
					MapFileName.clear();
				}
				
			}
			else {
				std::cerr << "ERROR: testMapFile failed validation checks." << ValidateMapFile.message << std::endl;
			}
		}
		else {
			std::cerr << "ERROR: Could not read map file: " << ReadMapFileResult.message << std::endl;
		}
	}

	

	while (InputObserverNotSucceed) {
		std::cout << "Observer on or off? [y/n]\n ";
		std::cin >> InputObserver;

		if (InputObserver == "y") {
			InputObserverNotSucceed = false;
			ObserverOn = true;
		}
		else if (InputObserver == "n") {
			InputObserverNotSucceed = false;
			ObserverOn = false;
		}
		else {
			std::cout << "Please don't troll around =__=\n\n"<<std::endl;
		}
	}

	std::cout << "now the game is ready to go! (≧▽≦)!! \n";



	

}
