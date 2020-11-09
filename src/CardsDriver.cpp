/////////////////////////////////////////////
// Filename:        CardsDriver.cpp
//
// Description:     Driver file for Implementation of Part 5 - Cards deck/hand
//
// Author:          Zahra Nikbakht - 40138253
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#include "CardsDriver.h"

#include <time.h>

#include "Cards.h"
#include "Map.h"
#include "Player.h"

void CardsDeckTest() {
  srand(time(NULL));

  // create two decks
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

  // create a player and an independent hand + orderlist
  Hand h = Hand();
  OrderList list;
  Player p = Player();

  // test deck 1 with player
  std::cout << "Deck 1 is: \n" << d << std::endl;

  std::cout << "Drawing from Deck 1:\n" << std::endl;

  for (int i = 0; i < 5; i++) {
    d.draw(*p.HandOfCards);
  }

  std::cout << "My hand now is: " << *p.HandOfCards << std::endl;

  //for (int i = 0; i < 5; i++) {
  //  p.HandOfCards->returnByPos(0).Play(*p.HandOfCards, *p.ListOfOrders, d);
  //}

  std::cout << "---------------------------\n" << std::endl;

  // test deck 2 with the independent hand and order list
  std::cout << "Deck 2 is:\n" << d2 << std::endl;
  std::cout << "Drawing from Deck 2:\n" << std::endl;

  for (int i = 0; i < 5; i++) {
    d2.draw(h);
  }

  std::cout << "My hand now is: " << h << std::endl;

  //for (int i = 0; i < 5; i++) {
  //  h.returnByPos(0).Play(h, list, d2);
  //}

  delete WorldMap;
  WorldMap = nullptr;
}
