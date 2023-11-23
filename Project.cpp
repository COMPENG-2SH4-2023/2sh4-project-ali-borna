#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000
GameMechs* myGM;
Player* myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);
//void printMatrix(char input[][COLS], int rows); //temporary

int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

    return 0;
}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(30,15);
    myPlayer = new Player(myGM);

    objPosArrayList* food = myPlayer->getPlayerPos(); //test
    myGM->generateFood(food); //test
}

void GetInput(void)
{
   myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos tempPos2;
    myGM->getFoodPosition(tempPos2);

    for(int i=0;i< myGM->getBoardSizeY();i++) //row for loop. for each row, the elements (which are in columns) will be printed
    {
        for(int j=0;j<myGM->getBoardSizeX();j++) //column for loop. 
        {
            drawn = false;
            for(int k = 0; k<playerBody->getSize();k++)
            {
                playerBody->getElement(tempBody, k);
                if(j==tempBody.x && i==tempBody.y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn=true;
                    break;
                }
            }

            if(drawn)continue;

            if(i==0 || i==myGM->getBoardSizeY()-1 || j==0 || j==myGM->getBoardSizeX()-1)
            {
                MacUILib_printf("%c", '#');
            }

            else if(j==tempPos2.x && i==tempPos2.y)
            {
                MacUILib_printf("%c", tempPos2.symbol);
            }
            else
            {
                MacUILib_printf("%c", 32);
            
            }
        }
        MacUILib_printf("\n");
    }

    //MacUILib_printf("Score: %d, Player Pos: <%d, %d>\n", myGM->getScore(), tempPos.x, tempPos.y);

    //printMatrix(board,ROWS);  //temporary testing
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();    
    
    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
}
/*
void printMatrix(char input[][COLS], int rows) //temporary
{
    int i, j;

    for(i=0;i<rows;i++) //row for loop
    {
        for(j=0;j<COLS;j++) //column for loop. 
        {
            MacUILib_printf("%c", input[i][j]);
        }
        MacUILib_printf("\n");
    }
}
*/