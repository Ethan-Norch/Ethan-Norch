#include <stdio.h>
#include <stdlib.h>
//#define N 3
int main()
{

    float x[10]={1,2,3,4,5,6,7,8,9,10};
    //float y[10]={5.56,5.7,5.91,6.4,6.8,7.05,8.9,8.7,9,9.05};
    int num,N,n,i,j,minIndex,cnt=0;
    printf("please enter num for X:{1,2,3,4...num}\n");
    scanf("%d",&num);
    float *y=(float*)malloc(n*sizeof(float));
    printf("please enter y value:\n");
    for(i=0;i<num;i++)
        scanf("%f",&y[i]);
    printf("please enter the area regression trees separates:\n");
    scanf("%d",&N);
    float *ans=(float*)malloc(N*sizeof(float));
    float *ansX=(float*)malloc((N-1)*sizeof(float));
    float temp,min;
    n=num-1;
    float *p=(float*)malloc(n*sizeof(float));
    float *c1=(float*)malloc(n*sizeof(float));
    float *c2=(float*)malloc(n*sizeof(float));
    while(cnt<N-1)
    {
        if(cnt!=0)
            n=minIndex;
        float *p=(float*)malloc(n*sizeof(float));
        float *c1=(float*)malloc(n*sizeof(float));
        float *c2=(float*)malloc(n*sizeof(float));
    for(i=0;i<n;i++)
    {
        p[i]=(float)i+1.5;
    }
    //for(i=0;i<n;i++)
    //{
    //    printf("%f\t",p[i]);
    //}
    for(i=0;i<n;i++)
    {
        temp=0.0;
        for(j=0;j<=i;j++)
            temp+=y[j];
        c1[i]=temp/(float)(i+1);
        //printf("%f\t",c1[i]);
    }
    for(i=0;i<n;i++)
    {
        temp=0.0;
        for(j=n;j>=i+1;j--)
            temp+=y[j];
        c2[i]=temp/(float)(n-i);
        //printf("%f\t",c2[i]);
    }
    float *m=(float*)malloc(n*sizeof(float));
    float *minc1=(float*)malloc(n*sizeof(float));
    float *minc2=(float*)malloc(n*sizeof(float));
    for(i=0;i<n;i++)
    {
        minc1[i]=0.0;
        for(j=0;j<=i;j++)
            minc1[i]+=(c1[i]-y[j])*(c1[i]-y[j]);
       // printf("minc1:%f\t",minc1[i]);
    }
    for(i=0;i<n;i++)
    {
        minc2[i]=0.0;
        for(j=n;j>=i+1;j--)
            minc2[i]+=(c2[i]-y[j])*(c2[i]-y[j]);
       // printf("minc2:%f\t",minc2[i]);
    }
    printf("\n");
    for(i=0;i<n;i++)
    {
        m[i]=minc1[i]+minc2[i];
        //printf("m=%f\t",m[i]);
    }
    minIndex=0;
    for(i=0;i<n;i++)
    {
        if(m[minIndex]>m[i])
            minIndex=i;
    }
    printf("%d\n%f\n%f\n%f\n",minIndex,p[minIndex],c2[minIndex],c1[minIndex]);
    if(cnt==0)
    {
        ans[0]=c2[minIndex];
        ansX[0]=p[minIndex];
    }
    else
    {
        ansX[cnt]=p[minIndex];
        ans[cnt]=c2[minIndex];
        if(cnt==N-2)
            ans[cnt+1]=c1[minIndex];


    }
    free(p);
    free(c1);
    free(c2);
    free(m);
    free(minc1);
    free(minc2);
    cnt++;
    }
    printf("finished the regressionTree:\n");
    printf("  T  =  ");
    for(i=N;i>0;i--)
        if(i==N)
            printf("%f\tX<%f\n",ans[i-1],ansX[i-2]);
        else if(i==1)
            printf("\t%f\t%f<=X\n",ans[i-1],ansX[i-1]);
        else
            printf("\t%f\t%f<=X<%f\n",ans[i-1],ansX[i-1],ansX[i-2]);

    return 0;
}
