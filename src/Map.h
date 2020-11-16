/////////////////////////////////////////////
// Filename:        Map.h
//
// Description:     Header file for Implementation of Part 1 - Map
//
// Author:          Le Cherng Lee - 40122814
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>

#include "GameObservers.hpp"


//this macro will only print when in debug mode :3
#ifdef _DEBUG
#define Log(x) std::cout << x << std::endl;
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define FindMemoryLeak()_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define FindMemoryLeak();
#define Log(x)
#endif

//#ifndef H_PLAYER
//#define H_PLAYER
//class Player;
//#endif

class Player;

// country only need name, a unique ID and a continent
// is a struct and not a class, so do what you need to do :)
struct Territory : public Subject {
 public:
  std::string Name;
  int TerritoryID;
  std::string Continent;
  float XCoordinate;
  float YCoordinate;
  std::string OwnedBy = "uninitializedT";
  Player* PlayerOwned;
  int Armies = 0;

  bool operator==(Territory &Territory) const;

  Territory();
  Territory(std::string name, int territoryID, std::string continent, float x,
            float y);
  Territory(std::string name, int territoryID, std::string continent, float x,float y, Player* playerOwned);
  Territory(const Territory &t);
  friend std::ostream &operator<<(std::ostream &out, const Territory &t);
  Territory &operator=(const Territory &t);
};

struct ContinentData {
  std::string Name;
  int ContinentID;
  int NumberOfTerritories;
  int BonusValue;  

  ContinentData();
  ContinentData(std::string name, int continentID, int numberOfTerritories, int bonusValue);
  ContinentData(const ContinentData &c);

  friend std::ostream &operator<<(std::ostream &out, const ContinentData &c);
  ContinentData &operator=(const ContinentData& c);

  bool operator==(ContinentData &ContinentData) const {
    return this->ContinentID == ContinentData.ContinentID;
  }
};

class Map {
  std::string *MapName;
  std::vector<Territory *> **ListOfCountries;
  int *NumberOfCountries;

  std::vector<Territory *> AllCountries;

  std::vector<ContinentData *> AllContinents;

 public:
  // minimal Constructor
  Map();

  // another minimal constructor
  Map(int size, std::string mapName);
  // full constructor
  Map(std::vector<struct ::Territory *> **listOfCountries, std::string mapName,
      int size, Map &continent);
  // partial constructor when the country doesn't have other maps
  Map(std::vector<struct ::Territory *> **listOfCountries, std::string mapName,
      int size);

  Map(Map &Copy);

  ~Map();

  void AddEdges(Territory &country1, Territory &country2);

  void AddContinent(ContinentData *new_continent);

  std::vector<struct::ContinentData*> Map::getListOfContinents();

  std::vector<struct ::Territory *> ReturnListOfCountries();

  //This function return the list of adjacent countries by their ID
  std::vector<struct ::Territory*> ReturnListOfAdjacentCountriesByID(int ID);

  std::vector<struct ::Territory*> ReturnListOfCountriesOwnedByPlayer(std::string PlayerName);

  std::vector<struct ::Territory*> ReturnListOfCountriesByContinent(std::string ContinentName);

  bool IfPlayerOwnContinent(std::string PlayerName, std::string ContinentName);

  void ShowListOfAdjacentCountriesByID(int ID);

  void ShowListOfAdjacentCountriesOwnedByPlayer(std::string PlayerName);

  int NumOfCountries();
  void Display();
  void Display(std::string continent);
  void SetMapName(std::string mapName);
  std::string GetMapName();

  bool Validate();
  void DFS(int x, bool **visited);

  friend std::ostream& operator<<(std::ostream& out, const Map& map);
  
  Map& operator=(const Map* map);
};
