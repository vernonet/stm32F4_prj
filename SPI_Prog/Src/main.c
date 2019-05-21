/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */
#include "stm32f4_discovery.h"
#include "usbd_storage.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

//#define NOT_DEBUG   //enable readout protections
#include "chip_drv.h"
#include "flashchips.h"
#include "Driver_SPI.h"
#include "spi.h"


extern uint8_t Wr_Protect;
volatile uint8_t complet=0, error = 0;
CRC_HandleTypeDef   CrcHandle;
/* Used for storing CRC Value */
__IO uint32_t CRCValue_actual =  0;  //calculated after write flash
__IO uint32_t CRCValue_nominal = 0;  //calculated before write flash
extern int32_t file_size;
//extern IWDG_HandleTypeDef hiwdg;
extern TIM_HandleTypeDef htim6;
uint8_t crc_buf[0x200] __attribute__ ((aligned (4)));
extern const struct flashchip * flschip;
extern unsigned char boot_sec[]; 
extern const struct flashchip flashchips[];
volatile uint32_t blink= 2;
uint32_t spi_spd[6] = {0,1313,2625,5250,10500,21000};  //spi speed in KHz for SPI2

/* SPI Driver */
#define _SPI_Driver_(n)  Driver_SPI##n
#define  SPI_Driver_(n)  _SPI_Driver_(n)
extern ARM_DRIVER_SPI     SPI_Driver_(DRIVER_SPI_NUM);
#define ptrSPI          (&SPI_Driver_(DRIVER_SPI_NUM))
#define DUR_PULSE       (200/10)                     //200ms
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void Delay_first (volatile uint32_t time);
void SystemClock_Deinit(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

 /* IWDG init function */

//SPI speed, one blink - 1313KHz....five blinks - 21000KHz
//press key to select
uint32_t set_spi_speed (void) {  //return ARM_DRIVER_ERROR, ARM_DRIVER_OK
	uint8_t i=1, c, t;
	int32_t status;
	
	BSP_LED_Off(LED4);
	HAL_Delay(1000);
	
	while (1){
		  c=0;
		  t=DUR_PULSE;
		  while ((c>>1)<i) { 
				if (t-- == 0) {BSP_LED_Toggle(LED4); t = DUR_PULSE; c++;}  //pulse & pause duration 200ms.
				HAL_Delay(9);
				if (BSP_PB_GetState(BUTTON_KEY) == 1) {
					 BSP_LED_Off(LED4);
					 status = ptrSPI->Control(ARM_SPI_SET_BUS_SPEED, spi_spd[i]*1000);
					 return status;
				} 
			}		  
			t=DUR_PULSE*3;
			while (t-->0) {     //pause duration 600ms.
			 if (BSP_PB_GetState(BUTTON_KEY) == 1) {
				  status = ptrSPI->Control(ARM_SPI_SET_BUS_SPEED, spi_spd[i]*1000);
			    return status;
			 }
			 HAL_Delay(9);
			}
			if (i++>sizeof(spi_spd)/sizeof(spi_spd[0]) - 2) i=1;
			}
	
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	
	
  BSP_LED_Init(LED3);	BSP_LED_Init(LED4);BSP_LED_Init(LED5);BSP_LED_Init(LED6);
	//DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_TIM6_STOP;  //stop timer when debugging
	 /* Initialize User Button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
	//Wr_Protect = 1;
	SPI_UsrLog("\033[2J");                           //clear screen
	SPI_UsrLog(" In base %d flashchips\n", flashchips_in_base());
	HAL_Delay(500);
	if (Initialize(NULL) == ARM_DRIVER_OK) {     //init SPI2 
		 PowerControl(ARM_POWER_FULL);
		//if (flschip){
		 if ((flschip) && !(set_spi_speed())) {
		 //boot_sec[20] = (flschip->total_size*1024/STORAGE_BLK_SIZ) >> 8;              //NumberOfSectors16
		 boot_sec[32] = ((flschip->total_size*1024/STORAGE_BLK_SIZ) & 0xFF) + FAT_FILE_DATA_BLK; //NumberOfSectors32 
		 boot_sec[33] = ((flschip->total_size*1024/STORAGE_BLK_SIZ) >>  8) & 0xFF;      //NumberOfSectors32
     boot_sec[34] = ((flschip->total_size*1024/STORAGE_BLK_SIZ) >> 16) & 0xFF;	    //NumberOfSectors32		 
		 while (1){
			if (blink-- == 0) {BSP_LED_Toggle(LED4); blink = 40;}
		  HAL_Delay(10);
			if (BSP_PB_GetState(BUTTON_KEY) == 1) {BSP_LED_Off(LED4); break; }
		 }			
		 if (EraseChip()) {              
		   Error_Handler();             //flash not erased
		  }
		 }	 
		 else Error_Handler();          //flash not identified   
	}
	if (flschip) {                    //flash identified	    
				BSP_LED_Off(LED4);
				HAL_Delay(500);
				//Wr_Protect = 0;            //allow write
				if (Prepare_FAT()) Error_Handler();				
				/* USER CODE END SysInit */

				/* Initialize all configured peripherals */
				MX_GPIO_Init();
				MX_USB_DEVICE_Init();
				/* USER CODE BEGIN 2 */
		
				/* USER CODE END 2 */

				/* Infinite loop */
				/* USER CODE BEGIN WHILE */
				while (1)
				{

				/* USER CODE END WHILE */
        if (complet)                       // if firmware update complet
					{ 
						HAL_Delay(10);
						MX_USB_DEVICE_DeInit();
						if ((file_size > STORAGE_BLK_SIZ) && (file_size <= (flschip->total_size*1024))) {
						volatile uint32_t adr=0, len=0;	
						while (adr < file_size) {
							if (file_size-adr > sizeof(crc_buf)) len =  sizeof(crc_buf);
							  else len = file_size-adr;
							ReadData(adr, crc_buf, len );//sizeof(crc_buf)
						  CRCValue_actual = CalcCRC32 (crc_buf, len, CRCValue_actual);
							adr += len;
						}
						if (!(CRCValue_nominal == CRCValue_actual) || (error)){
							Error_Handler();        //error CRC or any other error
						}
						else {
							while(1){
							BSP_LED_Toggle(LED4);   //no error
							HAL_Delay(500);
							}
						}
					}
						else Error_Handler();    //file size error
							
								
				}		
			}
	
}
	else   Error_Handler();             //flash not identified
		  
	 

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                               |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 1, 0);
}

void SystemClock_Deinit(void)
{
	__HAL_RCC_HSE_CONFIG(RCC_HSE_OFF)  ;
	 __HAL_RCC_PWR_CLK_DISABLE();
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_RESET);  //SET

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void Delay_first (volatile uint32_t time)
{
	
	while (time-->1)
	{
		__asm("nop");
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	SPI_UsrLog("\n\r ERROR -> %s %d", file, line);
	complet = 1;                                         
	error = 1;
  while(1){
			BSP_LED_Toggle(LED5);   
			HAL_Delay(100);
	}
  /* USER CODE END Error_Handler_Debug */
}
//#define USE_FULL_ASSERT
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	printf("\n\r ERROR -> %s %d", file, line);
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/*****************************END OF FILE*********************************/
