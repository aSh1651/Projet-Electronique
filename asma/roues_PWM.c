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
void convertir_sbus_to_pwm(int i, uint16_t* sbus_channel ){
	uint16_t neutre = ch_b[i];
	uint16_t sbus_valeur=sbus_channel[i];
	uint32_t pwm = 0;
	// securité pour éviter de sortir de la plage de donnée
	if (sbus_valeur < ch_min) sbus_valeur = ch_min;
	if (sbus_valeur > ch_max) sbus_valeur = ch_max;
	// distinction des cas selon que valeur sbus soit sup ou inferieur à la valeur neutre
	if (sbus_valeur > neutre) {
	        // Zone Haute : du neutre (0%) vers le max (100%)
	        // Formule : (Valeur - Depart) * (Arrivée_Max / Plage_SBUS)
	        pwm = (uint32_t)(sbus_valeur - neutre) * pwm_max / (ch_max - neutre);
	    } 
	    else if (sbus_valeur < neutre) {
	        // Zone Basse : du neutre (0%) vers le min (100%)
	        pwm = (uint32_t)(neutre - sbus_valeur) * pwm_max / (neutre - ch_min);
	    } 
	    else {
	        pwm = 0; // Pile sur le neutre
	    }
	TIM1->CCR1 = pmw;
	HAL_Delay(5);
  printf("Canal %d = %lu \r\n", i, pwm);// lu =long unsigned
}

