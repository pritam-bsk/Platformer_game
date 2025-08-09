#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "enemy.h"



class GameWorld{
public:

    std::vector<sf::Sprite> solidTiles;
    std::vector<sf::Sprite> decorTiles;
    std::vector<sf::Sprite> sky;
    sf::Texture bgTexture;

    int totalTileColumns;
    sf::Vector2f playerPosition;

    std::vector<Enemy> enemies;
    std::vector<sf::Vector2f> enemyPositions;

    //bool -> isSolid
    std::unordered_map<char,std::pair<sf::Texture,bool>> tiles;

    std::vector<sf::Sprite> coins;
    sf::Texture coinTexture;

    sf::Sprite goal;
    sf::Texture goalTexture;
    bool levelComplete = false;

    sf::Font uiFont;
    sf::Text levelCompleteText;

    bool isGameOver = false;
    sf::Text gameOverText;

public:
    GameWorld();
    void loadTextures();
    void setSprites();
};

#endif