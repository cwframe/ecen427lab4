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

XGpio gpPB;   // This is a handle for the push-button GPIO block.

#define CHAR_OFFSET 48
#define SECOND_TIMER_MAX 50

int currentButtonState;		// Value the button interrupt handler saves button values to
int onesecondtimer = 0;



void input(int c)
{
	int first,second;
	switch (c)
	{
		case 8:
			tankMove(0);
			break;
		case 2:
			tankMove(1);
			break;
		case 1:
			alienMarch();
			break;
//		case '2':
//			first = getchar();
//			second = getchar();
//			killAlien((first-CHAR_OFFSET) * 10 + (second-CHAR_OFFSET));
//			break;
//		case '5':
//			fireBullet();
//			//FIRE TEH TANK BULLET
//			break;
//		case '3':
//			fireAlienBullet();
//			//SHOOT ALL THE BULLETz
//			break;
//		case '9':
//			bulletMove();
//			break;
//		case '7':
//			bunkerHit(getchar()-48, (rand() % BUNKER_WIDTH));
//			break;
		default:
			break;
	}
}

// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);
	// Check the FIT interrupt first.

	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
		timer_interrupt_handler();
	}

}


// This is invoked in response to a timer interrupt.
// It does 2 things: 1) debounce switches, and 2) advances the time.
void timer_interrupt_handler()
{
	onesecondtimer++;

	//Poll the buttons
	handleButton();

	if(onesecondtimer == SECOND_TIMER_MAX && !currentButtonState)
	{
		xil_printf("1 Second\n");
		alienMarch();
		onesecondtimer = 0;
	}
}


	//Returns the number of the current button that is being pressed
void handleButton()
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
}

