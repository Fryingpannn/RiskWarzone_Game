/////////////////////////////////////////////
// Filename:        MapLoader.cpp
//
// Description:     MapLoader implementation
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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Map.h"

//////////////////////////////////////////////////////////////////////////////////////
// Continent
//////////////////////////////////////////////////////////////////////////////////////

int Continent::count = 0;

// Default Constructor
/**
 * @brief Construct a new Continent:: Continent object
 *
 */
Continent::Continent() {
    number = 0;
    name = "";
    value = 0;
    colour = "";
};

// Parameterized constructor
/**
 * @brief Construct a new Continent:: Continent object
 *
 * @param new_name
 * @param new_value
 * @param new_colour
 */
Continent::Continent(std::string new_name, int new_value,
                     std::string new_colour) {
    number = ++count;
    name = new_name;
    value = new_value;
    colour = new_colour;
};

/**
 * @brief Construct a new Continent:: Continent object
 *
 * @param other_continent
 */
Continent::Continent(const Continent &other_continent) {
    number = other_continent.number;
    name = other_continent.name;
    value = other_continent.value;
    colour = other_continent.colour;
};

/**
 * @brief Assignment operator overload
 *
 * @param other_continent
 * @return Continent&
 */
Continent &Continent::operator=(const Continent &other_continent) {
    number = other_continent.number;
    name = other_continent.name;
    value = other_continent.value;
    colour = other_continent.colour;

    return *this;
};

/**
 * @brief Stream insertion operator overload
 *
 * @param output
 * @param continent
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &output, const Continent &continent) {
    output << "Continent #: " << continent.number << std::endl;
    output << "Name: " << continent.name << std::endl;
    output << "Value: " << continent.value << std::endl;
    output << "Colour: " << continent.colour << std::endl;

    return output;
};

/**
 * @brief Destroy the Continent:: Continent object
 *
 */
Continent::~Continent(){
    // TODO Territories list
};

//////////////////////////////////////////////////////////////////////////////////////
// Territory
//////////////////////////////////////////////////////////////////////////////////////

// Default Constructor
/**
 * @brief Construct a new Territory:: Territory object
 *
 */
Territory::Territory() {
    number = 0;
    short_name = "";
    continent_number = 0;
    x_coord = 0;
    y_coord = 0;
};

/**
 * @brief Construct a new Territory:: Territory object
 *
 * @param new_number
 * @param new_short_name
 * @param new_continent_number
 * @param new_x_coord
 * @param new_y_coord
 */
Territory::Territory(int new_number, std::string new_short_name,
                     int new_continent_number, int new_x_coord,
                     int new_y_coord) {
    number = new_number;
    short_name = new_short_name;
    continent_number = new_continent_number;
    x_coord = new_x_coord;
    y_coord = new_y_coord;
};

// Copy Constructor
/**
 * @brief Construct a new Territory:: Territory object
 *
 * @param other_territory
 */
Territory::Territory(const Territory &other_territory) {
    number = other_territory.number;
    short_name = other_territory.short_name;
    continent_number = other_territory.continent_number;
    x_coord = other_territory.x_coord;
    y_coord = other_territory.y_coord;
};

// Assignment Operator
/**
 * @brief
 *
 * @param other_territory
 * @return Territory&
 */
Territory &Territory::operator=(const Territory &other_territory) {
    number = other_territory.number;
    short_name = other_territory.short_name;
    continent_number = other_territory.continent_number;
    x_coord = other_territory.x_coord;
    y_coord = other_territory.y_coord;

    return *this;
};

// Stream Insertion Operator
std::ostream &operator<<(std::ostream &output, const Territory &territory) {
    output << "Territory #: " << territory.number << std::endl;
    output << "Short Name: " << territory.short_name << std::endl;
    output << "Continent #: " << territory.continent_number << std::endl;
    output << "Coordinates: ( " << territory.x_coord << " / "
           << territory.y_coord << " )" << std::endl;
    return output;
};

Territory::~Territory(){

};

//////////////////////////////////////////////////////////////////////////////////////
// MapFile
//////////////////////////////////////////////////////////////////////////////////////

// Default Constructor
/**
 * @brief Construct a new Map File:: Map File object
 *
 */
MapFile::MapFile() {
    map_file_name = "";
    pic_file_name = "";
    map_pic_file_name = "";
    cards_file_name = "";
    prv_file_name = "";
}

/**
 * @brief Construct a new Map File:: Map File object
 *
 * @param new_map_file_name
 */
MapFile::MapFile(std::string new_map_file_name) {
    map_file_name = new_map_file_name;
    pic_file_name = "";
    map_pic_file_name = "";
    cards_file_name = "";
    prv_file_name = "";
}

// Copy Constructor
/**
 * @brief Construct a new Map File:: Map File object
 *
 * @param other_map_file
 */
MapFile::MapFile(const MapFile &other_map_file) {
    this->map_file_name = other_map_file.map_file_name;
    this->pic_file_name = other_map_file.pic_file_name;
    this->map_pic_file_name = other_map_file.map_pic_file_name;
    this->cards_file_name = other_map_file.cards_file_name;
    this->prv_file_name = other_map_file.prv_file_name;

    for (auto map_continent : other_map_file.map_continents)
        map_continents.push_back(new Continent(*map_continent));
    for (auto i = 0; i < other_map_file.map_territories.size(); i++)
        map_territories.push_back(
            new Territory(*(other_map_file.map_territories[i])));
};

// Assignment Operator
/**
 * @brief
 *
 * @param other_map_file
 * @return MapFile&
 */
MapFile &MapFile::operator=(const MapFile &other_map_file) {
    this->map_file_name = other_map_file.map_file_name;
    this->pic_file_name = other_map_file.pic_file_name;
    this->map_pic_file_name = other_map_file.map_pic_file_name;
    this->cards_file_name = other_map_file.cards_file_name;
    this->prv_file_name = other_map_file.prv_file_name;

    for (auto i = 0; i < other_map_file.map_continents.size(); i++)
        map_continents.push_back(
            new Continent(*(other_map_file.map_continents[i])));
    for (auto i = 0; i < other_map_file.map_territories.size(); i++)
        map_territories.push_back(
            new Territory(*(other_map_file.map_territories[i])));

    return *this;
};

// Stream insertion operator
/**
 * @brief Stream insertion operator overload
 *
 * @param output
 * @param map_file
 * @return std::ostream&
 */
// TODO Output map_continents and map_territories
std::ostream &operator<<(std::ostream &output, const MapFile *map_file) {
    output << "Map File: " << map_file->map_file_name
           << "\nPic File: " << map_file->pic_file_name
           << "\nMap Pic File: " << map_file->map_pic_file_name
           << "\nCards File: " << map_file->cards_file_name
           << "\nPreview File: " << map_file->prv_file_name;
    return output;
};

// Destructor
/**
 * @brief Destroy the Map File:: Map File object
 *
 */
MapFile::~MapFile() {
    // Delete the territories
    for (auto i = 0; i < this->map_territories.size(); i++) {
        delete (this->map_territories[i]);
        this->map_territories[i] = nullptr;
    }

    // Delete the continents
    for (auto i = 0; i < this->map_continents.size(); i++) {
        delete (this->map_continents[i]);
        this->map_continents[i] = nullptr;
    }
};

/**
 * @brief
 *
 */
void MapFile::readMapFile() {
    std::string current_section = "none";
    // Attempt to open the file.
    std::ifstream inputfilestream(map_file_name);
    if (!inputfilestream.is_open()) {
        std::cerr << "Cound not open map file";
    };
    std::string line = "";

    while (std::getline(inputfilestream, line)) {
        if (!line.empty() && !isStringBlank(line)) {
            trim(line);
            if (line[0] == ';') {
                // Do nothing, this is a commented line
            } else if (line[0] == '[') {
                std::size_t pos = line.find(']');
                current_section = line.substr(1, pos - 1);
            } else {
                // Do things according to what section we're in
                if (current_section == "files") {
                    this->processFileSectionLine(line);
                } else if (current_section == "continents") {
                    this->processContinentSectionLine(line);
                } else if (current_section == "countries") {
                    this->processTerritorySectionLine(line);
                } else if (current_section == "borders") {
                    this->processBordersSectionLine(line);
                }
            }
        }
    }
    inputfilestream.close();
};

/**
 * @brief
 *
 * @param line
 */
// TODO Change this function to return a Result
void MapFile::processFileSectionLine(const std::string line) {
    std::vector<std::string> line_args;
    line_args = split(line, ' ');

    if (line_args.size() == 2) {
        if (toLowerCase(line_args[0]) == "pic") {
            pic_file_name = line_args[1];
        } else if (toLowerCase(line_args[0]) == "map") {
            map_pic_file_name = line_args[1];
        } else if (toLowerCase(line_args[0]) == "crd") {
            cards_file_name = line_args[1];
        } else if (toLowerCase(line_args[0]) == "prv") {
            prv_file_name = line_args[1];
        }
    } else {
        std::cerr << "ERROR: Invalid file section config line: " << line
                  << std::endl;
        exit(-1);
    }
};

/**
 * @brief
 *
 * @param line
 */
// TODO Change this function to return a Result
// TODO Check the success of the std::stoi calls, exit with error if failed
void MapFile::processContinentSectionLine(const std::string line) {
    std::vector<std::string> line_args;
    line_args = split(line, ' ');

    if (line_args.size() == 3) {
        Continent *tempContinent;
        tempContinent =
            new Continent(line_args[0], std::stoi(line_args[1]), line_args[2]);

        map_continents.push_back(tempContinent);
        // delete (tempContinent);
    } else {
        std::cerr << "ERROR: Invalid continent section config line: " << line
                  << std::endl;
        exit(-1);
    }
};

/**
 * @brief
 *
 * @param line
 */
// TODO Change this function to return a Result
// TODO Check the success of the std::stoi calls, exit with error if failed
void MapFile::processTerritorySectionLine(const std::string line) {
    std::vector<std::string> line_args;
    line_args = split(line, ' ');
    if (line_args.size() == 5) {
        Territory *tempTerritory;
        tempTerritory = new Territory(
            std::stoi(line_args[0]), line_args[1], std::stoi(line_args[2]),
            std::stoi(line_args[3]), std::stoi(line_args[4]));
        map_territories.push_back(tempTerritory);
        // delete (tempTerritory);
    } else {
        std::cerr << "ERROR: Invalid file section config line: " << line
                  << std::endl;
        exit(-1);
    }
};

/**
 * @brief
 *
 * @param line
 */
// TODO Change this function to return a Result
// TODO Check the success of the std::stoi calls, exit with error if failed
void MapFile::processBordersSectionLine(const std::string line) {
    std::vector<std::string> line_args;
    line_args = split(line, ' ');

    if (line_args.size() > 1) {
        Result<Territory> result;
        result = getTerritoryByNumber(std::stoi(line_args[0]));
        if (result.success) {
            Territory *tempTerritory;
            tempTerritory = result.returnValue;
            for (int i = 1; i < line_args.size(); i++) {
                int border_territory_number = std::stoi(line_args[i]);
                Result<Territory> secondResult;
                secondResult = getTerritoryByNumber(border_territory_number);
                if (secondResult.success) {
                    tempTerritory->borders.push_back(border_territory_number);
                } else {
                }
            }
        } else {
            std::cerr << result.message << std::endl;
            std::cerr << "ERROR: Invalid territory in borders section: " << line
                      << std::endl;
            exit(-1);
        }
    } else {
        std::cerr << "ERROR: Invalid file section config line: " << line
                  << std::endl;
        exit(-1);
    }
};

/**
 * @brief
 *
 * @param territory_number
 * @return Territory*
 */
Result<Territory> MapFile::getTerritoryByNumber(int territory_number) {
    Result<Territory> returnResult;  // = new Result<Territory>();
    returnResult.success = false;
    returnResult.message =
        &"ERROR: No territory found with index number " [ territory_number];
    returnResult.returnValue = nullptr;

    for (int i = 0; i < map_territories.size(); i++) {
        if (map_territories[i]->number == territory_number) {
            returnResult.success = true;
            returnResult.message = &"SUCCESS: Found territory at index " [ i];
            returnResult.returnValue = map_territories[i];
            return returnResult;
        }
    }
    return returnResult;
};

Result<Continent> MapFile::getContinentByNumber(int continent_number) {
    Result<Continent> returnResult;  // = new Result<Territory>();
    returnResult.success = false;
    returnResult.message =
        &"ERROR: No continent found with index number " [ continent_number];
    returnResult.returnValue = nullptr;

    for (int i = 0; i < map_continents.size(); i++) {
        if (map_territories[i]->number == continent_number) {
            returnResult.success = true;
            returnResult.message = &"SUCCESS: Found continent at index " [ i];
            returnResult.returnValue = map_continents[i];
            return returnResult;
        }
    }
    return returnResult;
}

// /**
//  * @brief
//  *
//  * @param territory_number
//  * @return Territory*
//  */
// Territory *MapFile::getTerritoryByNumber(int territory_number) {
//     int i;
//     for (i = 0; i < map_territories.size(); i++) {
//         if (map_territories[i]->number == territory_number) {
//             return map_territories[i];
//         }
//     }
//     return nullptr;
// };

// Continent *MapFile::getContinentByNumber(int continent_number) {
//     int i;
//     for (i = 0; i < map_continents.size(); i++) {
//         if (map_continents[i]->number == continent_number) {
//             return map_continents[i];
//         }
//     }
//     return nullptr;
// }

// TODO Change return type to Result
struct ::Country *MapFile::generateMapCountry(Territory *territory) {
    Result<Continent> result = getContinentByNumber(territory->continent_number);
    if (result.success) {
        Continent *continent;
        continent = result.returnValue;
        struct ::Country *returnCountry = new struct ::Country();
        returnCountry->Name = territory->short_name;
        returnCountry->CountryID = territory->number;
        returnCountry->Continent = continent->name;
        return returnCountry;
    } else {
        std::cerr << result.message << std::endl;
        std::cerr
            << "ERROR: Invalid Continent ID passed to getContinentByNumber "
               "in MapFile::generateMapCountry()"
            << std::endl;
        exit(-1);
    }
};

// TODO Change return type to Result
Map *MapFile::generateMap() {
    Map *returnMap = new Map(map_territories.size(), map_file_name);
    for (int i = 0; i < map_territories.size(); i++) {
        struct ::Country *base_country;
        base_country = generateMapCountry(map_territories[i]);

        for (int j = 0; j < map_territories[i]->borders.size(); j++) {
            int borderCountry = map_territories[i]->borders[j];
            Result<Territory> secondResult =
                getTerritoryByNumber(borderCountry);
            if (secondResult.success) {
                Territory *secondTerritory;
                secondTerritory = secondResult.returnValue;
                struct ::Country *secondCountry;
                secondCountry = generateMapCountry(secondTerritory);
                returnMap->AddEdges(*base_country, *secondCountry);
            } else {
                std::cerr << "ERROR: Invalid Territory number passed as "
                             "secondCountry in MapFile::generateMap()"
                          << std::endl;
                exit(-1);
            }
        }
    }
    return returnMap;
};

/////////////////////////////////////////////////////////////////////////////////
//
// Miscellaneous String helper Functions
//
/////////////////////////////////////////////////////////////////////////////////

std::string toLowerCase(const std::string toLower) {
    std::string lowerCase = "";
    if (toLower.empty()) return toLower;
    for (int i = 0; i < toLower.length(); i++) {
        lowerCase += tolower(toLower[i]);
    }
    return lowerCase;
};

//////////////////
// Source:
// https://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
void trim(std::string &s) {
    size_t p = s.find_first_not_of("\t\n\v\f\r ");
    s.erase(0, p);

    p = s.find_last_not_of("\t\n\v\f\r ");
    if (std::string::npos != p) s.erase(p + 1);
}
/////////////////

// Returns false if no non-space characters are found
// Returns true otherwise
bool isStringBlank(const std::string line) {
    if (!line.empty()) {
        for (int i = 0; i < line.length(); i++) {
            // Source: https://en.cppreference.com/w/cpp/string/byte/isspace
            if (!std::isspace(static_cast<unsigned char>(line[i]))) {
                return false;
            }
        }
    }
    return true;
};

///////////////////
// Source: https://thispointer.com/how-to-split-a-string-in-c/
std::vector<std::string> split(std::string strToSplit, char delimiter) {
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimiter)) {
        splittedStrings.push_back(item);
    }
    return splittedStrings;
};
///////////////////

//  std::vector<int *> *myVar
//
// std::vector<int*>* p_vec1;
// std::vector<int*>* p_vec2;
// p_vec2->reserve(p_vec1->size());

// for (auto* p_int : *p_vec1) {
//     p_vec2->emplace_back(*p_int);
// }

////////////////////////////

// std::vector<int> *myVar
//
// std::vector<int>* p_vec1;
// auto* p_vec2 = new std::vector<int>{p_vec1->begin(), p_vec1->end()};

// or

// std::vector<int>* p_vec1;
// auto* p_vec2 = new std::vector<int>{*p_vec1};