#pragma once
#include <vector>
#include <iostream>
#include <string>


//country only need name, a unique ID and a continent
//is a struct and not a class, so do what you need to do :)
struct Territory {
	std::string* Name;
	int* TerritoryID;
	std::string* Continent;
	bool operator==(Territory& Territory) const { return this->TerritoryID == Territory.TerritoryID; }

	Territory(std::string name, int territoryID, std::string continent){
		Name = new std::string(name);
		TerritoryID = new int(territoryID);
		Continent = new std::string(continent);
	}

	~Territory() {
		std::cout << "Deleting: " << *Name << *TerritoryID << " " << *Continent << "\n";
		delete Name;
		delete TerritoryID;
		delete Continent;
	}

};

struct ContinentData {
	std::string* Name;
	int* ContinentID;
	bool operator==(ContinentData &ContinentData) const { return *(this->ContinentID) == *(ContinentData.ContinentID); }
};

class Map
{
	
	std::string* MapName;
	std::vector<Territory*> **ListOfCountries;
	int* NumberOfCountries;

	int ActualSize; 

	
public:
	//minimal Constructor
	Map();

	//another minimal constructor
	Map(int size, std::string mapName);
	//full constructor
	Map(std::vector<struct::Territory*> **listOfCountries, std::string mapName,int size, Map &continent);
	//partial constructor when the country doesn't have other maps
	Map(std::vector<struct::Territory*> **listOfCountries, std::string mapName, int size);


	Map(Map &Copy);

	~Map();

	void AddEdges(Territory &country1, Territory &country2);
	int NumOfCountries();
	void Display();
	void Display(std::string continent);
	void SetMapName(std::string mapName);

	bool Validate();
	
};

