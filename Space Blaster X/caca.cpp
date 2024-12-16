#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
using namespace std;
using namespace sf;

//""Sprite.setScale(1.3f, 1.3f); augmente la taille du sprite
//text.setStyle(sf::Text::Underlined); // Applique un soulignement


void cursor() {
    
}

int main()
{
    Player player(400.f, 300.f);
    Clock clock;
    Texture ifmTexture;
    Texture bpTexture;
    Texture setTexture;
    Texture exTexture;

    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    bpTexture.loadFromFile("assetocorsa\\bp.png");
    setTexture.loadFromFile("assetocorsa\\set.png");
    exTexture.loadFromFile("assetocorsa\\ex.png");

    RenderWindow window(VideoMode(1920, 1080), "Space Blaster X", Style::None);
    window.setFramerateLimit(9999999999999999999);

    Sprite ifmSprite(ifmTexture);
    ifmSprite.setPosition(0, 0);
    Sprite bpSprite(bpTexture);
    bpSprite.setPosition(50, 200);
    Sprite setSprite(setTexture);
    setSprite.setPosition(50, 350);
    Sprite exSprite(exTexture);
    exSprite.setPosition(50, 500);

    Font font;
    if (!font.loadFromFile("assetocorsa\\Neon Energy x.ttf")) {
        cerr << "Erreur : Impossible de charger la police !" << endl;
        return -1;
    }

    Text text;

    text.setFont(font);
    text.setString("Space Blaster X");
    text.setCharacterSize(75);
    text.setFillColor(Color(16, 39, 117));
    text.setStyle((Text::Bold | Text::Underlined));
    text.setPosition(50, 50);

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


            window.draw(ifmSprite);
            window.draw(text);
            //window.draw(player.ship);
            window.draw(bpSprite);
            window.draw(setSprite);
            window.draw(exSprite);
            window.display();
            window.clear();
        }

        return 0;
}



//Comment faire le changement de menu??
//
//Idee de teva: 1........Si play --> open menu diff --> lancement du jeu en fonction de la difficulte choisi!!
//              2........Faire un fichier pour chaque etape pour les ramener dans le caca.cpp 