/*
 * roues.c
 */

#include <stm32l4xx_hal.h>
#include "main.h"
#include "roues.h"
#include "sbus.h"

#define direction_gauche GPIO_PIN_11
#define direction_droite GPIO_PIN_10

#define PWM_MOTEUR 50000
#define INCLINAISON 100

#define REPOS_CH2 958
#define REPOS_CH3 956

// Retourne :
//  1  = haut
//  0  = bas
// -1  = repos
int decode_inclinaison(int channel, int repos)
{
	if(repos + INCLINAISON +10 < channel) //channel > repos + INCLINAISON
	{
		return 1;
	}
	else if(repos - INCLINAISON -10 > channel)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

void roue_stop(void)
{
	TIM1->CCR1 = 0; // roue droite
	TIM1->CCR2 = 0; // roue gauche

	HAL_GPIO_WritePin(GPIOA, direction_droite, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, direction_gauche, GPIO_PIN_RESET);
}

// roue_droite = 1 : roue droite
// roue_droite = 0 : roue gauche
// direction = 1 : avant
// direction = 0 : arrière
void roue_marche(int direction, int roue_droite)
{
	if(direction != 0 && direction != 1)
	{
		return;
	}

	if(roue_droite == 1)
	{
		HAL_GPIO_WritePin(GPIOA, direction_droite, direction);
		TIM1->CCR1 = PWM_MOTEUR;
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, direction_gauche, direction);
		TIM1->CCR2 = PWM_MOTEUR;
	}
}

void controle_roues_sbus(void)
{
	int direction_gauche_val;
	int direction_droite_val;
	// CH3 = joystick gauche = roue gauche
	direction_gauche_val = decode_inclinaison(sbus_channels[2], REPOS_CH3);
	direction_droite_val = decode_inclinaison(sbus_channels[1], REPOS_CH2);
	if(direction_gauche_val == 1)
	{
		roue_marche(1, 0); // roue gauche avant
	}
	else if(direction_gauche_val == 0)
	{
		roue_marche(0, 0); // roue gauche arrière
	}
	else
	{
		TIM1->CCR2 = 0; // repos roue gauche
	}

	// CH2 = joystick droit = roue droite
	// Attention : logique inversée


	if(direction_droite_val == 0)
	{
		roue_marche(0, 1); // roue droite avant
	}
	else if(direction_droite_val == 1)
	{
		roue_marche(1, 1); // roue droite arrière
	}
	else
	{
		TIM1->CCR1 = 0; // repos roue droite
	}
}

void setup_roue_PWM(void)
{
	roue_stop();
}

