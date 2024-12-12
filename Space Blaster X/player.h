#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player
{
private:

    int pv;
    bool invincible = false;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float acceleration;
    float friction;

public:
    Player(float x, float y, int Pv);
    ~Player() = default;

    bool isalive();
    void move(int dx, int dy);
    bool takedmg(int degat);

    void attack();

};


#endif
class Vaisseau {
public:
    Vaisseau(float x, float y) {
        position = sf::Vector2f(x, y);
        velocity = sf::Vector2f(0.f, 0.f);
        acceleration = 3750.f; // Vitesse de l'accélération
        friction = 0.99925f; // Friction pour ralentir la vitesse
        ship.setRadius(20.f);
        ship.setFillColor(sf::Color::Green);
        ship.setPosition(position);
    }

    void update(float deltaTime) {
        // Applique les entrées utilisateur pour la direction
        sf::Vector2f direction(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            direction.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            direction.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            direction.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            direction.x += 1.f;

        // Normaliser la direction si nécessaire pour éviter que la vitesse ne soit trop rapide en diagonale
        if (direction.x != 0.f || direction.y != 0.f) {
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length; // Normalisation
        }

        // Accélérer dans la direction donnée
        velocity += direction * acceleration * deltaTime;

        // Appliquer la friction pour ralentir le vaisseau
        velocity *= friction;

        // Mettre à jour la position en fonction de la vitesse
        position += velocity * deltaTime;

        ship.setPosition(position);
    }

    sf::CircleShape ship;
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float acceleration;
    float friction;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Vaisseau Glissant");
    Vaisseau vaisseau(400.f, 300.f);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        vaisseau.update(deltaTime.asSeconds());

        window.clear();
        window.draw(vaisseau.ship);
        window.display();
    }

    return 0;
}