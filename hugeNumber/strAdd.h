#include<iostream>
using namespace std;

extern void jumpZero(char * nptr);
extern int findDot(const char *nptr);//返回小数点位



//数值型字符result累加dst，结果保存在result。
char *integerAdd(char *result,const char * dst,int d1,int d2)//result长度为 d1,dst长度为 d2，【d1>=d2】
{
	d1--,d2--;
	int flag = 0;
	while(d2 >= 0)
	{
		result[d1] += (dst[d2] - '0');
		if(flag)result[d1] += 1;
		if(result[d1] > '9')
		{
			flag = 1;
			result[d1] -= 10;
		}
		else
			flag = 0;
		d1--,d2--;
	}
	while(flag)
	{
		result[d1] += 1;
		if(result[d1] > '9')
		{
			flag = 1;
			result[d1] -= 10;
		}
		else
			flag = 0;
		d1--;//result足够长，不可能在相乘后溢出
	}
	
	return result;
}


//整数字符串数组相加
void integerAdd(char *c,const char *a,const char *b,int k,int i,int j,int flag)//a，b都没有小数，k为c数组长度，i为a数组长度……flag有无进位
{
	int clength = k;//c数组长度
	c[k] = '\0';
	k--;i--;j--;
	while(j >= 0 && i >= 0)
	{
		c[k] = a[i] + (b[j] - '0');
		if(flag)c[k] += 1;
		if(c[k] > '9')
		{
			flag = 1;
			c[k] -= 10;
		}
		else
			flag = 0;
		k--;i--;j--;
	}
	while(j >= 0)
	{
		c[k] = b[j];
		if(flag)c[k] += 1;
		if(c[k] > '9')
		{
			flag = 1;
			c[k] -= 10;
		}
		else
			flag = 0;
		k--;j--;
	}
	while(i >= 0)
	{
		c[k] = a[i];
		if(flag)c[k] += 1;
		if(c[k] > '9')
		{
			flag = 1;
			c[k] -= 10;
		}
		else
			flag = 0;
		k--;i--;
	}
	if(flag)
	{
		//cout<<"k = "<<k<<endl;
		c[k] = '1';
		
	}
	else
	{//没有进位
		c[k] = '0';
		
	}
		
			
	
}

//数值型字符串相加
char * strAdd(char *c , const char *a, const char *b)  //c = a + b
{
	int i = findDot(a);//尾数a小数点位
	int j = findDot(b);//尾数b小数点位
	int k ;
	int flag = 0;
	//==============================================
	//a、b 皆为整数，无小数点
	//==============================================
	if(i == -1 && j == -1)
	{	
		i++;j++;
		while(a[i] != '\0')i++;
		while(b[j] != '\0')j++;
		//此时 b[j] == '\0'
		i--;j--;
		k =( (j>=i)? j : i) + 1;//考虑进位
		int clength = k;//c数组长度
		while(j >= 0 && i >= 0)
		{
			
			c[k] = a[i] + (b[j] - '0');
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;i--;j--;
		}
		while(j >= 0)
		{
			c[k] = b[j];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;j--;
		}
		while(i >= 0)
		{
			c[k] = a[i];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;i--;
		}
		if(flag)
		{
			//cout<<"k = "<<k<<endl;
			c[k] = '1';
			c[clength + 1] = '\0';
		}
		else
		{//排除首位空格并加结束符
			int i = 0;
			for(; i < clength; i++ )
			{
				c[i] = c[i+1];//所有数组元素前移一位
			}
			c[i] = '\0';
		}
		
			//return c;
	}
	//==================================================
	//a、b 有一个是小数
	//==================================================
	else if(i == -1 && j > 0)
	{
		
		i++;
		while(a[i] != '\0')i++;//a字符数组长度
		int bx = j + 1;//b数组小数点后一位的位置
		int cx ;
		j--;i--;//整数部分最后一位
		k =( (j>=i)? j : i) + 1;//考虑进位，k多一位
		//c[k + 1] = '.';//记录小数点
		int clen1 = k;//c数组整数部分长度【暂定】
		
		while(j >=0 && i >= 0)
		{
			c[k] = a[i] + (b[j] - '0');
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;

			}
			k--;j--;i--;
		}
		while(j >= 0)
		{
			c[k] = b[j];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;j--;
			
		}

		while(i >= 0)
		{
			c[k] = a[i];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;i--;
		}
		if(flag)
		{
			//cout<<"k1 = "<<k<<endl;
			c[k] = '1';
			c[clen1+1] = '.';
			cx = clen1 + 2;
		}
		else
		{//排除首位空格并加结束符
			int i = 0;
			for(; i < clen1; i++ )
			{
				c[i] = c[i+1];//所有数组元素前移一位
			}
			c[i] = '.';
			cx = i + 1;
		}
				
		//===================================
		//处理小数
		//===================================
		while(b[bx] != '\0')
			c[cx++] = b[bx++];
		c[cx] = '\0';//cx为该字符数组【总】长度
	
		//return c;
		
	}
//另一种情况
	else if(j == -1 && i >0)
	{
		j++;
		while(b[j] != '\0')j++;//b是整数，标记b字符数组长度
		int ax = i + 1;//标识b数组小数点后一位的位置
		int cx ;
		j--;i--;//整数部分最后一位
		k =( (j>=i)? j : i) + 1;//考虑进位，k多一位
		//c[k + 1] = '.';//记录小数点
		int clen1 = k;//c数组整数部分长度【暂定】
		
		while(j >=0 && i >= 0)
		{
			c[k] = a[i] + (b[j] - '0');
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;

			}
			k--;j--;i--;
		}
		while(j >= 0)
		{
			c[k] = b[j];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;j--;
			
		}

		while(i >= 0)
		{
			c[k] = a[i];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;i--; 
		}

		if(flag)
		{
			//cout<<"k2 = "<<k<<endl;
			c[k] = '1';
			c[clen1+1] = '.';
			cx = clen1 + 2;
		}
		else
		{//排除首位空格并加结束符
			int i = 0;
			for(; i < clen1; i++ )
			{
				c[i] = c[i+1];//所有数组元素前移一位
			}
			c[i] = '.';
			cx = i + 1;
		}
				
		//===================================
		//处理小数
		//===================================
		while(a[ax] != '\0')
			c[cx++] = a[ax++];
		c[cx] = '\0';//cx为该字符数组【总】长度
	
		//return c;

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
		int bx = blength -1 - j;//b小数点后面的字符长度
		//cout<<"ax= "<<ax<<endl;
		//cout<<"bx= "<<bx<<endl;
		int clength = (ax >= bx ? ax : bx) + (i >= j ? i : j) + 2;//c字符数组总长度，包括小数点位和一个防进位
		int k = (i >= j ? i : j) + 1;//c字符数组小数点位，预留防进位
		
		int cdot = k;//c字符数组小数点位
		c[clength] = '\0';//标记数组结束
		int w = 1 ;
		while(ax < bx)//a小数长度小于b
		{
			c[clength - w] = b[blength - w];
			w++;bx--;
		}		
		while(ax > bx)
		{
			c[clength - w] = a[alength - w];
			w++;ax--;			
		}	
		//cout<<ax<<bx;//二者已相等
		while(bx > 0)//a、b字符数组小数长度一样时
		{
			//c[clength - w] = a[ax+i] +(b[bx+j] - '0');//从最后一个有效位开始向前累加
			c[clength - w] = b[bx+j] +(a[ax+i] - '0');
			if(flag)c[clength - w] += 1;
			if(c[clength - w] > '9')//转换成进位
			{
				flag = 1;
				c[clength - w] -= 10;
			}
			else
			{
				flag = 0;
			}
			ax--;bx--;w++;
		}
	

	
		//cout<<clength - w<<endl;//测试是不是有最长的整数部分字符数组的小数点位 + 1
		//cout<<i<<"    "<<j<<endl;
		
		//整数部分累加
		
		integerAdd(c,a,b,k,i,j,flag);
		//累加到小数点啦
		c[cdot] = '.';
		//c[k] = '.';
		//if(c[0] == '0' && c[1] != '.')//排除首位无用0
		//{
		//	int i = 0;
		//	for(;c[i] != '\0'; i++)
		//		c[i] = c[i++];
		//	c[i] = '\0';//标记c字符数组结束
		//}
	}
	//==========================
	//去除最前面无效0
	//==========================
	jumpZero(c);
	return c;
}

