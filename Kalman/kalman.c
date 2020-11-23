#include "kalman.h"

typedef struct
{
	float Q;
	float R;
	float x_last;
	float p_last;
}Kalman_param_T;

static Kalman_param_T kalman_param = {.Q = 0, .R = 0, .x_last = 0, .p_last = 0};

void kalman_filter_init(Kalman_init_param_T* kalman_init_param)
{
	kalman_param.Q = kalman_init_param->Q;
	
	kalman_param.R = kalman_init_param->R;
}

float kalman_filter(float* measure_data, uint8_t data_len)
{
	kalman_param.x_last = measure_data[0];
	
	float x_mid, p_mid, kg, x_out, p_now;
	
	for(uint8_t i = 0; i < data_len; i++)
	{
		x_mid = kalman_param.x_last;
	
		p_mid = kalman_param.p_last + kalman_param.Q;
			
		kg = p_mid/(p_mid + kalman_param.R);

		x_out = x_mid + kg*(measure_data[i] - x_mid);
			
		p_now = (1 - kg) * p_mid;

		kalman_param.p_last = p_now;

		kalman_param.x_last = x_out;
	}
	return x_out;
}