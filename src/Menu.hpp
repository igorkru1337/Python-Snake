#ifndef H_MENU
#define H_MENU
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>
#include <time.h>

using namespace sf;
void menu(RenderWindow& window);
void dev(RenderWindow& window, Texture& BackgrounddevTexture, Texture& ButtonExitTexture);
extern int game(RenderWindow& window);

#endif
