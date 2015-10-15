/*
 * Graphics.c
 *
 *  Created on: Sep 28, 2015
 *      Author: superman
 */
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "xio.h"
#include "time.h"
#include "unistd.h"
#include "globals.h"
#include "graphics.h"
#include "gameLogic.h"



//Returns the number of the current button that is being pressed
void handleButton(int currentButtonState)
{
    currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.
    
    if(currentButtonState == 8)
    {
        tankMove(0);
    }
    else if(currentButtonState == 2)
    {
        tankMove(1);
    }
    else if(currentButtonState == 1)
    {
        fireBullet();
    }
    
}




//This function is passed a point and it returns the alien number that is at that position or it returns -1 if there is no alien there. Note this only finds the position of the bitmap, not the alien within
int alienHitDetection(point_t position)
{
    int alienNumber = -1;
    int tempX = 0;
    int tempY = 0;
    
    point_t alienLocation = getAlienLocation();
    
    //Get the X position
    if(position.x > alienLocation.x && position.x < (alienLocation.x + (NUM_ALIEN_COL * ALIEN_WIDTH)))
    {
        int tempPosition = position.x - alienLocation.x;
        
        //Get the X position
        tempX = tempPosition / ALIEN_WIDTH;
        
        //Get the Y position
        if(position.y < (alienLocation.y + (ALIEN_HEIGHT * NUM_ALIEN_ROW +(ROW_SPACING * (NUM_ALIEN_ROW -1)))) && position.y > alienLocation.y)
        {
            tempPosition = position.y - alienLocation.y;
            
            //Account for the alien row spacing
            while(tempPosition > 0)
            {
                tempPosition -= ALIEN_HEIGHT + ROW_SPACING;
                if(tempPosition < 0)
                {
                    //if the point falls in the row spacing, it is not part of an alien so return -1
                    if((tempPosition += ROW_SPACING) > 0)
                    {
                        return -1;
                    }
                }
                tempY++;
            }
            tempY--;
            
            alienNumber = (tempY * NUM_ALIEN_COL) + tempX;
        }
    }
    return alienNumber;
}



//This function is passed an alien number and returns a point that the alien is at. Returns point x = -1, y = -1 if invalid alien
point_t alienPosition(int alienNumber)
{
    
}

void bulletHitDetection()
{
    point_t alienLocation = getAlienLocation();
    point_t tankBulletPos = getTankBulletPosition();
    
    
    
}













