/*
	使用timer 0
	16位计数模式 
*/

#ifndef _TIME_H_
#define _TIME_H_

#include <type.h>

typedef struct
{
	u8 hour;
    u8 min;
    u8 sec;
} TIME_TYPE;

typedef struct
{
	TIME_TYPE time;
    bool state;
} USER_TIME_TYPE;


extern TIME_TYPE current_time;
extern USER_TIME_TYPE user_time[10];


extern void timer_init(void);
extern void timer_start(void);
extern void timer_stop(void);



#endif