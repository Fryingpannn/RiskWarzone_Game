/////////////////////////////////////////////
// Filename:        Cards.cpp
//
// Description:     Implementation of Part 5 - Cards deck/hand
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

#include "Cards.h"

#include <stdlib.h>

#include "Player.h"

// Card class implementation

// Constructors

/**
 * Default constructor initialize the type to EMPTY.
 */
Card::Card() { this->type = new CardType(EMPTY); }

/**
 * Constructor with given parameters.
 *
 * @param c a card type to assign to the current card.
 */

Card::Card(CardType c) { this->type = new CardType(c); }

/**
 * Copy constructor that creates a deep copy of a Card object.
 *
 * @param c The object to copy.
 */
Card::Card(const Card& c) { (this->type) = new CardType(*c.type); }

// Destructor

/**
 * Destructor of the card object.
 */
Card::~Card() {
  delete type;
  type = nullptr;
}

// Functions

/**
 * A function that returns a pointer to the type of the card.
 *
 * @return pointer to CardType
 */
CardType* Card::getType() { return (this->type); }

/**
 * A function that removes the card from the hand, adds it to the deck and
 * creates the associated order in the given orderlist.
 *
 * @param h The object hand that includes the card.
 * @param list The orderlist where the order created will be added to.
 * @param d The object Deck that the card will be return to.
 * @return void
 */
void Card::Play(Player& p, Hand& h, Deck& d) {
  int index = h.find(*this);
  if (index > -1) {
    CardType* type = (getType());

    d.add(*type);
    std::cout << "Playing " << *this << std::endl;

    h.remove(index);

    switch (*getType()) {
      case CardType::BOMB:
        p.createBomb();
        break;
      case CardType::AIRLIFT:
        p.createAirlift();
        break;
      case CardType::BLOCKADE:
        p.createBlockade();
        break;
      case CardType::DIPLOMACY:
        p.createNegotiate();
        break;
      case CardType::REINFORCEMENT:
        p.createDeploy();
        break;
    }

  } else {
    std::cout << "You do not have this card" << std::endl;
  }
}

// Operator overloading

/**
 * Overloaded assignment operator that create a deep copy of a card object.
 *
 * @param c The object to equate.
 */
Card& Card::operator=(const Card& c) {
  // check if two pointers dont point to the same address (not self assignment);
  if (this != &c) {
    delete this->type;
    this->type = new CardType(*c.type);
  }
  return *this;
}

/**
 * Overloaded stream operator for cards
 *
 * @param out The stream object.
 * @param card The card object to print.
 */
std::ostream& operator<<(std::ostream& out, const Card& card) {
  switch (*card.type) {
    case CardType::BOMB:
      return out << "Bomb";
      break;
    case CardType::AIRLIFT:
      return out << "Airlift";
      break;
    case CardType::BLOCKADE:
      return out << "Blockade";
      break;
    case CardType::DIPLOMACY:
      return out << "Diplomacy";
      break;
    case CardType::REINFORCEMENT:
      return out << "Reinforcement";
      break;
    case CardType::EMPTY:
      return out << "EMPTY";
      break;
  }
  return out;
}

// Hand class implementation

// Constructors

/**
 * Default constructor initialize the hand member to an empty vector.
 */
Hand::Hand() { this->hand = std::vector<Card*>{}; }

/**
 * Copy constructor that creates a deep copy of a Hand object.
 *
 * @param h The object to copy.
 */
Hand::Hand(const Hand& h) {
  for (auto i = h.hand.begin(); i != h.hand.end(); ++i) {
    auto* card = new Card(**i);
    this->hand.push_back(card);
  }
}

// Destructor
/**
 * Destructor of the hand object.
 */
Hand::~Hand() {
  if (!hand.empty()) {
    for (auto& i : hand) {
      delete i;
      i = nullptr;
    }
  } else {
    hand.clear();
  }
}

// Functions

/**
 * A function that creates and adds a card of the given type to the hand object.
 *
 * @param type A CardType
 * @return void
 */
void Hand::add(CardType const& type) {
  if (this->hand.size() < 6) {
    hand.emplace_back(new Card(type));
  } else {
    std::cout << "You cannot keep any more cards in your hand" << std::endl;
  }
}

/**
 * A function that removes the card at the given position from the hand.
 *
 * @param index The position of the card that should be removed
 * @return void
 */
void Hand::remove(int index) {
  for (unsigned int i = index; i < hand.size() - 1; i++) {
    *hand.at(i) = *hand.at(i + 1);
  }

  auto it = this->hand.end() - 1;
  delete *it;
  this->hand.erase(it);
}

/**
 * A function that finds the first card of the same time as the given card in
 * the hand and returns its position. If the card is not found, returns -1
 *
 * @param c The card that needs to be found
 * @return smallest index of the given card
 */
int Hand::find(Card c) {
  int index = -1;

  // iterate through the hand and find the index of the given card
  for (unsigned int i = 0; i < hand.size(); i++) {
    if (*(*hand.at(i)).getType() == *c.getType()) {
      index = i;
      break;
    }
  }
  return index;
}

/**
 * A function that returns the card at a given index.
 *
 * @param pos The position of the card that should be returned
 * @return A Card object
 */
Card Hand::returnByPos(int pos) {
  // return the card at the given position
  if (pos < hand.size()) {
    return *this->hand.at(pos);
  }
}

int Hand::size() { return hand.size(); }

// Operator overloading

/**
 * Overloaded assignment operator that create a deep copy of a hand object.
 *
 * @param h The object to equate.
 */
Hand& Hand::operator=(const Hand& h) {
  // check if two pointers dont point to the same address (not self assignment);
  if (this != &h) {
    for (auto i = h.hand.begin(); i != h.hand.end(); ++i) {
      auto* card = new Card(**i);
      this->hand.push_back(card);
    }
  }
  return *this;
}

/**
 * Overloaded stream operator for hand
 *
 * @param out The stream object.
 * @param h The hand to print.
 */
std::ostream& operator<<(std::ostream& out, const Hand& h) {
  for (auto* i : h.hand) {
    out << *i << ' ';
  }
  return out;
}

// Deck class implementation

// Constructors

// Constructors

/**
 * Default constructor initialize the deck members to their default value.
 */
Deck::Deck() {
  this->deck = std::queue<Card*>{};
  this->size = new int(0);
};

/**
 * Constructor with given parameters. A deck of the given size is created and
 * filled with random cards.
 *
 * @param deckSize the size of the deck to be created.
 */
Deck::Deck(int deckSize) {
  this->size = new int(deckSize);

  // fill the deck with random cards
  for (int i = 0; i < deckSize; i++) {
    CardType t = static_cast<CardType>(rand() % 5 + 1);
    deck.push(new Card(t));
  }
}

/**
 * Copy constructor that creates a deep copy of a Deck object.
 *
 * @param d The object to copy.
 */
Deck::Deck(const Deck& d) {
  while (!deck.empty()) {
    Card* p = deck.front();
    deck.pop();

    // memory should be freed here
    delete p;
    p = nullptr;
  }

  size = new int(*d.size);
  std::queue<Card*> q = (d.deck);
  while (!q.empty()) {
    deck.push(new Card(*q.front()));
    q.pop();
  }
}

// Destructor
/**
 * Destructor of the deck object.
 */
Deck::~Deck() {
  while (!deck.empty()) {
    Card* p = deck.front();
    deck.pop();

    // memory should be freed here
    delete p;
    p = nullptr;
  }
  delete size;
  size = nullptr;
}

// Functions

/**
 * A function that adds a card of the given type to the deck.
 *
 * @param type A CardType
 * @return void
 */
void Deck::add(CardType const type) { deck.push(new Card(type)); }

/**
 * A function that removes the front card in the queue and puts it in the given
 * hand object and returns that card.
 *
 * @param h A Hand object
 * @return A Card object
 */
Card Deck::draw(Hand& h) {
  // draw the card on top of the deck and put it in the hand
  Card chosen = *this->deck.front();
  CardType* t = chosen.getType();
  std::cout << "drawing a card of type " << chosen << std::endl;
  // memory should be freed here
  Card* p = deck.front();
  deck.pop();
  delete p;
  p = nullptr;

  h.add(*t);
  return chosen;
}

/**
 * A function that returns size of the deck
 *
 * @return size of the deck
 */
int Deck::GetSize() { return deck.size(); }

// Operator overloading
/**
 * Overloaded assignment operator that create a deep copy of a deck object.
 *
 * @param d The object to equate.
 */
Deck& Deck::operator=(const Deck& d) {
  // check if two pointers dont point to the same address (not self assignment);
  if (this != &d) {
    // empty the current queue
    while (!deck.empty()) {
      Card* p = deck.front();
      deck.pop();

      // memory should be freed here
      delete p;
      p = nullptr;
    }

    *size = *d.size;
    std::queue<Card*> q = (d.deck);
    // fill te queue with
    while (!q.empty()) {
      deck.push(new Card(*q.front()));
      q.pop();
    }
  }
  return *this;
}

/**
 * Overloaded stream operator for deck
 *
 * @param out The stream object.
 * @param d The deck to print.
 */
std::ostream& operator<<(std::ostream& out, const Deck& d) {
  std::queue<Card*> q = (d.deck);
  // printing content of queue
  while (!q.empty()) {
    out << " " << *q.front() << std::endl;
    q.pop();
  }
  return out;
}
