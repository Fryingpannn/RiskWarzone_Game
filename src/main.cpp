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

#include "GameEngine.h"

void displayA1DemoMenu();
void displayA2DemoMenu();
void displayAssginmentMenu();
void a1DemoHandler();
void a2DemoHandler();
void doA2MainGame();

int main()
{
  std::cout << "Group D26 Assignment Demos" << std::endl;
  std::cout << "Main Menu" << std::endl;
  std::cout << "========================" << std::endl;
  char choice;
  bool running = true;

  while (running)
  {
    std::cout << "1. Assignment 1 Demos" << std::endl;
    std::cout << "2. Assignment 2 Demos" << std::endl;
    std::cout << "Please enter your choice 1-2 (q to quit): ";
    std::cin >> choice;

    switch (choice)
    {
    case '1':
      a1DemoHandler();
      break;
    case '2':
      a2DemoHandler();
      break;
    case 'q':
    case 'Q':
      running = false;
      break;
    default:
      std::cout << "Invalid option." << std::endl;
      break;
    }
  }

  return 0;
}
void displayA1DemoMenu()
{
  std::cout << "1. Map driver" << std::endl;
  std::cout << "2. MapLoader driver" << std::endl;
  std::cout << "3. Player driver" << std::endl;
  std::cout << "4. Orders driver" << std::endl;
  std::cout << "5. Cards Driver" << std::endl;
}

void displayA2DemoMenu()
{
  std::cout << "1. Run main game" << std::endl;
  std::cout << "2. Part 4 Demo" << std::endl;
}

void displayAssignmentMenu()
{
  std::cout << "1. Assignment 1 Demos" << std::endl;
  std::cout << "2. Assignment 2 Demos" << std::endl;
}

void a1DemoHandler()
{
  std::cout << "\n\nAssignment 1 - Demo" << std::endl;
  std::cout << "Main Menu" << std::endl;
  std::cout << "========================" << std::endl;
  char choice;
  bool running = true;

  while (running)
  {
    displayA1DemoMenu();
    std::cout << "Please enter your choice 1-5 (q to quit): ";
    std::cin >> choice;

    switch (choice)
    {
    case '1':
      mapDriver();
      break;
    case '2':
      mapLoaderDriver();
      break;
    case '3':
      playerDriver();
      break;
    case '4':
      ordersDriver();
      break;
    case '5':
      CardsDeckTest();
      break;
    case 'q':
    case 'Q':
      running = false;
      break;
    default:
      std::cout << "Invalid option." << std::endl;
      break;
    }
  }
}

void a2DemoHandler()
{
  std::cout << "\n\nAssignment 2 - Demo" << std::endl;
  std::cout << "Main Menu" << std::endl;
  std::cout << "========================" << std::endl;
  char choice;
  bool running = true;

  while (running)
  {
    displayA2DemoMenu();
    std::cout << "Please enter your choice 1-2 (q to quit): ";
    std::cin >> choice;

    switch (choice)
    {
    case '1':
      doA2MainGame();
      break;
    case '2':
      ordersDriver();
      break;
    case 'q':
    case 'Q':
      running = false;
      break;
    default:
      std::cout << "Invalid option." << std::endl;
      break;
    }
  }
}

void doA2MainGame()
{
  GameEngine *MainEngine = new GameEngine();
  if (MainEngine->ObserverOn == false)
  {
    //person doing part 5 turn on observer or no in this part :)
  }
  delete MainEngine;
}