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
    testMapFile->readMapFile();

    std::cout << testMapFile->map_file_name << std::endl;
    // for (int i = 0; i < testMapFile->map_continents.size(); i++) {
    //   std::cout << *testMapFile->map_continents[i] << std::endl;
    // }

    // for (int i = 0; i < testMapFile->map_territories.size(); i++) {
    //   // std::cout << *testMapFile->map_territories[i] << std::endl;
    //   struct::Country firstCountry;
    //   Territory *firstTerritory;
    //   firstTerritory = testMapFile->map_territories[i];
    //   firstCountry = testMapFile->generateMapCountry(firstTerritory);

    //   for(int j = 0; j < testMapFile->map_territories[i]->borders.size();
    //   j++) {
    //     int borderCountry = testMapFile->map_territories[i]->borders[j];
    //     Territory *secondTerritory;
    //     secondTerritory = testMapFile->getTerritoryByNumber(borderCountry);
    //     struct::Country secondCountry;
    //     firstCountry = testMapFile->generateMapCountry(secondTerritory);
    //   }
    // }

    Map *testMap;
    testMap = testMapFile->generateMap();
    testMap->Display();

    delete (testMapFile);
    testMapFile = nullptr;
    // return 0;
}
