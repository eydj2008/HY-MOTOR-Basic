/**
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.h 
  * @author  CCW Application Team
  * @version V3.5.0
  * @date    2013-10-26
  * @brief   Main program body
  ******************************************************************************
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
**/ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "LCD.h"

//=======================================================================================================
#define CyclePWM		                    1500   //48KHZ  //3456  20.833KHZ

#define PanHall                             0x01
#define TiltHall                            0x02

//------LEDErrorStatus-----------------------
#define ErrorNO				0x0000

#define ErrorComBrd1		   0x0001
#define ErrorComBrd2		   0x0002
#define ErrorComBrd3		   0x0004
#define ErrorPanHall   		0x0008
#define	ErrorTiltHall		0x0010
#define ErrPanEncoder		0x0020
#define ErrTiltEncoder		0x0040
#define xxxxxxxxxxxxx		0x0080	   //test?---

#define	ErrorIrisHall		0x0100
#define ErrorGobo1Hall		0x0200
#define ErrorGobo1Rota		0x0400
#define ErrorGobo2Hall		0x0800
#define ErrorPrismHall		0x1000
#define ErrorFocusHall		0x2000
#define ErrorZoomHall		0x4000
#define ErrTemperature		0x8000

//========================================================================================================
#define step							        128		    //步进电机细分最高步数  不用修改！与数组最大细分有关
#define MaxStep 						        16			  //
#define SMALL_STEP						     128          //步进电机细分步数 初始设置
#define StartPostion					        1024        //
#define MotorXResetBackPostion			    ((s32)(StartPostion+MaxStep*255*7))
#define MotorYResetBackPostion			    ((s32)(StartPostion+MaxStep*255*3))

/* Private define ------------------------------------------------------------*/
#define CLI()		  	        __set_PRIMASK(1)					
#define SEI()			          __set_PRIMASK(0)
#define NOP()			          __nop()
#define Delay100ns()        NOP();NOP();NOP();NOP();NOP();   //72 NOP == 1us
#define Delay200ns()        NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
                           
//=============================================================================
#define	YES			        1
#define	NO			        0
#define True		        1
#define False		        0

//=============================================================================
#define DMXLEDH()           (GPIOB->BSRR = GPIO_Pin_2)
#define DMXLEDL()           (GPIOB->BRR  = GPIO_Pin_2)

// #define DMXLED1H()           (GPIOC->BSRR = GPIO_Pin_4)
// #define DMXLED1L()           (GPIOC->BRR  = GPIO_Pin_4)
// #define DMXLED2H()           (GPIOC->BSRR = GPIO_Pin_5)
// #define DMXLED2L()           (GPIOC->BRR  = GPIO_Pin_5)


//=============================================================================
#define XEnCoderA           (GPIOC->IDR & GPIO_Pin_2)
#define XEnCoderB           (GPIOC->IDR & GPIO_Pin_3)

#define YEnCoderA           (GPIOC->IDR & GPIO_Pin_0)
#define YEnCoderB           (GPIOC->IDR & GPIO_Pin_1)
//-----------------------------------------------------------------------------


/* Private function prototypes -----------------------------------------------*/
//=============================================================================
void FlashProtection(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void EXTI_Configuration(void);			
void USART1_Configuration8Bit(void);
void USART3_Configuration9Bit(void);
void SPI_Configuration(void);
void TIM_Configuration(void);
void NVIC_Configuration(void);

//----------------------------------------------------------------------------
u8 SPI1_ReadWrite(u8 writedat);
u8 SPI3_ReadWrite(u8 writedat);
u16 SPI_Write(SPI_TypeDef* SPIx,u16 wdata);


//extern u16 Motor1Tcnt1Val;
//extern u16 Motor2Tcnt1Val;
//extern u16 Motor3Tcnt1Val;
//extern u16 Motor4Tcnt1Val;
//=============================================================================
extern void delayus(u16 time);
extern void delayms(u16 time);
extern void LED_FLASH(u16 times);


extern void Motor1DAPointerControl(void);

//=============================================================================
extern u8 DMXSignalFlag;

//extern u8 MotorX_Dir;
//extern u8 MotorY_Dir;
extern u16 TIM1CCR3_Val;
extern u16 TIM1CCR4_Val;

extern u8 DecayXCurrentFlag;


extern u16 MotorXSpeedPos;
extern s32 CounterMotorXStepPostionCurrent;
extern u16 MotorXStep_StartStop; 

extern u16 MotorYSpeedPos;
extern s32 CounterMotorYStepPostionCurrent;
extern u16 MotorYStep_StartStop; 

extern void MotorXDmxDataControl(u8 Dmxdata,u8 Finedata);
extern void MotorYDmxDataControl(u8 Dmxdata,u8 Finedata);

extern void MotorXDriveInTimer(void);
extern void MotorYDriveInTimer(void);
extern void Motor1DriveInTimer(void);

extern void ResetMotorFunction(void);

//--------------------------------------------------------------------------------------
extern u8 RXDData[];
extern const u16 SinData[];
extern const u16 CosData[];
extern const u16 SpeedCurveTimerVal[];
extern const u16 SpeedCurve64TimerValUp[];
extern const u16 SpeedCurve64TimerValDown[];
extern const u8 DATA_VREF1[];
extern const u8 DATA_VREF2[];

extern u16 Motor1Tcnt1Val;       //M1
extern u16 Motor2Tcnt1Val;
extern u16 Motor3Tcnt1Val;
extern u16 Motor4Tcnt1Val;

extern u16 Motor5Tcnt1Val;       //M5
extern u16 Motor6Tcnt1Val;
extern u16 Motor7Tcnt1Val;
extern u16 Motor8Tcnt1Val;


#endif /* __MAIN_H */


