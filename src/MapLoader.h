/////////////////////////////////////////////
// Filename:        MapLoader.h
//
// Description:     Header file for MapLoader.cpp
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

#pragma once

#include <string>
#include <vector>

// Class: Continent
//
// Contains the data for each continent
class Continent {
public:
  int number;
  std::string name;
  int value;
  std::string colour;
  static int count;

  // Constructors
  Continent();
  Continent(std::string new_name, int new_value, std::string new_colour);
  Continent(const Continent &other_continent);

  // Assignment Operator
  Continent &operator=(const Continent &other_continent);

  // Stream Insertion
  friend std::ostream &operator<<(std::ostream &output,
                                  const Continent &continent);

  ~Continent();
};

std::ostream &operator<<(std::ostream &output, const Continent &continent);

class Country {
public:
  int number;
  std::string short_name;
  int continent_number;
  int x_coord;
  int y_coord;
  std::vector<int> borders;

  // Constructors
  Country();
  Country(int new_number, std::string new_short_name, int new_continent_number,
          int new_x_coord, int new_y_coord);
  Country(const Country &other_country);

  // Assignment Operator
  Country &operator=(const Country &other_country);

  // Stream Insertion
  friend std::ostream &operator<<(std::ostream &output, const Country &country);

  ~Country();
};

std::ostream &operator<<(std::ostream &output, const Country &country);

// class Borders {
// public:
//   int country_number;
//   std::vector<int> borders;

//   // Constructors
//   Borders();
//   Borders(int country_number);
//   Borders(const Borders &other_borders);

//   // Assignment Operator
//   Borders &operator=(const Borders &other_borders);

//   // Stream Insertion
//   friend std::ostream &operator<<(std::ostream &output, const Borders &borders);

//   ~Borders();
// };

// std::ostream &operator<<(std::ostream &output, const Borders &borders);

// Struct that can be passed as a parameter to obtain the success or failure of
// an operation, outside of the return value of the function
struct Result {
public:
  bool success;
  std::string message;
};

// Class: MapFile
//
// Contains the filename of the map to be loaded, and the data contained within
// the mapfile.
//
class MapFile {
public:
  std::string map_file_name;
  std::string pic_file_name;
  std::string map_pic_file_name;
  std::string cards_file_name;
  std::string prv_file_name;
  std::vector<Continent *> map_continents;
  std::vector<Country *> map_countries;
  // std::vector<Borders *> map_borders;

  // Constructors
  MapFile();
  MapFile(std::string new_map_file_name);
  MapFile(const MapFile &other_map_file);

  MapFile &operator=(const MapFile &other_map_file);
  MapFile &operator=(std::string new_map_file_name);

  friend std::ostream &operator<<(std::ostream &output,
                                  const MapFile *map_file);

  void readMapFile();
  void processFileSectionLine(const std::string line);
  void processContinentSectionLine(const std::string line);
  void processCountrySectionLine(const std::string line);
  void processBordersSectionLine(const std::string line);

  Country* getCountryByNumber(int country_number);

  ~MapFile();
};


std::string toLowerCase(const std::string toLower);

//////////////////
// Source: https://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
void trim(std::string &s);
/////////////////


// Returns a bool after checking each char for a space character
bool isStringblank(const std::string line);

// Source: https://thispointer.com/how-to-split-a-string-in-c/
std::vector<std::string> split(std::string strToSplit, char delimeter);

std::ostream &operator<<(std::ostream &output, const MapFile *map_file);

// Class Requirements
//
// Default constructor
// Parameterized constructor
// Copy constructor
// Assignment operator
// Stream insertion operator

// Functions
//
// File Reader
// Line splitter (splits the line that's read and returns a std::vector
// containing the elements)
