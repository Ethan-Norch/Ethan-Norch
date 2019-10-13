/*****按键头文件*****/


#ifndef _KEY_H_
#define _KEY_H_
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
	
#define Key P1  //矩阵按键P1
bit keyFlag;  //按键按下标志

uchar keyParser(uchar key);
void keyDelay();
uchar keyScan();


uchar keyParser(uchar key)  //按键解析--确定按键
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

void keyDelay()    //延时函数
{
	uchar n,m;
	for(n=100;n>0;n--)
		for(m=300;m>0;m--);
}


uchar keyScan()   //按键扫描程序 P1.0--P1.3为行线 P1.4--P1.7为列线
{
	uchar rcode, ccode;
	Key = 0xF0;      // 发全0行扫描码，列线输入
	if((Key&0xF0) != 0xF0) // 若有键按下
	{
		keyDelay();// 延时去抖动 
		if((Key&0xF0) != 0xF0)
		{  
			rcode = 0xFE;         // 逐行扫描初值
		    while((rcode&0x10) != 0)
		    {
		        Key = rcode;         // 输出行扫描码
			    if((Key&0xF0) != 0xF0) // 本行有键按下
			    {
						ccode = (Key&0xF0)|0x0F;
						do{;}
						while((Key&0xF0) != 0xF0); //等待键释放
						return keyParser((~rcode) + (~ccode)); // 返回键编码
			    }
			    else
						rcode = (rcode<<1)|0x01; // 行扫描码左移一位
			}
		}
	}  
	return 0; // 无键按下，返回值为0
}

#endif