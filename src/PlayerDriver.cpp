#include "Player.h"
#include <iostream>

int main()
{
    std::cout << "Begin Player Driver" << std::endl;
    // Declare player 1 with nothing initialized
    Player *player1 = new Player();

    std::cout << "Player 1" << std::endl;
    player1->print();

    // Declare player 2 with 3 territories, 3 cards
    std::vector<int> *territories = new std::vector<int>{1, 2, 3};
    std::vector<int> *cards = new std::vector<int>{4, 5, 6};
    Player *player2 = new Player(territories, cards);

    std::cout << "Player 2" << std::endl;

    player2->print();

    delete player1;
    delete player2;
    delete territories;
    delete cards;
    return 0;
}