#include"menu.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

// Appel automatique pour charger textures/polices
MENU::MENU() {
    initialisation();
    lvl1Texture.loadFromFile("assetocorsa\\lvl1.jpg");
    lvl1Sprite.setTexture(lvl1Texture);
}

// M thode pour initialiser les textures, polices et sprites
void MENU::initialisation() {


    backgroundTexture.loadFromFile("assetocorsa\\background.jpg");
    if (!backgroundTexture.loadFromFile("assetocorsa\\background.jpg"))
        cerr << "Erreur : Impossible de charger l'image de fond !" << endl;


    if (!playTexture.loadFromFile("assetocorsa\\bp.png"))
        cerr << "Erreur : Impossible de charger play.png !" << endl;

    settingsTexture.loadFromFile("assetocorsa\\set.png");
    if (!settingsTexture.loadFromFile("assetocorsa\\set.png"))
        cerr << "Erreur : Impossible de charger set.png !" << endl;

    exitTexture.loadFromFile("assetocorsa\\ex.png");
    if (!exitTexture.loadFromFile("assetocorsa\\ex.png"))
        cerr << "Erreur : Impossible de charger ex.png !" << endl;

    // Configuration des sprites
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);

    playSprite.setTexture(playTexture);
    playSprite.setPosition(50, 200);

    settingsSprite.setTexture(settingsTexture);
    settingsSprite.setPosition(50, 350);

    exitSprite.setTexture(exitTexture);
    exitSprite.setPosition(50, 500);


    if (!font.loadFromFile("assetocorsa\\Neon Energy x.ttf")) {
        cerr << "Erreur : Impossible de charger la police !" << endl;
        return;
    }

    titleText.setFont(font);
    titleText.setString("Space Blaster X");
    titleText.setCharacterSize(75);
    titleText.setFillColor(Color(16, 39, 117));
    titleText.setStyle(Text::Bold | Text::Underlined);
    titleText.setPosition(50, 50);
}

// Affiche le menu principal
void MENU::drawMainMenu(RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(playSprite);
    window.draw(settingsSprite);
    window.draw(exitSprite);
}

// Affiche le menu des param tres
void MENU::drawSettings(RenderWindow& window) {
    window.draw(backgroundSprite);

    Text settingsText;
    settingsText.setFont(font);
    settingsText.setString("Settings: Coming Soon...");
    settingsText.setCharacterSize(50);
    settingsText.setFillColor(Color::White);
    settingsText.setPosition(50, 300);

    window.draw(settingsText);
}

// Affiche un  cran de confirmation pour quitter
void MENU::drawExitConfirmation(RenderWindow& window) {
    window.draw(backgroundSprite);

    Text exitText;
    exitText.setFont(font);
    exitText.setString("Are you sure you want to exit? (Y/N)");
    exitText.setCharacterSize(50);
    exitText.setFillColor(Color::White);
    exitText.setPosition(50, 300);

    window.draw(exitText);
}

void MENU::drawplay(RenderWindow& window, int level) {



    if (level == 1) {
        window.draw(lvl1Sprite);
    }
    else if (level == 2) {
        lvl2Texture.loadFromFile("assetocorsa\\lvl2.jpg");
        lvl2Sprite.setTexture(lvl2Texture);
        window.draw(lvl1Sprite);
    }
    else if (level == 3) {
        lvl3Texture.loadFromFile("assetocorsa\\lvl3.png");
        lvl3Sprite.setTexture(lvl3Texture);
        window.draw(lvl1Sprite);
    }

}