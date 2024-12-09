#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Player
{
private:

    float x;
    float y;
    int pv;
    bool invincible;

public:
    Player(float X, float Y, int Pv, bool Invincible) {
        x = X;
        y = Y;
        pv = Pv;
        invincible = Invincible;
    }

};

int main() {
    
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
    bpTexture.loadFromFile("assetocorsa\\bouton-play");
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

    RenderWindow window(VideoMode(1920, 1080), "Space Blaster X");
    window.setFramerateLimit(9999999999999999999);

    Sprite ifmSprite(ifmTexture);
    ifmSprite.setPosition(0, 0);

    Sprite bpSprite(bpTexture);
    bpSprite.setPosition(10, 10);





    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close(); // Fermer la fen�tre
        }

        window.draw(ifmSprite);
        window.draw(bpSprite);
        window.display();
    }

    return 0;
}