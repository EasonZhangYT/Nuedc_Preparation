/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2013  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.20 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : F16B_AA.c
Content     : Font (AA4), Height 16
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.H"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

/* The following line needs to be included in any file selecting the
   font. A good place would be GUIConf.H
*/
extern GUI_CONST_STORAGE GUI_FONT GUI_FontF16B_AA;

/* Start of unicode area <Basic Latin> */
GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0020[  1] = { /* code 0020, SPACE */
  0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0021[ 10] = { /* code 0021, EXCLAMATION MARK */
  0xFF,
  0xFF,
  0xFF,
  0xDD,
  0xBB,
  0xAA,
  0x89,
  0x00,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0022[  9] = { /* code 0022, QUOTATION MARK */
  0xFF, 0x0F, 0xF0,
  0xFF, 0x0F, 0xF0,
  0xBC, 0x0B, 0xC0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0023[ 30] = { /* code 0023, NUMBER SIGN */
  0x01, 0xE0, 0x1E,
  0x04, 0xB0, 0x4B,
  0x07, 0x90, 0x79,
  0xFF, 0xFF, 0xFF,
  0x0D, 0x10, 0xD1,
  0x2D, 0x02, 0xD0,
  0xFF, 0xFF, 0xFF,
  0x87, 0x08, 0x70,
  0xB4, 0x0B, 0x40,
  0xE1, 0x0E, 0x10
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0024[ 36] = { /* code 0024, DOLLAR SIGN */
  0x00, 0xF0, 0x00,
  0x3D, 0xFD, 0x30,
  0xC5, 0xF7, 0xD0,
  0xF1, 0xF0, 0x00,
  0xEB, 0xF0, 0x00,
  0x8F, 0xFC, 0x20,
  0x0A, 0xFF, 0xB0,
  0x00, 0xF8, 0xF0,
  0x00, 0xF0, 0xF0,
  0xD5, 0xF4, 0xB0,
  0x4D, 0xFD, 0x30,
  0x00, 0xF0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0025[ 40] = { /* code 0025, PERCENT SIGN */
  0x7F, 0x70, 0x0A, 0x50,
  0xE3, 0xE0, 0x1D, 0x00,
  0xF0, 0xF0, 0x78, 0x00,
  0xE2, 0xE0, 0xD2, 0x00,
  0x7F, 0x74, 0xB0, 0x00,
  0x00, 0x0A, 0x57, 0xF7,
  0x00, 0x1D, 0x0E, 0x2E,
  0x00, 0x78, 0x0F, 0x0F,
  0x00, 0xD2, 0x0E, 0x3E,
  0x04, 0xB0, 0x07, 0xF7
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0026[ 40] = { /* code 0026, AMPERSAND */
  0x03, 0xDF, 0xD3, 0x00,
  0x0D, 0xF3, 0xFD, 0x00,
  0x0E, 0xF4, 0xFE, 0x00,
  0x06, 0xFE, 0xF7, 0x00,
  0x04, 0xEF, 0x80, 0x00,
  0x6F, 0xEF, 0xD1, 0x82,
  0xDF, 0x4A, 0xFD, 0xF3,
  0xFF, 0x03, 0xFF, 0xE0,
  0xAF, 0x44, 0xFF, 0xE4,
  0x1A, 0xFF, 0xC7, 0xC8
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0027[  3] = { /* code 0027, APOSTROPHE */
  0xFF,
  0xFF,
  0xBC
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0028[ 26] = { /* code 0028, LEFT PARENTHESIS */
  0x04, 0xD0,
  0x0C, 0x90,
  0x4F, 0x60,
  0x9F, 0x30,
  0xCF, 0x20,
  0xFF, 0x00,
  0xFF, 0x00,
  0xEF, 0x00,
  0xCF, 0x20,
  0x8F, 0x30,
  0x3F, 0x60,
  0x0C, 0x90,
  0x04, 0xD0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0029[ 26] = { /* code 0029, RIGHT PARENTHESIS */
  0xD4, 0x00,
  0x9D, 0x00,
  0x6F, 0x40,
  0x3F, 0x90,
  0x2F, 0xC0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xE0,
  0x2F, 0xC0,
  0x3F, 0x80,
  0x6F, 0x30,
  0x9C, 0x00,
  0xD4, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_002A[ 12] = { /* code 002A, ASTERISK */
  0x00, 0xF0, 0x00,
  0xBA, 0xD9, 0xB0,
  0x1A, 0xFB, 0x10,
  0xA9, 0x38, 0xA0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_002B[ 15] = { /* code 002B, PLUS SIGN */
  0x00, 0xFF, 0x00,
  0x00, 0xFF, 0x00,
  0xFF, 0xFF, 0xFF,
  0x00, 0xFF, 0x00,
  0x00, 0xFF, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_002C[  4] = { /* code 002C, COMMA */
  0xFF,
  0xFF,
  0x3D,
  0xB3
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_002D[  2] = { /* code 002D, HYPHEN-MINUS */
  0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_002E[  2] = { /* code 002E, FULL STOP */
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_002F[ 20] = { /* code 002F, SOLIDUS */
  0x00, 0x2D,
  0x00, 0x78,
  0x00, 0xB4,
  0x01, 0xE0,
  0x05, 0xA0,
  0x0A, 0x50,
  0x0E, 0x10,
  0x4B, 0x00,
  0x87, 0x00,
  0xD2, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0030[ 30] = { /* code 0030, DIGIT ZERO */
  0x19, 0xEE, 0x91,
  0x8F, 0x66, 0xF8,
  0xCF, 0x22, 0xFC,
  0xEF, 0x00, 0xFE,
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0xEF, 0x00, 0xFE,
  0xCF, 0x22, 0xFC,
  0x8F, 0x66, 0xF8,
  0x1A, 0xFE, 0x91
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0031[ 20] = { /* code 0031, DIGIT ONE */
  0x00, 0xBF,
  0x3B, 0xFF,
  0xFC, 0xFF,
  0xB1, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0032[ 30] = { /* code 0032, DIGIT TWO */
  0x3B, 0xFF, 0xA1,
  0xBF, 0x33, 0xF9,
  0x00, 0x00, 0xFE,
  0x00, 0x04, 0xFE,
  0x00, 0x1D, 0xF6,
  0x00, 0xBF, 0xB0,
  0x07, 0xFE, 0x20,
  0x2F, 0xE3, 0x00,
  0xAF, 0x60, 0x00,
  0xEF, 0xFF, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0033[ 30] = { /* code 0033, DIGIT THREE */
  0x3B, 0xFF, 0xA1,
  0xBE, 0x43, 0xFB,
  0x00, 0x00, 0xFF,
  0x00, 0x07, 0xFA,
  0x00, 0xDF, 0xE1,
  0x00, 0x06, 0xFA,
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFE,
  0xBF, 0x35, 0xF8,
  0x3B, 0xFE, 0x80
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0034[ 30] = { /* code 0034, DIGIT FOUR */
  0x00, 0x0E, 0xF0,
  0x00, 0x7F, 0xF0,
  0x00, 0xDF, 0xF0,
  0x06, 0xAF, 0xF0,
  0x0C, 0x3F, 0xF0,
  0x5C, 0x0F, 0xF0,
  0xB5, 0x0F, 0xF0,
  0xFF, 0xFF, 0xFF,
  0x00, 0x0F, 0xF0,
  0x00, 0x0F, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0035[ 30] = { /* code 0035, DIGIT FIVE */
  0x2F, 0xFF, 0xFF,
  0x5F, 0xA0, 0x00,
  0x8F, 0x50, 0x00,
  0xBF, 0xEF, 0xB1,
  0xBE, 0x36, 0xF9,
  0x00, 0x01, 0xFE,
  0x00, 0x00, 0xFF,
  0x00, 0x01, 0xFE,
  0xBF, 0x36, 0xFA,
  0x3B, 0xFE, 0x91
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0036[ 30] = { /* code 0036, DIGIT SIX */
  0x05, 0xDF, 0xC3,
  0x4F, 0x73, 0xEB,
  0xAF, 0x10, 0x00,
  0xEE, 0x00, 0x00,
  0xFE, 0xBF, 0xB1,
  0xFF, 0x55, 0xFA,
  0xEF, 0x00, 0xFF,
  0xCF, 0x10, 0xFE,
  0x8F, 0x64, 0xFA,
  0x1A, 0xFF, 0xA1
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0037[ 30] = { /* code 0037, DIGIT SEVEN */
  0xFF, 0xFF, 0xFF,
  0x00, 0x04, 0xFA,
  0x00, 0x0D, 0xE1,
  0x00, 0x6F, 0x80,
  0x00, 0xDF, 0x30,
  0x03, 0xFC, 0x00,
  0x07, 0xF8, 0x00,
  0x0B, 0xF4, 0x00,
  0x0D, 0xF2, 0x00,
  0x0F, 0xF0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0038[ 30] = { /* code 0038, DIGIT EIGHT */
  0x2B, 0xFF, 0xB2,
  0xCF, 0x44, 0xFC,
  0xFF, 0x00, 0xFF,
  0xAF, 0x44, 0xF9,
  0x0D, 0xFF, 0xF1,
  0x8F, 0x55, 0xF9,
  0xEF, 0x00, 0xFF,
  0xEF, 0x00, 0xFE,
  0xAF, 0x55, 0xF9,
  0x19, 0xEF, 0xA1
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0039[ 30] = { /* code 0039, DIGIT NINE */
  0x1A, 0xFE, 0x80,
  0xAF, 0x46, 0xF7,
  0xEF, 0x01, 0xFC,
  0xFF, 0x00, 0xFE,
  0xAF, 0x55, 0xFF,
  0x1B, 0xFB, 0xEF,
  0x00, 0x00, 0xEE,
  0x00, 0x01, 0xFA,
  0xBE, 0x37, 0xF4,
  0x3C, 0xFD, 0x50
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_003A[  7] = { /* code 003A, COLON */
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x00,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_003B[  9] = { /* code 003B, SEMICOLON */
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x00,
  0xFF,
  0xFF,
  0x3D,
  0xB3
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_003C[ 21] = { /* code 003C, LESS-THAN SIGN */
  0x00, 0x00, 0x5B,
  0x00, 0x6D, 0xFF,
  0x7E, 0xFC, 0x72,
  0xFE, 0x40, 0x00,
  0x7E, 0xFC, 0x61,
  0x00, 0x6D, 0xFF,
  0x00, 0x00, 0x5B
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_003D[ 12] = { /* code 003D, EQUALS SIGN */
  0xFF, 0xFF, 0xFF, 0xF0,
  0x00, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_003E[ 21] = { /* code 003E, GREATER-THAN SIGN */
  0xB5, 0x00, 0x00,
  0xFF, 0xD6, 0x00,
  0x27, 0xCF, 0xE7,
  0x00, 0x04, 0xEF,
  0x05, 0xBF, 0xE7,
  0xEF, 0xD6, 0x00,
  0xB5, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_003F[ 40] = { /* code 003F, QUESTION MARK */
  0x2A, 0xEF, 0xD8, 0x00,
  0xCF, 0x60, 0x7F, 0x90,
  0x00, 0x00, 0x0F, 0xF0,
  0x00, 0x00, 0x5F, 0xC0,
  0x00, 0x04, 0xFC, 0x20,
  0x00, 0x4E, 0x91, 0x00,
  0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0xFF, 0x00, 0x00,
  0x00, 0xFF, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0040[ 91] = { /* code 0040, COMMERCIAL AT */
  0x00, 0x03, 0x9D, 0xFF, 0xDA, 0x30, 0x00,
  0x00, 0x8D, 0x72, 0x00, 0x27, 0xE7, 0x00,
  0x08, 0xB1, 0x00, 0x00, 0x00, 0x2E, 0x40,
  0x3E, 0x13, 0xBF, 0xC5, 0xFF, 0x26, 0xB0,
  0x97, 0x2E, 0xFF, 0xFE, 0xFE, 0x01, 0xE0,
  0xD3, 0x9F, 0xA1, 0x3F, 0xFA, 0x00, 0xF0,
  0xF0, 0xEF, 0x10, 0x2F, 0xF7, 0x03, 0xC0,
  0xF0, 0xFF, 0x31, 0xAF, 0xF3, 0x0B, 0x50,
  0xC3, 0xBF, 0xFF, 0xFF, 0xF2, 0x98, 0x00,
  0x7B, 0x2B, 0xFB, 0x5E, 0xFB, 0x40, 0x00,
  0x1D, 0x70, 0x00, 0x00, 0x00, 0x05, 0xB0,
  0x02, 0xCC, 0x52, 0x00, 0x14, 0xAB, 0x10,
  0x00, 0x05, 0xBE, 0xFF, 0xEA, 0x50, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0041[ 50] = { /* code 0041, LATIN CAPITAL LETTER A */
  0x00, 0x1F, 0xFF, 0x00, 0x00,
  0x00, 0x5F, 0xFF, 0x50, 0x00,
  0x00, 0xAF, 0xBF, 0xA0, 0x00,
  0x00, 0xEF, 0x1F, 0xE0, 0x00,
  0x04, 0xFB, 0x0B, 0xF4, 0x00,
  0x09, 0xF6, 0x06, 0xF9, 0x00,
  0x0D, 0xF2, 0x01, 0xFD, 0x00,
  0x3F, 0xFF, 0xFF, 0xFF, 0x30,
  0x8F, 0x70, 0x00, 0x7F, 0x80,
  0xDF, 0x30, 0x00, 0x3F, 0xD0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0042[ 40] = { /* code 0042, LATIN CAPITAL LETTER B */
  0xFF, 0xFF, 0xFC, 0x20,
  0xFF, 0x00, 0x4F, 0xC0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x4F, 0x80,
  0xFF, 0xFF, 0xFC, 0x20,
  0xFF, 0x00, 0x6F, 0xC0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xE0,
  0xFF, 0x00, 0x5F, 0xA0,
  0xFF, 0xFF, 0xFB, 0x10
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0043[ 40] = { /* code 0043, LATIN CAPITAL LETTER C */
  0x01, 0x9E, 0xFD, 0x81,
  0x1D, 0xD2, 0x06, 0xFB,
  0x8F, 0x50, 0x00, 0x00,
  0xCF, 0x10, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xDF, 0x10, 0x00, 0x00,
  0x8F, 0x50, 0x00, 0x00,
  0x1D, 0xD2, 0x06, 0xFB,
  0x02, 0xAE, 0xFD, 0x81
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0044[ 40] = { /* code 0044, LATIN CAPITAL LETTER D */
  0xFF, 0xFF, 0xD4, 0x00,
  0xFF, 0x01, 0xBF, 0x30,
  0xFF, 0x00, 0x3F, 0xA0,
  0xFF, 0x00, 0x1F, 0xD0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x1F, 0xE0,
  0xFF, 0x00, 0x4F, 0xA0,
  0xFF, 0x00, 0xAF, 0x30,
  0xFF, 0xFF, 0xC4, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0045[ 30] = { /* code 0045, LATIN CAPITAL LETTER E */
  0xFF, 0xFF, 0xFF,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0xFF, 0xFF,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0xFF, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0046[ 30] = { /* code 0046, LATIN CAPITAL LETTER F */
  0xFF, 0xFF, 0xFF,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0xFF, 0xFF,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0047[ 40] = { /* code 0047, LATIN CAPITAL LETTER G */
  0x01, 0x9E, 0xFE, 0x91,
  0x1D, 0xD3, 0x06, 0xFC,
  0x8F, 0x50, 0x00, 0x00,
  0xDF, 0x10, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0xFF, 0xFF,
  0xCF, 0x20, 0x00, 0xFF,
  0x8F, 0x60, 0x00, 0xFF,
  0x1D, 0xE3, 0x16, 0xFF,
  0x01, 0x9E, 0xFE, 0xB5
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0048[ 40] = { /* code 0048, LATIN CAPITAL LETTER H */
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0xFF, 0xFF, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0049[ 10] = { /* code 0049, LATIN CAPITAL LETTER I */
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_004A[ 30] = { /* code 004A, LATIN CAPITAL LETTER J */
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFF,
  0xFF, 0x00, 0xFE,
  0xBF, 0x44, 0xF9,
  0x1B, 0xFE, 0xA1
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_004B[ 40] = { /* code 004B, LATIN CAPITAL LETTER K */
  0xFF, 0x00, 0x1D, 0xE2,
  0xFF, 0x00, 0xBF, 0x40,
  0xFF, 0x08, 0xF7, 0x00,
  0xFF, 0x6F, 0xC0, 0x00,
  0xFF, 0xFF, 0xF2, 0x00,
  0xFF, 0xE9, 0xF8, 0x00,
  0xFF, 0x41, 0xFE, 0x00,
  0xFF, 0x00, 0x9F, 0x60,
  0xFF, 0x00, 0x3F, 0xD0,
  0xFF, 0x00, 0x0B, 0xF4
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_004C[ 30] = { /* code 004C, LATIN CAPITAL LETTER L */
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0xFF, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_004D[ 50] = { /* code 004D, LATIN CAPITAL LETTER M */
  0xFF, 0xF1, 0x01, 0xFF, 0xF0,
  0xFF, 0xF5, 0x05, 0xFF, 0xF0,
  0xFF, 0xE8, 0x08, 0xEF, 0xF0,
  0xFF, 0xBB, 0x0B, 0xBF, 0xF0,
  0xFF, 0x7E, 0x0F, 0x7F, 0xF0,
  0xFF, 0x4F, 0x6F, 0x4F, 0xF0,
  0xFF, 0x1F, 0xDF, 0x1F, 0xF0,
  0xFF, 0x0D, 0xFD, 0x0F, 0xF0,
  0xFF, 0x0A, 0xFA, 0x0F, 0xF0,
  0xFF, 0x06, 0xF7, 0x0F, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_004E[ 40] = { /* code 004E, LATIN CAPITAL LETTER N */
  0xFF, 0x50, 0x0F, 0xF0,
  0xFF, 0xD0, 0x0F, 0xF0,
  0xFF, 0xF6, 0x0F, 0xF0,
  0xFF, 0xED, 0x0F, 0xF0,
  0xFF, 0x7F, 0x6F, 0xF0,
  0xFF, 0x1E, 0xEF, 0xF0,
  0xFF, 0x07, 0xFF, 0xF0,
  0xFF, 0x01, 0xEF, 0xF0,
  0xFF, 0x00, 0x7F, 0xF0,
  0xFF, 0x00, 0x1E, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_004F[ 40] = { /* code 004F, LATIN CAPITAL LETTER O */
  0x03, 0xBF, 0xFB, 0x20,
  0x2E, 0xD2, 0x2D, 0xE2,
  0x9F, 0x50, 0x05, 0xF9,
  0xDF, 0x10, 0x01, 0xFD,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xDF, 0x10, 0x01, 0xFD,
  0x9F, 0x50, 0x05, 0xF9,
  0x2E, 0xD2, 0x2D, 0xE2,
  0x02, 0xBF, 0xFB, 0x20
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0050[ 40] = { /* code 0050, LATIN CAPITAL LETTER P */
  0xFF, 0xFF, 0xEB, 0x10,
  0xFF, 0x00, 0x7F, 0xA0,
  0xFF, 0x00, 0x1F, 0xF0,
  0xFF, 0x00, 0x1F, 0xF0,
  0xFF, 0x00, 0x7F, 0xA0,
  0xFF, 0xFF, 0xEA, 0x10,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0051[ 44] = { /* code 0051, LATIN CAPITAL LETTER Q */
  0x03, 0xBF, 0xFB, 0x20,
  0x2E, 0xD2, 0x2D, 0xE1,
  0x9F, 0x50, 0x05, 0xF8,
  0xDF, 0x10, 0x01, 0xFC,
  0xFF, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0xFF,
  0xDF, 0x20, 0x00, 0xFE,
  0x9F, 0x60, 0xA6, 0xFB,
  0x2E, 0xE3, 0x7F, 0xF4,
  0x02, 0xBF, 0xFB, 0xE5,
  0x00, 0x00, 0x00, 0x3A
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0052[ 40] = { /* code 0052, LATIN CAPITAL LETTER R */
  0xFF, 0xFF, 0xFB, 0x20,
  0xFF, 0x00, 0x5F, 0xB0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x6F, 0xB0,
  0xFF, 0xFF, 0xFB, 0x10,
  0xFF, 0x04, 0xFC, 0x10,
  0xFF, 0x00, 0x7F, 0x90,
  0xFF, 0x00, 0x0E, 0xF2,
  0xFF, 0x00, 0x07, 0xFB
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0053[ 40] = { /* code 0053, LATIN CAPITAL LETTER S */
  0x19, 0xEF, 0xEB, 0x20,
  0xAF, 0x40, 0x4F, 0xD0,
  0xFF, 0x10, 0x00, 0x00,
  0xDF, 0xD4, 0x00, 0x00,
  0x5F, 0xFF, 0xB3, 0x00,
  0x04, 0xCF, 0xFF, 0x60,
  0x00, 0x05, 0xCF, 0xE0,
  0x00, 0x00, 0x1F, 0xF0,
  0xDF, 0x50, 0x5F, 0xA0,
  0x2A, 0xEF, 0xE9, 0x10
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0054[ 40] = { /* code 0054, LATIN CAPITAL LETTER T */
  0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0055[ 40] = { /* code 0055, LATIN CAPITAL LETTER U */
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xFF, 0x00, 0x0F, 0xF0,
  0xDF, 0x10, 0x1F, 0xD0,
  0x8F, 0x80, 0x7F, 0x80,
  0x08, 0xEF, 0xE8, 0x10
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0056[ 50] = { /* code 0056, LATIN CAPITAL LETTER V */
  0xDF, 0x30, 0x00, 0x3F, 0xD0,
  0x8F, 0x70, 0x00, 0x7F, 0x80,
  0x3F, 0xC0, 0x00, 0xCF, 0x30,
  0x0E, 0xF2, 0x02, 0xFE, 0x00,
  0x09, 0xF6, 0x06, 0xF9, 0x00,
  0x04, 0xFB, 0x0B, 0xF5, 0x00,
  0x00, 0xEF, 0x1F, 0xF0, 0x00,
  0x00, 0xAF, 0xBF, 0xA0, 0x00,
  0x00, 0x5F, 0xFF, 0x60, 0x00,
  0x00, 0x1F, 0xFF, 0x10, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0057[ 70] = { /* code 0057, LATIN CAPITAL LETTER W */
  0xDF, 0x20, 0x0E, 0xFE, 0x00, 0x2F, 0xD0,
  0xAF, 0x50, 0x3F, 0xFF, 0x30, 0x5F, 0xA0,
  0x7F, 0x80, 0x7F, 0xEF, 0x70, 0x8F, 0x70,
  0x4F, 0xB0, 0xAF, 0x8F, 0xA0, 0xBF, 0x40,
  0x1F, 0xF0, 0xEF, 0x1F, 0xE0, 0xEF, 0x10,
  0x0C, 0xF5, 0xFC, 0x0C, 0xF5, 0xFC, 0x00,
  0x09, 0xFC, 0xF8, 0x08, 0xFB, 0xF9, 0x00,
  0x06, 0xFF, 0xF4, 0x05, 0xFF, 0xF6, 0x00,
  0x03, 0xFF, 0xF1, 0x01, 0xFF, 0xF3, 0x00,
  0x00, 0xEF, 0xC0, 0x00, 0xDF, 0xF0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0058[ 50] = { /* code 0058, LATIN CAPITAL LETTER X */
  0x3F, 0xC0, 0x00, 0xCF, 0x30,
  0x09, 0xF6, 0x06, 0xF9, 0x00,
  0x01, 0xEE, 0x2E, 0xE1, 0x00,
  0x00, 0x6F, 0xEF, 0x60, 0x00,
  0x00, 0x0C, 0xFC, 0x00, 0x00,
  0x00, 0x0C, 0xFC, 0x00, 0x00,
  0x00, 0x6F, 0xEF, 0x60, 0x00,
  0x01, 0xEE, 0x2E, 0xE1, 0x00,
  0x09, 0xF6, 0x06, 0xF9, 0x00,
  0x3F, 0xC0, 0x00, 0xCF, 0x30
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0059[ 50] = { /* code 0059, LATIN CAPITAL LETTER Y */
  0x3F, 0xC0, 0x00, 0x0C, 0xF3,
  0x09, 0xF6, 0x00, 0x7F, 0x90,
  0x01, 0xEE, 0x11, 0xEE, 0x10,
  0x00, 0x6F, 0x9A, 0xF6, 0x00,
  0x00, 0x0C, 0xFF, 0xC0, 0x00,
  0x00, 0x03, 0xFF, 0x30, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_005A[ 40] = { /* code 005A, LATIN CAPITAL LETTER Z */
  0xFF, 0xFF, 0xFF, 0xF0,
  0x00, 0x00, 0x5F, 0xA0,
  0x00, 0x01, 0xDE, 0x10,
  0x00, 0x08, 0xF7, 0x00,
  0x00, 0x3F, 0xD0, 0x00,
  0x00, 0xCF, 0x40, 0x00,
  0x07, 0xFA, 0x00, 0x00,
  0x2E, 0xF2, 0x00, 0x00,
  0xAF, 0x70, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_005B[ 26] = { /* code 005B, LEFT SQUARE BRACKET */
  0xFF, 0xF0,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_005C[ 20] = { /* code 005C, REVERSE SOLIDUS */
  0xD2, 0x00,
  0x87, 0x00,
  0x4B, 0x00,
  0x0E, 0x10,
  0x0A, 0x50,
  0x05, 0xA0,
  0x01, 0xE0,
  0x00, 0xB4,
  0x00, 0x78,
  0x00, 0x2D
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_005D[ 26] = { /* code 005D, RIGHT SQUARE BRACKET */
  0xFF, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_005E[ 15] = { /* code 005E, CIRCUMFLEX ACCENT */
  0x00, 0xDE, 0x00,
  0x06, 0xFF, 0x60,
  0x0C, 0xCC, 0xD0,
  0x5F, 0x77, 0xF5,
  0xBF, 0x22, 0xFB
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_005F[  4] = { /* code 005F, LOW LINE */
  0xFF, 0xFF, 0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0060[  4] = { /* code 0060, GRAVE ACCENT */
  0x8F, 0x40,
  0x08, 0xB0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0061[ 21] = { /* code 0061, LATIN SMALL LETTER A */
  0x2B, 0xFF, 0xC4,
  0xC5, 0x03, 0xFE,
  0x03, 0x8C, 0xFF,
  0x7F, 0xB3, 0xFF,
  0xFF, 0x00, 0xFF,
  0xEF, 0x36, 0xFF,
  0x5E, 0xE9, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0062[ 30] = { /* code 0062, LATIN SMALL LETTER B */
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x6E, 0xC1,
  0xFF, 0x96, 0xFA,
  0xFF, 0x11, 0xFE,
  0xFF, 0x00, 0xFF,
  0xFF, 0x11, 0xFE,
  0xFF, 0x86, 0xF9,
  0xFF, 0x5E, 0xC1
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0063[ 21] = { /* code 0063, LATIN SMALL LETTER C */
  0x09, 0xEF, 0xB2,
  0x8F, 0x63, 0xFC,
  0xEF, 0x10, 0x00,
  0xFF, 0x00, 0x00,
  0xEF, 0x10, 0x00,
  0x8F, 0x63, 0xFC,
  0x09, 0xEF, 0xB2
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0064[ 30] = { /* code 0064, LATIN SMALL LETTER D */
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFF,
  0x1C, 0xE5, 0xFF,
  0xAF, 0x69, 0xFF,
  0xEF, 0x11, 0xFF,
  0xFF, 0x00, 0xFF,
  0xEF, 0x11, 0xFF,
  0x9F, 0x68, 0xFF,
  0x1C, 0xE6, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0065[ 21] = { /* code 0065, LATIN SMALL LETTER E */
  0x1A, 0xFE, 0x90,
  0x9F, 0x65, 0xF8,
  0xEF, 0x10, 0xFD,
  0xFF, 0xFF, 0xFF,
  0xEF, 0x00, 0x00,
  0x9F, 0x63, 0xFC,
  0x19, 0xEF, 0xB2
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0066[ 30] = { /* code 0066, LATIN SMALL LETTER F */
  0x05, 0xEF, 0xB0,
  0x0E, 0xF2, 0x00,
  0x0F, 0xF0, 0x00,
  0xFF, 0xFF, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0067[ 30] = { /* code 0067, LATIN SMALL LETTER G */
  0x1B, 0xE7, 0xFF,
  0x9F, 0x69, 0xFF,
  0xEF, 0x11, 0xFF,
  0xFF, 0x00, 0xFF,
  0xEF, 0x11, 0xFF,
  0x9F, 0x69, 0xFF,
  0x1C, 0xE6, 0xFF,
  0x00, 0x00, 0xFE,
  0xE7, 0x13, 0xFB,
  0x5C, 0xFF, 0xB2
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0068[ 30] = { /* code 0068, LATIN SMALL LETTER H */
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x6E, 0xE4,
  0xFF, 0x83, 0xFD,
  0xFF, 0x10, 0xFF,
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0069[ 10] = { /* code 0069, LATIN SMALL LETTER I */
  0xFF,
  0xFF,
  0x00,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_006A[ 26] = { /* code 006A, LATIN SMALL LETTER J */
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0x00,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x00, 0xFF,
  0x02, 0xFD,
  0xBF, 0xD4
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_006B[ 40] = { /* code 006B, LATIN SMALL LETTER K */
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00,
  0xFF, 0x06, 0xF8, 0x00,
  0xFF, 0x4F, 0x80, 0x00,
  0xFF, 0xEC, 0x00, 0x00,
  0xFF, 0xFF, 0x30, 0x00,
  0xFF, 0x6F, 0xC0, 0x00,
  0xFF, 0x08, 0xF7, 0x00,
  0xFF, 0x01, 0xDE, 0x20
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_006C[ 10] = { /* code 006C, LATIN SMALL LETTER L */
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_006D[ 35] = { /* code 006D, LATIN SMALL LETTER M */
  0xFF, 0x4E, 0xE8, 0x7E, 0xE5,
  0xFF, 0x83, 0xFF, 0x83, 0xFD,
  0xFF, 0x10, 0xFF, 0x10, 0xFF,
  0xFF, 0x00, 0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF, 0x00, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_006E[ 21] = { /* code 006E, LATIN SMALL LETTER N */
  0xFF, 0x4E, 0xE5,
  0xFF, 0x73, 0xFE,
  0xFF, 0x10, 0xFF,
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_006F[ 21] = { /* code 006F, LATIN SMALL LETTER O */
  0x08, 0xEE, 0x80,
  0x7F, 0x66, 0xF7,
  0xDF, 0x11, 0xFD,
  0xFF, 0x00, 0xFF,
  0xDF, 0x11, 0xFD,
  0x8F, 0x66, 0xF7,
  0x09, 0xEE, 0x80
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0070[ 30] = { /* code 0070, LATIN SMALL LETTER P */
  0xFF, 0x5E, 0xC1,
  0xFF, 0x96, 0xFA,
  0xFF, 0x11, 0xFE,
  0xFF, 0x00, 0xFF,
  0xFF, 0x11, 0xFE,
  0xFF, 0x95, 0xF9,
  0xFF, 0x6F, 0xB1,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00,
  0xFF, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0071[ 30] = { /* code 0071, LATIN SMALL LETTER Q */
  0x1C, 0xF5, 0xFF,
  0xAF, 0x68, 0xFF,
  0xEF, 0x11, 0xFF,
  0xFF, 0x00, 0xFF,
  0xEF, 0x11, 0xFF,
  0x9F, 0x69, 0xFF,
  0x1C, 0xF5, 0xFF,
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFF,
  0x00, 0x00, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0072[ 14] = { /* code 0072, LATIN SMALL LETTER R */
  0xFF, 0xBC,
  0xFF, 0x51,
  0xFF, 0x10,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00,
  0xFF, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0073[ 21] = { /* code 0073, LATIN SMALL LETTER S */
  0x3C, 0xFF, 0xB2,
  0xDF, 0x23, 0xFC,
  0xEF, 0xC6, 0x10,
  0x6E, 0xFF, 0xE6,
  0x00, 0x59, 0xFE,
  0xCF, 0x32, 0xFD,
  0x2B, 0xFF, 0xC3
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0074[ 18] = { /* code 0074, LATIN SMALL LETTER T */
  0x04, 0xB0,
  0x0F, 0xF0,
  0xFF, 0xFF,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0F, 0xF0,
  0x0E, 0xF0,
  0x05, 0xFB
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0075[ 21] = { /* code 0075, LATIN SMALL LETTER U */
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0xFF, 0x00, 0xFF,
  0xFF, 0x01, 0xFF,
  0xDF, 0x38, 0xFF,
  0x5E, 0xD4, 0xFF
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0076[ 35] = { /* code 0076, LATIN SMALL LETTER V */
  0x4F, 0xB0, 0x00, 0xBF, 0x40,
  0x0C, 0xF2, 0x02, 0xFD, 0x00,
  0x06, 0xF9, 0x09, 0xF6, 0x00,
  0x00, 0xEE, 0x2E, 0xE0, 0x00,
  0x00, 0x7F, 0xCF, 0x80, 0x00,
  0x00, 0x1F, 0xFF, 0x20, 0x00,
  0x00, 0x09, 0xFA, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0077[ 42] = { /* code 0077, LATIN SMALL LETTER W */
  0xDF, 0x10, 0x7F, 0x60, 0x1F, 0xD0,
  0x8F, 0x70, 0xBF, 0xA0, 0x7F, 0x80,
  0x3F, 0xC0, 0xFE, 0xE0, 0xCF, 0x30,
  0x0D, 0xF6, 0xF7, 0xF6, 0xFD, 0x00,
  0x08, 0xFE, 0xF1, 0xEE, 0xF8, 0x00,
  0x03, 0xFF, 0xB0, 0xBF, 0xF3, 0x00,
  0x00, 0xEF, 0x70, 0x7F, 0xE0, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0078[ 28] = { /* code 0078, LATIN SMALL LETTER X */
  0x3F, 0xC0, 0x0C, 0xF3,
  0x08, 0xF6, 0x7F, 0x80,
  0x00, 0xDE, 0xFD, 0x00,
  0x00, 0x7F, 0xF8, 0x00,
  0x01, 0xEA, 0xBF, 0x20,
  0x09, 0xF3, 0x4F, 0xA0,
  0x3F, 0xB0, 0x0B, 0xF3
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_0079[ 40] = { /* code 0079, LATIN SMALL LETTER Y */
  0xDF, 0x20, 0x2F, 0xD0,
  0x8F, 0x70, 0x7F, 0x80,
  0x4F, 0xB0, 0xBF, 0x40,
  0x0E, 0xF2, 0xFE, 0x00,
  0x0A, 0xFB, 0xFB, 0x00,
  0x06, 0xFF, 0xF6, 0x00,
  0x01, 0xFF, 0xF2, 0x00,
  0x00, 0xCF, 0xB0, 0x00,
  0x03, 0xEF, 0x60, 0x00,
  0xFF, 0xC7, 0x00, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_007A[ 21] = { /* code 007A, LATIN SMALL LETTER Z */
  0xFF, 0xFF, 0xE0,
  0x00, 0x5F, 0x90,
  0x00, 0xDE, 0x10,
  0x08, 0xF7, 0x00,
  0x2F, 0xD0, 0x00,
  0xBF, 0x40, 0x00,
  0xFF, 0xFF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_007B[ 39] = { /* code 007B, LEFT CURLY BRACKET */
  0x03, 0xBF, 0xF0,
  0x0C, 0xF3, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xE0, 0x00,
  0x4F, 0x90, 0x00,
  0xFD, 0x00, 0x00,
  0x5F, 0x80, 0x00,
  0x0F, 0xE0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0F, 0xF0, 0x00,
  0x0C, 0xF3, 0x00,
  0x03, 0xBF, 0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_007C[ 12] = { /* code 007C, VERTICAL LINE */
  0xF0,
  0xF0,
  0xF0,
  0xF0,
  0xF0,
  0xF0,
  0xF0,
  0xF0,
  0xF0,
  0xF0,
  0xF0,
  0xF0
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_007D[ 39] = { /* code 007D, RIGHT CURLY BRACKET */
  0xFF, 0xB3, 0x00,
  0x03, 0xFC, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0xEF, 0x00,
  0x00, 0x8F, 0x50,
  0x00, 0x0D, 0xF0,
  0x00, 0x9F, 0x40,
  0x00, 0xEF, 0x00,
  0x00, 0xFF, 0x00,
  0x00, 0xFF, 0x00,
  0x03, 0xFC, 0x00,
  0xFF, 0xB3, 0x00
};

GUI_CONST_STORAGE unsigned char acGUI_FontF16B_AA_007E[  8] = { /* code 007E, TILDE */
  0x7E, 0xE9, 0x31, 0x80,
  0x81, 0x28, 0xEE, 0x70
};

GUI_CONST_STORAGE GUI_CHARINFO_EXT GUI_FontF16B_AA_CharInfo[95] = {
   {   1,   1,   0,  13,   4, acGUI_FontF16B_AA_0020 } /* code 0020, SPACE */
  ,{   2,  10,   1,   3,   4, acGUI_FontF16B_AA_0021 } /* code 0021, EXCLAMATION MARK */
  ,{   5,   3,   1,   3,   6, acGUI_FontF16B_AA_0022 } /* code 0022, QUOTATION MARK */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_0023 } /* code 0023, NUMBER SIGN */
  ,{   5,  12,   1,   2,   7, acGUI_FontF16B_AA_0024 } /* code 0024, DOLLAR SIGN */
  ,{   8,  10,   1,   3,  10, acGUI_FontF16B_AA_0025 } /* code 0025, PERCENT SIGN */
  ,{   8,  10,   1,   3,   9, acGUI_FontF16B_AA_0026 } /* code 0026, AMPERSAND */
  ,{   2,   3,   1,   3,   3, acGUI_FontF16B_AA_0027 } /* code 0027, APOSTROPHE */
  ,{   3,  13,   1,   3,   4, acGUI_FontF16B_AA_0028 } /* code 0028, LEFT PARENTHESIS */
  ,{   3,  13,   0,   3,   4, acGUI_FontF16B_AA_0029 } /* code 0029, RIGHT PARENTHESIS */
  ,{   5,   4,   0,   3,   5, acGUI_FontF16B_AA_002A } /* code 002A, ASTERISK */
  ,{   6,   5,   1,   6,   8, acGUI_FontF16B_AA_002B } /* code 002B, PLUS SIGN */
  ,{   2,   4,   1,  11,   4, acGUI_FontF16B_AA_002C } /* code 002C, COMMA */
  ,{   3,   1,   1,  10,   4, acGUI_FontF16B_AA_002D } /* code 002D, HYPHEN-MINUS */
  ,{   2,   2,   1,  11,   4, acGUI_FontF16B_AA_002E } /* code 002E, FULL STOP */
  ,{   4,  10,   0,   3,   4, acGUI_FontF16B_AA_002F } /* code 002F, SOLIDUS */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_0030 } /* code 0030, DIGIT ZERO */
  ,{   4,  10,   1,   3,   7, acGUI_FontF16B_AA_0031 } /* code 0031, DIGIT ONE */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_0032 } /* code 0032, DIGIT TWO */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_0033 } /* code 0033, DIGIT THREE */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_0034 } /* code 0034, DIGIT FOUR */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_0035 } /* code 0035, DIGIT FIVE */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_0036 } /* code 0036, DIGIT SIX */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_0037 } /* code 0037, DIGIT SEVEN */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_0038 } /* code 0038, DIGIT EIGHT */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_0039 } /* code 0039, DIGIT NINE */
  ,{   2,   7,   1,   6,   4, acGUI_FontF16B_AA_003A } /* code 003A, COLON */
  ,{   2,   9,   1,   6,   4, acGUI_FontF16B_AA_003B } /* code 003B, SEMICOLON */
  ,{   6,   7,   0,   5,   8, acGUI_FontF16B_AA_003C } /* code 003C, LESS-THAN SIGN */
  ,{   7,   3,   0,   7,   8, acGUI_FontF16B_AA_003D } /* code 003D, EQUALS SIGN */
  ,{   6,   7,   1,   5,   8, acGUI_FontF16B_AA_003E } /* code 003E, GREATER-THAN SIGN */
  ,{   7,  10,   0,   3,   8, acGUI_FontF16B_AA_003F } /* code 003F, QUESTION MARK */
  ,{  13,  13,   0,   3,  13, acGUI_FontF16B_AA_0040 } /* code 0040, COMMERCIAL AT */
  ,{   9,  10,   0,   3,   9, acGUI_FontF16B_AA_0041 } /* code 0041, LATIN CAPITAL LETTER A */
  ,{   7,  10,   1,   3,   9, acGUI_FontF16B_AA_0042 } /* code 0042, LATIN CAPITAL LETTER B */
  ,{   8,  10,   1,   3,   9, acGUI_FontF16B_AA_0043 } /* code 0043, LATIN CAPITAL LETTER C */
  ,{   7,  10,   1,   3,   9, acGUI_FontF16B_AA_0044 } /* code 0044, LATIN CAPITAL LETTER D */
  ,{   6,  10,   1,   3,   8, acGUI_FontF16B_AA_0045 } /* code 0045, LATIN CAPITAL LETTER E */
  ,{   6,  10,   1,   3,   8, acGUI_FontF16B_AA_0046 } /* code 0046, LATIN CAPITAL LETTER F */
  ,{   8,  10,   1,   3,  10, acGUI_FontF16B_AA_0047 } /* code 0047, LATIN CAPITAL LETTER G */
  ,{   7,  10,   1,   3,   9, acGUI_FontF16B_AA_0048 } /* code 0048, LATIN CAPITAL LETTER H */
  ,{   2,  10,   1,   3,   4, acGUI_FontF16B_AA_0049 } /* code 0049, LATIN CAPITAL LETTER I */
  ,{   6,  10,   0,   3,   7, acGUI_FontF16B_AA_004A } /* code 004A, LATIN CAPITAL LETTER J */
  ,{   8,  10,   1,   3,   9, acGUI_FontF16B_AA_004B } /* code 004B, LATIN CAPITAL LETTER K */
  ,{   6,  10,   1,   3,   8, acGUI_FontF16B_AA_004C } /* code 004C, LATIN CAPITAL LETTER L */
  ,{   9,  10,   1,   3,  11, acGUI_FontF16B_AA_004D } /* code 004D, LATIN CAPITAL LETTER M */
  ,{   7,  10,   1,   3,   9, acGUI_FontF16B_AA_004E } /* code 004E, LATIN CAPITAL LETTER N */
  ,{   8,  10,   1,   3,  10, acGUI_FontF16B_AA_004F } /* code 004F, LATIN CAPITAL LETTER O */
  ,{   7,  10,   1,   3,   9, acGUI_FontF16B_AA_0050 } /* code 0050, LATIN CAPITAL LETTER P */
  ,{   8,  11,   1,   3,  10, acGUI_FontF16B_AA_0051 } /* code 0051, LATIN CAPITAL LETTER Q */
  ,{   8,  10,   1,   3,   9, acGUI_FontF16B_AA_0052 } /* code 0052, LATIN CAPITAL LETTER R */
  ,{   7,  10,   1,   3,   9, acGUI_FontF16B_AA_0053 } /* code 0053, LATIN CAPITAL LETTER S */
  ,{   8,  10,   0,   3,   8, acGUI_FontF16B_AA_0054 } /* code 0054, LATIN CAPITAL LETTER T */
  ,{   7,  10,   1,   3,   9, acGUI_FontF16B_AA_0055 } /* code 0055, LATIN CAPITAL LETTER U */
  ,{   9,  10,   0,   3,   9, acGUI_FontF16B_AA_0056 } /* code 0056, LATIN CAPITAL LETTER V */
  ,{  13,  10,   0,   3,  13, acGUI_FontF16B_AA_0057 } /* code 0057, LATIN CAPITAL LETTER W */
  ,{   9,  10,   0,   3,   9, acGUI_FontF16B_AA_0058 } /* code 0058, LATIN CAPITAL LETTER X */
  ,{  10,  10,  -1,   3,   8, acGUI_FontF16B_AA_0059 } /* code 0059, LATIN CAPITAL LETTER Y */
  ,{   7,  10,   0,   3,   7, acGUI_FontF16B_AA_005A } /* code 005A, LATIN CAPITAL LETTER Z */
  ,{   3,  13,   1,   3,   4, acGUI_FontF16B_AA_005B } /* code 005B, LEFT SQUARE BRACKET */
  ,{   4,  10,   0,   3,   4, acGUI_FontF16B_AA_005C } /* code 005C, REVERSE SOLIDUS */
  ,{   3,  13,   0,   3,   4, acGUI_FontF16B_AA_005D } /* code 005D, RIGHT SQUARE BRACKET */
  ,{   6,   5,   0,   4,   8, acGUI_FontF16B_AA_005E } /* code 005E, CIRCUMFLEX ACCENT */
  ,{   7,   1,   0,  15,   7, acGUI_FontF16B_AA_005F } /* code 005F, LOW LINE */
  ,{   3,   2,   0,   3,   4, acGUI_FontF16B_AA_0060 } /* code 0060, GRAVE ACCENT */
  ,{   6,   7,   1,   6,   8, acGUI_FontF16B_AA_0061 } /* code 0061, LATIN SMALL LETTER A */
  ,{   6,  10,   1,   3,   8, acGUI_FontF16B_AA_0062 } /* code 0062, LATIN SMALL LETTER B */
  ,{   6,   7,   1,   6,   7, acGUI_FontF16B_AA_0063 } /* code 0063, LATIN SMALL LETTER C */
  ,{   6,  10,   1,   3,   8, acGUI_FontF16B_AA_0064 } /* code 0064, LATIN SMALL LETTER D */
  ,{   6,   7,   1,   6,   8, acGUI_FontF16B_AA_0065 } /* code 0065, LATIN SMALL LETTER E */
  ,{   5,  10,   0,   3,   4, acGUI_FontF16B_AA_0066 } /* code 0066, LATIN SMALL LETTER F */
  ,{   6,  10,   1,   6,   8, acGUI_FontF16B_AA_0067 } /* code 0067, LATIN SMALL LETTER G */
  ,{   6,  10,   1,   3,   8, acGUI_FontF16B_AA_0068 } /* code 0068, LATIN SMALL LETTER H */
  ,{   2,  10,   1,   3,   4, acGUI_FontF16B_AA_0069 } /* code 0069, LATIN SMALL LETTER I */
  ,{   4,  13,  -1,   3,   4, acGUI_FontF16B_AA_006A } /* code 006A, LATIN SMALL LETTER J */
  ,{   7,  10,   1,   3,   7, acGUI_FontF16B_AA_006B } /* code 006B, LATIN SMALL LETTER K */
  ,{   2,  10,   1,   3,   4, acGUI_FontF16B_AA_006C } /* code 006C, LATIN SMALL LETTER L */
  ,{  10,   7,   1,   6,  12, acGUI_FontF16B_AA_006D } /* code 006D, LATIN SMALL LETTER M */
  ,{   6,   7,   1,   6,   8, acGUI_FontF16B_AA_006E } /* code 006E, LATIN SMALL LETTER N */
  ,{   6,   7,   1,   6,   8, acGUI_FontF16B_AA_006F } /* code 006F, LATIN SMALL LETTER O */
  ,{   6,  10,   1,   6,   8, acGUI_FontF16B_AA_0070 } /* code 0070, LATIN SMALL LETTER P */
  ,{   6,  10,   1,   6,   8, acGUI_FontF16B_AA_0071 } /* code 0071, LATIN SMALL LETTER Q */
  ,{   4,   7,   1,   6,   5, acGUI_FontF16B_AA_0072 } /* code 0072, LATIN SMALL LETTER R */
  ,{   6,   7,   0,   6,   6, acGUI_FontF16B_AA_0073 } /* code 0073, LATIN SMALL LETTER S */
  ,{   4,   9,   0,   4,   4, acGUI_FontF16B_AA_0074 } /* code 0074, LATIN SMALL LETTER T */
  ,{   6,   7,   1,   6,   8, acGUI_FontF16B_AA_0075 } /* code 0075, LATIN SMALL LETTER U */
  ,{   9,   7,  -1,   6,   7, acGUI_FontF16B_AA_0076 } /* code 0076, LATIN SMALL LETTER V */
  ,{  11,   7,   0,   6,  11, acGUI_FontF16B_AA_0077 } /* code 0077, LATIN SMALL LETTER W */
  ,{   8,   7,   0,   6,   8, acGUI_FontF16B_AA_0078 } /* code 0078, LATIN SMALL LETTER X */
  ,{   7,  10,   0,   6,   7, acGUI_FontF16B_AA_0079 } /* code 0079, LATIN SMALL LETTER Y */
  ,{   5,   7,   1,   6,   7, acGUI_FontF16B_AA_007A } /* code 007A, LATIN SMALL LETTER Z */
  ,{   5,  13,   0,   3,   5, acGUI_FontF16B_AA_007B } /* code 007B, LEFT CURLY BRACKET */
  ,{   1,  12,   1,   3,   3, acGUI_FontF16B_AA_007C } /* code 007C, VERTICAL LINE */
  ,{   5,  13,   0,   3,   5, acGUI_FontF16B_AA_007D } /* code 007D, RIGHT CURLY BRACKET */
  ,{   7,   2,   0,   8,   8, acGUI_FontF16B_AA_007E } /* code 007E, TILDE */
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontF16B_AA_Prop1 = {
   0x0020 /* first character */
  ,0x007E /* last character  */
  ,&GUI_FontF16B_AA_CharInfo[  0] /* address of first character */
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0 /* pointer to next GUI_FONT_PROP_EXT */
};

GUI_CONST_STORAGE GUI_FONT GUI_FontF16B_AA = {
   GUI_FONTTYPE_PROP_AA4_EXT /* type of font    */
  ,16 /* height of font  */
  ,16 /* space of font y */
  ,1 /* magnification x */
  ,1 /* magnification y */
  ,{&GUI_FontF16B_AA_Prop1}
  ,15 /* Baseline */
  ,7 /* Height of lowercase characters */
  ,10 /* Height of capital characters */
};

/*************************** End of file ****************************/
