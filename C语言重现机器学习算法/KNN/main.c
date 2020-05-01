#include <stdio.h>
#include <stdlib.h>
#define numAttr 4
#define numTrain 20
//#define K 5
//attr:kill ahead(int) economy ahead(float k) numOfAlive ahead(int) turretDestroy ahead(int)    ----> (打龙(1)？推塔(2)？发育(3)？）
int main()
{
    int trainSet[numTrain][numAttr+1]={
    {-9,-3,-2,-4,1},{10,4,3,4,1},{3,2,-2,3,3},{-10,-4,1,-2,1},{6,3,3,3,2},
    {-9,-4,3,-2,2},{-1,-1,0,-1,3},{5,2,2,1,2},{-6,-1,-2,-1,3},{5,2,3,2,2},
    {20,5,2,3,1},{18,-3,0,-4,3},{1,-2,2,2,1},{-10,-3,-2,-2,3},{-9,0,-1,2,1},
    {6,2,2,3,1},{14,4,3,3,2},{2,2,0,1,1},{-13,-5,1,-3,3},{14,4,2,3,2}};
    int K;
    printf("please enter K for KNN:\n");
    scanf("%d",&K);
    int i,j,minX=0,numX=0,draCnt=0,turCnt=0,groCnt=0;
    int testSet[numAttr];
    //int testSet[numAttr]={3,1,2,2};
    printf("请输入人头领先数（负数为落后）：\n");
    scanf("%d",&testSet[0]);
    printf("请输入经济领先数（负数为落后，单位为k）：\n");
    scanf("%d",&testSet[1]);
    printf("请输入活着的人头领先数（负数为落后）：\n");
    scanf("%d",&testSet[2]);
    printf("请输入推塔领先数（负数为落后）：\n");
    scanf("%d",&testSet[3]);
    int *threshold=(int*)malloc((K-1)*sizeof(int));
    float *dis=(float*)malloc(numTrain*sizeof(float));
    int *x=(int*)malloc(K*sizeof(int));
    for(i=0;i<numTrain;i++)
    {
        dis[i]=0.0;
        for(j=0;j<numAttr;j++)
            dis[i]+=(float)(trainSet[i][j]-testSet[j])*(float)(trainSet[i][j]-testSet[j]);
        //printf("dis[%d]=%f\n",i,dis[i]);
    }
    while(numX<K)
    {
        if(numX==0)
        {
            for(i=0;i<numTrain;i++)
            {
                if(dis[minX]>dis[i])
                    minX=i;
            }
            //printf("first min is dis[%d]=%f\n",minX,dis[minX]);
            x[0]=minX;
            numX++;
            threshold[0]=minX;
        }
        else
        {
            minX=0;
            for(i=0;i<numTrain;i++)
            {
                if(dis[minX]>dis[i])
                {
                    int cnt=0;
                    for(j=0;j<numX;j++)
                    {
                        if(threshold[j]!=i)
                        {
                            cnt++;
                        }
                    }
                    if(cnt==numX)
                    {
                        minX=i;
                        threshold[numX]=i;
                    }
                }
            }
            x[numX]=minX;
            numX++;
        }
    }
    printf("the shortest %d dis is:\n",K);
    for(i=0;i<K;i++)
    {
        printf("dis[%d]=%f\n",threshold[i],dis[x[i]]);
    }
    for(i=0;i<K;i++)
    {
        printf("%d",trainSet[threshold[i]][numAttr]);
        if(trainSet[threshold[i]][numAttr]==1)
            draCnt++;
        else if(trainSet[threshold[i]][numAttr]==2)
            turCnt++;
        else
            groCnt++;
    }
    printf("In its %d nearest neighbors:\ndragon for :%d\nturret for : %d\ngrow for : %d\n",K,draCnt,turCnt,groCnt);
    int temp=0;
    if(draCnt>=turCnt&&draCnt>=groCnt)
        printf("召唤师，您现在应该打龙!\n");
    else if(groCnt>=turCnt&&groCnt>=draCnt)
        printf("召唤师，您现在应该发育!\n");
    else if(turCnt>=groCnt&&turCnt>=draCnt)
        printf("召唤师，您现在应该推塔!\n");
    printf("Hello world!\n");
    return 0;
}
