/*****at24c02头文件*****/

#ifndef _AT24C02_H_
#define _AT24C02_H_
#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int
	
sbit sda=P0^1;
sbit scl=P0^2;

void atStart();
void atStop();
void atResponse();
void atWrite(uchar dat);
uchar atRead();
void atWriteData(uchar addr,uchar dat) ;
uchar atReadData(uchar addr);
extern void lcdDelay(uint x);

void atStart()   //at24开始信号
{
	sda=1;
	_nop_();
	_nop_();
	scl=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	sda=0;
	_nop_();
	_nop_();
}

void atStop()  //at停止信号
{
	sda=0;
	_nop_();
	_nop_();
	scl=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	sda=1;
	_nop_();
	_nop_();
}

void atResponse()  //at应答信号
{
	uchar i;
	scl=1;
	_nop_();
	_nop_();
	while((sda=1)&&(i<250))
		i++;
	scl=0;
	_nop_();
	_nop_();
}


void atWrite(uchar dat)   //写一个字节数据
{
	uchar i;
	scl = 0;
	for(i=0;i<8;i++)
	{
		sda = (bit)(dat&0x80);  //最高位赋值写法
		_nop_();
		scl = 1;
		_nop_();
		_nop_();
		scl = 0;
		dat<<=1;
	}
}


uchar atRead()   //读一个字节数据
{
	uchar i,j;
	for(i=0;i<8;i++)
	{
		scl = 1;
		j=(j<<1)|sda;
		scl = 0;
	}
	return j;
}

void atWriteData(uchar addr,uchar dat)     //向addr地址写入数据
{
	atStart();
	atWrite(0xa0);
	atResponse();
	atWrite(addr);
	atResponse();
	atWrite(dat);
	atResponse();
	atStop();
	lcdDelay(2);
}

uchar atReadData(uchar addr)
{
	uchar dat;
	atStart();			 
	atWrite(0xa0); 		  
	atResponse();			   
	atWrite(addr);
	atResponse();			   
	atStart();			   
	atWrite(0xa1);		   
	atResponse();			   
	dat=atRead(); 		   
	atStop();
	lcdDelay(2);
	return dat;
}