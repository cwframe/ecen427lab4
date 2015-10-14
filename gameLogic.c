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




void bulletHitDetection()
{
    point_t alienLocation = getAlienLocation()
    point_t tankBulletPos = get
    
    
    
}













