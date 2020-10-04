#include "Cards.h"
#include <time.h>
#include "Map.h"


int main() {

	srand(time(NULL));

	Deck d = Deck(10);

	Hand h = Hand();

	for (int i = 0;i < 5;i++) {
		d.draw(h);
	}

	cout << h <<endl;
	
	
	for (int i = 0;i < 5;i++) {
		h.returnByPos(0).Play(h, d);

	}
	
	return 0;
}
