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

#include "Map.h"

class Territory;

class Continent;

class MapFile;

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

    // Destructor
    ~Continent();
};

std::ostream &operator<<(std::ostream &output, const Continent &continent);

class Territory {
   public:
    int number;
    std::string short_name;
    int continent_number;
    int x_coord;
    int y_coord;
    std::vector<int> borders;

    static int count;

    // Constructors
    Territory();

    Territory(int new_number, std::string new_short_name,
              int new_continent_number, int new_x_coord, int new_y_coord);

    Territory(const Territory &other_territory);

    // Assignment Operator
    Territory &operator=(const Territory &other_territory);

    // Stream Insertion
    friend std::ostream &operator<<(std::ostream &output,
                                    const Territory &territory);

    ~Territory();
};

std::ostream &operator<<(std::ostream &output, const Territory &territory);

// Struct that can be passed as a parameter, to obtain the success or failure of
// an operation, outside of the return value of the function
template <typename T>
struct Result {
    T *returnValue;
    bool success;
    std::string message;
};

// Class: MapFile
//
// Contains the filename of the map to be loaded, and the data contained within
// the map file.
//
class MapFile {
   public:
    std::string map_file_name;
    std::string pic_file_name;
    std::string map_pic_file_name;
    std::string cards_file_name;
    std::string prv_file_name;
    std::vector<Continent *> map_continents;
    std::vector<Territory *> map_territories;

    // Constructors
    MapFile();

    MapFile(std::string new_map_file_name);

    MapFile(const MapFile &other_map_file);

    MapFile &operator=(const MapFile &other_map_file);

    friend std::ostream &operator<<(std::ostream &output,
                                    const MapFile *map_file);

    void readMapFile();

    void processFileSectionLine(const std::string line);

    void processContinentSectionLine(const std::string line);

    void processTerritorySectionLine(const std::string line);

    void processBordersSectionLine(const std::string line);

    // Territory *getTerritoryByNumber(int territory_number);
    Result<Territory> getTerritoryByNumber(int territory_number);

    // Continent *getContinentByNumber(int continent_number);
    Result<Continent> getContinentByNumber(int continent_number);

    struct ::Country *generateMapCountry(Territory *territory);

    Map *generateMap();

    ~MapFile();
};

std::string toLowerCase(const std::string toLower);

//////////////////
// Source:
// https://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
void trim(std::string &s);
/////////////////

// Returns a bool after checking each char for a space character
bool isStringBlank(const std::string line);

// Source: https://thispointer.com/how-to-split-a-string-in-c/
std::vector<std::string> split(std::string strToSplit, char delimiter);

std::ostream &operator<<(std::ostream &output, const MapFile *map_file);
