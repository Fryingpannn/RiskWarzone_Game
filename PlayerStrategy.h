#pragma once

class PlayerStrategy {
public:
	virtual void toAttack();
	virtual void issueOrder();
	virtual void toDefend();
};


class HumanStrategy : PlayerStrategy {
public:
	void toAttack();
	void issueOrder();
	void toDefend();

};

class AggresivePlayerStrategy : PlayerStrategy {
public:
	void toAttack();
	void issueOrder();
	void toDefend();

};

class BenevolentPlayerStrategy : PlayerStrategy {
public:
	void toAttack();
	void issueOrder();
	void toDefend();

};

class NeutralPlayerStrategy : PlayerStrategy {
public:
	void toAttack();
	void issueOrder();
	void toDefend();

};



