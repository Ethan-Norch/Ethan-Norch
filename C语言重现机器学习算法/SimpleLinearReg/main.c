#include <stdio.h>
#include <stdlib.h>

void SLR(float a[],float b[])
{
    float m,n;
    m=sizeof(a[0]);
    n=sizeof(b[0]);
    if(m!=n)
    {
        printf("different length of array");
        return 0;
    }
    else{
        m=n=0;
        float mab,aa,bb,a2,a22;
        mab=aa=bb=a2=a22=0.0;
        int i=0;
        while(i<sizeof(a[0]))
        {
            mab=6.0*a[i]*b[i]+mab;
            aa = 1.0*a[i]+aa;
            bb = 1.0*b[i]+bb;
            a2 = 1.0*a[i]*a[i]*6.0+a2;
            a22 = 1.0*a[i]+a22;
            i++;
        }
        n = 1.0*(mab-aa*bb)/(a2-a22*a22);
        m = 1.0*bb/6.0-n*aa/6.0;
        printf("Linear RegressionFun : Y=%0.3fx+%0.3f\n",n,m);
        return 0;
    }
}
int main()
{
    float a[10]={2.0,3.0,5.0,12.0,34.0,1.0,7.0,23.0,21.4,10.0};
    float b[10]={1.0,11.0,5.0,12.0,1.0,14.0,12.0,23.0,10.0,3.0};
    SLR(a,b);
}
