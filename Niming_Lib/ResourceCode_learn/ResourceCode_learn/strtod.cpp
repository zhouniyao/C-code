////strtod 源码
///* Convert NPTR to a double. If ENDPTR is not NULL, a pointer to the
// character after the last one used in the number is put in *ENDPTR. */
//*/
//double
//strtod (const char *nptr, char **endptr)
//{
//	 register const char *s;
//	 short int sign;
//	 double num;
//	 int got_dot;        //n. 点，小圆点;
//	 int got_digit;      //n. 数字; 手指，足趾; 一指宽;
//	 long int exponent;  //指数
//	 if (nptr == NULL) 
//	{
//		 errno = EINVAL;   //#define  EINVAL  22
//		 goto noconv; 
//	}
//
//	 s = nptr;
//	 while (ISSPACE (*s)) //跳过前面的空格
//		++s;
//	 sign = *s == '-' ? -1 : 1;   //保存正负号
//	 if (*s == '-' || *s == '+')  //取下一个字符元素
//		++s;
//
//	 num = 0.0;
//	 got_dot = 0;  //圆点句号
//	 got_digit = 0;//0-9数字
//	 exponent = 0; //指数
//
//	 //处理e之前的实数
//	 for (;; ++s)                 
//	{
//		 if (ISDIGIT (*s))  //是否是数值型字符
//		{
//			 got_digit = 1;
//
//			if (num > DBL_MAX * 0.1)  //DBL_MAX为double最大表示数
// 				++exponent;
//			else
//				num = (num * 10.0) + (*s - '0'); //累加数值
//
//			if (got_dot)
//				--exponent;
//		}
//		else if (!got_dot && *s == '.')   //没有遍历到小数点，又刚好碰到小数点
// 			got_dot = 1;
//		else
// 			break;
//	}
//
//	 if (!got_digit)					//没有收集到数字
//	   goto noconv;						//报错
//
//
//
//
//
//	 if (TOLOWER (*s) == 'e')			//TOLOWER()将大写字母转换成小写
//	{
// 
//		 int save = errno;
//		 char *end;
//		 long int exp;					//指数
//
//		 errno = 0;
//		 ++s;
//
///*		 strtol()会扫描参数nptr字符串，跳过前面的空格字符，直到遇上数字或正负符号才开始做转换，
//		 再遇到非数字或字符串结束时('\0')结束转换，并将结果返回。若参数endptr不为NULL，
//		 则会将遇到不合条件而终止的nptr中的字符指针由endptr返回；若参数endptr为NULL，则会不返回非法字符串。
//		 exp = strtol (s, &end, 10); */       //long int strtol(const char *nptr,char **endptr,int base);参数base代表采用的进制方式，如base值为10则采用10进制，若base值为16则采用16进制等
//		 if (errno == ERANGE)				//#define ERANGE   34    函式的结果超出范围,例如strtol("0xfffffffff",NULL,0)
//		{
// 			if (endptr != NULL)       
//				 *endptr = end;				//endptr 不为NULL，返回strtol不能转换的字符串
//			if (exp < 0)					//下溢出
//				goto underflow;
//			else
//				goto overflow;
//		}
//		 else if (end == s)
//		 //There was no exponent. Reset END to point to
//		 //the 'e' or 'E', so *ENDPTR will be set there. 
//			end = (char *) s - 1;
//		 errno = save;
//		 s = end;
//		 exponent += exp;
//	}
//
//	 if (endptr != NULL)
//		 *endptr = (char *) s;
//
//	 if (num == 0.0)
//		 return 0.0;
//	 if (exponent < 0)
//	{
//		 if (num < DBL_MIN * pow (10.0, (double) -exponent))
//			 goto underflow;
//	}
//	 else if (exponent > 0)
//	{
//			头文件：#include <math.h>
//			pow() 函数用来求 x 的 y 次幂（次方），其原型为：
//			double pow(double x, double y);
//			pow()用来计算以x 为底的 y 次方值，然后将结果返回。
//		 if (num > DBL_MAX * pow (10.0, (double) -exponent))
//		 goto overflow;
//	}
//	 num *= pow (10.0, (double) exponent);
//
//	 return num * sign;
//
//overflow:                   //上溢出
// 
//	 errno = ERANGE;
//	 return HUGE_VAL * sign;
//
//underflow:                   //下溢出
// 
//	 if (endptr != NULL)
//	 *endptr = (char *) nptr;
//	 errno = ERANGE;
//	 return 0.0;
//
//noconv:
// 
//	 if (endptr != NULL)
//	 *endptr = (char *) nptr;
//	 return 0.0;
//}
//*/
//
//
//
//**************************************************************************************
//* FunctionName   : atoi()
//* Description        : 字符串转换成数字，字符串内存放的是ASCII
//* EntryParameter : *arr - 需要转换的十六进制数组
//* ReturnValue      : number - 转换后的数字
//**************************************************************************************/
//uint32 atoi(const uint8 *arr)
//{
//    uint8 i;
//    uint32 number = 0;
//
// for (i=0; (*(arr+i)>='0') && (*(arr+i)<='9'); i++)
// {
//     number = 10*number + (*(arr+i) - '0');
// }
// 
// return number;     // 返回转换后的数字  
//}
