#include "Map.h"
#include "MapDriver.cpp"

int main()
{
	std::cout << "Please pick which driver you want to test "<< std::endl;
	int choice = std::cin.get();

	switch (choice)
	{
	case 0:
		MapTest();
		break;
	case 1:
		MapTest();
		break;
	case 2:
		MapTest();
		break;
	case 3:
		MapTest();
		break;
	case 4:
		MapTest();
		break;
	default:
		std::cout << "No trolling please\n";
		break;
		
	}
	return 0;
}