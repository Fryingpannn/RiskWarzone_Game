/////////////////////////////////////////////
// Filename:        MapLoaderDriver.cpp
//
// Description:     Driver file to demonstrate the functionality of the
// MapLoader
//
// Author:          Stefan Russo - 26683320
//
// Group:           Sandra Buchen
//                  Le Cherng Lee
//                  Zahra Nikbakht
//                  Matthew Pan
//                  Stefan Russo
//
/////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>

#include "Map.h"
#include "MapLoader.hpp"

void mapLoaderDriver() {
    std::cout << "MapLoaderDriver.cpp" << std::endl;
    std::cout << "By: Stefan Russo - 26683320" << std::endl;
    std::cout << "===========================" << std::endl;

    std::string map_folder_base_path = "./maps/";
    std::string map_file_name;

    std::cout << "Please enter a map file name: ";
    std::cin >> map_file_name;
    trim(map_file_name);

    MapFile *testMapFile;
    testMapFile = new MapFile(map_folder_base_path + map_file_name);
    Result<void> readMapFileResult = testMapFile->readMapFile();
    if (readMapFileResult.success) {
        std::cout << "Map file successfully read: " << testMapFile->map_file_name << std::endl;

        Result<void> validateMapFile = testMapFile->validate();
        if (validateMapFile.success) {
            Result<Map> generateMapResult;
            Map *testMap;
            generateMapResult = testMapFile->generateMap();
            if (generateMapResult.success) {
                testMap = generateMapResult.returnValue;
                testMap->Display();
            } else {
                std::cerr << generateMapResult.message << std::endl;
            }
        } else {
            std::cerr << "ERROR: testMapFile failed validation checks." << validateMapFile.message << std::endl;
        }
    } else {
        std::cerr << "ERROR: Could not read map file: " << readMapFileResult.message << std::endl;
    }

    delete (testMapFile);
    testMapFile = nullptr;
    // return 0;
}
