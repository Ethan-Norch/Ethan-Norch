/*****��Ƭ���ж�ͷ�ļ�*****/
#ifndef _TIMER2_H_
#define _TIMER2_H_
#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

//sfr T2MOD   = 0xC9;
uint  T2_num=0;            //��ʱ��1��������

sbit jdq=P3^6;  //�̵���

void T2_init()
{
	RCAP2H=(65536-50000)/256; 
	RCAP2L=(65536-50000)%256; //�Զ���װ 
	TH2=RCAP2H; 
	TL2=RCAP2L; //��ʱ��2����ֵ 
	T2CON=0; //���ö�ʱ��2���ƼĴ�����������ʵ�������ã�T2CON�ϵ�Ĭ�Ͼ���0�����︳ֵֻ��Ϊ����ʾ����Ĵ��������� 
	T2MOD=0; //���ö�ʱ��2����ģʽ�Ĵ�����������ʵ�������ã�T2MOD�ϵ�Ĭ�Ͼ���0�����︳ֵֻ��Ϊ����ʾ����Ĵ��������� 
	EA=1;                  //�����ж�
	ET2=1;                 //��ʱ��T0�ж�����      
	TR2=0;				   //����ʱ��
}

void T2_interrupt(void) interrupt 5    //50ms
{
	TF2=0; 
	 
	T2_num++;
	if(T2_num==200)//���1Sδ��ʱ���
	{
		T2_num=0;
		jdq=1;
		TR2=0;	
	} 
}
#endif