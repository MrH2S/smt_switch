#ifndef _KEY_H_
#define _KEY_H_
#include <reg52.h>
/*---------------register def-------------------*/
sfr P4=0XE8;
sbit INT2=P4^3;
sbit INT3=P4^2;

sfr XICON=0XC0;
sbit PX3 = XICON^7;
sbit EX3 = XICON^6;
sbit IE3 = XICON^5;
sbit IT3 = XICON^4;
sbit PX2 = XICON^3;
sbit EX2 = XICON^2;
sbit IE2 = XICON^1;
sbit IT2 = XICON^0;

typedef enum {MODE,CHOS,STEP} KEY_TYPE;

/*-------------------port def-------------------*/
sbit KEY_MODE =P3^2;//INT0
sbit KEY_CHOS =P3^3;//INT1
sbit KEY_STEP =P4^3;//INT2




extern void key_init(void);

#endif