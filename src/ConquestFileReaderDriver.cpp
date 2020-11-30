//
// Created by stef on 2020-11-28.
//

#include "ConquestFileReaderDriver.h"
#include "MapLoader.hpp"
#include "Map.h"

#include <iostream>
#include <string>

void a3_part2_demo() {
	std::cout << "ConquestFileReaderDriver.cpp" << std::endl;
	std::cout << "============================" << std::endl;

	std::string map_folder_base_path;
	std::string map_file_name;

	MapFile *testMapFile = nullptr;
	ConquestFileReaderAdapter *testCmapFile = nullptr;

	bool choice_made = false;
	char choice;
	while (!choice_made) {
		std::cout << "1. Load a Warzone map" << std::endl;
		std::cout << "2. Load a Conquest map" << std::endl;
		std::cout << "Please enter your choice: ";
		std::cin >> choice;
		if (choice == '1' || choice == '2') {
			choice_made = true;
		} else {
			std::cout << "Invalid choice.  Please try again." << std::endl;
		}
	}

	switch (choice) {
		case '1':
			map_folder_base_path = "./maps/";
			std::cout << "Please enter a map file name (must be in the ./maps/ directory): ";
			break;
		case '2':
			map_folder_base_path = "./cmaps/";
			std::cout << "Please enter a map file name (must be in the ./cmaps/ directory): ";
			break;
		default:
			break;
	}

	std::cin >> map_file_name;
	trim(map_file_name);

	Result<void> readMapFileResult;
	switch (choice) {
		case '1':
			testMapFile = new MapFile(map_folder_base_path + map_file_name);
			readMapFileResult = testMapFile->readMapFile();
			break;
		case '2':
			testCmapFile = new ConquestFileReaderAdapter(map_folder_base_path + map_file_name);
			readMapFileResult = testCmapFile->readMapFile();
			break;
		default:
			break;
	}



	if (readMapFileResult.success) {
		Result<void> validateMapFile;
		switch (choice) {
			case '1':
				std::cout << "Map file successfully read: " << testMapFile->map_file_name << std::endl;
				validateMapFile = testMapFile->validate();
				break;
			case '2':
				std::cout << "Map file successfully read: " << testCmapFile->map_file_name << std::endl;
				validateMapFile = testCmapFile->validate();
				break;
		}


		// Validate what was read into testMapFile

		if (validateMapFile.success) {

			// Valid items in testMapFile
			// Generate a Map object

			//testMapFile->generateMap();

			/*
			* Yes, this code is commented out.  For some unknown reason, testMap and
			* testMapFile are instantly deleted and we cannot figure out why that's happening.
			*/
			Map *testMap = nullptr;
			switch (choice) {
				case '1':
					testMap = testMapFile->generateMap();
					break;
				case '2':
					testMap = testCmapFile->generateMap();
					break;
			}


			// Display the map
			testMap->Display();
			delete testMap;
		} else {
			std::cerr << "ERROR: testMapFile failed validation checks." << validateMapFile.message << std::endl;
		}
	} else {
		std::cerr << "ERROR: Could not read map file: " << readMapFileResult.message << std::endl;
	}


	switch (choice) {
		case '1':
			delete testMapFile;
			testMapFile = nullptr;
			break;
		case '2':
			delete testCmapFile;
			testCmapFile = nullptr;
			break;
	}


}