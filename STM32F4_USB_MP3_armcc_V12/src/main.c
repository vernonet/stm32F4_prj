/**
  ******************************************************************************
  * @file    Audio_playback_and_record/src/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "mp3dec.h"
#include "mp3common.h"
#include "Audio.h"
#include "stm32f4_discovery_accelerometer.h"

/** @addtogroup STM32F4-Discovery_Audio_Player_Recorder
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BUTTON			(GPIOA->IDR & GPIO_PIN_0)

/* Private variables ---------------------------------------------------------*/
//TIM_HandleTypeDef hTimLed;
//TIM_OC_InitTypeDef sConfigLed;

/* Counter for User button presses. Defined as external in waveplayer.c file */
__IO uint32_t PressCount = 0;
volatile uint32_t		time_var1, time_var2;

/* Wave Player Pause/Resume Status. Defined as external in waveplayer.c file */
__IO uint32_t PauseResumeStatus = IDLE_STATUS;   

/* Wave Player Pause/Resume Status. Defined as external in waveplayer.c file */
//__IO uint32_t PauseResumeStatus = IDLE_STATUS;   
                                                   
extern uint32_t AudioPlayStart;


//UART_HandleTypeDef UartHandle;


/* Capture Compare Register Value.
   Defined as external in stm32f4xx_it.c file */
__IO uint16_t CCR1Val = 16826;              
                                            
extern __IO uint32_t LEDsState;

/* Save MEMS ID */
uint8_t MemsID = 0; 

__IO uint32_t CmdIndex = CMD_PLAY;
//__IO uint32_t PbPressCheck = 0;


FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
char USBDISKPath[4];          /* USB Host logical drive path */

//USBH_HandleTypeDef hUSBHost; /* USB Host handle */
USBH_HandleTypeDef hUSB_Host; /* USB Host handle */

MSC_ApplicationTypeDef AppliState = APPLICATION_IDLE;
static uint8_t  USBH_USR_ApplicationState = USBH_USR_FS_INIT;

// MP3 Variables
#define FILE_READ_BUFFER_SIZE   0x1000  //4096   //8192
MP3FrameInfo			mp3FrameInfo;
HMP3Decoder				hMP3Decoder;
FIL						file;
char					file_read_buffer[FILE_READ_BUFFER_SIZE] __attribute__((section ("BUFF")));
volatile int			bytes_left;
char					*read_ptr, button;
int16_t p_XYZ[3];
unsigned char AudioVol = 0x9a;

/* Private function prototypes -----------------------------------------------*/
//static void  TIM_LED_Config(void);
static void  SystemClock_Config(void);
static void  USBH_UserProcess  (USBH_HandleTypeDef *pHost, uint8_t vId);
static void  MSC_Application(void);
static void  COMMAND_AudioExecuteApplication(void);

// Private function prototypes
static void AudioCallback(void *context,int buffer);
static uint32_t Mp3ReadId3V2Tag(FIL* pInFile, char* pszArtist,
		uint32_t unArtistSize, char* pszTitle, uint32_t unTitleSize);
static void play_mp3(char* filename);
static FRESULT play_directory (char* path, unsigned char seek);


/* Private functions ---------------------------------------------------------*/
struct __FILE {int handle;/* Add whatever you need here */};

FILE __stdout;
FILE __stdin;



int fputc(int ch, FILE *f)
{
  ITM_SendChar(ch);
  return(ch);
}
/**
  * @brief  Main program.
  * @param  None
  * @retval None
*/

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void _InitializeAudio(unsigned int frek){
	switch(frek)
			{
			case 8000: InitializeAudio(Audio8000HzSettings);
					break;
			case 16000: InitializeAudio(Audio16000HzSettings);
					break;
			case 22050: InitializeAudio(Audio22050HzSettings);
					break;
			case 44100: InitializeAudio(Audio44100HzSettings);
					break;
			case 48000: InitializeAudio(Audio48000HzSettings);
					break;
			default:    InitializeAudio(Audio44100HzSettings);
			}           
}

static FRESULT play_directory (char* path, unsigned char seek) {
	FRESULT res;
	static FILINFO fno;
	DIR dir;
	char *fn; /* This function is assuming non-Unicode cfg. */
	char buffer[450];
	char buff[100];         //for directory
	
	int i;



	res = f_opendir(&dir, path); /* Open the directory */
	if (res == FR_OK) {
		for (;;) {
			res = f_readdir(&dir, &fno); /* Read a directory item */
			if (res != FR_OK || fno.fname[0] == 0) break; /* Break on error or end of dir */
			if (fno.fname[0] == '.') continue; /* Ignore dot entry */
			i = strlen(path);
			memcpy(&buff[0],path, i);
#if _USE_LFN
            //fn = fno.altname ? fno.altname : fno.fname;
						 fn = *fno.fname ? fno.fname : fno.altname;
#else
            fn = fno.fname;
#endif
			if (fno.fattrib & AM_DIR) { /* It is a directory */
				 sprintf(&buff[i], "/%s", fn);
         res = play_directory(&buff[0], seek);
         if (res != FR_OK) break;
         path[i] = 0;

			} else { /* It is a file. */
				sprintf(buffer, "%s/%s", path, fn);

				// Check if it is an mp3 file
				if (strcmp("mp3", get_filename_ext(buffer)) == 0) {

					// Skip "seek" number of mp3 files...
					if (seek) {
						seek--;
						continue;
					}
          //Delay(500);
					//printf("\n\rFile -> %s",buffer);
					play_mp3(buffer);
				}
			}
		}
	}

	return res;
}

static void play_mp3(char* filename) {
	unsigned int br, btr;
	FRESULT res;

	bytes_left = FILE_READ_BUFFER_SIZE;
	read_ptr = file_read_buffer;

	if (FR_OK == f_open(&file, filename, FA_OPEN_EXISTING | FA_READ)) {

		// Read ID3v2 Tag
		static char szArtist[120];
		static char szTitle[120];
		unsigned int cur_size , fullsize;
		char procent;
		static int16_t temp_buffer[0x3c0];
		int test, offs;
		
		
		//mp3FrameInfo.samprate = 0;
		
		fullsize = f_size(&file);
		Mp3ReadId3V2Tag(&file, szArtist, sizeof(szArtist), szTitle, sizeof(szTitle));
		printf("\n\r Song - %s  \n\r    Artist: %s",szTitle,szArtist);
		//printf("\n\r   Title :  %s",szTitle);

	
		// Fill buffer
		f_read(&file, file_read_buffer, FILE_READ_BUFFER_SIZE, &br);
		cur_size = FILE_READ_BUFFER_SIZE;

		// Play mp3
		hMP3Decoder = MP3InitDecoder();
		
		InitializeAudio(Audio44100HzSettings);
		SetAudioVolume(0);
		read_ptr = file_read_buffer;
		test = sizeof temp_buffer;
		offs = MP3FindSyncWord((unsigned char*)read_ptr, test);
	  read_ptr += offs;
		MP3Decode(hMP3Decoder, (unsigned char**)&read_ptr, (int*)&test, &temp_buffer[0], 0); //частота дискретизации
		StopAudio();
		read_ptr = file_read_buffer;
		MP3GetLastFrameInfo(hMP3Decoder, &mp3FrameInfo);
		_InitializeAudio(((MP3DecInfo *)hMP3Decoder)->samprate);    
		printf(" (%iHz", ((MP3DecInfo *)hMP3Decoder)->samprate);   //((MP3DecInfo *)hMP3Decoder)->samprate
		printf("  %ikbps)", ((MP3DecInfo *)hMP3Decoder)->bitrate/1000); 										
		printf("\n\r");
		SetAudioVolume(AudioVol);  //0xAF
		PlayAudioWithCallback(AudioCallback, 0);


		for(;;) {
			
			/*
			 * If past half of buffer, refill...
			 *
			 * When bytes_left changes, the audio callback has just been executed. This
			 * means that there should be enough time to copy the end of the buffer
			 * to the beginning and update the pointer before the next audio callback.
			 * Getting audio callbacks while the next part of the file is read from the
			 * file system should not cause problems.
			 */
			if (bytes_left < FILE_READ_BUFFER_SIZE / 4) {  //(bytes_left < (FILE_READ_BUFFER_SIZE / 2))
				BSP_ACCELERO_GetXYZ(&p_XYZ[0]);
			  if ((p_XYZ[0]> 200) && (AudioVol<0xB0)) AudioVol ++;  //регулировка громкости
			  if ((p_XYZ[0]<-200) && (AudioVol>0x50)) AudioVol --;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
				// Copy rest of data to beginning of read buffer
				memcpy(file_read_buffer, read_ptr, bytes_left);

				// Update read pointer for audio sampling
				read_ptr = file_read_buffer;

				// Read next part of file
				btr = FILE_READ_BUFFER_SIZE - bytes_left;
				res = f_read(&file, file_read_buffer + bytes_left, btr, &br);
				
				cur_size += btr;
				procent = cur_size * 100 / fullsize;
				printf("\r    playing - %3i",procent);
				printf("%%");    
				printf("   Volume - %3i", AudioVol);

				// Update the bytes left variable
				bytes_left = FILE_READ_BUFFER_SIZE;

				// Out of data or error or user button... Stop playback!
				if (br < btr || res != FR_OK || button) {				//BUTTON
					button = 0;
					StopAudio();

					// Re-initialize and set volume to avoid noise
					InitializeAudio(Audio44100HzSettings);
					SetAudioVolume(0);

					// Close currently open file
					f_close(&file);

					// Wait for user button release
					//while(BUTTON){};
          
					// Return to previous function
					return;
				}
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
				 if(PauseResumeStatus == PAUSE_STATUS)
         {
					/* Pause playing Wave */
					//StopAudio();
					 StopAudioDMA();
					// Re-initialize and set volume to avoid noise
					_InitializeAudio(((MP3DecInfo *)hMP3Decoder)->samprate);
					SetAudioVolume(0);
					PauseResumeStatus = IDLE_STATUS;
					while(1) {
						if(PauseResumeStatus == RESUME_STATUS)
							 {
								/* Resume playing Wave */				
								PauseResumeStatus = IDLE_STATUS;
								SetAudioVolume(0x9A);  //0xAF
								PlayAudioWithCallback(AudioCallback, 0);
								break;
							 }  
				   }
        }
				 SetAudioVolume(AudioVol);
			}
		}
	}
}

///*
// * Called by the SysTick interrupt
// */
//void TimingDelay_Decrement(void) {
//	if (time_var1) {
//		time_var1--;
//	}
//	time_var2++;
//}

///*
// * Delay a number of systick cycles (1ms)
// */
//void Delay(volatile uint32_t nTime) {
//	time_var1 = nTime;
//	while(time_var1){};
//}


/*
 * Called by the audio driver when it is time to provide data to
 * one of the audio buffers (while the other buffer is sent to the
 * CODEC using DMA). One mp3 frame is decoded at a time and
 * provided to the audio driver.
 */
static void AudioCallback(void *context, int buffer) {
	static int16_t audio_buffer0[0x1000];  // __attribute__((section ("BUFF")));
	static int16_t audio_buffer1[0x1000];  // __attribute__((section ("BUFF")));

	int offset, err;
	int outOfData = 0;

	int16_t *samples;
	if (buffer) {
		samples = audio_buffer0;
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	} else {
		samples = audio_buffer1;
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	}
	/* Toggle LED  */
     GPIOD->ODR ^= GPIO_PIN_13;

	offset = MP3FindSyncWord((unsigned char*)read_ptr, bytes_left);
	bytes_left -= offset;
	read_ptr += offset;

	//BSP_LED_On(LED4);
	err = MP3Decode(hMP3Decoder, (unsigned char**)&read_ptr, (int*)&bytes_left, samples, 0);
	//BSP_LED_Off(LED4);

	if (err) {
		/* error occurred */
		switch (err) {
		case ERR_MP3_INDATA_UNDERFLOW:
			outOfData = 1;
			break;
		case ERR_MP3_MAINDATA_UNDERFLOW:
			/* do nothing - next call to decode will provide more mainData */
			break;
		case ERR_MP3_FREE_BITRATE_SYNC:
		default:
			outOfData = 1;
			break;
		}
	} else {
		// no error
		MP3GetLastFrameInfo(hMP3Decoder, &mp3FrameInfo);

		// Duplicate data in case of mono to maintain playback speed
		if (mp3FrameInfo.nChans == 1) {
			for(int i = mp3FrameInfo.outputSamps;i >= 0;i--) 	{
				samples[2 * i]=samples[i];
				samples[2 * i + 1]=samples[i];
			}
			mp3FrameInfo.outputSamps *= 2;
		}
	}

	if (!outOfData) {
		ProvideAudioBuffer(samples, mp3FrameInfo.outputSamps);
	}
}



int main(void)
{
//	uint8_t ctrl;
//	RCC_ClocksTypeDef		RCC_Clocks;
  /* STM32F4xx HAL library initialization:
  - Configure the Flash prefetch, instruction and Data caches
  - Configure the Systick to generate an interrupt each 1 msec
  - Set NVIC Group Priority to 4
  - Global MSP (MCU Support Package) initialization
  */
	HAL_Init();
	 
  /* Initialize LEDs mounted on STM32F4-Discovery board */
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);
  
  /* Configure the system clock */
  SystemClock_Config();
	
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);   //BUTTON_MODE_EXTI   GPIO
	
	
	/* Initialize MEMS Accelerometer mounted on STM32F4-Discovery board */
  if(BSP_ACCELERO_Init() != ACCELERO_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  MemsID = BSP_ACCELERO_ReadID();
	/* MEMS Accelerometer configure to manage PAUSE, RESUME operations */
  BSP_ACCELERO_Click_ITConfig();
	 if (MemsID == MEMS_LIS302DL)
  {
    /* Read click and status registers*/
    BSP_ACCELERO_Click_ITClear();  
  }
	
	

//	UartHandle.Instance          = USART2;  
//  UartHandle.Init.BaudRate     = 9600;
//  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
//  UartHandle.Init.StopBits     = UART_STOPBITS_1;
//  UartHandle.Init.Parity       = UART_PARITY_NONE;
//  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
//  UartHandle.Init.Mode         = UART_MODE_TX_RX;
//  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
  
 // SysTick interrupt each 1ms
	//(RCC_GetClocksFreq(&RCC_Clocks);)
	//HAL_RCC_GetHCLKFreq
	
	//HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
	
	

  
  
  /*##-1- Link the USB Host disk I/O driver ##################################*/
  if(FATFS_LinkDriver(&USBH_Driver, USBDISKPath) == 0)
  { 
    /*##-2- Init Host Library ################################################*/
    USBH_Init(&hUSB_Host, USBH_UserProcess, 0);
    
    /*##-3- Add Supported Class ##############################################*/
    USBH_RegisterClass(&hUSB_Host, USBH_MSC_CLASS);
    
    /*##-4- Start Host Process ###############################################*/
    USBH_Start(&hUSB_Host);
    
    /* Run Application (Blocking mode)*/
    while (1)
    {
      switch(AppliState)
      {
      case APPLICATION_START:
        MSC_Application();
        break;      
      case APPLICATION_IDLE:
      default:
        break;      
      }
      
      /* USBH_Background Process */
      USBH_Process(&hUSB_Host);
    }
  }
  while (1) {}
}

/**
  * @brief  User Process
  * @param  phost: Host Handle
  * @param  id: Host Library user message ID
  * @retval none
  */
static void USBH_UserProcess (USBH_HandleTypeDef *pHost, uint8_t vId)
{  
  switch (vId)
  { 
  case HOST_USER_SELECT_CONFIGURATION:
    break;
    
  case HOST_USER_DISCONNECTION:
    //WavePlayer_CallBack();
    AppliState = APPLICATION_IDLE;
    f_mount(NULL, (TCHAR const*)"", 0);          
    break;
    
  case HOST_USER_CLASS_ACTIVE:
    AppliState = APPLICATION_START;
    break;
    
  case HOST_USER_CONNECTION:
    break;
    
  default:
    break; 
  }
}

/**
  * @brief  Main routine for Mass storage application
  * @param  None
  * @retval none
  */
static void MSC_Application(void)
{
  switch (USBH_USR_ApplicationState)
  {
  case USBH_USR_AUDIO:
    /* Go to Audio menu */
    COMMAND_AudioExecuteApplication();
    
    /* Set user initialization flag */
    USBH_USR_ApplicationState = USBH_USR_FS_INIT;
    break;
    
  case USBH_USR_FS_INIT:
    /* Initialises the File System */
    if (f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0 ) != FR_OK ) 
    {
      /* efs initialisation fails*/
      Error_Handler();
    }
    
    /* Go to menu */
    USBH_USR_ApplicationState = USBH_USR_AUDIO;
    break;
    
  default:
    break;
  }
}

/**
  * @brief  COMMAND_AudioExecuteApplication.
  * @param  None
  * @retval None
  */
static void COMMAND_AudioExecuteApplication(void)
{
  /* Execute the command switch the command index */
  switch (CmdIndex)
  {
  /* Start Playing from USB Flash memory */
  case CMD_PLAY:
    //if (RepeatState == REPEAT_ON)
      //WavePlayerStart();
	  printf("\033[2J");
	play_directory("0:", 0);  //0:
    break;
    /* Start Recording in USB Flash memory */ 
  case CMD_RECORD:
   // RepeatState = REPEAT_ON;
   // WaveRecorderProcess();
    break;  
  default:
    break;
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;//6; //
  RCC_OscInitStruct.PLL.PLLN = 336;//324; //336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;//9; //7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;//RCC_HCLK_DIV8;//  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;//RCC_HCLK_DIV4;//RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
//	__HAL_RCC_PLL_DISABLE();
//	/* Configure the main PLL */
//		RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) | (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);
//	__HAL_RCC_PLL_ENABLE();
//	/* Wait till the main PLL is ready */
//		while((RCC->CR & RCC_CR_PLLRDY) == 0)
//		{
//		}
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* Turn LED3 on */
  BSP_LED_On(LED6);
	BSP_LED_Off(LED3);
	BSP_LED_Off(LED4);
	BSP_LED_Off(LED5);
  while(1)
  {
  }
}

/*
 * Dummy function to avoid compiler error
 */
void _init() {

}

/*
 * Taken from
 * http://www.mikrocontroller.net/topic/252319
 */
static uint32_t Mp3ReadId3V2Text(FIL* pInFile, uint32_t unDataLen, char* pszBuffer, uint32_t unBufferSize)
{
	UINT unRead = 0;
	BYTE byEncoding = 0;
	if((f_read(pInFile, &byEncoding, 1, &unRead) == FR_OK) && (unRead == 1))
	{
		unDataLen--;
		if(unDataLen <= (unBufferSize - 1))
		{
			if((f_read(pInFile, pszBuffer, unDataLen, &unRead) == FR_OK) ||
					(unRead == unDataLen))
			{
				if(byEncoding == 0)
				{
					// ISO-8859-1 multibyte
					// just add a terminating zero
					pszBuffer[unDataLen] = 0;
				}
				else if(byEncoding == 1)
				{
					// UTF16LE unicode
					uint32_t r = 0;
					uint32_t w = 0;
					if((unDataLen > 2) && ((uint8_t)pszBuffer[0] == 0xFF) && ((uint8_t)pszBuffer[1] == 0xFE))
					{
						// ignore BOM, assume LE
						r = 2;
					}
					for(; r < unDataLen; r += 2, w += 1)
					{
						// should be acceptable for 7 bit ascii
						pszBuffer[w] = pszBuffer[r];
					}
					pszBuffer[w] = 0;
				}
			}
			else
			{
				return 1;
			}
		}
		else
		{
			// we won't read a partial text
			if(f_lseek(pInFile, f_tell(pInFile) + unDataLen) != FR_OK)
			{
				return 1;
			}
		}
	}
	else
	{
		return 1;
	}
	return 0;
}

static uint32_t Mp3ReadId3V2Tag(FIL* pInFile, char* pszArtist, uint32_t unArtistSize, char* pszTitle, uint32_t unTitleSize)
{
	pszArtist[0] = 0;
	pszTitle[0] = 0;

	BYTE id3hd[10];
	UINT unRead = 0;
	if((f_read(pInFile, id3hd, 10, &unRead) != FR_OK) || (unRead != 10))
	{
		return 1;
	}
	else
	{
		uint32_t unSkip = 0;
		if((unRead == 10) &&
				(id3hd[0] == 'I') &&
				(id3hd[1] == 'D') &&
				(id3hd[2] == '3'))
		{
			unSkip += 10;
			unSkip = ((id3hd[6] & 0x7f) << 21) | ((id3hd[7] & 0x7f) << 14) | ((id3hd[8] & 0x7f) << 7) | (id3hd[9] & 0x7f);

			// try to get some information from the tag
			// skip the extended header, if present
			uint8_t unVersion = id3hd[3];
			if(id3hd[5] & 0x40)
			{
				BYTE exhd[4];
				f_read(pInFile, exhd, 4, &unRead);
				size_t unExHdrSkip = ((exhd[0] & 0x7f) << 21) | ((exhd[1] & 0x7f) << 14) | ((exhd[2] & 0x7f) << 7) | (exhd[3] & 0x7f);
				unExHdrSkip -= 4;
				if(f_lseek(pInFile, f_tell(pInFile) + unExHdrSkip) != FR_OK)
				{
					return 1;
				}
			}
			uint32_t nFramesToRead = 2;
			while(nFramesToRead > 0)
			{
				char frhd[10];
				if((f_read(pInFile, frhd, 10, &unRead) != FR_OK) || (unRead != 10))
				{
					return 1;
				}
				if((frhd[0] == 0) || (strncmp(frhd, "3DI", 3) == 0))
				{
					break;
				}
				char szFrameId[5] = {0, 0, 0, 0, 0};
				memcpy(szFrameId, frhd, 4);
				uint32_t unFrameSize = 0;
				uint32_t i = 0;
				for(; i < 4; i++)
				{
					if(unVersion == 3)
					{
						// ID3v2.3
						unFrameSize <<= 8;
						unFrameSize += frhd[i + 4];
					}
					if(unVersion == 4)
					{
						// ID3v2.4
						unFrameSize <<= 7;
						unFrameSize += frhd[i + 4] & 0x7F;
					}
				}

				if(strcmp(szFrameId, "TPE1") == 0)
				{
					// artist
					if(Mp3ReadId3V2Text(pInFile, unFrameSize, pszArtist, unArtistSize) != 0)
					{
						break;
					}
					nFramesToRead--;
				}
				else if(strcmp(szFrameId, "TIT2") == 0)
				{
					// title
					if(Mp3ReadId3V2Text(pInFile, unFrameSize, pszTitle, unTitleSize) != 0)
					{
						break;
					}
					nFramesToRead--;
				}
				else
				{
					if(f_lseek(pInFile, f_tell(pInFile) + unFrameSize) != FR_OK)
					{
						return 1;
					}
				}
			}
		}
		if(f_lseek(pInFile, unSkip) != FR_OK)
		{
			return 1;
		}
	}

	return 0;
}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{ 
 
	if(GPIO_Pin == GPIO_PIN_0)               //key press
  {
		HAL_Delay(200); 
    button = 1;
    PauseResumeStatus = RESUME_STATUS;
  	__HAL_GPIO_EXTI_CLEAR_IT(EXTI_Line1);  //clear pending bit (Accelero)
		__HAL_GPIO_EXTI_CLEAR_IT(EXTI_Line0);
  }
  if(GPIO_Pin == GPIO_PIN_1)               //Accelerometer click
  {
    if (PressCount == 1)
    {
      /* Resume playing Wave status */
      PauseResumeStatus = RESUME_STATUS;
      PressCount = 0;
    }
    else
    {
      /* Pause playing Wave status */
      PauseResumeStatus = PAUSE_STATUS;
      PressCount = 1;
    }
		//__HAL_GPIO_EXTI_CLEAR_FLAG(EXTI_Line0);
  }
	//__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);  //добавил чтобы не перескакивало треки
	//__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_Pin);
	// HAL_NVIC_EnableIRQ((IRQn_Type)(KEY_BUTTON_EXTI_IRQn));
	if (MemsID == MEMS_LIS302DL)
	{
		/* Read click and status registers*/
		BSP_ACCELERO_Click_ITClear();  
	}
} 

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
