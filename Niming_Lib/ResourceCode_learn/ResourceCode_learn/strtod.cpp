////strtod Դ��
///* Convert NPTR to a double. If ENDPTR is not NULL, a pointer to the
// character after the last one used in the number is put in *ENDPTR. */
//*/
//double
//strtod (const char *nptr, char **endptr)
//{
//	 register const char *s;
//	 short int sign;
//	 double num;
//	 int got_dot;        //n. �㣬СԲ��;
//	 int got_digit;      //n. ����; ��ָ����ֺ; һָ��;
//	 long int exponent;  //ָ��
//	 if (nptr == NULL) 
//	{
//		 errno = EINVAL;   //#define  EINVAL  22
//		 goto noconv; 
//	}
//
//	 s = nptr;
//	 while (ISSPACE (*s)) //����ǰ��Ŀո�
//		++s;
//	 sign = *s == '-' ? -1 : 1;   //����������
//	 if (*s == '-' || *s == '+')  //ȡ��һ���ַ�Ԫ��
//		++s;
//
//	 num = 0.0;
//	 got_dot = 0;  //Բ����
//	 got_digit = 0;//0-9����
//	 exponent = 0; //ָ��
//
//	 //����e֮ǰ��ʵ��
//	 for (;; ++s)                 
//	{
//		 if (ISDIGIT (*s))  //�Ƿ�����ֵ���ַ�
//		{
//			 got_digit = 1;
//
//			if (num > DBL_MAX * 0.1)  //DBL_MAXΪdouble����ʾ��
// 				++exponent;
//			else
//				num = (num * 10.0) + (*s - '0'); //�ۼ���ֵ
//
//			if (got_dot)
//				--exponent;
//		}
//		else if (!got_dot && *s == '.')   //û�б�����С���㣬�ָպ�����С����
// 			got_dot = 1;
//		else
// 			break;
//	}
//
//	 if (!got_digit)					//û���ռ�������
//	   goto noconv;						//����
//
//
//
//
//
//	 if (TOLOWER (*s) == 'e')			//TOLOWER()����д��ĸת����Сд
//	{
// 
//		 int save = errno;
//		 char *end;
//		 long int exp;					//ָ��
//
//		 errno = 0;
//		 ++s;
//
///*		 strtol()��ɨ�����nptr�ַ���������ǰ��Ŀո��ַ���ֱ���������ֻ��������Ųſ�ʼ��ת����
//		 �����������ֻ��ַ�������ʱ('\0')����ת��������������ء�������endptr��ΪNULL��
//		 ��Ὣ����������������ֹ��nptr�е��ַ�ָ����endptr���أ�������endptrΪNULL����᲻���طǷ��ַ�����
//		 exp = strtol (s, &end, 10); */       //long int strtol(const char *nptr,char **endptr,int base);����base������õĽ��Ʒ�ʽ����baseֵΪ10�����10���ƣ���baseֵΪ16�����16���Ƶ�
//		 if (errno == ERANGE)				//#define ERANGE   34    ��ʽ�Ľ��������Χ,����strtol("0xfffffffff",NULL,0)
//		{
// 			if (endptr != NULL)       
//				 *endptr = end;				//endptr ��ΪNULL������strtol����ת�����ַ���
//			if (exp < 0)					//�����
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
//			ͷ�ļ���#include <math.h>
//			pow() ���������� x �� y ���ݣ��η�������ԭ��Ϊ��
//			double pow(double x, double y);
//			pow()����������x Ϊ�׵� y �η�ֵ��Ȼ�󽫽�����ء�
//		 if (num > DBL_MAX * pow (10.0, (double) -exponent))
//		 goto overflow;
//	}
//	 num *= pow (10.0, (double) exponent);
//
//	 return num * sign;
//
//overflow:                   //�����
// 
//	 errno = ERANGE;
//	 return HUGE_VAL * sign;
//
//underflow:                   //�����
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
//* Description        : �ַ���ת�������֣��ַ����ڴ�ŵ���ASCII
//* EntryParameter : *arr - ��Ҫת����ʮ����������
//* ReturnValue      : number - ת���������
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
// return number;     // ����ת���������  
//}
