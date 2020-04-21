#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main()
{
	int card[4];
	char word[20];
	char c;
	printf("******************************\n");
	printf("	  ��ӭ����24����Ϸ\n");
	do
	{
		getcard(card);		//������ɿ��� 
		printf("�����õ���4��������ƺ�Ϊ(��L����10)��\n");
		printcard(card);			//������ƺ� 
		printf("�밴������鿴�������L����10��\n");
		getchar();		//��ȡ�����ļ� 
		printresult(card,word); 		//������������� 
		printf("\n������Ϸ�밴�س����������밴������\n");
        c=getchar();//�������ļ��������C 
	}
	while(c=='\n');			//�ж������ļ��������Ƿ������Ϸ 
	return 0;

}

int getcard(int *card)						//��������� 
{
	int i;
	srand((unsigned)time(NULL));			 //����ϵͳʱ����Ϊ���Ӳ��������
    for(i=0;i<4;i++)
    {
        card[i]=rand()%12+1;			//��rand�����������������ΧΪ1-13 
    }
    return;
}

int printcard(int *card)		//�������õ��Ŀ��ƺ� 
{
	int i;
	for(i=0;i<4;i++)
	{
	/*	if(card[i]==10)
		{
			printf("%d  ",card[i]);
		}
		else
		{*/
			printf("%c  ",getcardcard(card[i]));
		//}
	}
	printf("\n");
	return;
}

int getcardcard(int a)				//���������ת��Ϊ���ƺ� 
{
	if(a==1)
	{
		return 'A';
	}
	else if(a<10)
	{
		return a+'0';
	}
	else if(a==10)
	{
		return 'L';
	 } 
	else if(a==11)
	{
		return 'J';
	}
	else if(a==12)
	{
		return 'Q';
	}
	else if(a==13)
	{
		return 'K';
	}
}



int printresult(int *card,char *word)			//�õ�������
{	
	char b[4]={'+','-','*','/'};
	char operator[3];
	int i,j,k,t=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<4;k++)
			{
				operator[0]=b[i];
				operator[1]=b[j];
				operator[2]=b[k];
				if(getresult(card,operator,word))
				t++;
			}
		}
	}
	if(t!=0)
	{
		printf("����%d�ֽ�\n",t);
	}
	else
	{
		printf("������޽�\n");
	}
	return;
}

void printword(int flag,int *card,char *operator,char *word)		//��������Ľ�� 
{
    char a=getcardcard(card[0]);
    char b=getcardcard(card[1]);
    char c=getcardcard(card[2]);
    char d=getcardcard(card[3]);
     
    switch(flag)
    {
        //1.((A*B)*C)*D
        case 1:
            printf("((%c%c%c)%c%c)%c%c=24\n",a,operator[0],b,operator[1],c,operator[2],d);
            break;
        //2.(A*(B*C))*D
        case 2:
            printf("(%c%c(%c%c%c))%c%c=24\n",a,operator[0],b,operator[1],c,operator[2],d);
            break;
        //3.(A*B)*(C*D)
        case 3:
            printf("(%c%c%c)%c(%c%c%c)=24\n",a,operator[0],b,operator[1],c,operator[2],d);
            break;
        //4.A*(B*(C*D))
        case 4:
            printf("%c%c(%c%c(%c%c%c))=24\n",a,operator[0],b,operator[1],c,operator[2],d);
            break;
        //5.A*((B*C)*D) 
        case 5:
            printf("%c%c((%c%c%c)%c%c)=24\n",a,operator[0],b,operator[1],c,operator[2],d);
            break;
        default:
            break;
    }
}

double getvalue(double num1,double num2,char operator)		//���������ļ����� 
{
    double result;
     
    switch(operator)
    {
        case '+':
        result=num1+num2;
        break;
        case '-':
        result=fabs(num1-num2);
        break;
        case '*':
        result=num1*num2;
        break;
        case '/':
        result=num1/num2;
        break;
        default :
        break;
    }
    return result;
}    
    
 
int getresult(int *card,char *operator,char *word)
{
    double t;
    //������ֵȡ�� 
    int a=card[0]>10?1:card[0];	
    int b=card[1]>10?1:card[1];
    int c=card[2]>10?1:card[2];
    int d=card[3]>10?1:card[3];
     
    //����������
    //1.((A*B)*C)*D
    t=0;
    t=getvalue(a,b,operator[0]);				//ͨ���ֲ����getvalue�������ﵽ���ŵ�Ч�� 
    t=getvalue(t,c,operator[1]);
    t=getvalue(t,d,operator[2]);
    
    if(fabs(t-24)<0.0001)		//fabs���������ֵ 
    {
        printword(1,card,operator,word);
        return 1;
    }
    
    //2.(A*(B*C))*D
    t=0;
    t=getvalue(b,c,operator[1]);	//������������ڵı��ʽ������ 
    t=getvalue(a,t,operator[0]);	//��������������ڵı��ʽ������ 
    t=getvalue(t,d,operator[2]);	//���������ʽ�Ľ�� 
    
    if(fabs(t-24)<0.0001)		//�жϽ���Ƿ�Ϊ24 
    {
        printword(2,card,operator,word);
        return 1;
    }
    
    //3.(A*B)*(C*D)
    t=0;
    t=getvalue(getvalue(a,b,operator[0]),getvalue(c,d,operator[2]),operator[1]);
    
    if(fabs(t-24)<0.0001)
    {
        printword(3,card,operator,word);
        return 1;
    }
    
    //4.A*(B*(C*D))
    t=0;
    t=getvalue(c,d,operator[2]);
    t=getvalue(b,t,operator[1]);
    t=getvalue(a,t,operator[0]);
    
    if(fabs(t-24)<0.0001)
    {
        printword(4,card,operator,word);
        return 1;
    }
    
    //5.A*((B*C)*D) 
    t=0;
    t=getvalue(b,c,operator[1]);
    t=getvalue(t,d,operator[2]);
    t=getvalue(a,t,operator[0]);
    
    if(fabs(t-24)<0.0001)
    {
        printword(5,card,operator,word);
        return 1;
    }
     return 0;
 }
