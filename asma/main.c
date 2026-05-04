/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : VERSION FINALE - CONFIGURATION PROF 8-BITS + DIAGNOSTIC
 ******************************************************************************
 */
/* USER CODE END Header */

#include "main.h"
#include <stdio.h>
#include <stdint.h>

/* --- VARIABLES --- */
UART_HandleTypeDef huart2; // Console PC
UART_HandleTypeDef huart3; // Radio SBUS (PC11)

uint8_t sbus_buffer[25];
uint16_t sbus_channels[8];

/* --- PROTOTYPES --- */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);

/* Redirection printf */
int __io_putchar(int ch) {
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 10);
	return ch;
}

int main(void) {
	/* 1. INITIALISATION */
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();

	HAL_Delay(500);
	printf("\r\n=================================");
	printf("\r\n   MODE DIAGNOSTIC SBUS ACTIF    ");
	printf("\r\n   CONFIG: 8B / EVEN / 2 STOP    ");
	printf("\r\n=================================\r\n");

	/* 2. BOUCLE DE LECTURE MODIFIÉE */
	while (1) {
		uint8_t byteRecu = 0;

		// "read" : On lit un octet
		if (HAL_UART_Receive(&huart3, &byteRecu, 1, 1000	) == HAL_OK) {

			// --- DIAGNOSTIC 1 : On affiche TOUT ce qui arrive ---
			// Si tu ne vois rien défiler ici, c'est un problème de CÂBLE.
			printf("REC: %02X ", byteRecu);

			// On accepte 0x0F (normal) ou n'importe quoi d'autre pour forcer la lecture
			if (byteRecu == 0x0F) // Octet debut de trame
				//if (byteRecu != 0)     // Version "force" pour voir si ça bouge
			{
				sbus_buffer[0] = byteRecu;

				// "read 24" : On tente de lire la suite
				if (HAL_UART_Receive(&huart3, &sbus_buffer[1], 24, 20) == HAL_OK) {

					/* DECODAGE DES CANAUX */
					sbus_channels[0] = ((sbus_buffer[1]      | sbus_buffer[2] << 8) & 0x07FF);
					sbus_channels[1] = ((sbus_buffer[2] >> 3 | sbus_buffer[3] << 5) & 0x07FF);

					// --- DIAGNOSTIC 2 : Affichage des canaux ---
					printf(" -> CH1: %d | CH2: %d\r\n", sbus_channels[0], sbus_channels[1]);
				} else {
					printf("HAL no OK sur octets 1-24, timeout?\r\n");
				}
			} else { // l'octet recu n'est un debut de trame
				printf("Pas un octet de debut de trame.\r\n");
				continue;
			}
		} else {
			printf("HAL no OK sur octet 0, timeout?\r\n");
		}
	}
}

/* --- CONFIGURATION USART3 (STRICTEMENT SELON IMAGE_64A764.PNG) --- */
static void MX_USART3_UART_Init(void) {
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 100000;
	huart3.Init.WordLength = UART_WORDLENGTH_9B; // 8 Bits (including Parity)
	huart3.Init.StopBits = UART_STOPBITS_2;      // 2 Stop Bits
	huart3.Init.Parity = UART_PARITY_EVEN;       // Even Parity
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK) {
		Error_Handler();
	}
}

/* --- CONFIGURATION USART2 (CONSOLE PC) --- */
static void MX_USART2_UART_Init(void) {
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	HAL_UART_Init(&huart2);
}

/* --- CONFIGURATION HORLOGE ET GPIO --- */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 10;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
}

static void MX_GPIO_Init(void) {
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
}

void Error_Handler(void) {
	__disable_irq();
	while (1) {}
}
