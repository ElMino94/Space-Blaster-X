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


void playlevel(RenderWindow& window, Player& player, float deltaTime, Clock& mobSpawnClock, Clock& levelClock, Texture& texture){

    float spawnTime = mobSpawnClock.getElapsedTime().asSeconds();
    float totalLevelTime = levelClock.getElapsedTime().asSeconds();

   
    if (totalLevelTime <= 41.0f && spawnTime >= 2.0f) {
        mobs.push_back(Mob(400, 400, 100, texture)); // Ajoutez votre logique de création de mob
        mobSpawnClock.restart();
    }


    for (auto& mob : mobs)
    {
        mob.update(deltaTime, player.getPosition(), mobs, window, player);
        window.draw(mob.shipSprite);
    }
    player.update(deltaTime, window, mobs);
    window.draw(player.pSprite);
    switch (level)
    {
    case(1):
        if (player.getscore() >= 2000) {
            level = 2;
            break;
        }
    case(2):
        if (player.getscore() >= 4500) {
            level = 3;
            break;
        }
    case(3):
        if (player.getscore() >= 5000) {
            level = 4;
            break;
        }
    default:
        break;
    }
}

void selmenu(RenderWindow& window, Player& player, MENU& menu, GameState& currentState, Event& event, float deltaTime, Clock& mobSpawnClock, Clock& levelClock, Texture& texture) {
    static bool escapePressed = false;
    Vector2f mousePos;

    if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {
            mousePos = Vector2f(event.mouseButton.x, event.mouseButton.y);

            if (currentState == MODMENU) {
                if (menu.playSprite.getGlobalBounds().contains(mousePos)) {
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
                if (menu.playSprite.getGlobalBounds().contains(mousePos)) {
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
