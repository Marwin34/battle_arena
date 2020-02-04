#include <iostream>
#include <ctime>
#include <Math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game.hpp"

Game::Game() {

	canQuit = false;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	window.create(sf::VideoMode(SCRN_WIDTH, SCRN_HEIGTH), "Battle Arena", sf::Style::Default, settings);
	window.setFramerateLimit(FRAME_RATE_LIMIT);
	window.setMouseCursorVisible(false);
	view.setSize(SCRN_WIDTH, SCRN_HEIGTH);
	view.setCenter(SCRN_WIDTH / 2, SCRN_HEIGTH / 2);
	window.setView(view);
	frames = 0;

	bulletList.resize(0);

	bulletImg.loadFromFile("resources/img/bullet.png");
	bulletText.loadFromImage(bulletImg);

	ammoText.loadFromFile("resources/img/ammo.png");
	kitText.loadFromFile("resources/img/kit.png");

	pointer.loadFromFile("resources/img/pointer.png");
	hitScan.loadFromFile("resources/img/hitScan.png");

	gui.initialize(SCRN_WIDTH, SCRN_HEIGTH);

	airdropPacks.resize(0);

	viewDiffs.x = SCRN_WIDTH / 2;

	gameStatus = loadingScreen;
	lastGameStatus = gameStatus;

	pushback = 0;
	difficult = 1;
	mapIndex = 0;

	theme.openFromFile("resources/sounds/maintheme.ogg");
	theme.setLoop(true);

	coinTexture.loadFromFile("resources/img/coin.png");

	level[0].loadFromFile("resources/maps/mapa1.txt", coinTexture);
	level[1].loadFromFile("resources/maps/mapa2.txt", coinTexture);
	level[2].loadFromFile("resources/maps/mapa3.txt", coinTexture);
	level[3].loadFromFile("resources/maps/mapa4.txt", coinTexture);
	level[4].loadFromFile("resources/maps/mapa5.txt", coinTexture);
	level[5].loadFromFile("resources/maps/mapa6.txt", coinTexture);
	level[6].loadFromFile("resources/maps/mapa7.txt", coinTexture);

	player1.x = level[mapIndex].getStartPos().x;
	player1.y = level[mapIndex].getStartPos().y;

	gunSounds[0].loadFromFile("resources/sounds/gun.ogg");
	gunSounds[1].loadFromFile("resources/sounds/bondGun.ogg");
	gunSounds[2].loadFromFile("resources/sounds/uzi.ogg");
	gunSounds[3].loadFromFile("resources/sounds/aka.ogg");
	gunSounds[4].loadFromFile("resources/sounds/rifle.ogg");
	gunSounds[5].loadFromFile("resources/sounds/smaw.ogg");

	current_weapon_sound = WeaponSound::GUN;
	last_weapon_sound = WeaponSound::NONE;
	sound_player.setBuffer(gunSounds[0]);
}

Game::~Game() {

}

void Game::start() {

	theme.play();

	mousePos.x = 0;
	mousePos.y = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			// ZAMKNIECIE OKNA PRZY OKRESŚLONYM WARUNKU
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//POBRANIE CZASU
		mainTimer = mainClock.getElapsedTime();
		frames++;

		if (window.hasFocus()) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))canQuit = true;
			if (gameStatus == endingScrren)gui.saveHighScore(player1.getScore());
			gui.switchState(gameStatus);

			//POBRANIE POZYCJI MYSZKI
			mousePos = sf::Mouse::getPosition(window);
			/*if(mousePos.x > SCRN_WIDTH) mousePos.x=SCRN_WIDTH;
			if(mousePos.y > SCRN_HEIGTH) mousePos.y=SCRN_HEIGTH;*/
			//sf::Mouse::setPosition(mousePos);

			cursor.setTexture(pointer);
			cursor.setOrigin(0, 0);


			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))pushback++;

			if ((gameStatus == playing && lastGameStatus == restartScreen) || (gameStatus == playing && lastGameStatus == endingScrren))reInitialize();
			if (gameStatus == playing) {

				cursor.setTexture(hitScan);
				cursor.setOrigin(9, 9);

				int pX, pXnormal, pY; //TYMCZASOWE ZMIENNE
				pX = player1.x + player1.width / 2 - (viewDiffs.x - SCRN_WIDTH / 2);
				pXnormal = player1.x + player1.width / 2;
				pY = player1.y + player1.height / 2;

				//ZAPEŁNIENIE ODNIESIEN DO NPC
				index = 0;
				for (unsigned int i = 0; i < level[mapIndex].npcList.size(); i++) {
					if (!level[mapIndex].npcList[i].toRemove) {
						wsk[index] = &level[mapIndex].npcList[i];
						index++;
					}
				}

				//RWORZENIE SPADAJĄCYCH PACZEK
				if (frames % 800 == 0) {
					int x = ((std::rand() % level[mapIndex].getWidth()) + 0) * BLOCK_SIZE;
					int a = 0;
					for (unsigned int i = 0; i < level[mapIndex].bricks.size(); i++) {
						if (level[mapIndex].bricks[i].y == 0) {//SPRAWDZAMY CZY NA POCZĄTKU AMMO NIE ZNAJDUJE SIE W SCIANIE
							if (x <= level[mapIndex].bricks[i].x * BLOCK_SIZE + level[mapIndex].bricks[i].width
								&& level[mapIndex].bricks[i].x * BLOCK_SIZE <= x + BLOCK_SIZE
								&& 0 + BLOCK_SIZE <= level[mapIndex].bricks[i].y + level[mapIndex].bricks[i].height
								&& level[mapIndex].bricks[i].height <= 0 + BLOCK_SIZE)
								a++;
						}
					}
					if (a == 0)
						airdropPacks.push_back(Airdrop(x, 0, (std::rand() % difficult) + 0, ammoText, kitText));
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player1.canFire && player1.ammunition[player1.activeGun] > 0) { //
					Bullet bullet1; // TYMCZASOWY OBIEKT KLASY BULLET
					bullet1.create(pXnormal + player1.weapon.getX(), pY, aiming(pX + player1.weapon.getX(), pY, mousePos.x, mousePos.y), player1.getName(), bulletText, player1.weapon.dmg, player1.activeGun);
					bulletList.push_back(bullet1);
					player1.canFire = false;
					player1.sCnt = 0;
					player1.ammunition[player1.activeGun]--;
					
					playSound();
				}

				//AKTUALIZACJA POCISKÓW
				for (unsigned int i = 0; i < bulletList.size(); i++) { //SPRAWDZAMY CZY POCISK NIE JEST ZA DŁUGO NA MAPIE I CZY NIE WPADŁ W ZIEMIE
					if (bulletList[i].ttl > 10 + player1.activeGun * 2) { // TU ZWIEKSZA SIE "RANGE"
						bulletList[i].toRemove = true;
					}
					for (unsigned int j = 0; j < level[mapIndex].bricks.size(); j++) {
						if (bulletList[i].colliding(level[mapIndex].bricks[j].x, level[mapIndex].bricks[j].y, level[mapIndex].bricks[j].width, level[mapIndex].bricks[j].height)) {
							bulletList[i].toRemove = true;
						}
					}
					//JEŚLI KULA TRAFI GRAZCA
					if (bulletList[i].colliding(player1.x / BLOCK_SIZE, player1.y / BLOCK_SIZE, player1.width, player1.height) && bulletList[i].originName != player1.getName()) { //  && bulletList[i].ttl>1 ODBUGOWANIESYTUCAJI GDZIE KULA RESPI SIE W STRZELCU I ZALICZA KOLIZJE NA NIM PODOBNIE NIŻEJ
						if (bulletList[i].originName != player1.getName())player1.hp -= bulletList[i].dmg;
						bulletList[i].toRemove = true;
					}
					//JASLI KULA TRAFI WROGA
					for (unsigned int j = 0; j < index; j++) {
						if (bulletList[i].colliding(wsk[j]->x / BLOCK_SIZE, wsk[j]->y / BLOCK_SIZE, wsk[j]->width, wsk[j]->height) && bulletList[i].originName == player1.getName()) {
							bulletList[i].toRemove = true;
							wsk[j]->hp -= bulletList[i].dmg;
						}
					}
					//USUWANIE ZBEDNYCH KUL
					if (bulletList[i].toRemove) {
						bulletList.erase(bulletList.begin() + i);
					}
				}

				for (unsigned int i = 0; i < bulletList.size(); i++) { //WŁAŚCIWY UPDATE
					bulletList[i].update(mainTimer);
				}

				//LOOP DO SPRAWDZANIA KOLIZJI Z OTOCZENIEM (GRACZ)
				for (unsigned int i = 0; i < level[mapIndex].bricks.size(); i++) {
					player1.collisionDetect(level[mapIndex].bricks[i].x, level[mapIndex].bricks[i].y, level[mapIndex].bricks[i].width, level[mapIndex].bricks[i].height);
				}
				for (unsigned int i = 0; i < index; i++) {
					player1.collisionDetect(wsk[i]->x / BLOCK_SIZE, wsk[i]->y / BLOCK_SIZE, wsk[i]->width, wsk[i]->height);
				}
				//SPRAWDZANIE KOLIZJI Z MONETAMI
				for (unsigned int i = 0; i < level[mapIndex].gifts.size(); i++) {
					float r = sqrt(pow(player1.x - level[mapIndex].gifts[i].x, 2) + pow(player1.y - level[mapIndex].gifts[i].y, 2));
					if (r < 20 && level[mapIndex].gifts[i].active) {
						level[mapIndex].gifts[i].active = false;
						player1.award(level[mapIndex].gifts[i].value);
					}
				}

				//TEST KOLIZJI NPC
				for (unsigned int i = 0; i < index; i++) {
					wsk[i]->collisionDetect(player1.x / BLOCK_SIZE, player1.y / BLOCK_SIZE, player1.width, player1.height);
					for (unsigned int j = 0; j < level[mapIndex].bricks.size(); j++) {
						wsk[i]->collisionDetect(level[mapIndex].bricks[j].x, level[mapIndex].bricks[j].y, level[mapIndex].bricks[j].width, level[mapIndex].bricks[j].height);
						wsk[i]->LineCast(player1.transformPos(), level[mapIndex].brickTransformPos(j), level[mapIndex].bricks[j].width, level[mapIndex].bricks[j].height);
					}
				}

				//PĘTLA DLA SPADAJĄCYCH PACZEK
				for (unsigned int i = 0; i < airdropPacks.size(); i++) {
					for (unsigned int j = 0; j < level[mapIndex].bricks.size(); j++) {
						airdropPacks[i].collisionDetect(level[mapIndex].bricks[j].x, level[mapIndex].bricks[j].y, level[mapIndex].bricks[j].width, level[mapIndex].bricks[j].height);
					}
					airdropPacks[i].update(mainTimer);
					if (airdropPacks[i].colliding(player1.x, player1.y, player1)) {
						airdropPacks.erase(airdropPacks.begin() + i);
					}
					if (airdropPacks[i].y > level[mapIndex].getHeight()* BLOCK_SIZE)airdropPacks.erase(airdropPacks.begin() + i);
				}
				//AKTUALIZAJCA GRACZA
				player1.update(mainTimer, aiming(pX, pY, mousePos.x, mousePos.y), level[mapIndex].getWidth() * BLOCK_SIZE);

				//ALTUALIZJACJA WROGA ORAZ STRZAŁ
				for (unsigned int i = 0; i < index; i++) {
					int nX, nY; //TYMCZASOWE ZMIENNE
					nX = wsk[i]->x + wsk[i]->width / 2;
					nY = wsk[i]->y + wsk[i]->height / 2;
					wsk[i]->update(mainTimer, player1.x, player1.y, player1.width, player1.height, aiming(nX, nY, pXnormal, pY));
					if (wsk[i]->canFire) {
						Bullet bullet1; // TYMCZASOWY OBIEKT KLASY BULLET
						bullet1.create(nX, nY, aiming(nX, nY, pXnormal, pY), wsk[i]->getName(), bulletText, 10, 0);
						bulletList.push_back(bullet1);
						wsk[i]->canFire = false;
						wsk[i]->sCnt = 0;
					}
					//USTAWIENIE FLAGI USUNIECIA WROGA
					if (wsk[i]->hp <= 0) {
						wsk[i]->toRemove = true;
						player1.award(wsk[i]->getScore());
						level[mapIndex].decreaseEndConditional();
					}
				}

				//USTAWIENIE FLAGI KONCA POZIOMU
				if (player1.y == level[mapIndex].portal.y) {
					if (player1.x == level[mapIndex].portal.x) {
						if (level[mapIndex].completed) {
							if (difficult < MAP_COUNT)difficult++;
							if (mapIndex + 1 > MAP_COUNT - 1)gui.setMode("quit");
							else {
								mapIndex++;
								initialize();
							}
						}
					}
				}

				//AKTUALIZACJA WIDOKU,TŁA,GUI(INGAME) I WYŒWIETLANIE
				viewUpdate(player1.x);
				level[mapIndex].update(viewDiffs.x);
				gui.updateWhilePlaying(player1.activeGun, player1.getMaxHp(), player1.getHp(), &player1.ammunition[0], player1.getScore(), viewDiffs.x, mapIndex);
				window.setView(view);
			}
			lastGameStatus = gameStatus;
			if (player1.hp <= 0 || player1.y > SCRN_HEIGTH)gui.setMode("restart");
			gui.activeButtons(mousePos.x + viewDiffs.x - 400, mousePos.y, pushback, gameStatus);
			cursor.setPosition(static_cast<float>(mousePos.x + viewDiffs.x - SCRN_WIDTH / 2), static_cast<float>(mousePos.y));
			pushback = 0;
		}
		draw();

		if (canQuit) window.close();

		//std::cout<<"FPS : "<<static_cast<int>(frames / mainTimer.asSeconds())<<std::endl; // FPSY
		//KONIEC PEWTLI G£ÓWNEJ
	}
}

void Game::draw() {
	window.clear();

	if (gameStatus == playing) {
		level[mapIndex].draw(&window);
		for (unsigned int i = 0; i < airdropPacks.size(); i++)airdropPacks[i].draw(&window);

		//WYŚWIETLANIE NPC
		for (unsigned int i = 0; i < index; i++) {
			wsk[i]->draw(&window);
		}

		player1.draw(&window);

		//WYŚWIETLANIE POCISKÓW
		for (unsigned int i = 0; i < bulletList.size(); i++) {
			bulletList[i].draw(&window);
		}
	}
	gui.draw(&window);
	window.draw(cursor);
	window.display();
}

float Game::aiming(int x, int y, int dstX, int dstY) {
	int diffX = 0, diffY = 0;

	diffX = x - dstX;
	diffY = y - dstY;

	return  atan2(diffX * (-1), diffY) * 180 / PI;
}

void Game::viewUpdate(int x) {
	if (x > SCRN_WIDTH / 2 - 4 && x < level[mapIndex].getWidth() * BLOCK_SIZE - SCRN_WIDTH / 2) {
		if (x > viewDiffs.x) {
			viewDiffs.x += MOVE_SPEED;
			view.move(MOVE_SPEED, 0);
		}
		if (x < viewDiffs.x) {
			viewDiffs.x -= MOVE_SPEED;
			view.move(-MOVE_SPEED, 0);
		}
		if (x == viewDiffs.x) {
			view.move(0, 0);
		}
	}
}

void Game::initialize() {
	player1.x = level[mapIndex].getStartPos().x;
	player1.y = level[mapIndex].getStartPos().y;

	bulletList.resize(0);
	airdropPacks.resize(0);
	viewDiffs.x = SCRN_WIDTH / 2;;
	level[mapIndex].update(viewDiffs.x);
	gui.updateWhilePlaying(player1.activeGun, player1.getMaxHp(), player1.getHp(), &player1.ammunition[0], player1.getScore(), viewDiffs.x, mapIndex);
	view.setCenter(SCRN_WIDTH / 2, SCRN_HEIGTH / 2);
	window.setView(view);
	gui.resetHSflag();
}

void Game::reInitialize() {
	mapIndex = 0;
	difficult = 1;
	initialize();
	player1.resetScore();
	player1.hp = player1.getMaxHp();
	player1.ammunitionRestart();
	for (int j = 0; j < MAP_COUNT; j++) {
		level[j].reinitialize();
		for (unsigned int i = 0; i < level[j].npcList.size(); i++) {
			wsk[i] = &level[j].npcList[i];
			wsk[i]->hp = wsk[i]->getMaxHp();
			wsk[i]->toRemove = false;
		}
		for (unsigned int i = 0; i < level[j].gifts.size(); i++) {
			level[j].gifts[i].active = true;
		}
	}
	std::cout << "REINITIALIZE" << std::endl;
}

void Game::playSound() {
	current_weapon_sound = player1.weapon.sound_type;

	if (current_weapon_sound == last_weapon_sound) {
		sound_player.setPlayingOffset(sf::seconds(0.0f));
		if (sound_player.getStatus() == sf::SoundSource::Status::Stopped) {
			sound_player.play();
		}
	}
	else {
		switch (current_weapon_sound)
		{
		case WeaponSound::GUN:
			sound_player.setBuffer(gunSounds[0]);
			break;
		case WeaponSound::BONDGUN:
			sound_player.setBuffer(gunSounds[1]);
			break;
		case WeaponSound::UZI:
			sound_player.setBuffer(gunSounds[2]);
			break;
		case WeaponSound::AK:
			sound_player.setBuffer(gunSounds[3]);
			break;
		case WeaponSound::RIFFLE:
			sound_player.setBuffer(gunSounds[4]);
			break;
		case WeaponSound::SMAW:
			sound_player.setBuffer(gunSounds[5]);
			break;
		default:
			break;
		}
		sound_player.play();
		last_weapon_sound = current_weapon_sound;
	}
}
