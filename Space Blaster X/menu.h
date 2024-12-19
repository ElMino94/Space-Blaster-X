#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;


class MENU {
public:

    MENU(); // Constructeur

    // Methodes pour initialiser et dessiner diff rents  crans du menu
    void initialisation();       // Charger les textures, polices et positions
    void drawMainMenu(RenderWindow& window); // Affiche le menu principal
    void drawSettings(RenderWindow& window); // Affiche le menu des param tres
    void drawExitConfirmation(RenderWindow& window); // Affiche un menu de confirmation de sortie
    void drawplay(RenderWindow& window, int level); // Afficher lorque que le jeu ce lance
    void drawPauseMenu(RenderWindow& window); // Afficher le menu pause pendant la partie


    Texture backgroundTexture;
    Sprite backgroundSprite;

    Texture playTexture;
    Sprite playSprite;

    Texture settingsTexture;
    Sprite settingsSprite;

    Texture exitTexture;
    Sprite exitSprite;

    Texture returnTexture;   
    Sprite returnSprite;     

    Texture lvl1Texture;
    Sprite lvl1Sprite;

    Texture lvl2Texture;
    Sprite lvl2Sprite;

    Texture lvl3Texture;
    Sprite lvl3Sprite;

    Font font;
    Text titleText;
};

#endif