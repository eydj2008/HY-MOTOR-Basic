/* Includes ------------------------------------------------------------------*/
//#include "config.h"
#include "menu.h"


static u16 AutoFuncFlag = 0;
//const u32 DelayTiming[14] = {2530, 3430, 730, 2515, 4765, 2790, 3240, 3530, 1420, 3530,
//                        2030, 3730, 2330, 2130};

//---------------------------------------------------------------------
void Display255(u16 x,u16 y,u8 data)
{	  
    u8 Date_buf[5];
	  u8 bak;
			bak = data;
			Date_buf[0] = (u8)(bak/100+'0');	
  			bak = bak%100;
  			Date_buf[1] = (u8)(bak/10+'0');
  			Date_buf[2] = (u8)(bak%10+'0');				
  			Date_buf[3]=NULL;
  			GUI_Text(x,y,(u8*)Date_buf,0xf800,0xffff);
}

//---------------------------------------------------------------------
void EnterSTOPMode_EXTI(void)
{
  //* Nothing to execute: return 
  return;
}

//---------------------------------------------------------------------
void EnterSTOPMode_RTCAlarm(void)
{
  //* Nothing to execute: return 
  return;
}

//---------------------------------------------------------------------
void EnterSTANDBYMode_WAKEUP(void)
{
  //* Nothing to execute: return 
  return;
}

//---------------------------------------------------------------------
void EnterSTANDBYMode_RTCAlarm(void)
{
  //* Nothing to execute: return 
  return;
}

//---------------------------------------------------------------------
void Time_Adjust(void)
{
  //* Nothing to execute: return 
  return;
}
/*******************************************************************************
* Function Name  : Time_Show
* Description    : Shows the current time (HH:MM:SS) on the Hyperterminal.
* Input          : None
* Output         : None
* Return         : None
******************************************************************************/
void Time_ShowFunc(void)
{
  //printf("\n\r");

  /* Infinite loop */
 // while (1)
  {
    //TimeDisplay = 1;
    /* If 1s has paased */
    //if (TimeDisplay == 1)
    {
      /* Display current time */
      //Time_Display(RTC_GetCounter());
	 // Time_Display(a,b,c);
	  
     // TimeDisplay = 0;
    }
  }
}

void Time_AdjustFunc(void)		//?
{
  u32 index = 0, KeyState = 0,RTCCounter = 0;

  RTCCounter = RTC_GetCounter();

  while(index < 14)
  {
      KeyState = ReadKey();  //DelayJoyStick(DelayTiming[index]);
      if(KeyState == UP)
      {
        //RTCCounter += 3600;
        //RTC_SetCounter(RTCCounter);
      }
      else if (KeyState == DOWN)
      {
        //RTCCounter -= 3600;
        //RTC_SetCounter(RTCCounter);
      }
      else if(KeyState == LEFT)
      {
        //RTCCounter -= 60;
        //RTC_SetCounter(RTCCounter);
        index = 15;
      }
      else if (KeyState == RIGHT)
      {
        //RTCCounter += 60;
        //RTC_SetCounter(RTCCounter);
      }
      else if (KeyState == SEL)
      {
        //RTC_SetCounter(RTCCounter);
        index = 15;
      }
      else if (KeyState == NOKEY)
      {
      }
     // TimeDisplay = 1;
  
    //Time_Display(200,180,RTC_GetCounter());
    GUI_Text(8,100,"SET TIME UP & DOWN / LEFT & RIGHT",Blue,Red);
  }

  LCD_Clear(Black);
  DisplayMenu();
  

  //return;
}

void Time_Show(void)
{
  //* Nothing to execute: return 
  return;
}	   

void Alarm_Adjust(void)
{
  //* Nothing to execute: return 
  return;
}

void Alarm_Show(void)
{
  //* Nothing to execute: return 
  return;
}

void AboutFunc(void)
{
  //* Nothing to execute: return 
  return;
}

void Date_Adjust(void)
{
  //* Nothing to execute: return 
  return;
}

void Date_Show(void)
{
  //* Nothing to execute: return 
  return;
}

void FunnyCircles(void)
{
  //* Nothing to execute: return 
  return;
}

void HelpFunc(void)
{
  //* Nothing to execute: return 
  return;
}

void Mass_Storage_Start(void)
{
  //* Nothing to execute: return 
  return;
}

//--------------------------------------------------------
void PanFunc(void)
{  static u8 PanData=0;
	  u8 index = 0, KeyState = 0;
    GUI_Text(8,100,"     PanFunc OK     ",Red,Blue);

  while(index < 14)
  {
    KeyState = ReadKey();  //DelayJoyStick(DelayTiming[index]);
    
    if(KeyState == UP)
    {
      PanData++; 
    }
    else if (KeyState == DOWN)
    {
      PanData--; 
    }
    else if(KeyState == LEFT)
    {
      index = 15;
    }
    else if (KeyState == RIGHT)
    {
      PanData	   = 255; 
    }
    else if (KeyState == SEL)
    {
      index = 15;
    }
    else if (KeyState == NOKEY)
    {
    }
    
	//TXDData[SendAddress] = PanData;   ////SendAddress = 1	 == TXDData[0];
   MotorXDmxDataControl(PanData,0);
	 Display255(180,20,PanData);
 
  }
	
	  LCD_Clear(Black); //LCD_Clear(White);
    DisplayMenu();
  //* Nothing to execute: return 
  return;
}

//--------------------------------------------------------
void TiltFunc(void)
{
    static u8 PanData=0;
	  u8 index = 0, KeyState = 0;
    GUI_Text(8,100,"    TiltFunc OK     ",Red,Blue);

  while(index < 14)
  {
    KeyState = ReadKey();  //DelayJoyStick(DelayTiming[index]);
    
    if(KeyState == UP)
    {
      PanData++; 
    }
    else if (KeyState == DOWN)
    {
      PanData--; 
    }
    else if(KeyState == LEFT)
    {
      index = 15;
    }
    else if (KeyState == RIGHT)
    {
      PanData	   = 255; 
    }
    else if (KeyState == SEL)
    {
      index = 15;
    }
    else if (KeyState == NOKEY)
    {
    }
    
	//TXDData[SendAddress] = PanData;   ////SendAddress = 1	 == TXDData[0];
   MotorYDmxDataControl(PanData,0);
	 Display255(180,20,PanData);
 
  }
	
	  LCD_Clear(Black); //LCD_Clear(White);
    DisplayMenu();

  //* Nothing to execute: return 
  return;
}

//-------------------------------------------------------
void AutoFunc(void)
{
  u8 index = 0, KeyState = 0;

  while(index < 14)
  {
     KeyState = ReadKey();  //DelayJoyStick(DelayTiming[index]);
     GUI_Text(8,100,"   AutoFunc OK   ",Red,Blue);
     TestMotorFucn();
    
    if (KeyState == RIGHT)
    {
	    AutoFuncFlag = 1; 
    }
	  else if (KeyState == SEL)
    {
	    AutoFuncFlag = 1;	
      index = 15;      
    }
    else if (KeyState == LEFT)
    {
	    index = 15;
	    AutoFuncFlag = 0;
    }
    else if (KeyState == NOKEY)
    {
    }
    
  }
  	LCD_Clear(Black);
    DisplayMenu();
  //* Nothing to execute: return 
  return;
}

u8 CheckAuto(void)
{  
  static u8 k=0;
  if (AutoFuncFlag)  
     k = 1;
  else
     k = 0;
	 return k;
}

//----------------------------------------------------------------------------
void ArmbusFucn(void)
{
  GUI_Text(8,80,"  Welcome To ARMBUS  ",Red,Blue);
  GUI_Text(8,100,"http://www.ArmBus.com",Red,Blue);
  GUI_Text(8,120,"20100622-LAN Sample",Red,Blue);
  //TCPUPD_RESET();		//test
  //* Nothing to execute: return 
  return;
}
/*******************************************************************************
* Function Name  : ProductPres
* Description    : Display the About menu.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ProductPres(void)
{
  static u8 PanData=0;
	  u8 index = 0, KeyState = 0;

  GUI_Text(8,100,"   SendAddress SET  ",Red,Blue);

  while(index < 14)
  {
    KeyState = ReadKey();  //DelayJoyStick(DelayTiming[index]);
    
    if(KeyState == UP)
    {
      PanData++; 
    }
    else if (KeyState == DOWN)
    {
      PanData--; 
    }
    else if(KeyState == LEFT)
    {
      PanData	   = 0; 
      index = 15;
    }
    else if (KeyState == RIGHT)
    {
      PanData	   = 255; 
    }
    else if (KeyState == SEL)
    {
      index = 15;
    }
    else if (KeyState == NOKEY)
    {
    }
	//SendAddress = PanData;   ////SendAddress = 1	 == TXDData[0];
	 //Display255(180,20,SendAddress);
 	//ShowADValue(250,100);	
  }
	
	LCD_Clear(Black); //LCD_Clear(White);
  DisplayMenu();
  //* Nothing to execute: return 
  return;
}

//------------------------------------------------------------------------
void SendFunc()
{	
	  u8 index = 0, KeyState = 0;

   GPIO_SetBits(GPIOB, GPIO_Pin_2);	 //RS485-DIR OUT  TXD
   GUI_Text(8,100,"  DMX SendFunc SET OK  ",Blue,Red);

  while(index < 14)
  {
      KeyState = ReadKey();  //DelayJoyStick(DelayTiming[index]);

    if(KeyState == LEFT)
    {
	index = 15; 
    }
    else if (KeyState == SEL)
    {
	 index = 15;
    }
    else if (KeyState == NOKEY)
    {
    }
	//Display255(180,20,SendAddress);
 	//ShowADValue(250,100);
	GUI_Text(18,180,"DMX512:",0xFF00,0x0880);
	//	  Display_TXDData(18,200,(u8*)TXDData);
		  //Display_RXDData(18,220,(u8*)RXDData);	
  }
}

//------------------------------------------------
void ReceiveFunc()
{	u8 index = 0, KeyState = 0;

   //GPIO_ResetBits(GPIOB, GPIO_Pin_2);	 //RS485-DIR IN	  RXD
   GUI_Text(8,100,"  DMX ReceiveFunc SET OK",Red,Blue);

  while(index < 14)
  {
      KeyState = ReadKey();  //DelayJoyStick(DelayTiming[index]);

    if(KeyState == LEFT)
    {
	index = 15; 
    }
    else if (KeyState == SEL)
    {
	 index = 15;
    }
    else if (KeyState == NOKEY)
    {
    }
	//Display255(180,20,SendAddress);
 	//ShowADValue(250,100);
	      GUI_Text(18,180,"DMX512:",0xFF00,0x0880);
		  //Display_TXDData(18,200,(u8*)TXDData);
		  //Display_RXDData(18,220,(u8*)RXDData);	
  }

}

/****************************************************************************
*
*                         end
*
*****************************************************************************/



