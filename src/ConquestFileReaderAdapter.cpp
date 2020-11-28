//
// Created by stef on 2020-11-23.
//

#include "ConquestFileReaderAdapter.h"
#include "MapLoader.hpp"

Result<void> ConquestFileReaderAdapter::readMapFile() {
	// Set the default return error
	Result<void> returnResult;
	returnResult.success = false;
	returnResult.message = "ERROR: Default failure message. This should not have happened. ConquestFileReaderAdapter::readMapFile()";

	std::string conquest_file_name = map_file_name;
	try {
		conquestFileReader.readMapFile(conquest_file_name);
	} catch (const char *msg) {
		returnResult.success = false;
		returnResult.message = msg;
		return returnResult;
	} catch (const std::invalid_argument &ia) {
		returnResult.success = false;
		returnResult.message = ia.what();
	} catch (const std::out_of_range &oor) {
		returnResult.success = false;
		returnResult.message = oor.what();
	}

	// Create continents from cmap.continents
	map_file_name = conquestFileReader.cmap.name;
	Continent::count = 0;
	for (std::shared_ptr<ConquestContinent> c : conquestFileReader.cmap.continents) {
		Continent *newContient = new Continent(c->name, c->bonus_value, "green");
		map_continents.push_back(newContient);
	}

	int territory_count = 0;
	// Loop through the continents to add their territories to map_territories.
	for (const std::shared_ptr<ConquestContinent> &c : conquestFileReader.cmap.continents) {
		Result<Continent> tempContinent = getContinentByName(c->name);
		if (tempContinent.success) {
			int continent_number = tempContinent.returnValue->number;

			for (std::shared_ptr<ConquestTerritory> t : c->territories) {
				MapFileTerritory *tempTerritory = new MapFileTerritory(territory_count++, t->name, continent_number, 0, 0);
				map_territories.push_back(tempTerritory);
			}
		} else {
			returnResult.success = false;
			returnResult.message = tempContinent.message;
			return returnResult;
		}
	}

	// Loop through continents again to process territory borders
	for (const std::shared_ptr<ConquestContinent> &c : conquestFileReader.cmap.continents) {
		for (const std::shared_ptr<ConquestTerritory> &t : c->territories) {
			Result<MapFileTerritory> mainTerritory = getTerritoryByName(t->name);
			if(mainTerritory.success) {
				for (std::string adjacentTerritoryName : t->adjacent_territories) {
					Result<MapFileTerritory> adjacentTerritory = getTerritoryByName(adjacentTerritoryName);
					if (adjacentTerritory.success) {
						mainTerritory.returnValue->borders.push_back(adjacentTerritory.returnValue->number);
					} else {
						returnResult.success = false;
						returnResult.message = "ERROR: Invalid territory in conquestTerritories list.";
						return returnResult;
					}
				}
			} else {
				returnResult.success = false;
				returnResult.message = "ERROR: Invalid territory in conquestTerritories list.";
				return returnResult;
			}
		}
	}

	returnResult.success = true;
	returnResult.message = "Succesfully converted ConquestMapReader data to MapFile format data.";
	return returnResult;
}


Result<Continent> ConquestFileReaderAdapter::getContinentByName(std::string name) {
	Result<Continent> returnResult;
	returnResult.success = false;
	returnResult.message = "ERROR: No continent found with name \"" + name + "\"";
	returnResult.returnValue = nullptr;

	for (unsigned int i = 0; i < map_continents.size(); i++) {
		if (toLowerCase(map_continents[i]->name) == name) {
			returnResult.success = true;
			returnResult.message = &"SUCCESS: Found continent at index "[i];
			returnResult.returnValue = map_continents[i];
			return returnResult;
		}
	}
	return returnResult;
}

Result<MapFileTerritory> ConquestFileReaderAdapter::getTerritoryByName(std::string name) {
	Result<MapFileTerritory> returnResult;
	returnResult.success = false;
	returnResult.message = "ERROR: No territory found with name \"" + name + "\"";
	returnResult.returnValue = nullptr;

	for (unsigned int i = 0; i < map_territories.size(); i++) {
		if (toLowerCase(map_territories[i]->short_name) == name) {
			returnResult.success = true;
			returnResult.message = &"SUCCESS: Found territory at index "[i];
			returnResult.returnValue = map_territories[i];
			return returnResult;
		}
	}
	return returnResult;
}
