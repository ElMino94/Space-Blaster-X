#include"menu.h"

using namespace sf;
using namespace std;

void MENU::initialisation()  
{
    ifmTexture.loadFromFile("assetocorsa\\image-fond-menu.jpg");
    bpTexture.loadFromFile("assetocorsa\\bp.png");
    setTexture.loadFromFile("assetocorsa\\set.png");
    exTexture.loadFromFile("assetocorsa\\ex.png");

    ifmSprite.setTexture(ifmTexture);
    ifmSprite.setPosition(0, 0);
    bpSprite.setTexture(bpTexture);
    bpSprite.setPosition(50, 200);
    setSprite.setTexture(setTexture);
    setSprite.setPosition(50, 350);
    exSprite.setTexture(exTexture);
    exSprite.setPosition(50, 500);

    Font font;
    if (!font.loadFromFile("assetocorsa\\Neon Energy x.ttf")) {
        cerr << "Erreur : Impossible de charger la police !" << endl;
        return;
    }

    

    text.setFont(font);
    text.setString("Space Blaster X");
    text.setCharacterSize(75);
    text.setFillColor(Color(16, 39, 117));
    text.setStyle((Text::Bold | Text::Underlined));
    text.setPosition(50, 50);

}

void MENU::menu(RenderWindow& window)
{
	


    window.draw(ifmSprite);
    window.draw(bpSprite);
    window.draw(setSprite);
    window.draw(exSprite);


}

void MENU::ep(RenderWindow& window) 
{
    window.draw(ifmSprite);

    
}

void MENU::set(RenderWindow& window)
{

}
