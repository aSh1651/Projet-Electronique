#ifndef SRC_ROUE_PWM_H_
#define SRC_ROUE_PWM_H_
#include <stdio.h>
#include "main.h"
void setup_roue_PWM();
void loop_roue_PWM();
int ch_b[4]= {1084, 957, 956, 1030};
int ch_min=200;
int ch_max=2000;
int pwm_min = 1000;
int pwm_max = 60000;
void convertir_sbus_to_pwm();

#endif /* SRC_ROUE_PWM_H_ */
