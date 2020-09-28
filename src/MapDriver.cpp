#include "Map.h"
#include "Map2.h"

int main()
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
    Country Malaysia{
        "Malaysia", 0, "ASEAN"
    };

    Country Indonesia{
        "Indonesia", 1, "ASEAN"
    };
    Country Singapore{
        "Singapore", 2, "ASEAN"
    };

    Country Philippine{
        "Philippine", 3, "ASEAN"
    };

    Country Thailand{
        "Thailand", 4, "ASEAN"
    };

    Country Vietnam{
        "Vietnam", 5, "ASEAN"
    };

    Country Japan{
        "Japan", 6, "East Asia"
    };

    Country Korea{
        "Korea", 7, "East Asia"
    };

    Country China{
        "China", 8, "East Asia"
    };

    std::cout << "test" << std::endl;
    Map2 *WorldMap = new Map2(9, "WorldMap");
    

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

    WorldMap->Display("East Asia");

    /*Map2* WorldMap = new Map2();
    WorldMap->AddContinent(EastAsia);
    WorldMap->AddContinent(ASEAN);

    WorldMap->Display();*/


    return 0;
}