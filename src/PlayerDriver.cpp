#include <iostream>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include "Player.h"

int main() {
  std::cout << "Begin Player Driver\n" << std::endl;
  // Declare player 1 with nothing initialized
  Player *player1 = new Player();

  std::cout << "Player 1" << std::endl;
  std::cout << *player1 << std::endl;

  Country arr[] = {Country{"Canada", 1, "North America"}, Country{"Romania",2,"Europe"}};
  std::vector<Country> countries(arr, arr + sizeof(arr) / sizeof(Country));

  Player *player2 = new Player(countries, Hand(), Orders());

  std::cout << "Player 2" << std::endl;
  std::cout << *player2 << std::endl;

  // Copy player 2 to player 3 with copy constructor
  Player player3 = *player2;

  std::cout << "Player 3" << std::endl;
  std::cout << player3 << std::endl;

  // Use assignment operator to assign player 4 from player 2
  Player player4;
  player4 = *player2;

  std::cout << "Player 4" << std::endl;
  std::cout << player4 << std::endl;

  delete player1;
  delete player2;
  return 0;
}