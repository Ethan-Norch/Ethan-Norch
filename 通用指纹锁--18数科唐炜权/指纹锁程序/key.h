/*****����ͷ�ļ�*****/


#ifndef _KEY_H_
#define _KEY_H_
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
	
#define Key P1  //���󰴼�P1
bit keyFlag;  //�������±�־

uchar keyParser(uchar key);
void keyDelay();
uchar keyScan();


uchar keyParser(uchar key)  //��������--ȷ������
{
	uchar n;
	switch(key)
	{
		case 0x11: n= 15; break;
	  case 0x21: n= 12; break;
	  case 0x41: n= 11; break;
	  case 0x81: n= 10; break;
	  case 0x12: n= 14; break;
	  case 0x22: n= 9; break;
	  case 0x42: n= 6; break;
	  case 0x82: n= 3; break;
	  case 0x14: n= 0; break;
	  case 0x24: n= 8; break;
	  case 0x44: n= 5; break;
	  case 0x84: n= 2; break;
	  case 0x18: n= 13; break;
	  case 0x28: n= 7; break;
	  case 0x48: n= 4; break;
	  case 0x88: n= 1; break;
		default: break;
	}
	keyFlag = 1;
	return n;
}

void keyDelay()    //��ʱ����
{
	uchar n,m;
	for(n=100;n>0;n--)
		for(m=300;m>0;m--);
}


uchar keyScan()   //����ɨ����� P1.0--P1.3Ϊ���� P1.4--P1.7Ϊ����
{
	uchar rcode, ccode;
	Key = 0xF0;      // ��ȫ0��ɨ���룬��������
	if((Key&0xF0) != 0xF0) // ���м�����
	{
		keyDelay();// ��ʱȥ���� 
		if((Key&0xF0) != 0xF0)
		{  
			rcode = 0xFE;         // ����ɨ���ֵ
		    while((rcode&0x10) != 0)
		    {
		        Key = rcode;         // �����ɨ����
			    if((Key&0xF0) != 0xF0) // �����м�����
			    {
						ccode = (Key&0xF0)|0x0F;
						do{;}
						while((Key&0xF0) != 0xF0); //�ȴ����ͷ�
						return keyParser((~rcode) + (~ccode)); // ���ؼ�����
			    }
			    else
						rcode = (rcode<<1)|0x01; // ��ɨ��������һλ
			}
		}
	}  
	return 0; // �޼����£�����ֵΪ0
}

#endif