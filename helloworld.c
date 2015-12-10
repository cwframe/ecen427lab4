#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "dma.h"

void print(char *str);

int main()
{


    int source_word[] = {0xDEADBEEF, 0xDEADBEAF, 0xDEEDBEEF, 0xDEEDBEAF};
    int destination_word[] = {0x0, 0x0, 0x0, 0x0};
    int transferlength = 4;

    init_platform();


    print("Hello World\n\r");
    cleanup_platform();
    printf("Printing value before DMA transfer.\n\r");
    xil_printf("%x\r\n", destination_word[0]);
	xil_printf("%x\r\n", destination_word[1]);
	xil_printf("%x\r\n", destination_word[2]);
	xil_printf("%x\r\n", destination_word[3]);

    Xil_Out32(XPAR_DMA_0_BASEADDR, (Xuint32)source_word);
    Xil_Out32(XPAR_DMA_0_BASEADDR+4, (Xuint32)destination_word);
    Xil_Out32(XPAR_DMA_0_BASEADDR+8, transferlength*4);
    Xil_Out16(XPAR_DMA_0_BASEADDR+DMA_MST_BE_REG_OFFSET, 0xFFFF);

    Xil_Out8(XPAR_DMA_0_BASEADDR+DMA_MST_GO_PORT_OFFSET, MST_START);

    printf("Printing value after DMA transfer.\n\r");
    xil_printf("%x\r\n", destination_word[0]);
    xil_printf("%x\r\n", destination_word[1]);
    xil_printf("%x\r\n", destination_word[2]);
    xil_printf("%x\r\n", destination_word[3]);

    cleanup_platform();

    return 0;
}
