#include "reg52.h"
#include "lcd12864.h"
//#include "at24c02.h"
#include "as608.h"
#include "timer2.h"
#define uchar unsigned char
#define uint unsigned int

sbit beep=P3^7;
sbit led=P0^0;
sbit key=P1^0;

#define max 100
uchar mode=0;       //0normal unlock,1add,2init,3delete
uint id=0;          //save enter id
bit fpF=0;          //mark the fingerprint collection
bit zhiwenF=0;
bit delF=0;
bit longP=0;
bit pressFlag;

/*********************************************************
函数名称:delayms(uint ms)
函数作用: 延时函数
参数说明:延时ms毫秒
*********************************************************/
void delayms(uint ms)
{
	uchar i;
	while(ms--)
	{
		for(i=0;i<80;i++);
	}
		
}

/*********************************************************
函数名称:keypro()
函数作用:按键处理函数
参数说明:短按、长按
*********************************************************/
void keypro()
{
	if(key==0)
	{
		delayms(10);
		if(!key)
		{
			pressFlag=1;
			while(!key)
			{
				delayms(2500);
				if(!key)
					longP=1;
			}
		}
	}
}
		
/*********************************************************
函数名称:beeping(uchar i)
函数作用:报警声
参数说明:连续响i声
*********************************************************/
void beeping(uchar i)    //loop for i times,the beep beeps i times
{
	uchar j;
	for(j=0;j<i;j++)
	{
		beep=0;
		led=0;
		delayms(40);
		beep=1;
		led=1;
		delayms(40);
	}
}

/*********************************************************
函数名称:cucun()
函数作用:储存一个指纹
参数说明:
*********************************************************/
void cucun()
{
	lcdWriteCom(0x01);
	lcdDisplayString(0,1,"ADD FINGERPRINT");
	delayms(500);
	if(enroll()==1)
	{
		id++;
		if(savefingure(id)==1)
		{
			lcdDisplayString(3,2,"SAVED");
			delayms(2000);
			lcdWriteCom(0x01);
		}
		else
		{
			lcdDisplayString(0,2,"SAVING FAIL");
			delayms(1000);
			lcdWriteCom(0x01);
			id--;
		}
	}
	else
	{
		lcdDisplayString(0,2,"COLLECTING FAIL");
		delayms(1000);
		lcdWriteCom(0x01);
	}
	zhiwenF=0;
	mode=0;
}

/*********************************************************
函数名称:shanchu()
函数作用:删除所有指纹
参数说明:
*********************************************************/
void shanchu()
{
	lcdWriteCom(0x01);
	if(Clear_All()==1)
	{
		lcdDisplayString(1,1,"ALL DELETED");
	  delayms(2000);
		lcdWriteCom(0x01); 
		mode=2;
		id=0;
	}
  else
	{
		lcdDisplayString(1,1,"DELETE FAIL");
		delayms(1000);
		lcdWriteCom(0x01);
		mode=0;
	}
} 

/*********************************************************
函数名称:fpsearch()
函数作用:搜索指纹开锁
参数说明:
*********************************************************/
void fpSearch()
{
	searchNum=search();     //search fp
	if((searchNum>=1&&searchNum<=max)||searchNum==255)     //maximum
	{
		if(searchNum>=1&&searchNum<=max)    //success
		{
			jdq=0;
			T2_num=0;           //recounting
			TR2=1;
			lcdWriteCom(0x01);
			lcdDisplayString(0,1,"    WELCOME");
			delayms(2000);
			lcdWriteCom(0x01);
		}
		else     //wrong
		{
			beeping(3);
		}
		delayms(500);
	}
	mode=0;
}


void main()
{
	lcdInit();
	UartInit();
	T2_init();
	mode=2;
	while(1)
	{
		if(mode==1&&zhiwenF==1)
			cucun();
		if(mode==3&&delF==1)
			shanchu();
		if(mode==2)
		{
			lcdDisplayString(1,1,"INITIATING...");
			lcdDisplayString(0,2,"SET FINGERPRINT");
			delayms(500);
			if(enroll()==1)
			{
				lcdDisplayString(0,3,"COMMUNICATING>>>");
				id++;
				if(savefingure(id)==1)
				{
					lcdWriteCom(0x01);
					lcdDisplayString(0,1,"SETTING SUCCESS");
					delayms(2000);
					lcdWriteCom(0x01);
					mode=0;
				}
				else
				{
					id=0;
					lcdWriteCom(0x01);
					lcdDisplayString(1,1,"SETTING FAILURE");
				}
			}
			else
			{	
				lcdWriteCom(0x01);
				lcdDisplayString(1,1,"COLLECTING FAIL");
			}
		}
		else
			if(mode!=2)
			{
				keypro();
				if(pressFlag==1&&(!longP))
				{
					pressFlag=0;
					mode=1;
					lcdWriteCom(0x01);
					lcdDisplayString(1,1,"ADD FINGER");
					lcdDisplayString(0,2,"COMMUNICATING>>>");
					while(1)
					{
						searchNum=search();
					  if((searchNum>=1&&searchNum<=max)||searchNum==255)
					  {
						  if(searchNum>=1&&searchNum<=max)
							{
								zhiwenF=1;
								break;
							}
							else
							{
								lcdWriteCom(0x01);
								beeping(3);
								lcdDisplayString(1,1,"NULL FINGER");
								delayms(1000);
								lcdWriteCom(0x01);
								mode=0;
								break;
							}
						}
					}
				}
				else
					if(pressFlag==1&&longP==1)
					{
						pressFlag=0;
						longP=0;
						lcdWriteCom(0x01);
						lcdDisplayString(1,1,"DELETE ALL");
					  lcdDisplayString(0,2,"COMMUNICATING>>>");
						while(1)
						{
							mode=3;
							searchNum=search();
							if((searchNum>=1&&searchNum<=max)||searchNum==255)
							{
								if(searchNum>=1&&searchNum<=max)
								{
									if(searchNum==1)
									{
										delF=1;
									  break;
									}
									
								}
								else
								{
									lcdWriteCom(0x01);
									beeping(3);
									lcdDisplayString(1,1,"UNAUTHORIZED");
									delayms(1000);
									lcdWriteCom(0x01);
									mode=0;
									break;
								}
							}
						}
					}
					else
						if(mode==0)
						{
							lcdDisplayString(0,1,"     LOCKED");
							lcdDisplayString(0,2,"COMMUNICATING>>>");
							fpSearch();
						}
					}
				}
}