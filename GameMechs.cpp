#include <iostream>
#include "GameMechs.h"
#include <cstdlib>
#include <ctime>
#include "objPos.h"
#include "MacUILib.h"

using namespace std;
GameMechs::GameMechs()
  :input(0), exitFlag(false), loseFlag(false), score(0)
{
    boardSizeX=30;
    boardSizeY=15;
    srand((unsigned int)time(NULL));
    foodPos.setObjPos(-1,-1,'F');
}
 
GameMechs::GameMechs(int boardX, int boardY)
  :input(0), exitFlag(false), loseFlag(false), score(0)
{
    boardSizeX=boardX;
    boardSizeY=boardY;
    srand((unsigned int)time(NULL));
    foodPos.setObjPos(-1,-1,'F');
}
 
// do you need a destructor?
//Added:
void GameMechs::generateFood(objPosArrayList* blockOff) //change
{
    int foodX, foodY, check=0;
    bool flag = false;
    cout<<"OUTSIDE WHILE LOOP" << endl;
    while(flag==false)
    {
        objPos temp0;
        foodX = rand() % (boardSizeX - 2) + 1;
        foodY = rand() % (boardSizeY - 2) + 1;

        for(int i = 0; i < blockOff->getSize()-1; i++)
        {
            blockOff->getElement(temp0, i);
            if(temp0.x != foodX || temp0.y != foodY)
            {
                check=0;
                continue;
            }
            else
            {
                check=1;
                break;
            }
        }
        cout<<"OUTSIDE IF LOOP, check = " << check << endl;

        if(check==0)
        {
            flag = true;
            break;
            cout<<"in break " << endl;
        }
            cout<<"end of while loop " << endl;
    }
    foodPos.setObjPos(foodX, foodY, 'o');
}

void GameMechs::getFoodPosition(objPos& returnPos)
{
    returnPos.setObjPos(foodPos);
}
 
bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}
 
char GameMechs::getInput()
{
    if(MacUILib_hasChar()) //check if an input is received
    {
        input=MacUILib_getChar(); 
    }
    return input;
}
 
int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}
 
int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}
 
 
void GameMechs::setExitTrue()
{
    exitFlag = true;
}
//Added:
bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}
 
void GameMechs::setLoseFlag()
{
    loseFlag = true;
    cout << "Game Over" << endl;
}
void GameMechs::setInput(char this_input)
{
    input = this_input;
}
 
void GameMechs::clearInput()
{
    input = 0;
}
//Added:
int GameMechs::getScore()
{
    return score;
}
 
void GameMechs::incrementScore()
{
    score++;
}