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
void convertir_sbus_to_pwm(int i, uint8_t* sbus_buffer ){
  int pmw= ((sbus_buffer[i] - ch_min) *( pwm_max- pwm_min ))/
                    (ch_max - ch_min) +
                   pwm_min;
  TIM1->CCR1 = pmw;
  printf("ccr%d=|\r\n ",pmw );
}
