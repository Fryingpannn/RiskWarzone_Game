#include <iostream>
#include "Map.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //// graph edges array.
    //graphEdge edges[] = {
    //    // (x, y, w) -> edge from x to y with weight w
    //    {0,1,2, "Malaysia"},{0,2,4, "Malaysia"},{1,4,3, "Indonesia"},{2,3,2, "No idea"},{3,1,4, "Mars"},{4,3,3, "England"}
    //};
    //
    //int Vertices = 6;      // Number of vertices in the graph
    //// calculate number of edges
    //int n = sizeof(edges) / sizeof(edges[0]);
    //// construct graph
    //Map diagraph(edges, n, Vertices);
    //// print adjacency list representation of graph
    //

    //diagraph.Display();

    //one way to optimise is to put enum
    Territory* Malaysia = new Territory(
        "Malaysia", 0, "ASEAN"
    );

    Territory* Indonesia = new Territory(
        "Indonesia", 1, "ASEAN"
    );
    Territory* Singapore= new Territory(
        "Singapore", 2, "ASEAN"
    );

    //call on heap memory
    Territory* Philippine = new Territory(
        "Philippine", 3, "ASEAN"
    );


    // Call on stack memory for this :O 
    Territory Thailand (
        "Thailand", 4, "ASEAN"
    );

    Territory* Vietnam = new Territory(
        "Vietnam", 5, "ASEAN"
    );

    Territory* Japan = new Territory(
        "Japan", 6, "EastAsia"
    );

    Territory* Korea = new Territory(
        "Korea", 7, "EastAsia"
    );

    Territory* China = new Territory(
        "China", 8, "EastAsia"
    );

    //incorrect Territory naming cases
    Territory* Germany = new Territory(
        "Germany", 8, "EastAsia"
    );

    Territory France (
        "France", 8, "Europe"
    );


    //testing out deleting memory
   /* std::cout << "test" << std::endl;

    std::vector<Territory*>** ASEAN = new std::vector<Territory*> *[8];

 

    for (int i = 0; i < 8; i++) {
        ASEAN[i] = new std::vector<Territory*>;
    }
    
    ASEAN[0]->push_back(Malaysia);
    
    ASEAN[1]->push_back(Indonesia);

    

    std::cout << "Hello?" << std::endl;
    for (int i = 0; i < 8; i++) {
        for (Territory* c : *ASEAN[i]) {
            std::cout << *c->Name << std::endl;
            delete c;
        }
        ASEAN[i]->clear();
        std::cout << "Deleted Yay! " << std::endl;
        delete ASEAN[i];
 
    }
    delete[] ASEAN;
    std::cout << "Deleted Yay 2! " << std::endl;*/

    //end testing

    Map *WorldMap = new Map(9, "WorldMap");
    

    WorldMap->AddEdges(*Malaysia, *Vietnam);
    WorldMap->AddEdges(*Malaysia, *Indonesia);
    WorldMap->AddEdges(*Indonesia, *Malaysia);
    WorldMap->AddEdges(*Indonesia, *Philippine);
    WorldMap->AddEdges(*Singapore, *Vietnam);
    WorldMap->AddEdges(*Singapore, *Malaysia);
    
    WorldMap->AddEdges(*Vietnam, *Malaysia);
    WorldMap->AddEdges(*Vietnam, Thailand);

    WorldMap->Display();

    
    WorldMap->AddEdges(*Japan, *Korea);
    WorldMap->AddEdges(*China, *Korea);
    WorldMap->AddEdges(*Malaysia, *Japan);

    WorldMap->Display();

    WorldMap->Display("EastAsia");

    if (WorldMap->Validate())
    {
        std::cout << "Success" << std::endl;
    }
    
    
    /*Map *WorldMap = new Map(9, "WorldMap");
    

    WorldMap->AddEdges(*Malaysia, *Vietnam);
    WorldMap->AddEdges(*Malaysia, *Indonesia);
    WorldMap->AddEdges(*Indonesia, *Malaysia);
    WorldMap->AddEdges(*Indonesia, *Philippine);
    WorldMap->AddEdges(*Singapore, *Vietnam);
    WorldMap->AddEdges(*Singapore, *Malaysia);
    
    WorldMap->AddEdges(*Vietnam, *Malaysia);
    WorldMap->AddEdges(*Vietnam, *Thailand);

    WorldMap->Display();

    
    WorldMap->AddEdges(*Japan, *Korea);
    WorldMap->AddEdges(*China, *Korea);
    WorldMap->AddEdges(*Malaysia, *Japan);

    WorldMap->Display();

    WorldMap->Display("EastAsia");

    if (WorldMap->Validate())
    {
        std::cout << "Success" << std::endl;
    }*/

    

    //test case 2


    //fail cases where the country won't register due to having same ID
    // the country ID will causes the algorithm to think that it is another country and will treat it the same
    
    //using copy constructor
    /*Map* WorldMap2 = new Map(*WorldMap);
    WorldMap2->AddEdges(Japan,Korea);
    WorldMap2->AddEdges(China, Korea);
    WorldMap2->AddEdges(Malaysia, Korea);
    WorldMap2->AddEdges(Germany, Korea);
    WorldMap2->AddEdges(France, Korea);
    WorldMap2->AddEdges(France, Malaysia);
    WorldMap2->Display();

    if (WorldMap2->Validate())
    {
        std::cout << "Success" << std::endl;
    }
    else {
        std::cout << "Failed" << std::endl;

    }*/

    //let me test memory leaks

    std::cout << "Deleting each countries" << std::endl;
    delete Malaysia;
    delete Indonesia;
    delete Singapore;
    delete Philippine;
    //delete &Thailand;
    delete Vietnam;
    delete Japan;
    delete Korea;
    delete China;
    //delete &France;
    delete Germany;
    std::cout << "Finish deleting each countries" << std::endl;
    delete WorldMap;
    system("pause");

    /*Map* WorldMap = new Map();
    WorldMap->AddContinent(EastAsia);
    WorldMap->AddContinent(ASEAN);

    WorldMap->Display();*/

   
    return 0;
}