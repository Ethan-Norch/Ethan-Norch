#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define numSample 500
#define numTrain 1000
#define interaction 10


int main()
{
    srand(time(NULL));
    int i,j,k,cir;
    printf("Generating trainSet:...\n\n");
    float alphaSum=0.0,alpha[numTrain],trainSet[numSample][2],VarX=0.0,VarY=0.0,CovXY=0.0,SumX,SumY,SumXY,EX=0.0,EY=0.0,EXY=0.0,tmpX,tmpY;
    for(i=0;i<numSample;i++)
    {
        for(j=0;j<2;j++)
        {
            trainSet[i][j]=(float)(rand()%45+5);
            printf("trainSet[%d][%d]=%f\t",i,j,trainSet[i][j]);
        }
        printf("\n");
    }
    for(cir=0;cir<interaction;cir++)
    {
        printf("Selecting %d samples:.../n",numSample);
    float sample[numTrain][2];
    for(i=0;i<numTrain;i++)
    {
        j=rand()%(numSample+1);
        for(k=0;k<2;k++)
        {
            sample[i][k]=trainSet[j][k];
            printf("sample[%d][%d]=%f\t",i,k,sample[i][k]);
        }
        printf("\n");
    }
    SumX=0.0;
    SumY=0.0;
    SumXY=0.0;
    for(i=0;i<numTrain;i++)
    {
        SumX+=sample[i][0];
        SumY+=sample[i][1];
        SumXY+=sample[i][0]*sample[i][1];
    }
    EX=SumX/(float)numTrain;
    EY=SumY/(float)numTrain;
    EXY=SumXY/(float)numTrain;
    tmpX=0.0;
    tmpY=0.0;
    for(i=0;i<numTrain;i++)
    {
        tmpX+=(sample[i][0]-EX)*(sample[i][0]-EX);
        tmpY+=(sample[i][1]-EY)*(sample[i][1]-EY);
    }
    VarX=tmpX/(float)numTrain;
    VarY=tmpY/(float)numTrain;
    CovXY=EXY-EX*EY;
    alpha[cir]=0.0;
    alpha[cir]=(VarY*VarY-CovXY)/(VarX*VarX+VarY*VarY-2*CovXY);
    alphaSum+=alpha[cir];
    printf("\nFor %d times bootstrapping:\nalpha[%d]=%f",cir+1,cir,alpha);
    }
    float alphaMean=alphaSum/(float)interaction,tmpA=0.0,VarA=0.0;
    for(i=0;i<interaction;i++)
        tmpA+=pow((alpha[i]-alphaMean),2);
    VarA=pow(tmpA/(float)(interaction-1),0.5);
    printf("\n\nThe result is:...\nalphaMean=%f\nalphaVar=%f\n",alphaMean,VarA);
    printf("Hello world!\n");
    return 0;
}
