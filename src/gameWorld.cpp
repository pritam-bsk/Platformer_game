#include "gameWorld.h"
#include "constants.h"

GameWorld::GameWorld(){
    loadTextures();
    setSprites();
}
void GameWorld::loadTextures(){
    coinTexture.loadFromFile("PNG/Items/coinGold.png");

    sf::Texture cloudTex,grassTex,grassLeftTex,grassRightTex,
                mudTex,halfgrassTex,halfgrassleftTex,halfgrassrightTex,largeHillTex,smallHillTex,
                bridgeTex,liquidWaterTopTex,liquidWaterTex,doorTopTex,mushroomTex,boxTex;

    bgTexture.loadFromFile("PNG/Background/bg.png");
    cloudTex.loadFromFile("PNG/Background/cloud1.png");
    grassTex.loadFromFile("PNG/Tiles/grassMid.png");
    grassLeftTex.loadFromFile("PNG/Tiles/grassLeft.png");
    grassRightTex.loadFromFile("PNG/Tiles/grassRight.png");
    mudTex.loadFromFile("PNG/Tiles/grassCenter.png");
    halfgrassTex.loadFromFile("PNG/Tiles/grassHalfMid.png");
    halfgrassleftTex.loadFromFile("PNG/Tiles/grassHalfLeft.png");
    halfgrassrightTex.loadFromFile("PNG/Tiles/grassHalfRight.png");
    largeHillTex.loadFromFile("PNG/Tiles/hill_large.png");
    smallHillTex.loadFromFile("PNG/Tiles/hill_small.png");
    bridgeTex.loadFromFile("PNG/Tiles/bridgeLogs.png");
    liquidWaterTopTex.loadFromFile("PNG/Tiles/liquidWaterTop.png");
    liquidWaterTex.loadFromFile("PNG/Tiles/liquidWater.png");
    doorTopTex.loadFromFile("PNG/Tiles/door_closedTop.png");
    mushroomTex.loadFromFile("PNG/Tiles/tallShroom_red.png");
    boxTex.loadFromFile("PNG/Tiles/boxAlt.png");

    //P A E C
    tiles['#'] = {mudTex,true};
    tiles['G'] = {grassTex,true};
    tiles['_'] = {halfgrassTex,true};
    tiles['S'] = {cloudTex,false};
    tiles['U'] = {halfgrassleftTex,true};
    tiles['D'] = {halfgrassrightTex,true};
    tiles['L'] = {grassLeftTex,true};
    tiles['R'] = {grassRightTex,true};
    tiles['H'] = {largeHillTex,false};
    tiles['h'] = {smallHillTex,false};
    tiles['B'] = {bridgeTex,true};
    tiles['W'] = {liquidWaterTopTex,false};
    tiles['w'] = {liquidWaterTex,false};
    tiles['a'] = {doorTopTex,false};
    tiles['M'] = {mushroomTex,false};
    tiles['*'] = {boxTex,true};
}

void GameWorld::setSprites(){
    std::ifstream mapFile(MAP_PATH);
    if (!mapFile)
    {
        std::cout<<"Map Load Error."<<std::endl;
        return;
    }

    std::string line;
    int row = 0;
    while (std::getline(mapFile,line))
    {
        totalTileColumns = std::max(totalTileColumns, static_cast<int>(line.size()));
        for (int col = 0; col < line.size(); col++)
        {
            sf::Sprite bg;
            bg.setTexture(bgTexture);
            bg.setScale((float)TILE_SIZE / bgTexture.getSize().x, (float)TILE_SIZE / bgTexture.getSize().y);
            bg.setPosition(col*TILE_SIZE, row*TILE_SIZE);
            sky.push_back(bg);
            char ch = line[col];
            if(ch != '.'){
                if(ch == 'P') {
                    playerPosition = sf::Vector2f(col*TILE_SIZE,row*TILE_SIZE);
                    continue;
                }
                else if(ch == 'E'){
                    enemyPositions.push_back(sf::Vector2f(col*TILE_SIZE,row*TILE_SIZE));
                    continue;
                }
                else if(ch == 'C'){
                    sf::Sprite coin(coinTexture);
                    coin.setPosition(col*TILE_SIZE,row*TILE_SIZE);
                    coins.push_back(coin);
                    continue;
                }
                else if(ch == 'A'){
                    goalTexture.loadFromFile("PNG/Tiles/door_closedMid.png");
                    goal.setTexture(goalTexture);
                    goal.setPosition(col * TILE_SIZE, row * TILE_SIZE);
                    continue;
                }
                sf::Sprite tile;
                tile.setTexture(tiles[ch].first);
                tile.setPosition(col*TILE_SIZE,row*TILE_SIZE);
                if(tiles[ch].second) solidTiles.push_back(tile);
                else decorTiles.push_back(tile);
            }
        }
        row++;
    }

    if (!uiFont.loadFromFile("Text/OpenSans-Bold.ttf")) {
        std::cout << "Font load error\n";
    } else {
        levelCompleteText.setFont(uiFont);
        levelCompleteText.setString("LEVEL COMPLETE!");
        levelCompleteText.setCharacterSize(48);
        levelCompleteText.setFillColor(sf::Color::Yellow);
        levelCompleteText.setOutlineColor(sf::Color::Black);
        levelCompleteText.setOutlineThickness(3);

        gameOverText.setFont(uiFont); 
        gameOverText.setString("GAME OVER!!");
        gameOverText.setCharacterSize(48);
        gameOverText.setFillColor(sf::Color::Yellow);
        gameOverText.setOutlineColor(sf::Color::Black);
        gameOverText.setOutlineThickness(3);
    }

}