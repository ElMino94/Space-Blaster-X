#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "player.h"
#include "mob.h"
#include "menu.h"

using namespace std;
using namespace sf;

void cursor() {

}

vector<Mob> mobs;
int level = 1;
//vector<Projectile> projectiles
enum GameState { MODMENU, PLAY, SETTINGS, EXIT, PAUSE };


void playlevel(RenderWindow& window, Player& player, float deltaTime, Clock& mobSpawnClock, Clock& levelClock, Texture& texture) {
    float spawnTime = mobSpawnClock.getElapsedTime().asSeconds();
    float totalLevelTime = levelClock.getElapsedTime().asSeconds();
    float spawnrate;
    float spawnlong;

    // Définir les paramètres selon le niveau
    switch (level) {
    case(1):
        spawnrate = 2;
        spawnlong = 41;
        if (player.getscore() >= 2000) {
            levelClock.restart();
            mobSpawnClock.restart();
            level = 2;
            break;
        }
        break; // Ajouté pour éviter de tomber dans le case suivant
    case(2):
        spawnrate = 1;
        spawnlong = 21;
        if (player.getscore() >= 4000) {
            levelClock.restart();
            mobSpawnClock.restart();
            level = 3;
            break;
        }
        break;
    case(3):
        spawnrate = 0.5;
        spawnlong = 11;
        if (player.getscore() >= 5000) {
            mobs.push_back(Mob(400, 400, 1000, 2, 0.25, texture));
            level = 4;
            break;
        }
        break;
    default:
        break;
    }

    // Générer un mob selon le temps
    if (totalLevelTime <= spawnlong && spawnTime >= spawnrate) {
        // Générer une position aléatoire sur un bord de l'écran
        int screenWidth = window.getSize().x;
        int screenHeight = window.getSize().y;
        float x, y;

        // Choisir un bord aléatoire
        int edge = std::rand() % 4; // 0 = haut, 1 = bas, 2 = gauche, 3 = droite
        switch (edge) {
        case 0: // Haut
            x = static_cast<float>(std::rand() % screenWidth);
            y = 0.f;
            break;
        case 1: // Bas
            x = static_cast<float>(std::rand() % screenWidth);
            y = static_cast<float>(screenHeight);
            break;
        case 2: // Gauche
            x = 0.f;
            y = static_cast<float>(std::rand() % screenHeight);
            break;
        case 3: // Droite
            x = static_cast<float>(screenWidth);
            y = static_cast<float>(std::rand() % screenHeight);
            break;
        }

        mobs.push_back(Mob(x, y, 100, 0.35, 1, texture));
        mobSpawnClock.restart();
    }

    // Mettre à jour et dessiner les mobs
    for (auto& mob : mobs) {
        mob.update(deltaTime, player.getPosition(), mobs, window, player);
        window.draw(mob.shipSprite);
    }

    // Mettre à jour et dessiner le joueur
    player.update(deltaTime, window, mobs);
    window.draw(player.pSprite);
}

void selmenu(RenderWindow& window, Player& player, MENU& menu, GameState& currentState, Event& event, float deltaTime, Clock& mobSpawnClock, Clock& levelClock, Texture& texture) {
    static bool escapePressed = false;
    Vector2f mousePos;

    if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {
            mousePos = Vector2f(event.mouseButton.x, event.mouseButton.y);

            if (currentState == MODMENU) {
                if (menu.playSprite.getGlobalBounds().contains(mousePos)) {
                    levelClock.restart();
                    currentState = PLAY;
                }
                else if (menu.settingsSprite.getGlobalBounds().contains(mousePos)) {
                    currentState = SETTINGS;
                }
                else if (menu.exitSprite.getGlobalBounds().contains(mousePos)) {
                    currentState = EXIT;
                }
            }

            else if (currentState == PAUSE) {
                if (menu.returnSprite.getGlobalBounds().contains(mousePos)) {
                    currentState = PLAY;
                }
                else if (menu.exitSprite.getGlobalBounds().contains(mousePos)) {
                    currentState = MODMENU;
                }
            }
        }
    }

    
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
        if (!escapePressed) {  
            escapePressed = true;  

            
            if (currentState == PLAY) {
                currentState = PAUSE;
            }
            
            else if (currentState == PAUSE) {
                currentState = PLAY;
            }
        }
    }

    
    if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
        escapePressed = false;  
    }

    switch (currentState) {
    case MODMENU:
        menu.drawMainMenu(window);
        break;

    case PLAY:
        if (!player.isalive())
        {
            currentState = MODMENU;
            player.pv = 100;
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            currentState = PAUSE;
        }
        else {
            menu.drawplay(window, level);
            playlevel(window, player, deltaTime, mobSpawnClock, levelClock, texture);
        }
        break;

    case PAUSE:
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            currentState = PLAY;
        }
        menu.drawPauseMenu(window);   
        break;

    case SETTINGS:
        menu.drawSettings(window);
        break;

    case EXIT:
        window.close();
        break;
    }
}


int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(1920, 1080), "Space Blaster X", Style::None);
    window.setFramerateLimit(120);
    
    MENU menu;
    menu.initialisation();
    Texture texture;
    if (!texture.loadFromFile("assetocorsa//ship.png")) {
        cerr << "Erreur : Impossible de charger la texture." << endl;
        return -1; 
    }    Player player(400.f, 300.f);
    
    Clock clock;
    Clock mobSpawnClock; 
    Clock levelClock;    

    GameState currentState = MODMENU;

    while (window.isOpen()) {
        Time deltaTime = clock.restart();
        Event event;

        

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::M))window.close();
        
        
        window.clear();
        selmenu(window, player, menu, currentState, event, deltaTime.asSeconds(), mobSpawnClock, levelClock, texture);
        window.display();
    }

}
