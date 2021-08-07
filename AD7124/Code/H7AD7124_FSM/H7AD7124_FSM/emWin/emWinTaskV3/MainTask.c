/*
*********************************************************************************************************
*	                                  
*	模块名称 : 酿造机过程动态演示
*	文件名称 : MainTask.c
*	版    本 : V1.0
*	说    明 : 实验内容
*              1. 这个工程主要是动态过程的演示，无需使用触摸功能。
*              2. 主要演示了两个动态过程，每个过程都是建立在一个窗口上，通过设置
*                 窗口的显示层从而实现轮流显示。
*              3. 刷新的时候，将静态图和动态图分开，只需刷新动态图即可。
*              4. 注意函数GUI_SetClipRect的使用。
*              
*	修改记录 :
*		版本号   日期         作者          说明
*		V1.0    2016-11-26   Eric2013  	    首版    
*                                     
*	Copyright (C), 2015-2020, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"
#include "MainTask.h"


/*
*********************************************************************************************************
*                                         宏定义
*********************************************************************************************************
*/
#define COLOR_BEER       0x0DC5FD

#define APP_NEXT_FRAME  (WM_USER + 0)
#define APP_DRAW        (WM_USER + 1)
#define APP_HIDE        (WM_USER + 2)
#define APP_FIRST_FRAME (WM_USER + 3)
#define GRID_DRAW_FULL  (WM_USER + 4)
#define GRID_DRAW_START (WM_USER + 5)

/*
*********************************************************************************************************
*                                         extern
*********************************************************************************************************
*/
extern GUI_CONST_STORAGE GUI_FONT GUI_FontF16B_AA;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontF19B_AA;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontF24B_AA;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Bubbles;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_ArrowDown;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_ArrowDown_2;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_ArrowLeft;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_ArrowRight;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Barrel;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Tank_2;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_B;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_SeggerLogo;

extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_armflySmall;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Detail_Mashing_00;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Detail_Mashing_01;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Detail_Mashing_02;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Detail_Mashing_03;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Detail_Mashing_04;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Detail_Mashing_05;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_00;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_01;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_02;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_03;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_04;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Boiling_05;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_00;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_01;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_02;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_03;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_04;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Lautering_05;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_00;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_01;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_02;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_03;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_04;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Mashing_05;

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_00;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_01;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_02;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_03;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_04;
extern GUI_CONST_STORAGE GUI_BITMAP bm320_Overview_Whirlpool_05;

/*
*********************************************************************************************************
*                                         变量
*********************************************************************************************************
*/
typedef struct {
  int TextY[5];
  int Cnt;
  int DrawBk;
} BkState;

typedef struct {
  int Cnt;
  int Draw;
} MashingState;

static const short _aTemperature[] = { 50, 51, 52, 52, 53, 54, 55, 55, 55, 55, 55,  //   0 -  10
                                       55, 55, 55, 55, 55, 55, 55, 55, 55, 55,      //  11 -  20
                                       55, 55, 55, 55, 55, 56, 57, 58, 58, 59,      //  21 -  30
                                       60, 61, 62, 62, 63, 64, 64, 64, 64, 64,      //  31 -  40
                                       64, 64, 64, 64, 64, 64, 64, 64, 64, 64,      //  41 -  50
                                       64, 64, 64, 64, 64, 64, 64, 64, 64, 64,      //  51 -  60
                                       64, 64, 64, 64, 64, 64, 64, 64, 64, 64,      //  61 -  70
                                       64, 64, 64, 64, 64, 65, 66, 67, 68, 68,      //  71 -  80
                                       69, 70, 71, 72, 72, 72, 72, 72, 72, 72,      //  81 -  90
                                       72, 72, 72, 72, 72, 72, 72, 72, 72, 72,      //  91 - 100
                                       73, 74, 74, 75, 76, 76, 77, 77, 78, 78,      // 101 - 110
                                       78, 78, 78, 78, 78, 78, 78, 78, 78, 78,      // 111 - 120
                                       78, 78, 78, 78                               // 121 - 124
                                     };

static int _iTemperature;
static int _iWort;
static int _iGraphCnt;
static int _Cnt;

/*
*********************************************************************************************************
*	函 数 名: _DrawMovingBitmapClipRect
*	功能说明: 这个函数的主要功能是实现位图的动态移动效果，并通过函数GUI_SetClipRect()限制输出的裁剪矩形
*             默认情况下，裁剪区域限制为配置的 （虚拟）显示器大小。
*             某些情况下，使用通过此函数可以设置的较小的裁剪矩形比较有用。
*             引用的矩形应保持不变，直到使用空指针再次调用该函数。
*	形    参：pBitmap     位图地址
*             ClipRectX0  裁剪矩形区首地址
*             ClipRectY0  裁剪矩形区首地址
*             ClipRectX1  裁剪矩形区结束地址
*             ClipRectY1  裁剪矩形区结束地址 
* 			  Step		  Number of current step
*			  StepDist	  Distance of a single step, use negative values to turn direction	
*             MovDir	  0 == x; 1 == y;								 
*	返 回 值: 无
*********************************************************************************************************
*/
static void _DrawMovingBitmapClipRect(GUI_CONST_STORAGE GUI_BITMAP * pBitmap,
                                                               int   ClipRectX0, int ClipRectY0,
                                                               int   ClipRectX1, int ClipRectY1,
                                                               int   Step,      
                                                               int   StepDist, 
                                                               int   MovDir)   
{ 
	int Stop = 0;
	GUI_RECT Rect;
	int x0, y0, x1, y1, dx, dy;

	Rect.x0 = ClipRectX0;
	Rect.y0 = ClipRectY0;
	Rect.x1 = ClipRectX1;
	Rect.y1 = ClipRectY1;

	GUI_SetClipRect(&Rect);
	
	y0 = ClipRectY0;
	
	/* 根据X轴或者Y轴的递增方向确定位图的起始点，并确定每次的增长值 */
	if (MovDir) 
	{
		dx = 0;
		dy = pBitmap->YSize;
		x0 = ClipRectX0;
		y0 = ClipRectY0 - pBitmap->YSize + Step * StepDist;
	} 
	else 
	{
		dx = pBitmap->XSize;
		dy = 0;
		x0 = ClipRectX0 - pBitmap->XSize + Step * StepDist;
		y0 = ClipRectY0;
	}
	
	/* 确定位图的结束点 */
	x1 = x0 + pBitmap->XSize - 1;
	y1 = y0 + pBitmap->YSize - 1;
	
	/* 根据设置的显示区域，用位图将显示区域填充满 */
	do 
	{
		GUI_DrawBitmap(pBitmap, x0, y0);
		x0 += dx;
		y0 += dy;
		x1 += dx;
		y1 += dy;
		if ((x0 > ClipRectX1) || (y0 > ClipRectY1)) 
		{
			Stop = 1;
		}
	} while (Stop == 0);
	
	GUI_SetClipRect(NULL);
}

/*
*********************************************************************************************************
*	函 数 名: _OverviewStatic
*	功能说明: 绘制静态图，用于窗口hWinBk的重绘部分
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void _OverviewStatic(void) 
{
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_DrawBitmap( &bm320_Overview_Whirlpool_B    , 270,  88);
	GUI_DrawBitmap( &bm320_Overview_Tank_2         ,   7, 125);
	GUI_DrawBitmap( &bm320_Overview_Tank_2         ,  88, 125);
	GUI_DrawBitmap( &bm320_Overview_Barrel         , 184, 184);
	GUI_DrawBitmap( &bm320_Overview_Barrel         , 227, 184);
	GUI_DrawBitmap( &bm320_Overview_Barrel         , 271, 184);
	//
	// Draw pipes
	//
	GUI_SetColor(GUI_BLACK);
	//
	// 第一步： whirlpooling 和 fermenting之间的长连接管
	//
	GUI_FillRect(304,  88, 304, 109);
	GUI_FillRect(313,  88, 313, 118);
	GUI_FillRect( 35, 109, 303, 109);
	GUI_FillRect( 44, 118, 312, 118);
	GUI_FillRect( 35, 110,  35, 123);
	GUI_FillRect( 44, 119,  44, 123);
	//
	// 第二步：fermenting和storage之间的短连接管
	//
	GUI_FillRect( 71, 162,  87, 162);
	GUI_FillRect( 71, 171,  87, 171);
	//
	// 第三步：torage 和 barrels之间的长连接管
	//
	GUI_FillRect(152, 162, 291, 162);
	GUI_FillRect(152, 171, 199, 171);
	GUI_FillRect(204, 171, 242, 171);
	GUI_FillRect(247, 171, 286, 171);
	//
	// 第四步：storage 和 barrels直接的短管连接
	//
	GUI_FillRect(199, 172, 199, 182);
	GUI_FillRect(204, 172, 204, 182);
	GUI_FillRect(242, 172, 242, 182);
	GUI_FillRect(247, 172, 247, 182);
	GUI_FillRect(286, 172, 286, 182);
	GUI_FillRect(291, 163, 291, 182);
	//
	// 第五步：mashing 和 lautering之间的拐角链接
	//
	GUI_FillRect( 60,  88,  60, 103);
	GUI_FillRect( 61, 103,  98, 103);
	GUI_FillRect( 98,  88,  98, 102);
	GUI_FillRect( 70,  88,  70,  94);
	GUI_FillRect( 71,  94,  88,  94);
	GUI_SetColor(0x5A525A);
	GUI_FillRect( 88,  88,  88,  93);
	GUI_SetColor(0x18738B);
	GUI_FillRect( 69,  88,  69,  94);
	GUI_FillRect( 97,  88,  97, 102);
	GUI_SetColor(0x737373);
	GUI_FillRect( 71,  93,  87,  93);
	GUI_SetColor(0x109CC5);
	GUI_FillRect( 89,  88,  89,  94);
	GUI_SetColor(GUI_BLACK);
	//
	// 第六步：lautering 和 boiling之间的拐角链接
	//
	GUI_FillRect(141,  88, 141, 103);
	GUI_FillRect(142, 103, 179, 103);
	GUI_FillRect(179,  88, 179, 102);
	GUI_FillRect(151,  88, 151,  94);
	GUI_FillRect(152,  94, 169,  94);
	GUI_SetColor(0x5A525A);
	GUI_FillRect(169,  88, 169,  93);
	GUI_SetColor(0x18738B);
	GUI_FillRect(150,  88, 150,  94);
	GUI_FillRect(178,  88, 178, 102);
	GUI_SetColor(0x737373);
	GUI_FillRect(152,  93, 168,  93);
	GUI_SetColor(0x109CC5);
	GUI_FillRect(170,  88, 170,  94);
	GUI_SetColor(GUI_BLACK);
	//
	// 第七步：boiling 和 whirlpooling直接的拐角连接
	//
	GUI_FillRect(222,  88, 222, 103);
	GUI_FillRect(223, 103, 260, 103);
	GUI_FillRect(260,  88, 260, 102);
	GUI_FillRect(232,  88, 232,  94);
	GUI_FillRect(233,  94, 250,  94);
	GUI_SetColor(0x5A525A);
	GUI_FillRect(250,  88, 250,  93);
	GUI_SetColor(0x18738B);
	GUI_FillRect(231,  88, 231,  94);
	GUI_FillRect(259,  88, 259, 102);
	GUI_SetColor(0x737373);
	GUI_FillRect(233,  93, 249,  93);
	GUI_SetColor(0x109CC5);
	GUI_FillRect(251,  88, 251,  94);
	GUI_SetColor(GUI_BLACK);
	
	
	//
	// 填充上面7部建立的管道
	//
	GUI_SetColor(COLOR_BEER);
	//
	// Fill 1
	//
	GUI_FillRect(305,  88, 312, 117);
	GUI_FillRect( 36, 110, 304, 117);
	GUI_FillRect( 36, 118,  43, 123);
	//
	// Fill 2
	//
	GUI_FillRect( 71, 163,  87, 170);
	//
	// Fill 3
	//
	GUI_FillRect(152, 163, 290, 170);
	//
	// Fill 4
	//
	GUI_FillRect(200, 171, 203, 182);
	GUI_FillRect(243, 171, 246, 182);
	GUI_FillRect(287, 171, 290, 182);
	//
	// Fill 5
	//
	GUI_FillRect( 61,  88,  68, 102);
	GUI_FillRect( 69,  95,  96, 102);
	GUI_FillRect( 90,  88,  96,  94);
	//
	// Fill 6
	//
	GUI_FillRect(142,  88, 149, 102);
	GUI_FillRect(150,  95, 177, 102);
	GUI_FillRect(171,  88, 177,  94);
	//
	// Fill 7
	//
	GUI_FillRect(223,  88, 230, 102);
	GUI_FillRect(231,  95, 258, 102);
	GUI_FillRect(252,  88, 258,  94);
	
	GUI_CURSOR_Show();
	//
	// Segger Logo
	//
	GUI_DrawBitmap(&bmLogo_armflySmall, 236, 121);
	GUI_CURSOR_Hide();
}

/*
*********************************************************************************************************
*	函 数 名: _OverviewDynamic
*	功能说明: 绘制动态图，用于窗口hWinBk的重绘部分
*	形    参：pBkState  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _OverviewDynamic(BkState * pBkState) 
{
	GUI_CONST_STORAGE GUI_BITMAP * apbm320_Overview_Mashing[] = 
	{
		&bm320_Overview_Mashing_00,
		&bm320_Overview_Mashing_01,
		&bm320_Overview_Mashing_02,
		&bm320_Overview_Mashing_03,
		&bm320_Overview_Mashing_04,
		&bm320_Overview_Mashing_05,
	};

	GUI_CONST_STORAGE GUI_BITMAP * apbm320_Overview_Lautering[] = 
	{
		&bm320_Overview_Lautering_00,
		&bm320_Overview_Lautering_01,
		&bm320_Overview_Lautering_02,
		&bm320_Overview_Lautering_03,
		&bm320_Overview_Lautering_04,
		&bm320_Overview_Lautering_05,
	};

	GUI_CONST_STORAGE GUI_BITMAP * apbm320_Overview_Boiling[] = 
	{
		&bm320_Overview_Boiling_00,
		&bm320_Overview_Boiling_01,
		&bm320_Overview_Boiling_02,
		&bm320_Overview_Boiling_03,
		&bm320_Overview_Boiling_04,
		&bm320_Overview_Boiling_05,
	};

	GUI_CONST_STORAGE GUI_BITMAP * apbm320_Overview_Whirlpool[] = 
	{
		&bm320_Overview_Whirlpool_00,
		&bm320_Overview_Whirlpool_01,
		&bm320_Overview_Whirlpool_02,
		&bm320_Overview_Whirlpool_03,
		&bm320_Overview_Whirlpool_04,
		&bm320_Overview_Whirlpool_05,
	};

	int       j;
	char *    TextString[5] = {"STM32-V6", "armfly", "Brewing", "Automation", "Demo"};
	const int TextX[5]      = {167,      171,     167,       157,          175};
	GUI_RECT  Rect          = {153, 121, 234, 159};

	/* 第一步：先绘制四个小仓库 */
	GUI_SetBkColor(GUI_WHITE);
	GUI_DrawBitmap(apbm320_Overview_Mashing[pBkState->Cnt],     7,  5);
	GUI_DrawBitmap(apbm320_Overview_Lautering[pBkState->Cnt],  88,  5);
	GUI_DrawBitmap(apbm320_Overview_Boiling[pBkState->Cnt],   169,  5);
	GUI_DrawBitmap(apbm320_Overview_Whirlpool[pBkState->Cnt], 250, 21);
	 
	//
	// Moving Arrows
	//
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowDown,   306,  88, 311, 111, pBkState->Cnt,  4, 1);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowLeft,    37, 111, 311, 116, pBkState->Cnt, -4, 0);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowRight,   72, 164,  86, 169, pBkState->Cnt,  4, 0);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowRight,  153, 164, 289, 169, pBkState->Cnt,  4, 0);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowDown_2, 200, 171, 203, 182, pBkState->Cnt,  2, 1);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowDown_2, 243, 171, 246, 182, pBkState->Cnt,  2, 1);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowDown_2, 287, 171, 290, 182, pBkState->Cnt,  2, 1);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowRight,   62,  96,  95, 101, pBkState->Cnt,  4, 0);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowRight,  143,  96, 176, 101, pBkState->Cnt,  4, 0);
	_DrawMovingBitmapClipRect(&bm320_Overview_ArrowRight,  224,  96, 257, 101, pBkState->Cnt,  4, 0);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,               48, 136,  64, 163, pBkState->Cnt, -2, 1);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,               45, 177,  65, 195, pBkState->Cnt, -2, 1);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,               47, 208,  63, 232, pBkState->Cnt, -2, 1);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,              128, 136, 144, 163, pBkState->Cnt, -2, 1);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,              125, 177, 145, 195, pBkState->Cnt, -2, 1);
	_DrawMovingBitmapClipRect(&bm320_Bubbles,              127, 208, 143, 232, pBkState->Cnt, -2, 1);
	
	//
	// Moving Text
	//
	/*
		设置用于限制输出的裁剪矩形。
		默认情况下，裁剪区域限制为配置的 （虚拟）显示器大小。
		某些情况下，使用通过此函数可以设置的较小的裁剪矩形比较有用。
		引用的矩形应保持不变，直到使用空指针再次调用该函数。
	*/
	GUI_SetClipRect(&Rect);
	GUI_SetFont(&GUI_FontF16B_AA); //GUI_Font16B_ASCII
	GUI_SetColor(0x9c4a31);
	
	for (j = 0; j < 5; j++) 
	{
		(void)_Cnt; /* 防止警告 */
		/* 返回用于显示当前所选字体中指定字符串的X大小 */
		_Cnt = GUI_GetStringDistX(TextString[j]);
		GUI_DispStringAt(TextString[j], TextX[j], pBkState->TextY[j]);
	}

	GUI_SetClipRect(NULL);
}

/*
*********************************************************************************************************
*	函 数 名: _MashingDetail
*	功能说明: 绘制动态和静态图，用于窗口hWinMashing的重绘部分
*	形    参：pBkState  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _MashingDetail(MashingState * pState) 
{
	GUI_CONST_STORAGE GUI_BITMAP * apbm320_Detail_Mashing[] = 
	{
		&bm320_Detail_Mashing_00,
		&bm320_Detail_Mashing_01,
		&bm320_Detail_Mashing_02,
		&bm320_Detail_Mashing_03,
		&bm320_Detail_Mashing_04,
		&bm320_Detail_Mashing_05,
	};
	
	GUI_SetBkColor(GUI_WHITE);
	
	/* 静态显示的部分 */
	if (pState->Draw) 
	{
		GUI_Clear();
		GUI_CURSOR_Show();
		GUI_DrawBitmap(&bmLogo_armflySmall,   2, 2);
		GUI_DrawBitmap(&bmLogo_armflySmall, 239, 2);
		GUI_CURSOR_Hide();
		GUI_SetFont(&GUI_FontF24B_AA);                //GUI_SetFont(&GUI_Font24B_ASCII);
		GUI_SetColor(0x9c4a31);
		GUI_DispStringAt("Mashing",      117, 10);
		GUI_SetFont(&GUI_FontF19B_AA);
		GUI_DispStringAt("Wort:",        139, 54);
		GUI_DispStringAt("Temperature:", 139, 78);
		GUI_SetColor(0x3f3f3f);
		GUI_DrawRoundedFrame(2, 43, 316, 236, 7, 2);
	}
	
	/* 动态显示的部分 */
	GUI_DrawBitmap(apbm320_Detail_Mashing[pState->Cnt], 9, 65);
	GUI_SetFont(&GUI_FontF19B_AA);
	GUI_SetColor(0x9c4a31);
	GUI_DispDecAt(_iWort,        261, 54, 2);
	GUI_DispDecAt(_iTemperature, 261, 78, 2);
	GUI_DispStringAt("癙", 285, 54);
	GUI_DispStringAt("癈", 285, 78);
}

/*
*********************************************************************************************************
*	函 数 名: _IncPos
*	功能说明: 位置递增
*	形    参：pBkState  参数指针
*             Start     起始位置
*             Step      步数
*             MaxCnt    允许最大值
*	返 回 值: 无
*********************************************************************************************************
*/
static void _IncPos(int * pStateCnt, int Start, int Step, int MaxCnt) 
{
	* pStateCnt = (* pStateCnt < MaxCnt) ? * pStateCnt + Step : Start;
}

/*
*********************************************************************************************************
*	函 数 名: _SetPos
*	功能说明: 指定显示位置
*	形    参：pBkState  参数指针
*             Pos       指定位置
*	返 回 值: 无
*********************************************************************************************************
*/
static void _SetPos(int * pStateCnt, int Pos) 
{
	* pStateCnt = Pos;
}

/*
*********************************************************************************************************
*	函 数 名: _cbMashing
*	功能说明: 窗口Mashing回调函数
*	形    参：pMsg  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _cbMashing(WM_MESSAGE * pMsg) 
{
	static MashingState State = 
	{
		0,
		0
	};
	switch (pMsg->MsgId) 
	{
		case APP_DRAW:
			State.Draw = 1;
			break;
		
		case APP_HIDE:
			State.Draw = 0;
			break;
		
		case APP_NEXT_FRAME:
			_IncPos(&State.Cnt, 0, 1, 5);
			break;
		
		case APP_FIRST_FRAME:
			_SetPos(&State.Cnt, 0);
			break;
		
		case WM_PAINT:
			_MashingDetail(&State);
			break;
	}
}

/*
*********************************************************************************************************
*	函 数 名: _BkOnPaint
*	功能说明: 背景窗口重绘函数
*	形    参：pBkState  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _BkOnPaint(BkState * pBkState) 
{
	if (pBkState->DrawBk) 
	{
		_OverviewStatic();
	}
	_OverviewDynamic(pBkState);
}

/*
*********************************************************************************************************
*	函 数 名: _IncPosBk
*	功能说明: 调整文本的显示位置，从而实现滚动的效果
*	形    参：pBkState  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _IncPosBk(BkState * pBkState) 
{
	int j;

	pBkState->Cnt = (pBkState->Cnt < 5) ? pBkState->Cnt + 1 : 0;
	for (j = 0; j < 5; j++) 
	{
		if (pBkState->TextY[j] < 107) 
		{
			pBkState->TextY[j] = 200;
		} 
		else 
		{
			pBkState->TextY[j]--;
		}
	}
}

/*
*********************************************************************************************************
*	函 数 名: _cbBk
*	功能说明: 窗口hWinBk回调函数
*	形    参：pBkState  参数指针
*	返 回 值: 无
*********************************************************************************************************
*/
static void _cbBk(WM_MESSAGE * pMsg) 
{
	static BkState BkState = 
	{
		{161, 178, 195, 212, 229},
		0,
		1
	};
	
	switch (pMsg->MsgId) 
	{
		case APP_DRAW:
			BkState.DrawBk = 1;
			break;
		
		case APP_HIDE:
			BkState.DrawBk = 0;
			break;
		
		case APP_NEXT_FRAME:
			_IncPosBk(&BkState);
			break;
		
		case WM_PAINT:
			_BkOnPaint(&BkState);
			break;
	}
}

/*
*********************************************************************************************************
*	函 数 名: _cbGraph
*	功能说明: 绘图控件的回调函数
*	形    参：hWin   窗口句柄
*             Stage  绘图阶段
*	返 回 值: 无
*********************************************************************************************************
*/
static void _cbGraph(WM_HWIN hWin, int Stage) 
{
	static int DrawGrid = 1;
	unsigned   OffX,  OffY;
	unsigned   MaxX,  MaxY;
	unsigned   StepX, StepY;
	unsigned   i;
	unsigned   Value;
	GUI_USE_PARA(hWin);
	OffX  = 148;
	OffY  = 12;
	MaxX  = 171;
	MaxY  = 131;
	StepX = 25;
	StepY = 25;
	
	switch (Stage) 
	{
		/* 此消息用于绘制绘图控件的垂直线 */
		case GRAPH_DRAW_AFTER_BORDER:
			GUI_SetColor(0x9c4a31);
			/* 在绘图控件上画水平线 */
		    for (i = OffY; i < MaxY; i += StepY) 
			{
				GUI_DrawHLine(i, 16, 169);
			}
			
			if (DrawGrid) 
			{
				GUI_DrawVLine(23,    /* X位置。*/
				               1,    /* Y起始位置 */
				               118); /* Y结束位置 */
				
				/*       
				  _iGraphCnt 从0到126变化，初始化的时候配置绘图控件支持126个数据项 
				         148       171 + 125         25 
				*/
				for (i = OffX; i < MaxX + 125; i += StepX) 
				{
					if (i - _iGraphCnt < 23) 
					{
						GUI_DrawVLine(i - _iGraphCnt + 125, 1, 118);
					}
					else 
					{
						GUI_DrawVLine(i - _iGraphCnt,       1, 118);
					}
				}
			} 
			else 
			{
				GUI_DrawVLine(148, 2, 118);
			}
			break;
		
		/* 此消息用于绘制刻度 */
		case GRAPH_DRAW_LAST:
			GUI_SetFont(&GUI_Font6x8);
			Value = 0;
			i     = OffX - 5;
			while (i - _iGraphCnt < 170) 
			{
				if (i - _iGraphCnt > 23) 
				{
					if (Value == 0) 
					{
						GUI_DispDecAt(Value, i - _iGraphCnt + 3, 120, 1);
					} 
					else if (Value > 0 && Value < 100) 
					{
						GUI_DispDecAt(Value, i - _iGraphCnt,     120, 2);
					} 
					else if (Value == 100) 
					{
						GUI_DispDecAt(Value, i - _iGraphCnt - 3, 120, 3);
					}
				}
				
				i     += StepX;
				Value += 20;
			};
			break;
			
		/* 设置执行垂直网格绘制 */
		case GRID_DRAW_FULL:
			DrawGrid = 1;
			break;
		
		/* 设置不执行垂直网格绘制 */
		case GRID_DRAW_START:
			DrawGrid = 0;
			break;
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
	WM_HWIN            hWinBk;
	WM_HWIN            hWinMashing;
	WM_HWIN            hGraph;
	GRAPH_DATA_Handle  hData;
	GRAPH_SCALE_Handle hScaleVert;
	int                i;
	
	
	/* 初始化 */
	GUI_Init();
	
//	GUI_SetOrientation(5);
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

//	GUI_CURSOR_Show();
	
	/* 设置桌面窗口的背景色 */
	WM_SetDesktopColor(GUI_BLUE);
	
		/* 创建两个窗口 
	   1. 窗口hWinBk用于演示第一幅动态效果
	   2. 窗口hWinMashing用于演示第二个动态效果
	*/
	hWinBk      = WM_CreateWindow((LCD_GetXSize() - 320)/2, 
	                              (LCD_GetYSize() - 240)/2,   
	                              320, 
	                              240, 
								  WM_CF_SHOW,  
								  _cbBk,      
								  0);
														  
	hWinMashing = WM_CreateWindow((LCD_GetXSize() - 320)/2, 
	                              (LCD_GetYSize() - 240)/2,    
								  320, 
								  240, 
								  0,           
								  _cbMashing, 
								  0);
	
	/* 创建绘图控件 
	   1. 绘图控件建立在窗口hWinMashing上面
	*/
	hGraph      = GRAPH_CreateEx (140, 100, 171, 131, hWinMashing, WM_CF_SHOW | WM_CF_MEMDEV, 0, GUI_ID_GRAPH0);
	hData       = GRAPH_DATA_YT_Create(COLOR_BEER,  /* 绘制数据要使用的颜色 */
	                                          147,  /* 数据项的最大数 */
	                                            0,  /* 指向要添加到对象的数据的指针。该指针应指向一组I16值。*/
												0); /* 要添加的数据项数。*/
	
	hScaleVert  = GRAPH_SCALE_Create(14,                      /* 相对于图形小工具的左边/顶边的位置。 */        
	                                 GUI_TA_RIGHT,            /* 用于绘制编号的文本对齐方式 */
									 GRAPH_SCALE_CF_VERTICAL, /* 创建垂直刻度对象 */ 
									 25);

	WIDGET_SetEffect      (hGraph, &WIDGET_Effect_Simple);  
	
	/* 设置GRAPH小工具的颜色 */
	GRAPH_SetColor        (hGraph,       /* 句柄 */
	                       GUI_WHITE,    /* 要用于所需项目的颜色 */
						   GRAPH_CI_BK); /* 设置背景颜色 */
						   
	/* 设置边框的尺寸 （上、下、左、右） */
	GRAPH_SetBorder       (hGraph,   /* 句柄 */
	                           23,   /* 左边框的尺寸 */
							    0,   /* 上边框的尺寸 */
							    0,   /* 右边框的尺寸 */
								18); /* 下边框的尺寸 */
								
	/* 设置用户绘制函数。此函数由小工具在绘制过程中调用，使应用程序能够绘制用户定义的数据 */							
	GRAPH_SetUserDraw     (hGraph, _cbGraph);
	
	/* 设置数据的对齐方式 左对齐或者右对齐 */
	GRAPH_DATA_YT_SetAlign(hData,  GRAPH_ALIGN_LEFT);

	/* 
		置用于计算要绘制的编号的因子
	    1. 不使用因子时，刻度对象的单位为 “像素”。因此给定因子应将像素值转换为所需的单位
	*/
	GRAPH_SCALE_SetFactor   (hScaleVert, 0.4f);
	
	/*
		设置用于在正或负方向上 “移动”刻度对象的偏移。
		1. 水平刻度对象从数据区的底边开始向顶部进行标记，垂直刻度对象从左边 （水平刻度）开始向右边
		   进行标记，其中第一个位置是零点。在许多情况下，不希望第一个位置是零点。如果刻度要向正方
		   向 “移动”，应添加正偏移，要向负方向 “移动”，应添加负值。
	*/
	GRAPH_SCALE_SetOff      (hScaleVert, -102);
	
	/* 设置用于绘制编号的文本颜色。*/
	GRAPH_SCALE_SetTextColor(hScaleVert, 0x9c4a31);
	
	/* 将数据对象附加到现有图形小工具。 */
	GRAPH_AttachData (hGraph, hData);
	/* 将刻度对象附加到现有图形小工具。 */
	GRAPH_AttachScale(hGraph, hScaleVert);

	while (1) 
	{
		/* 将窗口hWinBk设置为顶层 */
		WM_BringToTop(hWinBk);
		
		/* 窗口hWinBk显示了之后，回调函数中重绘部分的静态图片不再需要显示了 */
		WM_SendMessageNoPara   (hWinBk,      APP_DRAW);
		WM_Exec();
		WM_SendMessageNoPara   (hWinBk, APP_HIDE);
		
		/***********************窗口hWinBk演示********************************/
		for (i = 0; i < 100; i++) 
		{
			GUI_Delay(60);
			WM_SendMessageNoPara(hWinBk, APP_NEXT_FRAME);
			WM_InvalidateWindow (hWinBk);
		}
		
		/***********************窗口hWinMashing演示********************************/
		/* 第1步：先为绘图控件添加好数据 */
		for (i = 0; i < 147; i++) 
		{
			GRAPH_DATA_YT_AddValue(hData, (50 - 40) * 25 / 10);
		}
		_iTemperature = _aTemperature[0];
		_iWort        = 0;
		
		/* 将窗口hWinMashing设置为顶层 */
		/* 第2步：显示窗口hWinMashing，并为窗hWinMashing绘制静态图片 */
		WM_BringToTop(hWinMashing);
		WM_ShowWindow(hWinMashing);
		WM_SendMessageNoPara(hWinMashing, APP_DRAW);
		WM_Exec();
		
		/*  第3步：窗口hWinMashing和hWinBk都不再需要绘制静态图片 */
		WM_SendMessageNoPara(hWinMashing, APP_HIDE);
		WM_SendMessageNoPara(hWinBk, APP_HIDE);
		WM_Exec();
		
		/*  第4步：绘图控件表格全显示 */
		_cbGraph(hWinMashing, GRID_DRAW_FULL);
		
		/*  第5步：更新绘图控件的数据，更新窗口上的图片 */
		for (i = 0; i < 126; i++) 
		{
			GUI_Delay(60);
			_iTemperature = _aTemperature[i];
			_iWort        = i / 10;
			_iGraphCnt    = i;
			GRAPH_DATA_YT_AddValue(hData, (_aTemperature[i] - 40) * 25 / 10);
			WM_SendMessageNoPara  (hWinMashing, APP_NEXT_FRAME);
			WM_InvalidateWindow   (hWinMashing);
			WM_InvalidateWindow   (hGraph);
		}
	
		/*  第七步：清空数据 */
		GRAPH_DATA_YT_Clear     (hData);	

//		GUI_CURSOR_Hide();
	}
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
