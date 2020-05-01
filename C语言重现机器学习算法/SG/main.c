#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define numTrain 100
#define numAttr 5
#define kF 1
#define interactionPer 10
#define ylta 0.25
#define numNN 5
#define e 2.718282
int main()
{
//perceptino
    srand(time(NULL));
    int i,j,k,aa,bb;
    float gatherSet[10][numAttr+1];
    for(i=0;i<10;i++)
    {
        for(j=0;j<numAttr;j++)
            gatherSet[i][j]=(float)(rand()%100)/100.0;
        if(rand()%2==0)
            gatherSet[i][j]=-1.0;
        else
            gatherSet[i][j]=1.0;
    }
    float trainSet[numTrain][numAttr+1],sample[numTrain-kF*10][numAttr+1],test[10*kF][numAttr+1],stackSet[10][3];
    printf("Generating trainSet:...\n");
    for(i=0;i<numTrain;i++)
    {
        for(j=0;j<numAttr;j++)
        {
            trainSet[i][j]=(float)(rand()%100+1)/100.0;
            printf("trainSet[%d][%d]=%f\n",i,j,trainSet[i][j]);
        }
        if(rand()%2==0)
            trainSet[i][j]=-1.0;
        else
            trainSet[i][j]=1.0;
        printf("trainSet[%d][%d]=%f\n",i,j,trainSet[i][j]);
    }

    for(i=0;i<numTrain/10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(j<(10-kF))
            {
                for(k=0;k<numAttr+1;k++)
                {
                    sample[i*10+j][k]=0.0;
                    sample[i*10+j][k]=trainSet[i*10+j][k];
                }
            }
            else
            {

                for(k=0;k<numAttr+1;k++)
                {
                    sample[i*10+j][k]=0.0;
                    test[i*10+j][k]=0.0;
                    test[i*10+j][k]=trainSet[i*10+j][k];
                }
            }
        }
    }
    for(i=0;i<numTrain/10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(j<10-kF)
            {
                for(k=0;k<numAttr+1;k++)
                    printf("sample[%d][%d]=%f\n",i*10+j,k,sample[i*10+j][k]);
            }
            else
            {
                for(k=0;k<numAttr+1;k++)
                    printf("test[%d][%d]=%f\n",i*10+j,k,test[i*10+j][k]);
            }
        }
    }
    float wP[numAttr],b=0.0;
    for(i=0;i<numAttr;i++)
    {
        wP[i]=(float)(rand()%100+1)/100.0;
        printf("wP[%d]=%f\n",i,wP[i]);
    }
    float Sum[numTrain-10*kF];
    int m;
    for(i=0;i<interactionPer;i++)
    {
        for(j=0;j<numTrain/10;j++)
        {
            for(k=0;k<10;k++)
            {
                Sum[j*10+k]=0.0;
                if(k<10-kF)
                {
                    for(m=0;m<numAttr;m++)
                    {
                        Sum[j*10+k]+=wP[m]*sample[j*10+k][m];
                    }
                    Sum[j*10+k]+=b;
                    if(Sum[j*10+k]>=0)
                        Sum[j*10+k]=1;
                    else
                        Sum[j*10+k]=-1;
                    printf("Sum[%d]=%f\n",j*10+k,Sum[j*10+k]);
                }
            }
        }
        for(j=0;j<numTrain/10;j++)
        {
            for(k=0;k<10;k++)
            {
                if(k<10-kF)
                {
                    for(m=0;m<numAttr;m++)
                    {
                        wP[m]+=ylta*(sample[i*10+k][numAttr+1]-(float)Sum[j*10+k])*sample[j*10+k][m]/2;

                    }
                    b+=(sample[i*10+k][numAttr+1]-Sum[i*10+k])/2;
                }
            }
        }
        printf("\n%d times inter :\n",i);
        for(m=0;m<numAttr;m++)
            printf("wP[%d]=%f\n",m,wP[m]);
        if(i==interactionPer-1)
        {
            for(j=0;j<10;j++)
            {
                stackSet[j][0]=0.0;
                for(k=0;k<numAttr;k++)
                {
                    stackSet[j][0]+=gatherSet[j][k]*wP[k];
                }
                if(stackSet[j][0]+b>=0)
                    stackSet[j][0]=1.0;
                else
                    stackSet[j][0]=-1.0;
                //printf("stackSet[%d][0]=%f\n",j,stackSet[j][0]);
            }
        }
        printf("b=%f\n",b);
    }
//KNN
    float distance[numTrain-10*kF];
    int min=0,tmpX[numNN],cnt=0,flag=0,Ycnt=0,Ncnt=0,nn;
    for(i=0;i<10;i++)
    {
        for(j=0;j<numTrain/10;j++)
        {
            for(k=0;k<10;k++)
            {
                if(k<10-kF)
                {
                    distance[j*10+k]=0.0;

                    for(m=0;m<numAttr;m++)
                    {
                        //printf("sample[%d][%d]=%f\n",j*10+k,m,sample[j*10+k][m]);
                        //printf("gather[%d][%d]=%f\n",i,m,gatherSet[i][m]);
                        distance[j*10+k]+=(gatherSet[i][m]-sample[j*10+k][m])*(gatherSet[i][m]-sample[j*10+k][m]);
                    }
                    //printf("distance[%d]=%f\n",j*10+k,distance[j*10+k]);
                }
            }
        }
        for(nn=0;nn<numNN;nn++)
        {
            Ycnt=0;
            Ncnt=0;
            if(cnt==0)
            {
                for(j=0;j<numTrain/10;j++)
                {
                    for(k=0;k<10;k++)
                    {
                        if(k<10-kF)
                        {
                            if(distance[min]>distance[j*10+k])
                            {
                                min=j*10+k;
                            }
                        }
                    }
                }
                //printf("min=%d\n",min);
                tmpX[cnt]=min;

                if(sample[min][2]==1.0)
                    Ycnt++;
                else
                    Ncnt++;
                cnt++;
            }
            else
            {
                for(j=0;j<numTrain/10;j++)
                {
                    for(k=0;k<10;k++)
                    {
                        if(k<10-kF)
                        {
                            min=0;
                            if(distance[min]>distance[j*10+k])
                            {
                                for(m=0;m<cnt;m++)
                                {
                                    if(tmpX[m]!=j*10+k)
                                        flag=1;
                                    else
                                        flag=0;
                                }
                                if(flag==1)
                                {
                                    min=j*10+k;
                                }
                            }
                        }
                    }
                }
                tmpX[cnt]=min;
                if(sample[min][2]==1.0)
                    Ycnt++;
                else
                    Ncnt++;
                cnt++;
            }
        }
        if(Ycnt>Ncnt)
            stackSet[i][1]=1.0;
        else
            stackSet[i][1]=-1.0;
    }
    printf("The stackSet is :...\n");
    for(i=0;i<10;i++)
    {
        stackSet[i][2]=gatherSet[i][numAttr];
        for(j=0;j<3;j++)
            printf("stackSet[%d][%d]=%f\t",i,j,stackSet[i][j]);
        printf("\n");
    }

//gather logistic
    float wL[10][2],h[10],tmp;
    int cir;
    printf("The wL is:,,,\n");
    for(j=0;j<10;j++)
    {
        for(i=0;i<2;i++)
        {
            wL[j][i]=(float)(rand()%100+1)/100.0;
            printf("wL[%d][%d]=%f\t",j,i,wL[j][i]);
        }
        printf("\n");
    }
    for(cir=0;cir<interactionPer;cir++)
    {
        printf("%d times gather logistic:...\n",cir+1);
        for(i=0;i<10;i++)
        {
            h[i]=0.0;
            for(j=0;j<2;j++)
            {
                h[i]+=stackSet[i][j]*wL[i][j];
            }
            h[i]=(pow(e,h[i])-pow(e,-h[i]))/(pow(e,h[i])+pow(e,-h[i]));
        }
        for(i=0;i<10;i++)
        {

            for(j=0;j<2;j++)
            {
                tmp=0.0;
                for(k=0;k<10;k++)
                {
                    tmp+=(h[i]-stackSet[k][2])*stackSet[k][j];
                }
                wL[i][j]=wL[i][j]-ylta*tmp/10.0;
                printf("wL[%d][%d]=%f\t",i,j,wL[i][j]);
            }
            printf("\n");
        }
    }
//final (there is no test due to the data we use are all random....)
    float perY[10*kF],TEST[10*kF][3],tmpDis[numTrain-10*kF],testDis[numTrain-10*kF];
    for(i=0;i<numTrain/10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(j>=10-kF)
            {
                //per
                perY[i*10+j]=0.0;
                for(k=0;k<numAttr;k++)
                    perY[i*10+j]+=test[i*10+j][k]*wP[k];
                if(perY[i*10+j]+b>0)
                    perY[i*10+j]=1.0;
                else
                    perY[i*10+j]=-1.0;
                TEST[i*10+j][0]=perY[i*10+j];
                printf("TEST[%d][0]=%f\n",i*10+j,TEST[i*10+j][0]);
                TEST[i*10+j][2]=test[i*10+j][numAttr];
                //KNN
                testDis[i*10+j]=0.0;
                for(k=0;k<numTrain/10;k++)
                {
                    for(m=0;m<10;m++)
                    {
                        if(m<10-kF)
                        {
                            for(aa=0;aa<numAttr;aa++)
                            {
                                testDis[k*10+m]+=pow((test[i*10+j][aa]-sample[k*10+m][aa]),2);
                            }

                        }
                    }
                }
                cnt=0;
                min=0;
                for(nn=0;nn<numNN;nn++)
                {
                    Ycnt=0;
                    Ncnt=0;
                    if(cnt==0)
                    {
                        for(aa=0;aa<numTrain/10;aa++)
                        {
                            for(bb=0;bb<10;bb++)
                            {
                                if(bb<10-kF)
                                {
                                    if(testDis[min]>testDis[aa*10+bb])
                                    {
                                        min=aa*10+bb;
                                    }
                                }
                            }
                        }
                //printf("min=%d\n",min);
                        tmpX[cnt]=min;

                        if(sample[min][2]==1.0)
                            Ycnt++;
                        else
                            Ncnt++;
                        cnt++;
                    }
                    else
                    {
                        for(aa=0;aa<numTrain/10;aa++)
                        {
                            for(bb=0;bb<10;bb++)
                            {
                                if(bb<10-kF)
                                {
                                    min=0;
                                    if(testDis[min]>testDis[aa*10+bb])
                                    {
                                        for(m=0;m<cnt;m++)
                                        {
                                            if(tmpX[m]!=aa*10+bb)
                                                flag=1;
                                            else
                                                flag=0;
                                        }
                                        if(flag==1)
                                        {
                                            min=aa*10+bb;
                                        }
                                    }
                                }
                            }
                        }
                        tmpX[cnt]=min;
                        if(sample[min][2]==1.0)
                            Ycnt++;
                        else
                            Ncnt++;
                        cnt++;
                    }
                }
                if(Ycnt>Ncnt)
                    TEST[i*10+j][1]=1.0;
                else
                    TEST[i*10+j][1]=-1.0;
            }
        }
    }
    printf("The test stack:...\n");
    for(i=0;i<numTrain/10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(j>=10-kF)
            {
                for(k=0;k<3;k++)
                    printf("TEST[%d][%d]=%f\t",i*10+j,k,TEST[i*10+j][k]);
                printf("\n");
            }
        }
    }
//gather logistic
    float gathY[10*kF],corRate=0.0;
    int corCnt=0;
    for(i=0;i<numTrain/10;i++)
    {
        for(j=0;j<10;j++)
        {
            if(j>=10-kF)
            {
                gathY[i*10+j]=0.0;
                for(k=0;k<2;k++)
                {
                    gathY[i*10+j]+=TEST[i*10+j][k]*wL[i][k];
                }
                gathY[i*10+j]=(pow(e,gathY[i*10+j])+pow(e,-gathY[i*10+j]))/(pow(e,gathY[i*10+j])+pow(e,-gathY[i*10+j]));
                printf("GathY[%d]=%f\n",i*10+j,gathY[i*10+j]);
                printf("TEST[%d]=%f\n",i*10+j,TEST[i*10+j][2]);
                if(gathY[i*10+j]==TEST[i*10+j][2])
                    corCnt++;
            }
        }
    }
    printf("corCnt=%d\n",corCnt);
    printf("The k-Fold Test correct Rate is :%f\n",(float)corCnt/(float)(10*kF));

    printf("Hello world!\n");
    return 0;
}
