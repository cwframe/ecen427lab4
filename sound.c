/*
 * sound.c
 *
 *  Created on: Oct 26, 2015
 *      Author: superman
 */

#include "sound.h"
#include "xac97_l.h"

#define C_BASEADDR 0xFFFF8000
#define C_OPB_AWIDTH 32
#define C_OPB_DWIDTH 32
#define C_HIGHADDR 0xFFFF80FF
#define C_PLAYBACK 1
#define C_RECORD 1
#define C_INTR_LEVEL 1
#define C_USE_BRAM 1

extern int tankFireSoundFrames;
extern int* tankFireSound;
extern int tankFireSoundRate;

void init_Sound()
{
	xil_printf("RESET?\n\r");
	XAC97_HardReset(C_BASEADDR);
	//xil_printf("audio?\n\r");
	//XAC97_InitAudio(C_BASEADDR,2);
	xil_printf("clearfifo?\n\r");
	XAC97_ClearFifos(C_BASEADDR);
	xil_printf("done\n\r");
}

void playTankFireSound(int* sound)
{
	int i, j;
	for(j = 0; j < tankFireSoundFrames/100; j++)
	{
		for(i = 0; i < 100; i++)
		{
			XAC97_WriteFifo(C_BASEADDR + i, tankFireSound[i+(j*100)]);
		}
		XAC97_PlayAudio(C_BASEADDR, C_BASEADDR, C_BASEADDR+100);
		XAC97_ClearFifos(C_BASEADDR);
	}
}
