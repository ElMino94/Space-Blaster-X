#include "Mob.h"
#include <cmath>

// Constructeur qui initialise les variables du Mob
Mob::Mob(float x, float y, int hp) : position(x, y), pv(hp), velocity(0, 0), acceleration(3500.f), friction(0.975f) {
    // Initialisation du cercle représentant le vaisseau
    ship.setRadius(20.f);  // Rayon du vaisseau
    ship.setFillColor(sf::Color::Red);  // Couleur du vaisseau
    ship.setPosition(position);  // Position initiale du vaisseau
}

// Vérifie si le Mob est encore en vie
bool Mob::isalive() {
    return pv > 0;
}

// Déplace le Mob en fonction des coordonnées x et y
void Mob::move(int dx, int dy) {
    // Applique la vitesse (velocity) à la position
    position.x += dx * velocity.x;
    position.y += dy * velocity.y;
    ship.setPosition(position);  // Met à jour la position du sprite
}

// Applique des dégâts au Mob et retourne si le Mob est toujours en vie
bool Mob::takedmg(int degat) {
    pv -= degat;
    if (pv <= 0) {
        pv = 0;
        return false;  // Le Mob est mort
    }
    return true;  // Le Mob reste en vie
}

// Fonction d'attaque (pas utilisée ici)
void Mob::attack() {
    // La fonction est vide pour l'instant
}

// Mise à jour du Mob à chaque frame
void Mob::update(float deltaTime, sf::Vector2f playerPosition, std::vector<Mob>& mobs, sf::RenderWindow& window) {
    // Calcul de la distance entre le Mob et le joueur
    float distance = std::sqrt(std::pow(playerPosition.x - position.x, 2) + std::pow(playerPosition.y - position.y, 2));

    // Direction vers le joueur
    sf::Vector2f direction = playerPosition - position;

    // Normaliser la direction (rendre le vecteur unitaire)
    if (distance != 0) {
        direction /= distance;
    }

    // Si la distance est inférieure à 400 pixels, on recule (inverse la direction)
    if (distance < 400.f) {
        direction = -direction;
    }

    // Applique l'accélération dans la direction calculée
    velocity += direction * acceleration * deltaTime;

    // Appliquer la friction : on multiplie la vitesse par un facteur inférieur à 1 pour ralentir
    velocity *= friction;

    // Limiter la vitesse du mob pour qu'il ne devienne pas trop rapide
    float maxSpeed = 3000;  // Limite la vitesse maximale
    if (velocity.x > maxSpeed) velocity.x = maxSpeed;
    if (velocity.y > maxSpeed) velocity.y = maxSpeed;

    // Mise à jour de la position du Mob en fonction de la vitesse (velocity)
    position += velocity * deltaTime;

    // Vérification de la collision avec les bords de l'écran
    sf::Vector2u windowSize = window.getSize();
    float spriteHalfWidth = ship.getGlobalBounds().width / 2.f;
    float spriteHalfHeight = ship.getGlobalBounds().height / 2.f;

    if (position.x - spriteHalfWidth < 0.f) {
        position.x = spriteHalfWidth;
    }
    else if (position.x + spriteHalfWidth > windowSize.x) {
        position.x = windowSize.x - spriteHalfWidth;
    }

    if (position.y - spriteHalfHeight < 0.f) {
        position.y = spriteHalfHeight;
    }
    else if (position.y + spriteHalfHeight > windowSize.y) {
        position.y = windowSize.y - spriteHalfHeight;
    }

    // Vérification de la collision avec les autres Mobs
    for (Mob& other : mobs) {
        if (&other != this) {  // S'assurer qu'on ne vérifie pas la collision avec soi-même
            float dx = position.x - other.position.x;
            float dy = position.y - other.position.y;
            float distanceBetweenMobs = std::sqrt(dx * dx + dy * dy);
            float minDistance = ship.getRadius() * 2;  // Distance minimale (la taille des 2 Mobs)

            if (distanceBetweenMobs < minDistance) {
                // Calculer la direction de répulsion
                sf::Vector2f repulsionDirection = sf::Vector2f(dx, dy) / distanceBetweenMobs;
                float overlap = minDistance - distanceBetweenMobs;  // Calculer le chevauchement

                // Déplacer le Mob à l'extérieur du chevauchement
                position += repulsionDirection * overlap;
            }
        }
    }

    // Met à jour la position du sprite du Mob
    ship.setPosition(position);
}
