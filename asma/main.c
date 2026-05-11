/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : VERSION FINALE - CONFIGURATION PROF 8-BITS + DIAGNOSTIC
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdint.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
uint8_t sbus_buffer[25];
uint16_t sbus_channels[16];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* Redirection printf */
int __io_putchar(int ch) {
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 10);
	return ch;
}

/* USER CODE END 0 */

int main(void)
{
	HAL_Init();
	SystemClock_Config();

	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();

	/* USER CODE BEGIN 2 */
	HAL_Delay(500);
	printf("\r\n=================================");
	printf("\r\n   MODE DIAGNOSTIC SBUS ACTIF    ");
	printf("\r\n   CONFIG: 8B / EVEN / 2 STOP    ");
	printf("\r\n=================================\r\n");
	/* USER CODE END 2 */

	/* USER CODE BEGIN WHILE */
	while (1) {
		uint8_t byteRecu = 0;

		if (HAL_UART_Receive(&huart3, &byteRecu, 1, 1000) == HAL_OK) {

			printf("REC: %02X ", byteRecu);

			if (byteRecu == 0x0F)
			{
				sbus_buffer[0] = byteRecu;

				if (HAL_UART_Receive(&huart3, &sbus_buffer[1], 24, 20) == HAL_OK) {

					sbus_channels[0]  = ((sbus_buffer[1]      | sbus_buffer[2]  << 8) & 0x07FF);
					sbus_channels[1]  = ((sbus_buffer[2] >> 3 | sbus_buffer[3]  << 5) & 0x07FF);
					sbus_channels[2]  = ((sbus_buffer[3] >> 6 | sbus_buffer[4]  << 2 | sbus_buffer[5]  << 10) & 0x07FF);
					sbus_channels[3]  = ((sbus_buffer[5] >> 1 | sbus_buffer[6]  << 7) & 0x07FF);
					sbus_channels[4]  = ((sbus_buffer[6] >> 4 | sbus_buffer[7]  << 4) & 0x07FF);
					sbus_channels[5]  = ((sbus_buffer[7] >> 7 | sbus_buffer[8]  << 1 | sbus_buffer[9]  << 9) & 0x07FF);
					sbus_channels[6]  = ((sbus_buffer[9] >> 2 | sbus_buffer[10] << 6) & 0x07FF);
					sbus_channels[7]  = ((sbus_buffer[10] >> 5 | sbus_buffer[11] << 3) & 0x07FF);
					sbus_channels[8]  = ((sbus_buffer[12]     | sbus_buffer[13] << 8) & 0x07FF);
					sbus_channels[9]  = ((sbus_buffer[13] >> 3 | sbus_buffer[14] << 5) & 0x07FF);
					sbus_channels[10] = ((sbus_buffer[14] >> 6 | sbus_buffer[15] << 2 | sbus_buffer[16] << 10) & 0x07FF);
					sbus_channels[11] = ((sbus_buffer[16] >> 1 | sbus_buffer[17] << 7) & 0x07FF);
					sbus_channels[12] = ((sbus_buffer[17] >> 4 | sbus_buffer[18] << 4) & 0x07FF);
					sbus_channels[13] = ((sbus_buffer[18] >> 7 | sbus_buffer[19] << 1 | sbus_buffer[20] << 9) & 0x07FF);
					sbus_channels[14] = ((sbus_buffer[20] >> 2 | sbus_buffer[21] << 6) & 0x07FF);
					sbus_channels[15] = ((sbus_buffer[21] >> 5 | sbus_buffer[22] << 3) & 0x07FF);

					printf("CH1:%d | CH2:%d | CH3:%d | CH4:%d | CH5:%d | CH6:%d | CH7:%d | CH8:%d | CH9:%d | CH10:%d\r\n",
							sbus_channels[0], sbus_channels[1], sbus_channels[2], sbus_channels[3],
							sbus_channels[4], sbus_channels[5], sbus_channels[6], sbus_channels[7],
							sbus_channels[8], sbus_channels[9]);
				}
				else {
					printf("HAL no OK sur octets 1-24, timeout?\r\n");
				}
			}
			else {
				printf("Pas un octet de debut de trame.\r\n");
				continue;
			}
		}
		else {
			printf("HAL no OK sur octet 0, timeout?\r\n");
		}

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

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

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

static void MX_USART3_UART_Init(void) {
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 100000;
	huart3.Init.WordLength = UART_WORDLENGTH_9B;
	huart3.Init.StopBits = UART_STOPBITS_2;
	huart3.Init.Parity = UART_PARITY_EVEN;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&huart3) != HAL_OK) {
		Error_Handler();
	}
}

static void MX_USART2_UART_Init(void) {
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	HAL_UART_Init(&huart2);
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
