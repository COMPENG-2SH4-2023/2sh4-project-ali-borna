#include "Player.h"
/*
Player::Player() //temporary
{
    playerPos.x = 7;
    playerPos.y = 15;
    playerPos.symbol = 42;
}
*/
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos((mainGameMechsRef->getBoardSizeX())/2,(mainGameMechsRef->getBoardSizeY())/2,42);
    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos);

    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    switch(mainGameMechsRef->getInput())
    {                      
        case ' ':  // exit
            mainGameMechsRef->setExitTrue();
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
    mainGameMechsRef->clearInput();
}
    // PPA3 input processing logic        

void Player::movePlayer()
{
    if(myDir==RIGHT)
    {
        playerPos.x++;
        if(playerPos.x == (mainGameMechsRef->getBoardSizeX())-1 || playerPos.x == 0 || playerPos.y == (mainGameMechsRef->getBoardSizeY())-1 || playerPos.y == 0) 
        {
            playerPos.x=1;
        }
    }
    else if(myDir==LEFT)
    {
        playerPos.x--;
        if(playerPos.x == (mainGameMechsRef->getBoardSizeX())-1 || playerPos.x == 0 || playerPos.y == (mainGameMechsRef->getBoardSizeY())-1 || playerPos.y == 0) 
        {
            playerPos.x=(mainGameMechsRef->getBoardSizeX())-2;
        }
    }
    else if(myDir==DOWN)
    {
        playerPos.y++;
        if(playerPos.x == (mainGameMechsRef->getBoardSizeX())-1 || playerPos.x == 0 || playerPos.y == (mainGameMechsRef->getBoardSizeY())-1 || playerPos.y == 0) 
        {
            playerPos.y=1;
        }
    }
    else if(myDir==UP)
    {
        playerPos.y--;
        if(playerPos.x == (mainGameMechsRef->getBoardSizeX())-1 || playerPos.x == 0 || playerPos.y == (mainGameMechsRef->getBoardSizeY())-1 || playerPos.y == 0) 
        {
            playerPos.y=(mainGameMechsRef->getBoardSizeY())-2;
        }
    }
}

