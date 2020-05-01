#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>
#define e 2.718282
//#define numLay 4
//#define numIn 3
//#define BiggestNeu 3
//#define ylta 0.25
//#define interaction 20
int main()
{
    srand(time(NULL));
    int numLay,numIn,BiggestNeu,interaction,i,j,k,totalNeu=0,maxX=0;
    float ylta,Output;
    printf("Please enter the number of layers:\n");
    scanf("%d",&numLay);
    printf("Please enter the number of Inputs:\n");
    scanf("%d",&numIn);
    float *Input=(float*)malloc(numIn*sizeof(float));
    printf("Please enter %d Inputs(between 0~0.5):\n",numIn);
    for(i=0;i<numIn;i++)
        scanf("%f",&Input[i]);
    printf("Please enter the number of Neures for each layers:\n");
    int *numNeu=(int*)malloc(numLay*sizeof(int));
    for(i=0;i<numLay-1;i++)
        scanf("%d",&numNeu[i]);
    numNeu[i]=1;
    for(i=0;i<numLay;i++)
    {
        printf("%d",numNeu[i]);
        if(numNeu[maxX]<numNeu[i])
            maxX=i;
    }
    BiggestNeu=maxX;


    printf("Please enter the learning rate:\n");
    scanf("%f",&ylta);
    printf("Please enter interaction times:\n");
    scanf("%d",&interaction);
    printf("Please enter the output:\n");
    scanf("%f",&Output);
    //float Input[numIn]={0.05,0.3,0.03};
    //float Output=0.7;
    //int numNeu[numLay]={3,2,2,1},totalNeu=0;
    float w[numLay][BiggestNeu][BiggestNeu];
    for(i=0;i<numLay;i++)
    {
        totalNeu+=numNeu[i];
    }
    printf("Total Neures are:%d\n",totalNeu);
    float y[totalNeu];
    float delta[totalNeu];
    printf("Generating w below......\n");
    for(i=0;i<numLay;i++)
    {
        if(i==0)
        {
            printf("1 layer W:\n");
            for(j=0;j<numIn;j++)
            {
                for(k=0;k<numNeu[i];k++)
                {
                    w[i][j][k]=0.0;
                    w[i][j][k]=(float)(rand()%5+1)/10.0;
                    printf("w[%d][%d][%d]=%.3f\n",i,j,k,w[i][j][k]);
                }
            }
        }
        else
        {
            printf("%d layer W:\n",i);
            for(j=0;j<numNeu[i-1];j++)
            {
                for(k=0;k<numNeu[i];k++)
                {
                    w[i][j][k]=0.0;
                    w[i][j][k]=(float)(rand()%5+1)/10.0;
                    printf("w[%d][%d][%d]=%.3f\n",i,j,k,w[i][j][k]);
                }
            }
        }
    }
    for(int cir=0;cir<interaction;cir++)
    {
        printf("\nInteraction for %d times:\n",cir);
//FP
    int cnt=0,dele=0,addnum=0;
    float temp;
    for(i=0;i<numLay;i++)
    {
        if(i==0)
        {
            temp=0.0;
            for(j=0;j<numNeu[i];j++)
            {
                for(k=0;k<numIn;k++)
                {
                    temp+=w[i][k][j]*Input[k];
                }
                y[cnt]=1.0/(1+pow(e,-temp));
                cnt++;
                addnum++;
            }
        }
        else
        {
            dele=cnt-addnum;
            addnum=0;
            for(j=0;j<numNeu[i];j++)
            {
                temp=0.0;
                for(k=0;k<numNeu[i-1];k++)
                {
                    temp+=w[i][k][j]*y[dele+k];
                }
                printf("\n%f\n",temp);
                y[cnt]=1.0/(1.0+pow(e,-temp));
                cnt++;
                addnum++;
            }
        }
    }
    printf("\nResult of FP:\n");
    for(i=0;i<totalNeu;i++)
        printf("y[%d]=%.3f\n",i,y[i]);
//BP
    cnt=totalNeu-1;
    addnum=0;
    for(i=numLay;i>0;i--)
    {
        if(i==numLay)
        {
            delta[cnt]=Output-y[cnt];
            //printf("delta[%d]=%f\n",cnt,delta[cnt]);
            cnt--;
            addnum++;
        }
        else
        {
            int dele=cnt+addnum;
            addnum=0;
            //printf("dele===%d\n",dele);
            for(j=numNeu[i-1];j>0;j--)
            {
                temp=0.0;
                for(k=numNeu[i];k>0;k--)
                {
                    //printf("%f\n",w[i][j-1][k-1]);
                    temp+=w[i][j-1][k-1]*delta[dele-k+1];
                }
                //printf("temp=%f\n",temp);
                delta[cnt]=temp;
                cnt--;
                addnum++;
            }
        }
    }
    printf("BP result:\n");
    for(i=0;i<totalNeu;i++)
        printf("delta[%d]=%f\n",i,delta[i]);

//update W
    if(cir==interaction-1)
        printf("\n\nEnd interaction and the final w is:\n");
    else
        printf("\nUpdating W for %d times:...\n",cir);
    cnt=0;
    addnum=0;
    for(i=0;i<numLay;i++)
    {
        if(i==0)
        {
            temp=0.0;
            for(j=0;j<numNeu[i];j++)
            {
                for(k=0;k<numIn;k++)
                {
                    w[i][k][j]=w[i][k][j]+ylta*delta[cnt]*y[cnt]*(1-y[cnt])*Input[k];
                    printf("w[%d][%d][%d]=%f\n",i,k,j,w[i][k][j]);
                }
                cnt++;
                addnum++;
            }
            printf("\n");
        }
        else
        {
            dele=cnt-addnum;
            addnum=0;
            for(j=0;j<numNeu[i];j++)
            {
                temp=0.0;
                for(k=0;k<numNeu[i-1];k++)
                {
                    w[i][k][j]=w[i][k][j]+ylta*delta[cnt]*y[cnt]*(1-y[cnt])*y[dele+k];
                    printf("w[%d][%d][%d]=%f\n",i,k,j,w[i][k][j]);
                }
                cnt++;
                addnum++;
            }
            printf("\n");
        }
    }
    }
    printf("Hello world!\n");
    printf("%f\n",FLT_EPSILON);
    return 0;
}
