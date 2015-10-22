#include <keys.h>
#include <reg52.h>
#include <time.h>
#include <monitor.h>

void key_init(void){

	//下降沿
	IT0=1;
	IT1=1;
	IT2=1;

	EX0=1;
	EX1=1;
	EX2=1;

}

//MODE_NM:正常运行模式    false
//MODE_WRITE:设定时刻模式 true
//typedef enum{MODE_NM,MODE_WRITE=!MODE_NM} MODE;
//MODE PROG_MODE=MODE_NM;

bool PROG_MODE=false;

u8	time_index=0;//设定时间索引
//0              1 2 3-----10
//current_time   user_time[0]----user_time[9]
//1              2 3 4 ----11

TIME_TYPE time_buf={0,0,0};//按键输入时间信息缓存
bool state_buf=false;//按键输入通断信息缓存

//KEY_CHOS 0   1   2   3   4
//          min     hour   state
//最开始位于数码管最低位，按一次向上一位（循环）
u8 chos_count=0;

//KEY_MODE
void MODE_Handler(void) interrupt 0 {
   while(KEY_MODE==0);
	if (PROG_MODE==true)
	{
		if (time_index==0)
		{
			current_time=time_buf;//初始化当前时间
			timer_start();
		}else{
			(user_time+time_index-1)->time=time_buf;//设定通断时间表
			(user_time+time_index-1)->state=state_buf;
		}
		time_index++;//次数太多造成数组越界！！！！
		//设定完成后缓存  显示清零
		num1[0]=0;	
	  num1[1]=0;
	  num1[2]=0;
	  num1[3]=0;
		
		LED9=1;
		
		chos_count=0;
		
		time_buf.min=0;
		time_buf.hour=0;
		state_buf=false;
	}
	PROG_MODE=!PROG_MODE;
	
}



void CHOS_Handler(void) interrupt 2 {
	while(KEY_CHOS==0);//消抖
	if (PROG_MODE==true)
	{
		chos_count++;
		if (chos_count>=5)
		{
			chos_count=0;
		}
	}
}

//KEY_STEP
void STEP_Handler(void) interrupt 6 {
	while(KEY_STEP==0);//消抖
	//num1[4]={time_buf.min%10,time_buf.min/10,time_buf.hour%10,time_buf.hour/10};
	
	if (PROG_MODE==true)
	{
		switch(chos_count){
			case 0:
				time_buf.min++;
				if (time_buf.min>=60)
				{
					time_buf.min=0;
					time_buf.hour++;
				}
			break;
			case 1:
				time_buf.min=time_buf.min+10;
				if (time_buf.min>=60)
				{
					time_buf.min=0;
					time_buf.hour++;
				}
			break;
			case 2:
				time_buf.hour++;
				if (time_buf.hour>=24)
				{
					time_buf.hour=0;
				}
			break;
			case 3:
				time_buf.hour=time_buf.hour+10;
				if (time_buf.hour>=24)
				{
					time_buf.hour=0;
				}
			break;
			case 4:
				if(time_index>=1){
			  	state_buf=!state_buf;
		  		if (state_buf)
		  		{
		  			LED9=0;//亮--通
		  		}else{
		  			LED9=1;//灭--断
		  		}
				}
			break;
		}
		num1[0]=time_buf.min%10;
		num1[1]=time_buf.min/10;
		num1[2]=time_buf.hour%10;
		num1[3]=time_buf.hour/10;
	}
	
}