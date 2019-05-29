/**********************************************************************
*
*
*
***********************************************************************/
/************************************************************************
struct sMenuItem STANDBYMenuItems[] = {{"  Exit: Wakeup Pin  ", EnterSTANDBYMode_WAKEUP, IdleFunc},
                                       {"  Exit: RTC Alarm   ", EnterSTANDBYMode_RTCAlarm, IdleFunc},
                                       {"       Return       ", ReturnFunc, IdleFunc}};
*************************************************************************/
	
#include "menu.h"

//u8 PWM0_BIG_DutyCycle = 0;

/* Private typedef -----------------------------------------------------------*/
typedef void (* tMenuFunc)(void);
typedef struct sMenuItem * tMenuItem;
typedef struct sMenu * tMenu;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 MenuItemIndex = 0, nMenuLevel = 0;
u8 ItemNumb[MAX_MENU_LEVELS];
u32 TimingDelay = 0;

tMenuItem psMenuItem, psCurrentMenuItem;
tMenu psPrevMenu[MAX_MENU_LEVELS];
tMenu psCurrentMenu;

struct sMenuItem
{
  u8*  pszTitle;
  tMenuFunc pfMenuFunc;
  tMenuFunc pfUpDownMenuFunc;
  tMenu     psSubMenu;
};

struct sMenu
{
  u8* pszTitle;
  tMenuItem psItems;
  u8 nItems;
};
/*
struct sMenu MainMenu[]={	  
           {"DMX Address"},
		   {"Time and Colok"},
		   {"Tempreture"},
		   {"Motor Control"},
		   {"Lamp ON/OFF"},
		   };
*/

/*------------------------------ Menu level 3 -------------------------------*/

struct sMenuItem STOPMenuItems[] = {{"    Exit: EXTI      ", EnterSTOPMode_EXTI, IdleFunc},
                                    {"  Exit: RTC Alarm   ", EnterSTOPMode_RTCAlarm, IdleFunc},
                                    {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu STOPMenu = {"     STOP Mode      ", STOPMenuItems, countof(STOPMenuItems)};

struct sMenuItem STANDBYMenuItems[] = {{"  Exit: Wakeup Pin  ", EnterSTANDBYMode_WAKEUP, IdleFunc},
                                       {"  Exit: RTC Alarm   ", EnterSTANDBYMode_RTCAlarm, IdleFunc},
                                       {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu STANDBYMenu = {"   STANDBY Mode     ", STANDBYMenuItems, countof(STANDBYMenuItems)};

struct sMenuItem SettingTimeMenuItems[] = { {"       Adjust       ", Time_AdjustFunc, IdleFunc},
                                            {"        Show        ", Time_ShowFunc, IdleFunc},
                                            {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu TimeMenu = {"        Time        ", SettingTimeMenuItems, countof(SettingTimeMenuItems)};

struct sMenuItem SettingDateMenuItems[] = { {"       Adjust       ", Date_Adjust, IdleFunc},
                                            {"        Show        ", Date_Show, IdleFunc},
                                            {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu DateMenu = {"        Date        ", SettingDateMenuItems, countof(SettingDateMenuItems)};

struct sMenuItem SettingAlarmMenuItems[] = { {"       Adjust       ", Alarm_Adjust, IdleFunc},
                                             {"        Show        ", Alarm_Show, IdleFunc},
                                             {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu AlarmMenu = {"        Alarm       ", SettingAlarmMenuItems, countof(SettingAlarmMenuItems)};

   
/*------------------------------ Menu level 2 -------------------------------*/
struct sMenuItem ArmbusMenuItems[] = {{"       About        ", ArmbusFucn, IdleFunc},
                                      {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu ArmbusMenu = {"       Armbus       ", ArmbusMenuItems,countof(ArmbusMenuItems)};

struct sMenuItem AboutMenuItems[] = {{"       About        ", AboutFunc, IdleFunc},
                                     {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu AboutMenu = {"        About       ", AboutMenuItems, countof(AboutMenuItems)};

struct sMenuItem HelpMenuItems[] = {{"       Start        ", HelpFunc, IdleFunc},
                                    {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu HelpMenu = {"        Help        ", HelpMenuItems, countof(HelpMenuItems)};

struct sMenuItem FunnyMenuItems[] = {{"       Start        ", FunnyCircles, IdleFunc},
                                     {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu FunnyMenu = {"        Funny       ", FunnyMenuItems, countof(FunnyMenuItems)};

struct sMenuItem LampONOFFMenuItems[] = {{"       Start        ", Mass_Storage_Start, IdleFunc},
                                         {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu LampONOFFMenu = {"  LampONOFF       ", LampONOFFMenuItems, countof(LampONOFFMenuItems)};

struct sMenuItem MotorMenuItems[] = {{"       PAN          ", PanFunc, IdleFunc},
									 {"       TILT         ", TiltFunc, IdleFunc},
									 {"       Auto         ", AutoFunc, IdleFunc},
                                     {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu MotorMenu =      {"   Motor Control   ", MotorMenuItems, countof(MotorMenuItems)};


struct sMenuItem TempretureMenuItems[] = {{"    SHOW Tempreture ", IdleFunc, IdleFunc, &STOPMenu},
                                        //{"       STANDBY      ", IdleFunc, IdleFunc, &STANDBYMenu},
                                          {"       Return       ", ReturnFunc, IdleFunc}};
struct sMenu TempretureMenu = {"    Tempreture     ", TempretureMenuItems, countof(TempretureMenuItems)};

struct sMenuItem CalendarMenuItems[] = {{"        Time        ", IdleFunc, IdleFunc, &TimeMenu},
                                        {"        Date        ", IdleFunc, IdleFunc, &DateMenu},
                                        {"        Alarm       ", IdleFunc, IdleFunc, &AlarmMenu},
                                        {"        Return      ", ReturnFunc, IdleFunc}};
struct sMenu CalendarMenu = {"       Calendar     ", CalendarMenuItems, countof(CalendarMenuItems)};

struct sMenuItem DMXAddressSETMenuItems[] = {{"       Start        ", ProductPres, IdleFunc},
											 {"       Send         ", SendFunc,    IdleFunc},
											 {"       Receive      ", ReceiveFunc, IdleFunc},
                                             {"       Return       ", ReturnFunc,  IdleFunc}};
struct sMenu DMXAddressSETMenu = {"   DMX Address SET  ", DMXAddressSETMenuItems, countof(DMXAddressSETMenuItems)};

/*------------------------------ Menu level 1 -------------------------------*/
struct sMenuItem MainMenuItems[] = {
  {"     DMX Address    ", IdleFunc, IdleFunc, &DMXAddressSETMenu},
  {"       Calendar     ", IdleFunc, IdleFunc, &CalendarMenu},
  {"      Tempreture    ", IdleFunc, IdleFunc, &TempretureMenu},
  {"     Motor Control  ", IdleFunc, IdleFunc, &MotorMenu},
  {"      Lamp ON/OFF   ", IdleFunc, IdleFunc, &LampONOFFMenu},
  {"    Time and Colok  ", IdleFunc, IdleFunc, &FunnyMenu},
  {"        Help        ", IdleFunc, IdleFunc, &HelpMenu},
  {"      About Us      ", IdleFunc, IdleFunc, &AboutMenu},
  {"  yonyon.taobao.com ", IdleFunc, IdleFunc, &ArmbusMenu}};
struct sMenu MainMenu = {"     Main menu      ", MainMenuItems, countof(MainMenuItems)};

u16 MenuX = 8;	   
u16 MenuY = 8;
/**********************************************************************
*
*			void Menu(void)
*
***********************************************************************/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Menu_Init
* Description    : Initializes the navigation menu.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Menu_Init(void)
{
  psCurrentMenu = &MainMenu;
  psPrevMenu[nMenuLevel] = psCurrentMenu;
  psMenuItem = MainMenuItems;
}

/*******************************************************************************
* Function Name  : DisplayMenu
* Description    : Displays the current menu.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DisplayMenu(void)
{
  u16 MenuY = 8, index = 0;
  tMenuItem psMenuItem2;

  /* Clear the LCD Screen */
  //LCD_Clear(White);
  LCD_Clear(Black);	
  GUI_Text(MenuX,MenuY,psCurrentMenu->pszTitle,White,Blue);
  MenuY += 16;
  //LCD_DisplayStringLine(Line, psCurrentMenu->pszTitle);
 // Line += 24;

  while(!(index >= (psCurrentMenu->nItems)))
  {
    psMenuItem2 = &(psCurrentMenu->psItems[index]);
    //LCD_DisplayStringLine(Line, psMenuItem2->pszTitle);
	  GUI_Text(MenuX,MenuY,psMenuItem2->pszTitle,Blue,White);
    index++;
	  MenuY += 16;
    //Line += 24;
  }

  /* Get the current menu */
  psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]);
  GUI_Text(MenuX,(MenuItemIndex + 1) * 16+8,psMenuItem->pszTitle,White,Magenta);
  //LCD_DisplayStringLine(((MenuItemIndex + 1) * 24), psMenuItem->pszTitle);
}
/*******************************************************************************
* Function Name  : SelFunc
* Description    : This function is executed when "SEL" push-buttton is pressed.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SelFunc(void)
{

  psCurrentMenuItem = psMenuItem;

  if(psMenuItem->psSubMenu != '\0')
  {
    /* Update the current Item by the submenu */
    MenuItemIndex = 0;
    psCurrentMenu = psMenuItem->psSubMenu;
    psMenuItem = &(psCurrentMenu->psItems)[MenuItemIndex];
    DisplayMenu();
    nMenuLevel++;
    psPrevMenu[nMenuLevel] = psCurrentMenu;
  } 
  psCurrentMenuItem->pfMenuFunc();
  
}

/*******************************************************************************
* Function Name  : UpFunc
* Description    : This function is executed when any of "UP" push-butttons
*                  is pressed.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UpFunc(void)
{
  /* Set the Back Color */
 // LCD_SetBackColor(White);
  /* Set the Text Color */
 // LCD_SetTextColor(Blue);
  psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
  GUI_Text(MenuX,(MenuItemIndex + 1) * 16+8,psMenuItem->pszTitle,Blue,White);
 // LCD_DisplayStringLine(((MenuItemIndex + 1) * 24), psMenuItem->pszTitle);

  if(MenuItemIndex > 0)
  {
    MenuItemIndex--;
  }
  else
  {
    MenuItemIndex = psCurrentMenu->nItems - 1;
  }
  /* Set the Back Color */
  //LCD_SetBackColor(Green);
  /* Set the Text Color */
  //LCD_SetTextColor(White);
  psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
  GUI_Text(MenuX,(MenuItemIndex + 1) * 16+8,psMenuItem->pszTitle,White,Magenta);
  //LCD_DisplayStringLine(((MenuItemIndex + 1) * 24), psMenuItem->pszTitle);
  ItemNumb[nMenuLevel] = MenuItemIndex;
}

/*******************************************************************************
* Function Name  : DownFunc
* Description    : This function is executed when any of "Down" push-butttons
*                  is pressed.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DownFunc(void)
{
  /* Set the Back Color */
  //LCD_SetBackColor(White);
  /* Set the Text Color */
  //LCD_SetTextColor(Blue);
  psMenuItem = &psCurrentMenu->psItems[MenuItemIndex];
  GUI_Text(MenuX,(MenuItemIndex + 1) * 16+8,psMenuItem->pszTitle,Blue,White);
  //LCD_DisplayStringLine(((MenuItemIndex + 1) * 24), psMenuItem->pszTitle);
      
  /* Test on the MenuItemIndex value before incrementing it */
  if(MenuItemIndex >= ((psCurrentMenu->nItems)-1))
  {
    MenuItemIndex = 0;
  }
  else
  {
    MenuItemIndex++;
  }
  /* Set the Back Color */
  //LCD_SetBackColor(Green);
  /* Set the Text Color */
  //LCD_SetTextColor(White);
  /* Get the current menu */
  psMenuItem = &(psCurrentMenu->psItems[MenuItemIndex]);
  GUI_Text(MenuX,(MenuItemIndex + 1) * 16+8,psMenuItem->pszTitle,White,Magenta);
  //LCD_DisplayStringLine(((MenuItemIndex + 1) * 24), psMenuItem->pszTitle);
  ItemNumb[nMenuLevel] = MenuItemIndex;
}

/*******************************************************************************
* Function Name  : ReturnFunc
* Description    : This function is executed when the "RETURN" menu is selected.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ReturnFunc(void)
{
  psMenuItem->pfUpDownMenuFunc();

  if(nMenuLevel == 0)
  {
    nMenuLevel++;
  }

  psCurrentMenu = psPrevMenu[nMenuLevel-1];
  psMenuItem = &psCurrentMenu->psItems[0];
  ItemNumb[nMenuLevel] = 0;
  MenuItemIndex = 0;
  nMenuLevel--;
  if(nMenuLevel != 0)
  {
    DisplayMenu();
  }
  else
  {
    DisplayMenu();
    //ShowMenuIcons();
  }
}

/*******************************************************************************
* Function Name  : ReadKey
* Description    : Reads key from demoboard.
*					typedef enum
*					{ Bit_RESET = 0,
*					  Bit_SET
*					}BitAction;
* Input          : None
* Output         : None
* Return         : Return RIGHT, LEFT, SEL, UP, DOWN or NOKEY
*******************************************************************************/
u8 ReadKey(void)
{	
  static u16 CounterRight = 0;
	static u16 CounterLeft = 0;
	static u16 CounterUp = 0;
	static u16 CounterDown = 0;
    //static u16 CounterSel = 0;

	static u16 LeftFastFlag = 0;
	static u16 RightFastFlag = 0;
	static u16 UpFastFlag = 0;
	static u16 DownFastFlag = 0;
	//static u16 SelFastFlag = 0;

  /* "ESC" key is pressed */
   CounterLeft++;
  if(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0))		//PIN4==0
  {
   	if (CounterLeft==1)
    	return LEFT;
	if (LeftFastFlag)
	if (CounterLeft>28) CounterLeft = 0;

	if (CounterLeft>300) LeftFastFlag = 1;
  }
  else
  {
	  CounterLeft = 0;
	  LeftFastFlag = 0;
  }

    /* "OK" key is pressed */
   CounterRight++;
  if(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1))		//PIN4==0
  {
   	if (CounterRight==1)
    	return RIGHT;
	if (RightFastFlag)
	if (CounterRight>28) CounterRight = 0;

	if (CounterRight>300) RightFastFlag = 1;
  }
  else
  {
	  CounterRight = 0;
	  RightFastFlag = 0;
  }
  //------------------------------------------------------------------------------------
  /* "up" key is pressed */
   CounterUp++;
  if(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2))		//PIN4==0
  {
   	if (CounterUp==1)
    	return UP;
	if (UpFastFlag)
	if (CounterUp>28) CounterUp = 0;

	if (CounterUp>300) UpFastFlag = 1;
  }
  else
  {
	CounterUp = 0;
	UpFastFlag = 0;
  }
   //----------------------------------------------------------
  /* "down" key is pressed */ 
   	CounterDown++;
  if(!GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3))		//PIN1==0
  {
   	if (CounterDown==1)
    	 return DOWN;
	  if (DownFastFlag)
	  if (CounterDown>28) CounterDown = 0;

	  if (CounterDown>300) DownFastFlag = 1;
  }
  else
  {
	  CounterDown = 0;
	  DownFastFlag = 0;
  }

  //-------------------------------------------------------------------------------------
  /* "sel" key is pressed */
//    	CounterSel++;
//   if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0))		//PIN1==0
//   {
//    	if (CounterSel==1)
//     	return SEL;
// 	if (SelFastFlag)
// 	if (CounterSel>28) CounterSel = 0;

// 	if (CounterSel>300) SelFastFlag = 1;
//   }
//   else
//   {
// 	CounterSel = 0;
// 	SelFastFlag = 0;
//   }
  
if ((GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0))&&
	  (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1))&&
	  (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2))&&
	  (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)))
   
     return NOKEY;
   
}

/**********************************************************************
*
*			void KeyMenu(void)
*
***********************************************************************/
void KeyMenu(void)
{
	switch (ReadKey())
	{
		case LEFT :
        ReturnFunc();   
			break;
		case RIGHT :
        SelFunc();
			break;
		case UP : 
        UpFunc();
			
			//PWM0_BIG_DutyCycle++;
			break;
		case DOWN : 
        DownFunc();
        //PWM0_BIG_DutyCycle--;
			break;
		case SEL : 
        SelFunc();
			break;
		default : 
			break;
	}
}
/*******************************************************************************
* Function Name  : DelayJoyStick
* Description    : Inserts a delay time while no joystick RIGHT, LEFT and SEL 
                   pushbuttons are pressed.
* Input          : nCount: specifies the delay time length (time base 10 ms).
* Output         : None
* Return         : Pressed Key.  This value can be: NOKEY, RIGHT, LEFT or SEL.
*******************************************************************************/
u16 DelayJoyStick(u16 nTime)
{
  u16 keystate = 0;

  TimingDelay = nTime;
 
  while((TimingDelay != 0) && (keystate != RIGHT) && (keystate != LEFT) && (keystate != SEL))
  {
    keystate = ReadKey();
  } 
  
  return keystate;
}

/*******************************************************************************
* Function Name  : IdleFunc
* Description    : Idle function.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void IdleFunc(void)
{
  /* Nothing to execute: return */
  return;
}

/**********************************************************************
*
*			END Menu
*
***********************************************************************/

