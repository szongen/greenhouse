/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------������ģ����޸ļ�¼��---------------------------------                                   *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***********************************************
 * ���ݣ�����
 * ���ڣ�2016/9/29
 * ���ߣ�����
 * �汾�ţ�V1.0�����棩
 ***********************************************
 * �޸����ݣ�
 * �޸����ڣ�
 * �޸����ߣ�
 * �汾�ţ�
 ***********************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------������ģ���ʹ��˵����---------------------------------                                   *
*                                                                                                                                           *
********************************************************************************************************************************************/
/*                                           ģ��ʹ��˵����
 *
 * 1."Key_CurrentTime_ms"��"Key_TimingQuery_30ms"��"Key_TimingQuery_3s"����������Ҫ�û���Ӷ�ʱ���룬��ʱҪ����ɨ�跽ʽ�������Ժ���Ϊ��λ��
 * 2."Key_Check"������Ҫ�û���Ӱ���ɨ����롣
 * 3."Key_Task"������Ҫ�û���Ӱ���������롣
 * 4."APP_Key_Init"������Ҫ�û���Ӱ������IO�ڵ����ô��룬�����ɨ�谴��������IO��ҪƵ���ظı䷽��Ļ����磺���Ͱ���ɨ�裩����Ҫ��IO������д��"Key_Check"���������Ҫ�ú�����
 *
 */
#include "BSP.h"
#include "APP_U_Key.h"
#include "APP_S_Key.h"

/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------������ģ��ĶԽӺ�����---------------------------------                                    *
*                                                                                                                                           *
********************************************************************************************************************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------������ģ����ڲ�����������---------------------------------                                *
*                                                                                                                                           *
********************************************************************************************************************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------������ģ��ı��������ͺ궨����---------------------------------                            *
*                                                                                                                                           *
********************************************************************************************************************************************/

/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------������ģ���ϵͳ����������---------------------------------                               *
*                                                                                                                                           *
********************************************************************************************************************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------������ģ����ڲ�����������---------------------------------                                *
*                                                                                                                                           *
********************************************************************************************************************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------������ģ����û�����������---------------------------------                                *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* ��������  Key_CurrentTime_ms
* ������������ȡ��ǰʱ�䣬���ڶ�ʱ
* ��ڲ�������
* ���ڲ�����16λ���ĵ�ǰʱ�䣬��λΪ����
* ע�������
* �޸ļ�¼����
*           2016/9/29 BY:����
***************************************************************************/
u16 Key_CurrentTime_ms(void)
{
    return API_SystemClock_CurrentTime_ms();
}


/***************************************************************************
* ��������  Key_TimingQuery_30ms
* ������������ѯ��ʱ30����
* ��ڲ�����StartingTime_ms����ʼʱ�䣨���룩
* ���ڲ�����TimeOut����ʱʱ���ѵ�
*           NoTimeOut����ʱʱ�仹û��
* ע�������
* �޸ļ�¼����
*           2016/9/29 BY:����
***************************************************************************/
u8 Key_TimingQuery_30ms(u16 StartingTime_ms)
{
    return API_SystemClock_TimingQuery_ms(StartingTime_ms,30);
}


/***************************************************************************
* ��������  Key_TimingQuery_3s
* ������������ѯ��ʱ3��
* ��ڲ�����StartingTime_ms����ʼʱ�䣨���룩
* ���ڲ�����TimeOut����ʱʱ���ѵ�
*           NoTimeOut����ʱʱ�仹û��
* ע�����Ϊ�˼�������ڲ����ṩ����ʼʱ�����Ժ���Ϊ��λ��
* �޸ļ�¼����
*           2016/9/29 BY:����
***************************************************************************/
u8 Key_TimingQuery_3s(u16 StartingTime_ms)
{
    return API_SystemClock_TimingQuery_ms(StartingTime_ms,2000);  //����3��̫��������ĳ�2��
}


/***************************************************************************
* ��������  Key_Check
* �����������������
* ��ڲ�����*PressDownKey����ŵ�ǰ�����µİ�����
* ���ڲ�����PressDown���а���������
*           NoPressDown��û�а���������
* ע������ú�����Ҫ��Ӱ�����ɨ����루�磺IO�ڰ���ɨ�衢���󰴼�ɨ�衢
*           ���Ͱ���ɨ��ȣ������ɨ�赽�а��������£���Ҫ��"PressDownKey"
*           �ı�����ַ����뵱ǰ�����µİ�����������"PressDown"�����û��ɨ
*           �赽���������¾�Ҫ����"NoPressDown"��
* �޸ļ�¼����
*           2016/9/29 BY:����
***************************************************************************/
u8 Key_Check(u8 *PressDownKey)
{
    if(HC165.Key_Enter == 0)  //ȷ�ϰ���
    {
        *PressDownKey = ENTER;  //��ǰ�����µİ���
        return PressDown;  //�����а���������
    }

    if(HC165.Key_Menu == 0)  //�˵�����
    {
        *PressDownKey = MENU;  //��ǰ�����µİ���
        return PressDown;  //�����а���������
    }
    
    if(HC165.Key_Up == 0)  //�ϵ�
    {
        *PressDownKey = SWUP;  //��ǰ�����µİ���
        return PressDown;  //�����а���������
    }

    if(HC165.Key_Down == 0)  //�µ�
    {
        *PressDownKey = SWDOWN;  //��ǰ�����µİ���
        return PressDown;  //�����а���������
    }
		
    return NoPressDown;  //����û�а���������
}


/***************************************************************************
* ��������  Key_Task
* ����������ִ�а���������
* ��ڲ�����PressDownKey����ǰ�����µİ�����
*           KeyMode��SharedTask����ͬ���񣬵㶯�ͳ�����ͬ���ǲ��������磺��������
*                    PressDownOnce���㶯�����º�3�����ɿ���
*                    PressDownStabilize�����������³���3�����ɿ���
* ���ڲ�����HangInTheAir����������δִ�����
*           HasBeenCompleted������������ִ�����
* ע�����1."��ͬ����"����ִ��"�㶯"��"����"��ͬ���ǲ��������磺����������
*             ��Ҳ����äĿ��д��һ����Ϊ���߶�������Ӧ�Ӿ�����������ϣ�
*             "��ͬ����"�ǰ��������º�û�ſ��Ͷ�������"�㶯"��"����"���ǰ�
*             �I�����º󲻻����̶�����Ҫ�ȵ������ſ���Ŷ������������ֻ��
*             "�㶯"���ܵĻ����齫����ȫ��д��"��ͬ����"�У�����һ���¾Ͷ���
*             �ȽϷ������ǵĲ���ϰ�ߡ�
*           2.���°���һ����һ��ģʽֻ�����ú���һ�Σ������񰴼���������Ҫ
*             ��ʱ������Ͳ���ָ���ڸú�������ɣ�����Ǹ���ʱ��������һ����
*             ־λ���ڸú�����ʹ�ܱ�־λ��������������������������ʱ������
*             �����ڸú�������ɺ����뿪��
*           3.��������һ�λ����ú������Σ���һ����"��ͬ����"���ڶ�����"�㶯"
*             ����"����"�������"��ͬ����"���ѽ��ð���������ִ����ɾ�Ҫ����
*             �����"HasBeenCompleted"�������"��ͬ����"��ִ�к�Ҫ��"�㶯"��
*             "����"�����ִ�У���ʱ"��ͬ����"��Ҫ����δ���"HangInTheAir"��
*             ����˵"��ͬ����"�ǰ�������"�㶯"��"����"�ǰ�������������"��ͬ
*             ����"��Ҫ����δ���"HangInTheAir"��"�㶯"��"����"��Ҫ���������
*             "HasBeenCompleted"��
* �޸ļ�¼����
*           2016/9/29 BY:����
***************************************************************************/
u8 Key_Task(u8 PressDownKey,u8 KeyMode)
{
    switch(PressDownKey)  //��ǰ�����µİ���
    {                  
        case SWUP:  //��ֵ�ӡ��Լ�
             {
                 switch(KeyMode)  //�������µķ�ʽ
                 {
                     case SharedTask:  //��ͬ����
                          {
                              
                              
                              return HangInTheAir;  //����δִ�����
                          }
//                          break;
                          
                     case PressDownOnce:  //�㶯
                          {
                              if((g_showWindowType == SHOW_FUNCTIONSET_WINDOW)&&(FunctionSet_Reverse_DisplayFlag == 1))  //���õ�ַ
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
                              else if((g_showWindowType == SHOW_FUNCTIONSET_WINDOW)&&(FunctionSet_Reverse_DisplayFlag == 3))  //����������ʾ
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

                              if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 1))  //�����¶�����
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
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 2))  //�����¶�����
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
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 3))  //�����¶Ȼز�
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
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 4))  //����ʪ������
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
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 5))  //����ʪ������
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
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 1))  //���ý�ͷ�¶ȱ�������
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
                              
                              if(g_showWindowType == SHOW_UID_WINDOW)  //����UID��ֵ
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
                              
                              LED_ZM_Flag = Yes;  //LCD����
                              LED_ZM_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                              
                            
                              return HasBeenCompleted;  //������ִ�����
                          }
//                          break;
                          
                     case PressDownStabilize:  //��������ס3������ϣ�
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
                              
                              return HasBeenCompleted;  //������ִ�����
                          }
//                          break;
                          
                     default: break;
                 }
             }
             break;
             
        case SWDOWN:  //��ֵ��
             {
                 switch(KeyMode)  //�������µķ�ʽ
                 {
                     case SharedTask:  //��ͬ����
                          {
                              
                              
                              return HangInTheAir;  //����δִ�����
                          }
//                          break;
                          
                     case PressDownOnce:  //�㶯
                          {
                              if((g_showWindowType == SHOW_FUNCTIONSET_WINDOW)&&(FunctionSet_Reverse_DisplayFlag == 1))  //���õ�ַ
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
                              else if((g_showWindowType == SHOW_FUNCTIONSET_WINDOW)&&(FunctionSet_Reverse_DisplayFlag == 3))  //����������ʾ
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

                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 1))  //�����¶�����
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
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 2))  //�����¶�����
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
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 3))  //�����¶Ȼز�
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
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 4))  //����ʪ������
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
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 5))  //����ʪ������
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
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 1))  //���ý�ͷ�¶ȱ�������
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
                              else if(g_showWindowType == SHOW_UID_WINDOW)  //����UID��ֵ
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
                              else if(g_showWindowType == SHOW_GROUPWINDOW)  //�����л�
                              {
                                  g_showWindowType = SHOW_WIRELESSTEMP;
                                  s_initGroupShowWirelessFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //����     
                                  Switch_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                                
                              }
                              else if(g_showWindowType == SHOW_WIRELESSTEMP)  //�����л�
                              {
                                  g_showWindowType = SHOW_GROUPWINDOW;
                                  s_initGroupShowWindowFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //����  
                                  Switch_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                                   
                              }  
                              
                              LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              
                              LED_ZM_Flag = Yes;
                              LED_ZM_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                              
                              
                              return HasBeenCompleted;  //������ִ�����
                          }
//                          break;
                          
                     case PressDownStabilize:  //��������ס3������ϣ�
                          {
                              
                              return HasBeenCompleted;  //������ִ�����
                          }
//                          break;
                          
                     default: break;
                 }
             }
             break;
             
        case ENTER:  //���µ��л��������������߹���
             {
                 switch(KeyMode)  //�������µķ�ʽ
                 {
                     case SharedTask:  //��ͬ����
                          {
                              
                              
                              return HangInTheAir;  //����δִ�����
                          }
//                          break;
                          
                     case PressDownOnce:  //�㶯
                          {                        
															if(g_showWindowType == SHOW_MENUWINDOW)  //�˵�����
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
                              
                              if((g_showWindowType == SHOW_GROUPWINDOW)||(g_showWindowType == SHOW_WIRELESSTEMP))  //�������߹���
                              {
                                  JRQ1_Broken_Line_Flag = No;
                                  JRQ2_Broken_Line_Flag = No;
                                  FJ_Broken_Line_Flag = No;
                              }
                              
															if(g_showWindowType == SHOW_FUNCTIONSET_WINDOW)  //�������ý���
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

															if(g_showWindowType == SHOW_TEMPHUMISET_WINDOW)  //��ʪ�����ý���
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
                              
															if(g_showWindowType == SHOW_WIRELESSSET_WINDOW)  //���߲������ý���
                              {
                                  if(Wireless_Next_Page == 0)  //��һҳ�л�
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
                                  else  //�ڶ�ҳ�л�
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

                              if(g_showWindowType == SHOW_UID_WINDOW)  //���߲�������UID����
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
                              
                              return HasBeenCompleted;  //������ִ�����
                          }
//                          break;
                          
                     case PressDownStabilize:  //��������ס3������ϣ�
                          {
                              #if(Manual_Mode_FUNCTION == NEED)
                              if(Manual_Status_Flag == Yes)  //�ֶ�
                              {
                                  Manual_Status_Flag = No;
                                  s_initGroupShowWindowFlag = Yes;
                              }
                              else
                              {
                                  Manual_Status_Flag = Yes;
                                  JRQ1_Broken_Line_Flag = No;  //������߱�־λ
                                  JRQ2_Broken_Line_Flag = No;
                                  FJ_Broken_Line_Flag = No;
                                  s_initGroupShowWindowFlag = Yes;
                              }
                              #endif

                              LED_ZM_Flag = Yes;
                              LED_ZM_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              
                              return HasBeenCompleted;  //������ִ�����
                          }
//                          break;
                          
                     default: break;
                 }
             }
             break;
             
        case MENU:  //�˵���ȷ�ϱ��水��
             {
                 switch(KeyMode)  //�������µķ�ʽ
                 {
                     case SharedTask:  //��ͬ����
                          {
                              
                              
                              return HangInTheAir;  //����δִ�����
                          }
//                          break;
                          
                     case PressDownOnce:  //�㶯
                          {
														  if((g_showWindowType == SHOW_GROUPWINDOW)||(g_showWindowType == SHOW_WIRELESSTEMP))  //����˵�����
                              {
                                  g_showWindowType = SHOW_MENUWINDOW;
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //����
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }                              
                              else if((g_showWindowType == SHOW_MENUWINDOW)&&(Menu_Reverse_DisplayFlag == 1))  //���빦�����ý���
                              {
                                  Menu_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_FUNCTIONSET_WINDOW;
                                  FunctionSetFlag = Yes;
                                
                                  Temporary_Displag.Add = EEPROM.TheMachineAddress;  //������ֵ
                                  Temporary_Displag.YuYin = EEPROM.Voice_Prompt_Flag;
                                
                                  display_color(BACKGROUND_COLOR);  //����
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }
															else if((g_showWindowType == SHOW_MENUWINDOW)&&(Menu_Reverse_DisplayFlag == 2))  //������ʪ�����ý���
                              {
                                  Menu_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_TEMPHUMISET_WINDOW;
                                  TempHumiSetFlag = Yes;
                                
                                  Temporary_Displag.Humi_SX = EEPROM.Humidity_YuZhi;
                                  Temporary_Displag.Humi_HC = EEPROM.Humidity_HuiCha;
                                  Temporary_Displag.Temp_SX = EEPROM.Temp_Upper_Limit;
                                  Temporary_Displag.Temp_XX = EEPROM.Temp_Lower_Limit;
                                  Temporary_Displag.Temp_HC = EEPROM.Temp_HuiCha;
                                
                                  display_color(BACKGROUND_COLOR);  //���� 
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              } 
															else if((g_showWindowType == SHOW_MENUWINDOW)&&(Menu_Reverse_DisplayFlag == 3))  //�������߲������ý���
                              {
                                  Menu_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_WIRELESSSET_WINDOW;
                                  WirelessSetFlag = Yes;
                                
                                  Temporary_Displag.Connect_Temp = EEPROM.Connect_Temp_Alarm;
                                  Temporary_UID[0] = Wireless_Sensor[0].UID;  //��ֵ
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
                                  display_color(BACKGROUND_COLOR);  //���� 
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }                                                            
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(Wireless_Next_Page == 0)&&
                                      ((WirelessSet_Reverse_DisplayFlag == 2)  //0
                                      ||(WirelessSet_Reverse_DisplayFlag == 3)  //1
                                      ||(WirelessSet_Reverse_DisplayFlag == 4)  //2
                                      ||(WirelessSet_Reverse_DisplayFlag == 5)
                                      ||(WirelessSet_Reverse_DisplayFlag == 6)
                                      ||(WirelessSet_Reverse_DisplayFlag == 7)))  //����UID���ý���(��һҳ)
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
                                  display_color(BACKGROUND_COLOR);  //����
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(Wireless_Next_Page == 1)&&
                                      ((WirelessSet_Reverse_DisplayFlag == 1)  //6
                                      ||(WirelessSet_Reverse_DisplayFlag == 2)  //7
                                      ||(WirelessSet_Reverse_DisplayFlag == 3)))  //����UID���ý���(�ڶ�ҳ) 
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
                                  display_color(BACKGROUND_COLOR);  //����
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }
                              
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(Wireless_Next_Page == 0)&&
                                      (WirelessSet_Reverse_DisplayFlag == 9))  //����UID���������ص��˵����� 
                              {
                                  Wireless_Sensor[0].UID = Temporary_UID[0];  //��ֵ
                                  Wireless_Sensor[1].UID = Temporary_UID[1];
                                  Wireless_Sensor[2].UID = Temporary_UID[2];
                                  Wireless_Sensor[3].UID = Temporary_UID[3];
                                  Wireless_Sensor[4].UID = Temporary_UID[4];
                                  Wireless_Sensor[5].UID = Temporary_UID[5];
                                  EEPROM.Connect_Temp_Alarm = Temporary_Displag.Connect_Temp;
                                                                    
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_MENUWINDOW;                                                                
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //����

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
                                      (WirelessSet_Reverse_DisplayFlag == 5))  //����UID���������ص��˵����� 
                              {
                                  Wireless_Sensor[6].UID = Temporary_UID[6]; 
                                  Wireless_Sensor[7].UID = Temporary_UID[7];
                                  Wireless_Sensor[8].UID = Temporary_UID[8];                                  
                                  
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_MENUWINDOW;                                                                
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //���� 

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
                              else if(((g_showWindowType == SHOW_UID_WINDOW))  //���ص����߲��½���
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
                                  display_color(BACKGROUND_COLOR);  //����
                                  LCD_CurrentTime_ms = API_SystemClock_CurrentTime_ms();                                  
                              }
                            

                              if((g_showWindowType == SHOW_FUNCTIONSET_WINDOW)&&(FunctionSet_Reverse_DisplayFlag == 5))  //���ص��˵�����
                              {
                                  FunctionSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_MENUWINDOW;                                                                
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //����
                              }                              
                              else if((g_showWindowType == SHOW_MENUWINDOW)&&(Menu_Reverse_DisplayFlag == 4))  //���ص�������
                              {
                                  Menu_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_GROUPWINDOW;
                                  s_initGroupShowWindowFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //����
                                  Switch_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              }  
                              else if((g_showWindowType == SHOW_TEMPHUMISET_WINDOW)&&(TempHumiSet_Reverse_DisplayFlag == 7))  //���ص��˵�����
                              {
                                  TempHumiSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_MENUWINDOW;
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //����
                              }
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 10)&&(Wireless_Next_Page == 0))  //���߲��½��棬�·�ҳ
                              {
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_WIRELESSSET_WINDOW;
                                  WirelessSetFlag = Yes;
                                  WirelessSet_Flag_2 = Yes;
                                  Wireless_Next_Page = 1;
                                  display_color(BACKGROUND_COLOR);  //����                                                            
                              }
                              else if((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 6)&&(Wireless_Next_Page == 1))  //���߲��½��棬�Ϸ�ҳ
                              {
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_WIRELESSSET_WINDOW;
                                  WirelessSetFlag = Yes;
                                  WirelessSet_Flag_2 = Yes;
                                  Wireless_Next_Page = 0;
                                  display_color(BACKGROUND_COLOR);  //����                                                            
                              } 
                              else if(((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 8)&&(Wireless_Next_Page == 0))
                                      ||((g_showWindowType == SHOW_WIRELESSSET_WINDOW)&&(WirelessSet_Reverse_DisplayFlag == 4)&&(Wireless_Next_Page == 1)))  //���ص��˵�����   
                               {
                                  WirelessSet_Reverse_DisplayFlag = 0;
                                  g_showWindowType = SHOW_MENUWINDOW;
                                  ShowMenuFlag = Yes;
                                  display_color(BACKGROUND_COLOR);  //����
                               }

                              if(g_showWindowType == SHOW_FUNCTIONSET_WINDOW)  //�����ַ��������ʾ��������
                              {
                                  if(FunctionSet_Reverse_DisplayFlag == 4)
                                  {
                                      EEPROM.TheMachineAddress = Temporary_Displag.Add;
                                      EEPROM.Voice_Prompt_Flag = Temporary_Displag.YuYin;
                                    
                                      PRO_EEPROM_UpDate();
                                    
                                      FunctionSet_Reverse_DisplayFlag = 0;
                                      g_showWindowType = SHOW_MENUWINDOW;                                                                
                                      ShowMenuFlag = Yes;
                                      display_color(BACKGROUND_COLOR);  //����                                       
                                  }
                              }
                                                            
                              if(g_showWindowType == SHOW_TEMPHUMISET_WINDOW)  //������ʪ����ֵ
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
                                      display_color(BACKGROUND_COLOR);  //����                                        
                                  }
                              } 

                              LED_ZM_Flag = Yes;
                              LED_ZM_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
                              
                              return HasBeenCompleted;  //������ִ�����
                          }
//                          break;
                          
                     case PressDownStabilize:  //��������ס3������ϣ�
                          {

                              
                              return HasBeenCompleted;  //������ִ�����
                          }
//                          break;
                          
                     default: break;
                 }
             }
             break;            
             
        default: break;
    }
    return HasBeenCompleted;  //������ִ�����
}


/***************************************************************************
* ��������  APP_Key_Init
* ��������������ģ���ʼ��
* ��ڲ�������
* ���ڲ�������
* ע����������밴����ص�IO�ڣ������ɨ�谴��������IO��ҪƵ���ظı䷽���
*           �����磺���Ͱ���ɨ�裩����Ҫ��IO������д��"Key_Check"�����У���
*           ����Ǹú�����������õ��ú�������������ѭ��֮ǰ��
* �޸ļ�¼����
*           2016/9/29 BY:����
***************************************************************************/
void APP_Key_Init(void)
{
    
}
