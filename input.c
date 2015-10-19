/*
 * input.c
 *
 *  Created on: Sep 30, 2015
 *      Author: superman
 */

#include "xgpio.h"          // Provides access to PB GPIO driver.
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "graphics.h"
#include "globals.h"
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.
#include "gameLogic.h"

XGpio gpPB;   // This is a handle for the push-button GPIO block.

#define CHAR_OFFSET 48
#define SECOND_TIMER_MAX 100
#define TENTH_SECOND 10
#define QUARTER_SECOND 25
#define HALF_SECOND 50
#define BULLET_SPEED 3
#define BULLET_CHANCE 3
#define SHIP_MOVE_MAX_TIMER 3
#define TANK_SPEED 2
#define ALIEN_MARCH_SPEED QUARTER_SECOND
#define FLASH_MAX 3


int currentButtonState;		// Value the button interrupt handler saves button values to
int gameRunTime = 0;
int saucerTime = 0;
int secondTimer = 0;
int alienMarchTimer = 0;
int shipMoveTimer = 0;
int paused = 0;
int saucerFlash = 0;




// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
void interrupt_handler_dispatcher(void* ptr)
{
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);
    
	// Check the FIT interrupt first.
	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
		timer_interrupt_handler();
	}

}

void pauseGame()
{
	paused = 1;
}

void resumeGame()
{
	paused = 0;
}

int getPaused()
{
	return paused;
}

//Timer interrupt for the game.
void timer_interrupt_handler()
{
	if(!paused)
	{
		secondTimer++;
		alienMarchTimer++;
		if(getShipAlive())
			shipMoveTimer++;
	}
	//Poll the buttons
    if(secondTimer % TANK_SPEED == 0)
    {
        handleButton(currentButtonState);
    }

    //Advance the aliens and fire bullets
    if(alienMarchTimer >= ALIEN_MARCH_SPEED)
    {
       //alienMarch();
        if(rand() % BULLET_CHANCE == 0)
        {
            fireAlienBullet();
        }
        alienMarchTimer = 0;
    }
    
    //Advance the bullets
    if(secondTimer % BULLET_SPEED == 0 && !paused)
    {
        bulletMove();
    }
    


    //Move the saucer if it is active
	if(getShipActive() && !paused)
	{
		if(shipMoveTimer >= SHIP_MOVE_MAX_TIMER)
		{
			shipMoveTimer = 0;
			marchShip();
		}
	}



	//If the saucer is killed flash the score animation
	if(getMothershipKilled() && saucerFlash == 0)
	{
		saucerFlash = 1;
	}

	//If the saucer is killed flash the score animation
	if(saucerFlash > 0 && !paused)
	{

		//Paint score
		if(secondTimer == HALF_SECOND)
		{
			paintShipScore(1);
			saucerFlash++;
		}
		//paint black
		if(secondTimer == SECOND_TIMER_MAX)
		{
			paintShipScore(0);
			saucerFlash++;
		}
		if(saucerFlash >= 7)
		{
			paintShipScore(0);
			saucerFlash = 0;
			setMothershipKilled(0);
			if(getShipDirection())
			{

				setShipPos(-SHIP_WIDTH);
				setShipDirection(1);
				xil_printf("to the right\n\r");
			}
			else
			{
				setShipPos(SCREEN_WIDTH + SHIP_WIDTH);
				xil_printf("to the left\n\r");
				setShipDirection(0);

			}
		}

	}

	//Spawn the saucer every X seconds
	if(saucerTime == 10 && !paused)
	{
		saucerTime = 0;
		if(!getShipActive() && saucerFlash == 0)
		{
			setShipActive(1);
			setShipAlive(1);
			setMothershipKilled(0);
		}
	}

    //Tic the clock one second
	if(secondTimer == SECOND_TIMER_MAX && !paused)
	{

		secondTimer = 0;
        gameRunTime++;
        saucerTime++;
	}

}




