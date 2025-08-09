#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "gameWorld.h"

class Player{
public:
    sf::Texture playerTexture;
    sf::Sprite player;

    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
    bool isOnGround = false;

    std::vector<sf::Texture> tex;
    std::vector<sf::Texture> walkTextures;
    float animationTimer = 0.f;
    int currentFrame = 0;
    const float frameDuration = 0.1f;

    sf::Texture jumpTexture;
    sf::Texture fallTexture;

    int score = 0;
    sf::Font uiFont;
    sf::Text scoreText;

    int healthInt = 3;
    sf::Texture healthTex1,healthTex2,healthTex3;
    sf::Sprite healthSprite1,healthSprite2,healthSprite3;

public:
    Player(const sf::Vector2f& spawnPos);
    void setUpTexture(const sf::Vector2f& spawnPos);
    void update(float dt);
    void respawn(sf::Vector2f respawnPos);
    void showScoreText();
};

#endif