#include "stm32f4xx.h"
#include "scp.h"
#include "LED.h"
#include "main.h"


int main(void)
{
	HiSTM_SysTick_init();
	HiSTM_SCP_init();
	bsp_HiSTM_LED_init();
	HiSTM_SCP_clear(0xF800);

	HiSTM_ADC_Init();

//	HiSTM_SPWM_bipolar_init();
//	HiSTM_SPWM_bipolar_calculate();
//	HiSTM_SPWM_bipolar_cmd(ENABLE);

	while(1);

	return 0;

}

