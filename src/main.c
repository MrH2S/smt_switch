#include <time.h>
#include <reg52.h>
#include <keys.h>
#include <monitor.h>
#include <relay.h>

/*user manual：
1.第一次按下mode：设定当前时间，第二次按下mode确认设定值
2.第三次按下mode：设定第一个通断时间，第四次按下确认设定值
3.。。。同步骤2  最多10个通断时间设定
4.当到达指定时间时会进行设定好的通断电操作
*/

void main(void)
{  
	relay_on();
	
	num1[0]=0;	
	num1[1]=0;
	num1[2]=0;
	num1[3]=0;
	
	num2[0]=0;	
	num2[1]=0;
	num2[2]=0;
	num2[3]=0;

	
	//开启中断开关
	EA=1;
  timer_init();
	key_init();
	while(1){
		
		monitor_display(0X1,num1[0]);
		monitor_display(0X2,num1[1]);
		monitor_display(0X4,num1[2]);
		monitor_display(0X8,num1[3]);
		
		//当前时间显示
	  monitor2_display(0x1,num2[0]);
	  monitor2_display(0x2,num2[1]);
	  monitor2_display(0x4,num2[2]);
	  monitor2_display(0x8,num2[3]);
		
	};
	
}