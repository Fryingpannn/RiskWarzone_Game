#include "Map2.h"
#include <iostream>
#include <algorithm>


Map2::Map2()
{
	NumberOfCountries = new int(5);
	*ListOfCountries = new std::vector<struct::Country>[5] ;
	MapName = new std::string ("None");
	Continent = NULL;
}

Map2::Map2(int size)
{
	std::cout << "It passed" << std::endl;
	NumberOfCountries = new int (size);

	ListOfCountries = new std::vector<Country> *[size];
	for (int i = 0; i < size; i++)
		ListOfCountries[i] = new std::vector<struct::Country>;

	
	std::cout << "It passed 2" << std:: endl;
	MapName = new std::string ("None");
	Continent = NULL;

}

Map2::Map2(std::vector<struct::Country> **listOfCountries, std::string mapName, int size, Map2 &continent)
{
	NumberOfCountries = new int (size);
	ListOfCountries = listOfCountries;
	MapName = new std::string (mapName);
	Continent = new Map2(continent);
}

Map2::Map2(std::vector<struct::Country> **listOfCountries, std::string mapName, int size)
{
	NumberOfCountries = new int(size);
	ListOfCountries = listOfCountries;
	MapName = new std::string(mapName);
	Continent = NULL;
}

Map2::Map2(Map2 &Copy)
{
	MapName = Copy.MapName;
	ListOfCountries = Copy.ListOfCountries;
	Continent = NULL;
	NumberOfCountries = Copy.NumberOfCountries;
}

Map2::~Map2()
{
	for (int i = 0; i < *this->NumberOfCountries; i++)
		delete[] ListOfCountries[i];

	delete[] ListOfCountries;

	delete NumberOfCountries;
	delete MapName;
	delete Continent;
	//will make it into pointer later on
	/*delete MapName;*/
}



void Map2::AddEdges(Country country1, Country country2)
{
	std::cout << "Passed by Add Edges" << std::endl;

	if (this->ListOfCountries[country1.CountryID]->size()==0)
	{
		std::cout << "HEY HEY" << std::endl;
		this->ListOfCountries[country1.CountryID]->push_back(country1);
	}

	if (this->ListOfCountries[country2.CountryID]->size() == 0)
	{
		std::cout << "HEY HEY 2" << std::endl;
		this->ListOfCountries[country2.CountryID]->push_back(country2);
	}

	//error handling
	//if list of country1 contains country2
	int first = 0;
	for (Country country : *ListOfCountries[country1.CountryID])
	{
		std::cout << "HEY HEY 3" << std::endl;
		if (country == country2)
			return;
	
	}
	
	


	this->ListOfCountries[country2.CountryID]->push_back(country1);
	this->ListOfCountries[country1.CountryID]->push_back(country2);
	
}

void Map2::Display()
{
	std::cout << "\n\nMap Name: " << *MapName << std::endl;

	for (int i = 0; i < *this->NumberOfCountries; i++)
	{
		int j = 0;
		
		for (Country country: *this->ListOfCountries[i])
		{
			if (j == 0) {
				std::cout << "Country: " << i << std::endl;
				std::cout << "Name: " << country.Name << std::endl;
				std::cout << "Adjacent Countries " << std::endl;
				j++;
			}
			else {
				std::cout << "-> ";
				std::cout << "Country ID: " << country.CountryID << " ";
				std::cout << country.Name;
			}
		}
		j = 0;
		std::cout << std::endl;
	}
}

void Map2::SetMapName(std::string mapName)
{
	MapName = new std::string (mapName);
}

bool Map2::Equals(Country country2)
{
	return false;
}
