#include "main.h"

uint8_t str1[100], str2[100];

/*
 *         main program
 * */
int main(void)
{
	/* MCU init */
	HiSTM_SysTick_init();

	/* bsp init */
	HiSTM_SPI1_Init();
	HiSTM_SCP_init();
	HiSTM_SCP_clear(0x0000);
	bsp_HiSTM_LED_init();

	/* analog init */
	HiSTM_ADC_Init();
	HiSTM_DAC_init();

	/* control init */
	HiSTM_VC_init();

	/* timer init */
	HiSTM_SPWM_bipolar_init();
	HiSTM_SPWM_bipolar_calculate();

	/*  SPWM GENERATION START HERE  */
	HiSTM_SPWM_bipolar_cmd(ENABLE);

	while(1)
	{
		HiSTM_VC_realize();
		HiSTM_SCP_display_string(0,0,str1,HiSTM_SCP_CHARMODE_NOOVERLYING,0xffff,0x0000);
		HiSTM_SCP_display_string(0,0,str2,HiSTM_SCP_CHARMODE_NOOVERLYING,0xffff,0x0000);
	}

	return 0;

}

