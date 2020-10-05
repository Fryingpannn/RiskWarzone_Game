#pragma once
#include <vector>
#include <ostream>

class Player
{

public:
    std::vector<int> *Countries;
    std::vector<int> *Cards;

    std::vector<int> tempTerri{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Player();
    Player(std::vector<int> *countriesIn, std::vector<int> *cardsIn);

    std::vector<int> toDefend();
    std::vector<int> toAttack();
    void issueOrder();

    void print();
    ~Player();
};
