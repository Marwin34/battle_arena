#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "button.hpp"

Button::Button(){
    terminateWindow=false;
}

Button::~Button(){

}

void Button::define(int xx, int yy, std::string nAction){
    //ZDEFINIOWANIE PARAMETRÓW PRZYCISKU ZGODNIE Z PRZEZNACZENIEM
    if(nAction=="start"){
        x=xx-texture.getSize().x/2;
        y=yy-texture.getSize().y/2;
        startX=x;
        texture.loadFromFile("resources/img/startButton.png");
        hTexture.loadFromFile("resources/img/startButtonA.png");
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
        action=nAction;
    }
    if(nAction=="quit"){
        x=xx-texture.getSize().x/2;
        y=yy-texture.getSize().y/2;
        startX=x;
        texture.loadFromFile("resources/img/quitButton.png");
        hTexture.loadFromFile("resources/img/quitButtonA.png");
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
        action=nAction;
    }
    if(nAction=="restart"){
        x=xx-texture.getSize().x/2;
        y=yy-texture.getSize().y/2;
        startX=x;
        texture.loadFromFile("resources/img/restartButton.png");
        hTexture.loadFromFile("resources/img/restartButtonA.png");
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
        action=nAction;
    }


}

void Button::checkClick(int mouseX, int mouseY, int &mode, int pushback){
    if(mouseX>x && mouseX<x+texture.getSize().x && mouseY>y && mouseY<y+texture.getSize().y){
        if(pushback>0){
            if(mode==0 && action=="start")
                mode=1;
            if((mode==2 || mode==3) && action=="restart")
                mode=1;
            if((mode==3 || mode==2) && action=="quit")
                terminateWindow=true;
        }
        sprite.setTexture(hTexture);
    }else sprite.setTexture(texture);
}

void Button::setPosition(int xx, int yy){
    x=startX+xx;
    y=y+yy;
    sprite.setPosition(x,y);
}

void Button::draw(sf::RenderWindow *win){
    if(terminateWindow)win->close();
    win->draw(sprite);
}
