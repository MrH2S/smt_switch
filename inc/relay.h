#ifndef _RELAY_H_
#define _RELAY_H_
/*�̵�����������*/

#include <reg52.h>
/*---------port def-----------*/
sbit RELAY=P0^5;

extern void relay_on(void);
extern void relay_off(void);

#endif