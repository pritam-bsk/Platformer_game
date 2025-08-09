#include "enemy.h"
#include "constants.h"

Enemy::Enemy(int enemyNo,sf::Vector2f pos,float leftBlocks,float rightBlocks){
    if(enemyNo == 1){
        enemyTex.loadFromFile("PNG/Enemies/slimeWalk1.png");
        enemy.setTexture(enemyTex);
        tex.resize(2);
        tex[0].loadFromFile("PNG/Enemies/slimeWalk1.png");
        tex[1].loadFromFile("PNG/Enemies/slimeWalk2.png");
    }else{
        enemyTex.loadFromFile("PNG/Enemies/flyFly1.png");
        enemy.setTexture(enemyTex);
        tex.resize(2);
        tex[0].loadFromFile("PNG/Enemies/flyFly1.png");
        tex[1].loadFromFile("PNG/Enemies/flyFly2.png");

        pos.y -= 20;
    }
    for(auto& texi:tex) walkTextures.push_back(texi);
    enemy.setTexture(enemyTex);
    pos.y += 40;
    enemy.setPosition(pos);
    
    leftLimit = TILE_SIZE*((pos.x/TILE_SIZE) - leftBlocks);
    RightLimit = TILE_SIZE*((pos.x/TILE_SIZE)+rightBlocks);
    spawnX = pos.x;

    
}

void Enemy::update(float dt){
    enemy.move(speed*dt*direction,0.f);
    animationTimer += dt;
    if (animationTimer >= frameDuration) {
        currentFrame = (currentFrame + 1) % walkTextures.size();
        enemy.setTexture(walkTextures[currentFrame]);
        animationTimer = 0.f;
    }
    float x = enemy.getPosition().x;
    if(x<leftLimit){
        direction = 1;
        enemy.setPosition(leftLimit,enemy.getPosition().y);
        
    }else if(x>RightLimit){
        direction = -1;
        enemy.setPosition(RightLimit,enemy.getPosition().y);
        
    }
    if(direction == 1){
        enemy.setScale(-1.f,1.f);
        enemy.setOrigin(enemy.getGlobalBounds().width,0);
    }else{
        enemy.setScale(1.f,1.f);
        enemy.setOrigin(0,0);
    }
}