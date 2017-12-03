#include<iostream>
#include<stdio.h>
using namespace std;
const int MaxSize=50;
double InputReal2()
{
	char str[MaxSize];
	char * p=str;
	int flag;
	do{
		cout<<"Input a realnumble,Please!"<<endl;
		cin.clear();
		cin.sync();
		cin.getline(str,sizeof(str));
		flag=0;
		p=str;
		if(*p=='-'||*p=='+')p++;
		for(int count=0;*p!='\0'&&flag==0;p++)
		{

			switch (*p)
			{
				case '.':
					count++;
					if(count>1)flag=1;
					/*
				case '-':
					count1++;
					if(count>1)flag=1;
				case '+':
					count2++;
					if(count>1)flag=1;
					*/
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					break;
				default:
					flag=1;
			
			}
	
		
		}

	}while (flag);
	//cout<<str;

	return (strToDouble(str));
}
double strToDouble(const char str[])
{
	int flag=1,flag2;
	double dd=0.0;//保存整数部分
	double dx=0.0;//保存小数部分
	const char * p=str;
	if(*p=='-'||*p=='+')
	{
		if(*p=='-')	flag2=-1;
		p++;
	}
	for(int count=1;*p!='\0'&&flag;p++,count*=10)//处理整数部分
	{
			
			switch (*p)
			{
				
				case '0':dd=dd*count;break;
				case '1':dd=1+dd*count;break;
				case '2':dd=2+dd*count;break;
				case '3':dd=3+dd*count;break;
				case '4':dd=4+dd*count;break;
				case '5':dd=5+dd*count;break;
				case '6':dd=6+dd*count;break;
				case '7':dd=7+dd*count;break;
				case '8':dd=8+dd*count;break;
				case '9':dd=9+dd*count;break;
				case '.':flag=0;break;
			
			}
	}
	if(!flag)
		for(int count=1/10;*p!='\0';p++,count/=10)//处理小数部分
		{
			
				switch (*p)
			{
					
				case '0':dx=dx;break;
				case '1':dx=dx+1*count;break;
				case '2':dx=dx+2*count;break;
				case '3':dx=dx+3*count;break;
				case '4':dx=dx+4*count;break;
				case '5':dx=dx+5*count;break;
				case '6':dx=dx+6*count;break;
				case '7':dx=dx+7*count;break;
				case '8':dx=dx+8*count;break;
				case '9':dx=dx+9*count;break;
			}		
		}
	return(dd+dx);
}