/*
 * sound.c
 *
 *  Created on: Oct 26, 2015
 *      Author: superman
 */

#include "sound.h"
#include "xio.h"
#include "xac97_l.h"
#include "xparameters.h"
#include "platform.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "sound.h"

#define FIFO_SIZE 512

unsigned int* currentSound;
int currentNumFrames;
int currentIndex;
int currentPriority;

void init_Sound()
{
	xil_printf("RESET?\n\r");
	XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);

	XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);

	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, 1);

	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, AC97_PCM_RATE_11025_HZ);

	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_MAX);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_AuxOutVol, AC97_VOL_MAX);
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVolMono, AC97_VOL_MAX);

	XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);

	XAC97_AwaitCodecReady(XPAR_AXI_AC97_0_BASEADDR);

	currentSound = 0;
	currentIndex = 0;
	currentPriority = 0;
	currentNumFrames = 0;

	xil_printf("done\n\r");
}

void playSound()
{
	int sample = 0;
	int i;

	//xil_printf("playing sound\n\r");
	//XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, 1);
	//XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, AC97_PCM_RATE_11025_HZ);

	for(i=0; i < FIFO_SIZE/4; i++)
	{
//			xil_printf("%d        %d\n\r", sound, i);
		if(currentIndex >= currentNumFrames)
		{
			currentPriority = 0;
			//XAC97_WriteFifo(XPAR_AXI_AC97_0_BASEADDR, 0);
			XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR, 0);
		}
		else
		{
			sample = currentSound[currentIndex];
			currentIndex++;
			//XAC97_WriteFifo(XPAR_AXI_AC97_0_BASEADDR, sample);
			while(XAC97_isInFIFOFull(XPAR_AXI_AC97_0_BASEADDR));
			XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR, ((sample<<16)|sample));
		}
	}

}

void setSound(unsigned int* soundtoplay, int numFrames, int priority)
{
	if(priority > currentPriority)
	{
		currentSound = soundtoplay;
		currentNumFrames = numFrames;
		currentIndex = 0;
		currentPriority = priority;
	}
}
