#ifndef GAMEMECHS_H
#define GAMEMECHS_H
 
#include <cstdlib>
#include <time.h>
 
#include "objPos.h"
#include "objPosArrayList.h"
 
using namespace std;
 
 
class GameMechs
{
    // Construct the remaining declaration from the project manual.
 
    // Only some sample members are included here
 
    // You will include more data members and member functions to complete your design.
 
    private:
        char input;
        bool exitFlag;
    //Added:
        bool loseFlag;
        int score;
        int boardSizeX;
        int boardSizeY;
    //Added:
        objPos foodPos;
 
    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
       
        bool getExitFlagStatus();
        void setExitTrue();
    //Added:
        bool getLoseFlagStatus();
        void setLoseFlag();
 
        char getInput();
        void setInput(char this_input);
        void clearInput();
 
        int getBoardSizeX();
        int getBoardSizeY();
    //Added:
        int getScore();
        void incrementScore();
        void generateFood(objPos blockOff);
        void getFoodPosition(objPos& returnPos);
        bool isPositionFree(int x, int y);
 
};
 
#endif