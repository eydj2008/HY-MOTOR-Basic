/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : menu.h
* Author             : MCD Application Team
* Version            : V2.0.0
* Date               : 04/27/2009
* Description        : This file contains all the functions prototypes for the
*                      menu navigation firmware driver.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MENU_H
#define __MENU_H

/* Includes ------------------------------------------------------------------*/
//#include "config.h"
#include "main.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define  MAX_MENU_LEVELS 4

#define  NOKEY  0
#define  SEL    1
#define  RIGHT  2
#define  LEFT   3
#define  UP     4
#define  DOWN   5

/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0


/* Module private variables --------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))

/* Private functions ---------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void Menu_Init(void);
void DisplayMenu(void);

void SelFunc(void);
void UpFunc(void);
void DownFunc(void);
void ReturnFunc(void);
u8   ReadKey(void);
void IdleFunc(void);
void DisplayIcons(void);
void ShowMenuIcons(void);
void FunnyCircles(void);
void STM32Intro(void);
void HelpFunc(void);
void AboutFunc(void);
void ArmbusFucn(void);
void ProductPres(void);
void SendFunc(void);
void ReceiveFunc(void);
u32  CheckBitmapFiles(void);   

void EnterSTOPMode_EXTI(void);
void EnterSTOPMode_RTCAlarm(void);
void EnterSTANDBYMode_WAKEUP(void);
void EnterSTANDBYMode_RTCAlarm(void);
void Time_Adjust(void);
void Time_AdjustFunc(void);
void Time_Show(void);
void Time_ShowFunc(void);
void Date_Adjust(void);
void Date_Show(void);
void Alarm_Adjust(void);
void Alarm_Show(void);
void Mass_Storage_Start(void);
void PanFunc(void);
void TiltFunc(void);
void AutoFunc(void);


u16 DelayJoyStick(u16 nTime);
void Time_Display(u16 a,u16 b,u32 TimeVar);

extern void Display_TXDData(u8 x,u8 y,u8 *Val);
extern void Display_RXDData(u8 x,u8 y,u8 *Val);
extern void Display255(u16 a,u16 b,u8 data);
extern void  ShowADValue(u16 a,u16 b);


extern u32 TimeDisplay;
extern u16 SendAddress;
extern u8 RXDData[];	  //513
extern u8 TXDData[];





#endif /* __MENU_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
