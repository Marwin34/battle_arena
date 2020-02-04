#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "gui.hpp"
#include "level.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "airdrop.hpp"

#define PI 3.14159265
#define MOVE_SPEED 4
#define MAP_COUNT 7
#define SCRN_WIDTH 800
#define SCRN_HEIGTH 608
#define BLOCK_SIZE 32
#define FRAME_RATE_LIMIT 100


//using namespace sf;

class Game {
    int gameStatus;
    int lastGameStatus;
    enum status {
        loadingScreen,
        playing,
        restartScreen,
        endingScrren,
    };

    int pushback;
    int difficult;
    int frames;
    bool canQuit;

    int mapIndex;
    sf::Vector2i viewDiffs;

    sf::RenderWindow window;
    sf::View view;

    sf::Clock mainClock;
    sf::Time mainTimer;

    Gui gui;
    Level level[MAP_COUNT];
    Player player1;
    std::vector <Bullet> bulletList;
    //WSKAèNIK DLA NPC
    NPC *wsk[15];

    unsigned int index;

    sf::Vector2i mousePos;

    sf::Image bulletImg;
    sf::Texture bulletText;

    std::vector <Airdrop> airdropPacks;
    sf::Texture ammoText;
    sf::Texture kitText;

    //KURSORY
    sf::Sprite cursor;
    sf::Texture pointer;
    sf::Texture hitScan;
    sf::Texture coinTexture;

    // MUZYKA
    sf::Music theme;

	sf::SoundBuffer gunSounds[6];
	sf::Sound sound_player;

	WeaponSound current_weapon_sound;
	WeaponSound last_weapon_sound;
	
public:

    Game();
    ~Game();

    void start();
    void initialize();
	void reInitialize();
    float aiming(int,int,int,int);
	void playSound();
    void viewUpdate(int);
    void draw();

};
