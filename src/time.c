#include <time.h>
#include <reg52.h>
#include <keys.h>
#include <relay.h>
#include <monitor.h>
#include <type.h>
void timer_init(void){
   //16计数模式 timer 0
	//8无中断信号！！！
	TMOD=0X01;
	TH0=0X3C;
	TL0=0XAF;
	ET0=1;
}

//开始计数
void timer_start(void){

	TR0=1;
}

//停止计数
void timer_stop(void){

	TR0=0;
}

u8 timer_overflow_count=0;
extern u8 time_index;
TIME_TYPE current_time={0,0,0};
USER_TIME_TYPE user_time[10];

u8 i=0;//中断服务函数  访问全局变量  不能定义局部变量
void timer_handler(void) interrupt 1 {
	TH0=0X3C;
	TL0=0XAF;

	//当前时间更新
	timer_overflow_count++;
	if (timer_overflow_count>=20)
	{
		timer_overflow_count=0;
		current_time.sec++;
		if (current_time.sec>=60)
		{
			current_time.sec=0;
			current_time.min++;
			if (current_time.min>=60)
			{
				current_time.min=0;
				current_time.hour++;
				if (current_time.hour>=24)
				{
					current_time.hour=0;
				}
			}
		}
	}
	
	//num显示更新
  num2[0]=current_time.min%10;
	num2[1]=current_time.min/10;
	num2[2]=current_time.hour%10;
	num2[3]=current_time.hour/10;
	
  //时间检测
	for (i=0;i < time_index-1;++i)
	{
		if (current_time.min==((user_time+i)->time).min&&
			  current_time.hour==((user_time+i)->time).hour)
		{
			
			if ((user_time+i)->state)
			{
			    relay_on();
				  LED2=0;
			}else{
				  relay_off();
				  LED2=1;
			}
		}
	}
}

