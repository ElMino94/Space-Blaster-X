#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "menu.h"
using namespace std;
using namespace sf;

//""Sprite.setScale(1.3f, 1.3f); augmente la taille du sprite
//text.setStyle(sf::Text::Underlined); // Applique un soulignement


void cursor() {
    
}

int main()
{
    initialisation();
    RenderWindow window(VideoMode(1920, 1080), "Space Blaster X", Style::None);
    window.setFramerateLimit(9999999999999999999);
    Player player(400.f, 300.f);
    Clock clock;

    while (window.isOpen()) 
    {
        Time deltaTime = clock.restart();
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.key.code == Keyboard::Escape)
                window.close();
        }

        /*if (Mouse::isButtonPressed(Mouse::Left)) 
        {
            Vector2i mousePos = Mouse::getPosition(window);

            if (bpSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
            {

            }*/


            player.update(deltaTime.asSeconds());

            window.draw(player.ship);
            window.display();
            window.clear();
        }

        return 0;
}



//Comment faire le changement de menu??
//
//Idee de teva: 1........Si play --> open menu diff --> lancement du jeu en fonction de la difficulte choisi!!
//              2........Faire un fichier pour chaque etape pour les ramener dans le caca.cpp 