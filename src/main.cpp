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
#include "MapDriver.h"
#include "MapLoaderDriver.hpp"
#include "PlayerDriver.h"
#include "CardsDriver.h"
#include "OrdersDriver.h"

#include <stdlib.h>

void displayMenu();

int main()
{
    std::cout << "Assignment 1 - Demo" << std::endl;
    std::cout << "Main Menu" << std::endl;
    std::cout << "========================" << std::endl;
    
    char choice;

    bool running = true;
    while(running)
    {
        displayMenu();
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
    

    return 0;
}

void displayMenu() 
{
    std::cout << "1. Map driver" << std::endl;
    std::cout << "2. MapLoader driver" << std::endl;
    std::cout << "3. Player driver" << std::endl;
    std::cout << "4. Orders driver" << std::endl;
    std::cout << "5. Cards Driver" << std::endl;
}
