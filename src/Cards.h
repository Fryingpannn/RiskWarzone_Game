#pragma once
#include <vector> 
#include <iostream> 
#include <queue> 
#include <deque> 

using namespace std;


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

	//constructors
	Card();
	Card(CardType c);
	Card(const Card& c);
	~Card();

	//functions
	CardType* getType();
	void Play(Hand& h, Deck& d);

	//operator overloading
	friend ostream& operator << (ostream& out, const Card& card);
	void operator = (const Card& c);
};


class Hand {

private:
	vector<Card>* hand;

public:

	//constructors
	Hand();
	Hand(const Hand& h);
	~Hand();

	//functions
	void add(CardType& const type);
	void remove(int index);
	int find(Card c);
	Card returnByPos(int pos);

	//operator overloading
	friend ostream& operator << (ostream& out, const Hand& h);
	void operator = (const Hand& h);

};

class Deck {

private:
	queue<Card>* deck;
	int* size;
public:

	//constructors
	Deck(int const deckSize);
	Deck(const Deck& deck);
	~Deck();

	//functions
	Card draw(Hand& h);
	void add(CardType const type);
	int GetSize();

	//operator overloading
	friend ostream& operator << (ostream& out, const Deck& d);
	void operator = (const Deck& d);

};
