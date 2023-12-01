#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(); //default, unneeded. 
        Player(GameMechs* thisGMRef);
        ~Player(); //destructor 

        objPosArrayList* getPlayerPos(); // returns pointer to array list
        void updatePlayerDir();
        void movePlayer();
        bool checkSelfCollision(objPos &curr); //takes current head position via reference. evaluates collision.

        //don't need, for now, have been implemented inside member function 'movePlayer()'
        //void incPlayerLength(); 
        void checkFoodConsumption(objPos &curr);

    private:
        objPosArrayList* playerPosList;   // Snake body       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif