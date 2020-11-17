/////////////////////////////////////////////
// Filename:        MapDriver.cpp
//
// Description:     Driver file for the Implementation of Part 1 - Map
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

#include "MapDriver.h"
#include "Map.h"
#include "Player.h"
#include <stdlib.h>
#include <iostream>



void mapDriver()
{

    //FindMemoryLeak();
    //one way to optimise is to put enum
    //all these will be in stack memory

    


  // for maploader people, this is an example on how you can initialize it
  std::string ExampleName = "ahhh";
  std::string Continent = "continent";
  int CountryId = 2;

  Territory MapLoaderReference{ExampleName, CountryId, Continent, 0, 0};

  Territory *Malaysia = new Territory("Malaysia", 0, "ASEAN", 0, 0);

  Territory *Indonesia = new Territory("Indonesia", 1, "ASEAN", 0, 0);
  Territory *Singapore = new Territory("Singapore", 2, "ASEAN", 0, 0);

  Territory *Philippine = new Territory("Philippine", 3, "ASEAN", 0, 0);

  Territory *Thailand = new Territory ("Thailand", 4, "ASEAN", 0, 0);

  Territory *Vietnam = new Territory ("Vietnam", 5, "ASEAN", 0, 0);



  // This is how you add country to the map
  // you add the edges instead of isolated country
  Map* WorldMap = new Map(6, "WorldMap");
  WorldMap->AddEdges(*Malaysia, *Vietnam);
  WorldMap->AddEdges(*Malaysia, *Indonesia);
  WorldMap->AddEdges(*Indonesia, *Malaysia);
  WorldMap->AddEdges(*Indonesia, *Philippine);
  WorldMap->AddEdges(*Singapore, *Vietnam);
  WorldMap->AddEdges(*Singapore, *Malaysia);

  WorldMap->AddEdges(*Vietnam, *Malaysia);
  WorldMap->AddEdges(*Vietnam, *Thailand);

  WorldMap->Display();



  

  //Log("WorldMap number of territories");
  std::cout << WorldMap->NumOfCountries() << std::endl;

  // not connected graph
  if (WorldMap->Validate()) {
    std::cout << "\n\nSuccess" << std::endl;
  } else {
    std::cout << "\n\nfalse" << std::endl;
  }

  auto TestTerritory = WorldMap->ReturnListOfAdjacentCountriesByID(1);

  for (auto territory : TestTerritory)
  {
      std::cout << territory->Name << std::endl;
  }
  


  

  delete WorldMap;
  WorldMap = nullptr;
 // Log("Deleted WorldMap1");
  

  
}
