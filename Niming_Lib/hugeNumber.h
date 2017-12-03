#include <iostream>
#include <string>
#include <float.h>

//#include "strSub.h"
//#include "strMul.h"
//#include "strAdd.h"

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