#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>

class Continent {
    int number;
    string name;
    int value;
    string colour;
};

class Country {
    int number;
    string short_name;
    int continent_number;
    int x_coord;
    int y_coord;
    vector<int> borders;
};

class MapFile {
    string pic_file_name;
    string map_file_name;
    string cards_file_name;
    string prv_file_name;
};

#endif // MAPLOADER_H

