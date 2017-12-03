#include <iostream>
#include <string>
#include <float.h>

#include "strSub.h"
#include "strMul.h"
#include "strAdd.h"

#define isdigit(c)    ('0' <= (c) && (c) <= '9')
using namespace std;
const int MAXSIZE = 512;

class hugeNumber{			//定义大数，10进制
private:
	/*char deciNum[MAXSIZE];	*/		//尾数
	char *deciNum;
	long  exponent;			//指数
	short sign;				//符号位，取-1或1
	int set_dot;			//小数点位置，-1表示没有小数点
public:
	hugeNumber()
	{
		this->deciNum = new char [MAXSIZE];		//开辟尾数空间
		if(!this->deciNum )
		{
			cout<<"allocation failure!"<<endl;
			exit(EXIT_FAILURE);
		}
		this->exponent = 0;
		this->sign = 1;
		this->set_dot = -1;
	}
	hugeNumber(char deciNum[], long  exponent, int set_dot = -1);
	hugeNumber(const char *nptr);
	hugeNumber(const hugeNumber &b);      //拷贝构造函数
//	~hugeNumber(){delete []deciNum;}
	int getsign(){return sign;}
	int getdot(){return set_dot;}
	char *getdeciNum(){return deciNum;}
	long getexponent(){return exponent;}
	hugeNumber operator +(hugeNumber &b);
	hugeNumber operator +(char str[]);  
	hugeNumber operator -(hugeNumber &b);
	hugeNumber operator -(char str[]); 
	hugeNumber operator *(hugeNumber &b);
	hugeNumber operator *(char str[]);  
	hugeNumber operator /(hugeNumber &b);
	hugeNumber operator /(char str[]);  
	friend ostream& operator<<(ostream &out,hugeNumber &b);
	friend istream& operator>>(istream &in,hugeNumber &b);
	friend void norm(hugeNumber &hu);				//按科学计数规格化，如12.34e5，规格化后1.234e6
	friend void norm(hugeNumber &hu,  long exp );	//按exp介规格化
	friend void my_round(hugeNumber &hu ,int prec);	//按精度四舍五入
	

};

extern char * strAdd(char *c , const char *a, const char *b);//数值型字符串相加
extern void integerAdd(char *c,const char *a,const char *b,int k,int i,int j,int flag);//整数字符串数组相加
int isNumber(const char *nptr);//判断字符串是否符号数据特征
void expandArray(char a[], int n);//n表示数组头插入的元素个数
void jumpZero(char * nptr);//跳过尾数前面的无用的0，除了小数点前的
int findDot(const char *nptr);//返回小数点位

void expandArray(char a[], int n)//n表示数组头插入的元素个数
{
	char *tmp = new char[MAXSIZE];
	if(!tmp)
	{
		cout<<"allocation failure!"<<endl;
		exit(EXIT_FAILURE);
	}
	int j = 0;
	for(; a[j] != '\0'; j++)
		tmp[j+n] = a[j];
	tmp[j+1] = '\0';
//	tmp[0] = '1';
	for(j = 0; tmp[j] != '\0'; j++)
		a[j] = tmp[j];
	delete tmp;
}

//跳过尾数前面的无用的0，除小数点前的0，【ps】数值小数点后尾部无效0暂时无法剔除
void jumpZero(char * nptr)
{
	char *tmp = new char[MAXSIZE];
	if(!tmp)
	{
		cout<<"allocation failure!"<<endl;
		exit(EXIT_FAILURE);
	}
	char *s = nptr;
	while (*s == '0') 
		++s;
	int got_digit = 0;	//得到1-9数字
	int i = 0;
	for(; *s != '\0' &&  *s - '0' < 10 && *s - '0' >= 0;)//从第一个不是0的数开始记录
	{
		tmp[i++] = *s++; 
		got_digit = 1;
	}
	if (*s == '.')
	{
		if (!got_digit)  //  if (!i)  尾数的整数部分全是0或没有
		{
			tmp[0] = '0';
			i = 1;
		}
		tmp[i] = '.'; 
		s++;
		i++;
		
		while ( *s != '\0' &&  *s - '0' < 10 && *s - '0' >= 0)//提取尾数的小数
		{
			tmp[i++] = *s++; 
		}
	}
	tmp[i] = '\0';			//标记尾数结束
	i = 0;					//回头
	while(tmp[i] != '\0')	//复制字符数组
		nptr[i++] = tmp[i];
	nptr[i] = '\0';			//标记结束位
	delete []tmp;
}

//返回小数点真实数组下标的位置
int findDot(const char *nptr)
{
	const char *s = nptr;
	int count = -1;
	while(*s != '\0')
	{
		count++;
		if(*s== '.')
			return count;
		s++;
	}
	return -1;//标识未找到小数点
}

////返回一个对应的小写字母
char TOLOWER(const char *s)			//传入字符指针，地址
{
	char tmp;
	if(*s >= 'A' && *s <= 'Z')
		tmp = *s + 'a' - 'A';
	else if(*s >= 'a' && *s <= 'z')
		;
	else
		errno = EINVAL;   //#define  EINVAL  22  无效值异常
	return tmp;
}

//判断是否是实数，此处仅仅处理10进制
int isNumber(const char *nptr)
{
	const char *s = nptr;

	if (nptr == NULL) //判断字符串是否为空
	{
		
		 goto noNumber; 
	}
	s = nptr;
	 while (*s == 32) //跳过前面的空格，正确
		++s;
	if (*s == '-' || *s == '+')  //碰到正负号，取下一个字符元素
		++s;

	int flag = 1;		//遇到非数值字符标记
	int got_dot = 0;  //获得圆点个数
	int got_digit = 0;//0-9数字

	for(; (*s != '\0') ;++s)
	{
		//if( (*s - '0'< 10) && (*s - '0'>= 0))	//是否是字符型数字
		if(isdigit(*s))
			got_digit = 1 ;
		else if (!got_dot && *s == '.')			//没有遍历到小数点，又刚好碰到小数点时，设置函数状态
 			got_dot = 1;
		else
			break;				//这个字符不是数值型的字符,可能碰见e
		
	}
	
	if (!got_digit )					//没有收集到数字
		 goto noNumber;						                
	if( *s != '\0' && *s != 'e' && *s != 'E')//判断异常字符
		goto noNumber;	
	if( *s == 'e'||*s == 'E')//没有遍历到E，又刚好碰到E时，设置函数状态
	{
		s++;
		if (*s == '-' || *s == '+')  //碰到正负号，取下一个字符元素
		++s;
		for(;*s != '\0';++s)           //指数是否合法
		{
			//if( (*s - '0'< 10) && (*s - '0'>= 0))	//是否是字符型数字
			if(isdigit(*s))
				;
			else
				goto noNumber;	
		}

	}
	return 1;
noNumber:
	 errno = EINVAL;   //#define  EINVAL  22
	 return 0;
}

//按科学计数规格化，如12.34e5，规格化后1.234e6
void norm(hugeNumber &hu) //大染缸
{
	int i = findDot(hu.deciNum);	//小数点位置
	int k = 0;						//标记首个非0数字位置，

	char *s = hu.deciNum;
	for(; *s - '0'== 0 || *s == '.';)	// 跳过首字符0或小数点，直到扫描到第一个非0
	{
			++s;++k;
	}
	//k++;//首个即非0也不是小数点，***k不能再加***
	if(i == -1)//尾数为整数
	{
		i++;
		while(hu.deciNum[i])i++;//记录尾数长度
		hu.deciNum[i] = '.';
		hu.deciNum[i+1] = '\0';
		while(i > 1)
		{
			hu.deciNum[i] = hu.deciNum[i-1];
			hu.deciNum[i-1] = '.';			//小数点前一位向右移一位
			i--;
			hu.exponent++;
		}

	}
	else if (i-1 > k)
	{
		while(i-1 > k  && i > 1)//小数点在首个非0数字后
		{
			hu.deciNum[i] = hu.deciNum[i-1];
			hu.deciNum[i-1] = '.';			//小数点前一位向右移一位
			i--;
			hu.exponent++;
		}
	}
	else if(i < k)
	{
		
		while(i < k  )//小数点在首个非0数字前
		{
			hu.deciNum[i] = hu.deciNum[i+1];//小数点与后一个数据交换位置
			hu.deciNum[++i] = '.';
			hu.exponent--;
		}
		
	}
	else
		;
	jumpZero(hu.deciNum);
	//==========================================
	//剔除末尾是小数点
	//==========================================
	int j = 0;
	while(hu.deciNum[j]!= '\0')  //有效字符长度
		j++;
	if(hu.deciNum[j-1] == '.' ) //最后一位是小数点
	{
		hu.deciNum[--j] = '\0';
		hu.set_dot = -1;      //没有小数点啦！
	}
	else
		hu.set_dot = findDot(hu.deciNum);//找到小数点位置
}

//按exp介规格化
void  norm(hugeNumber &hu, long exp ) //按exp介规格化
{
	int i = hu.getdot(); //小数点位置
	if(exp == hu.exponent)return;
	else if(exp > hu.exponent)//小数点左移
	{
		while(exp > hu.exponent)//小数点左移
		{
			hu.exponent++;
			if(i == -1)//没有小数点
			{
				int j = 0;
				while(hu.deciNum[j]!= '\0')  //有效字符长度
					j++;
				hu.deciNum[j] = '.';
				i=j;//记录小数点位置
				hu.deciNum[++j] = '\0';
			}
			if(i == 1) //例如1.234时
			{
				//char *tmp = new char [512];
				//int j = 0;
				//for(; hu.deciNum[j] != '\0'; j++)
				//	tmp[j+1] = hu.deciNum[j];
				//tmp[j+1] = '\0';
				//tmp[0] = '0';
				//for(j = 0; tmp[j] != '\0'; j++)
				//	hu.deciNum[j] = tmp[j];
				//delete tmp;
				expandArray(hu.deciNum,1);//数组头插入1个元素0
				hu.deciNum[0] = '0';
				i++;//复制的小数点向右移动一位
			}
			hu.deciNum[i] = hu.deciNum[i-1];
			hu.deciNum[--i] = '.';			//小数点前一位向右移一位
			
		}
	}
	else          //当exp < hu.exponent 时，小数点右移
	{
		if(i == -1)//没有小数点
		{
			int j = 0;
			while(hu.deciNum[j]!= '\0')  //有效字符长度
				j++;
			while(exp < hu.exponent)  //尾数*10,即尾数添加0
			{
				hu.deciNum[j++] = '0';
				hu.exponent--;
			}
			hu.deciNum[j] = '\0';
		}
		else
		{

			while(exp < hu.exponent)  //有小数点，尾数*10,小数点右移
			{
				
				hu.exponent--;
			
				if(hu.deciNum[i+1] == '\0') //一次右移
				{
					hu.deciNum[i+1] = '0';
					hu.deciNum[i+2] = '\0';
					
				}
				hu.deciNum[i] = hu.deciNum[i+1];
				hu.deciNum[++i] = '.';
			}
			jumpZero(hu.deciNum);
		}
		
	}
	//==========================================
	//剔除末尾是小数点
	//==========================================
	int j = 0;
	while(hu.deciNum[j]!= '\0')  //有效字符长度
		j++;
	if(hu.deciNum[j-1] == '.' ) //最后一位是小数点
	{
		hu.deciNum[--j] = '\0';
		hu.set_dot = -1;      //没有小数点啦！
	}
	else
		hu.set_dot =  findDot(hu.deciNum);//找到小数点位置
}

//对大数按规定精度，四舍五入
void my_round(hugeNumber &hu ,int prec)  //precision，规定的精度位（不能再是大数）
{
	int i = -1;							//标记小数位，默认-1表示没有小数点
	int k = 0;		//标记首个非0数字位置，
	norm(hu ,0);	//按精度规整大数，数值大小不变
	//cout<<"niming   "<<hu<<endl;//正确
	norm(hu , -prec);
	//cout<<"niming   "<<hu<<endl;//正确

	char *s = hu.deciNum;
	for(; *s - '0'== 0 || *s == '.';)	// 跳过首字符0，扫描到第一个非0
	{
		++s;++k;	
	}
	i = findDot(hu.deciNum);			//找到小数点位置
	if(i == -1)			//没有小数点
	{
		norm(hu);		//大数规格化
		return;			//不需要处理，精度达不到
	}
	if(i < k )			// 首个出现的非0字符在小数点位后
	{
		errno = ERANGE;			//数据下溢
		hu.deciNum[0] = '0';
		hu.deciNum[1] = '\0';	//设置结束标识
		hu.exponent = 0;
		hu.set_dot = -1;
		return;
	}
	else         // 首个出现的非0字符在小数点位前
	{
		
		if(hu.deciNum[i+1] - '0' < 5)  
		{
			hu.deciNum[i] = '\0';//小数点变结束位
			hu.deciNum[i+1] = '\0';
		}
		else   //考虑进位
		{
			int j = i-1;			//小数点的前一位（最后一个保留位）
			hu.deciNum[i] = '\0';	//小数点变结束位
			hu.deciNum[i+1] = '\0';
			int flag = 1;			//进位标识
			//if(hu.deciNum[j] > '9')
			//	flag = 1;
			//	hu.deciNum[j] %= 10;
			//	j--;
			//	while(flag)
			//	{
			//		if(hu.deciNum[j] > '9')
			//		flag = 1;
			//		hu.deciNum[j] %= 10;
			//		j--;
			//	}
			
				do{
					hu.deciNum[j] += flag;
					if(hu.deciNum[j] <= '9')
					{
						flag = 0;
					}
					else
					{
						hu.deciNum[j] -= 10;
						flag = 1;
						j--;
					}
				}while(flag && j >= 0);

				if(flag && j < 0)  //数据溢出最高位
				{
					//char *tmp = new char [512];
					//int j = 0;
					//for(; hu.deciNum[j] != '\0'; j++)
					//	tmp[j+1] = hu.deciNum[j];
					//tmp[j+1] = '\0';
					//tmp[0] = '1';
					//for(j = 0; tmp[j] != '\0'; j++)
					//	hu.deciNum[j] = tmp[j];
					//delete tmp;
					expandArray(hu.deciNum, 1);//数组头插入1个元素
					hu.deciNum[0] = '1';
				}
			
		}
		//norm(hu);//大数规格化
	}
	
}

hugeNumber::hugeNumber(const hugeNumber &b)      //拷贝构造函数
{
		
	this->deciNum = new char [strlen(b.deciNum)+1];		//开辟尾数空间
	if(!this->deciNum )
	{
		cout<<"allocation failure!"<<endl;
		exit(EXIT_FAILURE);
	}
	strcpy(this->deciNum, b.deciNum);
	//memcpy(this->deciNum, b.deciNum, strlen(b.deciNum)*sizeof(char));//错
	this->exponent = b.exponent;
	this->sign = b.sign;
	this->set_dot = b.set_dot;
	//cout<<"你调用了复制构造函数"<<endl;
}
hugeNumber::hugeNumber(char deciNum[], long  exponent,int set_dot)
{
	if(!isNumber(deciNum))
	{
		cout<<"This is not a number! " ;
		exit(EXIT_FAILURE);				//非正常退出
	}
	this->deciNum = new char [MAXSIZE];		//开辟尾数空间
	if(!this->deciNum )
	{
		cout<<"allocation failure!"<<endl;
		exit(EXIT_FAILURE);
	}

	const char *s = deciNum;
	s = deciNum;
	while (*s == 32) //跳过前面的空格，正确
		++s;
	this->sign = *s == '-' ? -1 : 1;	//保存正负号
	if (*s == '-' || *s == '+')			//碰到正负号，取下一个字符元素
		++s;
	int i = 0;
	for(; *s != '\0' && *s - '0' < 10 ; i++)//遇到第一个不是数字的字符，停止
		*++s;
	if (*s == '.')
	{
		int set_dot = i;
	}
	strcpy(this->deciNum , deciNum);
	this->exponent = exponent;

}
//==========================
//核心构造函数
//==========================
hugeNumber::hugeNumber(const char *nptr)
{
	
	if(!isNumber(nptr))
	{
		cout<<"This is not a number! " ;
		exit(EXIT_FAILURE);				//非正常退出
	}
	this->deciNum = new char [MAXSIZE];		//开辟尾数空间
	if(!this->deciNum )
	{
		cout<<"allocation failure!"<<endl;
		exit(EXIT_FAILURE);
	}
	const char *s = nptr;
		
	s = nptr;
	while (*s == 32) //跳过前面的空格，正确
		++s;
	sign = *s == '-' ? -1 : 1;   //保存正负号
	if (*s == '-' || *s == '+')  //碰到正负号，取下一个字符元素
		++s;
	while (*s == '0') //跳过前面的无用的0，除了小数点前的
		++s;
	exponent = 0;		//指数，默认指数为0
	set_dot = -1;		//获得圆点位置
	int got_digit = 0;	//得到0-9数字
	int i = 0;

	//while(*s - '0' < 10 && *s != '\0') //提取尾数的整数
	//{
	//	deciNum = deciNum*10 + (*s++ - '0');
	//}
	//deciNum *= sign ;
	for(; *s != '\0' && *s - '0' < 10 && *s - '0' >= 0; )//提取尾数的整数部分 for(; *s != '\0' && isdigit(*s) ; i++) ; for(; *s != '\0' && *s - '0' < 10 && *s != '.'; i++)
	{
		deciNum[i++] = *s++; 
		got_digit = 1;
	}

	//提取尾数的小数部分
	if (*s == '.')
	{
		if (!got_digit)  //  if (!i)  尾数整数部分全是0或没有
		{
			deciNum[0] = '0';
			set_dot = 1;	//小数点在第二位
			i = 1;
		}
		else
		{
			set_dot = i;		//小数点在i位
		}
		deciNum[set_dot] = '.'; 
		s++;
		i++;
		
		while ( *s != '\0' && *s - '0' < 10 && *s - '0' >= 0)//提取尾数的小数	for(; *s != '\0' && *s - '0' < 10 && TOLOWER（*s） != 'e'; i++)
		{
			deciNum[i++] = *s++; 
		}
	}
	deciNum[i] = '\0';			//标记尾数结束
	//提取指数
	if( *s == 'e'||*s == 'E')//刚好碰到E时，设置函数状态
	{
		s++;
		int sign2 = 1 ;		//指数可能是负数
		sign2 = (*s == '-') ? -1 : 1;   //保存正负号
		if (*s == '-' || *s == '+')  //碰到正负号，取下一个字符元素
			++s;
		while( *s != '\0' ) //提取指数的整数
		{
			exponent = exponent*10 + (*s++ - '0');
		}
		exponent *= sign2;
	}

}

ostream& operator<<(ostream &out,hugeNumber &obj)  //输出
{
	if(obj.sign < 0)out<<"-";
	out<<obj.deciNum;
	if(obj.exponent != 0)out<<"e"<<obj.exponent;
	return out;
}

istream& operator>>(istream &in,hugeNumber &obj)  //输入
{
	//char ch;
	//in>>ch;
	//if(ch = '-')obj.sign = -1;
	//else 
	//{
	//	obj.sign = 1;
	//
	//}
	//in>>obj.deciNum;
	//in>>obj.exponent;

	char *nptr = new char[MAXSIZE];
	in>>nptr;
	obj = hugeNumber(nptr);
	return in;
	delete []nptr;
}

//大数相加运算
hugeNumber  hugeNumber::operator +(hugeNumber &b)
{
	if(exponent != b.exponent)
	{
		if((exponent < b.exponent))	// 按指数小的对介
			norm(b,this->exponent);
		else
			norm(*this,b.exponent);
	}

	//cout<<"b符号=    "<<b.getsign()<<endl;
	//cout<<"尾数=    "<<b.getdeciNum()<<endl;
	//cout<<"小数点位置=    "<<b.getdot()<<endl;
	//cout<<"指数=    "<<b.getexponent()<<endl;


	hugeNumber c; //最终返回该对象

	if(this->sign > 0 && b.sign > 0)//判断正负号
	{
		c.sign = 1;
		strAdd(c.deciNum, this->deciNum, b.deciNum);
		
	}
	else if (this->sign < 0 && b.sign < 0)
	{
		c.sign = -1;
		strAdd(c.deciNum, this->deciNum, b.deciNum);
	}
	else if(this->sign > 0 && b.sign < 0)
	{
		/*if(this->sign < 0)
			c = b - *this;
		if(b.sign < 0)
			c = *this - b;*/
		int sgn = 1;
		strSub(c.deciNum, this->deciNum, b.deciNum, sgn);
		c.sign = sgn;
	}
	else
	{
		int sgn = 1;
		strSub(c.deciNum, b.deciNum, this->deciNum, sgn);
		c.sign = sgn;
	}
	
	//cout<<c.getdeciNum()<<endl;
	c.exponent = this->exponent;
	c.set_dot = findDot(c.deciNum);
	//	cout<<"niming"<<c<<endl;//正确
	return c;
}

//大数相加运算2
hugeNumber hugeNumber::operator +(char str[])
{
	if(!isNumber(str))
	{
		cout<<"This is not a number! " ;
		exit(EXIT_FAILURE);				//非正常退出
	}
	hugeNumber b (str);
	return(*this + b);
}
//大数相减运算
hugeNumber	hugeNumber:: operator -(hugeNumber &b)
{
	if(exponent != b.exponent)
	{
		if((exponent < b.exponent))	//按指数小的对介
			norm(b,this->exponent);
		else
			norm(*this,b.exponent);
	}

	hugeNumber c; //返回该对象
	if(this->sign > 0 && b.sign > 0)//判断正负号
	{
		int sgn = 1;		
		strSub(c.deciNum, this->deciNum, b.deciNum,sgn);
		c.sign =sgn;
	}
	else if (this->sign < 0 && b.sign < 0)
	{
		int sgn = 1;
		strSub(c.deciNum, this->deciNum, b.deciNum,sgn);
		c.sign = -sgn;
	}
	else if(this->sign > 0 && b.sign < 0)
	{
		strAdd(c.deciNum, this->deciNum, b.deciNum);
		c.sign = 1;
	}
	else
	{
		strAdd(c.deciNum, this->deciNum, b.deciNum);
		c.sign = -1;
	}
	
	//cout<<c.getdeciNum()<<endl;
	c.exponent = this->exponent;
	c.set_dot = findDot(c.deciNum);
	
	return c;

}
//大数相减运算2
hugeNumber	hugeNumber:: operator -(char str[])
{
	if(!isNumber(str))
	{
		cout<<"This is not a number! " ;
		exit(EXIT_FAILURE);				//非正常退出
	}
	hugeNumber b (str);
	return(*this - b);
}

//大数相乘运算
hugeNumber	hugeNumber:: operator *(hugeNumber &b)
{
	//if((exponent != b.exponent))	// 对介
	//	norm(b,this->exponent);
	hugeNumber c; //返回该对象
	int clen = strlen(this->deciNum)+strlen(b.deciNum)+1;
	int i = 0;
	for(; i<clen;i++)
	{
		c.deciNum[i] = '0'; 
	}
	c.deciNum[i] = '\0';
	c.exponent = this->exponent + b.exponent;
	int cexp = 0;
	if(this->sign > 0 && b.sign > 0)//判断正负号
	{			
		strMul(c.deciNum, this->deciNum, b.deciNum, cexp, clen);
		c.sign = 1;c.exponent += cexp;
	}
	else if (this->sign < 0 && b.sign < 0)
	{
		strMul(c.deciNum, this->deciNum, b.deciNum, cexp, clen);
		c.sign = 1;c.exponent += cexp;
	}
	else if(this->sign > 0 && b.sign < 0)
	{
		strMul(c.deciNum, this->deciNum, b.deciNum, cexp, clen);
		c.sign = -1;c.exponent += cexp;
	}
	else
	{
		strMul(c.deciNum, this->deciNum, b.deciNum, cexp, clen);
		c.sign = -1;c.exponent += cexp;
	}
	
	//cout<<c.getdeciNum()<<endl;
	
	c.set_dot = findDot(c.deciNum);
	
	return c;

}
//大数相乘运算2
hugeNumber	hugeNumber:: operator *(char str[])
{
	if(!isNumber(str))
	{
		cout<<"This is not a number! " ;
		exit(EXIT_FAILURE);				//非正常退出
	}
	hugeNumber b (str);
	return((*this) * b);
} 

////大数相加运算
//hugeNumber hugeNumber::operator +(hugeNumber &b)
//{
//	if((exponent != b.exponent))						//以*this对象为基准，规格化对象b
//		norm(b,this->exponent);
//	hugeNumber c;
//	int i = findDot(this->deciNum);//*this对象的尾数小数点位
//	int j = findDot(b.deciNum);//b对象的尾数小数点位
//	int k = c.set_dot = (i > j) ? i : j;//k取最长的整数位
//	int min = (i < j) ? i -1 : j - 1;			//短的整数位
//	//尾数整数部分
//	c.deciNum[k] = '.';					//确定小数点
//	k--;
//	while(k > 0)
//	{
//		int flag = 0;
//		int j = k; 
//		
//			c.deciNum[k] = this->deciNum[k] + (b.deciNum[k] - '0');  //错误
//			if(c.deciNum[j] > '9')		//考虑进位
//			{
//				while(flag && j >= 0)
//				{
//					c.deciNum[j] -= 10;
//					flag = 1;
//					j--;
//				}
//				if(flag && j < 0)  //数据溢出最高位
//				{
//					expandArray(c.deciNum, 1);//数组头插入1个元素
//					c.deciNum[0] = '1';
//				}
//			}
//		k--;
//	}
//	return c;
//}

//大数相加运算2
//hugeNumber hugeNumber::operator +(char str[])
//{
//	if(!isNumber(str))
//	{
//		cout<<"This is not a number! " ;
//		exit(EXIT_FAILURE);				//非正常退出
//	}
//	hugeNumber b (str);
//	if((exponent != b.exponent))						//以*this对象为基准，规格化对象b
//		norm(b,this->exponent);
//	hugeNumber c(*this);
//	int i = findDot(this->deciNum);//*this对象的尾数小数点位
//	int j = findDot(b.deciNum);//b对象的尾数小数点位
//	int k = c.set_dot = (i > j) ? i : j;//k取最长的整数位
//	int min = (i < j) ? i -1 : j - 1;			//短的整数位
//	//尾数整数部分
//	c.deciNum[k] = '.';					//确定小数点
//	k--;
//	while(k > 0)
//	{
//		int flag = 0;
//		int j = k; 
//		
//			c.deciNum[k] += (b.deciNum[k] - '0');
//			if(c.deciNum[j] > '9')		//考虑进位
//			{
//				while(flag && j >= 0)
//				{
//					c.deciNum[j] -= 10;
//					flag = 1;
//					j--;
//				}
//				if(flag && j < 0)  //数据溢出最高位
//				{
//					expandArray(c.deciNum, 1);//数组头插入1个元素
//					c.deciNum[0] = '1';
//				}
//			}
//		k--;
//	}
//	return c;
//}

//ostream& operator<<(ostream &out,hugeNumber &obj)  //输出  发在此文件提示无法访问对象.元素
//{
//	if(obj.sign < 0)out<<"-";
//	out<<obj.deciNum<<"e"<<obj.exponent<<endl;
//	return out;
//}
//
//istream& operator>>(istream &in,hugeNumber &obj)  //输入
//{
//	char ch;
//	in>>ch;
//	if(ch = '-')obj.sign = -1;
//	else obj.sign = 1;
//	in>>obj.deciNum;
//	in>>obj.exponent;
//	return in;
//}

//void isSPACE(const char *nptr)
//{
//	const char *s = nptr;
//		s = nptr;
//	 while (*s == 32) //跳过前面的空格
//		++s;
//	 while(*s != '\0')
//		 printf("%c",*s++);
//
//}
//void TOLOWER(char &s)         //传入字符
//{
//	if(s >= 'A' && s <= 'Z')
//		s += 'a' - 'A';
//	else if(s >= 'a' && s <= 'z')
//		;
//	else
//		errno = EINVAL;   //#define  EINVAL  22  无效值异常
//}



	//if(!isNumber(nptr))return ;
	//if(my_strtod(nptr,NULL) < 1e15)return;
//
//long double 
//strToDouble(const char str[],char ** endptr)
//{
//	register const char *s;
//	short int sign;     //符号位
//	
//	int got_dot;			//n. 点，小圆点;
//	int got_digit;			//n. 数字; 手指，足趾; 一指宽;
//	long double decimalNum;	//十进制小数，尾数
//	long int exponent;		//指数，阶码
//
//	if (str == NULL)   //字符串为空，作异常处理
//	{
//		 errno = EINVAL;   //#define  EINVAL  22
//		 goto noconv; 
//	}
//	s = str;
//	//while (ISSPACE (*s)) //跳过前面的空格
//	//	++s;
//	while (*s == 32)++s;
//
//	//取数据首位符号位
//	if (*s == '-' || *s == '+')
//		sign = *s++ == '-' ? -1 : 1;
//
//	decimalNum = 0.0;
//	got_dot = 0;  //是否有圆点句号
//	got_digit = 0;//是否是0-9数字
//	exponent = 0; //指数实际大小
//
//	 //处理e之前的实数
//	for (;; ++s)                 
//	{
//		 if( (*s - '0'< 10) && (*s - '0'>= 0))  //是否是字符型数字
//		{
//			 got_digit = 1;
//
//			if (decimalNum > DBL_MAX * 0.1)  //DBL_MAX为double最大正数
// 				++exponent;
//			else
//				decimalNum = (decimalNum * 10.0) + (*s - '0'); //累加数值
//
//			if (got_dot)
//				--exponent;
//		}
//		else if (!got_dot && *s == '.')   //没有遍历到小数点，又刚好碰到小数点
// 			got_dot = 1;
//		else
// 			break;
//	}
//	if (!got_digit)					//没有收集到数字
//	goto noconv;						//报错处理
//
//
//}