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
#include <string>

// Handling file path seperators

#ifdef WIN32
#define OS_SEP '\\'
#else
#define OS_SEP '/'
#endif


int main() {
  std::cout << "MapLoaderDriver.cpp" << std::endl;
  std::cout << "By: Stefan Russo - 26683320" << std::endl;
  std::cout << "===========================" << std::endl;
  
  std::string map_folder_base_path = "./maps/";
  // MapFile *testMapFile;
  MapFile *testMapFile;
  testMapFile = new MapFile(map_folder_base_path + "bigeurope.map");
  // *testMapFile = new MapFile(mapFileName);
  testMapFile->readMapFile();

  std::cout << testMapFile->map_file_name << std::endl;

  delete(testMapFile);
  return 0;
}
