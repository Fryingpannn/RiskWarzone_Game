#include "Map.h"
#include <iostream>
#include <algorithm>


Map::Map()
{
	NumberOfCountries = new int(5);
	*ListOfCountries = new std::vector<struct::Territory*>[1000] ;
	MapName = new std::string ("World");
	
}

//use this constructor when you are sure of the sizes and will not change anymore
//to change the size, create another map and create another new std::vector<Territory *> *[size} and use another constructor :)
Map::Map(int size, std::string name)
{
	std::cout << "It passed" << std::endl;
	NumberOfCountries = new int (size);

	ListOfCountries = new std::vector<Territory *> *[size];
	for (int i = 0; i < size; i++)
		ListOfCountries[i] = new std::vector<struct::Territory*>;

	
	std::cout << "It passed 2" << std:: endl;
	MapName = new std::string (name);
	

}

Map::Map(std::vector<struct::Territory*> **listOfCountries, std::string mapName, int size, Map &continent)
{
	NumberOfCountries = new int (size);
	ListOfCountries = listOfCountries;
	MapName = new std::string (mapName);
	
}

Map::Map(std::vector<struct::Territory*> **listOfCountries, std::string mapName, int size)
{
	NumberOfCountries = new int(size);
	ListOfCountries = listOfCountries;
	MapName = new std::string(mapName);
	
}

Map::Map(Map &Copy)
{
	MapName = new std::string(*Copy.MapName);
	ListOfCountries = new std::vector<Territory *> * [100];

	for (int i = 0; i < 100; i++)
		ListOfCountries[i] = new std::vector<struct::Territory*>;

	for (int i = 0; i < *Copy.NumberOfCountries; i++)
	{
		for (Territory* country: *Copy.ListOfCountries[i])
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



void Map::AddEdges(Territory &country1, Territory &country2)
{
	std::cout << "Passed by Add Edges" << std::endl;

	if (this->ListOfCountries[country1.TerritoryID]->size()==0)
	{
		std::cout << "HEY HEY" << std::endl;
		this->ListOfCountries[country1.TerritoryID]->push_back(&country1);
	}

	if (this->ListOfCountries[country2.TerritoryID]->size() == 0)
	{
		std::cout << "HEY HEY 2" << std::endl;
		this->ListOfCountries[country2.TerritoryID]->push_back(&country2);
	}

	//error handling
	//if list of country1 contains country2
	int first = 0;
	for (Territory* country : *(ListOfCountries[country1.TerritoryID]))
	{
		std::cout << "HEY HEY 3" << std::endl;
		if (*country == country2)
			return;
	
	}
	
	


	this->ListOfCountries[country2.TerritoryID]->push_back(&country1);
	this->ListOfCountries[country1.TerritoryID]->push_back(&country2);
	
}

int Map::NumOfCountries() {

	return *this->NumberOfCountries;
}


void Map::Display()
{
	std::cout << "\n\nMap Name: " << *MapName << std::endl;

	for (int i = 0; i < *this->NumberOfCountries; i++)
	{
		int j = 0;
		
		for (Territory* country: *(this->ListOfCountries[i]))
		{
			if (j == 0) {
				std::cout << "Territory: " << i << std::endl;
				std::cout << "Name: " << country->Name << std::endl;
				std::cout << "Adjacent Countries " << std::endl;
				j++;
			}
			else {
				std::cout << "-> ";
				std::cout << "Country ID: " << country->TerritoryID << " ";
				std::cout << country->Name;
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

		for (Territory* country : *(this->ListOfCountries[i]))
		{
			if (j == 0) {
				if (continent == country->Continent) {
					std::cout << "Continent: " << country->Continent << std::endl;
					std::cout << "Country: " << j << std::endl;
					std::cout << "Name: " << country->Name << std::endl;
					std::cout << "Adjacent Countries " << std::endl;
					j++;
				}
			}
			else {
				if (continent == country->Continent) {
					std::cout << "-> ";
					std::cout << "Country ID: " << country->TerritoryID << " ";
					std::cout << country->Name;
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
	std::cout << "\n\n\nVALIDATING\n\n\n"<<std::endl;

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
			for (Territory* country : *(this->ListOfCountries[i]))
			{
				for (Territory* country2 : *(this->ListOfCountries[x]))
				{
					if (country->TerritoryID == country2->TerritoryID)
					{
						if (country->Name != country2->Name)
						{
							std::cout << "Error Occured! Country with different name with same ID: "
								<< country->Name << "& " << country2->Name << " with ID: " << country->TerritoryID << std::endl;
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
				if (this->ListOfCountries[i]->at(j)->Continent=="") {
					std::cout << "Continent is empty! Error " << std::endl;
					return false;
				}
				/*if (ListOfCountries[i]->at(j).CountryID == NULL) {
					std::cout << "CountryID is empty! Error " << std::endl;
					return false;
				}*/
				if (ListOfCountries[i]->at(j)->Name == "") {
					std::cout << "Name is empty! Error " << std::endl;
					return false;
				}


				//checking whether same country ID is found or same country name is found
				for (int k = j + 1; k < this->ListOfCountries[i]->size(); k++)
				{
					if (ListOfCountries[i]->at(j)->TerritoryID == ListOfCountries[i]->at(k)->TerritoryID) {
						std::cout << "Same Territory ID found!! Error " << std::endl;
						return false;
					}
					if (ListOfCountries[i]->at(j)->Name == ListOfCountries[i]->at(k)->Name) {
						std::cout << "Same Territory Name found!! Error " << std::endl;
						return false;
					}
				}
				
			
		}
		
		std::cout << std::endl;
	}

	return true;
}
