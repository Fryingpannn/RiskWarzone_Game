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

    Country Malaysia{
        "Malaysia", 0
    };

    Country Indonesia{
        "Indonesia", 1
    };
    Country Singapore{
        "Singapore", 2
    };

    Country Philippine{
        "Philippine", 3
    };

    Country Thailand{
        "Thailand", 4
    };

    Country Vietnam{
        "Vietnam", 5
    };

    std::cout << "test" << std::endl;
    Map2 *ASEAN = new Map2(6);
    std::cout << "test" << std::endl;
    
    ASEAN->SetMapName("ASEAN");
    ASEAN->AddEdges(Malaysia, Vietnam);
    ASEAN->AddEdges(Malaysia, Indonesia);
    ASEAN->AddEdges(Indonesia, Malaysia);
    ASEAN->AddEdges(Indonesia, Philippine);
    ASEAN->AddEdges(Singapore, Vietnam);
    ASEAN->AddEdges(Singapore, Malaysia);
    
    /*ASEAN->AddEdges(Vietnam, Malaysia);
    ASEAN->AddEdges(Vietnam, Thailand);*/


    ASEAN->Display();

    return 0;
}