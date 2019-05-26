#ifndef H_SNAKE
#define H_SNAKE
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include "Menu.hpp"

using namespace sf;
int N = 39, M = 39;
int scale = 25;

int w = scale * N;
int h = scale * M;

int dir, num = 4;
int game(RenderWindow& window);
void Display(sf::RenderWindow& win, Texture& GamegroundTexture, Texture& FructTexture, Texture& HeadLeftTexture);
void Key(int& dir);
void Snake(sf::RenderWindow& win, Texture& HeadLeftTexture);
void Draw(sf::RenderWindow& win, Texture& GamegroundTexture);

#endif
