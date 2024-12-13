#include <SFML/Graphics.hpp>
#include "player.h"
using namespace std;
using namespace sf;

int main() {
    Player player(400.f, 300.f);
    Clock clock;
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
    //bpTexture.loadFromFile("assetocorsa\\bouton-de-jeu.png");
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

    Font font;
    if (!font.loadFromFile("assetocorsa\\Neon Energy x.ttf")) {
        cerr << "Erreur : Impossible de charger la police !" << endl;
        return -1;
    }
    Text text;
    text.setFont(font);               
    text.setString("Space Blaster ");
    text.setCharacterSize(50);        
    text.setFillColor(Color::White); 
    text.setStyle(Text::Bold);    
    text.setPosition(1000, 0);   

    Text text2;
    text2.setFont(font);
    text2.setString("X");
    text2.setCharacterSize(50);
    text2.setFillColor(Color::White);
    text2.setStyle(Text::Bold);
    text2.setPosition(200, 540);

    Sprite bpSprite(bpTexture);
    bpSprite.setPosition(1000, 500);





    while (window.isOpen()) {
        Time deltaTime = clock.restart();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close(); 
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        player.update(deltaTime.asSeconds());

        window.clear();
        window.draw(ifmSprite);
        //window.draw(bpSprite);
        window.draw(text);
        window.draw(text2);
        window.draw(player.ship);
        window.display();
    }

    return 0;
}