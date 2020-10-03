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

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>


////////////////////////////////
// Continent
////////////////////////////////

// Default Constructor
Continent::Continent()
{
    number = 0;
    name = "";
    value = 0;
    colour = "";
};

// Parameterized constructor
Continent::Continent(int new_number, std::string new_name, int new_value, int new_colour)
{
    number = new_number;
    name = new_name;
    value = new_value;
    colour = new_colour;
};

Continent::Continent(const Continent &other_continent)
{
    number = other_continent.number;
    name = other_continent.name;
    value = other_continent.value;
    colour = other_continent.colour;
};

Continent &Continent::operator=(const Continent &other_continent)
{
    number = other_continent.number;
    name = other_continent.name;
    value = other_continent.value;
    colour = other_continent.colour;
};

std::ostream &operator<<(std::ostream &output, const Continent &continent)
{
    return output << "#" << continent.number << " - " << continent.name;
};

////////////////////////////////
// Country
////////////////////////////////

// Default Constructor
Country::Country()
{
    number = 0;
    short_name = "";
    continent_number = 0;
    x_coord = 0;
    y_coord = 0;
};

Country::Country(int new_number, std::string new_short_name, int new_continent_number, int new_x_coord, int new_y_coord)
{
    number = new_number;
    short_name = new_short_name;
    continent_number = new_continent_number;
    x_coord = new_x_coord;
    y_coord = new_y_coord;
};

Country::Country(const Country &other_country)
{
    number = other_country.number;
    short_name = other_country.short_name;
    continent_number = other_country.continent_number;
    x_coord = other_country.x_coord;
    y_coord = other_country.y_coord;
};

Country &Country::operator=(const Country &other_country)
{
    number = other_country.number;
    short_name = other_country.short_name;
    continent_number = other_country.continent_number;
    x_coord = other_country.x_coord;
    y_coord = other_country.y_coord;
};

std::ostream &operator<<(std::ostream &output, const Country &country)
{
    return output << "#" << country.number << " - " << country.short_name;
};

////////////////////////////////
// Borders
////////////////////////////////
Borders::Borders()
{
    country_number = 0;
};

Borders::Borders(int country_number)
{
    this->country_number = country_number;
    // std::vector<int> *borders;
};

Borders::Borders(const Borders &other_borders)
{
    this->country_number = other_borders.country_number;

    // TODO: Deep copy the borders vector
    // for(int i = 0; i < *other_borders.borders.size(); i++) {
    //     *this->borders->push_back()
    // };

    // std::copy(other_borders->borders->begin(), *other_borders.borders->end(), std::back_inserter(this->borders));
};

Borders &Borders::operator=(const Borders &other_borders)
{
    this->country_number = other_borders.country_number;

    // TODO: Deep copy the borders vector
    // std::copy(*other_borders.borders->begin(), *other_borders.borders->end(), std::back_inserter(this->borders));
};

std::ostream &operator<<(std::ostream &output, const Borders &borders)
{
    // output << "Country: " << borders.country_number << " Borders: [" << borders.borders;
    return output;
};

////////////////////////////////
// MapFile
////////////////////////////////

MapFile::MapFile()
{
    // map_file_name = new std::String ("");
    // pic_file_name = "";
    // map_pic_file_name = "";
    // cards_file_name = "";
    // prv_file_name = "";
}

MapFile::MapFile(std::string new_map_file_name)
{
    map_file_name = new_map_file_name;
    pic_file_name = "";
    map_pic_file_name = "";
    cards_file_name = "";
    prv_file_name = "";
}

MapFile &MapFile::operator=(std::string new_map_file_name)
{
    this->map_file_name = new_map_file_name;
    pic_file_name = "";
    map_pic_file_name = "";
    cards_file_name = "";
    prv_file_name = "";

    // std::copy(*other_map_file.map_continents->begin(), *other_map_file.map_continents->end(), std::back_inserter(*this->map_continents));
    // std::copy(*other_map_file.map_countries->begin(), *other_map_file.map_countries->end(), std::back_inserter(*this->map_countries));
    // std::copy(*other_map_file.map_borders->begin(), *other_map_file.map_borders->end(), std::back_inserter(*this->map_borders));
};

MapFile::MapFile(const MapFile &other_map_file)
{
    this->map_file_name = other_map_file.map_file_name;
    this->pic_file_name = other_map_file.pic_file_name;
    this->map_pic_file_name = other_map_file.map_pic_file_name;
    this->cards_file_name = other_map_file.cards_file_name;
    this->prv_file_name = other_map_file.prv_file_name;

    // std::copy(*other_map_file.map_continents->begin(), *other_map_file.map_continents->end(), std::back_inserter(*this->map_continents));
    // std::copy(*other_map_file.map_countries->begin(), *other_map_file.map_countries->end(), std::back_inserter(*this->map_countries));
    // std::copy(*other_map_file.map_borders->begin(), *other_map_file.map_borders->end(), std::back_inserter(*this->map_borders));
};

MapFile &MapFile::operator=(const MapFile &other_map_file)
{
    this->map_file_name = other_map_file.map_file_name;
    this->pic_file_name = other_map_file.pic_file_name;
    this->map_pic_file_name = other_map_file.map_pic_file_name;
    this->cards_file_name = other_map_file.cards_file_name;
    this->prv_file_name = other_map_file.prv_file_name;

    // std::copy(*other_map_file.map_continents->begin(), *other_map_file.map_continents->end(), std::back_inserter(*this->map_continents));
    // std::copy(*other_map_file.map_countries->begin(), *other_map_file.map_countries->end(), std::back_inserter(*this->map_countries));
    // std::copy(*other_map_file.map_borders->begin(), *other_map_file.map_borders->end(), std::back_inserter(*this->map_borders));
};

std::ostream &operator<<(std::ostream &output, const MapFile *map_file)
{
    output << "Map File: " << map_file->map_file_name;
    return output;
};

Result MapFile::readMapFile()
{
    // Declare our return result object
    Result *return_result;

    return_result->success = true; // Default return
    return_result->message = "Default result message value";

    // Attempt to open the file.
    std::ifstream inputfilestream(map_file_name);
    if (!inputfilestream.is_open())
    {
        std::cerr << "Cound not open map file";
        return_result->success = false;
        return_result->message = "ERROR: Could Not Open File: " + map_file_name;
        return *return_result;
    };

    std::string line = "";
    while (std::getline(inputfilestream, line))
    {
        std::cout << line << std::endl;
    }

    return_result->success = true;
    return_result->message = "Opened file successfully";

    return *return_result;
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