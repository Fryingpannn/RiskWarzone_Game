/*
TODO1
Make the size of the deck equal to the size of the territories
TODO2
In the play() method, add a special order to the list of orders

*/
#include "Cards.h"
#include <stdlib.h> 


// Card class implementation

// Constructors 
Card::Card() {

	*this->type = EMPTY;

}

Card::Card(CardType c) {

	(this->type) = new CardType(c);

}

Card::Card(const Card& c) {

	(this->type) = new CardType(*(c.type));

}

// Destructor
Card::~Card() {

	delete type;
	type = nullptr;

}

// Functions

CardType* Card::getType() {

	return (this->type);
}


void Card::Play(Hand& h, Deck& d) {

	int index = h.find(*this);
	if (index > -1) {

		CardType* type = (getType());

		d.add(*type);
		cout << "Playing " << *this << endl;

		h.remove(index);
		//TODO create an order in the order list
	}
	else {

		cout << "You do not have this card" << endl;
	}
}

// Operator overloading

void Card::operator = (const Card& c) {

	this->type = new CardType(*(c.type));

}

ostream& operator << (ostream& out, const Card& card) {

	switch (*(card.type)) {
	case CardType::BOMB:
		return cout << "Bomb";
		break;
	case CardType::AIRLIFT:
		return cout << "Airlift";
		break;
	case CardType::SPY:
		return cout << "Spy";
		break;
	case CardType::BLOCKADE:
		return cout << "Blockade";
		break;
	case CardType::DIPLOMACY:
		return cout << "Diplomacy";
		break;
	case CardType::REINFORCEMENT:
		return cout << "Reinforcement";
		break;
	case CardType::EMPTY:
		return cout << "EMPTY";
		break;

	}

}


// Hand class implementation

// Constructors
Hand::Hand() {


	hand = new vector<Card>;


}

Hand::Hand(const Hand& h) {

	this->hand = new vector<Card>{ *h.hand };
}

// Destructor
Hand::~Hand() {

	delete hand;
	hand = nullptr;

}

// Functions

void Hand::add(CardType& const type) {


	Card c = (Card(type));
	hand->emplace_back(c);

}

void Hand::remove(int index) {


	for (int i = index; i < hand->size() - 1; i++) {
		hand->at(i) = hand->at(i + 1);
	}

	hand->pop_back();

}

int Hand::find(Card c) {

	int index = -1;

	// iterate through the hand and find the index of the given card
	for (int i = 0; i < hand->size(); i++) {
		if (*hand->at(i).getType() == *c.getType()) {
			index = i;
		}
	}
	return index;

}


Card Hand::returnByPos(int pos) {

	// return the card at the given position
	if (pos <= hand->size()) {
		return this->hand->at(pos);
	}
}


// Operator overloading

void Hand::operator = (const Hand& h) {

	hand = new vector<Card>{ *h.hand };

}

ostream& operator << (ostream& out, const Hand& h) {

	for (int i = 0; i < h.hand->size(); i++) {
		out << (h.hand->at(i)) << ' ';
	}
	return out;

}


// Deck class implementation

// Constructors
Deck::Deck(int deckSize) {

	deck = new queue<Card>;
	this->size = new int(deckSize);

	// fill the deck with random cards
	for (int i = 0; i < deckSize; i++) {

		CardType t = static_cast<CardType>(rand() % 6 + 1);
		Card c = Card(t);
		deck->push(c);
	}

}

Deck::Deck(const Deck& deck) {

	size = new int(*deck.size);
	this->deck = new queue<Card>{ *deck.deck };
}

// Destructor

Deck::~Deck() {

	delete deck;
	deck = nullptr;
	delete size;
	size = nullptr;
}

// Functions

void Deck::add(CardType& const type) {

	Card c = (Card(type));
	deck->push(c);

}

Card Deck::draw(Hand& const h) {

	//draw the card on top of the deck and put it in the hand
	Card chosen = this->deck->front();
	CardType* t = chosen.getType();
	cout << "drawing a card of type " << chosen << endl;
	this->deck->pop();
	h.add(*t);
	return chosen;

}

// Operator overloading
void Deck::operator = (const Deck& d) {

	size = new int(*d.size);
	this->deck = new queue<Card>{ *d.deck };

}

ostream& operator << (ostream& out, const Deck& d) {

	queue<Card> q = *(d.deck);
	//printing content of queue 
	while (!q.empty()) {
		out << " " << q.front() << endl;
		q.pop();
	}
	return out;

}

