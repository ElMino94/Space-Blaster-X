#include <SFML/Graphics.hpp>
#include "player.h"
using namespace std;
using namespace sf;

int main() {
    Player player(400.f, 300.f);
    sf::Clock clock;
    Texture ifmTexture;
    Texture bpTexture;
    Texture vb1Texture;
    Texture vb2Texture;
    Texture vb3Texture;
    Texture ve1Texture;
    Texture ve2Texture;
    Texture ve3Texture;
    Texture vpTexture;
    Texture i1Texutre;
    Texture i2Texutre;
    Texture i3Texutre;

    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    bpTexture.loadFromFile("assetocorsa\\bouton-de-jeu.png");
    vb1Texture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    vb2Texture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    vb3Texture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");

    RenderWindow window(VideoMode(1920, 1080), "Space Blaster X", Style::None);
    window.setFramerateLimit(9999999999999999999);

    Sprite ifmSprite(ifmTexture);
    ifmSprite.setPosition(0, 0);

    Sprite bpSprite(bpTexture);
    bpSprite.setPosition(1000, 500);





    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close(); 
        }
        player.update(deltaTime.asSeconds());
        window.draw(ifmSprite);
        window.draw(bpSprite);
        window.draw(player.ship);
        window.display();
    }

    return 0;
}