#include <iostream>
#include "Map.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



void mapDriver() 
{
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
    //all these will be in stack memory

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Territory Malaysia{
        "Malaysia", 0, "ASEAN"
    };

    Territory Indonesia{
        "Indonesia", 1, "ASEAN"
    };
    Territory Singapore{
        "Singapore", 2, "ASEAN"
    };

    Territory Philippine{
        "Philippine", 3, "ASEAN"
    };

    Territory Thailand{
        "Thailand", 4, "ASEAN"
    };

    Territory Vietnam{
        "Vietnam", 5, "ASEAN"
    };

    Territory Japan{
        "Japan", 6, "EastAsia"
    };

    Territory Korea{
        "Korea", 7, "EastAsia"
    };

    Territory China{
        "China", 8, "EastAsia"
    };

    //incorrect Territory naming cases
    Territory Germany{
        "Germany", 8, "EastAsia"
    };

    Territory France{
        "France", 8, "Europe"
    };

    
    Map *WorldMap = new Map(9, "WorldMap");
    

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

    //not connected graph
    if (WorldMap->Validate())
    {
        std::cout << "\n\nSuccess" << std::endl;
    }
    else {
        std::cout << "\n\nfalse" << std::endl;
    }

    


    //fail cases where the country won't register due to having same ID
    // the country ID will causes the algorithm to think that it is another country and will treat it the same
    Map* WorldMap2 = new Map(*WorldMap);
    WorldMap2->AddEdges(Japan,Korea);
    WorldMap2->AddEdges(China, Korea);
    WorldMap2->AddEdges(Malaysia, Korea);
    WorldMap2->AddEdges(Germany, Korea);
    WorldMap2->AddEdges(France, Korea);
    WorldMap2->AddEdges(France, Malaysia);
    WorldMap2->Display();
    Log("ERM");

    if (WorldMap2->Validate())
    {
        std::cout << "Success" << std::endl;
    }
    else {
        std::cout << "Failed" << std::endl;

    }

    //connected graph
    //in a triangle
    Map* WorldMap3 = new Map(3, "Small Map");
    Log("Construct successful");
    WorldMap3->AddEdges(Malaysia, Indonesia);
    WorldMap3->AddEdges(Indonesia, Singapore);
    WorldMap3->AddEdges(Singapore,Malaysia);

    if (WorldMap3->Validate())
    {
        std::cout << "Success" << std::endl;
    }
    else {
        std::cout << "Failed" << std::endl;

    }
   

    delete WorldMap;
    Log("Deleted WorldMap1");
    delete WorldMap2;
    Log("Deleted WorldMap2");

    delete WorldMap3;

 
}