#include <iostream>
#include <string>
#include <float.h>

#include "strSub.h"
#include "strMul.h"
#include "strAdd.h"

#define isdigit(c)    ('0' <= (c) && (c) <= '9')
using namespace std;
const int MAXSIZE = 512;

class hugeNumber{			//���������10����
private:
	/*char deciNum[MAXSIZE];	*/		//β��
	char *deciNum;
	long  exponent;			//ָ��
	short sign;				//����λ��ȡ-1��1
	int set_dot;			//С����λ�ã�-1��ʾû��С����
public:
	hugeNumber()
	{
		this->deciNum = new char [MAXSIZE];		//����β���ռ�
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
	hugeNumber(const hugeNumber &b);      //�������캯��
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
	friend void norm(hugeNumber &hu);				//����ѧ������񻯣���12.34e5����񻯺�1.234e6
	friend void norm(hugeNumber &hu,  long exp );	//��exp����
	friend void my_round(hugeNumber &hu ,int prec);	//��������������
	

};

extern char * strAdd(char *c , const char *a, const char *b);//��ֵ���ַ������
extern void integerAdd(char *c,const char *a,const char *b,int k,int i,int j,int flag);//�����ַ����������
int isNumber(const char *nptr);//�ж��ַ����Ƿ������������
void expandArray(char a[], int n);//n��ʾ����ͷ�����Ԫ�ظ���
void jumpZero(char * nptr);//����β��ǰ������õ�0������С����ǰ��
int findDot(const char *nptr);//����С����λ

void expandArray(char a[], int n)//n��ʾ����ͷ�����Ԫ�ظ���
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

//����β��ǰ������õ�0����С����ǰ��0����ps����ֵС�����β����Ч0��ʱ�޷��޳�
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
	int got_digit = 0;	//�õ�1-9����
	int i = 0;
	for(; *s != '\0' &&  *s - '0' < 10 && *s - '0' >= 0;)//�ӵ�һ������0������ʼ��¼
	{
		tmp[i++] = *s++; 
		got_digit = 1;
	}
	if (*s == '.')
	{
		if (!got_digit)  //  if (!i)  β������������ȫ��0��û��
		{
			tmp[0] = '0';
			i = 1;
		}
		tmp[i] = '.'; 
		s++;
		i++;
		
		while ( *s != '\0' &&  *s - '0' < 10 && *s - '0' >= 0)//��ȡβ����С��
		{
			tmp[i++] = *s++; 
		}
	}
	tmp[i] = '\0';			//���β������
	i = 0;					//��ͷ
	while(tmp[i] != '\0')	//�����ַ�����
		nptr[i++] = tmp[i];
	nptr[i] = '\0';			//��ǽ���λ
	delete []tmp;
}

//����С������ʵ�����±��λ��
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
	return -1;//��ʶδ�ҵ�С����
}

////����һ����Ӧ��Сд��ĸ
char TOLOWER(const char *s)			//�����ַ�ָ�룬��ַ
{
	char tmp;
	if(*s >= 'A' && *s <= 'Z')
		tmp = *s + 'a' - 'A';
	else if(*s >= 'a' && *s <= 'z')
		;
	else
		errno = EINVAL;   //#define  EINVAL  22  ��Чֵ�쳣
	return tmp;
}

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
		if (*s == '-' || *s == '+')  //���������ţ�ȡ��һ���ַ�Ԫ��
		++s;
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

//����ѧ������񻯣���12.34e5����񻯺�1.234e6
void norm(hugeNumber &hu) //��Ⱦ��
{
	int i = findDot(hu.deciNum);	//С����λ��
	int k = 0;						//����׸���0����λ�ã�

	char *s = hu.deciNum;
	for(; *s - '0'== 0 || *s == '.';)	// �������ַ�0��С���㣬ֱ��ɨ�赽��һ����0
	{
			++s;++k;
	}
	//k++;//�׸�����0Ҳ����С���㣬***k�����ټ�***
	if(i == -1)//β��Ϊ����
	{
		i++;
		while(hu.deciNum[i])i++;//��¼β������
		hu.deciNum[i] = '.';
		hu.deciNum[i+1] = '\0';
		while(i > 1)
		{
			hu.deciNum[i] = hu.deciNum[i-1];
			hu.deciNum[i-1] = '.';			//С����ǰһλ������һλ
			i--;
			hu.exponent++;
		}

	}
	else if (i-1 > k)
	{
		while(i-1 > k  && i > 1)//С�������׸���0���ֺ�
		{
			hu.deciNum[i] = hu.deciNum[i-1];
			hu.deciNum[i-1] = '.';			//С����ǰһλ������һλ
			i--;
			hu.exponent++;
		}
	}
	else if(i < k)
	{
		
		while(i < k  )//С�������׸���0����ǰ
		{
			hu.deciNum[i] = hu.deciNum[i+1];//С�������һ�����ݽ���λ��
			hu.deciNum[++i] = '.';
			hu.exponent--;
		}
		
	}
	else
		;
	jumpZero(hu.deciNum);
	//==========================================
	//�޳�ĩβ��С����
	//==========================================
	int j = 0;
	while(hu.deciNum[j]!= '\0')  //��Ч�ַ�����
		j++;
	if(hu.deciNum[j-1] == '.' ) //���һλ��С����
	{
		hu.deciNum[--j] = '\0';
		hu.set_dot = -1;      //û��С��������
	}
	else
		hu.set_dot = findDot(hu.deciNum);//�ҵ�С����λ��
}

//��exp����
void  norm(hugeNumber &hu, long exp ) //��exp����
{
	int i = hu.getdot(); //С����λ��
	if(exp == hu.exponent)return;
	else if(exp > hu.exponent)//С��������
	{
		while(exp > hu.exponent)//С��������
		{
			hu.exponent++;
			if(i == -1)//û��С����
			{
				int j = 0;
				while(hu.deciNum[j]!= '\0')  //��Ч�ַ�����
					j++;
				hu.deciNum[j] = '.';
				i=j;//��¼С����λ��
				hu.deciNum[++j] = '\0';
			}
			if(i == 1) //����1.234ʱ
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
				expandArray(hu.deciNum,1);//����ͷ����1��Ԫ��0
				hu.deciNum[0] = '0';
				i++;//���Ƶ�С���������ƶ�һλ
			}
			hu.deciNum[i] = hu.deciNum[i-1];
			hu.deciNum[--i] = '.';			//С����ǰһλ������һλ
			
		}
	}
	else          //��exp < hu.exponent ʱ��С��������
	{
		if(i == -1)//û��С����
		{
			int j = 0;
			while(hu.deciNum[j]!= '\0')  //��Ч�ַ�����
				j++;
			while(exp < hu.exponent)  //β��*10,��β�����0
			{
				hu.deciNum[j++] = '0';
				hu.exponent--;
			}
			hu.deciNum[j] = '\0';
		}
		else
		{

			while(exp < hu.exponent)  //��С���㣬β��*10,С��������
			{
				
				hu.exponent--;
			
				if(hu.deciNum[i+1] == '\0') //һ������
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
	//�޳�ĩβ��С����
	//==========================================
	int j = 0;
	while(hu.deciNum[j]!= '\0')  //��Ч�ַ�����
		j++;
	if(hu.deciNum[j-1] == '.' ) //���һλ��С����
	{
		hu.deciNum[--j] = '\0';
		hu.set_dot = -1;      //û��С��������
	}
	else
		hu.set_dot =  findDot(hu.deciNum);//�ҵ�С����λ��
}

//�Դ������涨���ȣ���������
void my_round(hugeNumber &hu ,int prec)  //precision���涨�ľ���λ���������Ǵ�����
{
	int i = -1;							//���С��λ��Ĭ��-1��ʾû��С����
	int k = 0;		//����׸���0����λ�ã�
	norm(hu ,0);	//�����ȹ�����������ֵ��С����
	//cout<<"niming   "<<hu<<endl;//��ȷ
	norm(hu , -prec);
	//cout<<"niming   "<<hu<<endl;//��ȷ

	char *s = hu.deciNum;
	for(; *s - '0'== 0 || *s == '.';)	// �������ַ�0��ɨ�赽��һ����0
	{
		++s;++k;	
	}
	i = findDot(hu.deciNum);			//�ҵ�С����λ��
	if(i == -1)			//û��С����
	{
		norm(hu);		//�������
		return;			//����Ҫ�������ȴﲻ��
	}
	if(i < k )			// �׸����ֵķ�0�ַ���С����λ��
	{
		errno = ERANGE;			//��������
		hu.deciNum[0] = '0';
		hu.deciNum[1] = '\0';	//���ý�����ʶ
		hu.exponent = 0;
		hu.set_dot = -1;
		return;
	}
	else         // �׸����ֵķ�0�ַ���С����λǰ
	{
		
		if(hu.deciNum[i+1] - '0' < 5)  
		{
			hu.deciNum[i] = '\0';//С��������λ
			hu.deciNum[i+1] = '\0';
		}
		else   //���ǽ�λ
		{
			int j = i-1;			//С�����ǰһλ�����һ������λ��
			hu.deciNum[i] = '\0';	//С��������λ
			hu.deciNum[i+1] = '\0';
			int flag = 1;			//��λ��ʶ
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

				if(flag && j < 0)  //����������λ
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
					expandArray(hu.deciNum, 1);//����ͷ����1��Ԫ��
					hu.deciNum[0] = '1';
				}
			
		}
		//norm(hu);//�������
	}
	
}

hugeNumber::hugeNumber(const hugeNumber &b)      //�������캯��
{
		
	this->deciNum = new char [strlen(b.deciNum)+1];		//����β���ռ�
	if(!this->deciNum )
	{
		cout<<"allocation failure!"<<endl;
		exit(EXIT_FAILURE);
	}
	strcpy(this->deciNum, b.deciNum);
	//memcpy(this->deciNum, b.deciNum, strlen(b.deciNum)*sizeof(char));//��
	this->exponent = b.exponent;
	this->sign = b.sign;
	this->set_dot = b.set_dot;
	//cout<<"������˸��ƹ��캯��"<<endl;
}
hugeNumber::hugeNumber(char deciNum[], long  exponent,int set_dot)
{
	if(!isNumber(deciNum))
	{
		cout<<"This is not a number! " ;
		exit(EXIT_FAILURE);				//�������˳�
	}
	this->deciNum = new char [MAXSIZE];		//����β���ռ�
	if(!this->deciNum )
	{
		cout<<"allocation failure!"<<endl;
		exit(EXIT_FAILURE);
	}

	const char *s = deciNum;
	s = deciNum;
	while (*s == 32) //����ǰ��Ŀո���ȷ
		++s;
	this->sign = *s == '-' ? -1 : 1;	//����������
	if (*s == '-' || *s == '+')			//���������ţ�ȡ��һ���ַ�Ԫ��
		++s;
	int i = 0;
	for(; *s != '\0' && *s - '0' < 10 ; i++)//������һ���������ֵ��ַ���ֹͣ
		*++s;
	if (*s == '.')
	{
		int set_dot = i;
	}
	strcpy(this->deciNum , deciNum);
	this->exponent = exponent;

}
//==========================
//���Ĺ��캯��
//==========================
hugeNumber::hugeNumber(const char *nptr)
{
	
	if(!isNumber(nptr))
	{
		cout<<"This is not a number! " ;
		exit(EXIT_FAILURE);				//�������˳�
	}
	this->deciNum = new char [MAXSIZE];		//����β���ռ�
	if(!this->deciNum )
	{
		cout<<"allocation failure!"<<endl;
		exit(EXIT_FAILURE);
	}
	const char *s = nptr;
		
	s = nptr;
	while (*s == 32) //����ǰ��Ŀո���ȷ
		++s;
	sign = *s == '-' ? -1 : 1;   //����������
	if (*s == '-' || *s == '+')  //���������ţ�ȡ��һ���ַ�Ԫ��
		++s;
	while (*s == '0') //����ǰ������õ�0������С����ǰ��
		++s;
	exponent = 0;		//ָ����Ĭ��ָ��Ϊ0
	set_dot = -1;		//���Բ��λ��
	int got_digit = 0;	//�õ�0-9����
	int i = 0;

	//while(*s - '0' < 10 && *s != '\0') //��ȡβ��������
	//{
	//	deciNum = deciNum*10 + (*s++ - '0');
	//}
	//deciNum *= sign ;
	for(; *s != '\0' && *s - '0' < 10 && *s - '0' >= 0; )//��ȡβ������������ for(; *s != '\0' && isdigit(*s) ; i++) ; for(; *s != '\0' && *s - '0' < 10 && *s != '.'; i++)
	{
		deciNum[i++] = *s++; 
		got_digit = 1;
	}

	//��ȡβ����С������
	if (*s == '.')
	{
		if (!got_digit)  //  if (!i)  β����������ȫ��0��û��
		{
			deciNum[0] = '0';
			set_dot = 1;	//С�����ڵڶ�λ
			i = 1;
		}
		else
		{
			set_dot = i;		//С������iλ
		}
		deciNum[set_dot] = '.'; 
		s++;
		i++;
		
		while ( *s != '\0' && *s - '0' < 10 && *s - '0' >= 0)//��ȡβ����С��	for(; *s != '\0' && *s - '0' < 10 && TOLOWER��*s�� != 'e'; i++)
		{
			deciNum[i++] = *s++; 
		}
	}
	deciNum[i] = '\0';			//���β������
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
	out<<obj.deciNum;
	if(obj.exponent != 0)out<<"e"<<obj.exponent;
	return out;
}

istream& operator>>(istream &in,hugeNumber &obj)  //����
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

//�����������
hugeNumber  hugeNumber::operator +(hugeNumber &b)
{
	if(exponent != b.exponent)
	{
		if((exponent < b.exponent))	// ��ָ��С�ĶԽ�
			norm(b,this->exponent);
		else
			norm(*this,b.exponent);
	}

	//cout<<"b����=    "<<b.getsign()<<endl;
	//cout<<"β��=    "<<b.getdeciNum()<<endl;
	//cout<<"С����λ��=    "<<b.getdot()<<endl;
	//cout<<"ָ��=    "<<b.getexponent()<<endl;


	hugeNumber c; //���շ��ظö���

	if(this->sign > 0 && b.sign > 0)//�ж�������
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
	//	cout<<"niming"<<c<<endl;//��ȷ
	return c;
}

//�����������2
hugeNumber hugeNumber::operator +(char str[])
{
	if(!isNumber(str))
	{
		cout<<"This is not a number! " ;
		exit(EXIT_FAILURE);				//�������˳�
	}
	hugeNumber b (str);
	return(*this + b);
}
//�����������
hugeNumber	hugeNumber:: operator -(hugeNumber &b)
{
	if(exponent != b.exponent)
	{
		if((exponent < b.exponent))	//��ָ��С�ĶԽ�
			norm(b,this->exponent);
		else
			norm(*this,b.exponent);
	}

	hugeNumber c; //���ظö���
	if(this->sign > 0 && b.sign > 0)//�ж�������
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
//�����������2
hugeNumber	hugeNumber:: operator -(char str[])
{
	if(!isNumber(str))
	{
		cout<<"This is not a number! " ;
		exit(EXIT_FAILURE);				//�������˳�
	}
	hugeNumber b (str);
	return(*this - b);
}

//�����������
hugeNumber	hugeNumber:: operator *(hugeNumber &b)
{
	//if((exponent != b.exponent))	// �Խ�
	//	norm(b,this->exponent);
	hugeNumber c; //���ظö���
	int clen = strlen(this->deciNum)+strlen(b.deciNum)+1;
	int i = 0;
	for(; i<clen;i++)
	{
		c.deciNum[i] = '0'; 
	}
	c.deciNum[i] = '\0';
	c.exponent = this->exponent + b.exponent;
	int cexp = 0;
	if(this->sign > 0 && b.sign > 0)//�ж�������
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
//�����������2
hugeNumber	hugeNumber:: operator *(char str[])
{
	if(!isNumber(str))
	{
		cout<<"This is not a number! " ;
		exit(EXIT_FAILURE);				//�������˳�
	}
	hugeNumber b (str);
	return((*this) * b);
} 

////�����������
//hugeNumber hugeNumber::operator +(hugeNumber &b)
//{
//	if((exponent != b.exponent))						//��*this����Ϊ��׼����񻯶���b
//		norm(b,this->exponent);
//	hugeNumber c;
//	int i = findDot(this->deciNum);//*this�����β��С����λ
//	int j = findDot(b.deciNum);//b�����β��С����λ
//	int k = c.set_dot = (i > j) ? i : j;//kȡ�������λ
//	int min = (i < j) ? i -1 : j - 1;			//�̵�����λ
//	//β����������
//	c.deciNum[k] = '.';					//ȷ��С����
//	k--;
//	while(k > 0)
//	{
//		int flag = 0;
//		int j = k; 
//		
//			c.deciNum[k] = this->deciNum[k] + (b.deciNum[k] - '0');  //����
//			if(c.deciNum[j] > '9')		//���ǽ�λ
//			{
//				while(flag && j >= 0)
//				{
//					c.deciNum[j] -= 10;
//					flag = 1;
//					j--;
//				}
//				if(flag && j < 0)  //����������λ
//				{
//					expandArray(c.deciNum, 1);//����ͷ����1��Ԫ��
//					c.deciNum[0] = '1';
//				}
//			}
//		k--;
//	}
//	return c;
//}

//�����������2
//hugeNumber hugeNumber::operator +(char str[])
//{
//	if(!isNumber(str))
//	{
//		cout<<"This is not a number! " ;
//		exit(EXIT_FAILURE);				//�������˳�
//	}
//	hugeNumber b (str);
//	if((exponent != b.exponent))						//��*this����Ϊ��׼����񻯶���b
//		norm(b,this->exponent);
//	hugeNumber c(*this);
//	int i = findDot(this->deciNum);//*this�����β��С����λ
//	int j = findDot(b.deciNum);//b�����β��С����λ
//	int k = c.set_dot = (i > j) ? i : j;//kȡ�������λ
//	int min = (i < j) ? i -1 : j - 1;			//�̵�����λ
//	//β����������
//	c.deciNum[k] = '.';					//ȷ��С����
//	k--;
//	while(k > 0)
//	{
//		int flag = 0;
//		int j = k; 
//		
//			c.deciNum[k] += (b.deciNum[k] - '0');
//			if(c.deciNum[j] > '9')		//���ǽ�λ
//			{
//				while(flag && j >= 0)
//				{
//					c.deciNum[j] -= 10;
//					flag = 1;
//					j--;
//				}
//				if(flag && j < 0)  //����������λ
//				{
//					expandArray(c.deciNum, 1);//����ͷ����1��Ԫ��
//					c.deciNum[0] = '1';
//				}
//			}
//		k--;
//	}
//	return c;
//}

//ostream& operator<<(ostream &out,hugeNumber &obj)  //���  ���ڴ��ļ���ʾ�޷����ʶ���.Ԫ��
//{
//	if(obj.sign < 0)out<<"-";
//	out<<obj.deciNum<<"e"<<obj.exponent<<endl;
//	return out;
//}
//
//istream& operator>>(istream &in,hugeNumber &obj)  //����
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