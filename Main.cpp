#include "MapDriver.h"
#include "PlayerDriver.h"
#include <iostream>

int main()
{
	std::cout << "Please pick which driver you want to test "<< std::endl;
	int choice = std::cin.get();

	switch (choice)
	{
	case 0:
		playerDriver();
		break;
	case 1:
		mapDriver();
		break;
	case 2:
		//MapTest();
		break;
	case 3:
		//MapTest();
		break;
	case 4:
		//MapTest();
		break;
	default:
		std::cout << "No trolling please\n";
		break;
		
	}
	return 0;
}