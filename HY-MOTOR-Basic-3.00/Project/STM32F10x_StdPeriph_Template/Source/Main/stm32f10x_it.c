/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  *
  *
  *
  *
  *
  *
  *
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "main.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */
  
uint16_t capture = 0;


extern u16 TIM1CCR1_Val;
extern u16 TIM1CCR2_Val;
extern u16 TIM1CCR3_Val;
extern u16 TIM1CCR4_Val;

extern u16 Motor1Tcnt1Val;
extern u16 Motor2Tcnt1Val;
extern u16 Motor3Tcnt1Val;
extern u16 Motor4Tcnt1Val;
extern u16 Motor5Tcnt1Val;
extern u16 Motor6Tcnt1Val;
extern u16 Motor7Tcnt1Val;
extern u16 Motor8Tcnt1Val;

extern u16 CounterPanEncoder;
extern u16 CounterTiltEncoder;

u8 DMXSignalFlag = 0;
u8 RXDData[19]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/*******************************************************************************
* Function Name  : EXTI4-0_IRQHandler
* Description    : This function handles External lines 4 to 0 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//====================================================================================================
void EXTI0_IRQHandler(void)	 
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
	//------------------------------------------
        if(YEnCoderB)
        {
            if(!YEnCoderA)
             {
               CounterTiltEncoder--;
             }
             else
             {
               CounterTiltEncoder++;
             }
        }
        else
        {
           if(!YEnCoderA)
             {
               CounterTiltEncoder++;
             }
             else
             {
               CounterTiltEncoder--;
             }
        }


      
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

//====================================================================================================
void EXTI1_IRQHandler(void)	 
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
	//TEST 
        if(YEnCoderA)
        {
            if(YEnCoderB)
             {
               CounterTiltEncoder--;
             }
             else
             {
               CounterTiltEncoder++;
             }
        }
        else
        {
           if(YEnCoderB)
             {
               CounterTiltEncoder++;
             }
             else
             {
               CounterTiltEncoder--;
             }
        }


     
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

//====================================================================================================
void EXTI2_IRQHandler(void)	 
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
	if(XEnCoderB)
	{
	   	 if(!XEnCoderA)
		 {
		   CounterPanEncoder--;
		 }
		 else
		 {
		   CounterPanEncoder++;
		 }
	}
	else
	{
	     if(!XEnCoderA)
		 {
		   CounterPanEncoder++;
		 }
		 else
		 {
		   CounterPanEncoder--;
		 }
	} 



    /* Clear the EXTI Line 0 */  
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}

//====================================================================================================
void EXTI3_IRQHandler(void)	 
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {

	 
    if(XEnCoderA)
	{
	   	if(XEnCoderB)
		 {
		   CounterPanEncoder--;
		 }
		 else
		 {
		   CounterPanEncoder++;
		 }
	}
	else
	{
	   if(XEnCoderB)
		 {
		   CounterPanEncoder++;
		 }
		 else
		 {
		   CounterPanEncoder--;
		 }
	}


    /* Clear the EXTI Line 0 */  
    EXTI_ClearITPendingBit(EXTI_Line3);
  }
}

//====================================================================================================
void TIM1_CC_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);

    //100us
    //GPIO_WriteBit(GPIOC, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6)));
    //LED_FLASH(1000);    
      
    capture = TIM_GetCapture1(TIM1);
    TIM_SetCompare1(TIM1, capture + TIM1CCR1_Val);
  }
  else if (TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);

    /* Pin PC.07 toggling with frequency = 109.8 Hz */
    //GPIO_WriteBit(GPIOC, GPIO_Pin_7, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7)));
      
    capture = TIM_GetCapture2(TIM1);
    TIM_SetCompare2(TIM1, capture + TIM1CCR2_Val);
  }
  else if (TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);

    //X-------------------------------------------------
      
      MotorXDriveInTimer();   //IN 10us/140us
      //LED_FLASH(1);
      
    capture = TIM_GetCapture3(TIM1);
    TIM_SetCompare3(TIM1, capture + TIM1CCR3_Val);
  }
  else
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);

    //Y-------------------------------------------------
      MotorYDriveInTimer();
      
    capture = TIM_GetCapture4(TIM1);
    TIM_SetCompare4(TIM1, capture + TIM1CCR4_Val);
  }
}


//====================================================================================================
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
    //------------------------------------------------------
    //Motor1DriveInTimer();   
      
    capture = TIM_GetCapture1(TIM3);
    TIM_SetCompare1(TIM3, capture + Motor1Tcnt1Val);
  }
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
    //------------------------------------------------------
    //Motor2DriveInTimer();
      
    capture = TIM_GetCapture2(TIM3);
    TIM_SetCompare2(TIM3, capture + Motor2Tcnt1Val);
  }
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);

    //------------------------------------------------------
    //Motor3DriveInTimer();
      
    capture = TIM_GetCapture3(TIM3);
    TIM_SetCompare3(TIM3, capture + Motor3Tcnt1Val);
  }
  else
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);

    //------------------------------------------------------
    //Motor4DriveInTimer();
      
    capture = TIM_GetCapture4(TIM3);
    TIM_SetCompare4(TIM3, capture + Motor4Tcnt1Val);
  }
}

//====================================================================================================
void TIM5_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);

    //------------------------------------------------------
    //Motor5DriveInTimer();
      
    capture = TIM_GetCapture1(TIM5);
    TIM_SetCompare1(TIM5, capture + Motor5Tcnt1Val);
  }
  else if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);

    //------------------------------------------------------
    //Motor6DriveInTimer();
      
    capture = TIM_GetCapture2(TIM5);
    TIM_SetCompare2(TIM5, capture + Motor6Tcnt1Val);
  }
  else if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);

    //------------------------------------------------------
    //Motor7DriveInTimer();
      
    capture = TIM_GetCapture3(TIM5);
    TIM_SetCompare3(TIM5, capture + Motor7Tcnt1Val);
  }
  else
  {
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);

    /* Pin PC.09 toggling with frequency = 439.4 Hz */
    //GPIO_WriteBit(GPIOC, GPIO_Pin_9, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9)));
    capture = TIM_GetCapture4(TIM5);
    TIM_SetCompare4(TIM5, capture + Motor8Tcnt1Val);
  }
}


//====================================================================================================
/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval : None
  */
void USART3_IRQHandler(void)   //DMX512
{
	static u16 i=0;
   	static u16 UDR=0;
   	static u16 CODE_Data=0;
   	static u8 RXB8=0;

  if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET)
  {
    // Read one byte from the receive data register 
	//--------------------------------------------------------------------
	
	UDR = USART_ReceiveData(USART3);  //16bit  0-8  9bit

	RXB8 = (u8)((UDR>>8)&0x01);  

	if (RXB8)        //(1<<RXB8))
    {   
		//SIGN_LED_FLASH = YES;    //-------TEST LED---------------
		DMXSignalFlag = YES;

		//DMX address count register
		RXDData[i] = (u8)(UDR);		 
        if (++i>=512)  i = 0;
		   
    }
    else            //(0<<RXB8)
    {
        CODE_Data = UDR;
        if (CODE_Data==0)
        {   
            i = 0;
            CODE_Data  = 0x1ff;
        }
    }

	 
	//--------------------------------------------------------------------
  }
   
  if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  {   
      // Disable the USART3 Transmit interrupt 
      USART_ITConfig(USART3, USART_IT_TXE, DISABLE);	 //清中断 要不然一直执行此中断 OK
  }	
	 	

}


//====================================================================================================

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/






