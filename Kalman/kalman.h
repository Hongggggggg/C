#ifndef __KALMAN_H
#define __KALMAN_H

#include <stdint.h>

typedef struct
{
	float Q;
	float R;
}Kalman_init_param_T;

void kalman_filter_init(Kalman_init_param_T* kalman_init_param);

float kalman_filter(float* measure_data, uint8_t data_len);

#endif
