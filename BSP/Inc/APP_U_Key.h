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
 * 该文件用于定义IO口名和按键名，非系统函数所需，可以不定义。
 *
 */
#ifndef __APP_U_Key_h__
#define	__APP_U_Key_h__


/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------以下是模块的初始化定义区---------------------------------                                 *
*                                                                                                                                           *
********************************************************************************************************************************************/
//定义按键IO口（可以不定义，但在用户代码中需要使用MCU的寄存器名来写用户代码）


//定义按键名（按键名用户自定义，参数范围0~255）
#define MC           0  //自检
#define SWUP         1  //上调
#define SWDOWN       2  //下调
#define SWUP_SWDOWN  3  //上调和下调同时按下
#define SZD          4  //手自动
#define ENTER        5  //确认键
#define MENU         6  //菜单按键


/********************************************************************************************************************************************
*                                                                                                                                           *
*                ---------------------------------以下是模块的系统函数代码区---------------------------------                               *
*                                                                                                                                           *
********************************************************************************************************************************************/


/********************************************************************************************************************************************
*                                                                                                                                           *
*               ---------------------------------以下是模块的用户函数代码区---------------------------------                                *
*                                                                                                                                           *
********************************************************************************************************************************************/


#endif
