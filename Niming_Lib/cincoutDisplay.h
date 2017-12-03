#include <iomanip> 

/*
*这证明了cin读入数据遇到空格结束；
*并且丢弃空格符；缓冲区有残留数据，
*读入操作直接从缓冲区中取数据。
**结束符（Enter、Space、Tab）
*/
void cinDisplay()
{
	char str[10],str2[10];
	//cin.getline(str,5);
	cin>>str;
	cin>>str2;
	cout<<str<<endl;
	
	cout<<str2<<endl;
}
/*
*cin.get(数组名，长度，结束符)
*【用法】结束符为可选参数，读入的字符个数最多为（数组长度-1）个，结束符规定结束字符串读取的字符，默认为ENTER
*若要读取字符，直接cin.get(char ch)或ch=cin.get()即可
*除Enter结束符丢弃外，其他结束符仍然在缓冲区中。
*/
void cingetDisplay()
{
	/*
	char c1,c2;
	cin.get(c1);
	cin.get(c2);
	cout<<c1<<"    "<<c2<<endl;
	cout<<(int)c1<<"    "<<(int)c2<<endl;
	*/
	char ch[50];
	int i=0;
	cin.get(ch,49,'\n');
	//cout<<ch;
	for(;ch[i]!='\0';i++)//字符串都是以'\0'结束；
		cout<<ch[i];
	cout<<"##"<<(int)ch[i];//显示'\0'的ASCII值0；

}
/*
	cin.clear();   //cin.fail()返回0；否则循环录入，将陷入死循环。

	cin.sync();   //清空流

*/
//============================================
//cout格式化输出
//============================================
void coutDisplay()
{
//=================================================================
///*关于浮点数的格式*/ 
	/*
	【举例】 输出双精度数：
    double a=123.456789012345;  // 对a赋初值
		1) cout<<a;  输出： 123.456
		2) cout<<setprecision(9)<<a;  输出： 123.456789
		3) cout<<setprecision(6);  恢复默认格式(精度为6)
		4) cout<< setiosflags(ios∷fixed);  输出： 123.456789
		5) cout<<setiosflags(ios∷fixed)<<setprecision(8)<<a;  输出： 123.45678901
		6) cout<<setiosflags(ios∷scientific)<<a;  输出： 1.234568e+02
		7) cout<<setiosflags(ios∷scientific)<<setprecision(4)<<a;  输出： 1.2346e02
	*/
	//================================

	float f=2.0/3.0,f1=0.000000001,f2=-9.9;

	cout<<f<<' '<<f1<<' '<<f2<<endl; //正常输出

	cout.setf(ios::showpos); //强制在正数前加+号 

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout.unsetf(ios::showpos); //取消正数前加+号 

	cout.setf(ios::showpoint); //强制显示小数点后的无效0

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout.unsetf(ios::showpoint); //取消显示小数点后的无效0

	cout.setf(ios::scientific); //科学记数法 

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout.unsetf(ios::scientific); //取消科学记数法

	cout.setf(ios::fixed); //按点输出显示 

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout.unsetf(ios::fixed); //取消按点输出显示 

	cout.precision(18); //精度为18，正常为6 

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout.precision(6); //精度恢复为6 
	//===========================================================
	//浮点格式输出，方法二
	//===========================================================
	float f=2.0/3.0,f1=0.000000001,f2=-9.9;

	cout<<f<<' '<<f1<<' '<<f2<<endl; //正常输出

	cout<<setiosflags(ios::showpos); //强制在正数前加+号

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout<<resetiosflags(ios::showpos); //取消正数前加+号

	cout<<setiosflags(ios::showpoint); //强制显示小数点后的无效0

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout<<resetiosflags(ios::showpoint); //取消显示小数点后的无效0

	cout<<setiosflags(ios::scientific); //科学记数法

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout<<resetiosflags(ios::scientific); //取消科学记数法

	cout<<setiosflags(ios::fixed); //按点输出显示

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout<<resetiosflags(ios::fixed); //取消按点输出显示

	cout<<setprecision(18); //精度为18，正常为6 

	cout<<f<<' '<<f1<<' '<<f2<<endl; 

	cout<<setprecision(6); //精度恢复为6 



//=================================================================
//整数输出
//=================================================================
	int x=30, y=300, z=1024; 

	cout<<x<<' '<<y<<' '<<z<<endl; //按十进制输出

	cout.unsetf(ios::dec ); //取消十进制输出设置

	cout.setf(ios::showbase | ios::uppercase); //设置基指示符输出和数值中的字母大写输出

	cout<<x<<' '<<y<<' '<<z<<endl; 

	cout.unsetf(ios::showbase | ios::uppercase); //取消基指示符输出和数值中的字母大写输出

	cout.setf(ios::oct); //设置为八进制输出,此设置不取消一直有效

	cout<<x<<' '<<y<<' '<<z<<endl; //按八进制输出

	cout.setf(ios::showbase | ios::uppercase); //设置基指示符输出和数值中的字母大写输出

	cout<<x<<' '<<y<<' '<<z<<endl; 

	cout.unsetf(ios::showbase | ios::uppercase); //取消基指示符输出和数值中的字母大写输出

	cout.unsetf(ios::oct); //取消八进制输出设置，恢复按十进制输出

	cout.setf(ios::hex); //设置为十六进制输出 

	cout<<x<<' '<<y<<' '<<z<<endl; 

	cout.setf(ios::showbase | ios::uppercase); //设置基指示符输出和数值中的字母大写输出

	cout<<x<<' '<<y<<' '<<z<<endl; 

	cout.unsetf(ios::showbase | ios::uppercase); //取消基指示符输出和数值中的字母大写输出

	cout.unsetf(ios::hex); //取消十六进制输出设置，恢复按十进制输出

	cout<<x<<' '<<y<<' '<<z<<endl; 

	//==========================================================
	//整数输出，方法二
	//==========================================================
	cout<<x<<' '<<y<<' '<<z<<endl; //按十进制输出

	cout<<oct<<x<<' '<<y<<' '<<z<<endl; //按八进制输出

	cout<<setiosflags(ios::showbase); //设置基指示符

	cout<<x<<' '<<y<<' '<<z<<endl; //仍按八进制输出

	cout<<resetiosflags(ios::showbase); //取消基指示符

	cout<<hex<<x<<' '<<y<<' '<<z<<endl; //按十六进制输出

	cout<<setiosflags(ios::showbase | ios::uppercase);

	//设置基指示符和数值中的字母大写输出， 

	cout<<x<<' '<<y<<' '<<z<<endl; //仍按十六进制输出

	cout<<resetiosflags(ios::showbase | ios::uppercase);

	//取消基指示符和数值中的字母大写输出 

	cout<<x<<' '<<y<<' '<<z<<endl; //仍按十六进制输出

	cout<<dec<<x<<' '<<y<<' '<<z<<endl; //按十进制输出

}
/*
在c/c++系统中除了标准的输入输出外，还提供了更多的输入函数。这写函数主要有getch(),getche(),

getchar 

(),cin.get(),putch(),putchar(),cout.put(),gets(),cin.getline(),puts()。另外

还有些为了让缓冲区不影响程序的正确操作的缓冲去的操作，如：cin.putback(),fflush(stdin),cout.flush().我们

做一下简单的说明。 

1、getch()和getche(),非缓冲式输入，从键盘读入一个字符。getch()读入字符不显示。有conio.h支持。

2、cin.get(),getchar()，缓冲式输入，从键盘读入一个字符，并显示。getchar()由stdio.h支持，cin.get()由iostream.h支持。

3、putch()和putchar()，非缓冲式输出，输出一个字符到显示器。putch()由conio.h支持，putchar()由stdio.h支持。

4、cout.put()，缓冲式输出，输出一个字符到显示器。由iostream.h支持。

5、gets()和cin.geline()，缓冲式输入，读入一字符串（包括空格，不包括最后的回车），gets()由stdio.h支持，cin.getline()由iostream.h支持。

6、puts()，非缓冲输出，输出一个字符串，由stdio.h支持。 

7、cin.putback()，把一个字符送回输入缓冲区。 

8、fflush(stdin)，清除输入缓冲区操作。无法清除cin.get()等带来的操作。

9、cout.flush()，清楚输出缓冲区。 


*/