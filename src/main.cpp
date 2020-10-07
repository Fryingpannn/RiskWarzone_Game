/////////////////////////////////////////////
// Filename:        main.cpp
//
// Description:     Driver file controler to demonstrate the functionality of the MapLoader
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

#include <iostream>
#include <string>
// #include "MapDriver.hpp"
#include "MapLoaderDriver.hpp"

void displayMenu();

int main()
{
    std::cout << "Assignment 1 - Demo" << std::endl;
    std::cout << "Main Menu" << std::endl;
    std::cout << "========================" << std::endl;
    
    std::string choice;

    while(true)
    {
        displayMenu();
        std::cout << "Please enter your choice (q to quit): ";
        std::cin >> choice;

        if (choice == "1") {
            mapLoaderDriver();
        // } else if (choice == "2") {
        //     mapDriver();
        } else if (choice == "q" || choice == "Q"){
            break;
        }
    }
    

    return 0;
}

void displayMenu() 
{
    std::cout << "1. MapLoader driver" << std::endl;
    std::cout << "2. Map driver" << std::endl;

}