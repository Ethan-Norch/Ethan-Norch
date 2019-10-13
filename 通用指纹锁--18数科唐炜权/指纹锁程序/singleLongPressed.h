#ifndef _SINGLELONGPRESSED_H_
#define _SINGLELONGPRESSED_H_

#include "reg52.h"
#define uchar unsigned char

sbit  key=P2^4;

void delayms(uint ms)
{
	uchar i=100,j;
	for(;ms;ms--)
	{
		while(--i)
		{
			j=10;
			while(--j);
		}
	}
}
uchar keypro()
{
	static uchar pressFlag;
	if(!key)
	{
		delayms(10);
		if(!key)
		{
			pressFlag=1;
			TR0=1;
			while(!key);
			TR0=0;
		}
	}