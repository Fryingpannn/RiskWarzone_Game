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
#include <stdlib.h>
#include <iostream>

void mapDriver()
{

    FindMemoryLeak();
    //one way to optimise is to put enum
    //all these will be in stack memory


  // for maploader people, this is an example on how you can initialize it
  std::string ExampleName = "ahhh";
  std::string Continent = "continent";
  int CountryId = 2;

  Territory MapLoaderReference{ExampleName, CountryId, Continent, 0, 0};

  Territory Malaysia{"Malaysia", 0, "ASEAN", 0, 0};

  Territory Indonesia{"Indonesia", 1, "ASEAN", 0, 0};
  Territory Singapore{"Singapore", 2, "ASEAN", 0, 0};

  Territory Philippine{"Philippine", 3, "ASEAN", 0, 0};

  Territory Thailand{"Thailand", 4, "ASEAN", 0, 0};

  Territory Vietnam{"Vietnam", 5, "ASEAN", 0, 0};

  Territory Japan{"Japan", 6, "EastAsia", 0, 0};

  Territory Korea{ "Korea", 7, "EastAsia", 0, 0 };

  Territory China{ "China", 8, "EastAsia", 0, 0 };

  Territory Germany{ "Germany", 9, "Europe", 0, 0 };

  Territory France{ "France", 8, "Europe", 0, 0 };


  // This is how you add country to the map
  // you add the edges instead of isolated country
  Map* WorldMap = new Map(9, "WorldMap");
  WorldMap->AddEdges(Malaysia, Vietnam);
  WorldMap->AddEdges(Malaysia, Indonesia);
  WorldMap->AddEdges(Indonesia, Malaysia);
  WorldMap->AddEdges(Indonesia, Philippine);
  WorldMap->AddEdges(Singapore, Vietnam);
  WorldMap->AddEdges(Singapore, Malaysia);

  WorldMap->AddEdges(Vietnam, Malaysia);
  WorldMap->AddEdges(Vietnam, Thailand);

  WorldMap->Display();

  WorldMap->AddEdges(Japan, Korea);
  WorldMap->AddEdges(China, Korea);
  WorldMap->AddEdges(Malaysia, Japan);



  WorldMap->Display();

  WorldMap->Display("EastAsia");

  // not connected graph
  if (WorldMap->Validate()) {
    std::cout << "\n\nSuccess" << std::endl;
  } else {
    std::cout << "\n\nfalse" << std::endl;
  }

  // fail cases where the country won't register due to having same ID
  // the country ID will causes the algorithm to think that it is another
  // country and will treat it the same
  Map* WorldMap2 = new Map(*WorldMap);
  WorldMap2->AddEdges(Japan, Korea);
  WorldMap2->AddEdges(China, Korea);
  WorldMap2->AddEdges(Malaysia, Korea);
  WorldMap2->AddEdges(Germany, Korea);
  WorldMap2->AddEdges(France, Korea);
  WorldMap2->AddEdges(France, Malaysia);
  WorldMap2->Display();
  Log("ERM");



  // connected graph
  // in a triangle
  Map* WorldMap3 = new Map(3, "Small Map");
  Log("Construct successful");
  WorldMap3->AddEdges(Malaysia, Indonesia);
  WorldMap3->AddEdges(Indonesia, Singapore);
  WorldMap3->AddEdges(Singapore, Malaysia);

  if (WorldMap3->Validate()) {
    std::cout << "Success" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  //this to test whether copy constructor copies a value
  std::cout << "Testing Printing List Of Countries" << std::endl;
  std::vector<Territory* > test = WorldMap2->ReturnListOfCountries();
  test.at(0)->Name = "Hahaha";
  WorldMap->Display();
  Log("WorldMap2");
  WorldMap2->Display();

  

  Territory TestCopy{Malaysia};

  TestCopy.Name = "Hey Hey";
  test.push_back(&TestCopy);

  WorldMap2->Display();
  //it shouldn't be affected

  Log(Malaysia.Name);
  Log(TestCopy.Name);
  
  //testing assignment operator
  std::cout<<"Testing Assignment Operator"<<std::endl;
  
  Map* TestMap = WorldMap;

  TestMap->AddEdges(Philippine, China);
  TestMap->Display();

  WorldMap->Display();

  delete WorldMap;
  WorldMap = nullptr;
  Log("Deleted WorldMap1");
  
  delete WorldMap2;
  
  WorldMap2 = nullptr;
  Log("Deleted WorldMap2");

  delete WorldMap3;


}
