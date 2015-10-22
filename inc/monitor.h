#ifndef _MONITOR_H_
#define _MONITOR_H_
/*双数码管显示驱动程序  led指示灯驱动程序*/
#include <type.h>
#include <reg52.h>
/*----------port def----------*/
sbit DIO=P2^0;
sbit RCK=P2^1;
sbit SCK=P2^2;
/*----------port def----------*/
sbit DIO2=P2^3;
sbit RCK2=P2^4;
sbit SCK2=P2^5;



/*---------interface def--------*/
/*@pos 数码管位数
  @num 数码管单位显示数值*/
extern void monitor_display(u8 pos,u8 num1);//数码管1  时间显示
extern void monitor2_display(u8 pos,u8 num2);//数码管2   通断状态显示

extern void delay(u16 n);

//extern bool FLASH_STATE;
extern u8 num1[4];
extern u8 num2[4];

sbit LED9 = P0^0;//低电平有效


//c文件中定义符号symbol      
//1 h文件中extern暴露接口 在其他文件中include h文件  来使用其他c文件中定义的symbol
//2 或者直接在引用处使用extern声明                                                             
#endif