#include "Player.hpp"

Player::Player(Position pos){
    position=pos;
    orientation = 0;
    score = 0;
    dead = false;
    battery = 1200;
    struggle=0;
}

/////////////////////////////////////////////////////

void Player::move(int dir){
    battery--;
    if(battery==0)dead=true;
    if(struggle!=0 && !dead)return;
    switch (dir){
        case 0:
            position.posY--;
            orientation = dir;
            break;
        case 1:
            position.posX++;
            orientation = dir;
            break;
        case 2:
            position.posY++;
            orientation = dir;
            break;
        case 3:
            position.posX--;
            orientation = dir;
            break;
    }
}

void Player::interaction(Cell &tile,int direction){
    if ((tile.mimic || tile.trap) && struggle == 0) { struggle = 30; }
    if (tile.chest) {   score += 500; tile.chest = false;  ; return; }
    if (tile.battery) { battery = 450; tile.battery = false; score += 100; return; }
    if (tile.mimic){
        if (direction != 5) { struggle-=3; }
        else { struggle++; }
        if (struggle <= 0) { tile.mimic = false; score += 200; struggle=0;}
        if (struggle >= 60)dead = true; return;
    }
    if (tile.trap)
    {
        if (direction != 5) { struggle-=3; }
        if (struggle <= 0) { tile.trap = false; score += 100; struggle=0;}
    }
}

bool Player::isDead(){return dead;}

///////////////////////////////////////////////////

Position Player::getPosition(){return position;}