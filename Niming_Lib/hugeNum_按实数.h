#include <iostream>
#include <float.h>
using namespace std;
#define isdigit(c)    ('0' <= (c) && (c) <= '9')
int isNumber(const char *nptr);
class hugeNumber{			//定义大数，10进制
private:
	long double deciNum;	//尾数
	long  exponent;	//指数
	short sign;				//符号位，取-1或1
public:
	hugeNumber(){}
	hugeNumber(long double deciNum, long  exponent, short sign = 1);
	hugeNumber(const char *nptr, char ** endptr);
	~hugeNumber(){}
	    // +-*/
	friend ostream& operator<<(ostream &a,hugeNumber &b);
	friend istream& operator>>(istream &a,hugeNumber &b);
	friend void norm(hugeNumber &hu);
	friend void norm(hugeNumber &hu,  long exp );	//按exp介规格化
	friend void my_round(hugeNumber &hu ,int prec);	//按精度四舍五入
};


	
hugeNumber::hugeNumber(long double deciNum, long  exponent, short sign )
{
	this->deciNum = deciNum;
	this->exponent = exponent;
	this->sign = sign;
}
hugeNumber::hugeNumber(const char *nptr,char ** endptr)
{
	if(!isNumber(nptr))cout<<"This is not a number! " ;
	const char *s = nptr;
		
	s = nptr;
	while (*s == 32) //跳过前面的空格，正确
		++s;
	sign = *s == '-' ? -1 : 1;   //保存正负号
	if (*s == '-' || *s == '+')  //碰到正负号，取下一个字符元素
		++s;
	deciNum = 0;		//尾数
	exponent = 0;		//指数
	int got_dot = 0;	//获得圆点个数
	int got_digit = 0;	//0-9数字

	while(*s - '0' < 10 && *s != '\0') //提取尾数的整数
	{
		deciNum = deciNum*10 + (*s++ - '0');
	}
	deciNum *= sign ;
	//提取尾数的小数
	if (*s == '.')
	{
		double factor = 1.0 ;
		s++;
		while (*s - '0' < 10 && *s != '\0')
		{
			factor /= 10 ;
			deciNum += factor * (*s++ - '0');
				
		}
	}
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
	out<<obj.deciNum<<"e"<<obj.exponent<<endl;
	return out;
}

istream& operator>>(istream &in,hugeNumber &obj)  //输入
{
	char ch;
	in>>ch;
	if(ch = '-')obj.sign = -1;
	else obj.sign = 1;
	in>>obj.deciNum;
	in>>obj.exponent;
	return in;
}

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

////返回一个对应的小写字母
//char TOLOWER(const char *s)			//传入字符指针，地址
//{
//	char tmp;
//	if(*s >= 'A' && *s <= 'Z')
//		tmp = *s + 'a' - 'A';
//	else if(*s >= 'a' && *s <= 'z')
//		;
//	else
//		errno = EINVAL;   //#define  EINVAL  22  无效值异常
//	return tmp;
//}

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

//科学计数规格化，如12.34e5，规格化后1.234e6
void norm(hugeNumber &hu) //大染缸
{

	while(hu.deciNum < 1)
	{
		hu.deciNum *= 10;
		hu.exponent--;
	}
	while(hu.deciNum >= 10)
	{
		hu.deciNum /= 10;
		hu.exponent++;
	}
}
void  norm(hugeNumber &hu, long exp ) //按exp介规格化
{
	if(hu.exponent > exp)
		for ( ; hu.exponent != exp; hu.exponent--  )
		{
			hu.deciNum *= 10;
		}
	else if(hu.exponent < exp)
		while ( hu.exponent != exp )
		{
			hu.deciNum /= 10; hu.exponent++;
		}
	else
		;
}

void my_round(hugeNumber &hu ,int prec)  //precision，规定的精度位
{
	
	norm(hu , prec+1 );             //按精度规整大数
	long temp = (long)( hu.deciNum);
	temp = (temp % 10 > 5) ? (temp + 5) /10 : temp /10 ; //个位四舍五入
	norm(hu);
}

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