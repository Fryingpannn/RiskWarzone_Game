#include "Cards.h"
#include <time.h>

int main() {

	srand(time(NULL));

	Deck d = Deck(10);

	Hand h = Hand();

	for (int i = 0;i < 5;i++) {
		d.draw(h);
	}


	for (int i = 0;i < 5;i++) {
		h.returnFirst().Play(h, d);

	}

	return 0;
}