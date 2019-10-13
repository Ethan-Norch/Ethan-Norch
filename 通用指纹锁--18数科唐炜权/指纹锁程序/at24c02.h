/*****at24c02ͷ�ļ�*****/

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

void atStart()   //at24��ʼ�ź�
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

void atStop()  //atֹͣ�ź�
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

void atResponse()  //atӦ���ź�
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


void atWrite(uchar dat)   //дһ���ֽ�����
{
	uchar i;
	scl = 0;
	for(i=0;i<8;i++)
	{
		sda = (bit)(dat&0x80);  //���λ��ֵд��
		_nop_();
		scl = 1;
		_nop_();
		_nop_();
		scl = 0;
		dat<<=1;
	}
}


uchar atRead()   //��һ���ֽ�����
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

void atWriteData(uchar addr,uchar dat)     //��addr��ַд������
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