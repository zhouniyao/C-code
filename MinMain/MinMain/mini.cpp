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
		while( *str++ != '\0')      //����ԭ��������if�����ַ�����һ���ַ�����������ˣ�
		{
			if( *str == value )return 1;
		}
		/*��ȷд�����£�
		while( *str != '\0')      
		{
			if( *str++ == value )return 1;//��ȷ�����ַ�����һ���ַ���ʼ��飬��������strָ�롣
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
