#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "npc.hpp"
#define BLOCK_SIZE 32

class Level {
    int width;
    int height;
    int startPosX;
    int startPosY;
    int endConditional;

    sf::Image bgImg;
    sf::Texture bgTex;
    sf::Sprite background;

    sf::Image tileSet;

    struct brick {
        int x;
        int y;
        int width;
        int height;
    };

    struct endGame {
        int x;
        int y;
        sf::Texture textureI;
        sf::Texture textureC;
        sf::Sprite sprite;
    };

    struct gift {
        int x;
        int y;
        int value;
        sf::Sprite sprite;
        bool active;
    };

    std::vector<sf::Sprite> sBricks;
    std::vector<sf::Texture> tBricks;

public:
    endGame portal;

    std::vector<gift> gifts;

    std::vector<brick> bricks;

    std::vector<NPC> npcList;
    NPC temporary;

    bool completed;

    Level();
    ~Level();

    bool loadFromFile(std::string, sf::Texture&);
    void update(int);
    void draw(sf::RenderWindow*);
    void decreaseEndConditional();
    void resetEndConditional();
    void reinitialize();
    int getWidth();
    int getHeight();
    int getDificulty();
    sf::Vector2i getStartPos();
    sf::Vector2f brickTransformPos(int);
};
