#if 0


/* 
* Copyright (c) 2016, 烟台大学计算机与控制工程学院 
* All rights reserved. 
* 文件名称：非递归，利用数据结构——栈实现N皇后
* 作    者：单昕昕 
* 完成日期：2016年4月4日 
* 版 本 号：v1.0 
*/  
#include <iostream>  
#include <malloc.h>  
#include <cstdio>  
#include <cmath>  
#include <windows.h>
using namespace std;  
const int MaxSize=INT_MAX/100;  
  
typedef struct linknode//顺序栈  
{  
    int data[MaxSize];  
    int top;  
} SqStack;  
SqStack *st;  
  
void initStack(SqStack *&s)//初始化  
{  
    s=(SqStack *)malloc(sizeof(SqStack));  
    s->top=-1;  
}  
  
bool Push(SqStack *&s,int e)//压入栈  
{  
    if(s->top==MaxSize-1)  
        return false;  
    s->top++;  
    s->data[s->top]=e;  
    return true;  
}  
  
bool Pop(SqStack *&s)//移除栈顶元素  
{  
    if(s->top==-1)  
        return false;  
    s->top--;  
    return true;  
}  
  
bool GetTop(SqStack *s,int &e)//取栈顶元素  
{  
    if(s->top==-1)  
        return false;  
    e=s->data[s->top];  
    return true;  
}  
  
bool StackEmpty(SqStack *s)//判断栈是否为空  
{  
    return(s->top==-1);  
}  
  
void DestroyStack(SqStack *&s)//销毁栈  
{  
    free(s);  
}  
  
bool Check(int *qu, int t)//能放返回真，否则为假  
{  
    int i;  
    for(i=0; i<t; i++)//逐行判断  
        if(qu[i]==qu[t]||abs(t-i)==abs(qu[t]-qu[i]))//在同一列或对角线  
            return false;  
    return true;  
}  
  
void Show(int *qu, int len,int Count)  
{  
    int i;  
    cout<<"第"<<++Count<<"个解：";  
    for(i=0; i<len; i++)//i是行数  
        cout<<"("<<i<<", "<<qu[i]<<") ";  
    cout<<endl;  
}  
  
//【思路】：
//queen[row]数组记录第row行上皇后的列位置；
//st栈记录当前行数；
//从第0行开始，依次试探0-->n-1列；
//当row==n-1说明全部成功放置皇后；
//当queen[row]>=n说明当前行下，各列试探完毕，都不能成功放置，所以要回溯到上一行，将当前行出栈.。
int main()  
{  
    initStack(st);//初始化  
    cout<<"皇后问题（n<20） n=";  
    int n;  
    cin>>n;//输入皇后数目  
    cout<<n<<"皇后问题求解如下："<<endl;  
    int cnt=0,row=0;//问题的解的数目、行  
    int *queen = new int[n];//开辟动态数组保存每行皇后的列位置  
    queen[0]=-1;//最开始把首元素置为-1  
    Push(st,0);//把首位置压入栈  

	/*时间计时函数*/
	LARGE_INTEGER t1,t2,tc;//定义时间变量
	QueryPerformanceFrequency(&tc);//
	QueryPerformanceCounter(&t1);//


    while(!StackEmpty(st))//栈非空  
    {  
        GetTop(st,row);//row是当前栈顶元素值  
        queen[row]++;//尝试下一列  
        if(queen[row]>=n)//当前行的所有n列都已经尝试过，但是皇后没有摆放成功  
            Pop(st);//栈顶元素出栈，相当于回溯到上一行  
        else  
        {  
            if(Check(queen,row))//检查，如果能在该位置放皇后  
            {  
                if(row==n-1)//试探到第n行  
                {  
                    Show(queen,n,cnt);//输出皇后位置  
                    cnt++;//解法加一  
                }  
                else//仍需要试探  
                {  
                    queen[row+1]=-1;//标记-1  
                    Push(st,row+1);//皇后的位置压入栈  
                }  
            }  
        }  
    }  

	QueryPerformanceCounter(&t2);//结束时间
	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//打印耗时

    delete []queen;//释放动态数组  
    free(st);//销毁栈  
    return 0;  
}  
#endif