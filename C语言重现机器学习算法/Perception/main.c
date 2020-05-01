#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    int num,n,i,j,fin=0,t,cnt=0,m=0;
    float a,b=0.0;
    printf("please enter number of characteristics:\n");
    scanf("%d",&num);
    printf("please enter number of samples:\n");
    scanf("%d",&n);
    printf("please enter value of ylta:\n");
    scanf("%f",&a);
    printf("please enter times of interaction:\n");
    scanf("%d",&t);
    float *y=(float*)malloc(num*sizeof(float));
    for(i=0;i<num;i++)
        y[i]=0;
    float *temp=(float*)malloc(num*sizeof(float));
    float **arr=(float**)malloc(n*sizeof(float*));
    float *w=(float*)malloc(num*sizeof(float));
    for(i=0;i<num;i++)
    {
        arr[i]=(float*)malloc((num+1)*sizeof(float));
    }
    printf("please enter arr for x1 x2 x3 ... xn y for each samples\n");
    for(i=0;i<n;i++)
        for(j=0;j<num+1;j++)
            scanf("%f",&arr[i][j]);
    printf("the sample is:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<num+1;j++)
            printf("%f\t",arr[i][j]);
            printf("\n");
    }
    srand((unsigned)time(NULL));
    printf("creating w:\n");
    for(i=0;i<num;i++)
    {
        w[i]=((float)rand()/RAND_MAX);
        printf("w%d £º%.5f\n",i+1,w[i]);
    }
    while(cnt<t&&fin==0)
    {
        i=0;
        while(i<n)
        {
            for(j=0;j<num;j++)
            {
                y[i]=y[i]+w[j]*arr[i][j]+b;
            }
            if(y[i]>=0)
            {
                y[i]=1;
            }
            else
            {
                y[i]=-1;
            }
            i++;
        }
        i=0;
        while(i<n)
        {
            for(j=0;j<num;j++)
            {
                temp[j]=w[j];
                w[j]+=a*(arr[i][num]-(float)y[i])*arr[i][j]/2;
            }
            b+=(arr[i][num]-y[i])/2;
            i++;
        }
        printf("interaction for %d times:\n",cnt+1);
        for(j=0;j<num;j++)
            printf("w%d : %.5f\n",j+1,w[j]);
        printf("b : %.5f\n",b);
        cnt++;
        for(i=0;i<num;i++)
        {
            if(w[i]==temp[i]&&cnt<t)
                m++;
        }
    printf("m=%d\n",m);
        if(m==num&&cnt<t)
        {
            printf("interaction finished\n");
            for(i=0;i<num;i++)
                printf("w%d : %f\n",i+1,w[i]);
            printf("b : %.5f",b);
            fin=1;
            return 0;
        }
        if(cnt>t)
        {
            printf("interaction failed\n");
            return 0;
        }
    }

}
