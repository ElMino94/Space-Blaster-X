#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
using namespace std;
using namespace sf;

void initialisation() {


}
void cursor() {
    
}
int main() {
    Player player(400.f, 300.f);
    Clock clock;
    Texture ifmTexture;
    Texture ftmTexture;

    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    ftmTexture.loadFromFile("assetocorsa\\button_square_header_small_rectangle_screws.png");
    

    RenderWindow window(VideoMode(1920, 1080), "Space Blaster X");//, Style::None
    window.setFramerateLimit(9999999999999999999);

    Sprite ifmSprite(ifmTexture);
    ifmSprite.setPosition(0, 0);

    Sprite ftmSprite(ftmTexture);
    ftmSprite.setPosition(790, 150);
    ftmSprite.setScale(1.3f, 1, 3f);

    Font font;
    if (!font.loadFromFile("assetocorsa\\Neon Energy x.ttf")) {
        cerr << "Erreur : Impossible de charger la police !" << endl;
        return -1;
    }

    //
    //

    Text text;

    text.setFont(font);               
    text.setString("Space Blaster ");
    text.setCharacterSize(50);        
    text.setFillColor(Color::White); 
    text.setStyle(Text::Bold);    
    text.setPosition(800, 153);   

    Text text2;
    text2.setFont(font);
    text2.setString("X");
    text2.setCharacterSize(75);
    text2.setFillColor(Color::White);
    text2.setStyle(Text::Bold);
    text2.setPosition(960, 200);

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

        
        window.draw(ifmSprite);
        window.draw(ftmSprite);
        window.draw(text);
        window.draw(text2);
        window.draw(player.ship);
        window.display();
        window.clear();
    }

    return 0;
}