/////////////////////////////////////////////
// Filename:        Cards.h
//
// Description:     Header file for Implementation of Part 5 - Cards deck/hand
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

#pragma once
#include <deque>
#include <iostream>
#include <queue>
#include <vector>

#include "Orders.h"

class Card;
class Hand;
class Deck;

enum CardType {
  BOMB = 1,
  REINFORCEMENT,
  BLOCKADE,
  AIRLIFT,
  DIPLOMACY,

  EMPTY
};

class Card {
 private:
  CardType* type;

 public:
  // constructors
  Card();
  Card(CardType c);
  Card(const Card& c);
  ~Card();

  // functions
  CardType* getType();
  void Play(Hand  &h, OrderList &list, Deck& d);

  // operator overloading
  friend std::ostream& operator<<(std::ostream& out, const Card& card);
  Card& operator=(const Card& c);
};

class Hand {
 private:
  std::vector<Card*> hand;

 public:
  // constructors
  Hand();
  Hand(const Hand& h);
  ~Hand();

  // functions
  void add(CardType const &type);
  void remove(int index);
  int find(Card c);
  Card returnByPos(int pos);

  // operator overloading
  friend std::ostream& operator<<(std::ostream& out, const Hand& h);
  Hand& operator=(const Hand& h);
};

class Deck {
 private:
  std::queue<Card*> deck;
  int* size;

 public:
  // constructors
  Deck();
  Deck(int const deckSize);
  Deck(const Deck& deck);
  ~Deck();

  // functions
  Card draw(Hand& h);
  void add(CardType const type);
  int GetSize();

  // operator overloading
  friend std::ostream& operator<<(std::ostream& out, const Deck& d);
  Deck& operator=(const Deck& d);
};
