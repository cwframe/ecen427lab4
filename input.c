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
#include <xtmrctr.h>
#include <xintc_l.h>
#include <xgpio.h>
#include <xparameters.h>
#include "input.h"

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
int bulletMoveTimer = 0;
int tankMoveTimer = 0;
int paused = 0;
int saucerFlash = 0;




// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
void interrupt_handler_dispatcher(void* ptr)
{
//	 /* Reset the timers, and clear interrupts */
//	  XTmrCtr_mSetControlStatusReg(XPAR_DELAY_BASEADDR, 0, XTC_CSR_INT_OCCURED_MASK |
//	                               XTC_CSR_LOAD_MASK );
//
//	  /* Enable timer interrupts in the interrupt controller */
//	  XIntc_mEnableIntr(XPAR_DELAY_BASEADDR, XPAR_DELAY_INTERRUPT_MASK);
//
//	  /* Start the timers */
//	  XTmrCtr_mSetControlStatusReg(XPAR_DELAY_BASEADDR, 0, XTC_CSR_ENABLE_TMR_MASK |
//	                               XTC_CSR_ENABLE_INT_MASK | XTC_CSR_AUTO_RELOAD_MASK |
//	                               XTC_CSR_DOWN_COUNT_MASK);

	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);
    
	// Check the FIT interrupt first.
	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK)
	{
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
		timer_interrupt_handler();
	}

	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK)
	{
		XIntc_AckIntr(XPAR_AXI_AC97_0_BASEADDR, XPAR_AXI_AC97_0_INTERRUPT_MASK);
		xil_printf("herro\n\r");
	}



}

void pauseGame()
{
//	xil_printf("paused\n\r");
	paused = 1;
}
															//xtmrctr look at examples
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
		bulletMoveTimer++;
		if(getShipAlive())
			shipMoveTimer++;
	}
	tankMoveTimer++;
	//Poll the buttons
    if(tankMoveTimer >= TANK_SPEED)
    {
        handleButton(currentButtonState);
    }

    //Advance the aliens and fire bullets
    if(alienMarchTimer >= ALIEN_MARCH_SPEED)
    {
       alienMarch();
       if(rand() % BULLET_CHANCE == 0)
       {
           fireAlienBullet();
       }
       alienMarchTimer = 0;
    }
    
    //Advance the bullets
    if(bulletMoveTimer >= BULLET_SPEED)
    {
        bulletMove();
        bulletMoveTimer = 0;
    }
    


    //Move the saucer if it is active
	if(getShipActive())
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
	if(saucerFlash > 0)
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
			}
			else
			{
				setShipPos(SCREEN_WIDTH + SHIP_WIDTH);
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
	if(secondTimer >= SECOND_TIMER_MAX)
	{

		secondTimer = 0;
        gameRunTime++;
        saucerTime++;
	}

}




