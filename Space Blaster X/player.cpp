#include "player.h"

Player::Player(float x, float y){
    position = sf::Vector2f(x, y);
    velocity = sf::Vector2f(0.f, 0.f);
    acceleration = 3750.f; // Vitesse de l'accélération
    friction = 0.99925f; // Friction pour ralentir la vitesse
    invincible = false;
    pv = 100;
    ship.setRadius(20.f);
    ship.setFillColor(sf::Color::Green);
    ship.setPosition(position);

}

bool Player::isalive(){}
void Player::move(int dx, int dy) {}
bool Player::takedmg(int degat) {}

void Player::attack() {}
void Player::update(float deltaTime) {
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

