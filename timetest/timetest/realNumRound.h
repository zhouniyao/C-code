
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "math.h"
#include <limits>
#include <string>
using namespace std;

double InputReal()
{
	char InputString[256];//TranString[256];
	char *pend;
	double dwReal;

	bool bFlag = true;
	//int errorNum;
	//cout << "\n请输入一个数：";
	while(bFlag)
	{
		cin >> InputString;	
		dwReal = strtod(InputString,&pend);     //字符串转换为double
		//errorNum = errno; 
		//if (errorNum == ERANGE)  //#define ERANGE   34    函式的结果超出范围,例如strtol("0xfffffffff",NULL,0)
		if (errno == ERANGE) 
		{
			cout << "\n溢出，请重新输入一个数：";
			cin.ignore( numeric_limits<streamsize>::max(), '\n' );
			_set_errno(0);
		}
		else if(pend[0] > 0)	//不能完全转换,输入非法
		{
			cout << "\n输入非法，请重新输入一个数：";
			cin.ignore( numeric_limits<streamsize>::max(), '\n' );
		}
		else	
			bFlag = false;
	}
	return dwReal;

}