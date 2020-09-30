#pragma once
#include <vector> 
#include <iostream> 
#include <queue> 
#include <deque> 

using namespace std;


/*
TODO1
Make the size of the deck equal to the size of the territories

TODO2
In the play() method, add a special order to the list of orders

TODO3
Make sure all class members are of type pointer

TODO4
Add Destructors

TODO5
Complete copy constructors and assignment operatorover loading
*/

class Card;
class Hand;
class Deck;


enum CardType {
	BOMB = 1,
	REINFORCEMENT,
	BLOCKADE,
	AIRLIFT,
	DIPLOMACY,
	SPY,
	EMPTY
};


class Card {
private:
	CardType type;

public:

	Card();
	Card(CardType c);
	Card(const Card& c);

	CardType getType();

	void Play(Hand& h, Deck& d);
	friend ostream& operator << (ostream& out, const Card& card);

};


class Hand {

private:
	vector<Card>* hand;

public:

	Hand();
	Hand(const Hand& h);
	void add(CardType& const type);
	void remove(int index);
	int find(Card c);
	Card returnFirst();
	friend ostream& operator << (ostream& out, const Hand& h);

};

class Deck {

private:
	queue<Card>* deck;
	int size;
public:

	Deck(int const deckSize);
	Deck(const Deck& deck);

	Card draw(Hand& h);
	void add(CardType& const type);
	friend ostream& operator << (ostream& out, const Deck& d);

};



