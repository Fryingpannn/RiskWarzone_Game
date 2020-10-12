#include "PlayerDriver.h"

#include <iostream>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "Player.h"

/**
 * Driver method for the player class to demonstrate its behavior.
 */
void playerDriver() {
  std::cout << "Begin Player Driver\n" << std::endl;

  // Temporary runner variables creation until proper objects are connected
  // Used only for testing the behavior of the player class
  auto *country1 = new Territory("Canada", 1, "NA", 0,0);
  auto *country2 = new Territory("Romania", 2, "Europe", 0, 0);
  auto *country3 = new Territory("USA", 3, "NA", 0, 0);
  auto *country4 = new Territory("Croatia", 4, "Europe", 0, 0);
  auto *country5 = new Territory("Germany", 5, "Europe" ,0, 0);
  auto *country6 = new Territory("Chile", 6, "Latin America" ,0, 0);
  auto *country7 = new Territory("Australia", 7, "Oceania" ,0, 0);
  auto *country8 = new Territory("China", 8, "Asia", 0, 0);

  std::vector<Territory *> allCountries;
  allCountries.push_back(country1);
  allCountries.push_back(country2);
  allCountries.push_back(country3);
  allCountries.push_back(country4);
  allCountries.push_back(country5);
  allCountries.push_back(country6);
  allCountries.push_back(country7);
  allCountries.push_back(country8);

  std::vector<Territory *> countries;
  countries.push_back(country1);
  countries.push_back(country2);

  auto *card1 = new Card(BOMB);
  auto *card2 = new Card(AIRLIFT);
  Hand hand;
  hand.add(*card1->getType());
  hand.add(*card2->getType());

  auto *order = new Deploy();
  OrderList orderlist;
  orderlist.addToList(order);

  ////////////////////////////////////////////////////////////////////////
  // Start of tests
  ////////////////////////////////////////////////////////////////////////

  std::cout << "Testing default constructor of player" << std::endl;
  auto *player1 = new Player();
  std::cout << *player1 << std::endl;

  std::cout << "Testing regular constructor of player." << std::endl;
  auto *player2 = new Player(countries, hand, orderlist);
  std::cout << "Player2" << std::endl;
  std::cout << *player2 << std::endl;

  std::cout << "Testing copy constructor of player." << std::endl;
  auto player3 = *player2;
  std::cout << "Player 3" << std::endl;
  std::cout << player3 << std::endl;

  std::cout << "Testing issue order method of player." << std::endl;
  player3.issueOrder();
  std::cout << "Player3" << std::endl;
  std::cout << player3 << std::endl;

  std::cout << "Testing assignment operator of player." << std::endl;
  Player player4;
  player4 = *player2;
  std::cout << "Player4" << std::endl;
  std::cout << player4 << std::endl;

  std::cout << "Testing toAttack() method " << std::endl;
  std::cout << "Player2" << std::endl;
  auto toAttack = player2->toAttack();
  for (auto i = toAttack.begin(); i != toAttack.end(); ++i) {
    std::cout << **i << " ";
  }

  std::cout << "\n\nTesting toDefend() method " << std::endl;
  std::cout << "Player2 to defend " << std::endl;
  auto toDefend = player2->toDefend();
  for (auto i = toDefend.begin(); i != toDefend.end(); ++i) {
    std::cout << **i << " ";
  }

  std::cout << "\n\nFinished player driver." << std::endl;

  ////////////////////////////////////////////////////////////////////////
  // End of tests
  ////////////////////////////////////////////////////////////////////////

  // Clearing memory use
  delete player1;
  delete player2;
  player1 = nullptr;
  player2 = nullptr;
  allCountries.clear();
  countries.clear();
}
