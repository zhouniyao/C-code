#include <iostream>
#include <string>
#include <float.h>

//#include "strSub.h"
//#include "strMul.h"
//#include "strAdd.h"

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