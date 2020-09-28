#pragma once
#include <vector>
#include <string>


//country only need name, a unique ID and a continent
//is a struct and not a class, so do what you need to do :)
struct Country {
	std::string Name;
	int CountryID;
	std::string Continent;
	bool operator==(Country& country) const { return this->CountryID == country.CountryID; }

};

class Map
{
	
	std::string* MapName;
	std::vector<struct::Country> **ListOfCountries;
	int* NumberOfCountries;

	

	
public:
	//minimal Constructor
	Map();

	//another minimal constructor
	Map(int size, std::string mapName);
	//full constructor
	Map(std::vector<struct::Country> **listOfCountries, std::string mapName,int size, Map &continent);
	//partial constructor when the country doesn't have other maps
	Map(std::vector<struct::Country> **listOfCountries, std::string mapName, int size);


	Map(Map &Copy);

	~Map();

	void AddEdges(Country country1, Country country2);
	void Display();
	void Display(std::string continent);
	void SetMapName(std::string mapName);

	bool Validate();
	
};

