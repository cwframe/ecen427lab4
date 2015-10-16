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




//This function uses the point_t in a different way, the x value is the Bunker ID that was hit and the y value is the X segment of the bunker that was hit
point_t bunkerHitDetection(point_t position)
{
    point_t bunkerHit;
    
    int bullet_relative_pos = -1;

    if(position.y > BUNKER_Y_VALUE && position.y < (BUNKER_Y_VALUE + BUNKER_HEIGHT))
    {
        if(position.x > BUNKER_0_XPOSITION && position.x < BUNKER_0_XPOSITION + BUNKER_WIDTH)
        {
            bunkerHit.x = 0;
        }
        else if(position.x > BUNKER_1_XPOSITION && position.x < BUNKER_1_XPOSITION + BUNKER_WIDTH)
        {
            bunkerHit.x = 1;
        }
        else if(position.x > BUNKER_2_XPOSITION && position.x < BUNKER_2_XPOSITION + BUNKER_WIDTH)
        {
            bunkerHit.x = 2;
        }
        else if(position.x > BUNKER_3_XPOSITION && position.x < BUNKER_3_XPOSITION + BUNKER_WIDTH)
        {
            bunkerHit.x = 3;
        }
        else
        {
            bunkerHit.x = -1;
            bunkerHit.y = -1;
        }
        
        //Find where on the bunker it was hit
        if(bunkerHit.x != -1)
        {
            switch (bunkerHit.x)
            {
                case 0:
                    bullet_relative_pos = position.x - BUNKER_0_XPOSITION;
                    bullet_relative_pos = (bullet_relative_pos / (BUNKER_WIDTH/4));
                    break;
                    
                case 1:
                    bullet_relative_pos = position.x - BUNKER_1_XPOSITION;
                    bullet_relative_pos = (bullet_relative_pos / (BUNKER_WIDTH/4));
                    break;
                    
                case 2:
                    bullet_relative_pos = position.x - BUNKER_2_XPOSITION;
                    bullet_relative_pos = (bullet_relative_pos / (BUNKER_WIDTH/4));
                    break;
                    
                case 3:
                    bullet_relative_pos = position.x - BUNKER_3_XPOSITION;
                    bullet_relative_pos = (bullet_relative_pos / (BUNKER_WIDTH/4));
                    break;
                    
                default:
                    break;
            }
        }
    }
    //Add the x segment to the point
    bunkerHit.y = bullet_relative_pos;
    return bunkerHit;
}





//This function is passed an alien number and returns a point that the alien is at. Returns point x = -1, y = -1 if invalid alien
point_t alienPosition(int alienNumber)
{
    point_t alienCoordinates;
    alienCoordinates.x = -1;
    alienCoordinates.y = -1;
    
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


int tankHitDetection(point_t bulletPosition)
{
    unsigned short tankPosition = getTankPositionGlobal();
    int bitmapX = 0;
    int bitmapY = 0;
    int tankHit = 0;
    
    bitmapX = bulletPosition.x - tankPosition;
    bitmapY = bulletPosition.y - TANK_Y_VALUE;
    
    if(bulletPosition.y >= TANK_Y_VALUE && bulletPosition.y < (TANK_Y_VALUE + TANK_HEIGHT))
    {
        if(bulletPosition.x >= tankPosition && bulletPosition.x < tankPosition + TANK_WIDTH)
        {
            
            tankHit = ((tank[bitmapY] >> (TANK_WIDTH-1-bitmapX)) & MASK_ONE);
        }
    }
    return tankHit;
}




//This function is passed a bullet position,
void bulletHitDetection()
{
    point_t alienLocation = getAlienLocation();
    point_t tankBulletPos = getTankBulletPosition();
}













