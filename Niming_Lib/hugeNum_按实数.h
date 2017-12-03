#include <iostream>
#include <float.h>
using namespace std;
#define isdigit(c)    ('0' <= (c) && (c) <= '9')
int isNumber(const char *nptr);
class hugeNumber{			//���������10����
private:
	long double deciNum;	//β��
	long  exponent;	//ָ��
	short sign;				//����λ��ȡ-1��1
public:
	hugeNumber(){}
	hugeNumber(long double deciNum, long  exponent, short sign = 1);
	hugeNumber(const char *nptr, char ** endptr);
	~hugeNumber(){}
	    // +-*/
	friend ostream& operator<<(ostream &a,hugeNumber &b);
	friend istream& operator>>(istream &a,hugeNumber &b);
	friend void norm(hugeNumber &hu);
	friend void norm(hugeNumber &hu,  long exp );	//��exp����
	friend void my_round(hugeNumber &hu ,int prec);	//��������������
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
	while (*s == 32) //����ǰ��Ŀո���ȷ
		++s;
	sign = *s == '-' ? -1 : 1;   //����������
	if (*s == '-' || *s == '+')  //���������ţ�ȡ��һ���ַ�Ԫ��
		++s;
	deciNum = 0;		//β��
	exponent = 0;		//ָ��
	int got_dot = 0;	//���Բ�����
	int got_digit = 0;	//0-9����

	while(*s - '0' < 10 && *s != '\0') //��ȡβ��������
	{
		deciNum = deciNum*10 + (*s++ - '0');
	}
	deciNum *= sign ;
	//��ȡβ����С��
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
	//��ȡָ��
	if( *s == 'e'||*s == 'E')//�պ�����Eʱ�����ú���״̬
	{
		s++;
		int sign2 = 1 ;		//ָ�������Ǹ���
		sign2 = (*s == '-') ? -1 : 1;   //����������
		if (*s == '-' || *s == '+')  //���������ţ�ȡ��һ���ַ�Ԫ��
			++s;
		while( *s != '\0' ) //��ȡָ��������
		{
			exponent = exponent*10 + (*s++ - '0');
		}
		exponent *= sign2;
	}

}

ostream& operator<<(ostream &out,hugeNumber &obj)  //���
{
	if(obj.sign < 0)out<<"-";
	out<<obj.deciNum<<"e"<<obj.exponent<<endl;
	return out;
}

istream& operator>>(istream &in,hugeNumber &obj)  //����
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
//	 while (*s == 32) //����ǰ��Ŀո�
//		++s;
//	 while(*s != '\0')
//		 printf("%c",*s++);
//
//}
//void TOLOWER(char &s)         //�����ַ�
//{
//	if(s >= 'A' && s <= 'Z')
//		s += 'a' - 'A';
//	else if(s >= 'a' && s <= 'z')
//		;
//	else
//		errno = EINVAL;   //#define  EINVAL  22  ��Чֵ�쳣
//}

////����һ����Ӧ��Сд��ĸ
//char TOLOWER(const char *s)			//�����ַ�ָ�룬��ַ
//{
//	char tmp;
//	if(*s >= 'A' && *s <= 'Z')
//		tmp = *s + 'a' - 'A';
//	else if(*s >= 'a' && *s <= 'z')
//		;
//	else
//		errno = EINVAL;   //#define  EINVAL  22  ��Чֵ�쳣
//	return tmp;
//}

//�ж��Ƿ���ʵ�����˴���������10����
int isNumber(const char *nptr)
{
	const char *s = nptr;

	if (nptr == NULL) //�ж��ַ����Ƿ�Ϊ��
	{
		
		 goto noNumber; 
	}
	s = nptr;
	 while (*s == 32) //����ǰ��Ŀո���ȷ
		++s;
	if (*s == '-' || *s == '+')  //���������ţ�ȡ��һ���ַ�Ԫ��
		++s;

	int flag = 1;		//��������ֵ�ַ����
	int got_dot = 0;  //���Բ�����
	int got_digit = 0;//0-9����

	for(; (*s != '\0') ;++s)
	{
		//if( (*s - '0'< 10) && (*s - '0'>= 0))	//�Ƿ����ַ�������
		if(isdigit(*s))
			got_digit = 1 ;
		else if (!got_dot && *s == '.')			//û�б�����С���㣬�ָպ�����С����ʱ�����ú���״̬
 			got_dot = 1;
		else
			break;				//����ַ�������ֵ�͵��ַ�,��������e
		
	}
	
	if (!got_digit )					//û���ռ�������
		 goto noNumber;						                
	if( *s != '\0' && *s != 'e' && *s != 'E')//�ж��쳣�ַ�
		goto noNumber;	
	if( *s == 'e'||*s == 'E')//û�б�����E���ָպ�����Eʱ�����ú���״̬
	{
		s++;
		for(;*s != '\0';++s)           //ָ���Ƿ�Ϸ�
		{
			//if( (*s - '0'< 10) && (*s - '0'>= 0))	//�Ƿ����ַ�������
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

//��ѧ������񻯣���12.34e5����񻯺�1.234e6
void norm(hugeNumber &hu) //��Ⱦ��
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
void  norm(hugeNumber &hu, long exp ) //��exp����
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

void my_round(hugeNumber &hu ,int prec)  //precision���涨�ľ���λ
{
	
	norm(hu , prec+1 );             //�����ȹ�������
	long temp = (long)( hu.deciNum);
	temp = (temp % 10 > 5) ? (temp + 5) /10 : temp /10 ; //��λ��������
	norm(hu);
}

	//if(!isNumber(nptr))return ;
	//if(my_strtod(nptr,NULL) < 1e15)return;
//
//long double 
//strToDouble(const char str[],char ** endptr)
//{
//	register const char *s;
//	short int sign;     //����λ
//	
//	int got_dot;			//n. �㣬СԲ��;
//	int got_digit;			//n. ����; ��ָ����ֺ; һָ��;
//	long double decimalNum;	//ʮ����С����β��
//	long int exponent;		//ָ��������
//
//	if (str == NULL)   //�ַ���Ϊ�գ����쳣����
//	{
//		 errno = EINVAL;   //#define  EINVAL  22
//		 goto noconv; 
//	}
//	s = str;
//	//while (ISSPACE (*s)) //����ǰ��Ŀո�
//	//	++s;
//	while (*s == 32)++s;
//
//	//ȡ������λ����λ
//	if (*s == '-' || *s == '+')
//		sign = *s++ == '-' ? -1 : 1;
//
//	decimalNum = 0.0;
//	got_dot = 0;  //�Ƿ���Բ����
//	got_digit = 0;//�Ƿ���0-9����
//	exponent = 0; //ָ��ʵ�ʴ�С
//
//	 //����e֮ǰ��ʵ��
//	for (;; ++s)                 
//	{
//		 if( (*s - '0'< 10) && (*s - '0'>= 0))  //�Ƿ����ַ�������
//		{
//			 got_digit = 1;
//
//			if (decimalNum > DBL_MAX * 0.1)  //DBL_MAXΪdouble�������
// 				++exponent;
//			else
//				decimalNum = (decimalNum * 10.0) + (*s - '0'); //�ۼ���ֵ
//
//			if (got_dot)
//				--exponent;
//		}
//		else if (!got_dot && *s == '.')   //û�б�����С���㣬�ָպ�����С����
// 			got_dot = 1;
//		else
// 			break;
//	}
//	if (!got_digit)					//û���ռ�������
//	goto noconv;						//������
//
//
//}