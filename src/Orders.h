#pragma once

#include <iostream>
#include <string>

//Order class
class Orders
{
private:
	string name;
public:
	boolean validate();
	execute();
	Order(Order copy);
	Order& operator =();
	friend ostream& operator <<(ostream& out, const Order &order);
};

class OrderList
{
	
};