#include <stm32l4xx_hal.h>
#include "roue_PWM.h"s

void setup_roue_PWM(){
	TIM1->CCR1 = 40000;
}

void loop_roue_PWM(){
	for(int i= 0; i <=60000 ; i = i + 1000){
		TIM1->CCR1 = i;
		HAL_Delay(5);
		printf("test_boucle1");
	}
	for(int i= 60000; i >=0 ; i = i - 1000){
			TIM1->CCR1 = i;
			HAL_Delay(5);
			printf("test_boucle2");
		}
}
