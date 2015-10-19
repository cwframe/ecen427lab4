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
#include "input.h"
#include "xgpio.h"


#define TANK_MOVE_LEFT_MASK 8
#define TANK_MOVE_RIGHT_MASK 2
#define FIRE_BULLET_MASK 1

XGpio gpPB;
//Returns the number of the current button that is being pressed
void handleButton(int currentButtonState)
{
    currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.
    
    if(currentButtonState)
    {
    	if(getLives())
    	{
			paintTank();
			resumeGame();
    	}
    }

    if(currentButtonState & TANK_MOVE_LEFT_MASK)
    {
    	if(getLives())
    		tankMove(0);
    }
    if(currentButtonState & TANK_MOVE_RIGHT_MASK)
    {
    	if(getLives())
    		tankMove(1);
    }
    if(currentButtonState & FIRE_BULLET_MASK)
    {
    	if(getLives())
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
            	//xil_printf("alien hit detection\n\r");
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
    char bunkerHitBool = 0;
    char bunkerHitX = 0;
    char bunkerHitY = 0;
    int bitmapX = -1;
    int bitmapY = -1;
    
    
    if(position.y >= BUNKER_Y_VALUE && position.y < (BUNKER_Y_VALUE + BUNKER_HEIGHT))
    {
        
        if(position.x >= BUNKER_0_XPOSITION && position.x < BUNKER_0_XPOSITION + BUNKER_WIDTH)

        {
            bunkerHit.x = 0;
        }
        else if(position.x >= BUNKER_1_XPOSITION && position.x < BUNKER_1_XPOSITION + BUNKER_WIDTH)
        {
            bunkerHit.x = 1;
        }
        else if(position.x >= BUNKER_2_XPOSITION && position.x < BUNKER_2_XPOSITION + BUNKER_WIDTH)
        {
            bunkerHit.x = 2;
        }
        else if(position.x >= BUNKER_3_XPOSITION && position.x < BUNKER_3_XPOSITION + BUNKER_WIDTH)
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
                    bitmapX = position.x - BUNKER_0_XPOSITION;
                    bitmapY = position.y - BUNKER_Y_VALUE;
                    
                    if(bitmapX < 24)
                    {
                        bunkerHitBool = ((bunkerLeft[bitmapY] >> ((BUNKER_WIDTH/2)-1-bitmapX)) & MASK_ONE);
                    }
                    else
                    {
                        bunkerHitBool = ((bunkerRight[bitmapY] >> ((BUNKER_WIDTH/2)-1-(bitmapX - 24))) & MASK_ONE);
                    }
                    
                    bunkerHitX = (bitmapX / (BUNKER_WIDTH/4));
                    bunkerHitY = (bitmapY / (BUNKER_HEIGHT/3));
                    break;
                    
                case 1:
                    bitmapX = position.x - BUNKER_1_XPOSITION;
                    bitmapY = position.y - BUNKER_Y_VALUE;
                    
                    if(bitmapX < 24)
                    {
                        bunkerHitBool = ((bunkerLeft[bitmapY] >> ((BUNKER_WIDTH/2)-1-bitmapX)) & MASK_ONE);
                    }
                    else
                    {
                        bunkerHitBool = ((bunkerRight[bitmapY] >> ((BUNKER_WIDTH/2)-1-(bitmapX - 24))) & MASK_ONE);
                    }
                    
                    bunkerHitX = (bitmapX / (BUNKER_WIDTH/4));
                    bunkerHitY = (bitmapY / (BUNKER_HEIGHT/3));
                    break;
                    
                case 2:
                    bitmapX = position.x - BUNKER_2_XPOSITION;
                    bitmapY = position.y - BUNKER_Y_VALUE;
                    
                    if(bitmapX < 24)
                    {
                        bunkerHitBool = ((bunkerLeft[bitmapY] >> ((BUNKER_WIDTH/2)-1-bitmapX)) & MASK_ONE);
                    }
                    else
                    {
                        bunkerHitBool = ((bunkerRight[bitmapY] >> ((BUNKER_WIDTH/2)-1-(bitmapX - 24))) & MASK_ONE);
                    }
                    
                    bunkerHitX = (bitmapX / (BUNKER_WIDTH/4));
                    bunkerHitY = (bitmapY / (BUNKER_HEIGHT/3));
                    break;
                    
                    
                case 3:
                    bitmapX = position.x - BUNKER_3_XPOSITION;
                    bitmapY = position.y - BUNKER_Y_VALUE;
                    
                    if(bitmapX < 24)
                    {
                        bunkerHitBool = ((bunkerLeft[bitmapY] >> ((BUNKER_WIDTH/2)-1-bitmapX)) & MASK_ONE);
                    }
                    else
                    {
                        bunkerHitBool = ((bunkerRight[bitmapY] >> ((BUNKER_WIDTH/2)-1-(bitmapX - 24))) & MASK_ONE);
                    }
                    
                    bunkerHitX = (bitmapX / (BUNKER_WIDTH/4));
                    bunkerHitY = (bitmapY / (BUNKER_HEIGHT/3));
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    //Add the x segment to the point
    bunkerHit.y = (bunkerHitY * 4) + bunkerHitX;
    if(bunkerHitBool)
    {
        return bunkerHit;
    }
    else
    {
        bunkerHit.x = -1;
        bunkerHit.y = -1;
        return bunkerHit;
    }
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



int motherShipHitDetection(point_t bulletPosition)
{
    unsigned int shipPosition = getShipPos();
    int bitmapX = 0;
    int bitmapY = 0;
    int shipHit = 0;
    
    bitmapX = bulletPosition.x - shipPosition;
    bitmapY = bulletPosition.y - SHIP_Y;
    
    if(bulletPosition.y >= SHIP_Y && bulletPosition.y < (SHIP_Y + SHIP_HEIGHT))
    {
        if(bulletPosition.x >= shipPosition && bulletPosition.x < shipPosition + SHIP_WIDTH)
        {
            
            shipHit = ((saucer[bitmapY] >> (SHIP_WIDTH-1-bitmapX)) & MASK_ONE);
        }
    }
    return shipHit;
}




//This function is passed a bullet position,
void bulletHitDetection()
{
    point_t alienLocation = getAlienLocation();
    point_t tankBulletPos = getTankBulletPosition();
}













