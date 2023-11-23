#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    
    objPos tempPos;
    tempPos.setObjPos((mainGameMechsRef->getBoardSizeX())/2,(mainGameMechsRef->getBoardSizeY())/2,42);
    // more actions to be included
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    //debug
/*
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
*/
}


Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;

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
    objPos currHead; 
    playerPosList->getHeadElement(currHead);

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

    objPos beta;
    mainGameMechsRef->getFoodPosition(beta);
    const objPos* ref = &beta;

    if(currHead.isPosEqual(ref))
    {
        playerPosList->insertHead(currHead);
        mainGameMechsRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore();
    }
    else
    {
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
    }    
}   

bool Player::checkSelfCollision()
{
    
}



