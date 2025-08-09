#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
public:
    sf::Texture enemyTex;
    sf::Sprite enemy;
    float speed = 100.f;
    int direction = 1;
    float leftLimit;
    float RightLimit;
    float spawnX;

    std::vector<sf::Texture> tex;
    std::vector<sf::Texture> walkTextures;
    float animationTimer = 0.f;
    int currentFrame = 0;
    const float frameDuration = 0.1f;
public:
    Enemy(int enemyNo,sf::Vector2f pos,float leftBlocks,float rightBlocks);
    void update(float dt);
};


#endif