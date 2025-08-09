#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>

class Audio{
public:
    sf::Music bgMusic;

    sf::SoundBuffer coinBuffer;
    sf::Sound coinSound;

    sf::SoundBuffer jumpBuffer;
    sf::Sound jumpSound;

    sf::SoundBuffer stageClearBuffer;
    sf::Sound stageClearSound;
    bool stageClearPlayed = false;

    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverSound;
    bool gameOverPlayed = false;

    sf::SoundBuffer walkBuffer;
    sf::Sound walkSound;

    sf::SoundBuffer hurtBuffer;
    sf::Sound hurtSound;
public:
    Audio();
};

#endif