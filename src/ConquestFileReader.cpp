//
// Created by stef on 2020-11-23.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "ConquestFileReader.h"

/////////////////////////////
// Globals
/////////////////////////////
std::string exceptionMessage;

/////////////////////////////
// ConquestTerritory class
/////////////////////////////

ConquestTerritory::ConquestTerritory() {
	name = "none";
	x_coord = 0;
	y_coord = 0;
}

ConquestTerritory::ConquestTerritory(std::string n, int x, int y) {
	name = n;
	x_coord = x;
	y_coord = y;
}

ConquestTerritory::ConquestTerritory(const ConquestTerritory &t) {
	name = t.name;
	x_coord = t.x_coord;
	y_coord = t.y_coord;
	adjacent_territories = t.adjacent_territories;
}

ConquestTerritory &ConquestTerritory::operator=(const ConquestTerritory &t) {
	name = t.name;
	x_coord = t.x_coord;
	y_coord = t.y_coord;
	adjacent_territories = t.adjacent_territories;
	return *this;
}

ConquestTerritory::~ConquestTerritory() {

}

std::ostream &operator<<(std::ostream &os, const ConquestTerritory &t) {
	os << "Name: " << t.name << " (" << t.x_coord << "," << t.y_coord << ")";
	return os;
}

/////////////////////////////
// ConquestContinent class
/////////////////////////////

int ConquestContinent::count = 0;

ConquestContinent::ConquestContinent() {
	name = "none";
	bonus_value = 0;
	count++;
}

ConquestContinent::ConquestContinent(std::string n, int bv) {
	name = n;
	bonus_value = bv;
	count++;
}

ConquestContinent::ConquestContinent(const ConquestContinent &c) {
	name = c.name;
	bonus_value = c.bonus_value;
	territories = c.territories;
	count++;
}

ConquestContinent &ConquestContinent::operator=(const ConquestContinent &c) {
	name = c.name;
	bonus_value = c.bonus_value;
	territories = c.territories;
	count++;
	return *this;
}

ConquestContinent::~ConquestContinent() {
	count--;
}

std::ostream &operator<<(std::ostream &os, const ConquestContinent &c) {
	os << "Name: " << c.name << ", Bonus Value: " << c.bonus_value << std::endl;
	os << "\tTerritories: ";
	for (std::shared_ptr<ConquestTerritory> t : c.territories)
		os << t->name << ", ";
	os << std::endl;
	return os;
}

/////////////////////////////
// ConquestMap class
/////////////////////////////

ConquestMap::ConquestMap() {
	name = "none";
}

ConquestMap::ConquestMap(std::string n) {
	name = n;
}

ConquestMap::ConquestMap(const ConquestMap &m) {
	name = m.name;
	continents = m.continents;
}

ConquestMap &ConquestMap::operator=(const ConquestMap &m) {
	name = m.name;
	continents = m.continents;
	return *this;
}

ConquestMap::~ConquestMap() {

}

std::ostream &operator<<(std::ostream &os, const ConquestMap &m) {
	os << "Name: " << m.name;
	for (std::shared_ptr<ConquestContinent> c : m.continents)
		os << c;
	return os;
}

/////////////////////////////
// ConquestFileReader class
/////////////////////////////

void ConquestFileReader::readMapFile(std::string file_name) {
	ConquestContinent::count = 0;
	std::string current_section = "none";
	cmap.name = file_name;

	// Attempt to open the file.
	std::ifstream inputfilestream(file_name);
	if (!inputfilestream.is_open()) {
		exceptionMessage = "ERROR: Could not open file.";
		throw exceptionMessage;
	};

	std::string line = "";
	while (std::getline(inputfilestream, line)) {
		if (!line.empty() && !cfr::isStringBlank(line)) {
			cfr::trim(line);
			if (line[0] == ';') {
				// Do nothing, this is a commented line
			} else if (line[0] == '[') {
				std::size_t pos = line.find(']');
				current_section = line.substr(1, pos - 1);
				current_section = cfr::toLowerCase(current_section);
			} else {
				// Do things according to what section we're in
				if (current_section == "map") {
					// Do nothing with these values
				} else if (current_section == "continents") {
					processContinentLine(line);
				} else if (current_section == "territories") {
					processTerritoryLine(line);
				}
			}
		}
	}
}

void ConquestFileReader::processContinentLine(std::string line) {
	std::vector<std::string> line_args;
	line_args = cfr::split(line, '=');
	if (line_args.size() == 2) {
		int second_arg = 0;
		try {
			second_arg = std::stoi(line_args[1]);
		} catch (const std::invalid_argument &ia) {
			// invalid argument, not an integer
			throw std::invalid_argument("Invalid continent line argument, bonus value is not an integer.");
		} catch (const std::out_of_range &oor) {
			// number is integer, but out of the range of int
			throw std::range_error("Invalid continent line arguemnt: Range is outside of acceptable values for int.");
		}

		std::shared_ptr<ConquestContinent> newContinent(new ConquestContinent(line_args[0], second_arg));

		cmap.continents.push_back(newContinent);
	} else {
		throw "invalid continents line exception - too many or too few arguments.";
	}

}

void ConquestFileReader::processTerritoryLine(std::string line) {

	std::vector<std::string> line_args = cfr::split(line, ',');

	int arg1 = 0;
	int arg2 = 0;

	if (line_args.size() >= 4) {
		try {
			arg1 = std::stoi(line_args[1]);
			arg2 = std::stoi(line_args[2]);
		} catch (const std::invalid_argument &ia) {
			// invalid argument, not an integer
			throw std::invalid_argument("Invalid territory line argument, coordinate value is not an integer.");
		} catch (const std::out_of_range &oor) {
			// number is integer, but out of the range of int
			throw std::range_error("Invalid territory line arguemnt: Range is outside of acceptable values for int.");
		}

		// Create the new territory
		std::shared_ptr<ConquestTerritory> newTerritory(new ConquestTerritory(line_args[0], arg1, arg2));

		// Add its adjacent territories to its adjacent list
		for (unsigned int i = 4; i < line_args.size(); i++) {
			newTerritory->adjacent_territories.push_back(line_args[i]);
		}

		// Validate the Continent it belongs to, and add it to that continent
		bool found = false;
		for (int i = 0; i < cmap.continents.size(), !found; i++) {
			if (cmap.continents[i]->name == line_args[3]) {
				found = true;
				cmap.continents[i]->territories.push_back(newTerritory);
			}
		}
		if (!found) {
			throw "Invalid territory line exception: continent not found.";
		}

	} else {
		throw "invalid territories exception - too few line args";
	}

}

ConquestFileReader::~ConquestFileReader() {

}

/////////////////////////////////////////////////////////////////////////////////
//
// Miscellaneous String helper Functions
//
/////////////////////////////////////////////////////////////////////////////////

std::string cfr::toLowerCase(const std::string toLower) {
	std::string lowerCase = "";
	if (toLower.empty())
		return toLower;
	for (unsigned int i = 0; i < toLower.length(); i++) {
		lowerCase += tolower(toLower[i]);
	}
	return lowerCase;
}

//////////////////
// Source:
// https://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
void cfr::trim(std::string &s) {
	size_t p = s.find_first_not_of("\t\n\v\f\r ");
	s.erase(0, p);

	p = s.find_last_not_of("\t\n\v\f\r ");
	if (std::string::npos != p)
		s.erase(p + 1);
}
/////////////////

// Returns false if no non-space characters are found
// Returns true otherwise
bool cfr::isStringBlank(const std::string line) {
	if (!line.empty()) {
		for (unsigned int i = 0; i < line.length(); i++) {
			// Source: https://en.cppreference.com/w/cpp/string/byte/isspace
			if (!std::isspace(static_cast<unsigned char>(line[i]))) {
				return false;
			}
		}
	}
	return true;
}

///////////////////
// Source: https://thispointer.com/how-to-split-a-string-in-c/
std::vector<std::string> cfr::split(std::string strToSplit, char delimiter) {
	std::stringstream ss(strToSplit);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (std::getline(ss, item, delimiter)) {
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}
///////////////////

