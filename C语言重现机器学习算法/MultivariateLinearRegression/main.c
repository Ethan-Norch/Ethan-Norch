#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void freeData(float **dat,float *d,int cnt)
{
    int i=0;
    free(d);
    while(i<cnt)
    {
        free(dat[i]);
        i++;
    }
    free(dat);
}
//calculate linear function
//data[cnt*(cnt+1)] matrix  cnt demension.
int linearAns(float *data,int cnt,float *ans)
{
    int i,j,k,l;
    float tmp,**dat,*p=data;
    dat=(float**)malloc(cnt*sizeof(float*));
    j=0;
    float *a;
    a=(float*)malloc(sizeof(float));
    while(j<cnt)
    {
        dat[j]=(float*)malloc((cnt+1)*sizeof(float));
        memcpy(dat[j],p,(cnt+1)*sizeof(float));
        j++;
        p=p+cnt+1;
    }
    p=(float*)malloc((cnt+1)*sizeof(float));
    j=0;
    while(j<cnt-1)
    {
        k=j+1;
        while(k<cnt&&dat[j][j]==0.0)
        {
            if(dat[k][j]!=0.0)
            {
                memcpy(p,dat[j],(cnt+1)*sizeof(float));
                memcpy(dat[j],dat[k],(cnt+1)*sizeof(float));
                memcpy(dat[k],p,(cnt+1)*sizeof(float));
            }
            k++;
        }
        if(dat[j][j]==0.0)
        {
            freeData(dat,p,cnt);
            return -1;
        }
        //xiao yuan
        k=j+1;
        while(k<cnt)
        {
            tmp=dat[k][j]/dat[j][j];
            l=j;
            while(l<=cnt)
            {
                dat[k][l]=dat[k][l]-tmp*dat[j][l];
                l++;
            }
            k++;
        }
        j++;
    }
    l=0;
    while(l<cnt)
    {
        p[l]=0.0;
        l++;
    }
    ans[cnt-1]=dat[cnt-1][cnt]/dat[cnt-1][cnt-1];
    j=cnt-2;
    while(j>=0)
    {
        l=cnt-1;
        while(l>j)
        {
            p[j]=p[j]+ans[l]*dat[j][l];
            l--;
        }
        ans[j]=(dat[j][cnt]-p[j])/dat[j][j];
        j--;
    }
    free(a);
    freeData(dat,p,cnt);
    return 0;
}
int multiReg(float *arr,int row,int col,float *ans)
{
    int i,j,k,cnt;
    printf("row is %d\n",row);
    printf("col is %d\n",col);
    cnt=col-1;
    float *dat,*d,m,n;
    if(arr==0||ans==0||row<2||col<2)
        return -1;
    dat=(float*)malloc(col*(col+1)*sizeof(float));
    dat[0]=(float)row;
    j=0;
    while(j<cnt)
    {
        m=n=0.0;
        d=arr+j;
        k=0;
        while(k<row)
        {
            m=m+*d;
            n=n+*d**d;
            k++;
            d=d+col;
        }
        dat[j+1]=m;
        dat[(j+1)*(col+1)]=m;
        dat[(j+1)*(col+1)+j+1]=n;
        i=j+1;
        while(i<cnt)
        {
            m=0.0;
            d=arr;
            k=0;
            while(k<row)
            {
                m=m+(d[j]*d[i]);
                k++;
                d=d+col;
            }
            dat[(j+1)*(col+1)+i+1]=m;
            dat[(i+1)*(col+1)+j+1]=m;
            i++;
        }
        j++;
    }
    n=0.0;
    k=0;
    d=arr+j;
    while(k<row)
    {
        n+=*d;
        k++;
        d=d+col;
    }
    dat[col]=n;
    j=0;
    while(j<cnt)
    {
        m=0.0;
        d=arr;
        k=0;
        while(k<row)
        {
            m=m+(d[j]*d[cnt]);
            k++;
            d=d+col;
        }
        dat[(j+1)*(col+1)+col]=m;
        j++;
        d=d+col;
    }
    j=linearAns(dat,col,ans);
}
void dis(int col,float *ans)
{
    printf("the multiple regressionFunction  :  Y=%.3f",ans[0]);
    for(int i=1;i<col;i++)
        printf("+(%.3f*x%d)",ans[i],i);
}
int main()
{
    //float Arr[5][4]={
    //{123,496,176,300},{100,655,234,654},{234,643,231,123},{657,3545,3434,343},{4343,543,543,232}};
    //printf("%d,%d\n",sizeof(Arr)/sizeof(Arr[0]),sizeof(Arr[0])/sizeof(Arr[0][0]));
    int m,n,j,k,l;
    printf("please enter m n for array[m][n]:\n");
    scanf("%d%d",&m,&n);
    float **a=(float **)malloc(m * sizeof(float *));
    for(int i=0;i<m;i++)
    {
        a[i]=(float *)malloc(n * sizeof(float));
    }
    printf("please enter array for X1 X2 X3 ... Xn Y:\n");
    for(j=0;j<m;j++)
    {
        for(k=0;k<n;k++)
            scanf("%f",&a[j][k]);
    }
    printf("the array[%d][%d] is:\n",m,n);
    for(j=0;j<m;j++)
    {
        for(k=0;k<n;k++)
            printf("%f\t",a[j][k]);
        printf("\n");
    }
    float *ans=(float*)malloc(n*sizeof(float));
    for(int i=0;i<n;i++)
        ans[i]=0;
    //float ans[4];
    if(multiReg((float*)a,m,n,ans)==0)
    {
        dis(n,ans);
    }
    else
    {
        printf("wrong put in");
    }

    return 0;
}
