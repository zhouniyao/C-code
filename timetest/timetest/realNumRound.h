
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
	//cout << "\n������һ������";
	while(bFlag)
	{
		cin >> InputString;	
		dwReal = strtod(InputString,&pend);     //�ַ���ת��Ϊdouble
		//errorNum = errno; 
		//if (errorNum == ERANGE)  //#define ERANGE   34    ��ʽ�Ľ��������Χ,����strtol("0xfffffffff",NULL,0)
		if (errno == ERANGE) 
		{
			cout << "\n���������������һ������";
			cin.ignore( numeric_limits<streamsize>::max(), '\n' );
			_set_errno(0);
		}
		else if(pend[0] > 0)	//������ȫת��,����Ƿ�
		{
			cout << "\n����Ƿ�������������һ������";
			cin.ignore( numeric_limits<streamsize>::max(), '\n' );
		}
		else	
			bFlag = false;
	}
	return dwReal;

}