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
#include "xgpio.h"


XGpio gpPB;
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
    
    if(alienNumber >= 0 && getAlienAlive(alienNumber))
    {
        return alienNumber;
    }
    else
    {
        return -1;
    }
}



//This function is passed a bullet position and returns an integer that corresponds to the bunker that got hit and the x coordinate on the bunker that was hit.  Use / 4 and % 4 on the return value to get the bunker ID and x coordinate
int bunkerHitDetection(point_t position)
{
    int bunkerHitValue = -1;
    int bunkerID = 0;
    
    if(position.y > BUNKER_Y_VALUE && position.y < (BUNKER_Y_VALUE + BUNKER_HEIGHT))
    {
        
        if(position.x > BUNKER_1_XPOSITION && position.x < BUNKER_1_XPOSITION + BUNKER_WIDTH)
        {
            bunkerID = 0;
        }
        else if(position.x > BUNKER_2_XPOSITION && position.x < BUNKER_2_XPOSITION + BUNKER_WIDTH)
        {
            bunkerID = 1;
        }
        else if(position.x > BUNKER_3_XPOSITION && position.x < BUNKER_3_XPOSITION + BUNKER_WIDTH)
        {
            bunkerID = 2;
        }
        else if(position.x > BUNKER_4_XPOSITION && position.x < BUNKER_4_XPOSITION + BUNKER_WIDTH)
        {
            bunkerID = 3;
        }
        else
        {
            bunkerID = -1;
        }
        
        //Find where on the bunker it was hit
        if(bunkerID != -1)
        {
            switch (bunkerID)
            {
                case 0:
                    
                    break;
                case 1:
                    
                    break;
                case 2:
                    
                    break;
                case 3:
                    
                    break;
                default:
                    break;
            }
        }
    }
    
    return bunkerHitValue;
}





//This function is passed an alien number and returns a point that the alien is at. Returns point x = -1, y = -1 if invalid alien
point_t alienPosition(int alienNumber)
{
    point_t alienCoordinates;
    alienCoordinates.x = 0;
    alienCoordinates.y = 0;
    
    //Make sure the alienNumber is valid
    if(alienNumber < (NUM_ALIEN_ROW * NUM_ALIEN_COL) && alienNumber >= 0)
    {
        point_t alienLocation = getAlienLocation();
        
        int alienX = alienNumber % NUM_ALIEN_COL;
        int alienY = alienNumber / NUM_ALIEN_COL;
        
        alienCoordinates.x = alienLocation.x + (ALIEN_WIDTH * alienX);
        alienCoordinates.y = alienLocation.y + ((alienY * ALIEN_HEIGHT) + (alienY * ROW_SPACING));
    }
    
    return alienCoordinates;
}




//This function is passed a bullet position,
void bulletHitDetection()
{
    point_t alienLocation = getAlienLocation();
    point_t tankBulletPos = getTankBulletPosition();

    
    
    
}













