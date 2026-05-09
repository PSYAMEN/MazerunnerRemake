#include "Maze.hpp"
#include <math.h>
#include <iostream>

void Maze::exit(int dim){
    int c1 = rand() % 4;
    int c2 = ((rand() % (dim - 4)) & ~1) + 2;
    switch (c1)
    {
    case 0:
        maze[c2][1].wall = 0;
        break;
    case 1:
        maze[dim - 2][c2].wall = 0;
        break;
    case 2:
        maze[c2][dim - 2].wall = 0;
        break;
    case 3:
        maze[1][c2].wall = 0;
        break;
    }
}

int Maze::whereJump(int x,int y){
    bool WJ[4] = { false };
    int HowManyJump = 0;
    maze[x][y].visited = true;
    if (!maze[x][y + 2].visited) { HowManyJump++; WJ[0] = true; }
    if (!maze[x - 2][y].visited) { HowManyJump++; WJ[3] = true; }          if (!maze[x + 2][y].visited) { HowManyJump++; WJ[1] = true; }
    if (!maze[x][y - 2].visited) { HowManyJump++; WJ[2] = true; }
    if (HowManyJump == 0) return -1;
    while (true) { int dir = rand() % 4; if (WJ[dir]) return dir; }
}

void Maze::jump(int &x,int &y,int dir){
    switch (dir)
    {
    case 0:
        maze[x][y + 1].wall = 0;
        y += 2;
        break;
    case 1:
        maze[x + 1][y].wall = 0;
        x += 2;
        break;
    case 2:
        maze[x][y - 1].wall = 0;
        y -= 2;
        break;
    case 3:
        maze[x - 1][y].wall = 0;
        x -= 2;
        break;
    default:
        break;
    }
}

void Maze::placeStuff(int dim){
    for (int i = 0; i < (dim- 2) / 5 + rand() % 3; i++)
    {
        int x = ((rand() % (dim - 4)) & ~1) + 2;
        int y = ((rand() % (dim - 4)) & ~1) + 2;
        int r = 0;
        while (!maze[x][y].open)
        {
            r = rand() % 2;
            if (r == 0) { maze[x][y].chest = true; }
            else { maze[x][y].mimic = true; }
            maze[x][y].open = true;
            x = ((rand() % (dim - 4)) & ~1) + 2;
            y = ((rand() % (dim - 4)) & ~1) + 2;
        }
    }
    for (int i = 0; i < (dim - 2) / 5 - rand() % 3; i++)
    {
        int x = ((rand() % (dim - 4)) & ~1) + 2;
        int y = ((rand() % (dim - 4)) & ~1) + 2;
        while (!maze[x][y].open)
        {
            maze[x][y].trap = true;
            maze[x][y].open = true;
            x = ((rand() % (dim - 4)) & ~1) + 2;
            y = ((rand() % (dim - 4)) & ~1) + 2;
        }
    }
    for (int i = 0; i < (dim - 2) / 10 + rand() % 2; i++)
    {
        int x = ((rand() % (dim - 4)) & ~1) + 2;
        int y = ((rand() % (dim - 4)) & ~1) + 2;
        while (!maze[x][y].open)
        {
            maze[x][y].battery = true;
            maze[x][y].open = true;
            x = ((rand() % (dim - 4)) & ~1) + 2;
            y = ((rand() % (dim - 4)) & ~1) + 2;
        }
    }
}

void Maze::breakWall(int dim){
    for (int i = 0; i < dim * dim / 20; i++)
    {
        int dir = rand() % 4;
        int c1 = ((rand() % (dim - 4)) & ~1) + 2;
        int c2 = ((rand() % (dim - 4)) & ~1) + 2;
        jump( c1, c2, dir);
    }
}

Maze::Maze(int dim){
    dimention=dim;
    for (int i = 1; i < dim; i += 2)
    {
        for (int j = 1; j < dim; j++)
        {
            maze[i][j].wall = maze[j][i].wall = 1;
        }
    }
    for (int i = 0; i < dim; i++)
    {
        maze[0][i].visited = maze[i][dim - 1].visited = maze[dim - 1][i].visited = maze[i][0].visited = 1;
    }
    int stage = 0;
    int stack[MAX_SIZE * MAX_SIZE][2];
    stack[0][0] = ((rand() % (dim - 4)) & ~1) + 2;
    stack[0][1] = ((rand() % (dim - 4)) & ~1) + 2;
    do
    {
        int x = stack[stage][0];
        int y = stack[stage][1];
        int dir = whereJump(x, y);
        if (dir != -1)
        {
            jump(x, y, dir);
            stage++;
            stack[stage][0] = x;
            stack[stage][1] = y;
        }
        else { stage--; }
    } while (stage != 0);
    startPos.posX = ((rand() % (dim - 4)) & ~1) + 2;
    startPos.posY = ((rand() % (dim - 4)) & ~1) + 2;
    maze[startPos.posX][startPos.posY].open = true;
    placeStuff(dim);
    breakWall(dim);
    for (int i = 0; i < dim / 10; i++)
    {
        exit(dim);
    }
}



//////////////////////////////////////////////////////////////////////////////////

void Maze::win(){
    if(player.getPosition().posX==dimention-1 || player.getPosition().posX==0 || player.getPosition().posY==dimention-1 || player.getPosition().posY==0)states.won=true;
}

bool Maze::move(int dir){
    switch (dir){
        case 0:
            if (!maze[player.getPosition().posX][player.getPosition().posY + 1].wall) player.move(dir);
            break;
        case 1:
            if (!maze[player.getPosition().posX + 1][player.getPosition().posY].wall) player.move(dir);
            break;
        case 2:
            if (!maze[player.getPosition().posX][player.getPosition().posY - 1].wall) player.move(dir);
            break;
        case 3:
            if (!maze[player.getPosition().posX - 1][player.getPosition().posY].wall) player.move(dir);
            break;
        default: return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////

void Maze::update(Inputs i){
    if (player.isDead()){
        states.lost=true;
    }
    if(!states.lost || !states.won || !states.paused){
        move(i.direction);
        player.interaction(maze[player.getPosition().posX][player.getPosition().posY],i.direction);
        win();
    }
}

////////////////////////////////////////////////////////////////////////////////////

States Maze::getState(){return states;}
Position Maze::getPlayerPos(){return player.getPosition();}
Cell Maze::getCell(int x,int y){return maze[x][y];}\

//////////////////////////////////////////////////////////////////////////////////////

void Maze::renderTUI(){
    for(int i=0;i<dimention;i++){
        for(int j=0;j<dimention;j++){
            if(maze[i][j].wall){
                std::cout<<" X";
            }
            else if(maze[i][j].mimic){

                std::cout<<" M";
            }
            else if(maze[i][j].battery){

                std::cout<<" B";
            }
            else if(maze[i][j].trap){

                std::cout<<" T";
            }
            else if(maze[i][j].chest){

                std::cout<<" C";
            }
            else {

                std::cout<<"  ";
            }
        }
        std::cout<<std::endl;
    }
}