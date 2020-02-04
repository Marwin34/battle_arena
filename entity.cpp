#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "entity.hpp"

Entity::Entity() {

	x = 0;
	y = 0;
	width = BLOCK_SIZE;
	height = BLOCK_SIZE;

	cUp = false;
	cRight = false;
	cDown = false;
	cLeft = false;
	cNext = false;

	canFire = false;
	canSeePlayer = false;

	lStop = false;
	rStop = false;

	repair = false;

	scUp = false;

	dir = -1;
	lastDir = dir;

	fallSpeed = 0;
	jumpSpeed = 0;

	frameX = 0;
	frameY = 0;

	g = 0;

	hp = 0;
	maxHp = hp;

	movePhase = 0;

	sCnt = 0;

	score = 0;
}

Entity::~Entity() {

}

sf::Vector2f Entity::vectorDir(sf::Vector2f start, sf::Vector2f endp) {
	sf::Vector2f delta;
	delta.x = endp.x - start.x;
	delta.y = endp.y - start.y;

	return delta;
}

sf::Vector2f Entity::transformPos() {
	sf::Vector2f tmp;
	tmp.x = x;
	tmp.y = y;
	return tmp;
}

bool Entity::compareVectorsDir(sf::Vector2f dir1, sf::Vector2f dir2) {
	if (dir1.x * dir2.x > 0 && dir1.y * dir2.y > 0)
		return true;
	else return false;
}

void Entity::LineCast(sf::Vector2f ppos, sf::Vector2f opos, int owidth, int oheight) {
	float xa = x + 16;
	float ya = y + 16;

	sf::Vector2f start;
	start.x = xa;
	start.y = ya;

	float xb = ppos.x + 16;
	float yb = ppos.y + 16;

	sf::Vector2f endp;
	endp.x = xb;
	endp.y = yb;

	float a = (yb - ya) / (xb - xa);
	float b = (-xa * yb + xb * ya) / (xb - xa);

	float targetX = (opos.y * 32 - b) / a;

	sf::Vector2f middle1;
	middle1.x = targetX;
	middle1.y = opos.y;

	float targetX2 = ((opos.y * 32 + oheight) - b) / a;

	sf::Vector2f middle2;
	middle2.x = targetX2;
	middle2.y = opos.y * 32;

	if ((opos.x * 32 <= targetX && targetX <= opos.x * 32 + owidth) ||
		(opos.x * 32 <= targetX2 && targetX2 <= opos.x * 32 + owidth)) {
		if ((compareVectorsDir(vectorDir(start, middle1), vectorDir(middle1, endp)) || compareVectorsDir(vectorDir(start, middle2), vectorDir(middle2, endp))))
			canSeePlayer = false;
	}
}

void Entity::draw(sf::RenderWindow* win) {
	if (weapon.getFrame() == 0) {
		win->draw(sprite);
		weapon.draw(win);
	}
	else {
		weapon.draw(win);
		win->draw(sprite);
	}
	win->draw(hpBar);
}

void Entity::collisionDetect(int boxX, int boxY, int boxWidth, int boxHeight) {
	//NORMALOZACJA DANYCH WEJŒCIOWYCH (x32)
	boxX *= BLOCK_SIZE;
	boxY *= BLOCK_SIZE;

	if (x + 1 <= boxX + boxWidth
		&& boxX <= x + 1 + width - 2
		&& y + height <= boxY + boxHeight
		&& boxY <= y + height)
		cDown = true;

	if (x + width <= boxX + boxWidth
		&& boxX <= x + width
		&& y + 1 <= boxY + boxHeight
		&& boxY <= y + 1 + height - 2)
		cRight = true;

	if (x + 1 <= boxX + boxWidth
		&& boxX <= x + 1 + width - 2
		&& y - 1 <= boxY + boxHeight
		&& boxY <= y - 1)
		cUp = true;

	if (x <= boxX + boxWidth
		&& boxX <= x + 1
		&& y + 1 <= boxY + boxHeight
		&& boxY <= y + 1 + height - 2)
		cLeft = true;

	//DLA LEPSZEGO SKAKANIA  DODATKOWA KOLIZJA "PRZED" PRAWIDŁOWĄ KOLIZJĄ
	if (x + 1 <= boxX + boxWidth
		&& boxX <= x + 1 + width - 2
		&& y + height + fallSpeed <= boxY + boxHeight
		&& boxY <= y + height + fallSpeed)
		cNext = true;

	//JEŚLI DOLNY PRAWY LUB LEWY RÓG ZNAJDUJĄ SIE W PRZESZKODZIE TO USTAWIAMY FLAGE REPAIR

	if (movePhase == stand) {
		if (x < boxX + boxWidth
			&& boxX < x
			&& y + height < boxY + boxHeight
			&& boxY < y + height)
			repair = true;

		if (x + width < boxX + boxWidth
			&& boxX < x + width
			&& y + height < boxY + boxHeight
			&& boxY < y + height)
			repair = true;
	}
	//WCZEŚNIEJSZE WYKRYWANIE KOLIZJI PRZY SKOKU (FAZA DO GÓRY)
	if (x + 1 <= boxX + boxWidth
		&& boxX <= x + 1 + width - 2
		&& y - jumpSpeed <= boxY + boxHeight
		&& boxY <= y - jumpSpeed)
		scUp = true;

	//TYLKO DLA NPC

	if (x - 1 <= boxX + boxWidth
		&& boxX <= x - 1 + 1
		&& y + height <= boxY + boxHeight
		&& boxY <= y + height + 1)
		lStop = true;

	if (x + width + 1 <= boxX + boxWidth
		&& boxX <= x + width + 1
		&& y + height <= boxY + boxHeight
		&& boxY <= y + height + 1)
		rStop = true;
}

void Entity::resetScore() {
	score = 0;
}

std::string Entity::getName() {
	return name;
}

int Entity::getHp() {
	return hp;
}

int Entity::getMaxHp() {
	return maxHp;
}

int Entity::getScore() {
	return score;
}

