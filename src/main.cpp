/////////////////////////////////////////////
// Filename:        main.cpp
//
// Description:     Driver file controller to demonstrate the functionality of
// the MapLoader
//
// Author:          Stefan Russo - 26683320
//
// Group:           Sandra Buchen
//                  Le Cherng Lee
//                  Zahra Nikbakht
//                  Matthew Pan
//                  Stefan Russo
//
/////////////////////////////////////////////
#define _DEBUG
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "PlayerDriver.h"
#include <iostream>
#include <string>

void displayMenu();

int main() {
#ifdef _DEBUG
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  std::cout << "Assignment 1 - Demo" << std::endl;
  std::cout << "Main Menu" << std::endl;
  std::cout << "========================" << std::endl;

  std::string *choice = new std::string("a");

  // while (true) {
  //  displayMenu();
  //  std::cout << "Please enter your choice (q to quit): ";
  //  std::cin >> choice;
  //  playerDriver();
  //  if (choice == "1") {
  //    // mapLoaderDriver();
  //  } else if (choice == "2") {
  //    // mapDriver();
  //  } else if (choice == "3") {
  //    playerDriver();
  //  } else if (choice == "q" || choice == "Q") {
  //    break;
  //  }
  //}
  playerDriver();
  return 0;
}

void displayMenu() {
  std::cout << "1. MapLoader driver" << std::endl;
  std::cout << "2. Map driver" << std::endl;
  std::cout << "3. Player driver" << std::endl;
}