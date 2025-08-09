#include "player.h"

Player::Player(const sf::Vector2f& spawnPos){
    setUpTexture(spawnPos);
}

void Player::setUpTexture(const sf::Vector2f& spawnPos){
    playerTexture.loadFromFile("PNG/Player/p1_stand.png");
    player.setTexture(playerTexture);
    player.setPosition(spawnPos);

    tex.resize(11);
    tex[0].loadFromFile("PNG/Player/walk/p1_walk01.png");
    tex[1].loadFromFile("PNG/Player/walk/p1_walk02.png");
    tex[2].loadFromFile("PNG/Player/walk/p1_walk03.png");
    tex[3].loadFromFile("PNG/Player/walk/p1_walk04.png");
    tex[4].loadFromFile("PNG/Player/walk/p1_walk05.png");
    tex[5].loadFromFile("PNG/Player/walk/p1_walk06.png");
    tex[6].loadFromFile("PNG/Player/walk/p1_walk07.png");
    tex[7].loadFromFile("PNG/Player/walk/p1_walk08.png");
    tex[8].loadFromFile("PNG/Player/walk/p1_walk09.png");
    tex[9].loadFromFile("PNG/Player/walk/p1_walk10.png");
    tex[10].loadFromFile("PNG/Player/walk/p1_walk11.png");
    for (auto &texi : tex) walkTextures.push_back(texi);

    jumpTexture.loadFromFile("PNG/Player/p1_jump.png");
    fallTexture.loadFromFile("PNG/Player/p1_jump.png");

    uiFont.loadFromFile("Text/OpenSans-Bold.ttf");
    scoreText.setFont(uiFont);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(2);

    bool th = healthTex1.loadFromFile("PNG/Items/hud_heartFull.png");
    healthTex2.loadFromFile("PNG/Items/hud_heartFull.png");
    healthTex3.loadFromFile("PNG/Items/hud_heartFull.png");

    healthSprite1.setTexture(healthTex1);
    healthSprite2.setTexture(healthTex2);
    healthSprite3.setTexture(healthTex3);

}

void Player::update(float dt) {
    if(!isOnGround){
        player.setTexture(jumpTexture);
    }else{
        bool isWalking = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        if (isWalking) {
            animationTimer += dt;
            if (animationTimer >= frameDuration) {
                currentFrame = (currentFrame + 1) % walkTextures.size();
                player.setTexture(walkTextures[currentFrame]);
                animationTimer = 0.f;
            }
        } else {
            player.setTexture(playerTexture);
        }
    }
}

void Player::respawn(sf::Vector2f respawnPos){
    player.setPosition(respawnPos);
    velocity = sf::Vector2f(0.f,0.f);
}