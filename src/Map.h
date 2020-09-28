#pragma once
#include <vector>
#include <string>

//1) the map is a connected graph, 2) continents are connected subgraphs and 3) each country
//belongs to oneand only one continent.The driver must provide test cases for various valid / invalid maps.

#include <iostream>
using namespace std;



//version 2
// stores adjacency list items
struct CountryNode {
    int CountryID;
    //cost means how much need to travel etc. Might not be needed at all
    int Cost;
    std::string Name;
    CountryNode* Next;
};
// structure to store edges
struct graphEdge {
    int start_ver, end_ver, weight;
    std::string Name;
};
class Map {

    //version 1
    // insert new nodes into adjacency list from given graph
    CountryNode* getAdjListNode(int value, int weight, std::string Name, CountryNode* head);
    int N;  // number of nodes in the graph


    //version 2
    
public:
    CountryNode** head;                //adjacency list as array of pointers
    // Constructor
    Map(graphEdge edges[], int n, int N);
    
    Map();
    // Destructor
    ~Map();

    

    void Display();
};
// print all adjacent vertices of given vertex

