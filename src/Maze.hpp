#ifndef MAZE
#define MAZE

#include "Player.hpp"

const int MAX_SIZE=101;




class Maze{
private:
//the maze and the starting position
    Position startPos;
    Cell maze[MAX_SIZE][MAX_SIZE];
    int dimention;
    
//states
    States states;
//player
    Player player;
public:
//stuff needed to construct the maze
    void exit(int dim);
    int whereJump(int x, int y);
    void jump(int &x,int &y,int dir);
    void placeStuff(int dim);
    void breakWall(int dim);
//default custructor
    Maze(int dim=51);

//stuff needed for update
    void win();
    bool move(int dir);

//update function (basicaly loads a frame)
    void update(Inputs i);

//utilities for IHM
    States getState();
    Position getPlayerPos();
    Cell getCell(int x,int y);
};


#endif