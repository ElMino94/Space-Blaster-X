#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;


class MENU {
public:
	Text text;
	Texture ifmTexture;
	Texture bpTexture;
	Texture setTexture;
	Texture exTexture;	
	Sprite ifmSprite;
	Sprite bpSprite;
	Sprite setSprite;
	Sprite exSprite;
	void initialisation();//generation sprites
	void menu(RenderWindow& window);//pause
	void ep(RenderWindow& window);//first ecran
	void set(RenderWindow& window);//settings
};

#endif