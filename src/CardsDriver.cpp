#include "Cards.h"
#include <time.h>
#include "Map.h"
#include "CardsDriver.h"

void CardsDeckTest() {

	srand(time(NULL));

	// create two decks and a hand
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

	Hand h = Hand();

	cout << "Deck 1 is: \n" << d << endl;

	cout << "Drawing from Deck 1:\n" << endl;

	for (int i = 0;i < 5;i++) {
		d.draw(h);
	}

	cout << "My hand now is: " << h << endl;


	for (int i = 0;i < 5;i++) {
		h.returnByPos(0).Play(h, d);

	}


	cout << "---------------------------\n" << endl;

	cout << "Deck 2 is:\n" << d2 << endl;
	cout << "Drawing from Deck 2:\n" << endl;

	for (int i = 0;i < 5;i++) {
		d2.draw(h);
	}

	cout << "My hand now is: " << h << endl;


	for (int i = 0;i < 5;i++) {
		h.returnByPos(0).Play(h, d2);

	}

}
