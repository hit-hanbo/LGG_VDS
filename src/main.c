#include "stm32f4xx.h"
#include "scp.h"
#include "LED.h"
#include "main.h"

RCC_ClocksTypeDef a;

int main(void)
{
//	HiSTM_system_clocks_config();

	HiSTM_SysTick_init();
	HiSTM_SCP_init();
	bsp_HiSTM_LED_init();
//	HiSTM_SCP_clear(0xF800);
	HiSTM_LED_G_ON;
	HiSTM_LED_R_ON;

	HiSTM_ADC_Init();
	HiSTM_slave_TIM9_init();

	HiSTM_SPWM_bipolar_init();
	HiSTM_SPWM_bipolar_calculate();
	HiSTM_SPWM_bipolar_cmd(ENABLE);

	while(1);

	return 0;

}

/*  system clocks configure function  */
static void HiSTM_system_clocks_config(void)
{
	RCC_DeInit();

	/* switch to HSI */
//	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
//	while(RCC_GetSYSCLKSource() != 0x00);
	RCC_PLLCmd(DISABLE);

	/* config HSE */
//	RCC_HSEConfig(RCC_HSE_ON);
//	while(RCC_WaitForHSEStartUp() != SUCCESS);

	/* config sys & periph clks */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div2);
	RCC_PCLK1Config(RCC_HCLK_Div4);

	/* config PLL */
	RCC_PLLConfig(RCC_PLLSource_HSI, 8, 180, 2, 2, 2);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource() != 0x0c);

	/* call cmsis function to update syscoreclk */
	SystemCoreClockUpdate();
}


