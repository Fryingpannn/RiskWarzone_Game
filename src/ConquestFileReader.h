//
// Created by stef on 2020-11-23.
//

#ifndef RISKWARZONE_GAME_CONQUESTFILEREADER_H
#define RISKWARZONE_GAME_CONQUESTFILEREADER_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class ConquestTerritory {
public:
		std::string name;
		int x_coord;
		int y_coord;
		std::vector<std::string> adjacent_territories;

		ConquestTerritory();

		ConquestTerritory(std::string n, int x, int y);

		ConquestTerritory(const ConquestTerritory &t);

		ConquestTerritory &operator=(const ConquestTerritory &t);

		friend std::ostream &operator<<(std::ostream &os, const ConquestTerritory &t);

		~ConquestTerritory();
};

class ConquestContinent {
public:
		static int count;
		std::string name;
		int bonus_value;
		std::vector<std::shared_ptr<ConquestTerritory>> territories;

		ConquestContinent();

		ConquestContinent(std::string n, int bv);

		ConquestContinent(const ConquestContinent &c);

		ConquestContinent &operator=(const ConquestContinent &c);

		friend std::ostream &operator<<(std::ostream &os, const ConquestContinent &c);

		~ConquestContinent();
};

class ConquestMap {
public:
		std::string name;
		std::vector<std::shared_ptr<ConquestContinent>> continents;

		ConquestMap();

		ConquestMap(std::string n);

		ConquestMap(const ConquestMap &m);

		ConquestMap &operator=(const ConquestMap &m);

		friend std::ostream &operator<<(std::ostream &os, const ConquestMap &m);

		~ConquestMap();
};

class ConquestFileReader {
public:
		ConquestMap cmap;

		void processTerritoryLine(std::string line);

		void processContinentLine(std::string line);

		void readMapFile(std::string file_name);

		~ConquestFileReader();
};


namespace cfr {
//////////////////
// Source:
// https://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
		void trim(std::string &s);

		std::string toLowerCase(const std::string toLower);

// Returns a bool after checking each char for a space character
		bool isStringBlank(const std::string line);

// Source: https://thispointer.com/how-to-split-a-string-in-c/
		std::vector<std::string> split(std::string strToSplit, char delimiter);
}


#endif //RISKWARZONE_GAME_CONQUESTFILEREADER_H
