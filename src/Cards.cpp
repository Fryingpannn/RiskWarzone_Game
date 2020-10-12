/////////////////////////////////////////////
// Filename:        Cards.cpp
//
// Description:     Implementation of Part 5 - Cards deck/hand
//
// Author:          Zahra Nikbakht
//
// Group:           Sandra Buchen
//                  Le Cherng Lee
//                  Zahra Nikbakht
//                  Matthew Pan
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#include "Cards.h"
#include <stdlib.h> 



// Card class implementation

// Constructors
Card::Card() { this->type = new CardType(EMPTY); }

Card::Card(CardType c) { this->type = new CardType(c); }

Card::Card(const Card& c) { (this->type) = new CardType(*c.type); }

// Destructor
Card::~Card() {
	delete type;
	type = nullptr;
}

// Functions

CardType* Card::getType() { return (this->type); }


void Card::Play(Hand& const h, OrderList& const list, Deck& d) {

	int index = h.find(*this);
	if (index > -1) {

		CardType* type = (getType());

		d.add(*type);
		std::cout << "Playing " << *this << std::endl;

		h.remove(index);
		//TODO create an order in the order list
		switch (*getType()) {
		case CardType::BOMB:
			list.addToList(new Bomb());
			break;
		case CardType::AIRLIFT:
			list.addToList(new Airlift());
			break;
		case CardType::BLOCKADE:
			list.addToList(new Blockade());
			break;
		case CardType::DIPLOMACY:
			list.addToList(new Negotiate());
			break;
		case CardType::REINFORCEMENT:
			list.addToList(new Deploy());
			break;
		}

	}
	else {

		std::cout << "You do not have this card" << std::endl;
	}
}

// Operator overloading

Card& Card::operator=(const Card& c) {

	//check if two pointers dont point to the same address (not self assignment);
	if (this != &c){
	this->type = new CardType(*c.type);
		}
	return *this;
}

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
Hand::Hand() { this->hand = std::vector<Card*>{}; }

Hand::Hand(const Hand& h) {
	for (auto i = h.hand.begin(); i != h.hand.end(); ++i) {
		auto* card = new Card(**i);
		this->hand.push_back(card);
	}
}

// Destructor
Hand::~Hand() {
	for (auto& i : hand) {
		delete i;
		i = nullptr;
	}
}

// Functions
void Hand::add(CardType& const type) {
	if (this->hand.size() < 6) {
		hand.emplace_back(new Card(type));
	}
	else {
		std::cout << "You cannot keep any more cards in your hand" << std::endl;
	}
}

void Hand::remove(int index) {
	for (int i = index; i < hand.size() - 1; i++) {
		*hand.at(i) = *hand.at(i + 1);
	}

	delete hand.at(hand.size() - 1);
	hand.at(hand.size() - 1) = nullptr;
	hand.pop_back();
}

int Hand::find(Card c) {
	int index = -1;

	// iterate through the hand and find the index of the given card
	for (int i = 0; i < hand.size(); i++) {
		if (*(*hand.at(i)).getType() == *c.getType()) {
			index = i;
			break;
		}
	}
	return index;
}

Card Hand::returnByPos(int pos) {
	// return the card at the given position
	if (pos < hand.size()) {
		return *this->hand.at(pos);
	}
}
// Operator overloading

Hand& Hand::operator=(const Hand& h) {

	//check if two pointers dont point to the same address (not self assignment);
	if (this != &h) {
		for (auto i = h.hand.begin(); i != h.hand.end(); ++i) {
			auto* card = new Card(**i);
			this->hand.push_back(card);
		}
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Hand& h) {
	for (auto* i : h.hand) {
		out << *i << ' ';
	}
	return out;
}


// Deck class implementation

// Constructors

Deck::Deck() {
	this->deck = std::queue<Card*>{};
	this->size = new int(0);
};

Deck::Deck(int deckSize) {
	this->size = new int(deckSize);

	// fill the deck with random cards
	for (int i = 0; i < deckSize; i++) {
		CardType t = static_cast<CardType>(rand() % 5 + 1);
		deck.push(new Card(t));
	}
}

Deck::Deck(const Deck& d) {
	while (!deck.empty()) {
		delete deck.front();
		deck.front() = nullptr;
		deck.pop();
	}

	size = new int(*d.size);
	std::queue<Card*> q = (d.deck);
	while (!q.empty()) {
		deck.push(new Card(*q.front()));
		q.pop();
	}
}

// Destructor

Deck::~Deck() {
	for (int i = 0; i < deck.size(); i++) {
		delete deck.front();
		deck.front() = nullptr;
		deck.pop();
	}
	delete size;
	size = nullptr;
}

// Functions

void Deck::add(CardType const type) {

	deck.push(new Card(type));

}

Card Deck::draw(Hand& const h) {

	//draw the card on top of the deck and put it in the hand
	Card chosen = *this->deck.front();
	CardType* t = chosen.getType();
	std::cout << "drawing a card of type " << chosen << std::endl;
	delete deck.front();
	deck.front() = nullptr;
	this->deck.pop();
	h.add(*t);
	return chosen;

}


int Deck::GetSize() {

	return deck.size();

}

// Operator overloading
Deck& Deck::operator = (const Deck& d) {

	//check if two pointers dont point to the same address (not self assignment);
	if (this != &d) {
		//empty the current queue
		while (!deck.empty()) {
			delete deck.front();
			deck.front() = nullptr;
			deck.pop();
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

std::ostream& operator << (std::ostream& out, const Deck& d) {

	std::queue<Card*> q = (d.deck);
	//printing content of queue 
	while (!q.empty()) {
		out << " " << *q.front() << std::endl;
		q.pop();
	}
	return out;

}
