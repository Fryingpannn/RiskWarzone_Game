#include "Map.h"
#include <iostream>


CountryNode* Map::getAdjListNode(int value, int weight, std::string Name, CountryNode* head)
{
    CountryNode* newNode = new CountryNode;
    newNode->CountryID = value;
    newNode->Cost = weight;
    newNode->Name = Name;
    newNode->Next = head;   // point new node to current head
    return newNode;
}

Map::Map(graphEdge edges[], int n, int N)
{
        // allocate new node
        head = new CountryNode * [N]();
        this->N = N;
        // initialize head pointer for all vertices
        for (int i = 0; i < N; ++i)
            head[i] = nullptr;
        // construct directed graph by adding edges to it
        for (unsigned i = 0; i < n; i++) {
            int start_ver = edges[i].start_ver;
            int end_ver = edges[i].end_ver;
            int weight = edges[i].weight;

            std::string name = edges[i].Name;
            // insert in the beginning
            CountryNode* newNode = getAdjListNode(end_ver, weight, name, head[start_ver]);

            // point head pointer to new node
            head[start_ver] = newNode;
        }
 }

Map::~Map()
{
    for (int i = 0; i < N; i++)
        delete[] head[i];
    delete[] head;
}


void Map::Display()
{
    for (int i = 0; i < N; i++)
    {
        CountryNode* ptr = head[i];
        cout << "Country No: " << i <<"\nCountry Name: "<< ptr->Name<< std::endl;
        while (ptr != nullptr)
        {
            cout << "->" << ptr->CountryID;
            ptr = ptr->Next;
        }
        cout<<std::endl;
    }
}


