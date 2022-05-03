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
 * ��ģ���ǰ���ģ�飬ʹ�ò������£�
 * 1.��"APP_U_Key.c"�ļ����"APP_Key_Init"���������ð������IO�ڣ���������Ŀ��ѭ��֮ǰ���������ɨ�谴����������ҪƵ���ı�IO�ڷ���Ļ��������ò���
 * 2.��"APP_U_Key.h"�ļ����Զ��尴������IO������
 * 3.��"APP_U_Key.c"�ļ����"Key_CurrentTime_ms"��"Key_TimingQuery_30ms"��"Key_TimingQuery_3s"���������ڱ�д��ʱ���롣
 * 4.��"APP_U_Key.c"�ļ����"Key_Check"�����ڱ�д����ɨ����롣
 * 5.��"APP_U_Key.c"�ļ����"Key_Task"�����ڱ�д����������롣
 * 6.��"APP_Key_Scanning"����������Ŀ��ѭ����������ɷ�ʱ�����Ҫ��"APP_Key_CurrentState"������Ϲ����������ʵʱ����Ϳ��Ե���������
 *
 */
#ifndef __APP_S_Key_h__
#define	__APP_S_Key_h__

typedef volatile unsigned char vu8;
/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------������ģ��ĳ�ʼ��������---------------------------------                                 *
*                                                                                                                                           *
********************************************************************************************************************************************/
#define PressDown    0  //����
#define NoPressDown  1  //û��

#define SharedTask          0  //��ͬ����
#define PressDownOnce       1  //�㶯
#define PressDownStabilize  2  //����

#define AwaitOrders               0  //����
#define PressDownDispelDithering  1  //����ȥ��
#define CheckPressDownMode        2  //��ⰴ�·�ʽ
#define WaitUnclinch              3  //�ȴ�����
#define UnclinchDispelDithering   4  //����ȥ��

#define NoTimeOut  0  //ʱ�仹û��
#define TimeOut    1  //ʱ�䵽

#define Free  0  //����
#define Busy  1  //æµ

#define HangInTheAir      0  //��������δִ�����
#define HasBeenCompleted  1  //����������ִ�����


extern vu8 KeyStatus;  //������ǰ�Ĺ���״̬


/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------������ģ���ϵͳ����������---------------------------------                               *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* ��������  APP_Key_Scanning
* ��������������ɨ��
* ��ڲ�������
* ���ڲ�������
* ע������ú������������Ŀ��ѭ���ڣ�������ģ�鱻����ɷ�ʱ������������
*           Ҫ���"APP_Key_CurrentState"����һ������������ǰ���ģ�鹤����
*           ʱ�μ�������ģ�鴦��æµ״̬�Ļ�����ô��Ҫ�ð���ģ��һֱ������
*           ����״̬Ϊֹ�����������������Ϊ����ģ�����Լ��Ĺ���ʱ�λ�δ���
*           ����ͳ�����ʱ�Σ����Ծ����ǿ�ʱ�ι���ҲҪ������ʣ��Ĺ�����ɣ�
*           ��������ʵʱ����Ļ��Ϳ��Ե���������
* �޸ļ�¼����
*           2016/9/29 BY:����
***************************************************************************/
extern void APP_Key_Scanning(void);


/***************************************************************************
* ��������  APP_Key_CurrentState
* ��������������ģ��ĵ�ǰ״̬
* ��ڲ�������
* ���ڲ�����Free����ǰ����ģ�鴦�ڿ���״̬
*           Busy����ǰ����ģ�鴦��æµ״̬
* ע�����������ģ�鱻����ɷ�ʱ���������²���Ҫ�ú������"APP_Key_Scanning"
*           ����һ������������ǰ���ģ�鹤����ʱ�μ�������ģ�鴦��æµ״
*           ̬�Ļ�����ô��Ҫ�ð���ģ��һֱ����������״̬Ϊֹ���������������
*           ��Ϊ����ģ�����Լ��Ĺ���ʱ�λ�δ�������ͳ�����ʱ�Σ����Ծ�����
*           ��ʱ�ι���ҲҪ������ʣ��Ĺ�����ɣ���������ʵʱ����Ļ��Ϳ���
*           ��"APP_Key_Scanning"������������������Ҫ�ú�����
* �޸ļ�¼����
*           2016/9/29 BY:����
***************************************************************************/
extern u8 APP_Key_CurrentState(void);


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------������ģ����û�����������---------------------------------                                *
*                                                                                                                                           *
********************************************************************************************************************************************/
/***************************************************************************
* ��������  APP_Key_Init
* ��������������ģ���ʼ��
* ��ڲ�������
* ���ڲ�������
* ע����������밴����ص�IO�ڣ������ɨ�谴��������IO��ҪƵ���ظı䷽���
*           �����磺���Ͱ���ɨ�裩����Ҫ��IO������д��"Key_Check"�����У���
*           �����Ǹú�����������õ��ú�������������ѭ��֮ǰ��
* �޸ļ�¼����
*           2016/9/29 BY:����
***************************************************************************/
extern void APP_Key_Init(void);


#endif