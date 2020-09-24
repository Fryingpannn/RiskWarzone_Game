#pragma once
#include <vector> 
#include <iostream> 

using namespace std;

enum CardType {
	BOMB = 1,
	REINFORCEMENT,
	BLOCKADE,
	AIRLIFT,
	DIPLOMACY,
	SPY
};

class Card {
private:
	CardType* type;

public:
	Card(CardType& c);
	void Play();
};



class Deck {

private:
	vector<Card>* deck;
	int* size;
public:

	Deck(int& const deckSize);
	Deck(Deck& deck);

	Card draw(Hand& hand);
	void add(CardType& const type);

};

class Hand {

private:
	vector<Card>* hand;

public:
	Hand();
	Hand(Hand& h);
	void add(CardType& const type);
	void remove(Card& const Card);

};

ostream& operator << (ostream& out, const Card& card);
ostream& operator << (ostream& out, const Hand& hand);
ostream& operator << (ostream& out, const Deck& deck);
