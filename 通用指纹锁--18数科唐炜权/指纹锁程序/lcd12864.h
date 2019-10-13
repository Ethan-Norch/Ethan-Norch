/*****LCD2864ͷ�ļ�*****/

#ifndef _LCD12864_H_
#define _LCD12864_H_
#include <reg52.h> 
#include<intrins.h>  

#define uchar unsigned char
#define uint  unsigned int
	
#define lcd P2    //���Ŷ���
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

void lcdDelay(uint x)   //��ʱ����
{
	uint i,j;
	for(j=0;j<x;j++)
		for(i=0;i<120;i++);
}


uchar lcdCheckBusy()  //��æ����
{
	uchar busy;
	lcd=0xff;
	RS = 0;
	RW = 1;
	E = 1;
	_nop_();  //��ʱһ����е���ڣ�1us
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
	
void lcdWriteData(uchar dat)  //д����
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


void lcdDisplayLine(uchar x,uchar y)    //lcd��ʾ����
{
	uchar add;
	if(y==1)
		add = 0x80+x;   //�ڵ�һ����ʾ
	else
		if(y==2)
			add = 0x90+x;   //�ڵڶ�����ʾ
		else
			if(y==3)
				add = 0x88+x;   //�ڵ�������ʾ
			else
				if(y==4)
					add = 0x98+x;     //�ڵ�������ʾ
	lcdWriteCom(add);        //д����ʾ��ַ
}
		

void lcdDisplayChar(uchar x,uchar y,uchar dat)   //lcd��ʾ�ַ�����
{
	lcdDisplayLine(x,y);
	lcdWriteData(dat);
}


void lcdDisplayString(uchar x,uchar y,uchar *s)    //��ʾ�ַ���
{
	lcdDisplayLine(x,y);
	while(*s!='\0')
	{
		lcdWriteData(*s);
		s++;
		lcdDelay(1);
	}
}


void lcdWriteWhite(uchar x,uchar y,uchar num,bit mode)  //����--��ɫ�Ե�
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


void lcdClear()    //ȫ����ͼ
{
	uchar i;
	for(i=0;i<5;i++)
		lcdWriteWhite(0,i,16,0);
}

void lcdInit()
{
	lcdWriteCom(0x30);       //ѡ�����ָ�
  lcdWriteCom(0x30);       //ѡ��8bit������
  lcdWriteCom(0x0c);       //����ʾ(���αꡢ������)
  lcdWriteCom(0x01);       //�����ʾ�������趨��ַָ��Ϊ00H
  lcdWriteCom(0x06);       //ָ�������ϵĶ�ȡ��д��ʱ���趨�α���ƶ�����ָ����ʾ����λ�������������1λ�ƶ� 
  lcdClear();
}


#endif