#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

#include <Math.h>

#include "weapon.hpp"

Weapon::Weapon(){
    x=0;
    y=0;
    gX=0;
	difX1 = 0;
	difX2 = 0;
	difY = 0;
	oX = 0;
	oY = 0;

	attackSpeed = 0;

    frame=1;

    dmg=0;
    texture.setSmooth(true);

	sound_type = WeaponSound::GUN;
}

Weapon::~Weapon(){

}

void Weapon::define(std::string oName,int xx,int yy){
    if(oName=="glock"){
        x=xx;
        y=yy;

        dmg=10;
        attackSpeed=25;

        difX1=-4;
        difX2=3;
        difY=5;

        oX=5;
        oY=15;

        name=oName;
        image.loadFromFile("resources/img/glock.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);

		sound_type = WeaponSound::GUN;
    }
    if(oName=="bondGun"){
        x=xx;
        y=yy;

        dmg=25;
        attackSpeed=25;

        difX1=-4;
        difX2=3;
        difY=4;

        oX=5;
        oY=15;

        name=oName;
        image.loadFromFile("resources/img/exclusiveGlock.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);

		sound_type = WeaponSound::BONDGUN;
    }
    if(oName=="uzi"){
        x=xx;
        y=yy;

        dmg=8;
        attackSpeed=5;

        difX1=-4;
        difX2=3;
        difY=4;

        oX=6;
        oY=10;

        name=oName;
        image.loadFromFile("resources/img/uzi.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);

		sound_type = WeaponSound::UZI;
    }
    if(oName=="ak47"){
        x=xx;
        y=yy;

        dmg=50;
        attackSpeed=30;

        difX1=-4;
        difX2=3;
        difY=4;

        oX=7;
        oY=22;

        name=oName;
        image.loadFromFile("resources/img/ak.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);

		sound_type = WeaponSound::AK;
    }
    if(oName=="rifle"){
        x=xx;
        y=yy;

        dmg=70;
        attackSpeed=40;

        difX1=-4;
        difX2=3;
        difY=4;

        oX=7;
        oY=21;

        name=oName;
        image.loadFromFile("resources/img/rifle.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);

		sound_type = WeaponSound::RIFFLE;
    }
    if(oName=="smaw"){
        x=xx;
        y=yy;

        dmg=100;
        attackSpeed=80;

        difX1=-4;
        difX2=3;
        difY=2;

        oX=8;
        oY=12;

        name=oName;
        image.loadFromFile("resources/img/smaw.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);

		sound_type = WeaponSound::SMAW;
    }
    if(oName=="nicWmk1"){
        x=xx;
        y=yy;

        dmg=2;
        attackSpeed=45;

        difX1=2;
        difX2=-2;
        difY=2;

        oX=4;
        oY=12;

        name=oName;
        image.loadFromFile("resources/img/nicWmk1.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
    }
    if(oName=="nicWmk2"){
        x=xx;
        y=yy;

        dmg=10;
        attackSpeed=40;

        difX1=2;
        difX2=-2;
        difY=2;

        oX=4;
        oY=12;

        name=oName;
        image.loadFromFile("resources/img/nicWmk2.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
    }
    if(oName=="nicWmk3"){
        x=xx;
        y=yy;

        dmg=5;
        attackSpeed=35;

        difX1=2;
        difX2=-2;
        difY=2;

        oX=4;
        oY=12;

        name=oName;
        image.loadFromFile("resources/img/nicWmk3.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
    }
    if(oName=="nicWmk4"){
        x=xx;
        y=yy;

        dmg=10;
        attackSpeed=35;

        difX1=2;
        difX2=-2;
        difY=2;

        oX=4;
        oY=12;

        name=oName;
        image.loadFromFile("resources/img/nicWmk4.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
    }
    if(oName=="nicWmk5"){
        x=xx;
        y=yy;

        dmg=15;
        attackSpeed=45;

        difX1=2;
        difX2=-2;
        difY=2;

        oX=4;
        oY=12;

        name=oName;
        image.loadFromFile("resources/img/nicWmk5.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
    }
    if(oName=="nicWmk6"){
        x=xx;
        y=yy;

        dmg=20;
        attackSpeed=40;

        difX1=2;
        difX2=-2;
        difY=2;

        oX=4;
        oY=12;

        name=oName;
        image.loadFromFile("resources/img/nicWmk6.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
    }
    if(oName=="nicWmk7"){
        x=xx;
        y=yy;

        dmg=10;
        attackSpeed=40;

        difX1=2;
        difX2=-2;
        difY=2;

        oX=4;
        oY=12;

        name=oName;
        image.loadFromFile("resources/img/nicWmk7.png");
        texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
    }
}

void Weapon::update(int xx,int yy,float angle){
    x=xx;
    y=yy;

    if(angle<0){
        frame=1;
        sprite.setOrigin(oX,oY);
        x+=difX1;
        y+=difY;
        gX=difX1;
    }
    else {
        frame=0;
        sprite.setOrigin(oX,oY);
        x+=difX2;
        y+=difY;
        gX=difX2;
    }

    texture.loadFromImage(image,sf::IntRect(frame*image.getSize().x/2,0,image.getSize().x/2,image.getSize().y));
    sprite.setRotation(angle);
    sprite.setPosition(x,y);
}

void Weapon::draw(sf::RenderWindow *win){
    win->draw(sprite);
}

int Weapon::getFrame(){
    return frame;
}

int Weapon::getAttackSpeed(){
    return attackSpeed;
}

int Weapon::getX(){
    return gX;
}

int Weapon::getY(){
    return difY;
}