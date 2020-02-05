#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "level.hpp"

Level::Level()
{
    width = 0;
    height = 0;

    completed = false;

    endConditional = 0;

    startPosX = 0;
    startPosY = 0;

    bgImg.loadFromFile("resources/img/background.png");
    bgTex.loadFromImage(bgImg);
    background.setTexture(bgTex);
    background.setPosition(0, 0);

    bricks.clear();
    sBricks.clear();
    tBricks.clear();

    tileSet.loadFromFile("resources/img/newTileset.png");

    sf::Texture tmpTexture;

    for (unsigned int i = 0; i < tileSet.getSize().x / BLOCK_SIZE; i++) {
        tmpTexture.loadFromImage(tileSet, sf::IntRect(i * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE));
        tBricks.push_back(tmpTexture);
    }
    gifts.resize(0);
    npcList.resize(0);
}

Level::~Level() { }

bool Level::loadFromFile(std::string path, sf::Texture& coinTexture)
{
    completed = false;
    int tmpWidth = 0, tmpHeight = 0, fileBuffor, index = 0;
    std::string tmpString = "";
    std::vector<std::vector<int>> tmpBricks;
    brick tmpBrick;
    sf::Sprite tmpSprite;

    // OPEN SOURCE FILE
    std::ifstream file;
    file.open(path.c_str());

    if (!file.is_open())
        return false;

    file >> tmpWidth >> tmpHeight;

    // SET TMP ARRAY SIZE
    tmpBricks.resize(tmpHeight);
    for (int i = 0; i < tmpHeight; i++) {
        tmpBricks[i].resize(tmpWidth);
    }

    for (int h = 0; h < tmpHeight; h++) {
        for (int w = 0; w < tmpWidth; w++) {
            file >> fileBuffor;
            if (fileBuffor == 0)
                tmpBricks[h][w] = fileBuffor;
            else
                tmpBricks[h][w] = fileBuffor - 1;
        }
    }

    // CONVERT ARRAY TO STRUCTURES
    for (int h = 0; h < tmpHeight; h++) {
        for (int w = 0; w < tmpWidth; w++) {
            // MERGE BRICKS TO BLOCKS
            if (tmpBricks[h][w] >= 1) {
                if (index > 0 && (w > 0 && tmpBricks[h][w - 1] >= 1)) {
                    bricks[index - 1].width += BLOCK_SIZE;
                } else {
                    tmpBrick.x = w;
                    tmpBrick.y = h;
                    tmpBrick.width = BLOCK_SIZE;
                    tmpBrick.height = BLOCK_SIZE;

                    bricks.push_back(tmpBrick);
                    index++;
                }
                tmpSprite.setTexture(tBricks[tmpBricks[h][w]]);
                tmpSprite.setPosition(w * BLOCK_SIZE, h * BLOCK_SIZE);
                sBricks.push_back(tmpSprite);
            }
        }
    }

    file >> fileBuffor;
    npcList.resize(fileBuffor);
    endConditional = fileBuffor;
    index = 0;
    while (!file.eof()) {
        int tmp1 = 0, tmp2 = 0;
        std::string tmp3 = "";
        file >> tmp1 >> tmp2 >> tmp3;
        if (tmp3 == "End" || tmp3 == "Start" || tmp3 == "50" || tmp3 == "100") {
            if (tmp3 == "End") {
                portal.x = tmp1 * BLOCK_SIZE;
                portal.y = tmp2 * BLOCK_SIZE;
                portal.textureI.loadFromFile("resources/img/incompleteFlag.png");
                portal.textureC.loadFromFile("resources/img/completeFlag.png");
                portal.sprite.setTexture(portal.textureI);
                portal.sprite.setPosition(portal.x, portal.y);
            }
            if (tmp3 == "Start") {
                startPosX = tmp1;
                startPosY = tmp2;
            }
            if (tmp3 == "50" || tmp3 == "100") {
                gift tmpGift;
                tmpGift.x = tmp1 * BLOCK_SIZE;
                tmpGift.y = tmp2 * BLOCK_SIZE;
                tmpGift.value = atoi(tmp3.c_str());
                tmpGift.sprite.setTexture(coinTexture);
                tmpGift.sprite.setPosition(tmpGift.x, tmpGift.y);
                tmpGift.active = true;
                gifts.push_back(tmpGift);
            }

        } else {
            npcList[index].create(tmp1 * BLOCK_SIZE, tmp2 * BLOCK_SIZE, tmp3);
            index++;
        }
    }
    file.close();

    width = tmpWidth;
    height = tmpHeight;

    return true;
}

void Level::update(int x)
{
    x -= 400; // HALF OF SCREEN SIZE
    background.setPosition(x, 0);
    if (endConditional == 0) {
        portal.sprite.setTexture(portal.textureC);
        completed = true;
    }
}

void Level::decreaseEndConditional() { endConditional--; }

void Level::resetEndConditional() { endConditional = npcList.size(); }

void Level::reinitialize()
{
    portal.sprite.setTexture(portal.textureI);
    completed = false;
    resetEndConditional();
}

void Level::draw(sf::RenderWindow* win)
{
    win->draw(background);
    for (unsigned int i = 0; i < sBricks.size(); i++)
        win->draw(sBricks[i]);
    for (unsigned int i = 0; i < gifts.size(); i++) {
        if (gifts[i].active)
            win->draw(gifts[i].sprite);
    }
    win->draw(portal.sprite);
}

int Level::getWidth() { return width; }

int Level::getHeight() { return height; }

sf::Vector2i Level::getStartPos()
{
    sf::Vector2i pos;
    pos.x = startPosX * BLOCK_SIZE;
    pos.y = startPosY * BLOCK_SIZE;
    return pos;
}

sf::Vector2f Level::brickTransformPos(int index)
{
    sf::Vector2f tmp;
    tmp.x = bricks[index].x;
    tmp.y = bricks[index].y;
    return tmp;
}
