#include "vector_control.h"

arm_pid_instance_f32  pid_ud;
arm_pid_instance_f32  pid_uq;
arm_pid_instance_f32  pid_us;

float32_t  ADC_Vsample_U;
float32_t  tmp_u_s = 0;

extern float32_t  ADC_integral;
extern float32_t HiSTM_SPWM_Ma;
extern uint8_t   str1[100], str2[100];
extern uint16_t  ADC_injected_counter;
extern float32_t ADC_vsample[500];
extern float32_t ADC_vsample_Shift[500];


void HiSTM_VC_init(void)
{
	/* init pid */
	pid_ud.Kp = 0.10;
	pid_ud.Ki = 0.0;
	pid_ud.Kd = 0.0;
	arm_pid_init_f32(&pid_ud, 1);

	pid_uq.Kp = 1.0;
	pid_uq.Ki = 0.0;
	pid_uq.Kd = 0.0;
	arm_pid_init_f32(&pid_uq, 1);

	pid_us.Kp = 1.0;
	pid_us.Ki = 0.0;
	pid_us.Kd = 0.0;
	arm_pid_init_f32(&pid_us, 1);
}

void HiSTM_VC_realize(void)
{
	/* tmp variables */
	float32_t tmp_u_d = 0, tmp_u_q = 0;

	/* first calculate */
	uint16_t tmp_cnt = 500 - DMA_GetCurrDataCounter(DMA2_Stream5);
	if(tmp_cnt < 5)
			return ;

	float32_t  wc =  tmp_cnt * pi / 250 ;

	float32_t tmp_U  = 0.20*(ADC_vsample[tmp_cnt] + ADC_vsample[tmp_cnt-1] + ADC_vsample[tmp_cnt-2] + ADC_vsample[tmp_cnt-3] + ADC_vsample[tmp_cnt-4]);
	float32_t tmp_B  = 0.20*(ADC_vsample_Shift[tmp_cnt] + ADC_vsample_Shift[tmp_cnt-1] + ADC_vsample_Shift[tmp_cnt-2] + ADC_vsample_Shift[tmp_cnt-3] + ADC_vsample_Shift[tmp_cnt-4]);


	arm_park_f32(tmp_U, tmp_B, &tmp_u_d, &tmp_u_q,
			arm_sin_f32(wc), arm_cos_f32(wc));


	DAC_SetChannel1Data(DAC_Align_12b_R, (uint16_t)tmp_u_d/3.3*4096);
	DAC_SetChannel2Data(DAC_Align_12b_R, (uint16_t)tmp_u_q/3.3*4096);

	arm_sqrt_f32(tmp_u_d*tmp_u_d+tmp_u_q*tmp_u_q, &tmp_u_s);

	HiSTM_SPWM_bipolar_calculate();

	sprintf(str1, "%f    ", HiSTM_SPWM_Ma);
	sprintf(str2, "ud=%.2fV, uq=%.2fV, us=%.2fV   ", tmp_u_d, tmp_u_q, tmp_u_s);
	/* 3.  park transform (al, bt) -> (d, q)*/
}

