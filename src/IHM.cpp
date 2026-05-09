#include "IHM.hpp"
//////
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/rlgl.h"

#include <iostream>

const int PIXEL=1050;
const int LPIXEL=150;
//default constructor
IHM::IHM(){
    selector=0;
    inMenu=true;
    inGame=false;
    inHandbook=false;
    inputs.direction=0;
    inputs.select=false;
    inputs.pause=false;
    //Texture loading
    InitWindow(1050,1050,"Mazerunner");
    
    Image textureTemp;
    textureTemp=LoadImage("./assets/Sprites/Player.png");
    ImageResize(&textureTemp,150,150);
    playerTextures[0]=LoadTextureFromImage(textureTemp);
    ImageRotate(&textureTemp,90);
    playerTextures[1]=LoadTextureFromImage(textureTemp);
    ImageRotate(&textureTemp,90);
    playerTextures[2]=LoadTextureFromImage(textureTemp);
    ImageRotate(&textureTemp,90);
    playerTextures[3]=LoadTextureFromImage(textureTemp);

    textureTemp=LoadImage("./assets/Sprites/Battery.png");
    ImageResize(&textureTemp,150,150);
    battery=LoadTextureFromImage(textureTemp);

    textureTemp=LoadImage("./assets/Sprites/Chest.png");
    ImageResize(&textureTemp,150,150);
    chest=LoadTextureFromImage(textureTemp);

    textureTemp=LoadImage("./assets/Sprites/TrappedChest.png");
    ImageResize(&textureTemp,150,150);
    mimic=LoadTextureFromImage(textureTemp);

    textureTemp=LoadImage("./assets/Sprites/RustyBearTrap.png");
    ImageResize(&textureTemp,150,150);
    trap=LoadTextureFromImage(textureTemp);
}
//functions for update
void IHM::getInputs(){
    inputs.direction=5;
    inputs.select=false;
    inputs.pause=false;
    if(IsKeyPressed(keys.select))inputs.select=true;
    if(IsKeyPressed(keys.pause))inputs.pause=true;
    if(IsKeyPressed(keys.up)){
        inputs.direction=0;
        return;
    }
    if(IsKeyPressed(keys.right)){
        inputs.direction=1;
        return;
    }
    if(IsKeyPressed(keys.down)){
        inputs.direction=2;
        return;
    }
    if(IsKeyPressed(keys.left)){
        inputs.direction=3;
        return;
    }
}
//update function
void IHM::gameLoop(){
    game=Maze(51);
    States gameStates=game.getState();
    while(!WindowShouldClose() && inGame){
        getInputs();
        gameStates=game.getState();
        //input handeling

        if(inputs.pause && !gameStates.paused){
            game.pauseGame();
        }
        //game handeling
        if(!gameStates.paused && !gameStates.won && !gameStates.lost){
            game.update(inputs);
            renderGame();
        }
        else if(gameStates.paused){
            renderPauseMenu();
        }
        else if(gameStates.won){
            renderWinMenu();
        }
        else if(gameStates.lost){
            renderLoseMenu();
        }
    }
}

//render functions
void IHM::renderMainMenu(){
    BeginDrawing();
        ClearBackground(BLACK);
        if (selector == 0) {
            for (int i = 0.4 * LPIXEL; i < 6.6 * LPIXEL; i+=2){
                DrawLine(PIXEL / 2, PIXEL / 2 - 50, i, 0, FLASHLIGHTYELLOW);
            }
            DrawText("Mazerunner", 220,20,100 , {153,153,00,150});
        }
        if (selector == 1) {
            for (int i = 2 * LPIXEL + 2 * LPIXEL / 3 ; i < 5 * LPIXEL - 2 * LPIXEL / 3; i+=2){
                DrawLine(PIXEL, i, PIXEL / 2 + 5, PIXEL / 2, FLASHLIGHTYELLOW);
            }
            DrawText("Exit", 830,475,100 , {153,153,00,150});
        }
        if (selector == 2) {
            for (int i = 0.4 * LPIXEL; i < 6.6 * LPIXEL; i+=2){
                DrawLine(PIXEL / 2, PIXEL / 2 + 50, i, 7 * LPIXEL - 1,FLASHLIGHTYELLOW);
            }
            DrawText("Handbook", 285,930,100 , {153,153,00,150});
        }
        if (selector == 3){
            for (int i = 2 * LPIXEL + 2 * LPIXEL / 3 ; i < 5 * LPIXEL - 2 * LPIXEL / 3; i+=2){
                DrawLine(0, i, PIXEL / 2 - 5, PIXEL / 2, FLASHLIGHTYELLOW);
            }
            DrawText("Start", 20,475,100 , {153,153,00,150});
        }
        DrawTexture(playerTextures[selector],450,450,WHITE);
        if(inputs.select){
            inMenu=false;
            switch(selector){
                case 0:
                    selector=0;
                    inCredits=true;
                    break;
                case 1:
                    CloseWindow();
                    break;
                case 2:
                    selector=0;
                    inHandbook=true;
                    break;
                case 3:
                    selector=0;
                    inGame=true;
                    break;
            }
        }
    EndDrawing();
    //selector=0;
}

void IHM::renderSettings(){

}
void IHM::renderHandbook(){

}
void IHM::renderCredits(){}
void IHM::renderDiffcultySelect(){}
void IHM::renderPauseMenu(){inGame=false;inMenu=true;}
void IHM::renderLoseMenu(){inGame=false;inMenu=true;}
void IHM::renderWinMenu(){inGame=false;inMenu=true;}
void IHM:: renderGame(){
    Position playerPos =game.getPlayerPos();
    BeginDrawing();
    Cell save;
    for (int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            save=game.getCell(playerPos.posX-3+i,playerPos.posY-3+j);
            if(save.wall){
                DrawRectangle(i*LPIXEL,j*LPIXEL,150,150,BLACK);
            }
            else {
                DrawRectangle(i*LPIXEL,j*LPIXEL,150,150,WHITE);
                if(save.battery)DrawTexture(battery,i*LPIXEL,j*LPIXEL,WHITE);
                if(save.trap)DrawTexture(trap,i*LPIXEL,j*LPIXEL,WHITE);
                if(save.chest)DrawTexture(chest,i*LPIXEL,j*LPIXEL,WHITE);
                if(save.mimic)DrawTexture(mimic,i*LPIXEL,j*LPIXEL,WHITE);
            }

        }
    }
    DrawTexture(playerTextures[game.getPlayerOrientation()],450,450,WHITE);
    EndDrawing();
}
//aplication
void IHM::app(){
    SetTargetFPS(30);
    while(!WindowShouldClose()){
        getInputs();
        if(inputs.direction!=5)selector=inputs.direction;
        if(inMenu)renderMainMenu();
        if(inHandbook)renderHandbook();
        if(inGame)gameLoop();
        if(inCredits)renderCredits();
    }
}

