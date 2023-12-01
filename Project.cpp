#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000 // change to make fps higher/lower

GameMechs* myGM; 
// instantiate pointer to 'game mechanics' class - to be used together with ObjPos later in Draw() routine


Player* myPlayer; 
/* 
instantiate pointer to 'Player' class  
    - to be used together with ObjPosArrayList and the GameMech pointer above inside Draw() and RunLogic()
*/

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

// the program will only run while the exitflag is false (which is a method inside GameMechs class)
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

    // we need to instantiate some pointers and objects on the heap which will be used later in RunLogic() and Draw()

    myGM = new GameMechs(30,15); // initialize the gameboard, the args can be changed based on the user's desire.

    myPlayer = new Player(myGM); 
    // 'myPlayer' is a pointer which points to a 'Player' class in the heap, instantiated in global scope.
    // Instantiation of Player class needs to include a pointer to 'GameMech' class, 
    // which is 'myGM' (initialized in global scope above). This allows us to access stuff in 'GameMechs' class via 'Player'

    objPosArrayList* food = myPlayer->getPlayerPos(); 
    //we need to give 'food' the location of the player so that it knows where NOT to generate food.

    myGM->generateFood(food); //generate the food, which is a member function of 'GameMechs' class.
}

void GetInput(void)
{
   myGM->getInput(); //self explanatory, get the input, will be used in RunLogic() and Draw().
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir(); 
    myPlayer->movePlayer();

    myGM->clearInput(); //so that the previously help input in the buffer isn't used.
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos(); 
    // 'playerBody' of type array list is the snake body.
    // assign it the player's position for its head.

    objPos tempBody; // will be used when we start implementing getElement() down below. 

    objPos foodPos; // the getter function for the food position requires an arg of type objPos, hence we make a temp.
    myGM->getFoodPosition(foodPos);

    for(int i=0;i< myGM->getBoardSizeY();i++)  //this nested for loop loops through the rows/columns
    {
        for(int j=0;j<myGM->getBoardSizeX();j++)  
        {
            drawn = false; //only becomes true when the player's symbol is printed.

            for(int k = 0; k<playerBody->getSize();k++)
            {
                playerBody->getElement(tempBody, k); //get the element at index k from the list (snake body), puts it into 'tempBody'
                if(j==tempBody.x && i==tempBody.y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn=true; //drawn
                    break;
                }
            }

            if(drawn)continue; // makes sure that everything continues only when player symbol is drawn.

            if(i==0 || i==myGM->getBoardSizeY()-1 || j==0 || j==myGM->getBoardSizeX()-1) //border control
            {
                MacUILib_printf("%c", '#'); //border
            }

            else if(j==foodPos.x && i==foodPos.y) //food implementation
            {
                MacUILib_printf("%c", foodPos.symbol); //recall that the food was already generated in RunLogic()
            }
            else
            {
                MacUILib_printf("%c", 32); //white spaces , ascii type: 32
            
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d\n", myGM->getScore());
    MacUILib_printf("Press space bar to quit\n");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay, changeable
}

void CleanUp(void)
{
    MacUILib_clearScreen();    
    MacUILib_printf("GAME OVER! \nScore: %d\n", myGM->getScore());
    MacUILib_uninit();
    delete myGM; //we instantiated this on the heap.
    delete myPlayer; //we instantiated on the heap. 
}
