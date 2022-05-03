/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------������ģ����޸ļ�¼��---------------------------------                                   *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***********************************************
 * ���ݣ�ϵͳʱ��
 * ���ڣ�2016/7/8
 * ���ߣ�����
 * �汾�ţ�V1.0�����棩
 ***********************************************
 * �޸����ݣ�1.����ʱ��Ƭ��ѯ����Ҫ�õ���ʱ��㡣
 *           2.��ԭ����2���ļ��ֳ�4���ļ����ļ����д�"S"���Ǹ�ģ���ϵͳ���룬�û��������޸ģ���"U"���Ǹ�ģ����û����룬��Ҫ�����û���������ʹ�ø�ģ�顣
 *           3.ȡ�����ñ����Զ�����ķ�ʽ�������˹���ѯ�����ʽ��
 * �޸����ڣ�2016/9/23
 * �޸����ߣ�����
 * �汾�ţ�V1.1
 ***********************************************
 ***********************************************
 * �޸����ݣ�ȡ�����б�����ʹ��"volatile"�ؼ��֡�
 * �޸����ڣ�2017/10/24
 * �޸����ߣ�����
 * �汾�ţ�V1.2
 ***********************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------������ģ���ʹ��˵����---------------------------------                                   *
*                                                                                                                                           *
********************************************************************************************************************************************/
/*                                           ģ��ʹ��˵����
 *
 * ��ģ������Ŀ���̵�ϵͳ��׼ʱ�ӣ���"��"��"����"���ֵ�λ����Ҫ������Ŀ��Ҫ�󲻸ߵĶ�ʱ��������������"��1��"����������������"��10����"����
 * ģ�����ʹ��ɨ�跽ʽ������ʹ�ò������£�
 * 1.ʹ�ú���"API_SystemClock_Init"��ʼ��ϵͳʱ�ӣ��ں�����ʹ��һ��MCU��Ӳ����ʱ�������ó�ÿ10�����ж�һ�Σ������ʱ����ʼ��ʱ�ͱ�����������
 *   �Ҳ��ܷ����κ��¶�����ֹͣ������MCU��������״̬����Ҫ����Ŀ��ѭ��֮ǰ���г�ʼ����
 * 2.��"API_SystemClock_ReferenceClock"��������MCUӲ����ʱ�����жϷ���������ǵ�һ����ʼ�����Ǹ���ʱ������
 * 3.����Ҫ������ʱʱ����һ���޷���16λ������ȡϵͳ�ĵ�ǰʱ�䣬��"API_SystemClock_CurrentTime_ms"������"API_SystemClock_CurrentTime_s"������
 *   ���ֵ��
 * 4.����Ҫ��ʱ�ĵط�ɨ��"API_SystemClock_TimingQuery_ms"������"API_SystemClock_TimingQuery_s"���������ֵ�������Ϊ"TimeOut"˵��ʱ�䵽����
 *   �����"NoTimeOut"˵��ʱ��û����
 * ע����ģ�����ʹ��ɨ�跽ʽ����Ҫ��ʱ��ɨ��"API_SystemClock_TimingQuery_ms"������"API_SystemClock_TimingQuery_s"����������Ҫ�Ͳ�Ҫɨ�裬û
 *     ��ֹͣѡ�
 * 
 * ��ģ��ĵڶ���������Ϊ��ʱ�����ṩʱ��㣬�û�������������ָ����ʱ��������У�������������ʱ������һ��ʱ�Σ�������ֻ�����ʱ�������У�
 * ����ʹ�ò������£�
 * 1.��"API_U_SystemClock.h"�ļ����������ʱ��㣬����Ϊ0~65535��1���ʾ10ms������ʱʱ������"0~���ʱ���"֮��ѭ��������"0"��"���ʱ���"����
 * 2.����"API_SystemClock_TimePoint"�����ɻ�ȡ��ǰʱ��㡣
 *
 */
#include "stm32f1xx_hal.h"
#include "API_S_SystemClock.h"
#include "API_U_SystemClock.h"
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
static uint16_t SystemClock_ms = 0;  //ϵͳʱ�ӣ����룩
static uint16_t SystemClock_s = 0;  //ϵͳʱ�ӣ��룩
//static uint16_t SystemClock_min = 0;  //ϵͳʱ�ӣ����ӣ�
uint16_t SystemClock_min = 0;  //ϵͳʱ�ӣ����ӣ�
static uint16_t TimePoint = 0;  //ʱ��㣬Ϊ��ʱ�����ṩʱ���


/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------������ģ���ϵͳ����������---------------------------------                               *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* ��������  API_SystemClock_CurrentTime_ms
* ������������ȡ��ǰʱ�䣨���룩�����ڶ�ʱ��ѯ
* ��ڲ�������
* ���ڲ�����16λ�޷������ĵ�ǰʱ�䣨���룩
* ע���������ʱ���øú�������ȡ��ǰʱ�䣬����"API_SystemClock_TimingQuery_ms"
*           �����ĵ�1���������"StartingTime_ms"
* �޸ļ�¼����
*           2016/7/8 BY:����
***************************************************************************/
uint16_t API_SystemClock_CurrentTime_ms(void)
{
    return SystemClock_ms;
}


/***************************************************************************
* ��������  API_SystemClock_CurrentTime_s
* ������������ȡ��ǰʱ�䣨�룩�����ڶ�ʱ��ѯ
* ��ڲ�������
* ���ڲ�����16λ�޷������ĵ�ǰʱ�䣨�룩
* ע���������ʱ���øú�������ȡ��ǰʱ�䣬����"API_SystemClock_TimingQuery_s"
*           �����ĵ�1���������"StartingTime_s"
* �޸ļ�¼����
*           2016/7/8 BY:����
***************************************************************************/
uint16_t API_SystemClock_CurrentTime_s(void)
{
    return SystemClock_s;
}


/***************************************************************************
* ��������  API_SystemClock_CurrentTime_min
* ������������ȡ��ǰʱ�䣨���ӣ������ڶ�ʱ��ѯ
* ��ڲ�������
* ���ڲ�����16λ�޷������ĵ�ǰʱ�䣨���ӣ�
* ע���������ʱ���øú�������ȡ��ǰʱ�䣬����"API_SystemClock_TimingQuery_min"
*           �����ĵ�1���������"StartingTime_min"
* �޸ļ�¼����
*           2018/4/12 BY:����
***************************************************************************/
uint16_t API_SystemClock_CurrentTime_min(void)
{
    return SystemClock_min;
}


/***************************************************************************
* ��������  API_SystemClock_TimePoint
* ������������ȡ��ǰʱ��㣬Ϊ��ʱ�����ṩʱ��
* ��ڲ�������
* ���ڲ�����16λ�޷������ĵ�ǰʱ���
* ע�����1.����ʱ���øú�������ȡ��ǰʱ��㡣
*           2.��λΪ10ms
* �޸ļ�¼����
*           2016/7/8 BY:����
***************************************************************************/
uint16_t API_SystemClock_TimePoint(void)
{
    return TimePoint;
}


/***************************************************************************
* ��������  API_SystemClock_ReferenceClock
* ����������ϵͳ��׼ʱ�ӣ�10���룩
* ��ڲ�������
* ���ڲ�������
* ע������ú���������ڶ�ʱ���жϷ��������ʱ������Ϊÿ10�����ж�һ�Σ�
*           ��ʱ������һֱ��������״̬������ֹͣ��
* �޸ļ�¼����
*           2016/7/8 BY:����
***************************************************************************/
void API_SystemClock_ReferenceClock(void)
{
    static uint8_t a = 0;
    static uint8_t b = 0;
    
//    SystemClock_ms ++;  //����ú���һ��ϵͳʱ�Ӿ�����10ms
    if(SystemClock_ms == 0xffff)
    {
        SystemClock_ms = 0;
    }
    else
    {
        SystemClock_ms ++;
    }
    
    a ++;
    if(a > 99)  //100*10ms=1000ms=1s
    {
        a = 0;
        
//        SystemClock_s ++;  //ϵͳʱ������1s
        if(SystemClock_s == 0xffff)
        {
            SystemClock_s = 0;
        }
        else
        {
            SystemClock_s ++;
        }
        
        b ++;
        if(b > 59)  //60s=1min
        {
            b = 0;
            
//            SystemClock_min ++;  //ϵͳʱ������1����
            if(SystemClock_min == 0xffff)
            {
                SystemClock_min = 0;
            }
            else
            {
                SystemClock_min ++;
            }
        }
    }
    
    TimePoint ++;  //ʱ���ÿ10ms����һ��
    if(TimePoint > MaximumTimePoint)  //����������ʱ���
    {
        TimePoint = 0;
    }
}


/***************************************************************************
* ��������  API_SystemClock_TimingQuery_ms
* ������������ʱʱ���ѯ�����룩
* ��ڲ�����StartingTime_ms����ʼʱ�䣬����"API_SystemClock_CurrentTime_ms"�������������
*           TimingHowLong_ms����Ҫ��ʱ��ʱ�䣬ȡֵ��Χ��"1"~"65535"���ܱ�10��������
* ���ڲ�����TimeOut����ʱʱ���ѵ�
*           NoTimeOut����ʱʱ�仹û��
* ע������ú�����ʱ�䵥λ�Ǻ���
* �޸ļ�¼����
*           2016/7/8 BY:����
***************************************************************************/
uint8_t API_SystemClock_TimingQuery_ms(uint16_t StartingTime_ms,uint16_t TimingHowLong_ms)
{
//    vuint16_t a;
//    
//    TimingHowLong_ms = (TimingHowLong_ms / 10) - 1;  //��ʱ����ÿ10�����ж�һ�Σ���1��Ϊ�������ж�ʱ��">"������">="
//    a = SystemClock_ms - StartingTime_ms;  //ϵͳʱ�ӣ���ǰʱ�䣩- ��ʼʱ�� = �Ѿ���ȥ�˶���ʱ��
//    if(a > TimingHowLong_ms)  //�Ѿ���ȥ��ʱ���Ƿ���ڻ������Ҫ��ʱ��ʱ��
//    {
//        return TimeOut;  //�ǵĻ�˵����ʱʱ���ѵ�
//    }
//    else
//    {
//        return NoTimeOut;  //���ǵĻ�˵����ʱʱ�仹û��
//    }
    
    
    uint16_t i;
    
    if(SystemClock_ms < StartingTime_ms)  //���"��ǰʱ�� < ��ʼʱ��"˵��ʱ����������
    {
        i = (SystemClock_ms + (0xffff - StartingTime_ms)) + 1;
    }
    else  //���"��ǰʱ�� >= ��ʼʱ��"˵��ʱ�����û�����
    {
        i = SystemClock_ms - StartingTime_ms;
    }
    
    TimingHowLong_ms = TimingHowLong_ms / 10;  //��ʱ����ÿ10�����ж�һ��
    if(i >= TimingHowLong_ms)  //�Ѿ���ȥ��ʱ���Ƿ���ڻ������Ҫ��ʱ��ʱ��
    {
        return TimeOut;  //�ǵĻ�˵����ʱʱ���ѵ�
    }
    else
    {
        return NoTimeOut;  //���ǵĻ�˵����ʱʱ�仹û��
    }
}


/***************************************************************************
* ��������  API_SystemClock_TimingQuery_s
* ������������ʱʱ���ѯ���룩
* ��ڲ�����StartingTime_s����ʼʱ�䣬����"API_SystemClock_CurrentTime_s"�������������
*           TimingHowLong_s����Ҫ��ʱ��ʱ�䣬ȡֵ��Χ��"1"~"65535"
* ���ڲ�����TimeOut����ʱʱ���ѵ�
*           NoTimeOut����ʱʱ�仹û��
* ע������ú�����ʱ�䵥λ����
* �޸ļ�¼����
*           2016/7/8 BY:����
***************************************************************************/
uint8_t API_SystemClock_TimingQuery_s(uint16_t StartingTime_s,uint16_t TimingHowLong_s)
{
//    vuint16_t a;
//    
//    TimingHowLong_s --;  //��1��Ϊ�������ж�ʱ��">"������">="
//    a = SystemClock_s - StartingTime_s;  //ϵͳʱ�ӣ���ǰʱ�䣩- ��ʼʱ�� = �Ѿ���ȥ�˶���ʱ��
//    if(a > TimingHowLong_s)  //�Ѿ���ȥ��ʱ���Ƿ���ڻ������Ҫ��ʱ��ʱ��
//    {
//        return TimeOut;  //�ǵĻ�˵����ʱʱ���ѵ�
//    }
//    else
//    {
//        return NoTimeOut;  //���ǵĻ�˵����ʱʱ�仹û��
//    }
    
    
    uint16_t k;
    
    if(SystemClock_s < StartingTime_s)  //���"��ǰʱ�� < ��ʼʱ��"˵��ʱ����������
    {
        k = (SystemClock_s + (0xffff - StartingTime_s)) + 1;
    }
    else  //���"��ǰʱ�� >= ��ʼʱ��"˵��ʱ�����û�����
    {
        k = SystemClock_s - StartingTime_s;
    }
    
    if(k >= TimingHowLong_s)  //�Ѿ���ȥ��ʱ���Ƿ���ڻ������Ҫ��ʱ��ʱ��
    {
        return TimeOut;  //�ǵĻ�˵����ʱʱ���ѵ�
    }
    else
    {
        return NoTimeOut;  //���ǵĻ�˵����ʱʱ�仹û��
    }
}


/***************************************************************************
* ��������  API_SystemClock_TimingQuery_min
* ������������ʱʱ���ѯ�����ӣ�
* ��ڲ�����StartingTime_min����ʼʱ�䣬����"API_SystemClock_CurrentTime_min"�������������
*           TimingHowLong_min����Ҫ��ʱ��ʱ�䣬ȡֵ��Χ��"1"~"65535"
* ���ڲ�����TimeOut����ʱʱ���ѵ�
*           NoTimeOut����ʱʱ�仹û��
* ע������ú�����ʱ�䵥λ�Ƿ���
* �޸ļ�¼����
*           2018/4/12 BY:����
***************************************************************************/
uint8_t API_SystemClock_TimingQuery_min(uint16_t StartingTime_min,uint16_t TimingHowLong_min)
{
    uint16_t k;
    
    if(SystemClock_min < StartingTime_min)  //���"��ǰʱ�� < ��ʼʱ��"˵��ʱ����������
    {
        k = (SystemClock_min + (0xffff - StartingTime_min)) + 1;
    }
    else  //���"��ǰʱ�� >= ��ʼʱ��"˵��ʱ�����û�����
    {
        k = SystemClock_min - StartingTime_min;
    }
    
    if(k >= TimingHowLong_min)  //�Ѿ���ȥ��ʱ���Ƿ���ڻ������Ҫ��ʱ��ʱ��
    {
        return TimeOut;  //�ǵĻ�˵����ʱʱ���ѵ�
    }
    else
    {
        return NoTimeOut;  //���ǵĻ�˵����ʱʱ�仹û��
    }
}


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

