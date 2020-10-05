#include "Player.h"
#include <iostream>
#include <algorithm>

Player::Player()
{
    Countries = new std::vector<int>{0};
    Cards = new std::vector<int>{0};
}

Player::Player(std::vector<int> *countriesIn, std::vector<int> *cardsIn)
{
    Countries = countriesIn;
    Cards = cardsIn;
}

std::vector<int> Player::toDefend()
{
    return *Countries;
}

std::vector<int> Player::toAttack()
{
    std::vector<int> v1 = Player::tempTerri;
    std::vector<int> v2 = *Countries;
    std::vector<int> territoriesToAttack;
    std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                        std::inserter(territoriesToAttack, territoriesToAttack.begin()));

    return territoriesToAttack;
}

void Player::issueOrder()
{
    // todo create object to add to list of orders
}

void Player::print()
{
    std::cout << "  Countries: ";
    for (auto i = Countries->begin();
         i != Countries->end(); ++i)
    {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;

    std::cout << "  Cards: ";
    for (auto i = Cards->begin();
         i != Cards->end(); ++i)
    {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;
}

Player::~Player()
{
    delete Countries;
    delete Cards;
}
