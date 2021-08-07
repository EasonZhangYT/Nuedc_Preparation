/*
*********************************************************************************************************
*	                                  
*	ģ������ : uCOS-III
*	�ļ����� : mian.c
*	��    �� : V1.0
*	˵    �� : uCOS-III����ģ��
*              ʵ��Ŀ�ģ�
*                1. ѧϰMDK��IAR��uCOS-III����ģ�崴����              
*              ʵ�����ݣ�
*                1. �����������¼�������ͨ�����°���K1����ͨ�����ڴ�ӡ�����ջʹ�����
*                    ===============================================================
*                     ���ȼ� ʹ��ջ ʣ��ջ �ٷֱ� ������   ������
*                       60    624   1424   30%    1.45%   App Task GUI
*                        5     77    435   15%    0.00%   App Task COM
*                        4     77    435   15%    0.01%   App Task UserIF
*                        3     77    435   15%    0.00%   App Msp Pro
*                        2    162    350   31%    0.53%   App Task Start
*                       61     77     51   60%    0.00%   uC/OS-III Timer Task
*                       62     83    173   32%    0.06%   uC/OS-III Stat Task
*                       63     69    187   26%   97.93%   uC/OS-III Idle Task                   
*                    �����������ʹ��SecureCRT��V7���������д�������鿴��ӡ��Ϣ��
*                    App Task Start����  ������������������BSP����������
*                    App Task MspPro���� ����Ϣ������������LED��˸��
*                    App Task UserIF���� ��������Ϣ����
*                    App Task COM����    ����δʹ�á�
*                    App Task GUI����    ��emWin����
*                2. (1) �����õ�printf������ȫ��ͨ������App_Printfʵ�֡�
*                   (2) App_Printf���������ź����Ļ�������������Դ�������⡣
*              ע�����
*                1. Ϊ��֧��uC/Probe�������:
*                   (1).MDKҪ��ѡoption->output -> Debug Infomationѡ�ѡ���Ż��ȼ�0
*                   (2).IARҪѡ��ѡ���Ż��ȼ�low���������������ط��ȹ�ѡ
*                       a. option->C/C++ Compiler->Outputѡ���й�ѡGenerate debug information��
*                       b. option->linker->Outputѡ���й�ѡInclude Generate debug information in output��
*                   (3).ʹ��uCOS-III�궨��
*                       #define OS_CFG_DBG_EN             1u
*                       #define OS_CFG_STAT_TASK_EN       1u ͬʱ��ʼ��ͳ������
*                      	#define CPU_CFG_INT_DIS_MEAS_EN   1u 
*                   (4).Ϊ�˷�����ԣ�����OS_CFG_APP_HOOKS_EN��OS_CFG_ARG_CHK_EN��ʹ��
*                2. ��ʵ���Ƽ�ʹ�ô������SecureCRT��Ҫ�����ڴ�ӡЧ�������롣�������
*                   V7��������������С�
*                3. ��ؽ��༭��������������TAB����Ϊ4���Ķ����ļ���Ҫ��������ʾ�����롣
*
*	�޸ļ�¼ :
*		�汾��   ����         ����            ˵��
*       V1.0    2019-05-01   Eric2013    1. ST�̼���1.3.0�汾
*                                        2. BSP������V1.2
*                                        3. uCOS-III�汾V3.07.03
*                                        4. uC/CPU�汾V1.31.04
*                                        5. uC/LIB�汾V1.38.03
*                                        6. STemWin�汾V5.44                                       
*                                       
*	Copyright (C), 2019-2030, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"
#include "MainTask.h"


/*
*********************************************************************************************************
*                                       ��̬ȫ�ֱ���
*********************************************************************************************************
*/                                                          
static  OS_TCB   AppTaskStartTCB;
static  CPU_STK  AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static  OS_TCB   AppTaskMsgProTCB;
static  CPU_STK  AppTaskMsgProStk[APP_CFG_TASK_MsgPro_STK_SIZE];

static  OS_TCB   AppTaskCOMTCB;
static  CPU_STK  AppTaskCOMStk[APP_CFG_TASK_COM_STK_SIZE];

static  OS_TCB   AppTaskUserIFTCB;
static  CPU_STK  AppTaskUserIFStk[APP_CFG_TASK_USER_IF_STK_SIZE];

static  OS_TCB   AppTaskGUITCB;
static  CPU_STK  AppTaskGUIStk[APP_CFG_TASK_GUI_STK_SIZE];

/*
*********************************************************************************************************
*                                      ��������
*********************************************************************************************************
*/
static  void  AppTaskStart          (void     *p_arg);
static  void  AppTaskMsgPro         (void     *p_arg);
static  void  AppTaskUserIF         (void     *p_arg);
static  void  AppTaskCOM			(void 	  *p_arg);
static  void  AppTaskCreate         (void);
static  void  DispTaskInfo          (void);
static  void  AppObjCreate          (void);
static  void  App_Printf (CPU_CHAR *format, ...);

/*
*******************************************************************************************************
*                               ����
*******************************************************************************************************
*/
static  OS_SEM   AppPrintfSemp;	/* ����printf���� */


static void PrintfLogo(void);

/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: ��׼c������ڡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int main(void)
{
    OS_ERR  err;  
	
	/* HAL�⣬MPU��Cache��ʱ�ӵ�ϵͳ��ʼ�� */
	System_Init();

	/* �ں˿���ǰ�ر�HAL��ʱ���׼ */
	HAL_SuspendTick();
	
	/* ��ʼ���δ�ʱ�ӣ��������������濪�� */	
	BSP_OS_TickInit();
		
	/* ��ʼ��uC/OS-III �ں� */
    OSInit(&err);  

	/* ����һ����������Ҳ���������񣩡���������ᴴ�����е�Ӧ�ó������� */
	OSTaskCreate((OS_TCB       *)&AppTaskStartTCB,  /* ������ƿ��ַ */           
                 (CPU_CHAR     *)"App Task Start",  /* ������ */
                 (OS_TASK_PTR   )AppTaskStart,      /* ������������ַ */
                 (void         *)0,                 /* ���ݸ�����Ĳ��� */
                 (OS_PRIO       )APP_CFG_TASK_START_PRIO, /* �������ȼ� */
                 (CPU_STK      *)&AppTaskStartStk[0],     /* ��ջ����ַ */
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE / 10, /* ��ջ������������ʾ��10%��Ϊ����� */
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE,      /* ��ջ�ռ��С */
                 (OS_MSG_QTY    )0,  /* ������֧�ֽ��ܵ������Ϣ�� */
                 (OS_TICK       )0,  /* ����ʱ��Ƭ */
                 (void         *)0,  /* ��ջ�ռ��С */  
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		
				 /*  �������£�
					OS_OPT_TASK_STK_CHK      ʹ�ܼ������ջ��ͳ������ջ���õĺ�δ�õ�
					OS_OPT_TASK_STK_CLR      �ڴ�������ʱ����������ջ
					OS_OPT_TASK_SAVE_FP      ���CPU�и���Ĵ��������������л�ʱ���渡��Ĵ���������
				 */  
                 (OS_ERR       *)&err);

	/* ����������ϵͳ������Ȩ����uC/OS-III */
    OSStart(&err);                                               
    
    (void)&err;
    
    return (0);
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskStart
*	����˵��: ����һ�����������ڶ�����ϵͳ�����󣬱����ʼ���δ����������������Ҫʵ�ְ�����⡣
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 2
*********************************************************************************************************
*/
const char buf1[] = "���յ���������1\r\n";
const char buf2[] = "���յ���������2\r\n";
const char buf3[] = "���յ���������3\r\n";
const char buf4[] = "���յ���������4\r\n";
static  void  AppTaskStart (void *p_arg)
{
	OS_ERR      err;
	uint8_t    read;

   (void)p_arg;
	
	HAL_ResumeTick();
	
	CPU_Init(); /* �˺���Ҫ���ȵ��ã���Ϊ����������ʹ�õ�us��ms�ӳ��ǻ��ڴ˺����� */
 	bsp_Init();
	BSP_OS_TickEnable();
	
#if OS_CFG_STAT_TASK_EN > 0u
     OSStatTaskCPUUsageInit(&err);   
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
    
	/* �������� */
    AppTaskCreate(); 

	/* ���������ͨ�Ż��� */
	AppObjCreate();	
	
    while (1)
	{  
		/* ��Ҫ�����Դ���ĳ��򣬶�Ӧ������̵��õ�SysTick_ISR */
		bsp_ProPer1ms();
		OSTimeDly(1, OS_OPT_TIME_PERIODIC, &err);
		/* ���յ��Ĵ�������� */
		if (comGetChar(COM2, &read))
		{
			switch (read)
			{
				case '1':
					comSendBuf(COM2, (uint8_t *)buf1, strlen(buf1));
					break;

				case '2':
					comSendBuf(COM2, (uint8_t *)buf2, strlen(buf2));
					break;

				case '3':
					comSendBuf(COM2, (uint8_t *)buf3, strlen(buf3));
					break;

				case '4':
					comSendBuf(COM2, (uint8_t *)buf4, strlen(buf4));
					break;	
				
				default:
					break;
			}
		}
    }
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskMsgPro
*	����˵��: ��Ϣ������������LED��˸
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 3
*********************************************************************************************************
*/
static void AppTaskMsgPro(void *p_arg)
{
	OS_ERR  err;  
	
	(void)p_arg;
		  
	while(1)
	{
		bsp_LedToggle(2);
	    OSTimeDly(1000, OS_OPT_TIME_DLY, &err);		
	}   
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskUserIF
*	����˵��: ������Ϣ����
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 4
*********************************************************************************************************
*/
static void AppTaskUserIF(void *p_arg)
{
	OS_ERR  err;  
	uint8_t ucKeyCode;	/* �������� */
	
	(void)p_arg;
		  
	while(1)
	{        
		ucKeyCode = bsp_GetKey();
		
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				case KEY_DOWN_K1:			  /* K1������ ��ӡ����ִ����� */
					DispTaskInfo();	     
					break;
				
				default:                     /* �����ļ�ֵ������ */
					break;
			}
		}
		
		OSTimeDly(20, OS_OPT_TIME_DLY, &err);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskCom
*	����˵��: ��δʹ��
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 5
*********************************************************************************************************
*/
static void AppTaskCOM(void *p_arg)
{
	OS_ERR  err;  	

	(void)p_arg;
	
	while(1)
	{
	    OSTimeDly(1000, OS_OPT_TIME_DLY, &err);
	} 						  	 	       											   
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskGUI
*	����˵��: GUI����������ȼ�		  			  
*	��    �Σ�p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*   �� �� ����OS_CFG_PRIO_MAX - 4u
*********************************************************************************************************
*/
static void AppTaskGUI(void *p_arg)
{	
    (void)p_arg;		/* ����������澯 */

	PrintfLogo();
	
	while (1) 
	{
		MainTask();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ����Ӧ������
*	��    �Σ�p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static  void  AppTaskCreate (void)
{
	OS_ERR      err;
	
	/**************����MsgPro����*********************/
	OSTaskCreate((OS_TCB       *)&AppTaskMsgProTCB,             
                 (CPU_CHAR     *)"App Msp Pro",
                 (OS_TASK_PTR   )AppTaskMsgPro, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_MsgPro_PRIO,
                 (CPU_STK      *)&AppTaskMsgProStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_MsgPro_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_MsgPro_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);
				 
	/**************����USER IF����*********************/
	OSTaskCreate((OS_TCB       *)&AppTaskUserIFTCB,             
                 (CPU_CHAR     *)"App Task UserIF",
                 (OS_TASK_PTR   )AppTaskUserIF, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_USER_IF_PRIO,
                 (CPU_STK      *)&AppTaskUserIFStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_USER_IF_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_USER_IF_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);

	/**************����COM����*********************/
	OSTaskCreate((OS_TCB       *)&AppTaskCOMTCB,            
                 (CPU_CHAR     *)"App Task COM",
                 (OS_TASK_PTR   )AppTaskCOM, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_COM_PRIO,
                 (CPU_STK      *)&AppTaskCOMStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_COM_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_COM_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);	 
				 
	/**************����GUI����*********************/			 
	OSTaskCreate((OS_TCB       *)&AppTaskGUITCB,              
                 (CPU_CHAR     *)"App Task GUI",
                 (OS_TASK_PTR   )AppTaskGUI, 
                 (void         *)0,
                 (OS_PRIO       )APP_CFG_TASK_GUI_PRIO,
                 (CPU_STK      *)&AppTaskGUIStk[0],
                 (CPU_STK_SIZE  )APP_CFG_TASK_GUI_STK_SIZE / 10,
                 (CPU_STK_SIZE  )APP_CFG_TASK_GUI_STK_SIZE,
                 (OS_MSG_QTY    )0,
                 (OS_TICK       )0,
                 (void         *)0,
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR       *)&err);				 
}

/*
*********************************************************************************************************
*	�� �� ��: AppObjCreate
*	����˵��: ��������ͨѶ
*	��    ��: p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static  void  AppObjCreate (void)
{
	OS_ERR      err;
	
	/* 
	   �����ź�����ֵΪ1��ʱ�����ʵ�ֻ��⹦�ܣ�Ҳ����ֻ��һ����Դ����ʹ�� 
	   �������ǽ�����1�Ĵ�ӡ������Ϊ��������Դ����ֹ���ڴ�ӡ��ʱ������������ռ
	   ��ɴ��ڴ�ӡ���ҡ�
	*/
	OSSemCreate((OS_SEM    *)&AppPrintfSemp,
				(CPU_CHAR  *)"AppPrintfSemp",
				(OS_SEM_CTR )1,
				(OS_ERR    *)&err);
}

/*
*********************************************************************************************************
*	�� �� ��: App_Printf
*	����˵��: �̰߳�ȫ��printf��ʽ		  			  
*	��    ��: ͬprintf�Ĳ�����
*             ��C�У����޷��г����ݺ���������ʵ�ε����ͺ���Ŀʱ,������ʡ�Ժ�ָ��������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static  void  App_Printf(CPU_CHAR *format, ...)
{
    CPU_CHAR  buf_str[128 + 1];
    va_list   v_args;
    OS_ERR    os_err;


    va_start(v_args, format);
   (void)vsnprintf((char       *)&buf_str[0],
                   (size_t      ) sizeof(buf_str),
                   (char const *) format,
                                  v_args);
    va_end(v_args);

	/* ������� */
    OSSemPend((OS_SEM  *)&AppPrintfSemp,
              (OS_TICK  )0u,
              (OS_OPT   )OS_OPT_PEND_BLOCKING,
              (CPU_TS  *)0,
              (OS_ERR  *)&os_err);

    printf("%s", buf_str);

   (void)OSSemPost((OS_SEM  *)&AppPrintfSemp,
                   (OS_OPT   )OS_OPT_POST_1,
                   (OS_ERR  *)&os_err);

}

/*
*********************************************************************************************************
*	�� �� ��: DispTaskInfo
*	����˵��: ��uCOS-III������Ϣͨ�����ڴ�ӡ����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void DispTaskInfo(void)
{
	OS_TCB      *p_tcb;	        /* ����һ��������ƿ�ָ��, TCB = TASK CONTROL BLOCK */
	float CPU = 0.0f;
	CPU_SR_ALLOC();

	CPU_CRITICAL_ENTER();
    p_tcb = OSTaskDbgListPtr;
    CPU_CRITICAL_EXIT();
	
	/* ��ӡ���� */
	App_Printf("===============================================================\r\n");
	App_Printf(" ���ȼ� ʹ��ջ ʣ��ջ �ٷֱ� ������   ������\r\n");
	App_Printf("  Prio   Used  Free   Per    CPU     Taskname\r\n");

	/* ����������ƿ��б�(TCB list)����ӡ���е���������ȼ������� */
	while (p_tcb != (OS_TCB *)0) 
	{
		CPU = (float)p_tcb->CPUUsage / 100;
		App_Printf("   %2d  %5d  %5d   %02d%%   %5.2f%%   %s\r\n", 
		p_tcb->Prio, 
		p_tcb->StkUsed, 
		p_tcb->StkFree, 
		(p_tcb->StkUsed * 100) / (p_tcb->StkUsed + p_tcb->StkFree),
		CPU,
		p_tcb->NamePtr);		
	 	
		CPU_CRITICAL_ENTER();
        p_tcb = p_tcb->DbgNextPtr;
        CPU_CRITICAL_EXIT();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: PrintfLogo
*	����˵��: ��ӡ�������ƺ����̷�������, ���ϴ����ߺ󣬴�PC���ĳ����ն�������Թ۲���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
	printf("*************************************************************\n\r");
	
	/* ���CPU ID */
	{
		uint32_t CPU_Sn0, CPU_Sn1, CPU_Sn2;
		
		CPU_Sn0 = *(__IO uint32_t*)(0x1FF1E800);
		CPU_Sn1 = *(__IO uint32_t*)(0x1FF1E800 + 4);
		CPU_Sn2 = *(__IO uint32_t*)(0x1FF1E800 + 8);

		printf("\r\nCPU : STM32H743XIH6, BGA240, ��Ƶ: %dMHz\r\n", SystemCoreClock / 1000000);
		printf("UID = %08X %08X %08X\n\r", CPU_Sn2, CPU_Sn1, CPU_Sn0);
	}

	printf("\n\r");

	
	/* ��ӡCM7 CMSIS��ST��HAL��汾 */
	printf("* CM7 CMSIS �汾  : %x\r\n", __CM7_CMSIS_VERSION);
	printf("* HAL��汾  : %x (STM32H7xx HAL Driver)\r\n", HAL_GetHalVersion());
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
