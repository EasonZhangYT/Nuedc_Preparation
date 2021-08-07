/*
*********************************************************************************************************
*
*	ģ������ : BSPģ��(For STM32H7)
*	�ļ����� : bsp.c
*	��    �� : V1.0
*	˵    �� : ����Ӳ���ײ�������������ļ���ÿ��c�ļ����� #include "bsp.h" ���������е���������ģ�顣
*			   bsp = Borad surport packet �弶֧�ְ�
*	�޸ļ�¼ :
*		�汾��  ����         ����       ˵��
*		V1.0    2018-07-29  Eric2013   ��ʽ����
*
*	Copyright (C), 2018-2030, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"
#include "AD7124.h"


/*
*********************************************************************************************************
*	                                   ��������
*********************************************************************************************************
*/
static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);
static void MPU_Config(void);


/*
*********************************************************************************************************
*	                                   ��������
*********************************************************************************************************
*/
static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);
static void MPU_Config(void);

/*
*********************************************************************************************************
*	�� �� ��: System_Init
*	����˵��: ϵͳ��ʼ������Ҫ��MPU��Cache��ϵͳʱ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void System_Init(void)
{
	
	/* ����MPU */
	MPU_Config();
	
	/* ʹ��L1 Cache */
	CPU_CACHE_Enable();

	/* 
       STM32H7xx HAL ���ʼ������ʱϵͳ�õĻ���H7�Դ���64MHz��HSIʱ��:
	   - ���ú���HAL_InitTick����ʼ���δ�ʱ���ж�1ms��
	   - ����NVIV���ȼ�����Ϊ4��
	 */
	HAL_Init();

	/* 
       ����ϵͳʱ�ӵ�400MHz
       - �л�ʹ��HSE��
       - �˺��������ȫ�ֱ���SystemCoreClock������������HAL_InitTick��
    */
	SystemClock_Config();

	/* 
	   Event Recorder��
	   - �����ڴ���ִ��ʱ�������MDK5.25�������ϰ汾��֧�֣�IAR��֧�֡�
	   - Ĭ�ϲ����������Ҫʹ�ܴ�ѡ���ؿ�V7�������û��ֲ��8��
	*/	
#if Enable_EventRecorder == 1  
	/* ��ʼ��EventRecorder������ */
	EventRecorderInitialize(EventRecordAll, 1U);
	EventRecorderStart();
#endif

}

/*
*********************************************************************************************************
*	�� �� ��: bsp_Init
*	����˵��: ��ʼ�����е�Ӳ���豸���ú�������CPU�Ĵ���������ļĴ�������ʼ��һЩȫ�ֱ�����ֻ��Ҫ����һ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Init(void)
{
	/* ʹ��Ӳ��CRC��ʹ��STemWinǰ���������ʹ��CRCʱ�� */
	__HAL_RCC_CRC_CLK_ENABLE();
	
	
	//bsp_InitDWT();      /* ��ʼ��CM7�ں˵�ʱ�����ڼ����� */
	bsp_InitKey();    	/* ������ʼ����Ҫ���ڵδ�ʱ��֮ǰ����Ϊ��ť�����ͨ���δ�ʱ��ɨ�� */
	bsp_InitTimer();  	/* ��ʼ���δ�ʱ�� */
	bsp_InitUart();		/* ��ʼ������ */
//	bsp_InitExtIO();	/* ��ʼ��FMC����74HC574��չIO. ������ bsp_InitLed()ǰִ�� */	
//	bsp_InitLed();    	/* ��ʼ��LED */	
    bsp_InitExtSDRAM(); /* ��ʼ��SDRAM */
	
	bsp_DelayMS(200); 
	bsp_InitI2C();		/* ��ʼ��I2C���� */
	TOUCH_InitHard();   /* ��ʼ������оƬ��LCD����ͺŵļ��Ҳ�ڴ˺���������Ҫ�ں���LCD_InitHardǰ���� */ 

//	bsp_InitSPIBus();	/* ����SPI���� */	
//	AD1292_Init();
	AD7124Init();

	
//	ADS1292R_Work();
	
	/* �ӳ�200ms�ٵ������⣬����˲����� */
	bsp_DelayMS(200); 
	LCD_SetBackLight(255);
}

/*
*********************************************************************************************************
*	�� �� ��: SystemClock_Config
*	����˵��: ��ʼ��ϵͳʱ��
*            	System Clock source            = PLL (HSE)
*            	SYSCLK(Hz)                     = 400000000 (CPU Clock)
*           	HCLK(Hz)                       = 200000000 (AXI and AHBs Clock)
*            	AHB Prescaler                  = 2
*            	D1 APB3 Prescaler              = 2 (APB3 Clock  100MHz)
*            	D2 APB1 Prescaler              = 2 (APB1 Clock  100MHz)
*            	D2 APB2 Prescaler              = 2 (APB2 Clock  100MHz)
*            	D3 APB4 Prescaler              = 2 (APB4 Clock  100MHz)
*            	HSE Frequency(Hz)              = 25000000
*           	PLL_M                          = 5
*            	PLL_N                          = 160
*            	PLL_P                          = 2
*            	PLL_Q                          = 4
*            	PLL_R                          = 2
*            	VDD(V)                         = 3.3
*            	Flash Latency(WS)              = 4
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void SystemClock_Config(void)
{
//	RCC_ClkInitTypeDef RCC_ClkInitStruct;
//	RCC_OscInitTypeDef RCC_OscInitStruct;
//	HAL_StatusTypeDef ret = HAL_OK;

//	/* ��סSCU(Supply configuration update) */
//	MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

//	/* 
//      1��оƬ�ڲ���LDO��ѹ������ĵ�ѹ��Χ����ѡVOS1��VOS2��VOS3����ͬ��Χ��Ӧ��ͬ��Flash���ٶȣ�
//         ���鿴�ο��ֲ��Table 12�ı��
//      2������ѡ��ʹ��VOS1����ѹ��Χ1.15V - 1.26V��
//    */
//	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

//	while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

//	/* ʹ��HSE����ѡ��HSE��ΪPLLʱ��Դ */
//	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
//	RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
//	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//		
//	RCC_OscInitStruct.PLL.PLLM = 5;
//	RCC_OscInitStruct.PLL.PLLN = 160;
//	RCC_OscInitStruct.PLL.PLLP = 2;
//	RCC_OscInitStruct.PLL.PLLR = 2;
//	RCC_OscInitStruct.PLL.PLLQ = 4;		
//		
//	RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
//	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;	
//	ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
//	if(ret != HAL_OK)
//	{
//        Error_Handler(__FILE__, __LINE__);
//	}

//	/* 
//       ѡ��PLL�������Ϊϵͳʱ��
//       ����RCC_CLOCKTYPE_SYSCLKϵͳʱ��
//       ����RCC_CLOCKTYPE_HCLK ʱ�ӣ���ӦAHB1��AHB2��AHB3��AHB4����
//       ����RCC_CLOCKTYPE_PCLK1ʱ�ӣ���ӦAPB1����
//       ����RCC_CLOCKTYPE_PCLK2ʱ�ӣ���ӦAPB2����
//       ����RCC_CLOCKTYPE_D1PCLK1ʱ�ӣ���ӦAPB3����
//       ����RCC_CLOCKTYPE_D3PCLK1ʱ�ӣ���ӦAPB4����     
//    */
//	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_PCLK1 | \
//								 RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_D3PCLK1);

//	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
//	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
//	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;  
//	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2; 
//	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2; 
//	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2; 
//	
//	/* �˺��������SystemCoreClock������������HAL_InitTick */
//	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
//	if(ret != HAL_OK)
//	{
//        Error_Handler(__FILE__, __LINE__);
//	}

//    /*
//      ʹ��IO�ĸ���ģʽ��Ҫʹ��IO������������������������ 
//      ��1��ʹ��CSI clock
//      ��2��ʹ��SYSCFG clock
//      ��3��ʹ��I/O������Ԫ�� ����SYSCFG_CCCSR�Ĵ�����bit0
//    */
//	__HAL_RCC_CSI_ENABLE() ;

//	__HAL_RCC_SYSCFG_CLK_ENABLE() ;

//	HAL_EnableCompensationCell();

//   /* AXI SRAM��ʱ�����ϵ��Զ�ʹ�ܵģ���D2���SRAM1��SRAM2��SRAM3Ҫ����ʹ�� */	
//#if 0
//	__HAL_RCC_D2SRAM1_CLK_ENABLE();
//	__HAL_RCC_D2SRAM2_CLK_ENABLE();
//	__HAL_RCC_D2SRAM3_CLK_ENABLE();
//#endif

  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** ���õ�Դ���ø���
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** ����������ѹ�������ѹ
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** ��ʼ��CPU��AHB��APB����ʱ��
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
//  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
		while(1);
  }
  /** ��ʼ��CPU��AHB��APB����ʱ��
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
		while(1);
  }

    /*
      ʹ��IO�ĸ���ģʽ��Ҫʹ��IO������������������������ 
      ��1��ʹ��CSI clock
      ��2��ʹ��SYSCFG clock
      ��3��ʹ��I/O������Ԫ�� ����SYSCFG_CCCSR�Ĵ�����bit0
    */
	__HAL_RCC_CSI_ENABLE() ;

	__HAL_RCC_SYSCFG_CLK_ENABLE() ;

	HAL_EnableCompensationCell();

   /* AXI SRAM��ʱ�����ϵ��Զ�ʹ�ܵģ���D2���SRAM1��SRAM2��SRAM3Ҫ����ʹ�� */	
#if 1
	__HAL_RCC_D2SRAM1_CLK_ENABLE();
	__HAL_RCC_D2SRAM2_CLK_ENABLE();
	__HAL_RCC_D2SRAM3_CLK_ENABLE();
#endif  

}

/*
*********************************************************************************************************
*	�� �� ��: Error_Handler
*	��    ��: file : Դ�����ļ����ơ��ؼ��� __FILE__ ��ʾԴ�����ļ�����
*			  line �������кš��ؼ��� __LINE__ ��ʾԴ�����к�
*	�� �� ֵ: ��
*		Error_Handler(__FILE__, __LINE__);
*********************************************************************************************************
*/
void Error_Handler(char *file, uint32_t line)
{
	/* 
		�û���������Լ��Ĵ��뱨��Դ�����ļ����ʹ����кţ����罫�����ļ����кŴ�ӡ������
		printf("Wrong parameters value: file %s on line %d\r\n", file, line) 
	*/
	
	/* ����һ����ѭ��������ʧ��ʱ������ڴ˴��������Ա����û���� */
	if (line == 0)
	{
		return;
	}
	
	while(1)
	{
	}
}

/*
*********************************************************************************************************
*	�� �� ��: MPU_Config
*	����˵��: ����MPU
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void MPU_Config( void )
{
	MPU_Region_InitTypeDef MPU_InitStruct;

	/* ��ֹ MPU */
	HAL_MPU_Disable();
	
    /* ����AXI SRAM��MPU����ΪWrite through, read allocate��no write allocate */
	MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress      = 0x24000000;
	MPU_InitStruct.Size             = MPU_REGION_SIZE_512KB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable     = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number           = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	
	
	/* ����FMC��չIO��MPU����ΪDevice����Strongly Ordered */
	MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress      = 0x60000000;
	MPU_InitStruct.Size             = ARM_MPU_REGION_SIZE_64KB;	
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
	MPU_InitStruct.IsCacheable      = MPU_ACCESS_NOT_CACHEABLE;	/* ������MPU_ACCESS_CACHEABLE;�����2��CS��WE�ź� */
	MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number           = MPU_REGION_NUMBER1;
	MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;
	
	HAL_MPU_ConfigRegion(&MPU_InitStruct);
    
    /* 
	   ����SDRAM��MPU����ΪWrite through, read allocate��no write allocate 
	   �������õ�����£���Cache������������һ�������ã���ʹ��GUI��Alpha�ĳ���Ҫע�⡣
	   ��Ҫ�û��ֶ�����Ч��������
	*/
#if 0
	MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress      = 0xC0000000;
	MPU_InitStruct.Size             = MPU_REGION_SIZE_32MB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable     = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number           = MPU_REGION_NUMBER2;
	MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	
	/* 
	   ����SDRAM��MPU����Ϊ�ر�Cache
	*/
#else
	MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
//	MPU_InitStruct.BaseAddress      = 0xC0000000;
	MPU_InitStruct.BaseAddress      = 0xD0000000;
	MPU_InitStruct.Size             = MPU_REGION_SIZE_32MB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable     = MPU_ACCESS_NOT_BUFFERABLE;
//	MPU_InitStruct.IsCacheable      = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number           = MPU_REGION_NUMBER2;
	MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);
#endif

	/*ʹ�� MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/*
*********************************************************************************************************
*	�� �� ��: CPU_CACHE_Enable
*	����˵��: ʹ��L1 Cache
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void CPU_CACHE_Enable(void)
{
	/* ʹ�� I-Cache */
	SCB_EnableICache();

	/* ʹ�� D-Cache */
//	SCB_EnableDCache();
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer10ms
*	����˵��: �ú���ÿ��10ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ����ʱ��Ҫ���ϸ��
*			������Է��ڴ˺��������磺����ɨ�衢���������п��Ƶȡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer10ms(void)
{
	bsp_KeyScan10ms();
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer1ms
*	����˵��: �ú���ÿ��1ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ��Ҫ�����Դ��������
*			 ���Է��ڴ˺��������磺��������ɨ�衣
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_RunPer1ms(void)
{
	TOUCH_Scan();	  /* ���败�����ͼ��� */
	TOUCH_CapScan();  /* ���ݴ����� */
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_Idle
*	����˵��: ����ʱִ�еĺ�����һ����������for��whileѭ������������Ҫ���� CPU_IDLE() �������ñ�������
*			 ������ȱʡΪ�ղ������û��������ι��������CPU��������ģʽ�Ĺ��ܡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */

	/* ���� emWin ͼ�ο⣬���Բ���ͼ�ο���Ҫ����ѯ���� */
	//GUI_Exec();

	/* ���� uIP Э�飬���Բ���uip��ѯ���� */
	//TOUCH_CapScan();
}

/*
*********************************************************************************************************
*	�� �� ��: HAL_Delay
*	����˵��: �ض�������ӳٺ������滻HAL�еĺ�������ΪHAL�е�ȱʡ����������Systick�жϣ������USB��SD��
*             �ж������ӳٺ��������������Ҳ����ͨ������HAL_NVIC_SetPriority����Systick�ж�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
/* ��ǰ����ʹ��stm32h7xx_hal.cĬ�Ϸ�ʽʵ�֣�δʹ�������ض���ĺ��� */
#if 0
void HAL_Delay(uint32_t Delay)
{
	bsp_DelayUS(Delay * 1000);
}
#endif

/*
*********************************************************************************************************
*	�� �� ��: bsp_DelayMS
*	����˵��: Ϊ���õײ������ڴ�RTOS�����������и��õļ�����
*             ר������һ������ʽ���ӳٺ������ڵײ�������ms�����ӳ���Ҫ���ڳ�ʼ����������Ӱ��ʵʱ�ԡ�
*	��    ��: n �ӳٳ��ȣ���λ1 ms
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_DelayMS(uint32_t _ulDelayTime)
{
	bsp_DelayUS(1000*_ulDelayTime);
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_DelayUS
*	����˵��: �������ʱ����CPU���ڲ�����ʵ�֣�32λ������
*             	OSSchedLock(&err);
*				bsp_DelayUS(5);
*				OSSchedUnlock(&err); ����ʵ����������Ƿ���Ҫ�ӵ�������ѡ����ж�
*	��    ��: _ulDelayTime  �ӳٳ��ȣ���λ1 us
*	�� �� ֵ: ��
*   ˵    ��: 1. ��Ƶ168MHz������£�32λ������������2^32/168000000 = 25.565��
*                ����ʹ�ñ��������ӳٵĻ����ӳ���1�����¡�  
*             2. ʵ��ͨ��ʾ�������ԣ�΢���ӳٺ�����ʵ������ʵ�ʶ�����0.25us���ҵ�ʱ�䡣
*             �������ݲ���������
*             ��1��. MDK5.15���Ż��ȼ�0, ��ͬ��MDK�Ż��ȼ�����û��Ӱ�졣
*             ��2��. STM32F407IGT6
*             ��3��. ���Է�����
*				 GPIOI->BSRRL = GPIO_Pin_8;
*				 bsp_DelayUS(10);
*				 GPIOI->BSRRH = GPIO_Pin_8;
*             -------------------------------------------
*                ����                 ʵ��ִ��
*             bsp_DelayUS(1)          1.2360us
*             bsp_DelayUS(2)          2.256us
*             bsp_DelayUS(3)          3.256us
*             bsp_DelayUS(4)          4.256us
*             bsp_DelayUS(5)          5.276us
*             bsp_DelayUS(6)          6.276us
*             bsp_DelayUS(7)          7.276us
*             bsp_DelayUS(8)          8.276us
*             bsp_DelayUS(9)          9.276us
*             bsp_DelayUS(10)         10.28us
*            3. ����32λ�޷������������ȡ�Ľ���ٸ�ֵ��32λ�޷�������Ȼ������ȷ�Ļ�ȡ��ֵ��
*              ����A,B,C����32λ�޷�������
*              ���A > B  ��ôA - B = C������ܺ���⣬��ȫû������
*              ���A < B  ��ôA - B = C�� C����ֵ����0xFFFFFFFF - B + A + 1����һ��Ҫ�ر�ע�⣬�������ڱ�������
*********************************************************************************************************
*/
void bsp_DelayUS(uint32_t _ulDelayTime)
{
    uint32_t tCnt, tDelayCnt;
	uint32_t tStart;
		
	tStart = (uint32_t)CPU_TS_TmrRd();                       /* �ս���ʱ�ļ�����ֵ */
	tCnt = 0;
	tDelayCnt = _ulDelayTime * (SystemCoreClock / 1000000);	 /* ��Ҫ�Ľ����� */ 		      

	while(tCnt < tDelayCnt)
	{
		tCnt = (uint32_t)CPU_TS_TmrRd() - tStart; /* ��������У����������һ��32λ���������¼�������Ȼ������ȷ���� */	
	}
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_CPU_ClkFreq
*	����˵��: ��ȡϵͳʱ�ӣ�uCOS-II��Ҫʹ��
*	��    ��: ��
*	�� �� ֵ: ϵͳʱ��
*********************************************************************************************************
*/
//CPU_INT32U  BSP_CPU_ClkFreq (void)
//{
//    RCC_ClocksTypeDef  rcc_clocks;

//    RCC_GetClocksFreq(&rcc_clocks);
//    return ((CPU_INT32U)rcc_clocks.HCLK_Frequency);
//}

/*
*********************************************************************************************************
*	�� �� ��: BSP_Tick_Init
*	����˵��: ��ʼ��ϵͳ�δ�ʱ����ΪuCOS-II��ϵͳʱ�ӽ��ģ�1msһ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//void BSP_Tick_Init (void)
//{
//    CPU_INT32U  cpu_clk_freq;
//    CPU_INT32U  cnts;
//    
//    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* ��ȡϵͳʱ��  */
//    
//#if (OS_VERSION >= 30000u)
//    cnts  = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;     
//#else
//    cnts  = cpu_clk_freq / (CPU_INT32U)OS_TICKS_PER_SEC;        /* ��õδ�ʱ���Ĳ���  */
//#endif
//    
//	OS_CPU_SysTickInit(cnts);                                   /* ����Ĭ�ϵ���������ȼ�            */
//}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
