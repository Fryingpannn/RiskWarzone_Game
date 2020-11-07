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
#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#include "OrdersDriver.h"
#include "Orders.h"
#include "Map.h"
#include "Cards.h"

//This driver file tests the functionalities from the Orders.h/Orders.cpp files.
 void ordersDriver() {
//when ran in debug
#ifdef _DEBUG
	 _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

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
	auto* Philippines = new Territory{ "Philippines", 3, "ASEAN", 0, 0 };
	Philippines->OwnedBy = "Zahra";
	Philippines->Armies = 6;
	auto* China = new Territory{ "China", 4, "ASEAN", 0, 0 };
	China->OwnedBy = "Stef";
	China->Armies = 1;

	//creating map to link territories
	Map* WorldMap = new Map(9, "WorldMap");
	WorldMap->AddEdges(*Malaysia, *Indonesia);
	WorldMap->AddEdges(*Indonesia, *Malaysia);
	WorldMap->AddEdges(*Singapore, *Malaysia);
	WorldMap->AddEdges(*Malaysia, *Singapore);
	WorldMap->AddEdges(*Indonesia, *Philippines);
	WorldMap->AddEdges(*Philippines, *Indonesia);
	WorldMap->AddEdges(*Philippines, *China);
	
	//creating deck & player to test orders with
	Deck* deck = new Deck(12);
	Hand hand{};
	OrderList orders{};
	std::vector<Territory*> playerOwned{};
	std::vector<Territory*> playerOwned2{};
	playerOwned.push_back(Singapore); //matthew owns only singapore
	playerOwned2.push_back(Philippines); //zahra owns only philippines
	Player* matthew = new Player(playerOwned, hand, orders, "Matthew");
	Player* zahra = new Player(playerOwned2, hand, orders, "Zahra");

	/* The territories are linked as such: Singapore->Malaysia->Indonesia->Philippines->China */

	std::cout << "\n Territories in current map are linked as such: \n" <<
		" == Singapore->Malaysia->Indonesia->Philippines->China ==" << std::endl;

	//testing valid deploy order
	std::cout << std::endl << "----- Valid Deploy -----" << std::endl << std::endl;
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << " Matthew: [Deploy] Deploying 6 armies to Singapore." << std::endl;
	Order* deploy1 = new Deploy("Matthew", 6, Singapore);
	deploy1->execute();
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;

	//testing invalid deploy order
	std::cout << std::endl << "----- Invalid Deploy (Wrong territory) -----" << std::endl << std::endl;
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;
	std::cout << " Matthew: [Deploy] Deploying 5 armies to Malaysia." << std::endl;
	Order* deploy2 = new Deploy("Matthew", 5, Malaysia);
	deploy2->execute();
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;

	//testing valid advance order with no attack
	std::cout << std::endl << "----- Valid Advance (No Attack) -----" << std::endl << std::endl;
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;
	std::cout << " Matthew: [Advance] Advancing 4 armies from Singapore to Malaysia." << std::endl;
	Order* advance1 = new Advance("Matthew", 4, Singapore, Malaysia, WorldMap, matthew, deck);
	advance1->execute();
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;

	//testing valid advance order; attack
	std::cout << std::endl << "----- Valid Advance (Attack) -----" << std::endl << std::endl;
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;
	std::cout << " Matthew: [Advance] Advancing 2 armies from Malaysia to Indonesia." << std::endl;
	Order* advance2 = new Advance("Matthew", 2, Malaysia, Indonesia, WorldMap, matthew, deck);
	advance2->execute();
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;

	//testing invalid advance order; non-adjacent territory
	std::cout << std::endl << "----- Invalid Advance (Non-adjacent Territory) -----" << std::endl << std::endl;
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;
	std::cout << " Matthew: [Advance] Advancing 3 armies from Singapore to Indonesia." << std::endl;
	Order* advance3 = new Advance("Matthew", 3, Singapore, Indonesia, WorldMap, matthew, deck);
	advance3->execute();
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;

	//testing valid airlift order on non-adjacent territory
	std::cout << std::endl << "----- Valid Airlift -----" << std::endl << std::endl;
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;
	std::cout << " Matthew: [Airlift] Airlifting 1 army from Singapore to Indonesia." << std::endl;
	Order* airlift1 = new Airlift("Matthew", 1, Singapore, Indonesia, matthew, deck);
	airlift1->execute();
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;

	//testing valid airlift order on enemy territory (failed attack)
	std::cout << std::endl << "----- Valid Airlift (Failed Attack) -----" << std::endl << std::endl;
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Philippines's owner & army count: " << Philippines->OwnedBy << ", " << Philippines->Armies << std::endl;
	std::cout << " Matthew: [Airlift] Airlifting 1 army from Singapore to Philippines." << std::endl;
	Order* airlift2 = new Airlift("Matthew", 1, Singapore, Philippines, matthew, deck);
	airlift2->execute();
	std::cout << "- Singapore's owner & army count: " << Singapore->OwnedBy << ", " << Singapore->Armies << std::endl;
	std::cout << "- Philippines's owner & army count: " << Philippines ->OwnedBy << ", " << Philippines->Armies << std::endl;

	//testing valid bomb order on enemy territory
	std::cout << std::endl << "----- Valid Bomb -----" << std::endl << std::endl;
	std::cout << "- Philippines's owner & army count: " << Philippines->OwnedBy << ", " << Philippines->Armies << std::endl;
	std::cout << " Matthew: [Bomb] Bombing Philippines." << std::endl;
	Order* bomb1 = new Bomb("Matthew", Philippines, matthew);
	bomb1->execute();
	std::cout << "- Philippines's owner & army count: " << Philippines->OwnedBy << ", " << Philippines->Armies << std::endl;

	//testing invalid bomb order on friendly territory
	std::cout << std::endl << "----- Invalid Bomb (Friendly Territory) -----" << std::endl << std::endl;
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;
	std::cout << " Matthew: [Bomb] Bombing Malaysia." << std::endl;
	Order* bomb2 = new Bomb("Matthew", Malaysia, matthew);
	bomb2->execute();
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;

	//testing valid blockade order
	std::cout << std::endl << "----- Valid Blockade -----" << std::endl << std::endl;
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;
	std::cout << " Matthew: [Blockade] Setting blockade in Malaysia." << std::endl;
	Order* blockade1 = new Blockade("Matthew", Malaysia);
	blockade1->execute();
	std::cout << "- Malaysia's owner & army count: " << Malaysia->OwnedBy << ", " << Malaysia->Armies << std::endl;

	//testing valid negotiate order
	std::cout << std::endl << "----- Valid Negotiate -----" << std::endl << std::endl;
	std::cout << " Matthew: [Negotiate] Diplomacy status set between Matthew and Zahra." 
		<< " Nullyfing all attacks between them for this turn." << std::endl;
	Order* negotiate1 = new Negotiate(matthew, zahra);
	negotiate1->execute();

	//testing attack after negotiate order was done between 2 players
	std::cout << std::endl << "----- Invalid Airlift (Diplomacy Status) -----" << std::endl << std::endl;
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;
	std::cout << "- Philippines's owner & army count: " << Philippines->OwnedBy << ", " << Philippines->Armies << std::endl;
	std::cout << " Matthew: [Airlift] Airlifting 1 army from Indonesia to Philippines." << std::endl;
	Order* airlift3 = new Airlift("Matthew", 1, Indonesia, Philippines, matthew, deck);
	airlift3->execute();
	std::cout << "- Indonesia's owner & army count: " << Indonesia->OwnedBy << ", " << Indonesia->Armies << std::endl;
	std::cout << "- Philippines's owner & army count: " << Philippines->OwnedBy << ", " << Philippines->Armies << std::endl;

	//testing valid airlift order on enemy territory (attack)
	std::cout << std::endl << "----- Valid Airlift (Successful Attack) -----" << std::endl << std::endl;
	std::cout << "- Philippines's owner & army count: " << Philippines->OwnedBy << ", " << Philippines->Armies << std::endl;
	std::cout << "- China's owner & army count: " << China->OwnedBy << ", " << China->Armies << std::endl;
	std::cout << " Matthew: [Airlift] Airlifting 2 armies from Philippines to China." << std::endl;
	Order* airlift4 = new Airlift("Zahra", 2, Philippines, China, matthew, deck);
	airlift4->execute();
	std::cout << "- Philippines's owner & army count: " << Philippines->OwnedBy << ", " << Philippines->Armies << std::endl;
	std::cout << "- China's owner & army count: " << China->OwnedBy << ", " << China->Armies << std::endl;

	std::cout << std::endl;
	delete deploy1, delete deploy2, delete advance1, delete advance2, delete advance3; delete airlift1, delete airlift2,
	delete airlift3, delete airlift4, delete bomb1, delete bomb2, delete blockade1, delete negotiate1;
	delete Malaysia, delete Indonesia, delete China;
	delete deck, delete matthew, delete zahra, delete WorldMap;

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