#include <iostream>
#include <vector>


int main() {
	std::vector<int> test = { 1,2,3,4 };
	auto it = test.begin();
	std::cout << *it << std::endl;

}