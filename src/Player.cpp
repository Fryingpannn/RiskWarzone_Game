#include "Player.h"
#include <iostream>

Player::Player()
{
    std::cout << "player default constructor" << std::endl;
    std::vector<int> *Countries = new std::vector<int>[1];
    std::vector<int> *Cards = new std::vector<int>[1];
}

Player::Player(std::vector<int> *countriesIn, std::vector<int> *cardsIn)
{
    Countries = countriesIn;
    Cards = cardsIn;
}

std::vector<int> Player::toDefend()
{
    std::vector<int> countriesToDefend(1);
    return countriesToDefend;
}

std::vector<int> Player::toAttack()
{
    std::vector<int> countriesToAttack(1);
    return countriesToAttack;
}

void Player::issueOrder()
{
    // todo create object to add to list of orders
}

void Player::doSome()
{
    std::cout << "doing something" << std::endl;
}