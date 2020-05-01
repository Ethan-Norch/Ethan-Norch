#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define numAttr 5
#define numTrain 15
//attr:homework(deadline/done/almost) being(well/normal/bad) time(morning/afternoon/evening) friends(lots/few) moods(good/normal/bad) gotoparty?(yes/no)
int main()
{
    char trainSet[numTrain][numAttr+1][10]={
    {"deadline","well","evening","few","normal","no"},
    {"done","normal","afternoon","lots","good","yes"},
    {"almost","bad","evening","lots","normal","no"},
    {"done","well","evening","lots","normal","yes"},
    {"almost","normal","afternoon","few","bad","no"},
    {"deadline","well","morning","lots","normal","yes"},
    {"almost","well","afternoon","few","normal","no"},
    {"almost","bad","morning","few","normal","no"},
    {"done","bad","afternoon","lots","bad","no"},
    {"done","well","morning","lots","good","yes"},
    {"deadline","well","morning","few","good","yes"},
    {"almost","normal","evening","lots","normal","yes"},
    {"done","normal","morning","lots","normal","yes"},
    {"deadline","normal","afternoon","lots","good","yes"},
    {"deadline","bad","evening","lots","bad","no"}};
    char testSet[numAttr][10]={0};
    printf("please enter whether you've finished you homework for(almost/done/deadline):\n");
    scanf("%s",testSet[0]);
    printf("please enter your body condition for(well/normal/bad):\n");
    scanf("%s",testSet[1]);
    printf("please enter the time that party starts for(morning/afternoon/evening):\n");
    scanf("%s",testSet[2]);
    printf("please enter the number of your friends participating in the party for(lots/few):\n");
    scanf("%s",testSet[3]);
    printf("please enter your moods today for(good/normal/bad):\n");
    scanf("%s",testSet[4]);
    int i,yesNum=0,noNum=0,j,yesCnt,noCnt;
    printf("Your test data:\n");
    for(i=0;i<numAttr;i++)
    {
        printf("%s\t",testSet[i]);
    }
    for(i=0;i<numTrain;i++)
    {
        //printf("%s\n",trainSet[i][numAttr]);
        if(strcmp(trainSet[i][numAttr],"yes")==0)
            yesNum++;
        else
            noNum++;
    }
    //printf("yesNum:%d\n",yesNum);
    float Pyes,Pno,Pyestmp,Pnotmp;
    float PattrY[numAttr],PattrN[numAttr];
    float Ppre[numAttr]={(float)0.333,(float)0.333,(float)0.333,(float)0.5,(float)0.333};
    printf("prePossibility:\n");
    for(i=0;i<numAttr;i++)
        printf("%f\n",Ppre[i]);
    Pyes=(float)yesNum/(float)numTrain;
    Pno=(float)noNum/(float)numTrain;
    i=0;
    while(i<numAttr)
    {
        yesCnt=0;
        noCnt=0;
        for(j=0;j<numTrain;j++)
        {
            if(strcmp(trainSet[j][numAttr],"yes")==0)
            {
                if(strcmp(testSet[i],trainSet[j][i])==0)
                    yesCnt++;
            }
            else if(strcmp(trainSet[j][numAttr],"yes")==0)
            {

                if(strcmp(testSet[i],trainSet[j][i])==0)
                    noCnt++;
            }
            PattrY[i]=((float)yesCnt+(float)numTrain*Ppre[i])/(float)(yesNum+numTrain);
            PattrN[i]=((float)noCnt+(float)numTrain*Ppre[i])/(float)(noNum+numTrain);
        }
        i++;
    }
    i=0;
    while(i<numAttr)
    {
        Pyes*=PattrY[i];
        Pno*=PattrN[i];
        i++;
    }
    Pyestmp=Pyes/(Pyes+Pno);
    Pnotmp=Pno/(Pyes+Pno);
    printf("test possibility for going to the party is : %f\ntest possibility for not going to the party is : %f\n",Pyestmp,Pnotmp);
    if(Pyestmp>Pnotmp)
        printf("yes!you can go to the party!\n");
    else
        printf("for some reasons you'd better not go to the party.\n");
    return 0;
}
