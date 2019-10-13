/*************************************************************
                      指纹模块头文件
 
实现功能：指纹模块的控制

补充说明：
***************************************************************/
#ifndef _FPM10A_H_
#define _FPM10A_H_
#include<reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

/*****************变量定义*******************/
#define FALSE 0
#define TURE  1

#define MAX_NUMBER 63//接收数据最大字节
uchar xdata FIFO[MAX_NUMBER+1]={0};//数据暂存数组

uchar searchNum=0;   //暂存识别的指纹编号	
uint clk0=0;	     //计数
uchar FifoNumber=0;  //接收到的数据个数
sbit ledWait=P2^3;

/****************操作指令定义****************/
//验证设备握手口令
uchar code VPWD[16]={16,0X01,0Xff,0xff,0xff,0xff,0x01,0,7,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//返回12个

//设置设备握手口令
uchar code STWD[16]={16,0X01,0Xff,0xff,0xff,0xff,0x01,0,7,0x12,0x00,0x00,0x00,0x00,0x00,0x1a};//返回12个

//探测手指并从传感器上读入图像
uchar code GIMG[14]={12,0X01,0Xff,0xff,0xff,0xff,0x01,0,3,1,0x00,0x05};//返回12个

//根据原始图像生成指纹特征1
uchar code GENT1[14]={13,0X01,0Xff,0xff,0xff,0xff,0x01,0,4,2,1,0x00,0x08};//返回12个

//根据原始图像生成指纹特征2
uchar code GENT2[14]={13,0X01,0Xff,0xff,0xff,0xff,0x01,0,4,2,2,0x00,0x09};//返回12个	
	
//以CharBufferA或CharBufferB中的特征文件搜索整个或部分指纹库
uchar code SEAT[18]={17,0X01,0Xff,0xff,0xff,0xff,0x01,0,8,4,1,0,0,0,0x65,0x00,0x73};//返回12个

//将CharBufferA与CharBufferB中的特征文件合并生成模板，结果存于ModelBuffer。
uchar code MERG[14]={12,0X01,0Xff,0xff,0xff,0xff,0x01,0,3,5,0x00,0x09};//返回12个	

//将ModelBuffer中的文件储存到flash指纹库中
uchar code STOR[16]={15,0X01,0Xff,0xff,0xff,0xff,0x01,0,6,6,2,0x00,0x00,0x00,0x0f}; //返回12个

//清除某个指定指纹
uchar code DELE_one[16]={16,0X01,0Xff,0xff,0xff,0xff,0x01,0,7,0x0c,0x00,0x00,0,1,0x00,0x15};

//清空指纹库
uchar code DELE_all[12]={12,0X01,0Xff,0xff,0xff,0xff,0x01,0,3,0x0d,0x00,0x11};

/*****************操作函数定义*******************/
void delay1ms(uint ms);//1毫秒延时程序
void UART_send_char(uchar dat);//串口发送一个字节数据
bit Command(uchar *p,uchar MaxTime);//命令解析,给模块发送一个命令
uchar ImgProcess(uchar BUFID);//发获取图像并生成特征文件，存入BUFID中
uchar search();//搜索用户
bit savefingure(uchar ID);//保存指纹
bit dellfingure(uchar ID);//删除指纹
bit Clear_All();//清空指纹
uchar enroll(); //录入指纹
void UartInit();//串口通讯初始化
/*********************************************************
函数名称:void delay1ms(uint t)
函数作用:1毫秒延时程序
参数说明:
*********************************************************/
void delay1ms(uint ms)
{
	uint i,j;
	for(i=0;i<ms;i++)
	   for(j=0;j<120;j++);
}
/*********************************************************
函数名称:void UART_send_char(uchar dat)
函数作用:串口发送一个字节数据
参数说明:
*********************************************************/
void UART_send_char(uchar dat)
{
    TI = 0;		 //清除发送标志
    SBUF = dat;	 //读入数据
    while(!TI);	 //等待发送完毕
    TI = 0;		 //清除发送标志
}
/*********************************************************
函数名称:bit Command(uchar *p,uchar MaxTime)
函数作用:命令解析,给模块发送一个命令
参数说明:*p指令，MaxTime延时时长
*********************************************************/
bit Command(uchar *p,uchar MaxTime)
{
	uchar count=0,tmpdat=0,temp=0,i=0,package=0,flag=0,checksum=0;

	bit result=0, start=0,stop=0;
	
	UART_send_char(0xef);//数据包包头识别码
	UART_send_char(0x01);//数据包包头识别码
	i=p[0];//数组的第“0”个元素、里面存放了本数组的长度，把这个长度给变量i，方便进行操作

	for(count=2; count<i;count++)//发送数据包
    UART_send_char(p[count]);       //将数据发送出去
	 
	result=TURE; //发送完成,结果为真 (真为1)   	
	FifoNumber=0;//清除接收的数据个数
	for(count=0;count<=MAX_NUMBER;count++)//清空所有FIFO[]数组里面的内容，写入0X00
		 FIFO[count]=0x00; 
  	if(result)   
   	{		
     	result=FALSE;
      start =FALSE;
   		stop  =FALSE;
      count=0;
      clk0=0;	//清零CL0计数
		
       	do /////////////////////////////do的内容////////////////////////////////
		{	
			restart0:				
         	if (RI==1)//如果接收到数据
	      	{ 				
						tmpdat=SBUF;//先把接收到的数据放到tmpdat中
            RI=0;		//软件清除接收标志
						
            	if((tmpdat==0xef)&&(start==FALSE))//这个数据为第一个传回来的数据，也就是“指令应答”的第一个字节
            	{ 
					count=0;
			    	FIFO[0]=tmpdat;//读入第一个应答字节(0XEF)，存在第“0”个元素中    
					flag=1;	
					goto 
						restart0;//可以用中断方式进行			
		        	
             	}
				if(flag==1)//第一个字节已经回来，所以flag==1成立
				{  
					if(tmpdat!=0x01)//接收数据错误，将重新从缓冲区接收数据
					{  	
						flag=0;//接收应答失败
						result=FALSE;
      					start =FALSE;
   						stop=FALSE;
       					count=0;
						goto 
							restart0;					
					}
					//如果成功接收到0xef01，可以开始接收数据
					flag=2;//flag=2;表示应答成功，可以开始接收数据了
					count++;//现在count=1;
					FIFO[count]=tmpdat;//读入第二个应答字节（0X01），存在第“1”个元素中    
					start=TURE;	//应答成功可以开始接收数据
					    goto 
							restart0;	
				}                  
             	if((flag==2)&&(start==TURE))//flag=2;表示应答成功，可以开始接收数据了
             	{	   	  					 
			   		count++;//数据元素下标++
		            FIFO[count]=tmpdat;//存入数据
					if(count>=6)
					{
						checksum=FIFO[count]+checksum;//计算校验和
					}
					if(count==8)
					{ 
						package=FIFO[7]*0X100+FIFO[8];//计算包长度							
						stop= TURE;
					}
					if(stop)
					{						
						if(count==package+8)
						{
							checksum=checksum-FIFO[count-1] - FIFO[count];
							if(checksum != (FIFO[count]&0xff))  
								result=FALSE; //校验失败,置结果标志为0							
							else 
								result=TURE;
							flag=0;
							break;
						} 
					}
             	}
 	       	}
		}
		while((clk0<=MaxTime)&&(count<=MAX_NUMBER));//由定时器以及最大接收数据来控制，保证不会在此一直循环
		
		FifoNumber=count;//保存接收到的数据个数
	}
	return (result);//返回操作是否成功
}
/*********************************************************
函数名称:uchar ImgProcess(uchar BUFID)
函数作用:发获取图像并生成特征文件，存入BUFID中 
参数说明:BUFID为缓冲区号
*********************************************************/
uchar ImgProcess(uchar BUFID)
{	
    if(Command(GIMG,89) && (FifoNumber==11) && (FIFO[9]==0x00))//操作成功  
    {
			ledWait=0;
		if(BUFID==1)     //生成指纹特征1      
		{	   			
      		if(Command(GENT1,60) && (FifoNumber==11) && (FIFO[9]==0x00))//操作成功  						
				return 1; 
        	else
  				return 0;
		 }
		else if(BUFID==2)//生成指纹特征2
		{
		  	if(Command(GENT2,60) && (FifoNumber==11) && (FIFO[9]==0x00))//操作成功  			
				return 1;
        	else
  				return 0;		
		}
    }
    else
        return 0;  

	return 0;             
}
/*********************************************************
函数名称:uchar search()
函数作用:搜索指纹
参数说明:返回指纹序号
*********************************************************/
uchar search()
{
 	uchar SearchBuf=0;

 	if (ImgProcess(1)==1)//首先读入一次指纹  
	{
	if(Command(SEAT,60) && (FifoNumber==15) && (FIFO[9]==0x00))//进行指纹比对，如果搜索到，返回搜索到的指纹序号 
		return FIFO[10]*0x100+FIFO[11];
	else
		return 255; 	    
	}
  return 0;
}
/*********************************************************
函数名称:bit savefingure(uchar ID)
函数作用:保存指纹
参数说明:指定保存的序号
*********************************************************/
bit savefingure(uchar ID)
{
	uchar i;
	//现在开始进行存储指纹模板的操作
	for (i=0;i<16;i++)	    //获取保存指纹信息指令
	{
		FIFO[i]=STOR[i];
	}  
	FIFO[12]=ID;            //把指纹模板存放的PAGE_ID也就是FLASH的位置
	FIFO[14]=FIFO[14]+ID;   //重新计算校验和
	
	if (Command(FIFO,70)==1)//成功返回1	//此处进行存放指纹模板的命令
		{return(1);}
	else
		{return(0);}        //不成功返回0
}
/*********************************************************
函数名称:bit dellfingure(uchar ID)
函数作用:删除指纹
参数说明:指定序号删除
*********************************************************/
bit dellfingure(uchar ID)
{
	uchar i;
	//现在开始进行存储指纹模板的操作
	for (i=0;i<16;i++)	    //获取删除指纹信息指令
	{
		FIFO[i]=DELE_one[i];
	}  
	FIFO[11]=ID;            //把指纹模板存放的PAGE_ID也就是FLASH的位置
	FIFO[15]=FIFO[15]+ID;   //重新计算校验和
	
	if (Command(FIFO,70)==1)//成功返回1//此处进行存放指纹模板的命
		{return(1);}
	else
		{return(0);}        //不成功返回0
}
/*********************************************************
函数名称:bit Clear_All()
函数作用:清空指纹库
参数说明:返回1成功，返回0失败 
*********************************************************/
bit Clear_All()
{				
	if(Command(DELE_all,50)==1)
		return(1);
	else
		return(0);		
}
/*********************************************************
函数名称:uchar enroll()
函数作用:采集两次指纹，生成1个指纹模板
参数说明:
*********************************************************/
uchar enroll() 
{
 	uchar temp=0,count=0;
  	while(1)
  	{
			
  	 	temp=ImgProcess(1);//生成特征1
			   
   		if (temp==1)       //生成特征文件成功             
      	{   		      
        	break;
       	}
     	else                   
       	{
        	if (temp==0)//采集指纹没有成功
          { 
						count++;
            if (count>=40)//如果采集了40次，还不成功，直接采集失败，直接退出enroll函数－－－－返回0  
						{return(0);}
           }
        }
   	}
	//采集第一个特征成功 
   	count=0;  
	delay1ms(500);//延时0.5S开始采集下一个特征
	//开始采集第二个特征 
 	while(1)
  	{
   		temp=ImgProcess(2);//生成特征2    
   		if (temp==1)       //生成特征文件2成功
      	{
        	if((Command(MERG,40)&& (FifoNumber==11) && (FIFO[9]==0x00))==0) //合并不成功返回0，成功返回1
			{
				return 0;
			}	
			else//特征文件合并生成模板，结果存于ModelBuffer
			{
        	     return 1;
			}	
        }
      	else      
       	{	
        	if (temp==1)//采集指纹没有成功
        	{
				count++;
				
				if (count>=25) 
				
				return(0);
       		}
     	}
   	}
} 
/*********************************************************
函数名称:void UartInit()
函数作用:串口通讯初始化
参数说明:
*********************************************************/
void UartInit()
{
	PCON |= 0x00;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD = 0x21;		//设定定时器1为8位自动重装方式
	TL1 = 0xFd;		    //设定定时初值
	TH1 = 0xFd;		    //设定定时器重装值
	ET1 = 0;		    //禁止定时器1中断
	TR1 = 1;		    //启动定时器1

	ET0=1;     //定时器0开中断
	TL0=0x97;  //17ms的初值
	TH0=0xBD;

  TR0=1;// 开定时器0
	EA=1;
}
/*********************************************************
函数名称:void  Timer0() interrupt 1
函数作用:定时器0中断函数
参数说明:
*********************************************************/
void  Timer0() interrupt 1
{
 	TL0=0x97; //定时器重新赋初值
	TH0=0xBD;
	clk0++;   //延时17ms
}
#endif