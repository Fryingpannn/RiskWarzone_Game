#include "Map.h"
#include <iostream>
#include <algorithm>


Map::Map()
{
	NumberOfCountries = new int(5);
	*ListOfCountries = new std::vector<struct::Country>[100] ;
	MapName = new std::string ("World");
	
}

Map::Map(int size, std::string name)
{
	std::cout << "It passed" << std::endl;
	NumberOfCountries = new int (size);

	ListOfCountries = new std::vector<Country> *[100];
	for (int i = 0; i < 100; i++)
		ListOfCountries[i] = new std::vector<struct::Country>;

	
	std::cout << "It passed 2" << std:: endl;
	MapName = new std::string (name);
	

}

Map::Map(std::vector<struct::Country> **listOfCountries, std::string mapName, int size, Map &continent)
{
	NumberOfCountries = new int (size);
	ListOfCountries = listOfCountries;
	MapName = new std::string (mapName);
	
}

Map::Map(std::vector<struct::Country> **listOfCountries, std::string mapName, int size)
{
	NumberOfCountries = new int(size);
	ListOfCountries = listOfCountries;
	MapName = new std::string(mapName);
	
}

Map::Map(Map &Copy)
{
	MapName = new std::string(*Copy.MapName);
	ListOfCountries = new std::vector<Country> * [100];

	for (int i = 0; i < 100; i++)
		ListOfCountries[i] = new std::vector<struct::Country>;

	for (int i = 0; i < *Copy.NumberOfCountries; i++)
	{
		for (Country country: *Copy.ListOfCountries[i])
		{
			ListOfCountries[i]->push_back(country);
		}
	}
	std::cout << "Copied successful" << std::endl;
		

	
	NumberOfCountries = new int (*Copy.NumberOfCountries);
}

Map::~Map()
{
	for (int i = 0; i < *this->NumberOfCountries; i++)
		delete[] ListOfCountries[i];

	delete[] ListOfCountries;

	delete NumberOfCountries;
	delete MapName;
	
	//will make it into pointer later on
	/*delete MapName;*/
}



void Map::AddEdges(Country country1, Country country2)
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

void Map::Display()
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
				j++;
			}
		}
		j = 0;
		std::cout << std::endl;
	}
}

void Map::Display(std::string continent)
{
	std::cout << "\n\nMap Name: " << continent << std::endl;

	for (int i = 0; i < *this->NumberOfCountries; i++)
	{
		int j = 0;

		for (Country country : *this->ListOfCountries[i])
		{
			if (j == 0) {
				if (continent == country.Continent) {
					std::cout << "Continent: " << country.Continent << std::endl;
					std::cout << "Country: " << j << std::endl;
					std::cout << "Name: " << country.Name << std::endl;
					std::cout << "Adjacent Countries " << std::endl;
					j++;
				}
			}
			else {
				if (continent == country.Continent) {
					std::cout << "-> ";
					std::cout << "Country ID: " << country.CountryID << " ";
					std::cout << country.Name;
					j++;
				}
			}
		}
		j = 0;
		std::cout << std::endl;
	}
}

//setters for the map name
// not really necessary 
void Map::SetMapName(std::string mapName)
{
	MapName = new std::string (mapName);
}

//
bool Map::Validate()
{
	if (*this->NumberOfCountries==NULL)
		return false; 

	for (int i = 0; i < *this->NumberOfCountries; i++)
	{
		for (int x = i + 1; x < *this->NumberOfCountries; x++)
		{
			if (i == *this->NumberOfCountries)
			{
				x++;
				break;
			}
			//checking over2d arrays whether there are same ID with different names
			for (Country country : *this->ListOfCountries[i])
			{
				for (Country country2 : *this->ListOfCountries[x])
				{
					if (country.CountryID == country2.CountryID)
					{
						if (country.Name != country2.Name)
						{
							std::cout << "Error Occured! Country with different name with same ID: "
								<< country.Name << "& " << country2.Name << " with ID: " << country.CountryID << std::endl;
							return false;
						}
					}
				}
			}
		}

		for (int j=0; j< this->ListOfCountries[i]->size()-1; j++)
		{
			
			//using my code, and how I design it. You don't even need to check whether a country has two continents. 
			//They will have each individual string
				if (ListOfCountries[i]->at(j).Continent=="") {
					std::cout << "Continent is empty! Error " << std::endl;
					return false;
				}
				/*if (ListOfCountries[i]->at(j).CountryID == NULL) {
					std::cout << "CountryID is empty! Error " << std::endl;
					return false;
				}*/
				if (ListOfCountries[i]->at(j).Name == "") {
					std::cout << "Name is empty! Error " << std::endl;
					return false;
				}


				//checking whether same country ID is found or same country name is found
				for (int k = j + 1; k < this->ListOfCountries[i]->size(); k++)
				{
					if (ListOfCountries[i]->at(j).CountryID == ListOfCountries[i]->at(k).CountryID) {
						std::cout << "Same Country ID found!! Error " << std::endl;
						return false;
					}
					if (ListOfCountries[i]->at(j).Name == ListOfCountries[i]->at(k).Name) {
						std::cout << "Same Country Name found!! Error " << std::endl;
						return false;
					}
				}
				
			
		}
		
		std::cout << std::endl;
	}

	return true;
}
