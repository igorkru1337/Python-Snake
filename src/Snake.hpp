#ifndef H_SNAKE
#define H_SNAKE
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include "Menu.hpp"

using namespace sf;
int N = 30, M = 20;
int scale = 25;

int w = scale * N;
int h = scale * M;

int dir, num = 4;
int game(RenderWindow& window);
void Display(sf::RenderWindow& win);
void Key(int& dir);
int tick();
void Snake(sf::RenderWindow& win);
void Draw(sf::RenderWindow& win);

#endif
