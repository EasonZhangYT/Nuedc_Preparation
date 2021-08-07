/*
*********************************************************************************************************
*	                                  
*	模块名称 : uCOS-III
*	文件名称 : mian.c
*	版    本 : V1.0
*	说    明 : uCOS-III程序模板
*              实验目的：
*                1. 学习MDK和IAR的uCOS-III程序模板创建。              
*              实验内容：
*                1. 共创建了如下几个任务，通过按下按键K1可以通过串口打印任务堆栈使用情况
*                    ===============================================================
*                     优先级 使用栈 剩余栈 百分比 利用率   任务名
*                       60    624   1424   30%    1.45%   App Task GUI
*                        5     77    435   15%    0.00%   App Task COM
*                        4     77    435   15%    0.01%   App Task UserIF
*                        3     77    435   15%    0.00%   App Msp Pro
*                        2    162    350   31%    0.53%   App Task Start
*                       61     77     51   60%    0.00%   uC/OS-III Timer Task
*                       62     83    173   32%    0.06%   uC/OS-III Stat Task
*                       63     69    187   26%   97.93%   uC/OS-III Idle Task                   
*                    串口软件建议使用SecureCRT（V7光盘里面有此软件）查看打印信息。
*                    App Task Start任务  ：启动任务，这里用作BSP驱动包处理。
*                    App Task MspPro任务 ：消息处理，这里用作LED闪烁。
*                    App Task UserIF任务 ：按键消息处理。
*                    App Task COM任务    ：暂未使用。
*                    App Task GUI任务    ：emWin任务。
*                2. (1) 凡是用到printf函数的全部通过函数App_Printf实现。
*                   (2) App_Printf函数做了信号量的互斥操作，解决资源共享问题。
*              注意事项：
*                1. 为了支持uC/Probe调试组件:
*                   (1).MDK要勾选option->output -> Debug Infomation选项，选择优化等级0
*                   (2).IAR要选择选择优化等级low，其中如下两个地方比勾选
*                       a. option->C/C++ Compiler->Output选项中勾选Generate debug information。
*                       b. option->linker->Output选项中勾选Include Generate debug information in output。
*                   (3).使能uCOS-III宏定义
*                       #define OS_CFG_DBG_EN             1u
*                       #define OS_CFG_STAT_TASK_EN       1u 同时初始化统计任务
*                      	#define CPU_CFG_INT_DIS_MEAS_EN   1u 
*                   (4).为了方便调试，参数OS_CFG_APP_HOOKS_EN，OS_CFG_ARG_CHK_EN都使能
*                2. 本实验推荐使用串口软件SecureCRT，要不串口打印效果不整齐。此软件在
*                   V7开发板光盘里面有。
*                3. 务必将编辑器的缩进参数和TAB设置为4来阅读本文件，要不代码显示不整齐。
*
*	修改记录 :
*		版本号   日期         作者            说明
*       V1.0    2019-05-01   Eric2013    1. ST固件库1.3.0版本
*                                        2. BSP驱动包V1.2
*                                        3. uCOS-III版本V3.07.03
*                                        4. uC/CPU版本V1.31.04
*                                        5. uC/LIB版本V1.38.03
*                                        6. STemWin版本V5.44                                       
*                                       
*	Copyright (C), 2019-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"
#include "MainTask.h"


/*
*********************************************************************************************************
*                                       静态全局变量
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
*                                      函数声明
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
*                               变量
*******************************************************************************************************
*/
static  OS_SEM   AppPrintfSemp;	/* 用于printf互斥 */


static void PrintfLogo(void);

/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: 标准c程序入口。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
int main(void)
{
    OS_ERR  err;  
	
	/* HAL库，MPU，Cache，时钟等系统初始化 */
	System_Init();

	/* 内核开启前关闭HAL的时间基准 */
	HAL_SuspendTick();
	
	/* 初始化滴答时钟，在启动任务里面开启 */	
	BSP_OS_TickInit();
		
	/* 初始化uC/OS-III 内核 */
    OSInit(&err);  

	/* 创建一个启动任务（也就是主任务）。启动任务会创建所有的应用程序任务 */
	OSTaskCreate((OS_TCB       *)&AppTaskStartTCB,  /* 任务控制块地址 */           
                 (CPU_CHAR     *)"App Task Start",  /* 任务名 */
                 (OS_TASK_PTR   )AppTaskStart,      /* 启动任务函数地址 */
                 (void         *)0,                 /* 传递给任务的参数 */
                 (OS_PRIO       )APP_CFG_TASK_START_PRIO, /* 任务优先级 */
                 (CPU_STK      *)&AppTaskStartStk[0],     /* 堆栈基地址 */
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE / 10, /* 堆栈监测区，这里表示后10%作为监测区 */
                 (CPU_STK_SIZE  )APP_CFG_TASK_START_STK_SIZE,      /* 堆栈空间大小 */
                 (OS_MSG_QTY    )0,  /* 本任务支持接受的最大消息数 */
                 (OS_TICK       )0,  /* 设置时间片 */
                 (void         *)0,  /* 堆栈空间大小 */  
                 (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
		
				 /*  定义如下：
					OS_OPT_TASK_STK_CHK      使能检测任务栈，统计任务栈已用的和未用的
					OS_OPT_TASK_STK_CLR      在创建任务时，清零任务栈
					OS_OPT_TASK_SAVE_FP      如果CPU有浮点寄存器，则在任务切换时保存浮点寄存器的内容
				 */  
                 (OS_ERR       *)&err);

	/* 启动多任务系统，控制权交给uC/OS-III */
    OSStart(&err);                                               
    
    (void)&err;
    
    return (0);
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskStart
*	功能说明: 这是一个启动任务，在多任务系统启动后，必须初始化滴答计数器。本任务主要实现按键检测。
*	形    参: p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级: 2
*********************************************************************************************************
*/
const char buf1[] = "接收到串口命令1\r\n";
const char buf2[] = "接收到串口命令2\r\n";
const char buf3[] = "接收到串口命令3\r\n";
const char buf4[] = "接收到串口命令4\r\n";
static  void  AppTaskStart (void *p_arg)
{
	OS_ERR      err;
	uint8_t    read;

   (void)p_arg;
	
	HAL_ResumeTick();
	
	CPU_Init(); /* 此函数要优先调用，因为外设驱动中使用的us和ms延迟是基于此函数的 */
 	bsp_Init();
	BSP_OS_TickEnable();
	
#if OS_CFG_STAT_TASK_EN > 0u
     OSStatTaskCPUUsageInit(&err);   
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
    
	/* 创建任务 */
    AppTaskCreate(); 

	/* 创建任务间通信机制 */
	AppObjCreate();	
	
    while (1)
	{  
		/* 需要周期性处理的程序，对应裸机工程调用的SysTick_ISR */
		bsp_ProPer1ms();
		OSTimeDly(1, OS_OPT_TIME_PERIODIC, &err);
		/* 接收到的串口命令处理 */
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
*	函 数 名: AppTaskMsgPro
*	功能说明: 消息处理，这里用作LED闪烁
*	形    参: p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级: 3
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
*	函 数 名: AppTaskUserIF
*	功能说明: 按键消息处理
*	形    参: p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级: 4
*********************************************************************************************************
*/
static void AppTaskUserIF(void *p_arg)
{
	OS_ERR  err;  
	uint8_t ucKeyCode;	/* 按键代码 */
	
	(void)p_arg;
		  
	while(1)
	{        
		ucKeyCode = bsp_GetKey();
		
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				case KEY_DOWN_K1:			  /* K1键按下 打印任务执行情况 */
					DispTaskInfo();	     
					break;
				
				default:                     /* 其他的键值不处理 */
					break;
			}
		}
		
		OSTimeDly(20, OS_OPT_TIME_DLY, &err);
	}
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskCom
*	功能说明: 暂未使用
*	形    参: p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
	优 先 级: 5
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
*	函 数 名: AppTaskGUI
*	功能说明: GUI任务，最低优先级		  			  
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级：OS_CFG_PRIO_MAX - 4u
*********************************************************************************************************
*/
static void AppTaskGUI(void *p_arg)
{	
    (void)p_arg;		/* 避免编译器告警 */

	PrintfLogo();
	
	while (1) 
	{
		MainTask();
	}
}

/*
*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建应用任务
*	形    参：p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
*********************************************************************************************************
*/
static  void  AppTaskCreate (void)
{
	OS_ERR      err;
	
	/**************创建MsgPro任务*********************/
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
				 
	/**************创建USER IF任务*********************/
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

	/**************创建COM任务*********************/
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
				 
	/**************创建GUI任务*********************/			 
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
*	函 数 名: AppObjCreate
*	功能说明: 创建任务通讯
*	形    参: p_arg 是在创建该任务时传递的形参
*	返 回 值: 无
*********************************************************************************************************
*/
static  void  AppObjCreate (void)
{
	OS_ERR      err;
	
	/* 
	   创建信号量数值为1的时候可以实现互斥功能，也就是只有一个资源可以使用 
	   本例程是将串口1的打印函数作为保护的资源。防止串口打印的时候被其它任务抢占
	   造成串口打印错乱。
	*/
	OSSemCreate((OS_SEM    *)&AppPrintfSemp,
				(CPU_CHAR  *)"AppPrintfSemp",
				(OS_SEM_CTR )1,
				(OS_ERR    *)&err);
}

/*
*********************************************************************************************************
*	函 数 名: App_Printf
*	功能说明: 线程安全的printf方式		  			  
*	形    参: 同printf的参数。
*             在C中，当无法列出传递函数的所有实参的类型和数目时,可以用省略号指定参数表
*	返 回 值: 无
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

	/* 互斥操作 */
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
*	函 数 名: DispTaskInfo
*	功能说明: 将uCOS-III任务信息通过串口打印出来
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void DispTaskInfo(void)
{
	OS_TCB      *p_tcb;	        /* 定义一个任务控制块指针, TCB = TASK CONTROL BLOCK */
	float CPU = 0.0f;
	CPU_SR_ALLOC();

	CPU_CRITICAL_ENTER();
    p_tcb = OSTaskDbgListPtr;
    CPU_CRITICAL_EXIT();
	
	/* 打印标题 */
	App_Printf("===============================================================\r\n");
	App_Printf(" 优先级 使用栈 剩余栈 百分比 利用率   任务名\r\n");
	App_Printf("  Prio   Used  Free   Per    CPU     Taskname\r\n");

	/* 遍历任务控制块列表(TCB list)，打印所有的任务的优先级和名称 */
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
*	函 数 名: PrintfLogo
*	功能说明: 打印例程名称和例程发布日期, 接上串口线后，打开PC机的超级终端软件可以观察结果
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
	printf("*************************************************************\n\r");
	
	/* 检测CPU ID */
	{
		uint32_t CPU_Sn0, CPU_Sn1, CPU_Sn2;
		
		CPU_Sn0 = *(__IO uint32_t*)(0x1FF1E800);
		CPU_Sn1 = *(__IO uint32_t*)(0x1FF1E800 + 4);
		CPU_Sn2 = *(__IO uint32_t*)(0x1FF1E800 + 8);

		printf("\r\nCPU : STM32H743XIH6, BGA240, 主频: %dMHz\r\n", SystemCoreClock / 1000000);
		printf("UID = %08X %08X %08X\n\r", CPU_Sn2, CPU_Sn1, CPU_Sn0);
	}

	printf("\n\r");

	
	/* 打印CM7 CMSIS和ST的HAL库版本 */
	printf("* CM7 CMSIS 版本  : %x\r\n", __CM7_CMSIS_VERSION);
	printf("* HAL库版本  : %x (STM32H7xx HAL Driver)\r\n", HAL_GetHalVersion());
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
