/////////////////////////////////////////////
// Filename:        main.cpp
//
// Description:     Driver file controler to demonstrate the functionality of
// the MapLoader
//
// Author:          Stefan Russo - 26683320
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#include <stdlib.h>

#include <iostream>
#include <string>

#include "CardsDriver.h"
#include "MapDriver.h"
#include "MapLoaderDriver.hpp"
#include "OrdersDriver.h"
#include "PlayerDriver.h"

void displayMenu();

int main() {
  std::cout << "Assignment 1 - Demo" << std::endl;
  std::cout << "Main Menu" << std::endl;
  std::cout << "========================" << std::endl;
  char choice;
  bool running = true;

loop:
  while (running) {
    std::cout << "1. Map driver" << std::endl;
    std::cout << "2. MapLoader driver" << std::endl;
    std::cout << "3. Player driver" << std::endl;
    std::cout << "4. Orders driver" << std::endl;
    std::cout << "5. Cards Driver" << std::endl;
    std::cout << "Please enter your choice 1-5 (q to quit): ";
    std::cin >> choice;

    switch (choice) {
      case '1':
        mapDriver();
        goto loop;
      case '2':
        mapLoaderDriver();
        goto loop;
      case '3':
        playerDriver();
        goto loop;
      case '4':
        ordersDriver();
        goto loop;
      case '5':
        CardsDeckTest();
        goto loop;
      case 'q':
      case 'Q':
        running = false;
        break;
      default:
        std::cout << "Invalid option." << std::endl;
        break;
    }
    return 0;
  }
}
void displayMenu() {
  std::cout << "1. Map driver" << std::endl;
  std::cout << "2. MapLoader driver" << std::endl;
  std::cout << "3. Player driver" << std::endl;
  std::cout << "4. Orders driver" << std::endl;
  std::cout << "5. Cards Driver" << std::endl;
}
