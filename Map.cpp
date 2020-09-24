#include "Map.h"
#include <iostream>

Map::Map(int& Vertices, std::vector<struct::Country>& Countries, Map &Continent)
{
	this->Vertices = &Vertices;
	this->Continent = &Continent;
	this->ListOfCountries = new std::vector<struct::Country>;
	ListOfCountries = &Countries;

}

Map::Map()
{

}

Map::Map(Map& Map)
{
}

Map::~Map()
{
}

void Map::addEdge(struct::Country &Country, int& W)
{
}

void Map::connectedComponents()
{
}

void Map::DisplayGraph()
{
    for (int i = 0; i < *Vertices; ++i)
    {
        std::cout << "\n Adjacency list of vertex "
            << i << "\n head ";
        for (auto x = ListOfCountries->begin(); x != ListOfCountries->end(); x++)
            std::cout << "-> "<< (struct::Country*) x->CountryID;
        printf("\n");
    }
}
