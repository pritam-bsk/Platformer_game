#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "constants.h"
#include "gameWorld.h"
#include "player.h"
#include "enemy.h"
#include "audio.h"

void checkVerticalCollision(sf::Sprite& player,bool& isOnGround,std::vector<sf::Sprite>& tiles,sf::Vector2f& velocity){
    sf::FloatRect playerBounds = player.getGlobalBounds();
    isOnGround = false;
    for(auto& tile:tiles){
        sf::FloatRect tileBound = tile.getGlobalBounds();
        if(playerBounds.intersects(tileBound)){
            if(velocity.y > 0){
                player.setPosition(player.getPosition().x,tileBound.top - playerBounds.height);
                velocity.y = 0;
                isOnGround = true;
            }else if(velocity.y < 0){
                player.setPosition(player.getPosition().x,tileBound.top + playerBounds.height);
                velocity.y = 0;
            }
        }
        playerBounds = player.getGlobalBounds();
    }
}
void checkHorizontalCollision(sf::Sprite& player,std::vector<sf::Sprite>& tiles,float& moveX){
    sf::FloatRect playerBounds = player.getGlobalBounds();
    for(auto& tile: tiles){
        sf::FloatRect tileBound = tile.getGlobalBounds();
        if(playerBounds.intersects(tileBound)){
            if(moveX>0){
                player.setPosition(tileBound.left - playerBounds.width,player.getPosition().y);
            }else if(moveX < 0){
                player.setPosition(tileBound.left + tileBound.width,player.getPosition().y);
            }
        }
    }
}

int main(){
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH,WIN_HEIGHT),"Platformer");

    Audio audio;

    GameWorld world;
    Player user(world.playerPosition);

    Enemy enemy1(1,world.enemyPositions[0],2.f,2.f);
    world.enemies.push_back(enemy1);

    Enemy enemy2(2,world.enemyPositions[1],1.f,2.f);
    world.enemies.push_back(enemy2);

    Enemy enemy3(1,world.enemyPositions[2],4.f,1.f);
    world.enemies.push_back(enemy3);

    sf::Clock clock;
    sf::View camera(sf::FloatRect(0.f,0.f,WIN_WIDTH,WIN_HEIGHT));
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        const float moveSpeed = 200.f;
        float moveX = 0.f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            moveX -= moveSpeed * deltaTime;
            user.player.setScale(-1.f,1.f);
            user.player.setOrigin(user.player.getGlobalBounds().width,0);
            audio.walkSound.play();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            moveX += moveSpeed * deltaTime;
            user.player.setScale(1.f, 1.f);
            user.player.setOrigin(0, 0);
            audio.walkSound.play();
        }
        user.player.move(moveX,0);
        checkHorizontalCollision(user.player,world.solidTiles,moveX);

        float userX = user.player.getPosition().x + user.player.getGlobalBounds().width / 2.f;
        camera.setCenter(userX,(float)WIN_HEIGHT/2.f);

        float halfWidth = camera.getSize().x / 2.f;
        float mapWidth = world.totalTileColumns * TILE_SIZE;

        if (userX < halfWidth)
            camera.setCenter(halfWidth, (float)WIN_HEIGHT/2.f);
        else if (userX > mapWidth - halfWidth)
            camera.setCenter(mapWidth - halfWidth, (float)WIN_HEIGHT/2.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && user.isOnGround){
            user.velocity.y = -JUMP_SPEED;
            user.isOnGround = false;
            audio.jumpSound.play();
        }
        user.velocity.y += GRAVITY * deltaTime * 100;
        if (user.velocity.y > 600.f) user.velocity.y = 600.f;
        user.player.move(0, user.velocity.y * deltaTime);
        checkVerticalCollision(user.player,user.isOnGround,world.solidTiles,user.velocity);

        for (auto it = world.coins.begin(); it != world.coins.end(); ) {
            if (user.player.getGlobalBounds().intersects(it->getGlobalBounds())) {
                it = world.coins.erase(it); 
                user.score++;
                audio.coinSound.play();
            } else {
                ++it;
            }
        }

        for(auto it = world.enemies.begin();it!=world.enemies.end();){
            sf::FloatRect enemyBounds = it->enemy.getGlobalBounds();
            sf::FloatRect playerBounds = user.player.getGlobalBounds();
            if(playerBounds.intersects(enemyBounds)){
                user.respawn(world.playerPosition);
                user.healthInt--;
                audio.hurtSound.play();
                if(user.healthInt == 0 && !audio.gameOverPlayed){
                    audio.bgMusic.pause();
                    audio.gameOverSound.setVolume(100.f);
                    audio.gameOverSound.play();
                    audio.gameOverPlayed = true;
                }
                // float playerBottom = user.player.getPosition().y + playerBounds.height;
                // float enemyTop = it->enemy.getPosition().y;

                //  if(playerBottom<enemyTop + 10.f && user.velocity.y>0){
                //     world.enemies.erase(it);
                //     user.velocity.y = -JUMP_SPEED/1.5f;
                // }else{
                //     user.respawn();
                //     break;
                // }
            }else it++;
        }   

        if (!world.levelComplete) {
            if (user.player.getGlobalBounds().intersects(world.goal.getGlobalBounds())) {
                world.levelComplete = true;
                std::cout << "Level Completed!\n";
                if(!audio.stageClearPlayed){
                    audio.bgMusic.pause();
                    audio.stageClearSound.setVolume(100.f);
                    audio.stageClearSound.play();
                    audio.stageClearPlayed = true;
                }
            }
        }

        window.setView(camera);
        window.clear(sf::Color::Black);
        for(auto& bg: world.sky)
            window.draw(bg);

        for (auto& tile : world.decorTiles)
            window.draw(tile);

        for (auto& tile : world.solidTiles)
            window.draw(tile);

        for (auto& coin : world.coins)
            window.draw(coin);

        for (auto &enemy : world.enemies)
        {
            enemy.update(deltaTime);
            window.draw(enemy.enemy);
        }
        window.draw(world.goal);
        user.update(deltaTime);
        window.draw(user.player);

        if (world.levelComplete) {
            sf::Vector2f viewCenter = camera.getCenter();
            sf::FloatRect textRect = world.levelCompleteText.getLocalBounds();
            world.levelCompleteText.setOrigin(textRect.width / 2, textRect.height / 2);
            world.levelCompleteText.setPosition(viewCenter.x, viewCenter.y - 100); 

            window.draw(world.levelCompleteText);
        }

        if(world.isGameOver){
            sf::Vector2f viewCenter = camera.getCenter();
            sf::FloatRect textRect = world.gameOverText.getLocalBounds();
            world.gameOverText.setOrigin(textRect.width/2,textRect.height/2);
            world.gameOverText.setPosition(viewCenter.x,viewCenter.y-100);

            window.draw(world.gameOverText);
            
        }
        user.scoreText.setString("Score: " + std::to_string(user.score));
        user.scoreText.setPosition(camera.getCenter().x - WIN_WIDTH/2 + 50.f, camera.getCenter().y - WIN_HEIGHT/2 + 50.f);
        window.draw(user.scoreText);

        user.healthSprite1.setPosition(camera.getCenter().x + WIN_WIDTH/2 - 75.f,camera.getCenter().y - WIN_HEIGHT/2 + 50.f);
        user.healthSprite2.setPosition(camera.getCenter().x + WIN_WIDTH/2 - 75.f - TILE_SIZE,camera.getCenter().y - WIN_HEIGHT/2 + 50.f);
        user.healthSprite3.setPosition(camera.getCenter().x + WIN_WIDTH/2 - 75.f - 2*TILE_SIZE,camera.getCenter().y - WIN_HEIGHT/2 + 50.f);

        if(user.healthInt == 3){
            window.draw(user.healthSprite1);
            window.draw(user.healthSprite2);
            window.draw(user.healthSprite3);
        }else if(user.healthInt == 2){
            window.draw(user.healthSprite1);
            window.draw(user.healthSprite2);
        }else if(user.healthInt == 1){
            window.draw(user.healthSprite1);
        }else{
            world.isGameOver = true;
        }

        window.display();
    }
    
}