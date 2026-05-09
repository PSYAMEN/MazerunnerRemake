#ifndef PLAYER_H
#define PLAYER_H


#include "Structs.hpp"

class Player{
private:
    Position position;
    int score;
    bool dead;
    int battery;
    int struggle;
public:
//default constructer
    Player(Position pos={2,2});
//update functions
    void move(int dir);
    void interaction(Cell &tile,int direction);
    bool isDead();
//Utilities for Maze
    Position getPosition();
//utilities for IHM
    int orientation;
};

#endif