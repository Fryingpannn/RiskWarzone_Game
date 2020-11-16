/////////////////////////////////////////////
// Filename:        Player.h
//
// Description:     Driver for Implementation of Part 3 - Player
//
// Author:          Sandra Buchen - 26317987
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

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
  auto *Malaysia = new Territory{"Malaysia", 0, "ASEAN", 0, 0};
  auto *Indonesia = new Territory{"Indonesia", 1, "ASEAN", 0, 0};
  auto *Singapore = new Territory{"Singapore", 2, "ASEAN", 0, 0};
  auto *Philippine = new Territory{"Philippine", 3, "ASEAN", 0, 0};
  auto *Thailand = new Territory{"Thailand", 4, "ASEAN", 0, 0};
  auto *Vietnam = new Territory{"Vietnam", 5, "ASEAN", 0, 0};
  auto *Japan = new Territory{"Japan", 6, "EastAsia", 0, 0};
  auto *Korea = new Territory{"Korea", 7, "EastAsia", 0, 0};
  auto *China = new Territory{"China", 8, "EastAsia", 0, 0};

  Map *WorldMap = new Map(9, "WorldMap");
  WorldMap->AddEdges(*Malaysia, *Vietnam);
  WorldMap->AddEdges(*Malaysia, *Indonesia);
  WorldMap->AddEdges(*Indonesia, *Malaysia);
  WorldMap->AddEdges(*Indonesia, *Philippine);
  WorldMap->AddEdges(*Singapore, *Vietnam);
  WorldMap->AddEdges(*Singapore, *Malaysia);
  WorldMap->AddEdges(*Vietnam, *Malaysia);
  WorldMap->AddEdges(*Vietnam, *Thailand);
  WorldMap->AddEdges(*Japan, *Korea);
  WorldMap->AddEdges(*China, *Korea);
  WorldMap->AddEdges(*Malaysia, *Japan);

  // Creating a list of countries to be owned by a player
  std::vector<Territory *> countries;
  countries.push_back(China);
  countries.push_back(Malaysia);

  // Creating a deck the player can draw cards from
  Deck d = Deck(WorldMap->NumOfCountries());
  Hand hand{};
  d.draw(hand);
  d.draw(hand);

  // Creating orders to be owned by a player
  auto *order = new Deploy();
  OrderList orderlist;
  orderlist.addToList(order);

  ////////////////////////////////////////////////////////////////////////
  // Start of tests
  ////////////////////////////////////////////////////////////////////////

  std::cout << "\nTesting default constructor of player" << std::endl;
  auto *player1 = new Player();
  player1->PID = "Player[1]";
  d.draw(*(player1->HandOfCards));
  std::cout << *player1 << std::endl;

  std::cout << "\nTesting regular constructor of player." << std::endl;
  auto *player2 = new Player(countries, hand, orderlist, "Player[2]");
  std::cout << "------ Player2 ------" << std::endl;
  std::cout << *player2 << std::endl;

  std::cout << "\nTesting copy constructor of player." << std::endl;
  auto *player3 = new Player(*player2);
  d.draw(*(player3->HandOfCards));
  std::cout << "------ Player3 ------" << std::endl;
  std::cout << *player3 << std::endl;

  //std::cout << "\nTesting issue order method of player." << std::endl;
  //player3->issueOrder(*WorldMap, d);
  //std::cout << "------ Issue Order ------" << std::endl;
  //std::cout << *player3 << std::endl;

  //std::cout << "\nTesting assignment operator of player." << std::endl;
  //Player *player4 = new Player();
  //*player4 = *player2;
  //d.draw(*(player4->HandOfCards));
  //std::cout << "------ Player4 ------" << std::endl;
  //std::cout << *player4 << std::endl;

  //std::cout << "\nTesting toAttack() method " << std::endl;
  //std::cout << "------ toAttack() ------" << std::endl;
  //auto toAttack = player2->toAttack(*WorldMap);
  //for (auto i = toAttack.begin(); i != toAttack.end(); ++i) {
  //  std::cout << **i << " ";
  //}

  //std::cout << "\n\nTesting toDefend() method " << std::endl;
  //std::cout << "------ toDefend() ------" << std::endl;
  //auto toDefend = player2->toDefend();
  //for (auto i = toDefend.begin(); i != toDefend.end(); ++i) {
  //  std::cout << **i << " ";
  //}

  std::cout << "\n\nFinished player driver." << std::endl;

  ////////////////////////////////////////////////////////////////////////
  // End of tests
  ////////////////////////////////////////////////////////////////////////

  // Clearing memory use
  delete WorldMap;
  WorldMap = nullptr;

  delete player1;
  delete player2;
  delete player3;
  //delete player4;
  player1 = nullptr;
  player2 = nullptr;
  player3 = nullptr;
  //player4 = nullptr;
  countries.clear();
}
