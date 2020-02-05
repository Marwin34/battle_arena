#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "gui.hpp"

Gui::Gui()
{
    mode = sScreen;
    hSSaved = false;

    gunsImage.loadFromFile("resources/img/guns.png");
    gunsTexture[0].loadFromImage(gunsImage, sf::IntRect(0, 0, 32, 32));
    gunsTexture[1].loadFromImage(gunsImage, sf::IntRect(32, 0, 32, 32));

    for (int i = 0; i < 6; i++) {
        gunsTexture[i].loadFromImage(gunsImage, sf::IntRect(i * 32, 0, 32, 32));
        guns[i].setTexture(gunsTexture[i]);
    }

    playerHpTexture.loadFromFile("resources/img/playerhp2.png");
    playerHp.setTexture(playerHpTexture);
    playerHpBgTexture.loadFromFile("resources/img/playerhp.png");
    playerHpBg.setTexture(playerHpBgTexture);

    startTexture.loadFromFile("resources/img/start.png");
    endTexture.loadFromFile("resources/img/end.png");
    completeTexture.loadFromFile("resources/img/complete.png");
    lockedTexture.loadFromFile("resources/img/locked.png");

    locked.setTexture(lockedTexture);

    delayCnt = 0;
    lastMapIndex = -1;
}

Gui::~Gui() { }

void Gui::initialize(int sWidth, int sHeight)
{
    loadHighScores();
    gunsPosition = sWidth - gunsImage.getSize().x;
    int y = 0;

    for (int i = 0; i < 6; i++) {
        guns[i].setPosition(gunsPosition + i + 32, y);
    }

    playerHp.setPosition(1, 1);
    playerHpBg.setPosition(0, 0);

    ammuntion[0].setCharSize(12);
    ammuntion[0].setPosition(sWidth - 64, 18);

    ammuntion[1].setCharSize(12);
    ammuntion[1].setPosition(sWidth - 32, 18);

    ammuntion[2].setCharSize(12);
    ammuntion[2].setPosition(sWidth, 18);

    ammuntion[3].setCharSize(12);
    ammuntion[3].setPosition(sWidth + 32, 18);

    ammuntion[4].setCharSize(12);
    ammuntion[4].setPosition(sWidth + 64, 18);

    ammuntion[5].setCharSize(12);
    ammuntion[5].setPosition(sWidth + 96, 18);

    pointsPosition = sWidth / 2 + 20;
    points.setCharSize(20);
    points.setFillColor(127, 0, 127);
    points.setPosition(pointsPosition, 5);

    scorePosition = sWidth / 2 - 60;
    scores.setCharSize(20);
    scores.setFillColor(127, 0, 127);
    scores.setPositionAndValue(scorePosition, 5, "SCORE:");

    pointsPosition = sWidth / 2 + 20;
    ePoints.setCharSize(30);
    ePoints.setFillColor(255, 255, 0);
    ePoints.setPosition(pointsPosition + 10, 110);

    scorePosition = sWidth / 2 - 60;
    eScores.setCharSize(30);
    eScores.setFillColor(255, 255, 0);
    eScores.setPositionAndValue(scorePosition - 30, 110, "SCORE: ");

    hScores.setCharSize(15);
    hScores.setFillColor(255, 255, 0);
    hScores.setPositionAndValue(640, 180, scoreString);

    instruction.setCharSize(12);
    instruction.setFillColor(255, 255, 0);
    instruction.setPositionAndValue(
        5, 540, " INSTRUKCJA: \n PORUSZANIE - strzalki lub W,A,D \n STRZELANIE - LPM");

    mapName.index.setCharSize(30);
    mapName.index.setFillColor(255, 255, 0);
    mapName.index.setPosition(sWidth / 2 + 10, 35);

    mapName.name.setCharSize(30);
    mapName.name.setFillColor(255, 255, 0);
    mapName.name.setPositionAndValue(sWidth / 2 - 70, 35, "MAPA: ");

    startScreen.setPosition(0, 0);
    startScreen.setTexture(startTexture);

    endScreen.setPosition(0, 0);
    endScreen.setTexture(endTexture);

    completeScreen.setPosition(0, 0);
    completeScreen.setTexture(completeTexture);

    startButton.define(300, 530, "start");
    restartButton.define(300, 20, "restart");
    quitButton.define(550, 530, "quit");
}

void Gui::activeButtons(int mouseX, int mouseY, int locker, int& gameStatus)
{
    startButton.checkClick(mouseX, mouseY, mode, locker);
    restartButton.checkClick(mouseX, mouseY, mode, locker);
    quitButton.checkClick(mouseX, mouseY, mode, locker);
}

void Gui::switchState(int& gameStatus)
{
    if (mode == sScreen)
        gameStatus = 0;
    if (mode == rScreen)
        gameStatus = 1;
    if (mode == eScreen)
        gameStatus = 2;
    if (mode == cScrren)
        gameStatus = 3;
}

void Gui::setMode(std::string name)
{
    if (name == "restart")
        mode = eScreen;
    if (name == "quit")
        mode = cScrren;
}

void Gui::updateWhilePlaying(
    int index, int maxHp, int hp, int* aTable, int score, int x, int mapIndex)
{

    if (mode == rScreen) {
        for (int i = 0; i < 6; i++) {
            ammuntion[i].setValue(aTable[i]);
        }

        playerHp.setScale(static_cast<float>(hp) / static_cast<float>(maxHp), 1);

        points.setValue(score);
        ePoints.setValue(score);

        int newX = 0;
        newX = gunsPosition + x - 400; // 400 HALF OF SCREEN WIDTH
        for (int i = 0; i < 6; i++) {
            guns[i].setPosition(newX + i * 32, 0);
        }
        locked.setPosition(guns[index].getPosition().x, guns[index].getPosition().y);

        newX = 0 + x - 400;
        playerHp.setPosition(newX + 1, 1);
        playerHpBg.setPosition(newX, 0);

        newX = gunsPosition + x - 400;
        for (int i = 0; i < 6; i++) {
            ammuntion[i].setPosition(newX + i * 32, 18);
        }

        newX = pointsPosition + x - 400;
        points.setPosition(newX, 5);
        ePoints.setPosition(newX + 10, 110);

        newX = scorePosition + x - 400;
        scores.setPositionAndValue(newX, 5, "SCORE:");
        eScores.setPositionAndValue(newX - 30, 110, "SCORE:");

        endScreen.setPosition(x - 400, 0);
        restartButton.setPosition(x - 400, 0);
        startScreen.setPosition(x - 400, 0);

        mapName.index.setPosition(x + 20, 35);
        mapName.name.setPositionAndValue(x - 70, 35, "MAPA: ");

        completeScreen.setPosition(x - 400, 0);
        quitButton.setPosition(x - 400, 0);
        hScores.setPositionAndValue(x + 640 - 400, 180, scoreString);
        instruction.setPositionAndValue(x + 5 - 400, 540,
            " INSTRUKCJA: \n PORUSZANIE - strzalki lub W,A,D \n STRZELANIE - LPM");

        if (mapIndex != lastMapIndex) {
            mapName.index.setValue(mapIndex + 1);
            mapName.display = true;
            delayCnt = 200;
            lastMapIndex = mapIndex;
        }
        if (delayCnt > 1) {
            delayCnt--;
        } else
            mapName.display = false;

        lastMapIndex = mapIndex;
    }
}

void Gui::loadHighScores()
{
    std::ifstream file;
    file.open("C:/hs.txt", std::ios::app);
    std::string score;
    std::string index;
    scoreString = "HIGH SCORE: \n";
    int cnt = 0;
    while (file >> index >> score) {
        scoreString = scoreString + index + " : " + score + " points\n";
        if (cnt++ > 8)
            break;
    }
    file.close();
}

void Gui::saveHighScore(int eScore)
{
    if (!hSSaved) {
        std::ofstream file;
        std::ifstream file2;
        file.open("C:/tmp.txt", std::ios::app);
        file2.open("C:/hs.txt", std::ios::app);
        int fScore;
        std::vector<int> dataBufor;
        int tmp;

        while (file2 >> tmp >> fScore) {
            dataBufor.push_back(fScore);
        }
        dataBufor.push_back(eScore);

        // BUBBLE SORT
        for (unsigned int i = 0; i < dataBufor.size(); i++) {
            for (unsigned int j = 0; j < dataBufor.size() - 1; j++) {
                if (dataBufor[j] < dataBufor[j + 1])
                    std::swap(dataBufor[j], dataBufor[j + 1]);
            }
        }

        for (unsigned int i = 0; i < dataBufor.size(); i++) {
            file << i + 1 << " " << dataBufor[i] << std::endl;
        }
        file.close();
        file2.close();
        remove("C:/hs.txt");
        rename("C:/tmp.txt", "C:/hs.txt");

        hSSaved = true;
    }
}

void Gui::resetHSflag() { hSSaved = false; }

void Gui::draw(sf::RenderWindow* win)
{
    if (mode == sScreen) {
        win->draw(startScreen);
        startButton.draw(win);
        hScores.draw(win);
        instruction.draw(win);
    }
    if (mode == rScreen) {
        for (int i = 0; i < 6; i++) {
            win->draw(guns[i]);
        }
        win->draw(locked);
        win->draw(playerHpBg);
        win->draw(playerHp);

        for (int i = 0; i < 6; i++)
            ammuntion[i].draw(win);

        points.draw(win);
        scores.draw(win);
        if (mapName.display) {
            mapName.name.draw(win);
            mapName.index.draw(win);
        }
    }
    if (mode == eScreen) {
        win->draw(endScreen);
        restartButton.draw(win);
        ePoints.draw(win);
        eScores.draw(win);
        quitButton.draw(win);
    }
    if (mode == cScrren) {
        loadHighScores();
        win->draw(completeScreen);
        restartButton.draw(win);
        quitButton.draw(win);
        ePoints.draw(win);
        eScores.draw(win);
        hScores.draw(win);
    }
}
