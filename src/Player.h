#pragma once
#include <vector>

class Player
{
    std::vector<int> *Countries;
    std::vector<int> *Cards;

    Player();
    Player(std::vector<int> *countriesIn, std::vector<int> *cardsIn);

    std::vector<int> toDefend();
    std::vector<int> toAttack();
    void issueOrder();
    void doSome();
};
