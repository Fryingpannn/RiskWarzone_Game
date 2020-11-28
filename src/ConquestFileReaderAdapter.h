//
// Created by stef on 2020-11-23.
//

#ifndef RISKWARZONE_GAME_CONQUESTFILEREADERADAPTER_H
#define RISKWARZONE_GAME_CONQUESTFILEREADERADAPTER_H

#include "ConquestFileReader.h"
#include "MapLoader.hpp"

class ConquestFileReaderAdapter : public MapFile {
public:
		ConquestFileReader conquestFileReader;
		Result<void> readMapFile();
		Result<Continent> getContinentByName(std::string name);
		Result<MapFileTerritory> getTerritoryByName(std::string name);
};


#endif //RISKWARZONE_GAME_CONQUESTFILEREADERADAPTER_H
