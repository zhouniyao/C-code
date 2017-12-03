extern char *integerAdd(char *result,const char * dst,int d1,int d2);//整数相加
//extern char *removeDot(char *tmp, const char *nptr);//剔除小数点,转成整数形式
extern int findDot(const char *nptr);////返回小数点真实数组下标的位置


char *removeDot1(char *tmp, const char *nptr)
{
	int i=0,j=0;
	for(;nptr[i] != '\0';i++)
	{
		if(nptr[i] == '.')continue;
		tmp[j++] = nptr[i];
	}
	 tmp[j] = '\0';
	return tmp;
}
//两个整数相乘，c = a*b;k是结果c的长度，i是a的长度，j是b的长度，k = i+j+1;
char *integerMul(char *c, const char *a, const char *b,int k, int i, int j)//c = a*b;k是结果c的长度，i是a的长度，j是b的长度，k = i+j-1;
{
	int weight = 0;//记录当前所在位置，10的weight次方，即个十百千万……
	char *tmp = new char[k];//相乘中间值
	k--, i--, j--;
	
	//长整数作为被乘数，短整数作为乘数
	if(i > j)
	{
		
		while(j >= 0)//累加次数
		{
			int flag = 0;//进位标识
			int t = b[j] - '0';
			int tmplen = weight + i + 2;//中间值应部分使用的长度
			for(int d = 0; d < tmplen; d++)//初始化tmp，weight是多少，补多少个0
			{
				tmp[d] = '0';
			}
			tmp[tmplen] = '\0';
			for(int d = i; d >= 0; d--)//从后往前遍历a的有效数值
			{
				int tm = ((a[d]-'0')*t);
				if(flag)tm += flag;
				flag = 0;//进位标识清空
				while(tm > 9)
				{
					tm -= 10;
					flag++;
				}
				tmp[d+1] = '0' + tm;
			}
			if(flag)
				tmp[0] = flag + '0';//最高位
			else
				tmp[0] = '0';
			integerAdd(c,tmp,k+1,tmplen);
			
			j--,weight++;
		}		
	}
	else
	{
		while(i >= 0)//累加次数
		{
			int flag = 0;//进位标识
			int t = a[i] - '0';
			int tmplen = weight + j + 2;//中间值应部分使用的长度
			for(int d = 0; d < tmplen; d++)//初始化tmp，weight是多少，补多少个0
			{
				tmp[d] = '0';
			}
			tmp[tmplen] = '\0';
			for(int d = j; d >= 0; d--)//从后往前遍历b的有效数值
			{
				//tmp[d+1] = (char)((a[d]-'0')*t + '0');
				//if(flag)tmp[d+1] += flag;
				//while(tmp[d+1]>'9')
				//{
				//	tmp[d+1] -= 10;
				//	flag++;
				//}
				int tm = ((b[d]-'0')*t);
				if(flag)tm += flag;
				flag = 0;
				while(tm > 9)
				{
					tm -= 10;
					flag += 1;
				}
				
				tmp[d+1] = '0' + tm;
				//cout<<"tm"<<tm<<"   "<<tmp[d+1]<<endl;
			}
			if(flag)
				tmp[0] = flag + '0';//最高位
			else
				tmp[0] = '0';			
			integerAdd(c,tmp,k+1,tmplen);
			i--,weight++;
		}		
	}
	jumpZero(c);
	delete[]tmp;

	return c;
}
char *strMul(char *c, const char *a, const char *b,int &cexp,int k)//k为c的长度
{
	//int aexp=0, bexp=0;
	int adot = findDot(a);
	int bdot = findDot(b);
	int alength = 0 , blength = 0;//a、b字符数组总长度
	while(a[alength] != '\0')alength++;
	while(b[blength] != '\0')blength++;
	//=============================================================================================
	//第一种情形，a、b都是含有小数
	//=============================================================================================
	if(adot > 0 && bdot > 0)
	{
		int ax = alength - 1 - adot;//a小数点后面的字符长度
		int bx = blength - 1 - bdot;//b小数点后面的字符长度	
		//aexp = -ax;
		//bexp = -bx;
		cexp = -ax -bx;
		char *tmp2 = new char[512];//大小可调，拷贝a，
		char *tmp3 = new char[512];//大小可调，拷贝b
		removeDot1(tmp2,a);
		removeDot1(tmp3,b);
		integerMul(c, tmp2, tmp3, k, strlen(tmp2), strlen(tmp3));
		delete[]tmp2;
		delete[]tmp3;
	}
	//=============================================================================================
	//第二种情形，a、b都是整数
	//=============================================================================================
	if(adot < 0 && bdot < 0)
	{
		cexp = 0;
		integerMul(c,a,b,k,strlen(a),strlen(b));
	}
	//=============================================================================================
	//第三种情形，a是整数b含小数
	//=============================================================================================
	if(adot < 0 && bdot > 0)
	{
		char *tmp = new char[512];//大小可调，拷贝b
		int bx = blength - 1 - bdot;//b小数点后面的字符长度	
		cexp = - bx;
		removeDot1(tmp,b);
		integerMul(c, a, tmp, k, strlen(a),strlen(tmp));
		delete[]tmp;
	}
	//=============================================================================================
	//第四种情形，b是整数a含小数
	//=============================================================================================
	if(adot > 0 && bdot < 0)
	{
		char *tmp = new char[512];//大小可调，拷贝b
		int ax = alength - 1 - adot;//a小数点后面的字符长度
		cexp = - ax;
		removeDot1(tmp,a);
		integerMul(c, tmp, b, k, strlen(tmp),strlen(b));
		delete[]tmp;
	}
	return c;
}