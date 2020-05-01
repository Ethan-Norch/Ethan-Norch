#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define numAttr 10
//#define numTrain 100
//#define numClass 6
//#define numVec 6
//#define ylta 0.25
//#define interaction 100
int main()
{
    int numAttr,numTrain,numClass,numVec,interaction;
    float ylta;
    printf("Please enter the number of attributes:\n");
    scanf("%d",&numAttr);
    printf("Please enter the number of training sets:\n");
    scanf("%d",&numTrain);
    printf("Please enter the number of class:\n");
    scanf("%d",&numClass);
    printf("Please enter the number of vectors:\n");
    scanf("%d",&numVec);
    printf("Please enter the rate of learning speed:\n");
    scanf("%f",&ylta);
    printf("Please enter the times of interactions:\n");
    scanf("%d",&interaction);
    float trainSet[numTrain][numAttr+1];
    int a,i,j,b,cnt=0,m;
    srand((unsigned)time(NULL));
    printf("Generating trainingSet using seed:\n");
    for(i=0;i<numTrain;i++)
    {
        for(j=0;j<numAttr;j++)
        {
            trainSet[i][j]=0;
            a=rand()%51;
            //printf("%d\n",a);
            trainSet[i][j]=(float)a;
            //printf("%.3f\n",trainSet[i][j]);
            if(j==numAttr-1)
            {
                trainSet[i][j+1]=0;
                b=rand()%(numClass-1);
                trainSet[i][j+1]=(float)b;
            }
            cnt++;
        }
    }
    printf("Total attributes are : %d\n",cnt);
    printf("The trainingSet is(for x1,x2,x2...x%d,y):\n",numAttr);
    for(i=0;i<numTrain;i++)
    {
        for(j=0;j<numAttr+1;j++)
            printf("%.3f\t",trainSet[i][j]);
        printf("\n");
    }
    float t[numClass];
    printf("prototype vector marks are:\n");
    for(i=0;i<numVec;i++)
    {
        a=rand()%(numVec-1);
        t[i]=(float)a;
        printf("t[%d]=%.3f\t",i,t[i]);
    }
    printf("\n");
    float p[numVec][numAttr];
    printf("\nGenerating prototype vector:\n");
    for(i=0;i<numVec;i++)
    {
        for(j=0;j<numAttr;j++)
        {
            a=rand()%10;
            p[i][j]=(float)a;
            printf("p[%d][%d]=%.3f\n",i,j,p[i][j]);
        }
    }
    printf("\n");
    printf("start interaction......\n");
    float dis[numVec];
    for(i=0;i<interaction;i++)
    {
        int a=rand()%(numTrain+1);
        float sample[numAttr+1];
        printf("Selecting sample for %d times interaction:\nSample :\t",i);
        for(int n=0;n<numAttr+1;n++)
        {
            sample[n]=0.0;
            sample[n]=trainSet[a][n];
            printf("%.3f\t",sample[n]);
        }
        for(j=0;j<numAttr;j++)
        {
            for(m=0;m<numVec;m++)
            {
                if(m==0)
                    dis[m]=0.0;
                dis[m]+=(sample[j]-p[m][j])*(sample[j]-p[m][j]);
            }
        }
        for(m=0;m<numVec;m++)
                printf("\ndis[%d]=%.3f",m,dis[m]);
        int min=0;
        for(m=0;m<numVec;m++)
        {
            if(dis[min]>dis[m])
                min=m;
        }
        printf("\n");
        printf("The nearest distance dis[%d]=%.3f with x%d is p[%d]\n",min,dis[min],a+1,min,p[min]);
        if(sample[numAttr]==t[min])
        {
            for(m=0;m<numAttr;m++)
            {
                p[min][m]=p[min][m]+ylta*(sample[m]-p[min][m]);
            }
        }
        else
            for(m=0;m<numAttr;m++)
            {
                p[min][m]=p[min][m]-ylta*(sample[m]-p[min][m]);
            }
        printf("Prototype vector p[%d] has updated!\n",min);
        for(m=0;m<numAttr;m++)
            printf("p[%d][%d]=%.3f\n",min,m,p[min][m]);
    }
    printf("\n");
    printf("End all interaction!The prototype vectors are:\n");
    for(i=0;i<numVec;i++)
    {
        for(j=0;j<numAttr;j++)
            printf("p[%d][%d]=%.3f\n",i,j,p[i][j]);
        printf("\n");
    }
    return 0;
}
