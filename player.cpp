#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "player.hpp"

Player::Player() {

	x = 320;
	y = 500;

	frameX = 0;
	frameY = 2;

	g = 0;

	sCnt = 0;

	hp = 150;
	maxHp = hp;

	jumpSpeed = JUMP_SPEED;
	fallSpeed = 0;
	movePhase = fall;

	lastDir = none;
	dir = none;

	image.loadFromFile("resources/img/player2OLD.png");

	width = image.getSize().x / (image.getSize().x / BLOCK_SIZE);
	height = image.getSize().y / (image.getSize().y / BLOCK_SIZE);

	texture.loadFromImage(image, sf::IntRect(0, 0, width, height));
	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	//CZAS OSTATNIEH AKTUSALIZACJI
	lastUpdate = sf::Time::Zero;

	//FLAGI KOLIZYJNE
	cUp = false;
	cRight = false;
	cDown = false;
	cLeft = false;
	cNext = false;
	//FLAGI KLAWISZOWE
	Up = false;
	Right = false;
	Left = false;
	//FLAgA STRZAŁU
	canFire = false;

	//"IMIE"
	name = "HERO";

	//GLOCK
	weapon.define("glock", x + width / 2, y + height / 2);
	activeGun = 0;

	//AMUNICJA
	for (int i = 0; i < 6; i++) {
		if (i == 0)ammunition[i] = 40;
		if (i == 1)ammunition[i] = 25;
		if (i > 1)ammunition[i] = 99;
	}

	//SCORE
	score = 0;
}

Player::~Player() {

}

void Player::update(sf::Time timer, float angle, int mapWidth) {

	//"NPRAWIAMY POZYCJE NA OSI Y"
	if (repair) {
		y = (y / height) * height;
		repair = false;
	}

	//G£OWNY WARUNEK AKTUALIZACJI BOHATERA
	if (timer.asMilliseconds() - lastUpdate.asMilliseconds() > 15) {
		//CHOOSE GUN
		chooseGun();
		//OBS£UGA KLAWIATURY
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) Right = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))  Left = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))    Up = true;

		//USTAWIENIE GRAWITACJI ORAZ FAZY RUCHU ZALEŻNEJ OD KOLIZJI
		if (!cDown) {//JESLI NIC NIE MAMY POD STOPAMI
			g = 1;
			if (movePhase != fly)movePhase = fall;
		}
		else {  //JEŚLI NA CZYMŚ STwOIMY
			g = 0;
			movePhase = stand;
			jumpSpeed = JUMP_SPEED;
			fallSpeed = 0;
		}

		//RUCH W BOKI
		if (Right && !cRight && x < mapWidth - BLOCK_SIZE) {
			x += 4;
			dir = right;
		}
		if (Left && !cLeft && x > 0) {
			x -= 4;
			dir = left;
		}
		if (Left && Right) dir = none;

		//SKAKANIE I GRAWITACJA
		if (Up && !cUp && movePhase == stand) {
			movePhase = fly;
		}
		if (movePhase == fly) {
			if (cUp) {
				movePhase = fall;
			}
			else {
				jumpSpeed -= g;
				if (jumpSpeed > 0) {
					if (scUp)jumpSpeed = y - y / 32 * 32; //OBLICZENIE ODLEGLOSCI SKOKU JESLI WYKRYTE ZOSTANIE WCZESNIEJSZE KOLIDOWANIE
					y -= jumpSpeed;
				}
				else movePhase = fall;
			}
		}
		if (movePhase == fall) {
			if (fallSpeed < FALL_SPEED_MAX)fallSpeed += g;
			if (cNext)fallSpeed = (y / height + 1) * height - y;
			y += fallSpeed;
		}

		//UPDATE GRAFICNY
		if (movePhase == stand && !Left && !Right)dir = none;
		if (angle > 0)frameY = 2;
		else frameY = 1;
		if (dir == lastDir && dir != none)frameX++;
		else frameX = 0;
		if (movePhase == fall || movePhase == fly) {
			frameX = 4;
			dir = inAir;
		}
		if (frameX > 15)frameX = 0;
		texture.loadFromImage(image, sf::IntRect(frameX / 4 * width, frameY * height, width, height));

		//ZEROWANIE FLAG
		cUp = false;
		cRight = false;
		cDown = false;
		cLeft = false;
		cNext = false;
		repair = false;
		Right = false;
		Left = false;
		Up = false;
		scUp = false;
		//USTAWIENIE FLAGI STRZAŁU
		sCnt++;
		if (sCnt > weapon.getAttackSpeed()) {
			canFire = true;
		}

		weapon.update(x + width / 2, y + height / 2, angle);

		//ZAPAMIĘTANIE KIERUNKU
		lastDir = dir;
		//POBRANIE CZASU AKTUALIZACJI ORAZ PRZYPISANIE NOWEJ POZYCJI
		lastUpdate = timer;
		sprite.setPosition(x, y);

	}
}

void Player::chooseGun() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && ammunition[0] > 0) {
		weapon.define("glock", x + width / 2, y + height / 2);
		activeGun = 0;
		sCnt = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && ammunition[1] > 0) {
		weapon.define("bondGun", x + width / 2, y + height / 2);
		activeGun = 1;
		sCnt = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && ammunition[2] > 0) {
		weapon.define("uzi", x + width / 2, y + height / 2);
		activeGun = 2;
		sCnt = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && ammunition[3] > 0) {
		weapon.define("ak47", x + width / 2, y + height / 2);
		activeGun = 3;
		sCnt = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && ammunition[4] > 0) {
		weapon.define("rifle", x + width / 2, y + height / 2);
		activeGun = 4;
		sCnt = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && ammunition[5] > 0) {
		weapon.define("smaw", x + width / 2, y + height / 2);
		activeGun = 5;
		sCnt = 0;
	}
}

void Player::award(int points) {
	score += points;
}

void Player::ammunitionRestart() {
	for (int i = 0; i < 6; i++) {
		if (i == 0)ammunition[i] = 40;
		if (i == 1)ammunition[i] = 25;
		if (i > 1)ammunition[i] = 0;
	}
	sCnt = 0;
	canFire = false;
}
