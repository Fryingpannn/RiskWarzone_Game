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
#include "MapDriver.hpp"
#include "MapLoaderDriver.hpp"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void displayMenu();

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::cout << "Assignment 1 - Demo" << std::endl;
    std::cout << "Main Menu" << std::endl;
    std::cout << "========================" << std::endl;
    
    char choice;

    bool running = true;
    while(running)
    {
        displayMenu();
        std::cout << "Please enter your choice (q to quit): ";
        std::cin >> choice;

        switch (choice) 
        { 
            case '1':
                mapLoaderDriver();
                break;
            case '2':
                mapDriver();
                break;
            case'3':
                break;
            case '4':
                break;
            case '5':
                break;
            case'q':
            case 'Q':
                running = false;
                break;
            default:
                std::cout << "Please no messing around Zzz" << std::endl;
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


//#include <SFML/Graphics.hpp>
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}