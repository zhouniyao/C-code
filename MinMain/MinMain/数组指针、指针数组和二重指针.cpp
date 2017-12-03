/*【二维数组 各个元素包含操作符（&、*）的正确释义】
*(a+0)==>a[0]是第一个一维数组的数组名和首地址 【a[i] = *(a + 1)无论是一维二维，其含义无条件等级】
*a==>*(a+0)==>a[0]是第一个一维数组的数组名和首地址 

int a[3][4]={{0,1,2,3},{4,5,6,7},{8,9,10,11}}
设数组a的首地址为1000。

从二维数组的角度来看，a是二维数组名，a代表整个二维数组的首地址，也是二维数组0行的首地址a+1代表第一行的首地址。 

a[0]是第一个一维数组的数组名和首地址，因此也为1000。*(a+0)或*a是与a[0]等效的， 它表示一维数组a[0]0 号元素的首地址，也为1000。
&a[0][0]是二维数组a的0行0列元素首地址，同样是1000。因此，a，a[0]，*(a+0)，*a，&a[0][0]是相等的。 
同理，a+1是二维数组1行的首地址，等于1008。a[1]是第二个一维数组的数组名和首地址，因此也为1008。
&a[1][0]是二维数组a的1行0列元素地址，也是1008。因此a+1,a[1],*(a+1),&a[1][0]是等同的。 

由此可得出：a+i，a[i]，*(a+i)，&a[i][0]是等同的。 

此外，&a[i]和a[i]也是等同的。因为在二维数组中不能把&a[i]理解为元素a[i]的地址，不存在元素a[i]。C语言规定，它是一种地址计算方法，表示数组a第i行首地址。由此，我们得出：a[i]，&a[i]，*(a+i)和a+i也都是等同的。 

另外，a[0]也可以看成是a[0]+0，是一维数组a[0]的0号元素的首地址，而a[0]+1则是a[0]的1号元素首地址，由此可得出a[i]+j则是一维数组a[i]的j号元素首地址，它等于&a[i][j]。 

由a[i] = *(a+i)得 a[i]+j=*(a+i)+j。由于*(a+i)+j是二维数组a的i行j列元素的地址，所以，该元素(这是个地址)存储的值等于*(*(a+i)+j)。
*/





#include<iostream>
#include<stdio.h>
#include"fun_test.h"
using namespace std;
#define NUL 0
//#include"fun_test.h"
//方法一：给定一个指向以NULL结尾的指针列表的指针，在列表中的字符串中查找一个特定的字符。
int 
find_char( char **strings, char value )
{
	char *str;
	while(( str = *strings++ ) != NULL)
	{
		//while( *str++ != '\0')      //错误，原因是下面if语句把字符串第一个字符给跳过检查了；
		//{
		//	if( *str == value )return 1;
		//}
		//正确写法如下：
		
		while( *str != '\0')      
		{
			if( *str++ == value )return 1;//正确，从字符串第一个字符开始检查，后再自增str指针。
		}
		
	}
	return 0;
}
//方法二：给定一个指向以NULL结尾的指针列表的指针，在列表中的字符串中查找一个特定的字符。
//这个函数将破坏这些指针，所以它只适用于这组字符串只使用一次的情况。
int 
find_char2( char **strings, char value )
{
		//assert(strings != NULL);
		while(*strings != NULL)		//第一个间接访问，访问指针数组当前指针（此时还是个地址）。
		{
			while(**strings != '\0')//第二个间接访问，间接访问操作随该指针访问到字符串中最终字符。
			{
				if(**strings == value)return 1; //if(*(*strings)++ == value)return 1;//书本写法
				(*strings)++;					//*(*strings)++，括号是必需的，这样才能使表达式以正确的顺序进行求值。括号内部*strings间接访问操作当前指针数组的指针，增值操作把该指针所指向的那个位置的值加1，但是外部间接引用操作作用于原先那个值得拷贝上。
			}
			strings++;
		}
		return 0;
}
//小结：间接访问也叫解引用指针。
//指针加上整数的结果是另一个指针.
//
int main()
{
	char * cp[]={"niming","zhouyan","zhouniyao",NUL};
	find_char2(cp,'w')?printf("TRUE"):printf("FALSE");
	//printf("%d\n", ++*++cp);
	//printf("\n%d\n",find_char(cp,'z'));

	return 0;
}

void fun(int a[][2])  
{  
    a[1][1]=5;  
}  
void fun1(int (*a)[2])  
{  
    a[1][1]=3;  
}     
void fun2(int *p)
{
	printf("%d",p[4]);
}
 
//========
//测试一
//========
//
//int main()
//{
//	int a[3][2]={3,4,2,6,7,9};
//	int (*pa)[2] = a; //定义数组指针，并初始化
//
//	cout<<&a[1][0]<<endl;//第a[1][0]地址 &*(*(a+1)+0)
//	cout<<*(a + 1)<<endl;//第a[1][0]地址
//	cout<<*((a)+1)<<endl;//第a[1][0]地址
//	cout<<a[1]<<endl;	//第a[1][0]地址
//	cout<<a+1<<endl;	 //第a[1][0]地址
//	cout<<*((a)+1)<<endl;//第a[1][0]地址
//	cout<<(a)+1<<endl;   //第a[1][0]地址
//	
//	cout<<&a[0][1]<<endl;//第a[0][1]地址
//	cout<<a[0]+1<<endl;//第a[0][1]地址
//	cout<<*(a)+1<<endl;//第a[0][1]地址
//
//	cout<<endl;
//	cout<<"============================"<<endl;
//	cout<<endl;
//	cout<<pa<<endl;//第一层首地址
//	cout<<pa+1<<endl;//第二层地址，其跳过一维中的2个元素
//	cout<<*(pa)+1<<endl;
//	cout<<pa[0]+1<<endl;//第三层地址
//	cout<<&a[0][1]<<endl;
//	cout<<*(*(pa)+1)<<endl;
//	cout<<a[0][1]<<endl;
//
//	int tab[8]={3,4,2,6,7,9};
//    int tab2[3][4]={3,4,2,6,7,9};
//
//	cout<<"============================"<<endl;
//	extern char p[];
//	
//	printf("%c",p[4]);
//
//	//fun2(p);
//	cout<<endl;
//	cout<<"============================"<<endl;
//	cout<<endl;
//	cout<<*(tab+3)<<endl;
//    cout<<tab[5]<<endl;
//    cout<<*(&tab[6])<<endl;
//    cout<<*(*(tab2+1))<<endl;
//    cout<<*(&tab2[0][0]+1)<<endl;//&tab2[0][0]是第三层地址，&tab2[0][0]+1  当然也是第三层次的地址
//	cout<<endl;
//	cout<<(tab2[1]+1)<<endl;  //tab2[1][1]地址
//	cout<<(*(tab2+1)+1)<<endl;  //tab2[1][1]地址
//    cout<<&tab2[1][1]<<endl; //tab2[1][1]地址
//}


//========
//测试二
//========

//void output(int (&a)[5])  //数组的引用，【例】int a[3]={0}; int (&b)[3] = a;
//{  
//    for(int i = 0; i < 5; i++)  
//        cout<<a[i]<<endl;  
//}  
//
//void output2(int **a)  //二重指针，把二维数组的值以16进制方式输出。why?
//{  
//    for(int i = 0; i < 5; i++)  
//        cout<<a[i]<<endl;  
//} 
//int main()  
//{  
//    //int a[5]={1,2,3,4,5};  
//    //output(a); 
//	int a[5][2]={11,12,3,4,5};  
//	int **p = (int **)a;
//	output2(p);
//    //getchar();  
//    return 0;  
//} 