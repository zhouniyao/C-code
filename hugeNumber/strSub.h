#include <string>
#include <iostream>
using namespace std;
extern void integerAdd(char *c,const char *a,const char *b,int k,int i,int j,int flag);
extern void jumpZero(char * nptr);
extern int findDot(const char *nptr);//返回小数点位

//剔除小数点
char *removeDot(char *tmp, const char *nptr)
{
	int i=0,j=0;
	for(;nptr[i] != '\0';i++)
	{
		if(nptr[i] == '.')continue;
		tmp[j++] = nptr[i];
	}
	 tmp[j] = '\0';
	return tmp;
}


//按照字符数组长度，比较其数值型大小,s1子串大于s2子串返回1，相等返回0，s1子串小于s2子串返回-1。
int my_strcmp(const char *s1, const char * s2, int i, int j, int m, int n)//i-j为s1子串起止位，m-n为s2子串起止位
{
	int d1 = j + 1 - i;//子串从0开始的长度
	int d2 = n + 1 - m;
	char * tmp1 = new char[d1];
	char * tmp2 = new char[d2];
	for(int k = 0; k < d1; k++)
	{
		tmp1[k] = s1[i + k];
	}
	tmp1[d1] = '\0';
	for(int k = 0; k < d2; k++)
	{
		tmp2[k] = s2[i + k];
	}
	tmp2[d2] = '\0';
	return(strcmp(tmp1,tmp2));
}
//整数字符串数组相减c = a - b;并规定 a > b
void integerSub(char *c,const char *a,const char *b,int k,int i,int j,int refund)//a，b都没有小数，k为c数组长度，i为a数组长度……refund为退还 1 标识
{
	// k = a;
	c[k] = '\0';
	k--;i--;j--;//剔除最后的标记结束位
	while(j >= 0)
	{
		if(a[i] < b[j])//不够减
		{
			c[k] = a[i] - (b[j] -  '0') + 10;
			if(refund)c[k] -= 1;//兑换之前的借位
			refund = 1;			//a 数组向前一位借位
		}
		else if(a[i] == b[j])
		{
			if(!refund)c[k] = '0';
			else//兑换之前的借位
			{
				c[k] = '9';
				refund = 1;	
			}
		}
		else
		{
			c[k] = a[i] - (b[j] -  '0');
			if(refund)c[k] -= 1;//兑换之前的借位
			refund = 0;
		}
		k--;i--;j--;
	}
	while(i >= 0)
	{
		c[k] = a[i];
		if(refund)c[k] -= 1;//兑换之前的借位
		if(c[k] < '0')
		{
			refund = 1;
			c[k] += 10;
		}
		k--;i--;
	}
}

//数值型字符串相减，sign返回正负
char * strSub(char *c , const char *a, const char *b, int &sign)  //c = a - b, sign返回符号
{
	int i = findDot(a);//尾数a小数点位
	int j = findDot(b);//尾数b小数点位
	
	int refund = 0;
	//==============================================
	//a、b 皆为整数，无小数点
	//==============================================

	if(i == -1 && j == -1)
	{	
		int k = 0;
		i++;j++;
		while(a[i] != '\0')i++;//a数组长度
		while(b[j] != '\0')j++;//b数组长度
		//此时 b[j] == '\0'		
		if(i > j)//a大于b
		{
			k = i;
			sign = 1;
			integerSub(c, a, b, k, i, j, 0);
		}
		else if (i == j && a[0] > b[0])
		{
			k = i;
			sign = 1;
			integerSub(c, a, b, k, i, j, 0);
		}
		else//a小于b
		{
			k = j;
			sign = -1;
			integerSub(c, b, a, k, j, i, 0);
		}
	}
	//==================================================
	//a、b 有一个是小数
	//==================================================
	else if(i == -1 && j > 0)//a是整数，b是小数
	{
		i++;
		while(a[i] != '\0')i++;//a字符数组长度
		if(i > j)//a大于b
		{
			sign = 1;
			integerSub(c, a, b, i, i, j, 0);
			//cout<<c<<endl;//正确
			//处理小数，【问题】当b小数全是无效0本算法会出错
			char *tmp = new char[512];//大小可调
			int blen = 0;
			while(b[blen] != '\0')blen++;
			int bx = blen - 1 - j;  //b数组小数部分长度
		
			for(int k = j +1, d = 0 ; k < blen ; )
			{
				tmp[d++] = b[k++];//复制b小数部分	
				//cout<<bx<<"   "<<d<<endl;
			}
			
			tmp[bx] = '\0';//标记tmp结束位						
			char *tmp2 = new char[bx +1];//分配空间长度是0---bx
			char *tmp3 = new char[bx +1];//分配空间长度是0-至-bx
			for(int d = 0 ; d < bx ; d++)
				tmp2[d] = '9';
			tmp2[bx] = '\0';
			
			integerSub(tmp3, tmp2, tmp, bx, bx, bx, 0);// tmp3 = tmp2 - tmp
				//cout<<"此处"<<tmp3<<endl;//正确
			for(int d = 0 ; d < bx - 1 ; d++)//tmp2设置成临时数据"00000000001"
			{
				tmp2[d] = '0';
			}
			tmp2[bx - 1] = '1';
			tmp2[bx] = '\0';
			//cout<<tmp2;//正确
			integerAdd(tmp, tmp3, tmp2, bx, bx, bx, 0);//tmp = tmp3 + "00000000001"
			//cout<<tmp;//正确
			
			tmp[bx + 1] = '\0';	
			for( int d = bx ; d > 0; d--)//腾出位，插入小数点
			{
				tmp[d] = tmp[d - 1];
			}
			tmp[0] = '.';
			//c整数部分-1
			c[i-1] -= 1;
			if(c[i-1] < '0')//退位处理
			{
				int d = i-1;
				c[d--] += 10;//个位借位成功
				while(1)
				{
					c[d] -= 1;
					if(c[d] < '0')
					{						
						c[d--] += 10;//该位借位成功
					}
					else
						break;
				}
			}
			
			
			//==========================
			//连接整数和尾数
			//==========================
			strcat(c, tmp);

			delete[]tmp;//?分配的空间不能收回？？？
			delete[]tmp2;
			delete[]tmp3;
				
		}
		else if (i == j && my_strcmp(a,b,0,i-1,0,j-1) > 0)
		{
			sign = 1;
			integerSub(c, a, b, i, i, j, 0);
			//cout<<c<<endl;//正确
			//处理小数，【问题】当b小数全是无效0本算法会出错
			char *tmp = new char[512];//大小可调
			int blen = 0;
			while(b[blen] != '\0')blen++;
			int bx = blen - 1 - j;  //b数组小数部分长度
		
			for(int k = j +1, d = 0 ; k < blen ; )
			{
				tmp[d++] = b[k++];//复制b小数部分	
				//cout<<bx<<"   "<<d<<endl;
			}
			
			tmp[bx] = '\0';//标记tmp结束位						
			char *tmp2 = new char[bx +1];//分配空间长度是0---bx
			char *tmp3 = new char[bx +1];//分配空间长度是0-至-bx
			for(int d = 0 ; d < bx ; d++)
				tmp2[d] = '9';
			tmp2[bx] = '\0';
			
			integerSub(tmp3, tmp2, tmp, bx, bx, bx, 0);// tmp3 = tmp2 - tmp
				//cout<<"此处"<<tmp3<<endl;//正确
			for(int d = 0 ; d < bx - 1 ; d++)//tmp2设置成临时数据"00000000001"
			{
				tmp2[d] = '0';
			}
			tmp2[bx - 1] = '1';
			tmp2[bx] = '\0';
			//cout<<tmp2;//正确
			integerAdd(tmp, tmp3, tmp2, bx, bx, bx, 0);//tmp = tmp3 + "00000000001"
			//cout<<tmp;//正确
			
			tmp[bx + 1] = '\0';	
			for( int d = bx ; d > 0; d--)//腾出位，插入小数点
			{
				tmp[d] = tmp[d - 1];
			}
			tmp[0] = '.';
			//c整数部分-1
			c[i-1] -= 1;
			if(c[i-1] < '0')//退位处理
			{
				int d = i-1;
				c[d--] += 10;//个位借位成功
				while(1)
				{
					c[d] -= 1;
					if(c[d] < '0')
					{						
						c[d--] += 10;//该位借位成功
					}
					else
						break;
				}
			}
			
			
			//==========================
			//连接整数和尾数
			//==========================
			strcat(c, tmp);
			//delete[]tmp;
			//delete[]tmp2;
			//delete[]tmp3;
		}
		else//a小于b
		{
			sign = -1;//a比b小
			integerSub(c, b, a, j, j, i, 0);
			int d = 0;
			for(d = j; b[d] != '\0'; d++)//引入小数，包括小数点
				c[d]=b[d];
			c[d] = '\0';
		}
		
	}
	else if(i > 0 && j < 0)
		//==============================
		//a是小数，b是整数【有两种情形】
		//==============================
	{
		j++;
		while(b[j] != '\0')j++;//b字符数组长度
		//=============================================================================================
		//a是小数，a的整数部分大于等于b整数部分，但a > b,图示情形（3）
		//=============================================================================================
		if(i > j )
		{		
			sign = 1;
			integerSub(c,a,b,i,i,j,0);
			int d = 0;
			for(d = i; a[d] != '\0'; d++)//引入小数，包括小数点
				c[d]=a[d];
			c[d] = '\0';
		}
		else if(i == j && my_strcmp(a,b,0,i-1,0,j-1) >= 0)
		{
			sign = 1;
			integerSub(c,a,b,i,i,j,0);
			int d = 0;
			for(d = i; a[d] != '\0'; d++)//引入小数，包括小数点
				c[d]=a[d];
			c[d] = '\0';
		}
		else
		{ 
			//=============================================================================================
			//a是小数，a的整数部分小于b整数部分，但a < b,图示情形（4）
			//=============================================================================================
		 	sign = -1;
			integerSub(c, b, a, j, j, i, 0);
			//cout<<c<<endl;//正确
			//处理小数，【问题】当b小数全是无效0本算法会出错
			char *tmp = new char[512];//大小可调
			int alen = 0;
			while(a[alen] != '\0')alen++;
			int ax = alen - 1 - i;  //a数组小数部分长度
		
			for(int k = i +1, d = 0 ; k < alen ; )
			{
				tmp[d++] = a[k++];//复制b小数部分,不包括小数点	
				//cout<<bx<<"   "<<d<<endl;
			}			
			tmp[ax] = '\0';//标记tmp结束位		

			//cout<<tmp<<endl;//正确
			char *tmp2 = new char[ax +1];//分配空间长度是0---ax
			char *tmp3 = new char[ax +1];//分配空间长度是0-至-ax
			for(int d = 0 ; d < ax ; d++)
				tmp2[d] = '9';
			tmp2[ax] = '\0';
			//cout<<tmp2<<endl;//正确
			integerSub(tmp3, tmp2, tmp, ax, ax, ax, 0);// tmp3 = tmp2 - tmp
			//cout<<"此处"<<tmp3<<endl;//正确
			for(int d = 0 ; d < ax - 1 ; d++)//tmp2设置成临时数据"00000000001"
			{
				tmp2[d] = '0';
			}
			tmp2[ax - 1] = '1';
			tmp2[ax] = '\0';
			//cout<<tmp2;//正确
			integerAdd(tmp, tmp3, tmp2, ax, ax, ax, 0);//tmp = tmp3 + "00000000001"
			//cout<<tmp;//正确
			
			tmp[ax + 1] = '\0';	//腾出位，插入小数点
			for( int d = ax ; d > 0; d--)
			{
				tmp[d] = tmp[d - 1];
			}
			tmp[0] = '.';
			//cout<<tmp;//正确
			//c整数部分-1
			c[j-1] -= 1;
			if(c[j-1] < '0')//退位处理
			{
				int d = j-1;
				c[d--] += 10;//个位借位成功
				while(1)
				{
					c[d] -= 1;
					if(c[d] < '0')
					{						
						c[d--] += 10;//该位借位成功
					}
					else
						break;
				}
			}
			
			//==========================
			//连接整数和尾数
			//==========================
			strcat(c, tmp);
			//delete[]tmp;
			//delete[]tmp2;
			//delete[]tmp3;
		}
			
	}
	else
	{
		//===================================
		//a、b 皆是有小数
		//===================================
		int alength = 0 , blength = 0;//a、b字符数组总长度
		while(a[alength] != '\0')alength++;
		while(b[blength] != '\0')blength++;
		int ax = alength - 1 - i;//a小数点后面的字符长度
		int bx = blength - 1 - j;//b小数点后面的字符长度		
		//cout<<my_strcmp(a,b,0,i,0,j);//比较a、b整数部分大小
		if( i==j && (strcmp(a,b) == 0)) //a、b相等
		{
			c[0] = '0';
			c[1] = '\0';
			return c;
		}
		//=============================================================================================
		//第一种情形，a的整数部分大于等于b整数部分，但a > b,同时a的小数部分短于b的小数部分，图示情形（5）
		//=============================================================================================
		if((i > j ||( i==j && (strcmp(a,b) > 0))) && ax <= bx)
		{
			sign = 1;
			int clength = i + 1 + bx;//i+1是a的整数部分包含小数点的长度
			char *tmp = new char[512];//大小可调
			char *tmp2 = new char[512];//大小可调，拷贝a，后面补0
			char *tmp3 = new char[512];//大小可调，拷贝b
			////跳过小数点【旧】
			//int k = 0;
			//for(int d = 0; a[d] != '\0'; d++)
			//{
			//	if( a[d] == '.')continue;
			//	tmp2[k] = a[d];
			//	k++;
			//}
			//int count = bx - ax;//a末尾补0数
			//while(count > 0)
			//{
			//	tmp2[k++] = '0';
			//	count--;
			//}
			//int tmp2len = k;//记录tmp2长度
			//tmp2[k] = '\0';
			//k = 0;
			//for(int d = 0; b[d] != '\0'; d++)
			//{
			//	if( b[d] == '.')continue;
			//	tmp3[k] = b[d];
			//	k++;
			//}
			//tmp3[k] = '\0';

			//跳过小数点【新】
			removeDot(tmp2,a);			
			removeDot(tmp3,b);
			int tmp2len = strlen(tmp2);		
			int count = bx - ax;//a末尾补0数
			while(count > 0)
			{
				tmp2[tmp2len++] = '0';
				count--;
			}
			tmp2[tmp2len] = '\0';
			integerSub(tmp,tmp2,tmp3,tmp2len,tmp2len,strlen(tmp3),0);
			
			//插入小数点
			int d = tmp2len;
			for(; d > i; d--)
			{
				tmp[d] = tmp[d-1];
			}
			tmp[d--] = '.';
			tmp[tmp2len + 1] = '\0';
			strcpy(c,tmp);
			delete[]tmp;
			delete[]tmp2;
			delete[]tmp3;
		}
		//=============================================================================================
		//第二种情形，b的整数部分大于等于a整数部分，a < b，同时a的小数部分短于b的小数部分，图示情形（6）
		//=============================================================================================
		if((i < j ||( i==j && (strcmp(a,b) < 0))) && ax<=bx)
		{
			sign = -1;
			int clength = blength;
			char *tmp = new char[512];//大小可调
			char *tmp2 = new char[512];//大小可调，拷贝a
			char *tmp3 = new char[512];//大小可调，拷贝b，后面补0
			removeDot(tmp2,b);			
			removeDot(tmp3,a);
			int tmp3len = strlen(tmp3);	//去小数点后的长度
			int count = bx - ax;
			while(count > 0)
			{
				tmp3[tmp3len++] = '0';
				count--;
			}
			tmp3[tmp3len] = '\0';
			integerSub(tmp,tmp2,tmp3,strlen(tmp2),strlen(tmp2),tmp3len,0);
			//插入小数点
			int d = strlen(tmp2);
			for(; d > j; d--)
			{
				tmp[d] = tmp[d-1];
			}
			tmp[d--] = '.';
			tmp[strlen(tmp2) + 1] = '\0';
			strcpy(c,tmp);
			
			delete[]tmp;
			delete[]tmp2;
			delete[]tmp3;
		}
		//=============================================================================================
		//第三种情形，a的整数部分大于等于b整数部分，a > b，同时a的小数部分长于b的小数部分，图示情形（7）
		//=============================================================================================
		if((i > j ||( i==j && (strcmp(a,b) > 0))) && ax>=bx)
		{
			sign = 1;
			int clength = alength;
			char *tmp = new char[512];//大小可调
			char *tmp2 = new char[512];//大小可调，拷贝a
			char *tmp3 = new char[512];//大小可调，拷贝b，后面补0
			removeDot(tmp2,a);			
			removeDot(tmp3,b);
			int tmp3len = strlen(tmp3);	//去小数点后的长度
			int count = ax - bx;
			while(count > 0)
			{
				tmp3[tmp3len++] = '0';
				count--;
			}
			tmp3[tmp3len] = '\0';
			integerSub(tmp,tmp2,tmp3,strlen(tmp2),strlen(tmp2),tmp3len,0);
			//插入小数点
			int d = strlen(tmp2);
			for(; d > i; d--)
			{
				tmp[d] = tmp[d-1];
			}
			tmp[d--] = '.';
			tmp[strlen(tmp2) + 1] = '\0';
			strcpy(c,tmp);
			
			delete[]tmp;
			delete[]tmp2;
			delete[]tmp3;
		}
		//=============================================================================================
		//第四种情形，b的整数部分大于等于a整数部分，a < b，同时a的小数部分长于b的小数部分，图示情形（8）
		//=============================================================================================
		if((i < j ||( i==j && (strcmp(a,b) < 0))) && ax>=bx)
		{
			sign = -1;
			int clength = j + 1 + ax;//i+1是a的整数部分包含小数点的长度
			char *tmp = new char[512];//大小可调
			char *tmp2 = new char[512];//大小可调，拷贝b，后面补0
			char *tmp3 = new char[512];//大小可调，拷贝a
			removeDot(tmp2,b);			
			removeDot(tmp3,a);
			int tmp2len = strlen(tmp2);		
			int count = ax - bx;//b末尾补0数
			while(count > 0)
			{
				tmp2[tmp2len++] = '0';
				count--;
			}
			tmp2[tmp2len] = '\0';
			
			integerSub(tmp,tmp2,tmp3,tmp2len,tmp2len,strlen(tmp3),0);
			cout<<tmp<<endl;
			//插入小数点
			int d = tmp2len;
			for(; d > i; d--)
			{
				tmp[d] = tmp[d-1];
			}
			tmp[d--] = '.';
			tmp[tmp2len + 1] = '\0';
			strcpy(c,tmp);
			delete[]tmp;
			delete[]tmp2;
			delete[]tmp3;
		}
	}


	jumpZero(c);
	
	return c;
}

//
//void *__CRTDECL operator new(size_t) /*_THROW1(std::bad_alloc)*/;
//
//void * operator new[]( size_t cb )
//{
//    void *res = operator new(cb);
//
//    RTCCALLBACK(_RTC_Allocate_hook, (res, cb, 0));
//
//    return res;
//}
