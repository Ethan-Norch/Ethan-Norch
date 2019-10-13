/*****LCD2864头文件*****/

#ifndef _LCD12864_H_
#define _LCD12864_H_
#include <reg52.h> 
#include<intrins.h>  

#define uchar unsigned char
#define uint  unsigned int
	
#define lcd P2    //引脚定义
sbit RS  =P3^5;	  
sbit RW  =P3^4;	  
sbit E   =P3^3;
void lcdDelay(uint x);
uchar lcdCheckBusy();
void lcdWriteCom(uchar com);
void lcdWriteData(uchar dat);
void lcdDisplayLine(uchar x,uchar y);
void lcdDisplayChar(uchar x,uchar y,uchar dat);
void lcdDisplayString(uchar x,uchar y,uchar *s);
void lcdWriteWhite(uchar x,uchar y,uchar num,bit mode);
void lcdClear();
void lcdInit();

void lcdDelay(uint x)   //延时函数
{
	uint i,j;
	for(j=0;j<x;j++)
		for(i=0;i<120;i++);
}


uchar lcdCheckBusy()  //读忙函数
{
	uchar busy;
	lcd=0xff;
	RS = 0;
	RW = 1;
	E = 1;
	_nop_();  //延时一个机械周期，1us
	busy=lcd&0x80;
	E = 0;
	return busy;
}

void lcdWriteCom(uchar com)
{
	while(lcdCheckBusy());
	RS = 0;
	RW = 0;
	E = 0;
	_nop_();
	_nop_();
	lcd = com;
	E = 1;
	_nop_();
	_nop_();
	E = 0;
}
	
void lcdWriteData(uchar dat)  //写数据
{
	while(lcdCheckBusy());
	RS = 1;
	RW = 0;
	E = 0;
	_nop_();
	_nop_();
	lcd = dat;
	E = 1;
	_nop_();
	_nop_();
	E = 0;
}


void lcdDisplayLine(uchar x,uchar y)    //lcd显示行数
{
	uchar add;
	if(y==1)
		add = 0x80+x;   //在第一行显示
	else
		if(y==2)
			add = 0x90+x;   //在第二行显示
		else
			if(y==3)
				add = 0x88+x;   //在第三行显示
			else
				if(y==4)
					add = 0x98+x;     //在第四行显示
	lcdWriteCom(add);        //写入显示地址
}
		

void lcdDisplayChar(uchar x,uchar y,uchar dat)   //lcd显示字符》》
{
	lcdDisplayLine(x,y);
	lcdWriteData(dat);
}


void lcdDisplayString(uchar x,uchar y,uchar *s)    //显示字符串
{
	lcdDisplayLine(x,y);
	while(*s!='\0')
	{
		lcdWriteData(*s);
		s++;
		lcdDelay(1);
	}
}


void lcdWriteWhite(uchar x,uchar y,uchar num,bit mode)  //反白--颜色对调
{
	uchar add,i,j;
	if(y%2==1)
		add=0x80;
	else
		if(y%2==0)
			add=0x90;
		
	lcdWriteCom(0x34);
	lcdWriteCom(0x36);
	for(i=0;i<16;i++)
	{
		lcdWriteCom(add+i);
		if(y>2)
			lcdWriteCom(0x88+x/2);
		else
			lcdWriteCom(0x80+x/2);
		if(x%2==1)
			lcdWriteData( 0x00 );	

		for(j=0;j<num;j++)
		{
			if(mode==1)
				lcdWriteData( 0xff );
			else
				lcdWriteData( 0x00 );
		}
	}
	lcdWriteCom( 0x30 ) ;
}


void lcdClear()    //全屏绘图
{
	uchar i;
	for(i=0;i<5;i++)
		lcdWriteWhite(0,i,16,0);
}

void lcdInit()
{
	lcdWriteCom(0x30);       //选择基本指令集
  lcdWriteCom(0x30);       //选择8bit数据流
  lcdWriteCom(0x0c);       //开显示(无游标、不反白)
  lcdWriteCom(0x01);       //清除显示，并且设定地址指针为00H
  lcdWriteCom(0x06);       //指定在资料的读取及写入时，设定游标的移动方向及指定显示的移位，光标从右向左加1位移动 
  lcdClear();
}


#endif