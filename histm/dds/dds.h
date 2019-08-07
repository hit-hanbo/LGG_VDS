#ifndef DDS_H_
#define DDS_H_

/* header file for: dds.c */

#include "stm32f4xx.h"

#define   DDS_MODE_SERIAL
//#define DDS_MODE_PARALLEL

#define AD9850_SYSTEM_COLCK     7600000

#define AD9850_CONTROL_PORT  GPIOA
#define AD9850_FQUD          GPIO_Pin_2
#define AD9850_WCLK          GPIO_Pin_3
#define AD9850_RST           GPIO_Pin_4

#ifdef DDS_MODE_PARALLEL
#define AD9850_DATA_PORT  GPIOC
#endif
#ifdef DDS_MODE_SERIAL
#define AD9850_DATA   GPIO_Pin_5
#define AD9850_DATA_Write_1     GPIO_WriteBit(AD9850_CONTROL_PORT,AD9850_DATA,Bit_SET)
#define AD9850_DATA_Write_0     GPIO_WriteBit(AD9850_CONTROL_PORT,AD9850_DATA,Bit_RESET)
#endif

#define AD9850_WCLK_SET    GPIO_WriteBit(AD9850_CONTROL_PORT,AD9850_WCLK,Bit_SET)
#define AD9850_WCLK_CLR    GPIO_WriteBit(AD9850_CONTROL_PORT,AD9850_WCLK,Bit_RESET)
#define AD9850_FQUD_SET    GPIO_WriteBit(AD9850_CONTROL_PORT,AD9850_FQUD,Bit_SET)
#define AD9850_FQUD_CLR    GPIO_WriteBit(AD9850_CONTROL_PORT,AD9850_FQUD,Bit_RESET)
#define AD9850_RST_SET     GPIO_WriteBit(AD9850_CONTROL_PORT,AD9850_RST,Bit_SET)
#define AD9850_RST_CLR     GPIO_WriteBit(AD9850_CONTROL_PORT,AD9850_RST,Bit_RESET)

#ifdef DDS_MODE_SERIAL
extern void AD9850_Reset_Sreial(void) ;
void AD9850_Write_Serial(uint8_t W0,unsigned long freq);

#endif

#ifdef DDS_MODE_PARALLEL
extern void AD9850_Reset_Parallel(void) ;
extern void AD9850_Write_Parallel(unsigned char W0,unsigned long freq) ;
#endif

#endif

