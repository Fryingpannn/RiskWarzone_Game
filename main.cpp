#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <string>
#include <iostream>



int main()
{
    std::cout << "ouch" << std:: endl;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML window");
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("Image/cute_image.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    //setting position
    sprite.setPosition(123.0f, 2.0f);
    sprite.setScale(0.5f, 0.5f);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("Image/arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);
    text.setFillColor(sf::Color::Blue);
    // Load a music to play
    /*sf::Music music;
    if (!music.openFromFile("nice_music.ogg"))
        return EXIT_FAILURE;*/
     //   Play the music
        /*music.play();*/
    //     Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);
        // Draw the string
        window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}