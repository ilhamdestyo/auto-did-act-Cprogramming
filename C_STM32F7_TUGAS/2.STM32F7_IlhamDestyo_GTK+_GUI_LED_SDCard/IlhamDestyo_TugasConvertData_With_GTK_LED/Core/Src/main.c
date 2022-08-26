/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
FATFS FatFs;   /* Work area (filesystem object) for logical drive */
TS_StateTypeDef  ts;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

CRC_HandleTypeDef hcrc;

DMA2D_HandleTypeDef hdma2d;

LTDC_HandleTypeDef hltdc;

SD_HandleTypeDef hsd1;

UART_HandleTypeDef huart1;

SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN PV */
FRESULT res; //FatFS result var
FATFS SDFatFs; /* Work area (filesystem object) for logical drive */
FIL MyFile; //File object
char buffrd[30]; //buffer read
char SdPath[10];
char* data ;
char *led = "INACTIVE";
char *text = "";
int flag = 0;
uint32_t byteswritten, bytesread;

int datainput_1[100],datainput_2[100],datainput_3[100];
int number_data;
char *txtResult = NULL;
char datain1[100],dataraw[100][100],dataprint[100][100];

typedef struct{
 char **Input1;
 char **Input2;
 char **Input3;
 int ndata;
} dataInput;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_LTDC_Init(void);
static void MX_SDMMC1_SD_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void Soal1();
void Soal2();
void Soal3();
void Soal4();
void Soal5();
void Process();
void Error1(void);
void Error2(void);
enum _bool {
	false = 0,
	true = 1
};
typedef enum _bool boolean;

char* replaceWordInString(const char* s, const char* oldW, const char* newW);
char *trim(char *s);
char *shift_trim(char *s);
char *IntToStr(int x);
void read_file(char *namafile);
void get_data_from_rawdata();
void save_data_file(char *namafile, dataInput datatulis);
int c_round(double x);
double c_modulus(double a,double b);
int isGanjil(int num);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t Rx_data[64];

uint8_t buffer[64];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_SDMMC1_SD_Init();
  MX_USART1_UART_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
  BSP_SDRAM_Init(); /* Initializes the SDRAM device */
   __HAL_RCC_CRC_CLK_ENABLE(); /* Enable the CRC Module */
   //
   BSP_TS_Init(480, 272);

   BSP_LCD_Init();	// inisialisasi LCD
   BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS); // inisialisasi layer
   BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER); // set layer

   BSP_LCD_Clear(LCD_COLOR_DARKGREEN); // set clear lcd color black
   BSP_LCD_SetFont(&LCD_DEFAULT_FONT); // set font lcd
   BSP_LCD_SetTextColor(LCD_COLOR_WHITE);


   //SDCard Init
     res = BSP_SD_Init();
     if(res != FR_OK){
    	 BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
    	 BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    	 BSP_LCD_SetTextColor(LCD_COLOR_LIGHTYELLOW);
    	 BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"SDCARD NOT DETECTED!!!", CENTER_MODE);
    	 BSP_LCD_DisplayStringAt(0, 130, (uint8_t *)"Please insert your SDCard", CENTER_MODE);
    	 Error1(); // function error1
   	}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // get data from UART
	  HAL_UART_Receive(&huart1, (uint8_t *)&Rx_data, sizeof(Rx_data), 100);
	  if(Rx_data[0] != '\0'){	//If rxdata have a value
		 memset(buffer, '\0', 64);	//clear buffer
		 memcpy(buffer, Rx_data, 64);	//copy data to buffer after that
		 BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
		 BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
		 if(strlen(buffer) > 1 ){//If buffer > 1 (for entry text)
			 text = buffer;
			 BSP_LCD_DisplayStringAt(0, 150, (uint8_t *)text, CENTER_MODE);
						  }
		 else if (buffer[0] == 'a'){	//if buffer contain a
			  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_SET);
			  led = "ACTIVE";
		  }
		  else if(buffer[0] == 'b'){	//if buffer contain b
			  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_RESET);
			  led = "INACTIVE";
		  }else if(buffer[0] == 'H'){//if buffer contain H
			  text = "Hello World!";
		  }
		  else if(buffer[0] == '1'){//if buffer contain 1
			Soal1(); //for soal1 condition
		  }
		  else if(buffer[0] == '2'){//if buffer contain 2
			Soal2(); //for soal2 condition
		  }
		  else if(buffer[0] == '3'){//if buffer contain 3
			Soal3(); //for soal3 condition
		  }
		  else if(buffer[0] == '4'){//if buffer contain 4
			Soal4(); //for soal4 condition
		  }
		  else if(buffer[0] == '5'){//if buffer contain 5
			Soal5(); //for soal5 condition
		  }

	  }
	  BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
	  BSP_LCD_DisplayStringAt(-60, 50, (uint8_t *)"LED STATUS:", CENTER_MODE);
	  BSP_LCD_DisplayStringAt(110,50, (uint8_t *)led, CENTER_MODE);
	  BSP_LCD_DisplayStringAt(0, 150, (uint8_t *)text, CENTER_MODE);
	  memset(Rx_data, '\0', 64);	//set clear Rx_data
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_SDMMC1
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 384;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV8;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_8;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};
  LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 7;
  hltdc.Init.VerticalSync = 3;
  hltdc.Init.AccumulatedHBP = 14;
  hltdc.Init.AccumulatedVBP = 5;
  hltdc.Init.AccumulatedActiveW = 494;
  hltdc.Init.AccumulatedActiveH = 277;
  hltdc.Init.TotalWidth = 500;
  hltdc.Init.TotalHeigh = 279;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 0;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 0;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg.Alpha = 0;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 0;
  pLayerCfg.ImageHeight = 0;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg1.WindowX0 = 0;
  pLayerCfg1.WindowX1 = 0;
  pLayerCfg1.WindowY0 = 0;
  pLayerCfg1.WindowY1 = 0;
  pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg1.Alpha = 0;
  pLayerCfg1.Alpha0 = 0;
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg1.FBStartAdress = 0;
  pLayerCfg1.ImageWidth = 0;
  pLayerCfg1.ImageHeight = 0;
  pLayerCfg1.Backcolor.Blue = 0;
  pLayerCfg1.Backcolor.Green = 0;
  pLayerCfg1.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief SDMMC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDMMC1_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC1_Init 0 */

  /* USER CODE END SDMMC1_Init 0 */

  /* USER CODE BEGIN SDMMC1_Init 1 */

  /* USER CODE END SDMMC1_Init 1 */
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockBypass = SDMMC_CLOCK_BYPASS_DISABLE;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_1B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 0;
  /* USER CODE BEGIN SDMMC1_Init 2 */

  /* USER CODE END SDMMC1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_SDRAM_TimingTypeDef SdramTiming = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_1;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_DISABLE;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 16;
  SdramTiming.ExitSelfRefreshDelay = 16;
  SdramTiming.SelfRefreshTime = 16;
  SdramTiming.RowCycleDelay = 16;
  SdramTiming.WriteRecoveryTime = 16;
  SdramTiming.RPDelay = 16;
  SdramTiming.RCDDelay = 16;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */

  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin : PI3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/* ========================FUNGSI CONVERT DATA SOAL 1-5============================ */
// Function Soal1
void Soal1(){
	read_file("data.txt");	// membaca file "data.txt"
	get_data_from_rawdata();	// mengambil data dari rawdata
	dataInput dataBaca;	// struct variabel
	dataBaca.Input1 = calloc(100,sizeof(char));	// alokasi memory
	dataBaca.Input2 = calloc(100,sizeof(char));
	dataBaca.Input3 = calloc(100,sizeof(char));

	for(int i=1;i<number_data+1;i++){		// Perulangan sebanyak number_data+1
		dataBaca.Input1[i]=IntToStr(datainput_1[i]); // Konversi integer ke string dan dimasukkan ke struct dataBaca
		dataBaca.Input2[i]=IntToStr(datainput_2[i]);
		dataBaca.Input3[i]=IntToStr(datainput_3[i]);
	}
	for (int k = 1; k<= 4; k++){ // pengulangan sebanyak k <=4
		data = replaceWordInString(dataraw[k],","," ");	// mengubah charakter "," menjadi " "
		strcpy(dataraw[k], data);	// copy data string data ke dataraw[index ke-k]
	}

	dataBaca.ndata = number_data;	//isi value dengan number_data

	save_data_file("data_copy1.txt",dataBaca);	// save file dengan nama "data_copy1.txt"

	free(dataBaca.Input1),dataBaca.Input1=NULL;	// Membebaskan memory pada struct dataBaca
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;

	Process();	// Function display process
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN);	// set clear lcd color black
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);	// set back text color black
	BSP_LCD_DisplayStringAt(0, 80, (uint8_t *)dataraw[1], CENTER_MODE);		// display dataraw[index-1]
	BSP_LCD_DisplayStringAt(0, 110, (uint8_t *)dataraw[2], CENTER_MODE);	// display dataraw[index-2]
	BSP_LCD_DisplayStringAt(0, 140, (uint8_t *)dataraw[3], CENTER_MODE);	// display dataraw[index-3]
	BSP_LCD_DisplayStringAt(0, 170, (uint8_t *)dataraw[4], CENTER_MODE);	// display dataraw[index-4]

	HAL_Delay(2000);	// delay selama 2 detik
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN); // set clear display
}
// Function Soal2
void Soal2(){
	read_file("data.txt");	// membaca file "data.txt"
	get_data_from_rawdata();	// mengambil data dari rawdata
	dataInput dataBaca; // struct variabel
	dataBaca.Input1 = calloc(100,sizeof(char));	// alokasi memory
	dataBaca.Input2 = calloc(100,sizeof(char));
	dataBaca.Input3 = calloc(100,sizeof(char));

	for(int i=1;i<number_data+1;i++){		// Perulangan sebanyak number_data+1
		dataBaca.Input1[i]=IntToStr(datainput_1[i]); // Konversi integer ke string dan dimasukkan ke struct dataBaca
		dataBaca.Input2[i]= ",";	// mengubah data menjadi ","
		dataBaca.Input3[i]=IntToStr(datainput_3[i]);
	}

	if(flag == 0){	// jika flag == 0
		for (int k = 1; k<= 4; k++){	// pengulangan sebanyak k <= 4
			strcat(dataprint[k], dataBaca.Input1[k]);	// menambahkan data string pada dataprint[k]
			strcat(dataprint[k], dataBaca.Input2[k]);
			strcat(dataprint[k], dataBaca.Input3[k]);
		}
	}
	flag = 1;	//flag = 1
	dataBaca.ndata = number_data;	//isi value dengan number_data

	save_data_file("data_copy2.txt",dataBaca);	// save file dengan nama "data_copy2.txt"

	free(dataBaca.Input1),dataBaca.Input1=NULL;	// Membebaskan memory pada struct dataBaca
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;

	Process();	// Function display process
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
	BSP_LCD_DisplayStringAt(0, 80, (uint8_t *)dataprint[1], CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 110, (uint8_t *)dataprint[2], CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 140, (uint8_t *)dataprint[3], CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 170, (uint8_t *)dataprint[4], CENTER_MODE);
	HAL_Delay(2000);
	BSP_LCD_Clear(LCD_COLOR_BLACK);
}
// Function Soal3
void Soal3(){
	read_file("data.txt");	// membaca file "data.txt"
	get_data_from_rawdata();	// mengambil data dari rawdata
	dataInput dataBaca;	// struct variabel
	dataBaca.Input1 = calloc(100,sizeof(char));	// alokasi memory
	dataBaca.Input2 = calloc(100,sizeof(char));
	dataBaca.Input3 = calloc(100,sizeof(char));

	int count1=0;	// Variabel integer awal 0
	int count2=0;	// Variabel integer awal 0

	for(int i=1;i<number_data+1;i++){		// Perulangan sebanyak number_data+1
		if(isGanjil(datainput_1[i])==0){	// Jika modulus datainput_1 = 0 (Genap),maka count1 + 1
			count1++;
			dataBaca.Input1[count1] = IntToStr(datainput_1[i]);	// Mengisi Struct dataBaca.Input1 dengan datainput_1
		}
		if(isGanjil(datainput_2[i])==0){	// Jika modulus datainput_2 = 0 (Genap),maka count1 + 1
			count1++;
			dataBaca.Input1[count1] = IntToStr(datainput_2[i]);	// Mengisi Struct dataBaca.Input1 dengan datainput_2
		}
		if(isGanjil(datainput_3[i])==0){	// Jika modulus datainput_3 = 0 (Genap),maka count1 + 1
			count1++;
			dataBaca.Input1[count1] = IntToStr(datainput_3[i]);	// Mengisi Struct dataBaca.Input1 dengan datainput_3
		}

		if(isGanjil(datainput_1[i])==1){	// Jika modulus datainput_1 = 1 (Ganjil),maka count2 + 1
			count2++;
			dataBaca.Input2[count2] = IntToStr(datainput_1[i]);	// Mengisi Struct dataBaca.Input2 dengan datainput_1
		}
		if(isGanjil(datainput_2[i])==1){	// Jika modulus datainput_2 = 1 (Ganjil),maka count2 + 1
			count2++;
			dataBaca.Input2[count2] = IntToStr(datainput_2[i]);	// Mengisi Struct dataBaca.Input2 dengan datainput_2
		}
		if(isGanjil(datainput_3[i])==1){	// Jika modulus datainput_3 = 1 (Ganjil),maka count2 + 1
			count2++;
			dataBaca.Input2[count2] = IntToStr(datainput_3[i]);	// Mengisi Struct dataBaca.Input2 dengan datainput_3
		}
	}

	dataBaca.ndata = (count1 > count2 ? count1 : count2); // Mengisi data jika count1 lebih besar dari count2,maka hasilnya count1,

	for(int i=1;i<dataBaca.ndata+1;i++){	// Mengulang sebanyak dataBaca.ndata+1
		if(dataBaca.Input1[i]==NULL){dataBaca.Input1[i]="";} // Jika dataBaca.Input1==NULL , maka berisi ""
		if(dataBaca.Input2[i]==NULL){dataBaca.Input2[i]="";} // Jika dataBaca.Input2==NULL , maka berisi ""
		dataBaca.Input3[i]="";					// Mengisi dataBaca.Input3 dengan ""
	}

	save_data_file("data_copy3.txt",dataBaca);	// save file dengan nama "data_copy3.txt"

	Process();	// Function display process
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
	int j=30;	// set variabel
	for(int i = 1; i<=7;i++){ // pengulangan untuk cetak display sesuai data i dan j
		BSP_LCD_DisplayStringAt(-10, j, (uint8_t *)dataBaca.Input1[i], CENTER_MODE);
		BSP_LCD_DisplayStringAt(10, j, (uint8_t *)dataBaca.Input2[i], CENTER_MODE);
		j = j + 30;
	}

	free(dataBaca.Input1),dataBaca.Input1=NULL;	// Membebaskan memory pada struct dataBaca
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;


	HAL_Delay(2000);
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
}
// Function Soal4
void Soal4(){
	read_file("data.txt");	// membaca file "data.txt"
	get_data_from_rawdata();	// mengambil data dari rawdata
	dataInput dataBaca;	// struct variabel
	dataBaca.Input1 = calloc(100,sizeof(char));	// alokasi memory
	dataBaca.Input2 = calloc(100,sizeof(char));
	dataBaca.Input3 = calloc(100,sizeof(char));

	int count=0;
	for(int i=1;i<number_data+1;i++){		// Perulangan sebanyak number_data+1
		count++;											// count + 1
		dataBaca.Input1[count]=IntToStr(datainput_1[i]);	// Mengisi struct dataBaca.Input1 dengan datainput_1
		count++;											// count + 1
		dataBaca.Input1[count]=IntToStr(datainput_2[i]);	// Mengisi struct dataBaca.Input1 dengan datainput_2
		count++;											// count + 1
		dataBaca.Input1[count]=IntToStr(datainput_3[i]);	// Mengisi struct dataBaca.Input1 dengan datainput_3
	}

	dataBaca.ndata = count;

	for(int i=1;i<dataBaca.ndata+1;i++){	// Mengulang sebanyak dataBaca.ndata+1
		if(dataBaca.Input1[i]==NULL){dataBaca.Input1[i]="";}	// Jika dataBaca.Input1==NULL , maka berisi ""
			dataBaca.Input2[i]="";	// Mengisi dataBaca.Input2 dengan ""
			dataBaca.Input3[i]="";	// Mengisi dataBaca.Input3 dengan ""
	}

	save_data_file("data_copy4.txt",dataBaca);	// save file dengan nama "data_copy4.txt"
	Process();
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);

	int j=20;
	for(int i = 1; i<=12;i++){
		BSP_LCD_DisplayStringAt(0, j, (uint8_t *)dataBaca.Input1[i], CENTER_MODE);
		j = j + 20;
	}

	free(dataBaca.Input1),dataBaca.Input1=NULL;	// Membebaskan memory pada struct dataBaca
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;

	HAL_Delay(2000);
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
}
// Function Soal5
void Soal5(){
	read_file("data.txt");	// membaca file "data.txt"
	get_data_from_rawdata();	// mengambil data dari rawdata
	dataInput dataBaca;	// struct variabel
	dataBaca.Input1 = calloc(100,sizeof(char));	// alokasi memory
	dataBaca.Input2 = calloc(100,sizeof(char));
	dataBaca.Input3 = calloc(100,sizeof(char));

	int count=0;
	for(int i=1;i<number_data+1;i++){		// Perulangan sebanyak number_data+1
		count++;											// count + 1
		dataBaca.Input1[count]=IntToStr(datainput_1[i]);	// Mengisi struct dataBaca.Input1 dengan datainput_1
		count++;											// count + 1
		dataBaca.Input1[count]=IntToStr(datainput_2[i]);	// Mengisi struct dataBaca.Input1 dengan datainput_2
		count++;											// count + 1
		dataBaca.Input1[count]=IntToStr(datainput_3[i]);	// Mengisi struct dataBaca.Input1 dengan datainput_3
	}

	dataBaca.ndata = count;

	for(int i=1;i<dataBaca.ndata+1;i++){	// Mengulang sebanyak dataBaca.ndata+1
		if(dataBaca.Input1[i]==NULL){dataBaca.Input1[i]="";}	// Jika dataBaca.Input1==NULL , maka berisi ""
			dataBaca.Input2[i]="";	// Mengisi dataBaca.Input2 dengan ""
			dataBaca.Input3[i]="";	// Mengisi dataBaca.Input3 dengan ""

			// Jika modulus databaca.Input1==1 dan lebih besar dari 5(> 5) , maka dataBaca.Input1 = "ganjil > 5"
			if(isGanjil(atoi(dataBaca.Input1[i]))==1 && atoi(dataBaca.Input1[i]) > 5){dataBaca.Input1[i]="ganjil > 5";}
			// Dan jika modulus dataBaca.Input1==0 dan lebih besar dari 5(> 5) , maka dataBaca.Input1 = "genap > 5"
			else if(isGanjil(atoi(dataBaca.Input1[i]))==0 && atoi(dataBaca.Input1[i]) > 5){dataBaca.Input1[i]="genap > 5";}
			// Jika bukan , maka dataBaca.Input1 = dataBaca.Input1
			else{dataBaca.Input1[i]=dataBaca.Input1[i];
		}
	}

	save_data_file("data_copy5.txt",dataBaca);	// save file dengan nama "data_copy3.txt"
	Process();
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);

	int j=5;
	for(int i = 1; i<=12;i++){
		BSP_LCD_DisplayStringAt(0, j, (uint8_t *)dataBaca.Input1[i], CENTER_MODE);
		j = j + 22;
	}

	free(dataBaca.Input1),dataBaca.Input1=NULL;	// Membebaskan memory pada struct dataBaca
	free(dataBaca.Input2),dataBaca.Input2=NULL;
	free(dataBaca.Input3),dataBaca.Input3=NULL;

	HAL_Delay(2000);
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
}
/* ====================== END OF FUNGSI CONVERT DATA SOAL 1-5 ==================== */

// Function display process
void Process(){
	BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
	BSP_LCD_DisplayStringAt(0, 110, (uint8_t *)"loading in progress", CENTER_MODE);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
	int j=-120;
	for(int i = 0; i<12;i++){
		BSP_LCD_DisplayStringAt(j, 135, (uint8_t *)".", CENTER_MODE);
		j = j + 22;
		HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_3);
		HAL_Delay(150);
	}
}
// Function pada kondisi Error1
void Error1(){
	while(1){
		res = BSP_SD_Init();
		if(res == FR_OK){	// jika kondisi res OK
			BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
			BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHTYELLOW);
			BSP_LCD_DisplayStringAt(0, 115, (uint8_t *)"SDCARD DETECTED!", CENTER_MODE);
			Error2();
		   	}
	}
}
// Function error2
void Error2(){
	while(1){
		HAL_Delay(1000);	// delay 1s
		NVIC_SystemReset(); // Reset System
	}
}

// Fungsi untuk mengubah sebuah karakter pada sebuah string
char* replaceWordInString(const char* s, const char* oldW, const char* newW){
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW); // Variabel newWlen menampung banyaknya data string pada newW
    int oldWlen = strlen(oldW); // Variabel oldWlen menampung banyaknya data string pada oldW
    for (i = 0; s[i] != '\0'; i++) { 	// Pengulangan isian string s sampai diakhir '\0'
        if (strstr(&s[i], oldW) == &s[i]) { //mengecek string s sesuai kata oldW dan dilakukan compare karakter index ke i
            cnt++;
            i += oldWlen - 1;
        }
    }
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1); // i=22,+ cnt=8,* (newWlen=1, oldWlen=1)+1 hasilnya = 23 banyaknya string
    //malloc akan mengalokasi sebanyak 23byte memory yang dipointing ke pointer result

    i = 0;
    while (*s) { // Perulangan sebanyak panjang pointer s selama tidak menunjuk ke '\0'(terminal string)
        if (strstr(s, oldW) == s) { // Cek data s apakah berisi karakter ","
            strcpy(&result[i], newW); // Jika benar akan diubah menjadi " "
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0'; // Memberikan terminator string di akhir
    return result;
}

// Membuat function untuk menghilangkan space diawal string
char *trim(char *s) {
	int count = -1;
	for(int i=0;i<strlen(s)+1;i++){	// Pengulangan sebanyak data s
		if(isspace(s[i])==0){	// Jika tidak berisi spasi ,nilai count sebesar i,dan break(pengulangan berhenti)
			count = i;
			break;	// Keluar dari for()
		}
	}

	char *result = calloc((strlen(s)+1),sizeof(char));	// mengalokasi blok memory sebanyak s+1
	int count1 = -1;
	for(int i=count;i<strlen(s)+1;i++){	// Pengulangan untuk copy data string ke result
		count1++;
		result[count1] = s[i];
	}

	return result;
}
// membuat Function untuk menghilangkan space di akhir string
char *shift_trim(char *s) {
	int count;
	for(int i=1;i<strlen(s)+1;i++){
		count = strlen(s)-i;
		if(isspace(s[count])==0){	// Jika tidak berisi spasi ,nilai count sebesar s-1,dan break(pengulangan berhenti)
			count = strlen(s)-i;
			break;	// Keluar dari for()
		}
	}
	char *result = calloc((strlen(s)+1),sizeof(char));	// mengalokasikan blok memory sebanyak s+1
	int count1 = -1;
	for(int i=0;i<count+1;i++){
		count1++;
		result[count1] = s[i];
	}

	result = trim(result);	// Menghilangkan space diawal string
	return result;
}

// Mengkonvert dari Integer ke String
char *IntToStr(int x){
	char *str=(char *)malloc(10 * sizeof (char));	// Mengalokasikan blok memory sebesar 10byte dan di pointing ke pointer str
	sprintf(str, "%d", x);	// Memasukkan data integer x ke str
	return str;
}

// Function Read file data
void read_file(char *namafile){
	res = f_mount(&SDFatFs, "", 1);	// mount sd card
	if(res != FR_OK){
	   		Error1();
	}

	res = f_open(&MyFile, namafile, FA_READ);	// open data file sebagai READ
	if(res != FR_OK){	// jika file tidak ada akan ada display error
		BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
		BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTYELLOW);
		BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"NO DATA AVAILABLE!", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 130, (uint8_t *)"Input your data.txt...", CENTER_MODE);
	   	Error2();
	}
	int i = 0;	// Variabel i dengan nilai = 0
	int j = 1;	// Variabel j dengan nilai = 1
	while(!f_eof(&MyFile)){	// Melakukan perulangan selama belum mencapai End Of File
		i++;
	   	f_gets(buffrd, sizeof buffrd, &MyFile);	// mengambil isi file dimasukkan kedalam buffrd

	   	strcpy(dataraw[i], shift_trim(buffrd));	// copy data buffrd ke dataraw[i]

	   	if(strlen(dataraw[i])>=0){	// Melakukan pengecekan dan copy data
	   		j++;
	   		strcpy(dataraw[j], shift_trim(buffrd));
	   	}
	 }
	if(res != FR_OK){
	   		 Error1();
	}
	f_close(&MyFile);	// close file
	number_data = j;

	if(strlen(dataraw[number_data]) == strlen(dataraw[number_data-1]))	// mengecek panjang baris akhir dan baris akhir-1
	{
		number_data=j-1;
	}
	else{number_data = j;
	}
}

// Membuat Fungsi untuk mengambil data dari rawdata
void get_data_from_rawdata(){
	char *datain1,*datain2,*datain3;	// declare variabel
	datain1 = calloc(100,sizeof(char));	// alokasi memory
	datain2 = calloc(100,sizeof(char));
	datain3 = calloc(100,sizeof(char));

	for(int i=1;i<number_data+1;i++){
		txtResult = replaceWordInString(dataraw[i],","," ");	// Mengubah suatu karakter pada string dari "," menjadi " "
		sscanf(txtResult,"%s  %s  %s ",datain1,datain2, datain3);	// Mengambil data dari txtresult, datain1,datain2,datain3 sebagai string
		datainput_1[i] = atoi(datain1);	// Mengubah string ke integer
		datainput_2[i] = atoi(datain2);
		datainput_3[i] = atoi(datain3);
		free(txtResult),txtResult=NULL;	// membebaskan memory txtResult
	}
	free(datain1),datain1=NULL;	// membebaskan memory datain
	free(datain2),datain2=NULL;
	free(datain3),datain3=NULL;
}

// Membuat Fungsi untuk menyimpan dan menuliskan sebuah file text
void save_data_file(char *namafile, dataInput datatulis){
	res = f_mount(&SDFatFS, "", 1);	// mount sd card
	if(res != FR_OK){
		Error1();
	}
	res = f_open(&MyFile, namafile, FA_CREATE_ALWAYS | FA_WRITE);	// open file dengan mode membuat file jika belum ada atau hanya menulis
	if(res != FR_OK){
		Error1();
	}
	for (int i = 1;i < (datatulis.ndata+1);i++){	// menulis isi file
		f_printf(&MyFile, "%s %s %s \n",  datatulis.Input1[i], datatulis.Input2[i],datatulis.Input3[i]);
	}

	f_close(&MyFile);	// close file
	f_mount(0, "", 1);	// unmount sd card
}

//Function pembulatan
int c_round(double x){
	return x < 0 ? x - 0.5 : x + 0.5; // Jika x kurang dari 0, maka x - 0.5 , jika tidak x + 0.5
}
// Function sisa pembagian
double c_modulus(double a,double b){
	double tempres;
	tempres = c_round(b*((double)(a/b)-(int)(a/b)));
	return tempres;
}
// Function cek angka ganjil
int isGanjil(int num)
{
	if (num == 0 || num == 1)	// Jika ganjil akan return 1 , dan genap return 0
		return 1;
	else
		return (c_modulus(num,2) == 0 ? 0 : 1) ;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
