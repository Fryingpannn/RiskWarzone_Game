#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"


class Test {
public:
	Test() {};
	int hi{};

	void show() { 
		std::cout << "hi friend" << std::endl; 
	}
};

class B : public Test {
public:
	B() {};
};

int main() {
	B testFriend;
	testFriend.show();

	//std::vector<int> testo;
	//testo = {};

	OrderList oList;

	Order* o1 = new Order();
	Deploy* o2 = new Deploy();
	Deploy* o3 = new Deploy();

	oList.addToList(o1);
	oList.addToList(o2);
	oList.addToList(o3);

	std::cout << oList;

	OrderList listCopy = oList;


	oList.move(0, 2);

	std::cout << oList;

	oList.remove(0);

	std::cout << oList << std::endl;

	std::cout << listCopy << std::endl;

	return 0;
}