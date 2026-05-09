#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/rlgl.h"
#include "Maze.hpp"

int main(){
    Maze maze(61);
    maze.renderTUI();
}