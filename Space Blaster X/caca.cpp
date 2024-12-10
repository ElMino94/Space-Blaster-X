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
    Texture bmTexture;
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
    bmTexture.loadFromFile("assetocorsa\\bouton-de-jeu");
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








    // Création d'un cercle
    CircleShape shape(50); // Rayon de 50 pixels
    shape.setFillColor(sf::Color::Green);

    // Boucle principale
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close(); // Fermer la fenêtre
        }

        // Effacer la fenêtre
        window.clear();
        // Dessiner la forme
        window.draw(shape);
        // Afficher le contenu
        window.display();
    }

    return 0;
}