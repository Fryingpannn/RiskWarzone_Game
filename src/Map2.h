#pragma once
#include <vector>
#include <string>

struct Country {
	std::string Name;
	int CountryID;

	bool operator==(Country& country) const { return this->CountryID == country.CountryID; }

};

class Map2
{
	Map2* Continent;
	std::string* MapName;
	std::vector<struct::Country> **ListOfCountries;
	int* NumberOfCountries;

	bool Equals(Country country2);

	
public:
	//minimal Constructor
	Map2();

	//another minimal constructor
	Map2(int size);
	//full constructor
	Map2(std::vector<struct::Country> **listOfCountries, std::string mapName,int size, Map2 &continent);
	//partial constructor when the country doesn't have other maps
	Map2(std::vector<struct::Country> **listOfCountries, std::string mapName, int size);


	Map2(Map2 &Copy);

	~Map2();

	void AddEdges(Country country1, Country country2);
	void Display();

	void SetMapName(std::string mapName);

	
};

