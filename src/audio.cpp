#include "audio.h"
#include <iostream>

Audio::Audio(){
    if(!bgMusic.openFromFile("Audio/SuperMarioBros.mp3")){
        std::cout<<"bgMusic Load Failed!"<<std::endl;
    }
    bgMusic.setLoop(true);
    bgMusic.setVolume(50.f);
    bgMusic.play();

    coinBuffer.loadFromFile("Audio/smb_coin.wav");
    coinSound.setBuffer(coinBuffer);

    jumpBuffer.loadFromFile("Audio/smb_jump.wav");
    jumpSound.setBuffer(jumpBuffer);

    stageClearBuffer.loadFromFile("Audio/smb_stage_clear.wav");
    stageClearSound.setBuffer(stageClearBuffer);

    gameOverBuffer.loadFromFile("Audio/smb_gameover.wav");
    gameOverSound.setBuffer(gameOverBuffer);

    walkBuffer.loadFromFile("Audio/smb_walk.wav");
    walkSound.setBuffer(walkBuffer);

    hurtBuffer.loadFromFile("Audio/smb_walk.wav");
    hurtSound.setBuffer(hurtBuffer);
}
