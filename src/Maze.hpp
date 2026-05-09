#ifndef MAZE
#define MAZE

#include "Player.hpp"

const int MAX_SIZE=101;

struct Cell{
    bool wall = false;
    bool visited = false;
    bool trap = false;
    bool mimic = false;
    bool chest = false;
    bool boost = false;
    bool lightup = false;
    bool open = false;
};

class Maze{
private:
    int startPos[2];
    Cell maze[MAX_SIZE][MAX_SIZE];

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
};


#endif