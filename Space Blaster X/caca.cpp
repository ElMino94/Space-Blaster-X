#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "menu.h"

using namespace std;
using namespace sf;

void cursor() {
    
}

enum GameState{ MODMENU, PLAY, SETTINGS, EXIT };

int main()
{
    
    RenderWindow window(VideoMode(1920, 1080), "Space Blaster X", Style::None);
    window.setFramerateLimit(200);

    MENU menu; 
    menu.initialisation();

    Player player(400.f, 300.f);
    Clock clock;

    

    Texture pTexture;
    pTexture.loadFromFile("assetocorsa\\player.png");
    player.pSprite.setTexture(pTexture);

    
    
    // Gestion des états du jeu
    GameState currentState = MODMENU;

    while (window.isOpen()) {
        Time deltaTime = clock.restart();
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    window.close();

                // Gestion des interactions selon l'état actuel
                switch (currentState) {
                case MODMENU:
                    if (event.key.code == Keyboard::Enter) {
                        currentState = PLAY; // Passer au jeu
                    }
                    if (event.key.code == Keyboard::S) {
                        currentState = SETTINGS; // Aller aux paramètres
                    }
                    if (event.key.code == Keyboard::E) {
                        currentState = EXIT; // Quitter le jeu
                    }
                    break;

                case PLAY:
                    if (event.key.code == Keyboard::P) {
                        currentState = MODMENU; // Retour au menu principal
                    }
                    break;

                case SETTINGS:
                    if (event.key.code == Keyboard::BackSpace) {
                        currentState = MODMENU; // Retour au menu principal
                    }
                    break;

                case EXIT:
                    window.close();
                    break;

                default:
                    break;
                }
            }
        }

        window.clear();

        switch (currentState) {
        
        case MODMENU:
            menu.drawMainMenu(window);
            break;

        case PLAY:
            player.update(deltaTime.asSeconds());
            window.draw(player.pSprite);
            break;

        case SETTINGS:
            menu.drawSettings(window);
            break;

        case EXIT:
            window.close();
            break;
        }
            
        window.display();
    }

        return 0;
}

//Comment faire le changement de menu??
//
//Idee de teva: 1........Si play --> open menu diff --> lancement du jeu en fonction de la difficulte choisi!!
//              2........Faire un fichier pour chaque etape pour les ramener dans le caca.cpp 






/*if (Mouse::isButtonPressed(Mouse::Left))
        {
            Vector2i mousePos = Mouse::getPosition(window);

            if (bpSprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {

            }*/




//Ce que teva a appris:
//""Sprite.setScale(1.3f, 1.3f); augmente la taille du sprite
//text.setStyle(sf::Text::Underlined); // Applique un soulignement