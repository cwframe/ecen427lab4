/*
 * PIT.c
 *
 *  Created on: Nov 5, 2015
 *      Author: superman
 */
#include "xparameters.h"
#include <xil_io.h>

#define PIT_DECREMENT_ENABLE_MASK 1
#define PIT_INTERRUPT_ENABLE_MASK 2
#define PIT_COUNTER_ENABLE_MASK 4
#define PIT_COUNT_REG_OFFSET 4


void PIT_enable_counter()
{
	Xil_Out32LE(XPAR_PIT_0_BASEADDR, PIT_DECREMENT_ENABLE_MASK | Xil_In32LE(XPAR_PIT_0_BASEADDR));
}

void PIT_disable_counter()
{
	Xil_Out32LE(XPAR_PIT_0_BASEADDR, !PIT_DECREMENT_ENABLE_MASK & Xil_In32LE(XPAR_PIT_0_BASEADDR));
}


void PIT_enable_interrupts()
{
	Xil_Out32LE(XPAR_PIT_0_BASEADDR, PIT_INTERRUPT_ENABLE_MASK | Xil_In32LE(XPAR_PIT_0_BASEADDR));
}

void PIT_disable_interrupts()
{
	Xil_Out32LE(XPAR_PIT_0_BASEADDR, !PIT_INTERRUPT_ENABLE_MASK & Xil_In32LE(XPAR_PIT_0_BASEADDR));
}


void PIT_enable_reload()
{
	Xil_Out32LE(XPAR_PIT_0_BASEADDR, PIT_COUNTER_ENABLE_MASK | Xil_In32LE(XPAR_PIT_0_BASEADDR));
}

void PIT_disable_reload()
{
	Xil_Out32LE(XPAR_PIT_0_BASEADDR, !PIT_COUNTER_ENABLE_MASK & Xil_In32LE(XPAR_PIT_0_BASEADDR));
}


void PIT_set_counter(int count)
{
	Xil_Out32LE(XPAR_PIT_0_BASEADDR + PIT_COUNT_REG_OFFSET, count);
}
