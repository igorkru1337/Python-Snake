#ifndef H_MENU
#define H_MENU
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <string.h>
#include <time.h>
using namespace sf;
void menu(RenderWindow& window);
void dev(RenderWindow& window, Texture& BackgrounddevTexture, Texture& ButtonExitTexture);
extern int game(RenderWindow& window);
void filesave();
void filesee();
std::string intToStr(int);
void rec(RenderWindow& window, Texture& BackgroundTexture, Texture& ButtonExitTexture);
#endif
