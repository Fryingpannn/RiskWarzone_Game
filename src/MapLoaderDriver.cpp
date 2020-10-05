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

#include "MapLoader.hpp"
#include <fstream>
#include <iostream>

int main() {
  std::cout << "MapLoaderDriver.cpp" << std::endl;
  std::cout << "By: Stefan Russo - 26683320" << std::endl;
  std::cout << "===========================" << std::endl;

  std::string mapFileName;
  mapFileName = "../maps/bigeurope.map";
  // MapFile *testMapFile;
  MapFile *testMapFile;
  testMapFile = new MapFile("./maps/bigeurope.map");
  // *testMapFile = new MapFile(mapFileName);
  testMapFile->readMapFile();

  return 0;
}
