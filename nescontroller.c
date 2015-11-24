/*
 * nescontroller.c
 *
 *  Created on: Nov 23, 2015
 *      Author: superman
 */

#include "nescontroller.h"
#include "xparameters.h"
#include <xil_io.h>

#define B_MASK 2
#define LEFT_MASK 64
#define RIGHT_MASK 128
#define BIT_0_MASK 1



void readController()
{
	/*if(prev != Xil_In32LE(XPAR_NES_CONTROL_0_BASEADDR))
	{
		prev = Xil_In32LE(XPAR_NES_CONTROL_0_BASEADDR);
		xil_printf("%d\n\r", prev);
	}*/
	int controllerin = Xil_In32LE(XPAR_NES_CONTROL_0_BASEADDR);
	int buttonpressed = 0;
	if((controllerin & B_MASK) == 0)
	{
		buttonpressed += B_MASK;
	}
	if((controllerin & LEFT_MASK) == 0)
	{
		buttonpressed += LEFT_MASK;
	}
	if((controllerin & RIGHT_MASK) == 0)
	{
		buttonpressed += RIGHT_MASK;
	}

	handleController(buttonpressed);
}
