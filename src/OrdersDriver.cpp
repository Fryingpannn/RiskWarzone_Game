/////////////////////////////////////////////
// Filename:        OrdersDriver.cpp
//
// Description:     Driver for Implementation of Part 4 - Orders List
//
// Author:          Matthew Pan - 40135588
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#include "OrdersDriver.h"
#include "Orders.h"
#include "Map.h"
#include "Cards.h"

//This driver file tests the functionalities from the Orders.h/Orders.cpp files.
 void ordersDriver() {
	std::cout << "-------- OrderList driver program: Let's create some orders! -------\n" << std::endl;
	std::cout << "-------- Assignment 2 code tests -------\n" << std::endl;

	//creating territories to test orders with
	auto* Malaysia = new Territory{ "Malaysia", 0, "ASEAN", 0, 0 };
	Malaysia->OwnedBy = "neutral";
	auto* Indonesia = new Territory{ "Indonesia", 1, "ASEAN", 0, 0 };
	Indonesia->OwnedBy = "Sandra";
	Indonesia->Armies = 2;
	auto* Singapore = new Territory{ "Singapore", 2, "ASEAN", 0, 0 };
	Singapore->OwnedBy = "Matthew";
	auto* Philippine = new Territory{ "Philippine", 3, "ASEAN", 0, 0 };
	Philippine->OwnedBy = "Penguin";

	//creating map to link territories
	Map* WorldMap = new Map(9, "WorldMap");
	WorldMap->AddEdges(*Malaysia, *Indonesia);
	WorldMap->AddEdges(*Indonesia, *Malaysia);
	WorldMap->AddEdges(*Singapore, *Malaysia);
	WorldMap->AddEdges(*Malaysia, *Singapore);
	WorldMap->AddEdges(*Indonesia, *Philippine);
	WorldMap->AddEdges(*Philippine, *Indonesia);
	
	//creating deck & player to test orders with
	Deck* deck = new Deck(12);
	Hand hand{};
	OrderList orders{};
	std::vector<Territory*> playerOwned{};
	playerOwned.push_back(Singapore); //player owns only singapore
	Player* matthew = new Player(playerOwned, hand, orders, "Matthew");

	//testing valid deploy order
	std::cout << std::endl << "----- Valid Deploy -----" << std::endl << std::endl;
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "Matthew: [Deploy] Deploying 5 armies to Singapore." << std::endl;
	Order* deploy1 = new Deploy("Matthew", 5, Singapore);
	deploy1->execute();
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;

	//testing invalid deploy order
	std::cout << std::endl << "----- Invalid Deploy (Wrong territory) -----" << std::endl << std::endl;
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;
	std::cout << "Matthew: [Deploy] Deploying 5 armies to Malaysia." << std::endl;
	Order* deploy2 = new Deploy("Matthew", 5, Malaysia);
	deploy2->execute();
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;

	//testing valid advance order with no attack
	std::cout << std::endl << "----- Valid Advance (No Attack) -----" << std::endl << std::endl;
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;
	std::cout << "Matthew: [Advance] Advancing 4 armies from Singapore to Malaysia." << std::endl;
	Order* advance1 = new Advance("Matthew", 4, Singapore, Malaysia, WorldMap, matthew, deck);
	advance1->execute();
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;

	//testing valid advance order; attack
	std::cout << std::endl << "----- Valid Advance (Attack) -----" << std::endl << std::endl;
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;
	std::cout << "Matthew: [Advance] Advancing 3 armies from Malaysia to Indonesia." << std::endl;
	Order* advance2 = new Advance("Matthew", 2, Malaysia, Indonesia, WorldMap, matthew, deck);
	advance2->execute();
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;

	//testing invalid advance order; non-adjacent territory
	std::cout << std::endl << "----- Invalid Advance (Non-adjacent Territory) -----" << std::endl << std::endl;
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;
	std::cout << "Matthew: [Advance] Advancing 3 armies from Singapore to Indonesia." << std::endl;
	Order* advance3 = new Advance("Matthew", 3, Singapore, Indonesia, WorldMap, matthew, deck);
	advance3->execute();
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;
	
	delete deploy1, delete deploy2, delete advance1, delete advance2, delete advance3;
	delete Malaysia, delete Singapore, delete Philippine, delete Indonesia;
	delete deck, delete matthew, delete WorldMap;
	/*------------------------------------------------------------------------------------------------------*/

	std::cout << "-------- Assignment 1 code tests -------\n" << std::endl;
	//creating new OrderList
	OrderList oList;

	//adding orders to the list
	oList.addToList(new Deploy());
	oList.addToList(new Advance());
	oList.addToList(new Bomb());
	oList.addToList(new Blockade());
	oList.addToList(new Negotiate());
	oList.addToList(new Airlift());

	//displaying list
	std::cout << std::endl << oList;

	//making a copy of the previous list (copy constructor)
	std::cout << "----- Copying previous list with Copy Constructor: Constructor chain -----" << std::endl;
	OrderList listCopy = oList;
	std::cout << std::endl;

	//moving the orders in the list & displaying list again
	oList.move(0, 2);
	std::cout << oList << std::endl;

	//displaying previously copied list
	std::cout << "Displaying previously copied list, which has not changed." << std::endl;
	std::cout << listCopy << std::endl;

	//removing item 1 from the list & displaying list again
	std::cout << "-> Removing item 1 from the list <-" << std::endl;
	oList.remove(1);
	std::cout << oList << std::endl;

	//Displaying an order without executing it
	std::cout << "Displaying an order before it has been executed:" << std::endl;
	Deploy obj;
	std::cout << obj << std::endl << std::endl;

	//Displaying an order when its been executed
	std::cout << "Displaying an order after it has been executed:" << std::endl;
	obj.execute();
	std::cout << obj << std::endl;

	//making a copy of the list with assignment operator and displaying it
	std::cout << "----- Copying previous list with assignment operator: Constructor chain -----" << std::endl;
	OrderList assignCopy;
	assignCopy = oList;
	std::cout << std::endl << "Copied list:" << std::endl << assignCopy << std::endl;

	std::cout << "----- Destructor call stack below -----" << std::endl;
}