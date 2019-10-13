/*****单片机中断头文件*****/
#ifndef _TIMER2_H_
#define _TIMER2_H_
#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

//sfr T2MOD   = 0xC9;
uint  T2_num=0;            //定时器1计数变量

sbit jdq=P3^6;  //继电器

void T2_init()
{
	RCAP2H=(65536-50000)/256; 
	RCAP2L=(65536-50000)%256; //自动重装 
	TH2=RCAP2H; 
	TL2=RCAP2L; //定时器2赋初值 
	T2CON=0; //配置定时器2控制寄存器，这里其实不用配置，T2CON上电默认就是0，这里赋值只是为了演示这个寄存器的配置 
	T2MOD=0; //配置定时器2工作模式寄存器，这里其实不用配置，T2MOD上电默认就是0，这里赋值只是为了演示这个寄存器的配置 
	EA=1;                  //开总中断
	ET2=1;                 //定时器T0中断允许      
	TR2=0;				   //开定时器
}

void T2_interrupt(void) interrupt 5    //50ms
{
	TF2=0; 
	 
	T2_num++;
	if(T2_num==200)//如果1S未定时完成
	{
		T2_num=0;
		jdq=1;
		TR2=0;	
	} 
}
#endif