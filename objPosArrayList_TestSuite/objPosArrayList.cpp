#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    sizeList=0;
    sizeArray=ARRAY_MAX_CAP;
    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(sizeList == sizeArray) //list is full
    {
        return;
    }
    for(int i = sizeList; i>0; i--) //starts at one space after tail
    {
        aList[i].setObjPos(aList[i-1]);
    }
    aList[0].setObjPos(thisPos);
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeList == sizeArray) //list is full
    {
        return;
    }
    aList[sizeList].setObjPos(thisPos);
    sizeList++;
}

void objPosArrayList::removeHead()
{
    for(int i = 0; i<sizeList; i++)
    {
        aList[i].setObjPos(aList[i+1]);
    }
    aList[sizeList-1].setObjPos(0,0,0);
    sizeList--;
}

void objPosArrayList::removeTail()
{
    aList[sizeList-1].setObjPos(0,0,0);
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}