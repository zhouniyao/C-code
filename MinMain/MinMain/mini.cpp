#include<iostream>
#include<stdio.h>
using namespace std;
#define NUL 0
//#include"fun_test.h"
int 
find_char( char **strings, char value )
{
	char *str;
	while(( str = *strings++ ) != NULL)
	{
		while( *str++ != '\0')      //错误，原因是下面if语句把字符串第一个字符给跳过检查了；
		{
			if( *str == value )return 1;
		}
		/*正确写法如下：
		while( *str != '\0')      
		{
			if( *str++ == value )return 1;//正确，从字符串第一个字符开始检查，后再自增str指针。
		}
		*/
	}
	return 0;
}

int main()
{
	char * cp[]={"niming","zhouyan","zhouniyao",NUL};
	//find_char(cp,'z')?printf("TRUE"):printf("FALSE");
	//printf("%d\n", ++*++cp);
	printf("%d\n",find_char(cp,'z'));

	return 0;
}
