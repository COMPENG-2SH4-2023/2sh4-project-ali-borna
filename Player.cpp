#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP; // player starts in a stationary position of course.
    
    objPos tempPos; //since the 'objPos' setter takes in a type 'objPos' for arg, we need to instantiate temp objPos.

    tempPos.setObjPos((mainGameMechsRef->getBoardSizeX())/2,(mainGameMechsRef->getBoardSizeY())/2,42);
    // default settings, player must start in the middle of the board with symbol '*' denoted by ascii = 42.

    playerPosList = new objPosArrayList(); // will be destroyed by destructor.
    playerPosList->insertHead(tempPos); // instantiate the head at the default: middle of the board via tempPos

}

Player::~Player()
{
    delete playerPosList; //destroy what was initialized on the heap from the constructors.
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList; 
    // return the reference to the playerPos arrray list, this is a pointer to the heap from line 16 above.
}

void Player::updatePlayerDir()
{
    switch(mainGameMechsRef->getInput()) //we can access the GameMechs class via the pointer to check if theres an input.
    {                      
        case ' ':  // exit, we chose space to exit, can be changed to ESC or whatever...
            mainGameMechsRef->setExitTrue(); //end game.
            break;

        case 'W':
        case 'w':
            if(myDir==DOWN)
            {
                break;
            }
            myDir = UP;
            break;

        case 'A':
        case 'a':
            if(myDir==RIGHT)
            {
                break;
            }
            myDir = LEFT;
            break;

        case 'S':
        case 's':
            if(myDir==UP)
            {
                break;
            }
            myDir = DOWN;
            break;

        case 'D':
        case 'd':
            if(myDir==LEFT)
            {
                break;
            }
            myDir = RIGHT;
            break;

        default:
            break;
    }
    mainGameMechsRef->clearInput(); //remove old inputs from buffer.
}

void Player::movePlayer()
{

    objPos currHead;   
    playerPosList->getHeadElement(currHead); // lets keep track of the current head position using the objPos class.

    // --------------- START OF BODY MOVING ROUTINE (from PPA3) -------------

    if(myDir==RIGHT)
    {
        currHead.x++;
        if(currHead.x == (mainGameMechsRef->getBoardSizeX())-1 || currHead.x == 0 || currHead.y == (mainGameMechsRef->getBoardSizeY())-1 || currHead.y == 0) 
        {
            currHead.x=1;
        }
    }
    else if(myDir==LEFT)
    {
        currHead.x--;
        if(currHead.x == (mainGameMechsRef->getBoardSizeX())-1 || currHead.x == 0 || currHead.y == (mainGameMechsRef->getBoardSizeY())-1 || currHead.y == 0) 
        {
            currHead.x=(mainGameMechsRef->getBoardSizeX())-2;
        }
    }
    else if(myDir==DOWN)
    {
        currHead.y++;
        if(currHead.x == (mainGameMechsRef->getBoardSizeX())-1 || currHead.x == 0 || currHead.y == (mainGameMechsRef->getBoardSizeY())-1 || currHead.y == 0) 
        {
            currHead.y=1;
        }
    }
    else if(myDir==UP)
    {
        currHead.y--;
        if(currHead.x == (mainGameMechsRef->getBoardSizeX())-1 || currHead.x == 0 || currHead.y == (mainGameMechsRef->getBoardSizeY())-1 || currHead.y == 0) 
        {
            currHead.y=(mainGameMechsRef->getBoardSizeY())-2;
        }
    }

    // --------------- END OF BODY MOVING ROUTINE -------------

    // ----------- food consumption check: -------------
    objPos foodP; 
    mainGameMechsRef->getFoodPosition(foodP); //put the co-ordinated of the food into 'foodP' of type objPos.
    const objPos* ref = &foodP; //needed for 'isEqual()' member function to evaluate whether or not collision has occured.

    if(currHead.isPosEqual(ref)) // if the head crashes into the food's co-ordinates, pointed by 'ref'
    {
        playerPosList->insertHead(currHead);
        mainGameMechsRef->generateFood(playerPosList); //generate new food
        mainGameMechsRef->incrementScore(); //gain score
    }
    else
    {
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
    }


    // ------- self collision check ------------
    if(checkSelfCollision(currHead))
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }    
}   

bool Player::checkSelfCollision(objPos &curr)
{
    objPos temp2; //temporary, needed for element getter function below in line 164

    for(int i = playerPosList->getSize(); i > 0; i--) 
    {
        playerPosList->getElement(temp2, i); //evaluate each element of the snake body by getter function

        if(temp2.x == curr.x  && temp2.y == curr.y) //collision has occured at current head and snake's body.
        {
            return true;
        }
        else
        {
            continue;
        }
    }
    return false;
}



