/**
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  CCW Application Team
  * @version V3.5.0
  * @date    2013-10-26
  * @brief   Main program body
  ******************************************************************************
  * @attention
  * 1.printf()     -----------------ok
  * 2.times PWM    -----------------ok
  * 3.L6205        -----------------ok
  * 4.TFT          -----------------ok
  * 5.MotorX Y ENCODER
  * 6.Motor Head
  * 7.COM
  * 8. ...
  * 
  ******************************************************************************
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
**/  

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#include "stm32f10x_spi.h"



/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/




/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
//==============================================================================
//TIM1-----------------------------------
u16 TimerPeriod  = 0;

//TIM1   35+1 0.5us
u16 TIM1CCR1_Val    = 200; //us
u16 TIM1CCR2_Val    = 1000;
u16 TIM1CCR3_Val    = 500;    //M X 20000
u16 TIM1CCR4_Val    = 500;    //M Y

//TIM3    35+1 0.5us
u16 Motor1Tcnt1Val  = 2000;       //M1
u16 Motor2Tcnt1Val  = 2000;
u16 Motor3Tcnt1Val  = 2000;
u16 Motor4Tcnt1Val  = 2000;

//TIM5    35+1 0.5us
u16 Motor5Tcnt1Val  = 2000;       //M5
u16 Motor6Tcnt1Val  = 2000;
u16 Motor7Tcnt1Val  = 2000;
u16 Motor8Tcnt1Val  = 2000;
//---------------------------------------
//PWM M-X 
u16 T2CCR1_Val      = CyclePWM>>1;
u16 T2CCR2_Val      = CyclePWM>>1;
u16 T2CCR3_Val      = CyclePWM>>1;
u16 T2CCR4_Val      = CyclePWM>>1;

//PWM M-Y
u16 T8CCR1_Val      = CyclePWM>>1;
u16 T8CCR2_Val      = CyclePWM>>1;
u16 T8CCR3_Val      = CyclePWM>>1;
u16 T8CCR4_Val      = CyclePWM>>1;

//==============================================================================

u16 M1DataPWM1        = 0;
u16 M1DataPWM2        = 0;
u16 M1DataPWM3        = 0;
u16 M1DataPWM4        = 0;

u16 M2DataPWM1        = 0;
u16 M2DataPWM2        = 0;
u16 M2DataPWM3        = 0;
u16 M2DataPWM4        = 0;

//==============================================================================
USART_InitTypeDef USART_InitStructure;
//----------------------------------------
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private functions ---------------------------------------------------------*/


//===============================================================================
void delayus(u16 time)			//delay routine		
{
	static u16 i;
    
	for(i=0;i<time*4;i++)		//*4  64M 1us  *1 16M  1us
	{
        NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	}
}

//===============================================================================
void delayms(u16 time)
{
	static u16 j;
	static u16 i;
	
	for(i=0; i<time*3; i++)	  //*4  64M 1ms  *1 16M  1ms
	    for(j=0; j<2000; j++)
	        NOP();
}

//===============================================================================
void LED_FLASH(u16 times)
{     
    //static u16 temp = 2000;  //200
	static u16 LEDCounter = 0;

    if (times == 0)   times = 1;
    if (++LEDCounter == 1*times)
    {
        DMXLEDH();
    }
	  else if (LEDCounter == 2*times)
    {
        LEDCounter = 0;
        
        DMXSignalFlag  = NO;	

        DMXLEDL();   
    }	 		
}

//===============================================================================
void TestFucn(void)   //test?
{
    
     //static u16 i = 0; 
 
     u8 iTest = 0; 
     //DMXLEDH(); 
     //delayms(1); 
     //delayus(1000); 
     //DMXLEDL(); 
     //delayms(1); 
     //delayus(1); 
      
      //MotorX_Dir = 1;
      

      
        
    
     //LED_FLASH(1);
    
      
    //SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
      
    //SP1Data = (u16)(0x007F)|(0x01<<8); //11

      
    //SPI_Write(SPI1,SP1Data); 
      
    //while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);  //(Transmit buffer empty)
    //SPI_I2S_SendData(SPI1, 0x088f);     //(u16)(i++)|(0x01<<8) 
    
    //Delay100ns(); Delay100ns();   
      
    
    //SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Reset);
    
    //Delay100ns(); Delay100ns(); 

    //SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
     
    
      
      
     //M1DataPWM1 += 1; 
     //if (M1DataPWM1 >= CyclePWM)     M1DataPWM1 = 0;    //test?
      
     //TIM_SetCompare1(TIM2, M1DataPWM1);   //TIM2->CCR1 = M1DataPWM1;
     //TIM_SetCompare2(TIM2, M1DataPWM1); 
     //TIM_SetCompare3(TIM2, M1DataPWM1);  
     //TIM_SetCompare4(TIM2, M1DataPWM1);  
     
      M1DataPWM1 = CyclePWM/4;
      
      TIM2->CCR1 = M1DataPWM1;
      TIM2->CCR2 = M1DataPWM1;
      TIM2->CCR3 = M1DataPWM1;
      TIM2->CCR4 = M1DataPWM1;
      
      TIM4->CCR1 = M1DataPWM1;
      TIM4->CCR2 = M1DataPWM1;
      TIM4->CCR3 = M1DataPWM1;
      TIM4->CCR4 = M1DataPWM1;
      
     
      
      
      //printf("%d_postion_now ! ->%d\r\n",i,Motor1_postion_now);  //
      //printf("%d_postion_user! ->%d\r\n",i,Motor1_postion_user); //
      //printf("%d_Pointer     ! ->%d\r\n",i,MotorPositionPointer);
}

//===============================================================================
void TestLCDFucn(void)   //test?
{
    
     static u16 i = 0; 
 
      i++;
      
      delayms(100);
      
   
      if (i == 60)
      {
         //MotorXDmxDataControl(0,0);
         //MotorYDmxDataControl(0,0);
        
         LCD_Clear(Blue);   
         GUI_Text(132,104,"HY-DEV-1",White,Blue);  
         GUI_Text(76,120,"Development Board V1.0",White,Red);
      
      }
      else if (i == 120)
      {
         i = 0;
         //MotorXDmxDataControl(50,0);
         //MotorYDmxDataControl(50,0);  
    
         LCD_Clear(Blue);
         GUI_Text(132,104,"HY-DEV-2",White,Blue);   
         GUI_Text(76,120,"Development Board V2.0",White,Red);

      }
      
    
//          MotorXDmxDataControl(RXDData[1],RXDData[2]);
//          MotorYDmxDataControl(RXDData[3],RXDData[4]);
//          
//          Motor1DmxDataControl(RXDData[5],0);
//          Motor2DmxDataControl(RXDData[6],0);
      
    if ((i%10)==0)
    {
        //ENCODER
        //if (Motor1_postion_user != CounterPanEncoder*2*MaxStep)
        //{
        //    CounterMotorXStepPostionNow = CounterPanEncoder*2*MaxStep;//+StartPostion;
        //}
      
      //printf("%d_CounterPanEncoder-->\r\n",i);     //
      
      //printf("%d_CounterTiltEncoder-->%d\r\n",i,CounterTiltEncoder);  //
      
      //printf("%d_RXDData[i]-->%d,%d,%d,%d,%d,%d \r\n",i,RXDData[0],RXDData[1],RXDData[2],RXDData[3],RXDData[4],RXDData[5]);  //RXDData
       //printf("i->%d user->%d now->%d pointer->%d SpeedPos->%d StepNow->%d \r\n",i,Motor1_postion_user,Motor1_postion_now,MotorPositionPointer,MotorXSpeedPos,SmallStepNow);
    }

}

/********************************************************************
*          ReadKEY
*********************************************************************/
void ReadKEY(void)
{	   
    static u16 KeyCounter   = 0;
//--------------------------------------------------------
    KeyCounter++;
    if (KeyCounter == 2 )
    {
       KeyCounter = 0;
       KeyMenu();		 //检测按键
    }
//--------------------------------------------------------
}

//===============================================================================
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
//===============================================================================
int main(void)
{
  /*!< @At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     

  //-----------------------------------------------------------------------------
  //FlashProtection();  //发行保护
    
  RCC_Configuration();

  GPIO_Configuration();
    
  EXTI_Configuration();			  
    
  USART1_Configuration8Bit();

  USART3_Configuration9Bit();    

  TIM_Configuration();
    
  SPI_Configuration();  

  NVIC_Configuration();
  
  LCD_Initializtion();


  Menu_Init();             //菜单配置

  DisplayMenu();           //菜单函数

  // Add your application code here----------------------------------------------
  ResetMotorFunction();   
 
  // Infinite loop --------------------------------------------------------------
  while (1)
  {
     
      
     //TestFucn();  //PWM
    //TestLCDFucn();
    
     TestMotorFucn();//  电机测试
    
    
     ReadKEY();
    //DisplayMenu();   //test?
     delayms(100);
    //DMXLEDH();
//     DMXLEDH(); 
//     delayms(1);
//     DMXLEDL(); 
//     delayms(1);
    
    LED_FLASH(3);
    
    //delay_ms(10);
    

      
  }
  //-----------------------------------------------------------------------------
}



//===============================================================================
void FlashProtection(void) 
{ 
  
  FlagStatus status = RESET;  
	status = FLASH_GetReadOutProtectionStatus(); 	//读出保护状态
    
    if(status != SET) 	//如果没有保护
    { 
        FLASH_Unlock();  					// Flash 解锁 
        FLASH_ReadOutProtection(ENABLE);    //读保护使能 
        FLASH_EnableWriteProtection(FLASH_WRProt_AllPages);  //写保护使能 
        FLASH_Lock();	   					// Flash 加锁
    } 
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  
  /* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  
  /* Enable TIM2, TIM3 and TIM4 clocks 36M*/
  RCC_APB1PeriphClockCmd( 
            //RCC_APB1Periph_WWDG |
            //RCC_APB1Periph_PWR | 
            //RCC_APB1Periph_BKP |
            //RCC_APB1Periph_USB |
            //RCC_APB1Periph_I2C1 | //和TIM4 PWM 1 2 不能同时使用
            //RCC_APB1Periph_I2C2 |
            //RCC_APB1Periph_USART2 |
            RCC_APB1Periph_USART3 |
            //RCC_APB1Periph_SPI2 |
            //RCC_APB1Periph_SPI3 |
            RCC_APB1Periph_TIM2 | //X
            RCC_APB1Periph_TIM3 |
            RCC_APB1Periph_TIM4 | //Y
            RCC_APB1Periph_TIM5, ENABLE); 
	  
  /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE and AFIO clocks 72M*/
  RCC_APB2PeriphClockCmd(
             RCC_APB2Periph_GPIOA | 
             RCC_APB2Periph_GPIOB |
						 RCC_APB2Periph_GPIOC | 
						 RCC_APB2Periph_GPIOD | 
						 RCC_APB2Periph_GPIOE |
						 RCC_APB2Periph_SPI1  |
						 RCC_APB2Periph_USART1 |	//和TIME1 PWM 2 3 不能同时使用
						 RCC_APB2Periph_TIM1 |
             RCC_APB2Periph_TIM8 |
						 //RCC_APB2Periph_ADC1 |
						 //RCC_APB2Periph_ADC2 |
						 //RCC_APB2Periph_ADC3 |
						 RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configure the TIM1 Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
    //test? OUT IO //PWM-IN
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

//#ifdef STM32F10X_CL


//#else
    //------------------------------------------------------------
    // Configure USART1 TxD (PA.09) as alternate function push-pull 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure USART1 RxD (PA.10) as input floating 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    //------------------------------------------------------------
    // Configure USART3 Tx (PB.10) as alternate function push-pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Configure USART3 Rx (PB.11) as input floating
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    //------------------------------------------------------------    
    //T2 PWM
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //T4 PWM
    //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    //T8 PWM
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //------------------------------------------------------------ 
    //DMX LED Output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //GPIO_Init(GPIOA, &GPIO_InitStructure);
    //------------------------------------------------------------
    //XEnCoder YEnCoder
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    //------------------------------------------------------------
    
    //------------------------------------------------------------ 
    //Motor1 Output
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOC, &GPIO_InitStructure);
//     
//     //Motor2 Output
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOC, &GPIO_InitStructure);
//     
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    
    
    
    

//#endif
}


//====================================================================================================
void EXTI_Configuration(void)
{   
    EXTI_InitTypeDef EXTI_InitStructure;

	// Connect -- EnCoder 0 1 2 3
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);
    // Connect -- HALL


    
    EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	 //EXTI_Trigger_Falling  //EXTI_Trigger_Rising_Falling
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}


/*******************************************************************************
* Function Name  : USART1_Configuration8Bit
* Description    : Configures the USART1.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_Configuration8Bit(void)
{
     USART_InitTypeDef USART_InitStructure;
/* USART1 configuration ------------------------------------------------------*/
	  USART_InitStructure.USART_BaudRate = 115200;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  	
  	USART_Init(USART1, &USART_InitStructure); 

  	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

  	USART_Cmd(USART1, ENABLE);
}

/*******************************************************************************
* Function Name  : USART1_Configuration9Bit
* Description    : Configures the USART1.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_Configuration9Bit(void)
{
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 250000;
  	USART_InitStructure.USART_WordLength = USART_WordLength_9b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  	USART_Init(USART3, &USART_InitStructure);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

  	USART_Cmd(USART3, ENABLE);

}

/*******************************************************************************
*
*	         定时器配置
*
*******************************************************************************/
/*******************************************************************************
TIM_OCMode_Timing是在比较成功后不在对应输出管脚上产生输出。

TIM_OCMode_Toggle是在比较成功后翻转对应输出管脚上的电平。

TIM_OCMode_Inactive;       //输出比较非主动模式

TIM_OCPolarity_High;  //极性为正
********************************************************************************/
void TIM_Configuration(void) 
{ 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  // TIM1 Configuration ---------------------------------------------------
  
  //TimerPeriod 	= 65535;//3456;   //Cycle 48us*(1/72)==3456
  //Channel1Pulse = CyclePWM/2;		 //50% Duty Cycle
  //Channel2Pulse = CyclePWM/2;
  //Channel3Pulse = CyclePWM/2;
  //Channel4Pulse = CyclePWM/2;	

  // Time Base configuration 
  TIM_TimeBaseStructure.TIM_Period = 0xffff;	 //设置自动重载寄存器值为最大值  比较中断中一定要设置为65535
  TIM_TimeBaseStructure.TIM_Prescaler = 35;	     //自定义预分频 71  test?
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  // Channel 1, 2,3 and 4 Configuration in TIME mode 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  //TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TIM1CCR1_Val;  // 1
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  //TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  //TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;    //Specifies the TIM Output Compare pin state during Idle state.
  //TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; //Specifies the TIM Output Compare pin state during Idle state.
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  
  TIM_OCInitStructure.TIM_Pulse = TIM1CCR2_Val;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = TIM1CCR3_Val;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = TIM1CCR4_Val;
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);

  
  TIM_ARRPreloadConfig(TIM1, ENABLE);

  // TIM1 enable counter 
  TIM_Cmd(TIM1, ENABLE);

  // Clear TIM1 update pending flag 
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);

  // TIM IT enable 	 // 打开捕获比较中断  test?---
  TIM_ITConfig(TIM1, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);


  //-------------------T3---------------------------------------
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 0xffff;  //设置自动重载寄存器值为最大值  比较中断中一定要设置为65535 
  TIM_TimeBaseStructure.TIM_Prescaler = 35;	  //自定义预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM3, 35, TIM_PSCReloadMode_Immediate);

  /* Output Compare Active Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;	 //输出比较定时模式
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

  TIM_OCInitStructure.TIM_Pulse = Motor1Tcnt1Val;		 //用户定义定时的周期
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);     //关闭预载入寄存器

  /* Output Compare Active Mode configuration: Channel2 */
  //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Motor2Tcnt1Val;
  
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);

  /* Output Compare Active Mode configuration: Channel3 */
  //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Motor3Tcnt1Val;
  
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);

  /* Output Compare Active Mode configuration: Channel4 */
  //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Motor4Tcnt1Val;
  
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);

  TIM_ARRPreloadConfig(TIM3, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);

  /* Clear TIM3 update pending flag */
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);

  /* TIM IT enable */	 // 打开捕获比较中断  test?---
  TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
  
    //-------------------T5---------------------------------------
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 0xffff;  //设置自动重载寄存器值为最大值  比较中断中一定要设置为65535 
  TIM_TimeBaseStructure.TIM_Prescaler = 35;	  //自定义预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM5, 35, TIM_PSCReloadMode_Immediate);

  /* Output Compare Active Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;	 //输出比较定时模式
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

  TIM_OCInitStructure.TIM_Pulse = Motor5Tcnt1Val;		 //用户定义定时的周期
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Disable);  //关闭预载入寄存器

  /* Output Compare Active Mode configuration: Channel2 */
  //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Motor6Tcnt1Val; 
  TIM_OC2Init(TIM5, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Disable);

  /* Output Compare Active Mode configuration: Channel3 */
  //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Motor7Tcnt1Val;  
  TIM_OC3Init(TIM5, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Disable);

  /* Output Compare Active Mode configuration: Channel4 */
  //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Motor8Tcnt1Val;  
  TIM_OC4Init(TIM5, &TIM_OCInitStructure); 
  TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Disable);
  

  TIM_ARRPreloadConfig(TIM5, ENABLE);

  /* TIM5 enable counter */
  TIM_Cmd(TIM5, ENABLE);

  /* Clear TIM5 update pending flag */
  TIM_ClearFlag(TIM5, TIM_FLAG_Update);

  /* TIM IT enable */	 // 打开捕获比较中断  test?---
  TIM_ITConfig(TIM5, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
  
  
  //==========================================================================================
  //PWM
  //-------------------T2---------------------------------------
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = CyclePWM;  //设置自动重载寄存器值为最大值  比较中断中一定要设置为65535 
  TIM_TimeBaseStructure.TIM_Prescaler = 0;	  //自定义预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	 //PWM1边沿对齐
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

  TIM_OCInitStructure.TIM_Pulse = T2CCR1_Val;		 //用户定义定时的周期
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);  //关闭预载入寄存器

  /* Output Compare Active Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = T2CCR2_Val;
  
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* Output Compare Active Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = T2CCR3_Val;
  
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* Output Compare Active Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = T2CCR4_Val;
  
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Disable);

  TIM_ARRPreloadConfig(TIM2, ENABLE);
  
  
  

//PWM
//-----------------------T4---------------------------------------   
  //TIM_TimeBaseStructure.TIM_Period = 299;            
  //* TIM4 configuration * 3600    3600*60000*1/72*10^6= 3 S     0xE0F
  //TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  /* Output Compare Timing Mode configuration: Channel1 */
  //TIM_OC1Init(TIM4, &TIM_OCInitStructure);
/*----------------------------------------------------------------------------
  TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
  =72M/(71999+1)=1KHZ
-----------------------------------------------------------------------------*/
    /* Time base configuration */
//   TIM_TimeBaseStructure.TIM_Period = CyclePWM;  //1023; //1ms自动重装值
//   TIM_TimeBaseStructure.TIM_Prescaler = 0;      //71;	   //预分频器值
//   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

//   TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

//   /* PWM1 Mode configuration: Channel1 */
//   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	 //PWM1边沿对齐
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//   TIM_OCInitStructure.TIM_Pulse = T8CCR1_Val;
//   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

//   TIM_OC1Init(TIM8, &TIM_OCInitStructure);
//   TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);	  //Disable

//   /* PWM1 Mode configuration: Channel2 */
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//   TIM_OCInitStructure.TIM_Pulse = T8CCR2_Val;

//   TIM_OC2Init(TIM8, &TIM_OCInitStructure);
//   TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);

//   /* PWM1 Mode configuration: Channel3 */
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//   TIM_OCInitStructure.TIM_Pulse = T8CCR3_Val;

//   TIM_OC3Init(TIM8, &TIM_OCInitStructure);
//   TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);

//   /* PWM1 Mode configuration: Channel4 */
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//   TIM_OCInitStructure.TIM_Pulse = T8CCR4_Val;

//   TIM_OC4Init(TIM8, &TIM_OCInitStructure);
//   TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);

//   TIM_ARRPreloadConfig(TIM8, ENABLE);

//--------------------------------------------------------------
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);

  /* TIM4 enable counter */
  //TIM_Cmd(TIM8, ENABLE);
//--------------------------------------------------------------


  /* Clear TIM2 update pending flag */
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);

  /* Clear TIM4 update pending flag */
  //TIM_ClearFlag(TIM8, TIM_FLAG_Update);
 //--------------------------------------------------------------

  /* Enable TIM2 Update interrupt */
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  /* Enable TIM4 Update interrupt */
  //TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);
//--------------------------------------------------------------
  //MOTOR Y-----------------------------------------------------
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = CyclePWM;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  //TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = T8CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  //TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  //TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  //TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM8, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = T8CCR2_Val;
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = T8CCR3_Val;
  TIM_OC3Init(TIM8, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = T8CCR4_Val;
  TIM_OC4Init(TIM8, &TIM_OCInitStructure);

  /* TIM1 counter enable */
  TIM_Cmd(TIM8, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM8, ENABLE);


}

//=============================================================================
//SPI1初始化
void SPI1_Init(void)
{
   SPI_InitTypeDef SPI_InitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;



   /* Configure SPI1 pins: NSS, SCK, MISO and MOSI */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   //上拉输入
   GPIO_Init(GPIOA, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;   //LD
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure); 

   /* SPI1 configuration */ 
   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
   SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
   SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;         //空闲时CLK电平
   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
   SPI_InitStructure.SPI_CRCPolynomial = 7;
   SPI_Init(SPI1, &SPI_InitStructure);

   /* Enable SPI1  */
   SPI_Cmd(SPI1, ENABLE);
}

//=============================================================================
//SPI1读写一字节数据
u8 SPI1_ReadWrite(u8 writedat)
{
   /* Loop while DR register in not emplty */
   while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

   /* Send byte through the SPI1 peripheral */
   SPI_I2S_SendData(SPI1, writedat);

   /* Wait to receive a byte */
   while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

   /* Return the byte read from the SPI bus */
   return SPI_I2S_ReceiveData(SPI1);
}

//============================================================================
void SPI3_Init(void)
{
   SPI_InitTypeDef SPI_InitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;




   /* Configure SPI3 pins: NSS, SCK, MISO and MOSI */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
   GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   //上拉输入
   GPIO_Init(GPIOB, &GPIO_InitStructure);
    
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;       //LD
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   /* SPI3 configuration */ 
   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
   SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
   SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
   SPI_InitStructure.SPI_CRCPolynomial = 7;

   SPI_Init(SPI3, &SPI_InitStructure);
   /* Enable SPI3  */
   SPI_Cmd(SPI3, ENABLE);
}

//SPI3读写一字节数据
u8 SPI3_ReadWrite(u8 writedat)
{
   /* Loop while DR register in not emplty */
   while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET);

   /* Send byte through the SPI1 peripheral */
   SPI_I2S_SendData(SPI3, writedat);

   /* Wait to receive a byte */
   while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET);

   /* Return the byte read from the SPI bus */
   return SPI_I2S_ReceiveData(SPI3);
}

//=============================================================================
void SPI_Configuration(void)
{
    
    //SPI1_Init();
    //SPI3_Init();
    
    
    // Configure SPI1 pins: NSS, SCK, MISO and MOSI   
    //模拟IO SPI1
   GPIO_InitTypeDef GPIO_InitStructure;
    
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;        //MISO  test?
   GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   //上拉输入
   GPIO_Init(GPIOA, &GPIO_InitStructure);
    
   // Configure SPI3 pins: NSS, SCK, MISO and MOSI 
   //模拟IO SPI3 
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  //NSS
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5; //SCK MOSI
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;       //MISO
   GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;   //上拉输入
   GPIO_Init(GPIOB, &GPIO_InitStructure); 
   
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //PA15 PB4 ==>IO
    
    
    

}

//=============================================================================
u16 SPI_Write(SPI_TypeDef* SPIx,u16 wdata)
{
    // Loop while DR register in not emplty 
   while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);

   // Send byte through the SPI1 peripheral
   SPI_I2S_SendData(SPIx, wdata);
    
    //!< Wait to receive a byte
  while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
  
  //!< Return the byte read from the SPI bus 
  return SPI_I2S_ReceiveData(SPIx);
    
    

}

/*******************************************************************************
* Function Name  : InterruptConfig	NVIC_Configuration
* Description    : Configures the used IRQ Channels and sets their priority.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{ 
	  NVIC_InitTypeDef NVIC_InitStructure;
	  //EXTI_InitTypeDef EXTI_InitStructure;
	  
	  /* Set the Vector Table base address at 0x08000000 */
	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);  //选择从FLASH启动
	  //NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);	  //选择从RAM启动
	  
	  /* Configure the Priority Group to 2 bits 各四级*/
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_Init(&NVIC_InitStructure);
	  
	  /* Enable the EXTI0-4 Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 //占先式优先级
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		 //副优先级P45
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	  NVIC_Init(&NVIC_InitStructure);
    
      NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 //占先式优先级
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		 //副优先级P45
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	  NVIC_Init(&NVIC_InitStructure);
      
      NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 //占先式优先级
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		 //副优先级P45
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	  NVIC_Init(&NVIC_InitStructure);
      
      NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 //占先式优先级
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		 //副优先级P45
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	  NVIC_Init(&NVIC_InitStructure);

	  /* Enable the EXTI9_5 Interrupt */
	  //NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //占先式优先级
	  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //副优先级P45
	  //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	  //NVIC_Init(&NVIC_InitStructure);
	  
	  /* Enable the EXTI15_10 Interrupt */
	  //NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	  //NVIC_Init(&NVIC_InitStructure);

	  /* Enable the EXTI16 Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	  NVIC_Init(&NVIC_InitStructure);
      
	  
	  /* Enable the TIM1 UP Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;	//TIM1_CC_IRQn	 TIM1_UP_IRQn
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //占先式优先级
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         //副优先级P45
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

  	  /* Enable the TIM2 Interrupt */
	  //NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	  //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  //NVIC_Init(&NVIC_InitStructure);
	  
	  /* Enable the TIM3 Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_Init(&NVIC_InitStructure);
	 
	  /* Enable the TIM5 Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_Init(&NVIC_InitStructure);

	  /* Enable the USART1 Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//TO PC
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	
	  /* Enable the USART3 Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; //COM
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	
	  

}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
