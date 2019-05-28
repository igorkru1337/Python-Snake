#ifndef H_SNAKE
#define H_SNAKE
#include "Menu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>

using namespace sf;
extern int dir;
int game(RenderWindow& window);
void Display(sf::RenderWindow& win, Texture& GamegroundTexture, Texture& FructTexture, Texture& HeadLeftTexture);
void Key(int& dir);
void Snake(sf::RenderWindow& win, Texture& HeadLeftTexture);
void Draw(sf::RenderWindow& win, Texture& GamegroundTexture);
int RotateHead(int dir, Sprite& head);
int SnakeCrush(struct S* s);
#endif
