/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 */

#include <stdio.h>
#include "platform.h"
#include "sound.h"
#include "xparameters.h"
#include "xac97_l.h"



void print(char *str);

int main()
{
	init_platform();
	xil_printf("init\n\r");
	init_Sound();//hard reset
	xil_printf("FIRE EVERYTHING\n\r");
	//for(i = 0; i < 1; i++)
	/*XAC97_PlayAudio(XPAR_AXI_AC97_0_BASEADDR, Test_getSound(),
			Test_getSound()+Test_getNumFrames());*/
	playSound(shoot_getSound(), shoot_getNumFrames());
	//playTankFireSound();
	xil_printf("done and cleaning\n\r");
	cleanup_platform();
    return 0;
}
