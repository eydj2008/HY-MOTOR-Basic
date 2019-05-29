/**
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  ******************************************************************************
  * @file    Project\STM32F10x_StdPeriph_Template\Source\Motor\motor.c 
  * @author  CCW Application Team
  * @version V3.5.0
  * @date    2013-10-26
  * @brief   Main program body
  ******************************************************************************
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
**/

#include "main.h"

//-----------main and motor------------------------------------------------------------------
u16 MotorYSpeedPos 						   	           = 0;
s32 CounterMotorYStepPostionCurrent           	 = StartPostion; //步进电机1当前位置计数器
u16 MotorYStep_StartStop                     = 256;	//最高速度 MotorSpeed

//-----------------------------------------------------------------------------------
//static uint32 Count_Motor1_Postion_Current         = 0;
/*****************************************************************************************/
static u16 step_startstop 				   	      = 0;	//起停距离1 256微步 起停距离2 512微步
//static u16 SmallStepCurrent 				 	    = SMALL_STEP;       //当前步进电机细分步数寄存器 127  64  32  16  8  4  2  1步 //步进电机细分步数 初始设置
static u8  LineFlag						              = YES;
//----------------------------Motor-1---------------------------------------------------------------
static s16 MotorPositionPointer             = 0;  
static u8  Motor1_Stop_Flag                 = 0;
static u8  Motor1_dir                       = 1;  
static u8  Motor1WillBackFlag               = 0;
static u8  Motor1_dir_Current               = 1;
static u8  Motor1_speed_postion_dir         = 1;
static s32 Motor1_postion_Current           = StartPostion;
static s32 Motor1_postion_user              = StartPostion;
static s32 Motor1_dynamic_postion_gap       = 0;           
static s32 Motor1_user_postion_gap          = 0;         
//-----------------------------------------------------------------------------------------------


/*****************************************************************************
*		s32	CheckValChange 	   two times
*****************************************************************************/
static u8 CheckValChange1(s32 Val)
{
    static s32 tempa1    = 0;
    static s32 tempb1    = 0;
    static u8  i         = 0;
	  static u8  m		 = 0;

//-------------------------------------------------------------------
    i++;
    switch (i)
    {
    case 1:
        tempa1 = Val;
        break;
    case 2:
        i = 0;      //CLR 0
        tempb1 = Val;
        break;
    }
   //-------------------------------
    if (tempa1 != tempb1)
		m = YES;
	else
		m = NO;

		return m;
//-------------------------------------------------------------------
}

/*******************************************************************/
static u8 CheckValChange2(s32 Val)
{
    static s32 tempa1    = 0;
    static s32 tempb1    = 0;
    static u8  i         = 0;
	static u8  m		 = 0;

//-------------------------------------------------------------------
    i++;
    switch (i)
    {
    case 1:
        tempa1 = Val;
        break;
    case 2:
        i = 0;      //CLR 0
        tempb1 = Val;
        break;
    }
   //-------------------------------
    if (tempa1 != tempb1)
		m = YES;
	else
		m = NO;

		return m;
//-------------------------------------------------------------------
}

/*******************************************************************/
static u8 CheckValChange3(s32 Val)
{
    static s32 tempa1    = 0;
    static s32 tempb1    = 0;
    static u8  i         = 0;
	static u8  m		 = 0;

//-------------------------------------------------------------------
    i++;
    switch (i)
    {
    case 1:
        tempa1 = Val;
        break;
    case 2:
        i = 0;      //CLR 0
        tempb1 = Val;
        break;
    }
   //-------------------------------
    if (tempa1 != tempb1)
		m = YES;
	else
		m = NO;

		return m;
//-------------------------------------------------------------------
}

//----------------------------Motor1WaitProgram--------------------------------------------------------------
static void Motor1WaitProgram(void)
{
    if (Motor1_postion_user  > Motor1_postion_Current)  
    {
        Motor1_user_postion_gap   = Motor1_postion_user - Motor1_postion_Current;  
        if (Motor1_dir_Current == 1)  //MotorYSpeedPos
        {
            Motor1WillBackFlag = 0;
        }
        else
        {
            Motor1WillBackFlag = 1;
        }
        if (Motor1_Stop_Flag) Motor1_speed_postion_dir = YES;
    }
    //--------------------------------------------------------------------------------------------------------------------------
    if (Motor1_postion_user  < Motor1_postion_Current)  
    {
        Motor1_user_postion_gap   = Motor1_postion_Current  - Motor1_postion_user;  
        if (Motor1_dir_Current == 0)
        {
            Motor1WillBackFlag = 0;
        }
        else
        {
            Motor1WillBackFlag = 1;
        }
        if (Motor1_Stop_Flag) Motor1_speed_postion_dir = NO;
    }
//-----------------------------------------------------------------------------------
    if (Motor1_user_postion_gap <= 8*MaxStep)
    {
        step_startstop = Motor1_user_postion_gap/MaxStep / 4;
    }
    else if ((8*MaxStep < Motor1_user_postion_gap) && (Motor1_user_postion_gap < MotorYStep_StartStop*2*MaxStep)) //<=512*2
    {   // only two state
        step_startstop = Motor1_user_postion_gap/MaxStep / 2;
    }
    else
    {
        step_startstop = MotorYStep_StartStop;
    }
}








//==============================================================================================================
//----------------------细分数选择128-8函数-------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------
/*****************************************************************************************
*
*				 步进电机驱动根据位置，控制速度函数 
*       
*****************************************************************************************/
static void Motor1DynamicPostionGap(void)             // LOOP IN TIME0 48us
{
    
//------------------------------------------------------------------------
    if (!MotorYSpeedPos)
    {
        Motor1_Stop_Flag = 1;
    }
    else
    {
        Motor1_Stop_Flag = 0;
    }
    //-------------------------------------------------------------------
    if (Motor1_Stop_Flag)  //如果当前电机已经停止  再检查
    {
        Motor1WaitProgram();
    }
//---------------------------------------------------------------------------------------------------------------
    
	if (Motor1_postion_user == Motor1_postion_Current)
    {
	    Motor1_dynamic_postion_gap = 0;

	} 
	//---------------------------------------------------------------------------------
    else if (Motor1_postion_user  > Motor1_postion_Current)  
    {  // 同向
        Motor1_dynamic_postion_gap  = Motor1_postion_user - Motor1_postion_Current;   //位置差 Postion_gap   一个位置差为10步 一圈200步
		if (Motor1_Stop_Flag) Motor1_speed_postion_dir = YES;
    }
	//-----------------------------------------------------------------------------------
    else if (Motor1_postion_user < Motor1_postion_Current)       
    {
        Motor1_dynamic_postion_gap  = Motor1_postion_Current - Motor1_postion_user;    //反向位置差值
		if (Motor1_Stop_Flag)  Motor1_speed_postion_dir = NO;
    }
//-----------------------------------------------------------------------------------------------------------------
}

//----------------------------------------------------------------------


/*****************************************************************************************
*
*				 步进电机驱动函数 
*       
*      Motor1_drive(Motor1_speed_postion_dir,20,Motor1_dynamic_postion_gap/100);
*****************************************************************************************/
static void Motor1_drive(u8 dir,u16 SpeedPostion)    //STEP  步进电机步数  200步 为一圈
{
    static u16 SpeedVal =0;

	SpeedVal = SpeedCurveTimerVal[SpeedPostion];
	
    //----------------------------------------------------------------------
    Motor1_dir      = dir;
    TIM1CCR4_Val	= 65535 - SpeedVal;  //u16
    //T0Tcnt0Val      = speed;   //改变定时器初值 改变每个微步的时间  //test?
}



/*****************************************************************************************
*
*				 步进电机根据当前位置 控制 速度 达到指定位置 驱动函数 
*                                
*****************************************************************************************/
static void Motor1PostionControlSpeed(void)          // LOOP IN T0
{

//---------------------------------------------------------------------------------------
	if (CheckValChange3(Motor1_dynamic_postion_gap))
	{
	  	if (((Motor1_user_postion_gap-step_startstop*MaxStep) < Motor1_dynamic_postion_gap) && (Motor1_dynamic_postion_gap <= Motor1_user_postion_gap))
            LineFlag = 1;  //1 加速  0 减速  2 匀速 (停止)  
	}

    Motor1_drive(Motor1_speed_postion_dir,MotorYSpeedPos);

	//MicroStep and MaxStep  Motor1_postion_Current	  Motor1_dynamic_postion_gap
	//-------- CheckValChange --------
    if (CheckValChange2(Motor1_dynamic_postion_gap/MaxStep))
    {
        if (Motor1WillBackFlag==0)
        {   //-----------------------------------------------------------------
            if ((0 < Motor1_dynamic_postion_gap) && (Motor1_dynamic_postion_gap <= MotorYSpeedPos*MaxStep))  //loop 20*256/x (256-32) 20为20步
            {                
                if (MotorYSpeedPos)
                {
                    MotorYSpeedPos--;  //减速制动
                    LineFlag = 0;
                }
            }//-----------------------------------------------------------------
            else if ((step_startstop*MaxStep < Motor1_dynamic_postion_gap) && (Motor1_dynamic_postion_gap <= (Motor1_user_postion_gap-step_startstop*MaxStep)))
            {
				LineFlag = 2;
            }//-----------------------------------------------------------------
            else if (((Motor1_user_postion_gap-step_startstop*MaxStep) < Motor1_dynamic_postion_gap) && (Motor1_dynamic_postion_gap <= Motor1_user_postion_gap))
            {
                if (MotorYSpeedPos<step_startstop)
                {
					          MotorYSpeedPos++;  //加速启动
                    LineFlag = 1;
                }
            }//-----------------------------------------------------------------
            else if (Motor1_dynamic_postion_gap > Motor1_user_postion_gap)
            {
                Motor1WillBackFlag = 1;  //减速制动
            }
        }
        //----------------------------------------------------------------------------------------
        else if ((Motor1WillBackFlag==1))//|(Motor1MakeStopFlag==1)) //stop
        {   
            if (MotorYSpeedPos)
            {
                MotorYSpeedPos--;
                LineFlag = 0;
            }
            else
            {
                Motor1WillBackFlag = 0;
            }
        }
    }

//----------------------------------------------------------------------------------------------------------------------------------------------
}


/*****************************************************************************************
*      当前步进电机状态寄存器   方向  速度  角度 等信息记录
*	      Motor_state        0x01   ==> 正向   0x00   ==> 反向       		0   1
*  1111 1111 1111 1111    1111 1111 1111 1111         4*8 = 32
*                                              方向为 00-07位               0 - 1
*				  		速度为 08-15位         0X0000-0x0000 ff00                0-255
*						位置为 16-23位  表示  0X00 00 00 00 -  0X00 FF 00 00     0-255
*****************************************************************************************/
static void Motor1PointerControl(void)        //100us*32 == 3.2ms     LOOP in Time0
{
	static u16 iStop = 0;

	//----------------------------------------------------------------------DmxFinedataUser
    if ((Motor1_postion_Current == Motor1_postion_user)&&(!MotorYSpeedPos))//&&(DmxFinedataUser==CounterFinedataCurrent))
    { 
        Motor1_user_postion_gap    = 0;
        Motor1_dynamic_postion_gap = 0;

		LineFlag = 2;//YES;		

        //------------------------------------------------------------       
        if (iStop > 100) //655us/2*500
        {
            TIM8->CCR1 =          (SinData[MotorPositionPointer])>>2;
            TIM8->CCR2 = (CyclePWM-SinData[MotorPositionPointer])>>2;
            TIM8->CCR3 =          (CosData[MotorPositionPointer])>>2;
            TIM8->CCR4 = (CyclePWM-CosData[MotorPositionPointer])>>2;
            //LED_FLASH(1);
        }
        else
        {
            iStop++;
        }
        //----------------STOP AND AUTO TURN BACK---------------------
		        //Motor1_StopAutoBACK();
        //------------------------------------------------------------
    }
    else   //---(Motor1_postion_Current != Motor1_postion_user)---
    {
        //Motor1_Arrive_Flag = 0;   //电机停止 用户设定位置未到达 标记
		//------------------------------------------------------------
      iStop = 0;   
        
	    TIM8->CCR1 =          SinData[MotorPositionPointer];
      TIM8->CCR2 = CyclePWM-SinData[MotorPositionPointer];
      TIM8->CCR3 =          CosData[MotorPositionPointer];
      TIM8->CCR4 = CyclePWM-CosData[MotorPositionPointer];


		//---------正反转控制-----------------------------------------
        if (Motor1_dir == 1)            //用户欲控制方向 为正向时  
            Motor1_dir_Current     = 1;
        else                           //用户欲控制方向 为反向时
            Motor1_dir_Current     = 0;
		//------------------------------------------------------------ 
        
      if (Motor1_dir_Current == YES)   //控制步进电机 正向旋转
      {
          //不加则停止转动 锁定状态
        
            MotorPositionPointer += 8;
            CounterMotorYStepPostionCurrent += 1;

          //--------------------------------------------------          
	     if (MotorPositionPointer >= 512)  MotorPositionPointer = 0; 
     }
     else                //控制步进电机 反向旋转
     {                          
				
            MotorPositionPointer -= 8;
            CounterMotorYStepPostionCurrent -= 1;
	
          //--------------------------------------------------
          if (MotorPositionPointer <= 0)  MotorPositionPointer = 512; 
     }
  } 

//---------------------------------------------------------------------------------------------------------------
	Motor1_postion_Current = CounterMotorYStepPostionCurrent;
    //当前状态侦测  并存入状态寄存器 存入当前状态	    
//---------------------------------------------------------------------------------------------------------------
}

/*****************************************************************************************
*
*				 步进电机  位置  控制函数 
*                         void Motor1_postion_control(u16 Motor1_postion)   0-255
*****************************************************************************************/
static void Motor1_postion_control(s32 postion)   // 一个位置 ==  ？
{

    if (CheckValChange1(postion))
    {
        //-------------------------------------------------------------------------------------------------
        Motor1_postion_user      = postion;     //用户设定位置  全局变量
        Motor1WaitProgram();
    }//-----------------------------------------------------------------------------------------------------
}

/********************************************************************
*
*          Motor1DmxDataControl
*
*********************************************************************/
void MotorYDmxDataControl(u8 Dmxdata,u8 Finedata)
{    //0-255 ==== 0-9R*200 =1800  1800/255 = 7.05     540/360=1.5 *变比==> 1.5*6=9
    static s32 i=0;
	static u8 RatioA  = 8;//50;   //8  9
	static u8 RatioB  = 1;//255;   //1

	i = (s32)((Dmxdata*MaxStep*RatioA/RatioB)+Finedata+StartPostion);

        //---------每步大于一步1.8--------------------------------------------------	
	//i = (Dmxdata*RatioA/RatioB)+(Finedata)/MaxStep+StartPostion;  //+100 6	 Step
	//DmxFinedataUser = (Finedata)%MaxStep;	
						  //Micro-Step
	//---------每步小于一步1.8--------------------------------------------------
	//i = Dmxdata*RatioA/RatioB + StartPostion;
    //DmxFinedataUser = (u8)(Dmxdata*RatioA*MaxStep/RatioB) % MaxStep;

    //i = 20*Dmxdata;
    Motor1_postion_control(i);
}

/*****************************************************************************************
*
*				 步进电机 驱动函数 
*                                     
*****************************************************************************************/
void MotorYDriveInTimer(void)
{
    Motor1PointerControl();
    Motor1DynamicPostionGap();
    Motor1PostionControlSpeed(); 
}













/***************************************************************************************************************
*                                             END
***************************************************************************************************************/
