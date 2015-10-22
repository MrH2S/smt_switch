#include <monitor.h>
#include <type.h>
/*该数码管需要一次性输入4位 数值位置信息  为输入默认为0
所以每次更改显示     需要同时输入未更改的信息
*/
/*----------data def----------*/
             //  0    1    2     3   4    5    6     7   8    9    A    B     C   D    E    F    -
u8 code num[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf};
/*
void monitor_write(u8 byte){
	u8 i;
	for(i=0;i<8;i++){
		if ((byte&0X80)==1)
		{
			DIO=1;
		}else{
			DIO=0;
		}
		byte<<=1;
		SCK=0;
		SCK=1;
	}
}
*/

void monitor_write(u8 byte)
{
  u8 i;
	for(i=8;i>=1;i--)
	{
		if (byte&0x80) DIO=1; else DIO=0;
		byte<<=1;
		SCK = 0;
		SCK = 1;
	}
}
/*
void monitor2_write(u8 byte){
  u8 i;
	for(i=0;i<8;i++){
		  if ((byte&0X80)==1)
		  {
		  	DIO2=1;
	  	}else{
	  		DIO2=0;
	  	}
		  byte<<=1;
		  SCK2=0;
	  	SCK2=1;
  }
}
*/


void monitor2_write(u8 byte)
{
	u8 i;
	for(i=8;i>=1;i--)
	{
		if (byte&0x80) DIO2=1; else DIO2=0;
		byte<<=1;
		SCK2 = 0;
		SCK2 = 1;
	}
}

//数码管1 2显示值
u8 num1[4];
u8 num2[4];
//@pos 0X01 0X02 0X04 0X08
//@num1 :0-17
//每次写入会导致其他位显示消失--该数码管"同一时刻"只能显示一位
void monitor_display(u8 pos,u8 num1){
	u8 code* table;
	table=num+num1;
	//写入当前的笔画
	monitor_write(*table);
	monitor_write(pos);
	RCK=0;
	RCK=1;
}

void monitor2_display(u8 pos,u8 num2){
	  u8 code* table;
	  table=num+num2;
	  monitor2_write(*table);
    monitor2_write(pos);
    RCK2=0;
    RCK2=1;
}

//12M  ms

void delay(u16 n){ 
	u16 i=0,j=0;
	for(i=0;i<n;i++) 
	for(j=0;j<123;j++); 
} 
/*
bool FLASH_STATE =true;

void monitor_flash(u8 pos){
	u8 position;
  switch(pos){
		case 0X1:
			position =0;
		break;
		case 0X2:
			position =1;
		break;
		case 0X4:
			position =2;
		break;
		case 0X8:
			position =3;
		break;
	}
	while(FLASH_STATE){
		monitor_display(pos,num1[position]);//显示原值
		delay(500);
		monitor_display(pos,16);//显示-
		delay(500);
	}
}

void monitor2_flash(u8 pos){
  u8 position;
  switch(pos){
		case 0X1:
			position =0;
		break;
		case 0X2:
			position =1;
		break;
		case 0X4:
			position =2;
		break;
		case 0X8:
			position =3;
		break;
	}
	while(FLASH_STATE){
		monitor2_display(pos,num2[position]);//显示原值
		delay(500);
		monitor2_display(pos,16);//显示-
		delay(500);
	}
}

*/

