#ifndef VECTOR_CONTROL_H_
#define VECTOR_CONTROL_H_

#include "stm32f4xx.h"
#include "stdio.h"
#include "stdlib.h"
#include "arm_math.h"
#include "spwm_calculator.h"
#include "stm32f4xx_dac.h"

void HiSTM_VC_init(void);
void HiSTM_VC_realize(void);

#endif

