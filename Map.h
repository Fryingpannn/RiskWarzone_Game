#pragma once
#include <vector>
#include <string>

//1) the map is a connected graph, 2) continents are connected subgraphs and 3) each country
//belongs to oneand only one continent.The driver must provide test cases for various valid / invalid maps.
struct Country
{
    std::string* Name;
    int* CountryID; //country ID will act as vertices

    //the graph
};

class Map
{
    int* Vertices;    
    // No. of vertices 

    //std::string* Country;

    Map* Continent;

    // Pointer to an array containing adjacency lists 
    std::vector<struct::Country>* ListOfCountries;



    // A function used by DFS 
    //void DFSUtil(int Vertices, bool Visited[]);
public:
    //initializing the vertices, and the list of countries
    //if the list of countries doesn't match the vertices it will return error :D 
    Map(int &Vertices,std::vector<struct::Country>& Countries, Map &Continent);   // Constructor 
    Map();//default Constructor
    ~Map();
    void addEdge(struct::Country &Country, int &W);
    void connectedComponents();

    void DisplayGraph();
};

