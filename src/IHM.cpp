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

    std::cout<<"Difficulty size:"<<MeasureText("Difficulty",100);
    std::cout<<"\nWin size:"<<MeasureText("Win",100);
    std::cout<<"\nNew Game size:"<<MeasureText("New Game",75);
    std::cout<<"\nExit size:"<<MeasureText("Exit",75);
    std::cout<<"\nContinue size:"<<MeasureText("Continue",75);
    
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
    getInputs();
    selector=31;
    while(!WindowShouldClose() && !inputs.select){
        getInputs();
        renderDiffcultySelect();
    }
    game=Maze(selector);
    States gameStates=game.getState();
    while(!WindowShouldClose() && inGame){
        getInputs();
        gameStates=game.getState();
        //input handeling

        if(inputs.pause && !gameStates.paused){
            game.pauseGame();
        }
        //game handeling
        if(!gameStates.paused && !gameStates.won && !gameStates.lost && !inSettings){
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
        }else if(inSettings){
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
        
    EndDrawing();
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
    //selector=0;
}

void IHM::renderSettings(){

}
void IHM::renderHandbook(){

}
void IHM::renderCredits(){}

void IHM::renderDiffcultySelect(){
    BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Difficulty", 295,50,100 , {153,153,00,150});
        DrawTriangle({525,450},{500,475},{550,475},{153,153,0,150});
        DrawTriangle({500,575},{525,600},{550,575},{153,153,0,150});
        DrawText(std::to_string(selector).c_str(),(1050-MeasureText(std::to_string(selector).c_str(),100))/2,480,100,{153,153,00,150});
    EndDrawing();
    if(inputs.direction==0 && selector <101)selector+=2;
    if(inputs.direction==2 && selector >11)selector-=2;
}
void IHM::renderPauseMenu(){
    //4 options : continue, main menu, Exit, settings
    if(inputs.direction!=5)selector=inputs.direction;
    //HANDELING INPUTS
    BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Paused", 345,50,100 , {153,153,00,150});
        DrawText("Paused", 345,50,100 , {153,153,00,200});
        DrawText("Continue",365,500,75,{153,153,00,150});
        DrawRectangleLines(325,475,400,125,{153,153,00,150});
        DrawRectangleLines(326,476,398,123,{153,153,00,150});
        DrawRectangleLines(327,477,396,121,{153,153,00,150});

        DrawText("Settings",654,700,75,{153,153,00,150});
        DrawRectangleLines(610,675,400,125,{153,153,00,150});
        DrawRectangleLines(611,676,398,123,{153,153,00,150});
        DrawRectangleLines(612,677,396,121,{153,153,00,150});

        DrawText("Main Menu",51,700,75,{153,153,00,150});
        DrawRectangleLines(40,675,400,125,{153,153,00,150});
        DrawRectangleLines(41,676,398,123,{153,153,00,150});
        DrawRectangleLines(42,677,396,121,{153,153,00,150});

        DrawText("Exit",454,900,75,{153,153,00,150});
        DrawRectangleLines(325,875,400,125,{153,153,00,150});
        DrawRectangleLines(326,876,398,123,{153,153,00,150});
        DrawRectangleLines(327,877,396,121,{153,153,00,150});

        if(selector==0){
            DrawText("Continue",365,500,75,{153,153,00,200});
            DrawRectangleLines(325,475,400,125,{153,153,00,200});
            DrawRectangleLines(326,476,398,123,{153,153,00,200});
            DrawRectangleLines(327,477,396,121,{153,153,00,200});
        }
        if(selector==1){
            DrawText("Settings",654,700,75,{153,153,0,200});
            DrawRectangleLines(610,675,400,125,{153,153,00,200});
            DrawRectangleLines(611,676,398,123,{153,153,00,200});
            DrawRectangleLines(612,677,396,121,{153,153,00,200});
        }
        if(selector==2){
            DrawText("Exit",454,900,75,{153,153,00,200});
            DrawRectangleLines(325,875,400,125,{153,153,00,200});
            DrawRectangleLines(326,876,398,123,{153,153,00,200});
            DrawRectangleLines(327,877,396,121,{153,153,00,200});
        }
        if(selector==3){
            DrawText("Main Menu",51,700,75,{153,153,00,200});
            DrawRectangleLines(40,675,400,125,{153,153,00,200});
            DrawRectangleLines(41,676,398,123,{153,153,00,200});
            DrawRectangleLines(42,677,396,121,{153,153,00,200});
        }
    EndDrawing();
    if(inputs.select){
        switch(selector){
            case 0:
                game.unpauseGame();
                break;
            case 1:
                inSettings=true;
                game.unpauseGame();
                break;
            case 2:
                CloseWindow();
                break;
            case 3: 
                inGame=false;
                inMenu=true;
                break;
        }
    }
}
void IHM::renderLoseMenu(){
    if(inputs.direction!=5)selector=inputs.direction;
    //HANDELING INPUTS
    BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Lost", 415,50,100 , {153,153,00,150});
        DrawText("Lost", 415,50,100 , {153,153,00,200});
        DrawText("New Game",350,500,75,{153,153,00,200});
        DrawRectangleLines(325,475,400,125,{153,153,00,150});
        DrawRectangleLines(326,476,398,123,{153,153,00,150});
        DrawRectangleLines(327,477,396,121,{153,153,00,150});

        DrawText("Settings",654,700,75,{153,153,00,150});
        DrawRectangleLines(610,675,400,125,{153,153,00,150});
        DrawRectangleLines(611,676,398,123,{153,153,00,150});
        DrawRectangleLines(612,677,396,121,{153,153,00,150});

        DrawText("Main Menu",51,700,75,{153,153,00,150});
        DrawRectangleLines(40,675,400,125,{153,153,00,150});
        DrawRectangleLines(41,676,398,123,{153,153,00,150});
        DrawRectangleLines(42,677,396,121,{153,153,00,150});

        DrawText("Exit",454,900,75,{153,153,00,150});
        DrawRectangleLines(325,875,400,125,{153,153,00,150});
        DrawRectangleLines(326,876,398,123,{153,153,00,150});
        DrawRectangleLines(327,877,396,121,{153,153,00,150});

        if(selector==0){
            DrawText("New Game",350,500,75,{153,153,00,200});
            DrawRectangleLines(325,475,400,125,{153,153,00,200});
            DrawRectangleLines(326,476,398,123,{153,153,00,200});
            DrawRectangleLines(327,477,396,121,{153,153,00,200});
        }
        if(selector==1){
            DrawText("Settings",654,700,75,{153,153,0,200});
            DrawRectangleLines(610,675,400,125,{153,153,00,200});
            DrawRectangleLines(611,676,398,123,{153,153,00,200});
            DrawRectangleLines(612,677,396,121,{153,153,00,200});
        }
        if(selector==2){
            DrawText("Exit",454,900,75,{153,153,00,200});
            DrawRectangleLines(325,875,400,125,{153,153,00,200});
            DrawRectangleLines(326,876,398,123,{153,153,00,200});
            DrawRectangleLines(327,877,396,121,{153,153,00,200});
        }
        if(selector==3){
            DrawText("Main Menu",51,700,75,{153,153,00,200});
            DrawRectangleLines(40,675,400,125,{153,153,00,200});
            DrawRectangleLines(41,676,398,123,{153,153,00,200});
            DrawRectangleLines(42,677,396,121,{153,153,00,200});
        }
    EndDrawing();
    if(inputs.select){
        switch(selector){
            case 0:
                gameLoop();
                break;
            case 1:
                inSettings=true;
                game.unpauseGame();
                break;
            case 2:
                CloseWindow();
                break;
            case 3: 
                inGame=false;
                inMenu=true;
                break;
        }
    }
}
void IHM::renderWinMenu(){
    if(inputs.direction!=5)selector=inputs.direction;
    //HANDELING INPUTS
    BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Win", 450,50,100 , {153,153,00,150});
        DrawText("Win", 450,50,100 , {153,153,00,200});
        DrawText("New Game",350,500,75,{153,153,00,150});
        DrawRectangleLines(325,475,400,125,{153,153,00,150});
        DrawRectangleLines(326,476,398,123,{153,153,00,150});
        DrawRectangleLines(327,477,396,121,{153,153,00,150});

        DrawText("Settings",654,700,75,{153,153,00,150});
        DrawRectangleLines(610,675,400,125,{153,153,00,150});
        DrawRectangleLines(611,676,398,123,{153,153,00,150});
        DrawRectangleLines(612,677,396,121,{153,153,00,150});

        DrawText("Main Menu",51,700,75,{153,153,00,150});
        DrawRectangleLines(40,675,400,125,{153,153,00,150});
        DrawRectangleLines(41,676,398,123,{153,153,00,150});
        DrawRectangleLines(42,677,396,121,{153,153,00,150});

        DrawText("Exit",454,900,75,{153,153,00,150});
        DrawRectangleLines(325,875,400,125,{153,153,00,150});
        DrawRectangleLines(326,876,398,123,{153,153,00,150});
        DrawRectangleLines(327,877,396,121,{153,153,00,150});

        if(selector==0){
            DrawText("New Game",350,500,75,{153,153,00,200});
            DrawRectangleLines(325,475,400,125,{153,153,00,200});
            DrawRectangleLines(326,476,398,123,{153,153,00,200});
            DrawRectangleLines(327,477,396,121,{153,153,00,200});
        }
        if(selector==1){
            DrawText("Settings",654,700,75,{153,153,0,200});
            DrawRectangleLines(610,675,400,125,{153,153,00,200});
            DrawRectangleLines(611,676,398,123,{153,153,00,200});
            DrawRectangleLines(612,677,396,121,{153,153,00,200});
        }
        if(selector==2){
            DrawText("Exit",454,900,75,{153,153,00,200});
            DrawRectangleLines(325,875,400,125,{153,153,00,200});
            DrawRectangleLines(326,876,398,123,{153,153,00,200});
            DrawRectangleLines(327,877,396,121,{153,153,00,200});
        }
        if(selector==3){
            DrawText("Main Menu",51,700,75,{153,153,00,200});
            DrawRectangleLines(40,675,400,125,{153,153,00,200});
            DrawRectangleLines(41,676,398,123,{153,153,00,200});
            DrawRectangleLines(42,677,396,121,{153,153,00,200});
        }
    EndDrawing();
    if(inputs.select){
        switch(selector){
            case 0:
                gameLoop();
                break;
            case 1:
                inSettings=true;
                game.unpauseGame();
                break;
            case 2:
                CloseWindow();
                break;
            case 3: 
                inGame=false;
                inMenu=true;
                break;
        }
    }
}
void IHM::renderFlashlightTwT(){
    Cell save;
    Position playerPos = game.getPlayerPos();
    DrawCircleGradient(525,525,400,{0,0,0,0},{0,0,0,255});
    //std::cout<<"fuck you i will deal with it its just painfull to do\n";
    for (int i=1;i<6;i++){
        for(int j=1;j<6;j++){
            save=game.getCell(playerPos.posX-3+i,playerPos.posY-3+j);
            if(save.wall){

            }

        }
    }
}
void IHM:: renderGame(){
    Position playerPos =game.getPlayerPos();
    Cell save;
    BeginDrawing();
        ClearBackground(BLACK);
        for (int i=1;i<6;i++){
            for(int j=1;j<6;j++){
                save=game.getCell(playerPos.posX-3+i,playerPos.posY-3+j);
                if(save.wall){
                    DrawRectangle(i*LPIXEL,j*LPIXEL,150,150,BLACK);
                }
                else{    
                    DrawRectangle(i*LPIXEL,j*LPIXEL,150,150,{155,155,0,255});
                    if(save.battery)DrawTexture(battery,i*LPIXEL,j*LPIXEL,WHITE);
                    if(save.trap)DrawTexture(trap,i*LPIXEL,j*LPIXEL,WHITE);
                    if(save.chest)DrawTexture(chest,i*LPIXEL,j*LPIXEL,WHITE);
                    if(save.mimic)DrawTexture(mimic,i*LPIXEL,j*LPIXEL,WHITE);
                }

            }
        }
        renderFlashlightTwT();
        DrawTexture(playerTextures[game.getPlayerOrientation()],450,450,WHITE);
    EndDrawing();
}
//aplication
void IHM::app(){
    SetTargetFPS(30);
    SetExitKey(-1);
    while(!WindowShouldClose()){
        getInputs();
        if(inputs.direction!=5)selector=inputs.direction;
        if(inMenu)renderMainMenu();
        if(inHandbook)renderHandbook();
        if(inGame)gameLoop();
        if(inCredits)renderCredits();
    }
}

