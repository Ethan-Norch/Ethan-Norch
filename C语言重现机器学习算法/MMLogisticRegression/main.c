#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define e 2.718282
#define numAttr 9
#define numSample 100
#define ylta 0.25
#define K 20
#define interaction 10
int main()
{
    srand(time(NULL));
    int i,j,k;
    float trainSet[numSample][numAttr];
    printf("Generating training set:...\n");
    for(i=0;i<numSample;i++)
    {
        for(j=0;j<numAttr;j++)
        {
            trainSet[i][j]=(float)(rand()%100)/100.0;
            printf("trainSet[%d][%d]=%f\n",i,j,trainSet[i][j]);
        }
        printf("\n");
    }
    printf("Generating w[%d][%d]:...\n",K,numAttr);
    float w[K][numAttr];
    for(j=0;j<K;j++)
    {
        for(i=0;i<numAttr;i++)
        {
            w[j][i]=0.0;
            w[j][i]=(float)(rand()%100+1)/100.0;
            printf("w[%d][%d]=%f\n",j,i,w[j][i]);
        }
    }
for(int cir=0;cir<interaction;cir++)
{
    printf("Start %d times interaction\n",cir+1);
    float h[numSample][K],Sum[numSample];
    for(i=0;i<numSample;i++)
    {
        Sum[i]=0.0;
        for(j=0;j<K;j++)
        {
            h[i][j]=0.0;
            for(k=0;k<numAttr;k++)
            {
                h[i][j]+=w[j][k]*trainSet[i][k];
            }
            h[i][j]=pow(e,h[i][j]);
            Sum[i]+=h[i][j];
        }
        for(j=0;j<K;j++)
        {
            h[i][j]=h[i][j]/Sum[i];
            //printf("h[%d][%d]=%f\n",i,j,h[i][j]);
        }
    }
//update
    float deltaJ[numAttr];
    for(i=0;i<K;i++)
    {
        for(j=0;j<numAttr;j++)
        {
            deltaJ[j]=0.0;
            for(k=0;k<numSample;k++)
            {
                deltaJ[j]+=trainSet[k][j]*((i==j?1:0)-h[k][j]);
            }
            w[i][j]=w[i][j]-ylta*deltaJ[j]/(float)numSample;
        }
    }
    printf("New W:...\n");
    for(i=0;i<K;i++)
    {
        for(j=0;j<numAttr;j++)
        {
            printf("w[%d][%d]=%f\n",i,j,w[i][j]);
        }
    }
}


    printf("Hello world!\n");
    return 0;
}
