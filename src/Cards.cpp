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

	this->type = new CardType(EMPTY);

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


void Card::Play(Player& p, Deck& d) {

	int index = p.Cards->find(*this);
	if (index > -1) {

		CardType* type = (getType());

		d.add(*type);
		cout << "Playing " << *this << endl;

		p.Cards->remove(index);
		//TODO create an order in the order list
		//p.Orders->addToList(new Order("Bomb"));
	}
	else {

		cout << "You do not have this card" << endl;
	}
}

// Operator overloading

Card& Card::operator = (const Card& c) {

	*this->type =  *(c.type);
	return *this;

}

ostream& operator << (ostream& out, const Card& card) {

	switch (*(card.type)) {
	case CardType::BOMB:
		return cout << "Bomb";
		break;
	case CardType::AIRLIFT:
		return cout << "Airlift";
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
Hand::Hand() = default;

Hand::Hand(const Hand& h) {

	for (int i = 0; i < h.hand.size(); i++) {
		hand.emplace_back(new Card(*h.hand.at(i)));
	}
}

// Destructor
Hand::~Hand() {

	for (int i = 0; i < hand.size(); i++) {
		delete hand.at(i);
		hand.at(i) = nullptr;
		hand.pop_back();
	}
	
}

// Functions

void Hand::add(CardType& const type) {

	if (this->hand.size() < 6) {
		hand.emplace_back(new Card(type));
	}
	else {
		cout << "You cannot keep any more cards in your hand" << endl;
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

Hand& Hand::operator = (const Hand& h) {

	for (int i = 0; i < hand.size(); i++) {
		delete hand.at(i);
		hand.at(i) = nullptr;
		hand.pop_back();
	}

	for (int i = 0; i < h.hand.size(); i++) {
		hand.emplace_back(new Card(*h.hand.at(i)));
	}
	return *this;
}

ostream& operator << (ostream& out, const Hand& h) {

	for (int i = 0; i < h.hand.size(); i++) {
		out << *(h.hand.at(i)) << ' ';
	}
	return out;

}


// Deck class implementation

// Constructors

Deck::Deck() = default;

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
	queue<Card*> q = (d.deck);
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
	cout << "drawing a card of type " << chosen << endl;
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

	//empty the current queue
	while (!deck.empty()) {
		delete deck.front();
		deck.front() = nullptr;
		deck.pop();
	}

	*size = *d.size;
	queue<Card*> q = (d.deck);
	// fill te queue with 
	while (!q.empty()) {
		deck.push(new Card(*q.front()));
		q.pop();
	}
	return *this;
}

ostream& operator << (ostream& out, const Deck& d) {

	queue<Card*> q = (d.deck);
	//printing content of queue 
	while (!q.empty()) {
		out << " " << *q.front() << endl;
		q.pop();
	}
	return out;

}
