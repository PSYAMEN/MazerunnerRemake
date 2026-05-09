#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/rlgl.h"
#include "IHM.hpp"
#include <time.h>

int main(){
    srand(time(NULL));
    //Maze maze(61);
    //maze.renderTUI();
    IHM test;
    test.app();
    return 0;
}