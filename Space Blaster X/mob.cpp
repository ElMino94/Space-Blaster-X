#include "Mob.h"
#include <cmath>

// Constructeur qui initialise les variables du Mob
Mob::Mob(float x, float y, int hp, Texture texture)
    : position(x, y), pv(hp), velocity(0, 0), acceleration(500.f), friction(0.975f), texture(texture) {
    attackCooldown = 1;
    attackTimer = 0;

    if (!texture.loadFromFile("assetocorsa//ship.png")) {
        std::cerr << "Erreur : impossible de charger 'assetocorsaship.png'" << std::endl;
    }
    shipSprite.setTexture(texture);
    shipSprite.setScale(Vector2f(0.35, 0.35));
    shipSprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
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
    shipSprite.setPosition(position);  // Met à jour la position du sprite
}

// Applique des dégâts au Mob et retourne si le Mob est toujours en vie
void Mob::takeDamage(int damage) {
    pv -= damage;
}

// Fonction d'attaque (pas utilisée ici)
void Mob::attack(sf::Vector2f playerPosition) {
    
    if (attackTimer >= attackCooldown) {
        // Calculer la direction du tir vers le joueur
        sf::Vector2f direction = playerPosition - position;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance != 0) {
            direction /= distance; // Normaliser la direction
        }

        // Angle du tir en degrés
        float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;

        // Ajouter un projectile
        projectiles.push_back(Projectile(position.x, position.y, angle, 800, sf::Color::Yellow));

        // Réinitialiser le timer d'attaque
        attackTimer = 0.f;
    }
}

void Mob::update(float deltaTime, sf::Vector2f playerPosition, std::vector<Mob>& mobs, sf::RenderWindow& window, Player& player) {
    // Calcul de la distance entre le Mob et le joueur
    float distance = std::sqrt(std::pow(playerPosition.x - position.x, 2) + std::pow(playerPosition.y - position.y, 2));
    sf::Vector2f direction = playerPosition - position;
    // Direction vers le joueur
    if (distance < 500) direction = -direction;
      
    // Normaliser la direction (rendre le vecteur unitaire)
    if (distance != 0) {
        direction /= distance;
    }

    // Calcul de l'angle pour que le Mob regarde le joueur
    float angleToPlayer = std::atan2(direction.y, direction.x) * 180.f / 3.14159f; // Convertir en degrés
    shipSprite.setRotation(angleToPlayer + 90.f); // +90° pour aligner avec l'axe vertical du sprite

    // Applique l'accélération dans la direction calculée (si nécessaire pour mouvement)
    velocity += direction * acceleration * deltaTime;

    // Appliquer la friction : on multiplie la vitesse par un facteur inférieur à 1 pour ralentir
    velocity *= friction;

    // Mise à jour de la position en fonction de la vitesse
    position += velocity * deltaTime;

    // Vérification des collisions avec les bords de l'écran
    sf::Vector2u windowSize = window.getSize();
    float spriteHalfWidth = shipSprite.getGlobalBounds().width / 2.f;
    float spriteHalfHeight = shipSprite.getGlobalBounds().height / 2.f;

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

    // Gérer les collisions entre Mobs
    for (Mob& other : mobs) {
        if (&other != this) {
            float dx = position.x - other.position.x;
            float dy = position.y - other.position.y;
            float distanceBetweenMobs = std::sqrt(dx * dx + dy * dy);
            float spriteHalfWidth = shipSprite.getGlobalBounds().width / 2.f;
            float spriteHalfHeight = shipSprite.getGlobalBounds().height / 2.f;
            float minDistance = spriteHalfWidth + spriteHalfHeight;

            if (distanceBetweenMobs < minDistance) {
                sf::Vector2f repulsionDirection = sf::Vector2f(dx, dy) / distanceBetweenMobs;
                float overlap = minDistance - distanceBetweenMobs;
                position += repulsionDirection * overlap;
            }
        }
    }

    // Gérer les projectiles
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        it->update(deltaTime);
        it->render(window);

        if (it->checkCollisionP(player.getBounds())) {
            player.takedmg(34);
            it = projectiles.erase(it);
        }
        else if (it->isOutOfBounds(window)) {
            it = projectiles.erase(it);
        }
        else {
            ++it;
        }
    }

    attackTimer += deltaTime;
    attack(playerPosition);

    // Mise à jour de la position du sprite
    shipSprite.setPosition(position);
}



sf::FloatRect Mob::getBounds() const {
    return shipSprite.getGlobalBounds();
}
