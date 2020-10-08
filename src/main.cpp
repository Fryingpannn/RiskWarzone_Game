#include <iostream>
#include <vector>
#include <string>


class Test {
public:
	//std::vector<int> list;
	int hi;
};


int main() {
	Test* test2;
	test2->hi = 5;

	

	//Order* temp = *it2;
	//*it2 = *it1;
	//*it1 = temp;
	//return true;

	int ok = 2;
	int notok = 3;
	int* one = &ok;
	int* two = &notok;

	std::vector<int*> test = { one, two };
	//auto it1 = test.begin();
	//auto it2 = test.begin()+4-1;

	//int temp = *it1;
	//*it1 = *it2;
	//*it2 = temp;

	for(int i = 0; i < test.size(); i++)
		std::cout << test[i];
	
	std::string ok = "ok";

}