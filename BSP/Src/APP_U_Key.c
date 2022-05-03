/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------以下是模块的修改记录区---------------------------------                                   *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***********************************************
 * 内容：按键
 * 日期：2016/9/29
 * 作者：陈勇
 * 版本号：V1.0（初版）
 ***********************************************
 * 修改内容：
 * 修改日期：
 * 修改作者：
 * 版本号：
 ***********************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------以下是模块的使用说明区---------------------------------                                   *
*                                                                                                                                           *
********************************************************************************************************************************************/
/*                                           模块使用说明：
 *
 * 1."Key_CurrentTime_ms"、"Key_TimingQuery_30ms"、"Key_TimingQuery_3s"三个函数需要用户添加定时代码，定时要采用扫描方式，必须以毫秒为单位。
 * 2."Key_Check"函数需要用户添加按键扫描代码。
 * 3."Key_Task"函数需要用户添加按键任务代码。
 * 4."APP_Key_Init"函数需要用户添加按键相关IO口的配置代码，如果在扫描按键过程中IO口要频繁地改变方向的话（如：塔型按键扫描），就要把IO口配置写在"Key_Check"函数里，不需要该函数。
 *
 */
#include "BSP.h"
#include "APP_U_Key.h"
#include "APP_S_Key.h"

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------以下是模块的对接函数区---------------------------------                                    *
*                                                                                                                                           *
********************************************************************************************************************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------以下是模块的内部函数申明区---------------------------------                                *
*                                                                                                                                           *
********************************************************************************************************************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------以下是模块的变量申明和宏定义区---------------------------------                            *
*                                                                                                                                           *
********************************************************************************************************************************************/

/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------以下是模块的系统函数代码区---------------------------------                               *
*                                                                                                                                           *
********************************************************************************************************************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------以下是模块的内部函数代码区---------------------------------                                *
*                                                                                                                                           *
********************************************************************************************************************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------以下是模块的用户函数代码区---------------------------------                                *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* 函数名：  Key_CurrentTime_ms
* 功能描述：获取当前时间，用于定时
* 入口参数：无
* 出口参数：16位数的当前时间，单位为毫秒
* 注意事项：无
* 修改记录：无
*           2016/9/29 BY:陈勇
***************************************************************************/
u16 Key_CurrentTime_ms(void)
{
    return API_SystemClock_CurrentTime_ms();
}


/***************************************************************************
* 函数名：  Key_TimingQuery_30ms
* 功能描述：查询定时30毫秒
* 入口参数：StartingTime_ms：起始时间（毫秒）
* 出口参数：TimeOut：定时时间已到
*           NoTimeOut：定时时间还没到
* 注意事项：无
* 修改记录：无
*           2016/9/29 BY:陈勇
***************************************************************************/
u8 Key_TimingQuery_30ms(u16 StartingTime_ms)
{
    return API_SystemClock_TimingQuery_ms(StartingTime_ms,30);
}


/***************************************************************************
* 函数名：  Key_TimingQuery_3s
* 功能描述：查询定时3秒
* 入口参数：StartingTime_ms：起始时间（毫秒）
* 出口参数：TimeOut：定时时间已到
*           NoTimeOut：定时时间还没到
* 注意事项：为了减少误差，入口参数提供的起始时间是以毫秒为单位。
* 修改记录：无
*           2016/9/29 BY:陈勇
***************************************************************************/
u8 Key_TimingQuery_3s(u16 StartingTime_ms)
{
    return API_SystemClock_TimingQuery_ms(StartingTime_ms,2000);  //常按3秒太长，这里改成2秒
}


/***************************************************************************
* 函数名：  Key_Check
* 功能描述：按键检测
* 入口参数：*PressDownKey：存放当前被按下的按键名
* 出口参数：PressDown：有按键被按下
*           NoPressDown：没有按键被按下
* 注意事项：该函数需要添加按键的扫描代码（如：IO口按键扫描、矩阵按键扫描、
*           塔型按键扫描等），如果扫描到有按键被按下，就要在"PressDownKey"
*           的变量地址里放入当前被按下的按键名并返回"PressDown"，如果没有扫
*           描到按键被按下就要返回"NoPressDown"。
* 修改记录：无
*           2016/9/29 BY:陈勇
***************************************************************************/
u8 Key_Check(u8 *PressDownKey)
{
    if(HC165.Key_Enter == 0)  //确认按键
    {
        *PressDownKey = ENTER;  //当前被按下的按键
        return PressDown;  //返回有按键被按下
    }

    if(HC165.Key_Menu == 0)  //菜单按键
    {
        *PressDownKey = MENU;  //当前被按下的按键
        return PressDown;  //返回有按键被按下
    }
    
    if(HC165.Key_Up == 0)  //上调
    {
        *PressDownKey = SWUP;  //当前被按下的按键
        return PressDown;  //返回有按键被按下
    }

    if(HC165.Key_Down == 0)  //下调
    {
        *PressDownKey = SWDOWN;  //当前被按下的按键
        return PressDown;  //返回有按键被按下
    }
		
    return NoPressDown;  //返回没有按键被按下
}


/***************************************************************************
* 函数名：  Key_Task
* 功能描述：执行按键的任务
* 入口参数：PressDownKey：当前被按下的按键名
*           KeyMode：SharedTask：共同任务，点动和常按相同的那部分任务（如：按键声）
*                    PressDownOnce：点动（按下后3秒内松开）
*                    PressDownStabilize：常按（按下超过3秒后才松开）
* 出口参数：HangInTheAir：按键任务未执行完成
*           HasBeenCompleted：按键任务已执行完成
* 注意事项：1."共同任务"用于执行"点动"和"常按"相同的那部分任务（如：按键声），
*             但也不能盲目的写在一起，因为三者都有区别，应视具体情况来整合，
*             "共同任务"是按键被按下后还没放开就动作，而"点动"和"常按"则是按
*             鍵被按下后不会立刻动作，要等到按键放开后才动作，所以如果只有
*             "点动"功能的话建议将代码全部写在"共同任务"中，这样一按下就动作
*             比较符合人们的操作习惯。
*           2.按下按键一次则一种模式只会进入该函数一次，所以像按键声这类需要
*             延时的任务就不能指望在该函数里完成，最好是给延时任务设置一个标
*             志位，在该函数里使能标志位，任务在其他函数里解决，非延时任务是
*             可以在该函数里完成后再离开。
*           3.按键按下一次会进入该函数两次，第一次是"共同任务"，第二次是"点动"
*             或者"常按"，如果在"共同任务"中已将该按键的任务执行完成就要返回
*             已完成"HasBeenCompleted"，如果在"共同任务"中执行后还要在"点动"或
*             "常按"里继续执行，这时"共同任务"就要返回未完成"HangInTheAir"，
*             比如说"共同任务"是按键声，"点动"或"常按"是按键任务，这样在"共同
*             任务"里要返回未完成"HangInTheAir"，"点动"或"常按"都要返回已完成
*             "HasBeenCompleted"。
* 修改记录：无
*           2016/9/29 BY:陈勇
***************************************************************************/
u8 Key_Task(u8 PressDownKey,u8 KeyMode)
{
    switch(PressDownKey)  //当前被按下的按键
    {                  
        case SWUP:  //数值加、自检
             {
                 switch(KeyMode)  //按键按下的方式
                 {
                     case SharedTask:  //共同任务
                          {
                              
                              
                              return HangInTheAir;  //返回未执行完成
                          }
//                          break;
                          
                     case PressDownOnce:  //点动
                          {
                              if((g_showWindowType == SHOW_FUNCTIONSET_WINDOW)&&(FunctionSet_Reverse_DisplayFlag == 1))  //设置地址
                              {
                                  if(Temporary_Displag.Add < ADD_UPPER_LIMIT)
                                  {
                                      Temporary_Displag.Add ++;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Add = ADD_LOWER_LIMIT;
                                  }
                                  FunSet_Flag_2 = Yes;
                              }
                              else if((g_showWindowType == SHOW_FUNCTIONSET_WINDOW)&&(FunctionSet_Reverse_DisplayFlag == 3))  //设置语音提示
                              {
                                  if(Temporary_Displag.YuYin == No)
                                  {
                                      Temporary_Displag.YuYin = Yes;
                                  }
                                  else
                                  {
                                      Temporary_Displag.YuYin = No;
                                  }
                                  FunSet_Flag_2 = Yes;
                              }   

                              if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 1))  //设置温度上限
                              {
                                  if(Temporary_Displag.Temp_SX < TEMP_UPPER_LIMIT_H)
                                  {
                                      Temporary_Displag.Temp_SX ++;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Temp_SX = TEMP_UPPER_LIMIT_L;
                                  }
                                  TempHumiSet_Flag_2 = Yes;
                              }
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 2))  //设置温度下限
                              {
                                  if(Temporary_Displag.Temp_XX < TEMP_LOWER_LIMIT_H)
                                  {
                                      Temporary_Displag.Temp_XX ++;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Temp_XX = TEMP_LOWER_LIMIT_L;
                                  }
                                  TempHumiSet_Flag_2 = Yes;                              
                              }
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 3))  //设置温度回差
                              {
                                  if(Temporary_Displag.Temp_HC < TEMP_HUICHA_UPPER_LIMIT)
                                  {
                                      Temporary_Displag.Temp_HC ++;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Temp_HC = TEMP_HUICHA_LOWER_LIMIT;
                                  }
                                  TempHumiSet_Flag_2 = Yes;                               
                              }
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 4))  //设置湿度上限
                              {
                                  if(Temporary_Displag.Humi_SX < HUMI_YUZHI_UPPER_LIMIT)
                                  {
                                      Temporary_Displag.Humi_SX ++;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Humi_SX = HUMI_YUZHI_LOWER_LIMIT;
                                  }
                                  TempHumiSet_Flag_2 = Yes;                               
                              }
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 5))  //设置湿度下限
                              {
                                  if(Temporary_Displag.Humi_HC < HUMI_HUICHA_UPPER_LIMIT)
                                  {
                                      Temporary_Displag.Humi_HC ++;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Humi_HC = HUMI_HUICHA_LOWER_LIMIT;
                                  }
                                  TempHumiSet_Flag_2 = Yes;                               
                              }  
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 1))  //设置接头温度报警下限
                              {
                                  if(Temporary_Displag.Connect_Temp < TEMP_ALARM_UPPER_LIMIT)
                                  {
                                      Temporary_Displag.Connect_Temp ++;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Connect_Temp = TEMP_ALARM_UPPER_LIMIT;
                                  }
                                  WirelessSet_Flag_2 = Yes;                               
                              } 
                              
                              if(g_showWindowType == SHOW_UID_WINDOW)  //设置UID数值
                              {
                                  if(UID_Arr[WirelessSet_Bit - 1] < 10)
                                  {
                                      UID_Arr[WirelessSet_Bit - 1] ++;
                                  }
                                  else
                                  {
                                      UID_Arr[WirelessSet_Bit - 1] = 0;
                                  }
                              }                              
                              
                              LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              
                              LED_ZM_Flag = Yes;  //LCD背光
                              LED_ZM_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                              
                            
                              return HasBeenCompleted;  //返回已执行完成
                          }
//                          break;
                          
                     case PressDownStabilize:  //常按（按住3秒或以上）
                          {
                              #if(Manual_Self_Test_Function == NEED)
                              if(Manual_self_check_Flag == No)
                              {
                                  Manual_self_check_Flag = Yes;
                                  Manual_self_check_Flag_s = API_SystemClock_CurrentTime_s(); 
                              }
                              else
                              {
                                  Manual_self_check_Flag = No;
                                  Export._ZJ_QD = OFF;
                              }
                              s_initGroupShowWindowFlag = Yes;
                              #endif
                              
                              return HasBeenCompleted;  //返回已执行完成
                          }
//                          break;
                          
                     default: break;
                 }
             }
             break;
             
        case SWDOWN:  //数值减
             {
                 switch(KeyMode)  //按键按下的方式
                 {
                     case SharedTask:  //共同任务
                          {
                              
                              
                              return HangInTheAir;  //返回未执行完成
                          }
//                          break;
                          
                     case PressDownOnce:  //点动
                          {
                              if((g_showWindowType == SHOW_FUNCTIONSET_WINDOW)&&(FunctionSet_Reverse_DisplayFlag == 1))  //设置地址
                              {
                                  if(Temporary_Displag.Add > ADD_LOWER_LIMIT)
                                  {
                                      Temporary_Displag.Add --;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Add = ADD_UPPER_LIMIT;
                                  }
                                  FunSet_Flag_2 = Yes;
                              } 
                              else if((g_showWindowType == SHOW_FUNCTIONSET_WINDOW)&&(FunctionSet_Reverse_DisplayFlag == 3))  //设置语音提示
                              {
                                  if(Temporary_Displag.YuYin == No)
                                  {
                                      Temporary_Displag.YuYin = Yes;
                                  }
                                  else
                                  {
                                      Temporary_Displag.YuYin = No;
                                  }
                                  FunSet_Flag_2 = Yes;
                              }  

                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 1))  //设置温度上限
                              {
                                  if(Temporary_Displag.Temp_SX > TEMP_UPPER_LIMIT_L)
                                  {
                                      Temporary_Displag.Temp_SX --;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Temp_SX = TEMP_UPPER_LIMIT_H;
                                  }
                                  TempHumiSet_Flag_2 = Yes;
                              }
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 2))  //设置温度下限
                              {
                                  if(Temporary_Displag.Temp_XX > TEMP_LOWER_LIMIT_L)
                                  {
                                      Temporary_Displag.Temp_XX --;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Temp_XX = TEMP_LOWER_LIMIT_H;
                                  }
                                  TempHumiSet_Flag_2 = Yes;                              
                              }
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 3))  //设置温度回差
                              {
                                  if(Temporary_Displag.Temp_HC > TEMP_HUICHA_LOWER_LIMIT)
                                  {
                                      Temporary_Displag.Temp_HC --;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Temp_HC = TEMP_HUICHA_UPPER_LIMIT;
                                  }
                                  TempHumiSet_Flag_2 = Yes;                               
                              }
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 4))  //设置湿度上限
                              {
                                  if(Temporary_Displag.Humi_SX > HUMI_YUZHI_LOWER_LIMIT)
                                  {
                                      Temporary_Displag.Humi_SX --;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Humi_SX = HUMI_YUZHI_UPPER_LIMIT;
                                  }
                                  TempHumiSet_Flag_2 = Yes;                               
                              }
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 5))  //设置湿度下限
                              {
                                  if(Temporary_Displag.Humi_HC > HUMI_HUICHA_LOWER_LIMIT)
                                  {
                                      Temporary_Displag.Humi_HC --;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Humi_HC = HUMI_HUICHA_UPPER_LIMIT;
                                  }
                                  TempHumiSet_Flag_2 = Yes;                               
                              } 
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 1))  //设置接头温度报警下限
                              {
                                  if(Temporary_Displag.Connect_Temp > TEMP_ALARM_LOWER_LIMIT)
                                  {
                                      Temporary_Displag.Connect_Temp --;
                                  }
                                  else
                                  {
                                      Temporary_Displag.Connect_Temp = TEMP_ALARM_LOWER_LIMIT;
                                  }
                                  WirelessSet_Flag_2 = Yes;                               
                              }
                              else if(g_showWindowType == SHOW_UID_WINDOW)  //设置UID数值
                              {
                                  if(UID_Arr[WirelessSet_Bit - 1] > 0)
                                  {
                                      UID_Arr[WirelessSet_Bit - 1] --;
                                  }
                                  else
                                  {
                                      UID_Arr[WirelessSet_Bit - 1] = 10;
                                  }
                              }                                 
                              else if(g_showWindowType == SHOW_GROUPWINDOW)  //界面切换
                              {
                                  g_showWindowType = SHOW_WIRELESSTEMP;
                                  s_initGroupShowWirelessFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //清屏     
                                  Switch_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                                
                              }
                              else if(g_showWindowType == SHOW_WIRELESSTEMP)  //界面切换
                              {
                                  g_showWindowType = SHOW_GROUPWINDOW;
                                  s_initGroupShowWindowFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //清屏  
                                  Switch_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                                   
                              }  
                              
                              LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              
                              LED_ZM_Flag = Yes;
                              LED_ZM_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                              
                              
                              return HasBeenCompleted;  //返回已执行完成
                          }
//                          break;
                          
                     case PressDownStabilize:  //常按（按住3秒或以上）
                          {
                              
                              return HasBeenCompleted;  //返回已执行完成
                          }
//                          break;
                          
                     default: break;
                 }
             }
             break;
             
        case ENTER:  //上下调切换按键、消除断线故障
             {
                 switch(KeyMode)  //按键按下的方式
                 {
                     case SharedTask:  //共同任务
                          {
                              
                              
                              return HangInTheAir;  //返回未执行完成
                          }
//                          break;
                          
                     case PressDownOnce:  //点动
                          {                        
															if(g_showWindowType == SHOW_MENUWINDOW)  //菜单界面
                              {
                                  if(Menu_Reverse_DisplayFlag < 4)
                                  {
                                      Menu_Reverse_DisplayFlag ++;
                                      ShowMenuFlag = Yes;
                                  }
                                  else
                                  {
                                      Menu_Reverse_DisplayFlag = 1;
                                      ShowMenuFlag = Yes;                                  
                                  }
                              }
                              
                              if((g_showWindowType == SHOW_GROUPWINDOW)||(g_showWindowType == SHOW_WIRELESSTEMP))  //消除断线故障
                              {
                                  JRQ1_Broken_Line_Flag = No;
                                  JRQ2_Broken_Line_Flag = No;
                                  FJ_Broken_Line_Flag = No;
                              }
                              
															if(g_showWindowType == SHOW_FUNCTIONSET_WINDOW)  //功能设置界面
                              {
                                  if(FunctionSet_Reverse_DisplayFlag < 5)
                                  {
                                      FunctionSet_Reverse_DisplayFlag ++;
                                      FunSet_Flag_2 = Yes;
                                  }
                                  else
                                  {
                                      FunctionSet_Reverse_DisplayFlag = 1;
                                      FunSet_Flag_2 = Yes;                                  
                                  }
                              } 

															if(g_showWindowType == SHOW_TEMPHUMISET_WINDOW)  //温湿度设置界面
                              {
                                  if(TempHumiSet_Reverse_DisplayFlag < 7)
                                  {
                                      TempHumiSet_Reverse_DisplayFlag ++;
                                      TempHumiSet_Flag_2 = Yes;
                                  }
                                  else
                                  {
                                      TempHumiSet_Reverse_DisplayFlag = 1;
                                      TempHumiSet_Flag_2 = Yes;                                  
                                  }
                              } 
                              
															if(g_showWindowType == SHOW_WIRELESSSET_WINDOW)  //无线测温设置界面
                              {
                                  if(Wireless_Next_Page == 0)  //第一页切换
                                  {
                                      if((WirelessSet_Reverse_DisplayFlag < 10)&&(Wireless_Next_Page == 0))
                                      {
                                          WirelessSet_Reverse_DisplayFlag ++;
                                          WirelessSet_Flag_2 = Yes;
                                      }
                                      else
                                      {
                                          WirelessSet_Reverse_DisplayFlag = 1;
                                          WirelessSet_Flag_2 = Yes;                                  
                                      }                                  
                                  }
                                  else  //第二页切换
                                  {
                                      if((WirelessSet_Reverse_DisplayFlag < 6)&&(Wireless_Next_Page == 1))
                                      {
                                          WirelessSet_Reverse_DisplayFlag ++;
                                          WirelessSet_Flag_2 = Yes;
                                      }
                                      else
                                      {
                                          WirelessSet_Reverse_DisplayFlag = 1;
                                          WirelessSet_Flag_2 = Yes;                                  
                                      }                                   
                                  }                                                                
                              }                               

                              if(g_showWindowType == SHOW_UID_WINDOW)  //无线测温设置UID界面
                              {
                                  if(WirelessSet_Bit < 5)
                                  {
                                      WirelessSet_Bit ++;
                                  }
                                  else
                                  {
                                      WirelessSet_Bit = 0;
                                  }
                              }
                              
                              
                              LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              
                              LED_ZM_Flag = Yes;
                              LED_ZM_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                              
                              
                              return HasBeenCompleted;  //返回已执行完成
                          }
//                          break;
                          
                     case PressDownStabilize:  //常按（按住3秒或以上）
                          {
                              #if(Manual_Mode_FUNCTION == NEED)
                              if(Manual_Status_Flag == Yes)  //手动
                              {
                                  Manual_Status_Flag = No;
                                  s_initGroupShowWindowFlag = Yes;
                              }
                              else
                              {
                                  Manual_Status_Flag = Yes;
                                  JRQ1_Broken_Line_Flag = No;  //清除断线标志位
                                  JRQ2_Broken_Line_Flag = No;
                                  FJ_Broken_Line_Flag = No;
                                  s_initGroupShowWindowFlag = Yes;
                              }
                              #endif

                              LED_ZM_Flag = Yes;
                              LED_ZM_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              
                              return HasBeenCompleted;  //返回已执行完成
                          }
//                          break;
                          
                     default: break;
                 }
             }
             break;
             
        case MENU:  //菜单、确认保存按键
             {
                 switch(KeyMode)  //按键按下的方式
                 {
                     case SharedTask:  //共同任务
                          {
                              
                              
                              return HangInTheAir;  //返回未执行完成
                          }
//                          break;
                          
                     case PressDownOnce:  //点动
                          {
														  if((g_showWindowType == SHOW_GROUPWINDOW)||(g_showWindowType == SHOW_WIRELESSTEMP))  //进入菜单界面
                              {
                                  g_showWindowType = SHOW_MENUWINDOW;
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //清屏
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }                              
                              else if((g_showWindowType == SHOW_MENUWINDOW)&&(Menu_Reverse_DisplayFlag == 1))  //进入功能设置界面
                              {
                                  Menu_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_FUNCTIONSET_WINDOW;
                                  FunctionSetFlag = Yes;
                                
                                  Temporary_Displag.Add = EEPROM.TheMachineAddress;  //变量赋值
                                  Temporary_Displag.YuYin = EEPROM.Voice_Prompt_Flag;
                                
                                  display_color(BACKGROUND_COLOR);  //清屏
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }
															else if((g_showWindowType == SHOW_MENUWINDOW)&&(Menu_Reverse_DisplayFlag == 2))  //进入温湿度设置界面
                              {
                                  Menu_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_TEMPHUMISET_WINDOW;
                                  TempHumiSetFlag = Yes;
                                
                                  Temporary_Displag.Humi_SX = EEPROM.Humidity_YuZhi;
                                  Temporary_Displag.Humi_HC = EEPROM.Humidity_HuiCha;
                                  Temporary_Displag.Temp_SX = EEPROM.Temp_Upper_Limit;
                                  Temporary_Displag.Temp_XX = EEPROM.Temp_Lower_Limit;
                                  Temporary_Displag.Temp_HC = EEPROM.Temp_HuiCha;
                                
                                  display_color(BACKGROUND_COLOR);  //清屏 
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              } 
															else if((g_showWindowType == SHOW_MENUWINDOW)&&(Menu_Reverse_DisplayFlag == 3))  //进入无线测温设置界面
                              {
                                  Menu_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_WIRELESSSET_WINDOW;
                                  WirelessSetFlag = Yes;
                                
                                  Temporary_Displag.Connect_Temp = EEPROM.Connect_Temp_Alarm;
                                  Temporary_UID[0] = Wireless_Sensor[0].UID;  //赋值
                                  Temporary_UID[1] = Wireless_Sensor[1].UID;
                                  Temporary_UID[2] = Wireless_Sensor[2].UID;
                                  Temporary_UID[3] = Wireless_Sensor[3].UID;
                                  Temporary_UID[4] = Wireless_Sensor[4].UID;
                                  Temporary_UID[5] = Wireless_Sensor[5].UID;
                                  Temporary_UID[6] = Wireless_Sensor[6].UID; 
                                  Temporary_UID[7] = Wireless_Sensor[7].UID;
                                  Temporary_UID[8] = Wireless_Sensor[8].UID;
                                  Temporary_Displag.Connect_Temp = EEPROM.Connect_Temp_Alarm;
                                
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  display_color(BACKGROUND_COLOR);  //清屏 
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }                                                            
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(Wireless_Next_Page == 0)&&
                                      ((WirelessSet_Reverse_DisplayFlag == 2)  //0
                                      ||(WirelessSet_Reverse_DisplayFlag == 3)  //1
                                      ||(WirelessSet_Reverse_DisplayFlag == 4)  //2
                                      ||(WirelessSet_Reverse_DisplayFlag == 5)
                                      ||(WirelessSet_Reverse_DisplayFlag == 6)
                                      ||(WirelessSet_Reverse_DisplayFlag == 7)))  //进入UID设置界面(第一页)
                              {
                                  Temporary_UID[WirelessSet_Reverse_DisplayFlag - 2] = Wireless_Sensor[WirelessSet_Reverse_DisplayFlag - 2].UID;
                                  memset(UID_Arr,0,5);
                                  UID_Arr[4] = Temporary_UID[WirelessSet_Reverse_DisplayFlag - 2]/10000;
                                  UID_Arr[3] = Temporary_UID[WirelessSet_Reverse_DisplayFlag - 2]/1000%10;
                                  UID_Arr[2] = Temporary_UID[WirelessSet_Reverse_DisplayFlag - 2]/100%10;
                                  UID_Arr[1] = Temporary_UID[WirelessSet_Reverse_DisplayFlag - 2]/10%10;
                                  UID_Arr[0] = Temporary_UID[WirelessSet_Reverse_DisplayFlag - 2]/1%10; 
                                  WirelessSet_Bit = 0;
                                  
                                  g_showWindowType = SHOW_UID_WINDOW;
                                  display_color(BACKGROUND_COLOR);  //清屏
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(Wireless_Next_Page == 1)&&
                                      ((WirelessSet_Reverse_DisplayFlag == 1)  //6
                                      ||(WirelessSet_Reverse_DisplayFlag == 2)  //7
                                      ||(WirelessSet_Reverse_DisplayFlag == 3)))  //进入UID设置界面(第二页) 
                              {
                                  Temporary_UID[WirelessSet_Reverse_DisplayFlag + 5] = Wireless_Sensor[WirelessSet_Reverse_DisplayFlag + 5].UID;
                                  memset(UID_Arr,0,5);
                                  UID_Arr[4] = Temporary_UID[WirelessSet_Reverse_DisplayFlag + 5]/10000;
                                  UID_Arr[3] = Temporary_UID[WirelessSet_Reverse_DisplayFlag + 5]/1000%10;
                                  UID_Arr[2] = Temporary_UID[WirelessSet_Reverse_DisplayFlag + 5]/100%10;
                                  UID_Arr[1] = Temporary_UID[WirelessSet_Reverse_DisplayFlag + 5]/10%10;
                                  UID_Arr[0] = Temporary_UID[WirelessSet_Reverse_DisplayFlag + 5]/1%10; 
                                  WirelessSet_Bit = 0;
                                  
                                  g_showWindowType = SHOW_UID_WINDOW;
                                  display_color(BACKGROUND_COLOR);  //清屏
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }
                              
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(Wireless_Next_Page == 0)&&
                                      (WirelessSet_Reverse_DisplayFlag == 9))  //保存UID参数并返回到菜单界面 
                              {
                                  Wireless_Sensor[0].UID = Temporary_UID[0];  //赋值
                                  Wireless_Sensor[1].UID = Temporary_UID[1];
                                  Wireless_Sensor[2].UID = Temporary_UID[2];
                                  Wireless_Sensor[3].UID = Temporary_UID[3];
                                  Wireless_Sensor[4].UID = Temporary_UID[4];
                                  Wireless_Sensor[5].UID = Temporary_UID[5];
                                  EEPROM.Connect_Temp_Alarm = Temporary_Displag.Connect_Temp;
                                                                    
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_MENUWINDOW;                                                                
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //清屏

                                  EEPROM.UID[0] = Wireless_Sensor[0].UID;
                                  EEPROM.UID[1] = Wireless_Sensor[1].UID;
                                  EEPROM.UID[2] = Wireless_Sensor[2].UID;
                                  EEPROM.UID[3] = Wireless_Sensor[3].UID;
                                  EEPROM.UID[4] = Wireless_Sensor[4].UID;
                                  EEPROM.UID[5] = Wireless_Sensor[5].UID;
                                  EEPROM.UID[6] = Wireless_Sensor[6].UID;
                                  EEPROM.UID[7] = Wireless_Sensor[7].UID;
                                  EEPROM.UID[8] = Wireless_Sensor[8].UID;                                
                                  PRO_EEPROM_UpDate();
                              }   
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(Wireless_Next_Page == 1)&&
                                      (WirelessSet_Reverse_DisplayFlag == 5))  //保存UID参数并返回到菜单界面 
                              {
                                  Wireless_Sensor[6].UID = Temporary_UID[6]; 
                                  Wireless_Sensor[7].UID = Temporary_UID[7];
                                  Wireless_Sensor[8].UID = Temporary_UID[8];                                  
                                  
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_MENUWINDOW;                                                                
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //清屏 

                                  EEPROM.UID[0] = Wireless_Sensor[0].UID;
                                  EEPROM.UID[1] = Wireless_Sensor[1].UID;
                                  EEPROM.UID[2] = Wireless_Sensor[2].UID;
                                  EEPROM.UID[3] = Wireless_Sensor[3].UID;
                                  EEPROM.UID[4] = Wireless_Sensor[4].UID;
                                  EEPROM.UID[5] = Wireless_Sensor[5].UID;
                                  EEPROM.UID[6] = Wireless_Sensor[6].UID;
                                  EEPROM.UID[7] = Wireless_Sensor[7].UID;
                                  EEPROM.UID[8] = Wireless_Sensor[8].UID;                                
                                  PRO_EEPROM_UpDate();                                
                              }  
                              else if(((g_showWindowType == SHOW_UID_WINDOW))  //返回到无线测温界面
                                      ||((WirelessSet_Reverse_DisplayFlag == 1)
                                      ||(WirelessSet_Reverse_DisplayFlag == 2)
                                      ||(WirelessSet_Reverse_DisplayFlag == 3)
                                      ||(WirelessSet_Reverse_DisplayFlag == 4)
                                      ||(WirelessSet_Reverse_DisplayFlag == 5) 
                                      ||(WirelessSet_Reverse_DisplayFlag == 6)))
                              {
                                  if(Wireless_Next_Page == 0)
                                  {
                                      Temporary_UID[WirelessSet_Reverse_DisplayFlag-2] = UID_Arr[0] + (UID_Arr[1]*10)+(UID_Arr[2]*100)+(UID_Arr[3]*1000)+(UID_Arr[4]*10000);                                  
                                  }
                                  else
                                  {
                                      Temporary_UID[WirelessSet_Reverse_DisplayFlag+5] = UID_Arr[0] + (UID_Arr[1]*10)+(UID_Arr[2]*100)+(UID_Arr[3]*1000)+(UID_Arr[4]*10000);                                   
                                  }

                                  g_showWindowType = SHOW_WIRELESSSET_WINDOW;
                                  WirelessSetFlag = Yes;
                                  WirelessSet_Flag_2 = Yes;
                                  display_color(BACKGROUND_COLOR);  //清屏
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                                  
                              }
                            

                              if((g_showWindowType == SHOW_FUNCTIONSET_WINDOW)&&(FunctionSet_Reverse_DisplayFlag == 5))  //返回到菜单界面
                              {
                                  FunctionSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_MENUWINDOW;                                                                
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //清屏
                              }                              
                              else if((g_showWindowType == SHOW_MENUWINDOW)&&(Menu_Reverse_DisplayFlag == 4))  //返回到主界面
                              {
                                  Menu_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_GROUPWINDOW;
                                  s_initGroupShowWindowFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //清屏
                                  Switch_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }  
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 7))  //返回到菜单界面
                              {
                                  TempHumiSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_MENUWINDOW;
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //清屏
                              }
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 10)&&(Wireless_Next_Page == 0))  //无线测温界面，下翻页
                              {
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_WIRELESSSET_WINDOW;
                                  WirelessSetFlag = Yes;
                                  WirelessSet_Flag_2 = Yes;
                                  Wireless_Next_Page = 1;
                                  display_color(BACKGROUND_COLOR);  //清屏                                                            
                              }
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 6)&&(Wireless_Next_Page == 1))  //无线测温界面，上翻页
                              {
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_WIRELESSSET_WINDOW;
                                  WirelessSetFlag = Yes;
                                  WirelessSet_Flag_2 = Yes;
                                  Wireless_Next_Page = 0;
                                  display_color(BACKGROUND_COLOR);  //清屏                                                            
                              } 
                              else if(((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 8)&&(Wireless_Next_Page == 0))
                                      ||((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 4)&&(Wireless_Next_Page == 1)))  //返回到菜单界面   
                               {
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_MENUWINDOW;
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //清屏
                               }

                              if(g_showWindowType == SHOW_FUNCTIONSET_WINDOW)  //保存地址、语音提示、波特率
                              {
                                  if(FunctionSet_Reverse_DisplayFlag == 4)
                                  {
                                      EEPROM.TheMachineAddress = Temporary_Displag.Add;
                                      EEPROM.Voice_Prompt_Flag = Temporary_Displag.YuYin;
                                    
                                      PRO_EEPROM_UpDate();
                                    
                                      FunctionSet_Reverse_DisplayFlag = 0;
                                      g_showWindowType = SHOW_MENUWINDOW;                                                                
                                      ShowMenuFlag = Yes;
                                      display_color(BACKGROUND_COLOR);  //清屏                                       
                                  }
                              }
                                                            
                              if(g_showWindowType == SHOW_TEMPHUMISET_WINDOW)  //保存温湿度阈值
                              {
                                  if(TempHumiSet_Reverse_DisplayFlag == 6)
                                  {
                                      EEPROM.Humidity_YuZhi = Temporary_Displag.Humi_SX;
                                      EEPROM.Humidity_HuiCha = Temporary_Displag.Humi_HC;
                                      EEPROM.Temp_Upper_Limit = Temporary_Displag.Temp_SX;
                                      EEPROM.Temp_Lower_Limit = Temporary_Displag.Temp_XX;
                                      EEPROM.Temp_HuiCha = Temporary_Displag.Temp_HC;
                                      PRO_EEPROM_UpDate();
                                    
                                      TempHumiSet_Reverse_DisplayFlag = 0;
                                      g_showWindowType = SHOW_MENUWINDOW;                                                                
                                      ShowMenuFlag = Yes;
                                      display_color(BACKGROUND_COLOR);  //清屏                                        
                                  }
                              } 

                              LED_ZM_Flag = Yes;
                              LED_ZM_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              
                              return HasBeenCompleted;  //返回已执行完成
                          }
//                          break;
                          
                     case PressDownStabilize:  //常按（按住3秒或以上）
                          {

                              
                              return HasBeenCompleted;  //返回已执行完成
                          }
//                          break;
                          
                     default: break;
                 }
             }
             break;            
             
        default: break;
    }
    return HasBeenCompleted;  //返回已执行完成
}


/***************************************************************************
* 函数名：  APP_Key_Init
* 功能描述：按键模块初始化
* 入口参数：无
* 出口参数：无
* 注意事项：配置与按键相关的IO口，如果在扫描按键过程中IO口要频繁地改变方向的
*           话（如：塔型按键扫描），就要把IO口配置写在"Key_Check"函数中，不
*           用理睬该函数，如果有用到该函数则必须放在主循环之前。
* 修改记录：无
*           2016/9/29 BY:陈勇
***************************************************************************/
void APP_Key_Init(void)
{
    
}
