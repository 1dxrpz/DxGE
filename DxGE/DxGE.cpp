// DxGE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MathUtils.h"

using namespace::dx;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "DxGE", sf::Style::Close);
    
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\HP\\AppData\\Local\\Microsoft\\Windows\\Fonts\\04B_03_.TTF"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        
        window.draw(text);

        window.display();
    }
    return EXIT_SUCCESS;
}