#include <SFML/Graphics.hpp>

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
    // Cr�ation de la fen�tre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fen�tre SFML");

    // Cr�ation d'un cercle
    sf::CircleShape shape(50); // Rayon de 50 pixels
    shape.setFillColor(sf::Color::Green);

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Fermer la fen�tre
        }

        // Effacer la fen�tre
        window.clear();
        // Dessiner la forme
        window.draw(shape);
        // Afficher le contenu
        window.display();
    }

    return 0;
}