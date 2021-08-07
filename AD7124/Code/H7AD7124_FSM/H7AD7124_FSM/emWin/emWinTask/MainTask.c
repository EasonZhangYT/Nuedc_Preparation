/*
*********************************************************************************************************
*	                                  
*	模块名称 : 简易时钟表盘界面设计
*	文件名称 : MainTask.c
*	版    本 : V1.0
*	说    明 : 实验内容
*              1. 本实例有两个值得大家学习的地方:
*                 （1）函数GUI_MEMDEV_CreateAuto和GUI_MEMDEV_DrawAuto的使用，保证时钟表盘不闪烁。
*                 （2）抗锯齿多边形的绘制GUI_AA_FillPolygon。
*              2. 本设计界面仅支持演示。
*              3. 注意演示时间和指针旋转速度的设置，防止指针旋转的时候出现卡顿的现象。
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



/*
*********************************************************************************************************
*                                       引用外部定义
*********************************************************************************************************
*/ 
extern GUI_CONST_STORAGE GUI_FONT GUI_FontYahei;
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_armflySmall;
extern GUI_CONST_STORAGE GUI_BITMAP _bmSpeedometerScale;
extern GUI_CONST_STORAGE GUI_BITMAP bmclock;

/*
*********************************************************************************************************
*                                       宏定义
*********************************************************************************************************
*/
#define countof(Obj) (sizeof(Obj) / sizeof(Obj[0]))
#define DEG2RAD      (3.1415926f / 180)
#define MAG          4

/*
*********************************************************************************************************
*                                       数值
*********************************************************************************************************
*/ 
static const GUI_POINT _aNeedle[] = {
  { MAG * ( -1), MAG * (  0 ) },
  { MAG * (-1), MAG * (-50 ) },
  { MAG * (0), MAG * (-65 ) },
  { MAG * ( 1), MAG * (-50 ) },
  { MAG * ( 1), MAG * (0 ) },
};

static const GUI_POINT _aNeedle1[] = {
  { MAG * ( -2), MAG * (  0 ) },
  { MAG * (-2), MAG * (-50 ) },
  { MAG * (0), MAG * (-65 ) },
  { MAG * ( 2), MAG * (-50 ) },
  { MAG * ( 2), MAG * (0 ) },
};

static const GUI_POINT _aNeedle2[] = {
  { MAG * ( -2), MAG * (  0 ) },
  { MAG * (-2), MAG * (-40 ) },
  { MAG * (0), MAG * (-55 ) },
  { MAG * ( 2), MAG * (-40 ) },
  { MAG * ( 2), MAG * (0 ) },
};

/*
*********************************************************************************************************
*                                       类型定义
*********************************************************************************************************
*/ 
typedef struct {
  GUI_AUTODEV_INFO AutoDevInfo;  // Information about what has to be displayed
  GUI_POINT        aPoints[7];   // Polygon data
  float            Angle;
  
  GUI_POINT        aPoints1[7];   // Polygon data
  float            Angle1;
	
  GUI_POINT        aPoints2[7];   // Polygon data
  float            Angle2;
} PARAM;


/*
*********************************************************************************************************
*	函 数 名: _Draw
*	功能说明: 此函数被GUI_MEMDEV_DrawAuto所调用
*	形    参：p   参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _Draw(void * p) {
	PARAM * pParam;

	pParam = (PARAM *)p;

    /* 绘制背景 ************************************************************/
	if (pParam->AutoDevInfo.DrawFixed) 
	{
		/* 清除部分背景 */
		GUI_ClearRect ( (LCD_GetXSize()- bmclock.XSize)/2, 
					    (LCD_GetYSize()- bmclock.YSize)/2, 
					    (LCD_GetXSize()- bmclock.XSize)/2+bmclock.XSize, 
					    (LCD_GetYSize()- bmclock.YSize)/2+bmclock.YSize);
 		/* 显示时钟图片 */
 		GUI_DrawBitmap(&bmclock, 
 		               (LCD_GetXSize()- bmclock.XSize)/2, 
 		               (LCD_GetYSize()- bmclock.YSize)/2);
//		GUI_DrawBitmap(&bmLogo_armflySmall, 2, 2);
	}
	
	/* 绘制移动的指针 ************************************************************/
	GUI_SetColor(GUI_RED);
	GUI_AA_FillPolygon(pParam->aPoints, countof(_aNeedle), MAG * LCD_GetXSize()/2, MAG * (LCD_GetYSize()/2+17));
	
	GUI_SetColor(GUI_RED);
	GUI_AA_FillPolygon(pParam->aPoints1, countof(_aNeedle1), MAG * LCD_GetXSize()/2, MAG * (LCD_GetYSize()/2+17));
	
	GUI_SetColor(GUI_RED);
	GUI_AA_FillPolygon(pParam->aPoints2, countof(_aNeedle2), MAG * LCD_GetXSize()/2, MAG * (LCD_GetYSize()/2+17));
	
	/* 绘制前景色 ************************************************************/
	if (pParam->AutoDevInfo.DrawFixed) 
	{
//		GUI_SetTextMode(GUI_TM_TRANS);
//		GUI_SetColor(GUI_BLACK);
//		GUI_SetFont(&GUI_Font24B_ASCII);
//		GUI_DispStringHCenterAt("armfly", LCD_GetXSize()/2, LCD_GetYSize()/2+30);
	}
}

/*
*********************************************************************************************************
*	函 数 名: _DemoScale
*	功能说明: 演示函数
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void _DemoScale(void) 
{
	GUI_AUTODEV AutoDev;      /* 内存设备 */
	PARAM       Param;        /* PARAM类型变量 */

    int         t0 = 36000;   /* 用于三个指针的计数 */
	int         t1 = 36000;
    int         t2 = 36000;

	/* 设置背景上的显示内容 */
	GUI_SetBkColor(GUI_BLUE);
//	GUI_SetBkColor(GUI_WHITE); /* 设置背景色 */
	GUI_Clear();
	GUI_SetFont(&GUI_Font24B_1);
	GUI_DispStringAt("Draw Panel", 0, 0);
	
	GUI_CURSOR_Show();
	GUI_DrawBitmap(&bmLogo_armflySmall, 2, 2);
	GUI_CURSOR_Hide();
	
	GUI_UC_SetEncodeUTF8();
	GUI_SetFont(&GUI_FontYahei);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringHCenterAt("简易始终表盘界面设计", LCD_GetXSize()/2, 2);
	GUI_UC_SetEncodeUTF8();

	/* 使能抗锯齿 */
	GUI_AA_EnableHiRes();
	/* 设置抗锯齿因数 */
	GUI_AA_SetFactor(MAG);
	/* 创建自动设备对象 */
	GUI_MEMDEV_CreateAuto(&AutoDev);


	while (1) 
	{
		/* 第一个指针计数，用于旋转速度 */
		t0-= 100;
		if(t0 < 0)
		{
			t0 = 36000;
		}

		/* 第二个指针计数，用于旋转速度 */
		t1-= 10;
		if(t1 < 0)
		{
			t1 = 36000;
		}

		/* 第三个指针计数，用于旋转速度 */
		t2-= 1;
		if(t2 < 0)
		{
			t2 = 36000;
		}

		/* 旋转第一个指针 */
		Param.Angle= t0;
		Param.Angle *= 3.1415926f / 18000;
		GUI_RotatePolygon(Param.aPoints, _aNeedle, countof(_aNeedle), Param.Angle);

		/* 旋转第二个指针 */
		Param.Angle1= t1;
		Param.Angle1 *= 3.1415926f / 18000;
		GUI_RotatePolygon(Param.aPoints1, _aNeedle1, countof(_aNeedle1), Param.Angle1);

		/* 旋转第三个指针 */
		Param.Angle2= t2;
		Param.Angle2 *= 3.1415926f / 18000;
		GUI_RotatePolygon(Param.aPoints2, _aNeedle2, countof(_aNeedle2), Param.Angle2);
		GUI_MEMDEV_DrawAuto(&AutoDev, &Param.AutoDevInfo, &_Draw, &Param);
		
		/* 延迟时间 */
		GUI_Delay(10);
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
	
	/*
       触摸校准函数默认是注释掉的，电阻屏需要校准，电容屏无需校准。如果用户需要校准电阻屏的话，执行
	   此函数即可，会将触摸校准参数保存到EEPROM里面，以后系统上电会自动从EEPROM里面加载。
	*/
    //TOUCH_Calibration();
	
	while (1) 
	{
		_DemoScale();
	}
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
