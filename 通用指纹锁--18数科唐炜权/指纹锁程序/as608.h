/*************************************************************
                      ָ��ģ��ͷ�ļ�
 
ʵ�ֹ��ܣ�ָ��ģ��Ŀ���

����˵����
***************************************************************/
#ifndef _FPM10A_H_
#define _FPM10A_H_
#include<reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

/*****************��������*******************/
#define FALSE 0
#define TURE  1

#define MAX_NUMBER 63//������������ֽ�
uchar xdata FIFO[MAX_NUMBER+1]={0};//�����ݴ�����

uchar searchNum=0;   //�ݴ�ʶ���ָ�Ʊ��	
uint clk0=0;	     //����
uchar FifoNumber=0;  //���յ������ݸ���
sbit ledWait=P2^3;

/****************����ָ���****************/
//��֤�豸���ֿ���
uchar code VPWD[16]={16,0X01,0Xff,0xff,0xff,0xff,0x01,0,7,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//����12��

//�����豸���ֿ���
uchar code STWD[16]={16,0X01,0Xff,0xff,0xff,0xff,0x01,0,7,0x12,0x00,0x00,0x00,0x00,0x00,0x1a};//����12��

//̽����ָ���Ӵ������϶���ͼ��
uchar code GIMG[14]={12,0X01,0Xff,0xff,0xff,0xff,0x01,0,3,1,0x00,0x05};//����12��

//����ԭʼͼ������ָ������1
uchar code GENT1[14]={13,0X01,0Xff,0xff,0xff,0xff,0x01,0,4,2,1,0x00,0x08};//����12��

//����ԭʼͼ������ָ������2
uchar code GENT2[14]={13,0X01,0Xff,0xff,0xff,0xff,0x01,0,4,2,2,0x00,0x09};//����12��	
	
//��CharBufferA��CharBufferB�е������ļ����������򲿷�ָ�ƿ�
uchar code SEAT[18]={17,0X01,0Xff,0xff,0xff,0xff,0x01,0,8,4,1,0,0,0,0x65,0x00,0x73};//����12��

//��CharBufferA��CharBufferB�е������ļ��ϲ�����ģ�壬�������ModelBuffer��
uchar code MERG[14]={12,0X01,0Xff,0xff,0xff,0xff,0x01,0,3,5,0x00,0x09};//����12��	

//��ModelBuffer�е��ļ����浽flashָ�ƿ���
uchar code STOR[16]={15,0X01,0Xff,0xff,0xff,0xff,0x01,0,6,6,2,0x00,0x00,0x00,0x0f}; //����12��

//���ĳ��ָ��ָ��
uchar code DELE_one[16]={16,0X01,0Xff,0xff,0xff,0xff,0x01,0,7,0x0c,0x00,0x00,0,1,0x00,0x15};

//���ָ�ƿ�
uchar code DELE_all[12]={12,0X01,0Xff,0xff,0xff,0xff,0x01,0,3,0x0d,0x00,0x11};

/*****************������������*******************/
void delay1ms(uint ms);//1������ʱ����
void UART_send_char(uchar dat);//���ڷ���һ���ֽ�����
bit Command(uchar *p,uchar MaxTime);//�������,��ģ�鷢��һ������
uchar ImgProcess(uchar BUFID);//����ȡͼ�����������ļ�������BUFID��
uchar search();//�����û�
bit savefingure(uchar ID);//����ָ��
bit dellfingure(uchar ID);//ɾ��ָ��
bit Clear_All();//���ָ��
uchar enroll(); //¼��ָ��
void UartInit();//����ͨѶ��ʼ��
/*********************************************************
��������:void delay1ms(uint t)
��������:1������ʱ����
����˵��:
*********************************************************/
void delay1ms(uint ms)
{
	uint i,j;
	for(i=0;i<ms;i++)
	   for(j=0;j<120;j++);
}
/*********************************************************
��������:void UART_send_char(uchar dat)
��������:���ڷ���һ���ֽ�����
����˵��:
*********************************************************/
void UART_send_char(uchar dat)
{
    TI = 0;		 //������ͱ�־
    SBUF = dat;	 //��������
    while(!TI);	 //�ȴ��������
    TI = 0;		 //������ͱ�־
}
/*********************************************************
��������:bit Command(uchar *p,uchar MaxTime)
��������:�������,��ģ�鷢��һ������
����˵��:*pָ�MaxTime��ʱʱ��
*********************************************************/
bit Command(uchar *p,uchar MaxTime)
{
	uchar count=0,tmpdat=0,temp=0,i=0,package=0,flag=0,checksum=0;

	bit result=0, start=0,stop=0;
	
	UART_send_char(0xef);//���ݰ���ͷʶ����
	UART_send_char(0x01);//���ݰ���ͷʶ����
	i=p[0];//����ĵڡ�0����Ԫ�ء��������˱�����ĳ��ȣ���������ȸ�����i��������в���

	for(count=2; count<i;count++)//�������ݰ�
    UART_send_char(p[count]);       //�����ݷ��ͳ�ȥ
	 
	result=TURE; //�������,���Ϊ�� (��Ϊ1)   	
	FifoNumber=0;//������յ����ݸ���
	for(count=0;count<=MAX_NUMBER;count++)//�������FIFO[]������������ݣ�д��0X00
		 FIFO[count]=0x00; 
  	if(result)   
   	{		
     	result=FALSE;
      start =FALSE;
   		stop  =FALSE;
      count=0;
      clk0=0;	//����CL0����
		
       	do /////////////////////////////do������////////////////////////////////
		{	
			restart0:				
         	if (RI==1)//������յ�����
	      	{ 				
						tmpdat=SBUF;//�Ȱѽ��յ������ݷŵ�tmpdat��
            RI=0;		//���������ձ�־
						
            	if((tmpdat==0xef)&&(start==FALSE))//�������Ϊ��һ�������������ݣ�Ҳ���ǡ�ָ��Ӧ�𡱵ĵ�һ���ֽ�
            	{ 
					count=0;
			    	FIFO[0]=tmpdat;//�����һ��Ӧ���ֽ�(0XEF)�����ڵڡ�0����Ԫ����    
					flag=1;	
					goto 
						restart0;//�������жϷ�ʽ����			
		        	
             	}
				if(flag==1)//��һ���ֽ��Ѿ�����������flag==1����
				{  
					if(tmpdat!=0x01)//�������ݴ��󣬽����´ӻ�������������
					{  	
						flag=0;//����Ӧ��ʧ��
						result=FALSE;
      					start =FALSE;
   						stop=FALSE;
       					count=0;
						goto 
							restart0;					
					}
					//����ɹ����յ�0xef01�����Կ�ʼ��������
					flag=2;//flag=2;��ʾӦ��ɹ������Կ�ʼ����������
					count++;//����count=1;
					FIFO[count]=tmpdat;//����ڶ���Ӧ���ֽڣ�0X01�������ڵڡ�1����Ԫ����    
					start=TURE;	//Ӧ��ɹ����Կ�ʼ��������
					    goto 
							restart0;	
				}                  
             	if((flag==2)&&(start==TURE))//flag=2;��ʾӦ��ɹ������Կ�ʼ����������
             	{	   	  					 
			   		count++;//����Ԫ���±�++
		            FIFO[count]=tmpdat;//��������
					if(count>=6)
					{
						checksum=FIFO[count]+checksum;//����У���
					}
					if(count==8)
					{ 
						package=FIFO[7]*0X100+FIFO[8];//���������							
						stop= TURE;
					}
					if(stop)
					{						
						if(count==package+8)
						{
							checksum=checksum-FIFO[count-1] - FIFO[count];
							if(checksum != (FIFO[count]&0xff))  
								result=FALSE; //У��ʧ��,�ý����־Ϊ0							
							else 
								result=TURE;
							flag=0;
							break;
						} 
					}
             	}
 	       	}
		}
		while((clk0<=MaxTime)&&(count<=MAX_NUMBER));//�ɶ�ʱ���Լ����������������ƣ���֤�����ڴ�һֱѭ��
		
		FifoNumber=count;//������յ������ݸ���
	}
	return (result);//���ز����Ƿ�ɹ�
}
/*********************************************************
��������:uchar ImgProcess(uchar BUFID)
��������:����ȡͼ�����������ļ�������BUFID�� 
����˵��:BUFIDΪ��������
*********************************************************/
uchar ImgProcess(uchar BUFID)
{	
    if(Command(GIMG,89) && (FifoNumber==11) && (FIFO[9]==0x00))//�����ɹ�  
    {
			ledWait=0;
		if(BUFID==1)     //����ָ������1      
		{	   			
      		if(Command(GENT1,60) && (FifoNumber==11) && (FIFO[9]==0x00))//�����ɹ�  						
				return 1; 
        	else
  				return 0;
		 }
		else if(BUFID==2)//����ָ������2
		{
		  	if(Command(GENT2,60) && (FifoNumber==11) && (FIFO[9]==0x00))//�����ɹ�  			
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
��������:uchar search()
��������:����ָ��
����˵��:����ָ�����
*********************************************************/
uchar search()
{
 	uchar SearchBuf=0;

 	if (ImgProcess(1)==1)//���ȶ���һ��ָ��  
	{
	if(Command(SEAT,60) && (FifoNumber==15) && (FIFO[9]==0x00))//����ָ�Ʊȶԣ������������������������ָ����� 
		return FIFO[10]*0x100+FIFO[11];
	else
		return 255; 	    
	}
  return 0;
}
/*********************************************************
��������:bit savefingure(uchar ID)
��������:����ָ��
����˵��:ָ����������
*********************************************************/
bit savefingure(uchar ID)
{
	uchar i;
	//���ڿ�ʼ���д洢ָ��ģ��Ĳ���
	for (i=0;i<16;i++)	    //��ȡ����ָ����Ϣָ��
	{
		FIFO[i]=STOR[i];
	}  
	FIFO[12]=ID;            //��ָ��ģ���ŵ�PAGE_IDҲ����FLASH��λ��
	FIFO[14]=FIFO[14]+ID;   //���¼���У���
	
	if (Command(FIFO,70)==1)//�ɹ�����1	//�˴����д��ָ��ģ�������
		{return(1);}
	else
		{return(0);}        //���ɹ�����0
}
/*********************************************************
��������:bit dellfingure(uchar ID)
��������:ɾ��ָ��
����˵��:ָ�����ɾ��
*********************************************************/
bit dellfingure(uchar ID)
{
	uchar i;
	//���ڿ�ʼ���д洢ָ��ģ��Ĳ���
	for (i=0;i<16;i++)	    //��ȡɾ��ָ����Ϣָ��
	{
		FIFO[i]=DELE_one[i];
	}  
	FIFO[11]=ID;            //��ָ��ģ���ŵ�PAGE_IDҲ����FLASH��λ��
	FIFO[15]=FIFO[15]+ID;   //���¼���У���
	
	if (Command(FIFO,70)==1)//�ɹ�����1//�˴����д��ָ��ģ�����
		{return(1);}
	else
		{return(0);}        //���ɹ�����0
}
/*********************************************************
��������:bit Clear_All()
��������:���ָ�ƿ�
����˵��:����1�ɹ�������0ʧ�� 
*********************************************************/
bit Clear_All()
{				
	if(Command(DELE_all,50)==1)
		return(1);
	else
		return(0);		
}
/*********************************************************
��������:uchar enroll()
��������:�ɼ�����ָ�ƣ�����1��ָ��ģ��
����˵��:
*********************************************************/
uchar enroll() 
{
 	uchar temp=0,count=0;
  	while(1)
  	{
			
  	 	temp=ImgProcess(1);//��������1
			   
   		if (temp==1)       //���������ļ��ɹ�             
      	{   		      
        	break;
       	}
     	else                   
       	{
        	if (temp==0)//�ɼ�ָ��û�гɹ�
          { 
						count++;
            if (count>=40)//����ɼ���40�Σ������ɹ���ֱ�Ӳɼ�ʧ�ܣ�ֱ���˳�enroll����������������0  
						{return(0);}
           }
        }
   	}
	//�ɼ���һ�������ɹ� 
   	count=0;  
	delay1ms(500);//��ʱ0.5S��ʼ�ɼ���һ������
	//��ʼ�ɼ��ڶ������� 
 	while(1)
  	{
   		temp=ImgProcess(2);//��������2    
   		if (temp==1)       //���������ļ�2�ɹ�
      	{
        	if((Command(MERG,40)&& (FifoNumber==11) && (FIFO[9]==0x00))==0) //�ϲ����ɹ�����0���ɹ�����1
			{
				return 0;
			}	
			else//�����ļ��ϲ�����ģ�壬�������ModelBuffer
			{
        	     return 1;
			}	
        }
      	else      
       	{	
        	if (temp==1)//�ɼ�ָ��û�гɹ�
        	{
				count++;
				
				if (count>=25) 
				
				return(0);
       		}
     	}
   	}
} 
/*********************************************************
��������:void UartInit()
��������:����ͨѶ��ʼ��
����˵��:
*********************************************************/
void UartInit()
{
	PCON |= 0x00;		//ʹ�ܲ����ʱ���λSMOD
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD = 0x21;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFd;		    //�趨��ʱ��ֵ
	TH1 = 0xFd;		    //�趨��ʱ����װֵ
	ET1 = 0;		    //��ֹ��ʱ��1�ж�
	TR1 = 1;		    //������ʱ��1

	ET0=1;     //��ʱ��0���ж�
	TL0=0x97;  //17ms�ĳ�ֵ
	TH0=0xBD;

  TR0=1;// ����ʱ��0
	EA=1;
}
/*********************************************************
��������:void  Timer0() interrupt 1
��������:��ʱ��0�жϺ���
����˵��:
*********************************************************/
void  Timer0() interrupt 1
{
 	TL0=0x97; //��ʱ�����¸���ֵ
	TH0=0xBD;
	clk0++;   //��ʱ17ms
}
#endif