/*
*********************************************************************************************************
*	                                  
*	模块名称 : 医疗监护仪简易界面设计
*	文件名称 : MainTask.c
*	版    本 : V1.0
*	说    明 : 实验内容
*              1. 本实例有三个值得大家学习的地方:
*                 （1）同一个窗口多定时器的创建。
*                 （2）通过外部按键创建窗口。
*                 （3）多波形的显示。
*              2. 按键K2按键创建病人信息窗口。
*                 按下K3关闭创建的窗口。
*              
*	修改记录 :
*		版本号   日期         作者          说明
*		V1.0    2016-11-26   Eric2013  	    首版    
*                                     
*	Copyright (C), 2015-2020, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "MainTask.h"
#include "includes.h"
//#include "AD1292.h"
#include "AD7124.h" 

/*
*********************************************************************************************************
*                                       引用外部定义
*********************************************************************************************************
*/ 
extern GUI_CONST_STORAGE GUI_FONT GUI_FontYahei;
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_armflySmall;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontFontSpecialChar;

/*
*********************************************************************************************************
*                                      变量和数组
*********************************************************************************************************
*/ 
WM_HWIN hWinInfo;    /* 信息窗口句柄 */
WM_HWIN  hWinMain;   /* 主窗口句柄 */
static GRAPH_DATA_Handle  ahData[3];                         /* 用于 GRAPH_DATA 类型的句柄 */
static GUI_COLOR _aColor[3] = {GUI_YELLOW,GUI_GREEN,GUI_RED};/* 三种曲线的颜色值 */

/* 下面是为三种曲线定义好的曲线值 */
const static int _HeartBeat[] = {
    2,   4,   6,   8,  10,   6,   2,   0,   0,   0,
   -8,  16,  40,  64,  88,  58,  28,  -2, -32, -30,
  -20, -10,   0,   2,   2,   4,   4,   6,   6,   8,
    8,  10,  12,  14,  16,  18,  20,  16,  12,   8,
    4,   2,   2,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

const static int _HeartBeat1[] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    2,   4,   8,  16,  32,  64,   0,   0,   0,   0
};

const static int _HeartBeat2[] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   60,   0, -60, -32,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

/*
*********************************************************************************************************
*                                     宏定义
*********************************************************************************************************
*/ 
#define ID_WINDOW_0    (GUI_ID_USER + 0x00)
#define ID_FRAMEWIN_0  (GUI_ID_USER + 0x01)
#define ID_GRAPH_0     (GUI_ID_USER + 0x02)
#define ID_TEXT_0      (GUI_ID_USER + 0x03)
#define ID_TEXT_1      (GUI_ID_USER + 0x04)
#define ID_TEXT_2      (GUI_ID_USER + 0x05)
#define ID_TEXT_3      (GUI_ID_USER + 0x06)
#define ID_TEXT_4      (GUI_ID_USER + 0x07)
#define ID_TEXT_5      (GUI_ID_USER + 0x08)
#define ID_TEXT_6      (GUI_ID_USER + 0x09)
#define ID_TEXT_7      (GUI_ID_USER + 0x0A)
#define ID_TEXT_8      (GUI_ID_USER + 0x0B)
#define ID_TEXT_9      (GUI_ID_USER + 0x0C)
#define ID_TEXT_10     (GUI_ID_USER + 0x0D)
#define ID_TEXT_11     (GUI_ID_USER + 0x0E)
#define ID_TEXT_12     (GUI_ID_USER + 0x0F)
#define ID_TEXT_13     (GUI_ID_USER + 0x10)
#define ID_TEXT_14     (GUI_ID_USER + 0x11)

#define ID_TimerGraph   0
#define ID_TimerTime    1

/*
*********************************************************************************************************
*                                     对话框GUI_WIDGET_CREATE_INFO类型数组
*********************************************************************************************************
*/ 
static const GUI_WIDGET_CREATE_INFO _aDialogCreateInfo[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 80, 40, 200, 220, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 10, 12, 190, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_1, 10, 37, 190, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_2, 10, 60, 190, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_3, 10, 85, 190, 20, 0, 0x64, 0 },
};

/*
*********************************************************************************************************
*	函 数 名: _cbDialogInfo
*	功能说明: 信息窗口的回调函数
*	形    参：pMsg   参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _cbDialogInfo(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;

	switch (pMsg->MsgId) 
	{
		/* 显示armfly的logo*/
		case WM_PAINT:
			GUI_DrawBitmap(&bmLogo_armflySmall, 50,130);
			break;
		
		case WM_INIT_DIALOG:
			
			/* 初始化框架窗口 */
			hItem = pMsg->hWin;
			FRAMEWIN_SetFont(hItem, &GUI_FontYahei);
			FRAMEWIN_SetText(hItem, "病人信息");
			FRAMEWIN_SetTextColor(hItem, 0x00000000);
		
			/* 初始化ID_TEXT_0到ID_TEXT_3*/
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			TEXT_SetFont(hItem, &GUI_FontYahei);
			TEXT_SetText(hItem, "床    号:1");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetFont(hItem, &GUI_FontYahei);
			TEXT_SetText(hItem, "病人类型:成人");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
			TEXT_SetFont(hItem, &GUI_FontYahei);
			TEXT_SetText(hItem, "病人姓名:张三");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
			TEXT_SetFont(hItem, &GUI_FontYahei);
			TEXT_SetText(hItem, "性    别:男");
			break;
			
		default:
			WM_DefaultProc(pMsg);
	}
}


/*
*********************************************************************************************************
*	函 数 名: CreateFramewin
*	功能说明: 信息窗口的创建
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void CreateFramewin(void) 
{
	hWinInfo = GUI_CreateDialogBox(_aDialogCreateInfo, GUI_COUNTOF(_aDialogCreateInfo), _cbDialogInfo, WM_HBKWIN, 0, 0);
}

/*
*********************************************************************************************************
*	函 数 名: DeleteFramewin
*	功能说明: 信息窗口的删除
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void DeleteFramewin(void) 
{
	WM_DeleteWindow(hWinInfo);
}

/*
*********************************************************************************************************
*                                     对话框GUI_WIDGET_CREATE_INFO类型数组
*********************************************************************************************************
*/ 
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = 
{
	{ WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 854, 480, 0, 0x0, 0 },
	{ GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 8, 25, 668, 252, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 8, 27, 80, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_1, 8, 110, 80, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_2, 8, 193, 80, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_3, 681, 26, 117, 83, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_4, 681, 111, 117, 83, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_5, 681, 195, 117, 83, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_6, 770, 31, 27, 17, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_7, 766, 113, 28, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_8, 769, 199, 31, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_9, 672, 5, 71, 17, 0, 0x64, 0  },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_10, 749, 5, 57, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_11, 281, 281, 300, 83, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_12, 281, 365, 300, 83, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_13, 680, 281+32, 128, 83, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_14, 680, 365+32, 128, 83, 0, 0x64, 0 },
};

/*
*********************************************************************************************************
*	函 数 名: Caculate_RTC
*	功能说明: 显示RTC时间
*	形    参：pMsg 指针参数            
*	返 回 值: 无
*********************************************************************************************************
*/
extern RTC_TimeTypeDef  RTC_TimeStructure;
extern RTC_DateTypeDef  RTC_DateStructure;
static void Caculate_RTC(WM_MESSAGE * pMsg)
{
	  char buf[30];
	  WM_HWIN hWin = pMsg->hWin;

//	  HAL_RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
//	  HAL_RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);

	  sprintf(buf, 
	          "%0.2d:%0.2d:%0.2d", 
			  RTC_TimeStructure.Hours, 
			  RTC_TimeStructure.Minutes,
			  RTC_TimeStructure.Seconds);
	 TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_10), buf);
 
	  sprintf(buf, 
	          "20%0.2d/%0.2d/%0.2d", 
			  RTC_DateStructure.Year, 
			  RTC_DateStructure.Month, 
			  RTC_DateStructure.Date);
	  TEXT_SetText(WM_GetDialogItem(hWin,ID_TEXT_9), buf); 			  	          
}

/*
*********************************************************************************************************
*	函 数 名: _cbDialogInfo
*	功能说明: 主窗口的回调函数
*	形    参：pMsg   参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
float fProbe;
static void _cbDialog(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	char buf[32];
	static 	char Index = 0;

	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
			
			/* 创建曲线 */
			hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
			GRAPH_SetBorder(hItem, 0, 0, 0, 0);
			ahData[0] = GRAPH_DATA_YT_Create(_aColor[0], 512, 0, 0);
			ahData[1] = GRAPH_DATA_YT_Create(_aColor[1], 700, 0, 0);
			ahData[2] = GRAPH_DATA_YT_Create(_aColor[2], 700, 0, 0);

			/* 为绘图控件添加数据对象 */
			GRAPH_AttachData(hItem, ahData[0]);
			GRAPH_AttachData(hItem, ahData[1]);
			GRAPH_AttachData(hItem, ahData[2]);
			WIDGET_SetEffect(hItem, &WIDGET_Effect_None);

			/* 创建文本 */
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			TEXT_SetTextColor(hItem, 0x000000FF);
			TEXT_SetFont(hItem, &GUI_FontYahei);
			TEXT_SetText(hItem, "心率");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetTextColor(hItem, 0x0000FF00);
			TEXT_SetFont(hItem, &GUI_FontYahei);
			TEXT_SetText(hItem, "呼吸率");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
			TEXT_SetTextColor(hItem, 0x0000FFFF);
			TEXT_SetFont(hItem, &GUI_FontYahei);
			TEXT_SetText(hItem, "脉搏率");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
			TEXT_SetFont(hItem, GUI_FONT_D48);
			TEXT_SetTextColor(hItem, 0x000000FF);
			TEXT_SetText(hItem, "50");
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
			TEXT_SetFont(hItem, GUI_FONT_D48);
			TEXT_SetText(hItem, "60");
			TEXT_SetTextColor(hItem, 0x0000FF00);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
			TEXT_SetTextColor(hItem, 0x0000FFFF);
			TEXT_SetFont(hItem, GUI_FONT_D48);
			TEXT_SetText(hItem, "70");
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
			TEXT_SetTextColor(hItem, 0x0000FFFF);
			TEXT_SetFont(hItem, GUI_FONT_D48);
			TEXT_SetText(hItem, "0");
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
			TEXT_SetTextColor(hItem, 0x0000FFFF);
			TEXT_SetFont(hItem, GUI_FONT_D48);
			TEXT_SetText(hItem, "0");
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
			TEXT_SetFont(hItem, GUI_FONT_13B_ASCII);
			TEXT_SetTextColor(hItem, 0x000000FF);
			TEXT_SetText(hItem, "bmp");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
			TEXT_SetFont(hItem, GUI_FONT_13B_ASCII);
			TEXT_SetTextColor(hItem, 0x0000FF00);
			TEXT_SetText(hItem, "BrPM");

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
			TEXT_SetFont(hItem, GUI_FONT_13B_ASCII);
			TEXT_SetText(hItem, "bmp");
			TEXT_SetTextColor(hItem, 0x0000FFFF);

			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
			TEXT_SetFont(hItem, GUI_FONT_16B_ASCII);
			TEXT_SetTextColor(hItem, 0x00FFFFFF);
			TEXT_SetText(hItem, "2014-06-17");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
			TEXT_SetFont(hItem, GUI_FONT_16B_ASCII);
			TEXT_SetTextColor(hItem, 0x00FFFFFF);
			TEXT_SetText(hItem, "00:00:00");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
			TEXT_SetFont(hItem, GUI_FONT_32B_ASCII);
			TEXT_SetTextColor(hItem, 0x00FFFFFF);
			TEXT_SetText(hItem, "mmHg");
			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
			TEXT_SetFont(hItem, &GUI_FontFontSpecialChar);
			TEXT_SetTextColor(hItem, 0x00FFFFFF);
			TEXT_SetText(hItem, "℃");
			break;
			
		case WM_PAINT:
			/* 显示标题并重绘背景色 */
		    GUI_SetBkColor(0x00408000);
			GUI_ClearRect(0,0,LCD_GetXSize()-1, 24);
			GUI_SetFont(&GUI_FontYahei);
			GUI_DispStringAt("床号 1 姓名: 张三", 5, 3);
			GUI_SetBkColor(GUI_BLACK);
			GUI_ClearRect(0,25,LCD_GetXSize()-1, LCD_GetYSize()-1);

		    /* 用于绘制三个白色的圆角方框 */
			GUI_SetColor(GUI_WHITE);
			GUI_AA_DrawRoundedRect(680,  25, 799, 108, 6);
			GUI_AA_DrawRoundedRect(680, 110, 799, 193, 6);
			GUI_AA_DrawRoundedRect(680, 195, 799, 276, 6);
		
			GUI_AA_DrawRoundedRect(280, 280, 799, 363, 6);
			GUI_AA_DrawRoundedRect(280, 366, 799, 447, 6);
			break;
			
		case WM_TIMER:
			if(WM_GetTimerId(pMsg->Data.v) == ID_TimerGraph)
		    {
				unsigned int i;
//				if(Flag_HALF_Full == 1)
//				{
//					for(i = 0; i < 511; i++ )
//					{
//						GRAPH_DATA_YT_AddValue(ahData[0], (Store_Data_2[i]/500)-200);
//	//					GRAPH_DATA_YT_AddValue(ahData[1], (_HeartBeat1[Index]/2)+100);
//	//					GRAPH_DATA_YT_AddValue(ahData[2],(_HeartBeat2[Index]/2)+190);
//					}
//				}
//				else if(Flag_HALF_Full == 2)
//				{
//					for(i = 0; i < 511; i++ )
//					{
//						GRAPH_DATA_YT_AddValue(ahData[0], (Store_Data_1[i]/500)-200);
//					}
//				}
				
				if (++Index == GUI_COUNTOF(_HeartBeat)) 
				{
					Index = 0;
				}

				/* 重启定时器 */
				WM_RestartTimer(pMsg->Data.v, 512);
			}
			else if(WM_GetTimerId(pMsg->Data.v) == ID_TimerTime)
//			else if(0)
			{
				/* 显示文本ID_TEXT_5的动态数据 */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
				sprintf(buf, "%d", rand()%100);
				TEXT_SetText(hItem, buf);
			
				/* 显示文本ID_TEXT_4的动态数据 */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
				sprintf(buf, "%d", rand()%100);
				TEXT_SetText(hItem, buf);

				/* 显示文本ID_TEXT_3的动态数据 */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
				sprintf(buf, "%d", rand()%100);
				TEXT_SetText(hItem, buf);
				
				/* 显示文本ID_TEXT_11的动态数据 */
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
//				sprintf(buf, "%7.1f", (AD7124.fvalue + 43.5)/12.5 );
				fProbe = (sAD7124Signle[0].fvalue + 53.35)/12.5;
				sprintf(buf, "%7.1f", fProbe );
				TEXT_SetText(hItem, buf);
				
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
//				sprintf(buf, "%7.1f", AD7124.fvalue );
//				fProbe = -0.000033333*sAD7124Signle[1].fvalue + 62.433;
				sprintf(buf, "%7.1f", -0.000033333*sAD7124Signle[1].fvalue + 62.433 );
				TEXT_SetText(hItem, buf);
				
				/* 显示时间和日期 */
				Caculate_RTC(pMsg);
				
				/* 重启定时器 */
				WM_RestartTimer(pMsg->Data.v, 1000);
			}
			break;
		
	    /* 创建信息窗口 */
		case MSG_CreateInfo:
			if(!WM_IsWindow(hWinInfo))
			{
				CreateFramewin();
			}
			break;
		
		/* 删除信息窗口 */
		case MSG_DeleteInfo:
			if(WM_IsWindow(hWinInfo))
			{
				DeleteFramewin();				
			}
			break;
		
		default:
			WM_DefaultProc(pMsg);
	}
}

/*
*********************************************************************************************************
*	函 数 名: MainTask
*	功能说明: GUI主函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void MainTask(void) 
{
	/* 初始化 */
	GUI_Init();
	
	GUI_SetOrientation(5);	
	/*
	 关于多缓冲和窗口内存设备的设置说明
	   1. 使能多缓冲是调用的如下函数，用户要在LCDConf_Lin_Template.c文件中配置了多缓冲，调用此函数才有效：
		  WM_MULTIBUF_Enable(1);
	   2. 窗口使能使用内存设备是调用函数：WM_SetCreateFlags(WM_CF_MEMDEV);
	   3. 如果emWin的配置多缓冲和窗口内存设备都支持，二选一即可，且务必优先选择使用多缓冲，实际使用
		  STM32F429BIT6 + 32位SDRAM + RGB565/RGB888平台测试，多缓冲可以有效的降低窗口移动或者滑动时的撕裂
		  感，并有效的提高流畅性，通过使能窗口使用内存设备是做不到的。
	   4. 所有emWin例子默认是开启三缓冲。
	*/
	WM_MULTIBUF_Enable(1);
	
	GUI_CURSOR_Show();
	
	/*
       触摸校准函数默认是注释掉的，电阻屏需要校准，电容屏无需校准。如果用户需要校准电阻屏的话，执行
	   此函数即可，会将触摸校准参数保存到EEPROM里面，以后系统上电会自动从EEPROM里面加载。
	*/
    //TOUCH_Calibration();
	
	hWinMain = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	
	/* 使能UTF-8解码用于汉字显示 */
	GUI_UC_SetEncodeUTF8();
	
	/* 创建两个定时器 */
	WM_CreateTimer(WM_GetClientWindow(hWinMain), /* 接受信息的窗口的句柄 */
				   ID_TimerGraph, 	         /* 用户定义的Id。如果不对同一窗口使用多个定时器，此值可以设置为零。 */
				   10,                       /* 周期，此周期过后指定窗口应收到消息*/
				   0);	                     /* 留待将来使用，应为0 */
	
	WM_CreateTimer(WM_GetClientWindow(hWinMain), /* 接受信息的窗口的句柄 */
				   ID_TimerTime, 	         /* 用户定义的Id。如果不对同一窗口使用多个定时器，此值可以设置为零。 */
				   10,                       /* 周期，此周期过后指定窗口应收到消息*/
				   0);	                     /* 留待将来使用，应为0 */
	
	while (1) 
	{
//		AD7124.CODE = AD7124_RDATA();
////		AD7124.fvalue = AD7124_CodeValue(0,AD7124.CODE,2.5,1000000);
//		AD7124.fvalue = AD7124_CodeValue(1,AD7124.CODE,2.5,1000000);
//		AD7124_RDATA_Multi();
//		AD7124_RDATA_Single();
		if( AD7124_RDATA_Single() == 1 )
		{
			sAD7124Signle[0].fvalue = AD7124_CodeValue(1,sAD7124Signle[0].CODE,2.5,1000000);
			sAD7124Signle[1].fvalue = AD7124_CodeValue(1,sAD7124Signle[1].CODE,2.5,1000000);
		}
//		GUI_Delay(200);
		GUI_Exec();
	}
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
