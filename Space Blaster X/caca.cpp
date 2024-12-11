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
    // Création de la fenêtre
    RenderWindow window(VideoMode(1920, 1080), "Fenêtre SFML");

    // Création d'un cercle
    CircleShape shape(500); // Rayon de 50 pixels
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