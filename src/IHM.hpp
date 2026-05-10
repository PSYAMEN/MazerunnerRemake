#ifndef IHM_H
#define IHM_H

#include "Maze.hpp"
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/rlgl.h"
#define FLASHLIGHTYELLOW (Color){153,153,00,75}

struct Keys{
    int up=KEY_UP;
    int down=KEY_DOWN;
    int left=KEY_LEFT;
    int right=KEY_RIGHT;
    int select=KEY_ENTER;
    int pause=KEY_ESCAPE;
};

class IHM{
private:
    Inputs inputs;
    Keys keys;
//states
    int selector;
    bool inMenu;
    bool inGame;
    bool inHandbook;
    bool inCredits;
    bool inSettings;
//game
    Maze game;
//textures
    Texture2D playerTextures[4];
    Texture2D chest;
    Texture2D mimic;
    Texture2D trap;
    Texture2D battery;
public:
//default constructor
    IHM();
//utilities to communicxate with the hooman
    void getInputs();
//update function
    void gameLoop();
//render functions
    void renderFlashlightTwT();
    void renderMainMenu();
    void renderSettings();
    void renderHandbook();
    void renderCredits();
    void renderDiffcultySelect();
    void renderGame();
    void renderPauseMenu();
    void renderWinMenu();
    void renderLoseMenu();
//aplication
    void app();
};

#endif