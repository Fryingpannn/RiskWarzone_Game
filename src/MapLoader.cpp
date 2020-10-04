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

#include "MapLoader.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

////////////////////////////////
// Continent
////////////////////////////////

int Continent::count = 0;

// Default Constructor
Continent::Continent() {
  number = 0;
  name = "";
  value = 0;
  colour = "";
};

// Parameterized constructor
Continent::Continent(std::string new_name, int new_value,
                     std::string new_colour) {
  number = ++count;
  name = new_name;
  value = new_value;
  colour = new_colour;
};

Continent::Continent(const Continent &other_continent) {
  number = other_continent.number;
  name = other_continent.name;
  value = other_continent.value;
  colour = other_continent.colour;
};

Continent &Continent::operator=(const Continent &other_continent) {
  number = other_continent.number;
  name = other_continent.name;
  value = other_continent.value;
  colour = other_continent.colour;
  return *this;
};

std::ostream &operator<<(std::ostream &output, const Continent &continent) {
  return output << "#" << continent.number << " - " << continent.name;
};

////////////////////////////////
// Country
////////////////////////////////

// Default Constructor
Country::Country() {
  number = 0;
  short_name = "";
  continent_number = 0;
  x_coord = 0;
  y_coord = 0;
};

Country::Country(int new_number, std::string new_short_name,
                 int new_continent_number, int new_x_coord, int new_y_coord) {
  number = new_number;
  short_name = new_short_name;
  continent_number = new_continent_number;
  x_coord = new_x_coord;
  y_coord = new_y_coord;
};

Country::Country(const Country &other_country) {
  number = other_country.number;
  short_name = other_country.short_name;
  continent_number = other_country.continent_number;
  x_coord = other_country.x_coord;
  y_coord = other_country.y_coord;
};

Country &Country::operator=(const Country &other_country) {
  number = other_country.number;
  short_name = other_country.short_name;
  continent_number = other_country.continent_number;
  x_coord = other_country.x_coord;
  y_coord = other_country.y_coord;

  return *this;
};

std::ostream &operator<<(std::ostream &output, const Country &country) {
  return output << "#" << country.number << " - " << country.short_name;
};

////////////////////////////////
// Borders
////////////////////////////////
// Borders::Borders() { country_number = 0; };

// Borders::Borders(int country_number) {
//   this->country_number = country_number;
//   // std::vector<int> borders;
// };

// Borders::Borders(const Borders &other_borders) {
//   this->country_number = other_borders.country_number;

//   // TODO: Deep copy the borders vector
//   // std::copy(other_borders->borders->begin(), *other_borders.borders->end(),
//   // std::back_inserter(this->borders));
// };

// Borders &Borders::operator=(const Borders &other_borders) {
//   this->country_number = other_borders.country_number;

//   // TODO: Deep copy the borders vector
//   // std::copy(*other_borders.borders->begin(), *other_borders.borders->end(),
//   // std::back_inserter(this->borders));

//   return *this;
// };

// std::ostream &operator<<(std::ostream &output, const Borders &borders) {
//   // output << "Country: " << borders.country_number << " Borders: [" <<
//   // borders.borders;
//   return output;
// };

////////////////////////////////
// MapFile
////////////////////////////////

MapFile::MapFile() {
  map_file_name = "";
  pic_file_name = "";
  map_pic_file_name = "";
  cards_file_name = "";
  prv_file_name = "";
}

MapFile::MapFile(std::string new_map_file_name) {
  map_file_name = new_map_file_name;
  pic_file_name = "";
  map_pic_file_name = "";
  cards_file_name = "";
  prv_file_name = "";
}

MapFile &MapFile::operator=(std::string new_map_file_name) {
  this->map_file_name = new_map_file_name;
  pic_file_name = "";
  map_pic_file_name = "";
  cards_file_name = "";
  prv_file_name = "";

  // std::copy(*other_map_file.map_continents->begin(),
  // *other_map_file.map_continents->end(),
  // std::back_inserter(*this->map_continents));
  // std::copy(*other_map_file.map_countries->begin(),
  // *other_map_file.map_countries->end(),
  // std::back_inserter(*this->map_countries));
  // std::copy(*other_map_file.map_borders->begin(),
  // *other_map_file.map_borders->end(),
  // std::back_inserter(*this->map_borders));

  return *this;
};

MapFile::MapFile(const MapFile &other_map_file) {
  this->map_file_name = other_map_file.map_file_name;
  this->pic_file_name = other_map_file.pic_file_name;
  this->map_pic_file_name = other_map_file.map_pic_file_name;
  this->cards_file_name = other_map_file.cards_file_name;
  this->prv_file_name = other_map_file.prv_file_name;

  // std::copy(*other_map_file.map_continents->begin(),
  // *other_map_file.map_continents->end(),
  // std::back_inserter(*this->map_continents));
  // std::copy(*other_map_file.map_countries->begin(),
  // *other_map_file.map_countries->end(),
  // std::back_inserter(*this->map_countries));
  // std::copy(*other_map_file.map_borders->begin(),
  // *other_map_file.map_borders->end(),
  // std::back_inserter(*this->map_borders));
};

MapFile &MapFile::operator=(const MapFile &other_map_file) {
  this->map_file_name = other_map_file.map_file_name;
  this->pic_file_name = other_map_file.pic_file_name;
  this->map_pic_file_name = other_map_file.map_pic_file_name;
  this->cards_file_name = other_map_file.cards_file_name;
  this->prv_file_name = other_map_file.prv_file_name;

  // std::copy(*other_map_file.map_continents->begin(),
  // *other_map_file.map_continents->end(),
  // std::back_inserter(*this->map_continents));
  // std::copy(*other_map_file.map_countries->begin(),
  // *other_map_file.map_countries->end(),
  // std::back_inserter(*this->map_countries));
  // std::copy(*other_map_file.map_borders->begin(),
  // *other_map_file.map_borders->end(),
  // std::back_inserter(*this->map_borders));

  return *this;
};

std::ostream &operator<<(std::ostream &output, const MapFile *map_file) {
  output << "Map File: " << map_file->map_file_name
         << "\nPic File: " << map_file->pic_file_name
         << "\nMap Pic File: " << map_file->map_pic_file_name
         << "\nCards File: " << map_file->cards_file_name
         << "\nPreview File: " << map_file->prv_file_name;
  return output;
};

void MapFile::readMapFile() {

  std::string current_section = "none";
  // Attempt to open the file.
  std::ifstream inputfilestream(map_file_name);
  if (!inputfilestream.is_open()) {
    std::cerr << "Cound not open map file";
  };
  std::string line = "";

  while (std::getline(inputfilestream, line)) {
    if (!line.empty() && !isStringblank(line)) {
      trim(line);
      if (line[0] == ';') {
        // Do nothing, this is a commented line
      } else if (line[0] == '[') {
        std::size_t pos = line.find(']');
        current_section = line.substr(1, pos - 1);
        // std::cout << "Section detected: " << current_section << std::endl;
      } else {
        if (current_section == "files") {
          this->processFileSectionLine(line);
        } else if (current_section == "continents") {
          this->processContinentSectionLine(line);
        } else if (current_section == "countries") {
          this->processCountrySectionLine(line);
        } else if (current_section == "borders") {
          this->processBordersSectionLine(line);
        }
      }
    }
  }
};

void MapFile::processFileSectionLine(const std::string line) {

  std::vector<std::string> line_args;
  line_args = split(line, ' ');

  if (line_args.size() == 2) {
    // std::cout << "Found File Line - Size: " << line_args.size() << "
    // "
    //           << line_args[0] << " " << toLowerCase(line_args[0])
    //           << std::endl;
    if (toLowerCase(line_args[0]) == "pic") {
      pic_file_name = line_args[1];
    } else if (toLowerCase(line_args[0]) == "map") {
      map_pic_file_name = line_args[1];
    } else if (toLowerCase(line_args[0]) == "crd") {
      cards_file_name = line_args[1];
    } else if (toLowerCase(line_args[0]) == "prv") {
      prv_file_name = line_args[1];
    }
    // std::cout << this << std::endl;
    // std::cout << "=======" << std::endl;
  } else {
    std::cerr << "Invalid file section config line: " << line << std::endl;
  }
};

void MapFile::processContinentSectionLine(const std::string line) {
  std::vector<std::string> line_args;
  line_args = split(line, ' ');

  // std::cout << "Found Continents Line - Size: " << line_args.size()
  //           << std::endl;
  if (line_args.size() == 3) {
    Continent *tempContinent;
    tempContinent =
        new Continent(line_args[0], std::stoi(line_args[1]), line_args[2]);

    map_continents.push_back(tempContinent);
    // std::cout << "Name: '" << line_args[0] << "'" << std::endl;
    // std::cout << "Value: '" << std::stoi(line_args[1]) << "'" <<
    // std::endl; std::cout << "Colour: '" << line_args[2] << "'" <<
    // std::endl;
    // std::cout << "# Continents: " << Continent::count << std::endl;
  } else {
    std::cerr << "Invalid file section config line: " << line << std::endl;
  }
};

void MapFile::processCountrySectionLine(const std::string line) {
  std::vector<std::string> line_args;
  line_args = split(line, ' ');
  // std::cout << "Found Countries Line - Size: " << line_args.size()
  //           << std::endl;
  if (line_args.size() == 5) {
    Country *tempCountry;
    tempCountry = new Country(std::stoi(line_args[0]), line_args[1],
                              std::stoi(line_args[2]), std::stoi(line_args[3]),
                              std::stoi(line_args[4]));
    map_countries.push_back(tempCountry);
  } else {
    std::cerr << "Invalid file section config line: " << line << std::endl;
  }
};

void MapFile::processBordersSectionLine(const std::string line) {
  std::vector<std::string> line_args;
  line_args = split(line, ' ');

  // std::cout << "Found Borders Line - Size: " << line_args.size()
  //           << std::endl;
  if (line_args.size() > 1) {
    Country *tempCountry;
    tempCountry = getCountryByNumber(std::stoi(line_args[0])); 
    for (int i = 1; i < line_args.size(); i++) {
      tempCountry->borders.push_back(std::stoi(line_args[i]));
    }
    // this->map_borders.push_back(tempBorders);
  } else {
    std::cerr << "Invalid file section config line: " << line << std::endl;
  }
};

Country* MapFile::getCountryByNumber(int country_number)
{
  int i;
  for (i = 0; i < map_countries.size(); i++) {
    if (map_countries[i]->number == country_number) {
      return map_countries[i];
    }
  }
  return nullptr;
};

std::string toLowerCase(const std::string toLower) {
  std::string lowerCase = "";
  if (toLower.empty())
    return toLower;
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
  if (std::string::npos != p)
    s.erase(p + 1);
}
/////////////////

// Returns false if no non-space characters are found
// Returns true otherwise
bool isStringblank(const std::string line) {
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

// Source: https://thispointer.com/how-to-split-a-string-in-c/
std::vector<std::string> split(std::string strToSplit, char delimeter) {
  std::stringstream ss(strToSplit);
  std::string item;
  std::vector<std::string> splittedStrings;
  while (std::getline(ss, item, delimeter)) {
    splittedStrings.push_back(item);
  }
  return splittedStrings;
};

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