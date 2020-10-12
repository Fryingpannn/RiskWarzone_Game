#include "Cards.h"
#include <time.h>
#include "Map.h"
#include "Player.h"
#include "CardsDriver.h"

void CardsDeckTest() {

	srand(time(NULL));

	// create two decks
	// deck 1 is randomized with 15 cards
	// deck 2 is empty and can be manually filled for testing purposes

	Map* WorldMap = new Map(15, "WorldMap");
	Deck d = Deck(WorldMap->NumOfCountries());
	Deck d2 = Deck(0);

	d2.add(BOMB);
	d2.add(AIRLIFT);
	d2.add(DIPLOMACY);
	d2.add(BLOCKADE);
	d2.add(REINFORCEMENT);


	// create a player and an independent hand + orderlist
	Hand h = Hand();
	OrderList list;
	Player p = Player();

	// test deck 1 with player
	cout << "Deck 1 is: \n" << d << endl;

	cout << "Drawing from Deck 1:\n" << endl;

	for (int i = 0;i < 5;i++) {
		d.draw(*p.HandOfCards);
	}

	
	cout << "My hand now is: " << *p.HandOfCards << endl;


	for (int i = 0;i < 5;i++) {
		p.HandOfCards->returnByPos(0).Play(*p.HandOfCards, *p.ListOfOrders, d);

	}


	cout << "---------------------------\n" << endl;

	//test deck 2 with the independent hand and order list
	cout << "Deck 2 is:\n" << d2 << endl;
	cout << "Drawing from Deck 2:\n" << endl;

	for (int i = 0;i < 5;i++) {
		d2.draw(h);
	}

	cout << "My hand now is: " << h << endl;


	for (int i = 0;i < 5;i++) {
		h.returnByPos(0).Play(h, list, d2);

	}

}
