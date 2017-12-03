#if 0


/* 
* Copyright (c) 2016, ��̨��ѧ���������ƹ���ѧԺ 
* All rights reserved. 
* �ļ����ƣ��ǵݹ飬�������ݽṹ����ջʵ��N�ʺ�
* ��    �ߣ����� 
* ������ڣ�2016��4��4�� 
* �� �� �ţ�v1.0 
*/  
#include <iostream>  
#include <malloc.h>  
#include <cstdio>  
#include <cmath>  
#include <windows.h>
using namespace std;  
const int MaxSize=INT_MAX/100;  
  
typedef struct linknode//˳��ջ  
{  
    int data[MaxSize];  
    int top;  
} SqStack;  
SqStack *st;  
  
void initStack(SqStack *&s)//��ʼ��  
{  
    s=(SqStack *)malloc(sizeof(SqStack));  
    s->top=-1;  
}  
  
bool Push(SqStack *&s,int e)//ѹ��ջ  
{  
    if(s->top==MaxSize-1)  
        return false;  
    s->top++;  
    s->data[s->top]=e;  
    return true;  
}  
  
bool Pop(SqStack *&s)//�Ƴ�ջ��Ԫ��  
{  
    if(s->top==-1)  
        return false;  
    s->top--;  
    return true;  
}  
  
bool GetTop(SqStack *s,int &e)//ȡջ��Ԫ��  
{  
    if(s->top==-1)  
        return false;  
    e=s->data[s->top];  
    return true;  
}  
  
bool StackEmpty(SqStack *s)//�ж�ջ�Ƿ�Ϊ��  
{  
    return(s->top==-1);  
}  
  
void DestroyStack(SqStack *&s)//����ջ  
{  
    free(s);  
}  
  
bool Check(int *qu, int t)//�ܷŷ����棬����Ϊ��  
{  
    int i;  
    for(i=0; i<t; i++)//�����ж�  
        if(qu[i]==qu[t]||abs(t-i)==abs(qu[t]-qu[i]))//��ͬһ�л�Խ���  
            return false;  
    return true;  
}  
  
void Show(int *qu, int len,int Count)  
{  
    int i;  
    cout<<"��"<<++Count<<"���⣺";  
    for(i=0; i<len; i++)//i������  
        cout<<"("<<i<<", "<<qu[i]<<") ";  
    cout<<endl;  
}  
  
//��˼·����
//queen[row]�����¼��row���ϻʺ����λ�ã�
//stջ��¼��ǰ������
//�ӵ�0�п�ʼ��������̽0-->n-1�У�
//��row==n-1˵��ȫ���ɹ����ûʺ�
//��queen[row]>=n˵����ǰ���£�������̽��ϣ������ܳɹ����ã�����Ҫ���ݵ���һ�У�����ǰ�г�ջ.��
int main()  
{  
    initStack(st);//��ʼ��  
    cout<<"�ʺ����⣨n<20�� n=";  
    int n;  
    cin>>n;//����ʺ���Ŀ  
    cout<<n<<"�ʺ�����������£�"<<endl;  
    int cnt=0,row=0;//����Ľ����Ŀ����  
    int *queen = new int[n];//���ٶ�̬���鱣��ÿ�лʺ����λ��  
    queen[0]=-1;//�ʼ����Ԫ����Ϊ-1  
    Push(st,0);//����λ��ѹ��ջ  

	/*ʱ���ʱ����*/
	LARGE_INTEGER t1,t2,tc;//����ʱ�����
	QueryPerformanceFrequency(&tc);//
	QueryPerformanceCounter(&t1);//


    while(!StackEmpty(st))//ջ�ǿ�  
    {  
        GetTop(st,row);//row�ǵ�ǰջ��Ԫ��ֵ  
        queen[row]++;//������һ��  
        if(queen[row]>=n)//��ǰ�е�����n�ж��Ѿ����Թ������ǻʺ�û�аڷųɹ�  
            Pop(st);//ջ��Ԫ�س�ջ���൱�ڻ��ݵ���һ��  
        else  
        {  
            if(Check(queen,row))//��飬������ڸ�λ�÷Żʺ�  
            {  
                if(row==n-1)//��̽����n��  
                {  
                    Show(queen,n,cnt);//����ʺ�λ��  
                    cnt++;//�ⷨ��һ  
                }  
                else//����Ҫ��̽  
                {  
                    queen[row+1]=-1;//���-1  
                    Push(st,row+1);//�ʺ��λ��ѹ��ջ  
                }  
            }  
        }  
    }  

	QueryPerformanceCounter(&t2);//����ʱ��
	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//��ӡ��ʱ

    delete []queen;//�ͷŶ�̬����  
    free(st);//����ջ  
    return 0;  
}  
#endif