#include "Player.hpp"

Player::Player(Position pos){
    position=pos;
    orientation = 0;
    score = 0;
    dead = false;
    battery = 450;
}

/////////////////////////////////////////////////////

void Player::move(int dir){
    switch (dir){
        case 0:
            position.posY++;
            orientation = dir;
            break;
        case 1:
            position.posX++;
            orientation = dir;
            break;
        case 2:
            position.posY--;
            orientation = dir;
            break;
        case 3:
            position.posY--;
            orientation = dir;
            break;
    }
    battery--;
}

void Player::interaction(Cell &tile,int direction){
    if (tile.chest) {   score += 500; tile.chest = false;  ; return; }
    if (tile.battery) { battery = 450; tile.battery = false; score += 100; return; }
    if (tile.mimic)
    {
        if (direction != 4) { struggle--; }
        else { struggle++; }
        if (struggle == 0) { tile.mimic = false; score += 200; }
        if (struggle == 30)dead = true; return;
    }
    if (tile.trap)
    {
        if (direction != 4) { struggle--; }
        if (struggle == 0) { tile.trap = false; score += 100; }
    }
}

bool Player::isDead(){return dead;}

///////////////////////////////////////////////////

Position Player::getPosition(){return position;}