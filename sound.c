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

void init_Sound()
{
	xil_printf("RESET?\n\r");
	XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);

	XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);

	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, 1);

	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_PCM_DAC_Rate, AC97_PCM_RATE_11025_HZ);

	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_MAX);


	XAC97_AwaitCodecReady(XPAR_AXI_AC97_0_BASEADDR);








	xil_printf("done\n\r");
}

void playSound(unsigned int* sound, int numFrames)
{
	int sample = 0;
	int i;
	XAC97_AwaitCodecReady(XPAR_AXI_AC97_0_BASEADDR);

	XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);

	unsigned int* start = sound;

	while( sound < (unsigned int*)(start+numFrames))
	{
		sample = *sound;
		sound = sound + 1;
		XAC97_WriteFifo(XPAR_AXI_AC97_0_BASEADDR, sample);
		/*for(i=0; i < 256; i++)
		{
//			xil_printf("%d        %d\n\r", sound, i);
			XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR, sample);
		}*/
	}

	XAC97_ClearFifos(XPAR_AXI_AC97_0_BASEADDR);
}
