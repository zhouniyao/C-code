
#include"hugeNumHandle.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "math.h"
#include <limits>
#include <string>
using namespace std;


//测试大数四则运算
int main()
{
	char str[MAXSIZE];
	do{
		cout<<"请输入第一个实数(退出请输入esc):"<<endl;
		cin.clear(); //cin.fail()返回0；
		cin.sync();  //清空流
		cin.getline(str,sizeof(str));
		if(strcmp(str,"esc") == 0)exit(0);
	}while(!isNumber(str) );
		
	hugeNumber a(str);

	do{
		cout<<"请输入第二个实数(退出请输入esc):"<<endl;
		cin.clear(); //cin.fail()返回0；
		cin.sync();  //清空流
		cin.getline(str,sizeof(str));
		if(strcmp(str,"esc") == 0)exit(0);
	}while(!isNumber(str) );
		
	hugeNumber b(str);
	hugeNumber c = a + b;//只能初始化调用复制构造函数
	cout<<"输出结果为："<<endl;	
	cout<<"a + b = "<<(a + b)<<endl;
	cout<<"a - b = "<<(a - b)<<endl;
	cout<<"a * b = "<<(a * b)<<endl;
}

#if 0
//测试按精度四舍五入
int main()
{
	char str[MAXSIZE];
	do{
		cout<<"请输入一个实数(退出请输入esc):"<<endl;
		cin.clear(); //cin.fail()返回0；
		cin.sync();  //清空流
		cin.getline(str,sizeof(str));
		if(strcmp(str,"esc") == 0)exit(0);
	}while(!isNumber(str) );
		
	hugeNumber a(str);
	int prec = 0;
	do{
		cout<<"\n请输入要保留的有效位数："<<endl;
		cin.clear(); //cin.fail()返回0；
		cin.sync();  //清空流
		cin.getline(str,sizeof(str));
		prec = atoi(str);
	}while(!isNumber(str) && prec >= 0 );

	my_round(a,prec);
	cout<<"输出结果为："<<endl;
	cout<<a<<endl;
	
	//hugeNumber a("1234567890000000000e-4");
	//norm(a);
	//cout<<a<<endl;
	return 0;
}
#endif
#if 0
int main()
{
	//hugeNumber b("0000.099995");
	hugeNumber b("0.2e5");
	//hugeNumber a("00012345678.934567");
	hugeNumber c("123.456e3");
	//hugeNumber b("0000.0012345");
	//测试============
	//my_round(a,5);
	//hugeNumber a("0.2e5");
	//norm(a);  

	hugeNumber a = c*b;
	cout<<a<<endl;
	//cout<<"符号=    "<<a.getsign()<<endl;
	//cout<<"尾数=    "<<a.getdeciNum()<<endl;
	//cout<<"小数点位置=    "<<a.getdot()<<endl;
	//cout<<"指数=    "<<a.getexponent()<<endl;

	//char *a = "2222.22";
	//char *b = "3333";
	//char *c= new char[50] ;

	//int sign = 1;
	//strSub (c,a,b,sign);
	//cout<<sign<<endl;
	//cout<<c<<endl;

	//整数部分相等测试
	//char b[] = "480.012";
	//char *a = "50.55";
	//char *b = "2046";
	////char *b= "22";
	//char *c= new char[50] ;
	//int i=0;
	//int clen = strlen(a)+strlen(b)+1;
	//for(; i<clen;i++)
	//{
	//	c[i] = '0'; 
	//}
	//c[i] = '\0';
	//int cexp = 0;
	//strMul(c,a,b,cexp,clen);
	//integerMul(c,a,b,clen,strlen(a),strlen(b));
	//integerMul(c,a,b,clen,4,4);
	//integerAdd(c,b,5,4);
	//cout<<c<<endl;
	//cout<<cexp<<endl;
	////integerSub(char *c,const char *a,const char *b,int k,int i,int j,int refund)
	//int sign = 1;
	//cout<<strcmp(a,b)<<endl;
	//int i = findDot(a);//尾数a小数点位
	//int j = findDot(b);//尾数b小数点位
	//cout<<strcmp(a,b)<<endl;
	//integerMul(c,a,b,5,1,4);
	//cout<<c<<endl;
//strSub(c, a, b, sign);
//	//strAdd(c,a,b);
//	cout<<sign;//数的正负
//	cout<<endl<<c<<endl;
	return 0;
}

#endif

//int main()//求精度
//{
//	hugeNumber a("0000.012345678934567");
//	my_round(a,5);
//	cout<<a.getdeciNum()<<endl;
//	cout<<a.getdot()<<endl;
//	cout<<a.getexponent()<<endl;
//	return 0;
//}


//
//#define TOLOWER(x) ((x) | 0x20)
////#define isxdigit(c)    (('0' <= (c) && (c) <= '9') /   
////             || ('a' <= (c) && (c) <= 'f') /  
////             || ('A' <= (c) && (c) <= 'F'))  
//#define isxdigit(c)    (('0' <= (c) && (c) <= '9') || ('a' <= (c) && (c) <= 'f') || ('A' <= (c) && (c) <= 'F'))  
//#define isdigit(c)    ('0' <= (c) && (c) <= '9')
//
//unsigned long strtoul(const char *cp,char **endp,unsigned int base)
//{
//    unsigned long result = 0,value;
//
//    if (!base) {
//        base = 10;
//        if (*cp == '0') {
//            base = 8;
//            cp++;
//            if ((TOLOWER(*cp) == 'x') && isxdigit(cp[1])) {
//                cp++;
//                base = 16;
//            }
//        }
//    }
//	else if (base == 16) {
//        if (cp[0] == '0' && TOLOWER(cp[1]) == 'x')
//            cp += 2;
//    }
//    while (isxdigit(*cp) &&
//           (value = isdigit(*cp) ? *cp-'0' : TOLOWER(*cp)-'a'+10) < base) {//isdigit(*cp)是否是十进制；TOLOWER(*cp)-'a'+10   ——16进制
//        result = result*base + value;
//        cp++;
//    }
//    if (endp)
//        *endp = (char *)cp;
//    return result;
//}
//
//long strtol(const char *cp,char **endp,unsigned int base)
//{
//    if(*cp=='-')
//        return -strtoul(cp+1,endp,base);
//    return strtoul(cp,endp,base);
//}
//int atoi(const    char  *nptr)//
//{
//    return  strtol(nptr,(char **)NULL,10);
//}
//
//
//class Rectangle{
//private:
//	int width;
//	int height;
//public:
//	Rectangle(){}
//	Rectangle(int w,int h = 10):width(w),height(h)
//	{
//		cout<<"normal constructor"<<endl;
//	}
//	Rectangle(const Rectangle &b )
//	{
//		width = b.width;
//		height = b.height;
//		cout<<"copy constructor"<<endl;
//	}
//	~Rectangle()
//	{
//		cout<<"destructor"<<endl;
//	}
//	void display ()
//	{
//		cout<<"width: "<<width<<"       "<<"height: "<<height<<endl;
//	}
//};
//
//Rectangle fun(Rectangle a)
//{
//	return a;
//}
//Rectangle fun2()
//{
//	Rectangle a(10,10);
//	return a;
//}
//struct student{
//char name[20];
//int age;
//};
//int main()
//{
//	//Rectangle p[4] = {Rectangle(1,2),Rectangle(3,4),Rectangle(5,6),Rectangle(7,8)};//对象数组初始化
//	//for(int i = 0;i<4;i++)
//	//	p[i].display();
//	//
//	//struct student stu[2] = {{"yaoyao",6},{"niming",31}};		//结构数组初始化
//	//for(int i = 0;i<2;i++)
//	//	cout<<stu[i].name<<"  "<<stu[i].age<<endl;
//	//struct student st = {"mingming",32};						//结构变量初始化
//	//cout<<st.name<<"  "<<st.age<<endl;
//
//
//	return 0;
//}

