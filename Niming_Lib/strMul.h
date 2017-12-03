extern char *integerAdd(char *result,const char * dst,int d1,int d2);//�������
//extern char *removeDot(char *tmp, const char *nptr);//�޳�С����,ת��������ʽ
extern int findDot(const char *nptr);////����С������ʵ�����±��λ��


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
//����������ˣ�c = a*b;k�ǽ��c�ĳ��ȣ�i��a�ĳ��ȣ�j��b�ĳ��ȣ�k = i+j+1;
char *integerMul(char *c, const char *a, const char *b,int k, int i, int j)//c = a*b;k�ǽ��c�ĳ��ȣ�i��a�ĳ��ȣ�j��b�ĳ��ȣ�k = i+j-1;
{
	int weight = 0;//��¼��ǰ����λ�ã�10��weight�η�������ʮ��ǧ�򡭡�
	char *tmp = new char[k];//����м�ֵ
	k--, i--, j--;
	
	//��������Ϊ����������������Ϊ����
	if(i > j)
	{
		
		while(j >= 0)//�ۼӴ���
		{
			int flag = 0;//��λ��ʶ
			int t = b[j] - '0';
			int tmplen = weight + i + 2;//�м�ֵӦ����ʹ�õĳ���
			for(int d = 0; d < tmplen; d++)//��ʼ��tmp��weight�Ƕ��٣������ٸ�0
			{
				tmp[d] = '0';
			}
			tmp[tmplen] = '\0';
			for(int d = i; d >= 0; d--)//�Ӻ���ǰ����a����Ч��ֵ
			{
				int tm = ((a[d]-'0')*t);
				if(flag)tm += flag;
				flag = 0;//��λ��ʶ���
				while(tm > 9)
				{
					tm -= 10;
					flag++;
				}
				tmp[d+1] = '0' + tm;
			}
			if(flag)
				tmp[0] = flag + '0';//���λ
			else
				tmp[0] = '0';
			integerAdd(c,tmp,k+1,tmplen);
			
			j--,weight++;
		}		
	}
	else
	{
		while(i >= 0)//�ۼӴ���
		{
			int flag = 0;//��λ��ʶ
			int t = a[i] - '0';
			int tmplen = weight + j + 2;//�м�ֵӦ����ʹ�õĳ���
			for(int d = 0; d < tmplen; d++)//��ʼ��tmp��weight�Ƕ��٣������ٸ�0
			{
				tmp[d] = '0';
			}
			tmp[tmplen] = '\0';
			for(int d = j; d >= 0; d--)//�Ӻ���ǰ����b����Ч��ֵ
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
				tmp[0] = flag + '0';//���λ
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
char *strMul(char *c, const char *a, const char *b,int &cexp,int k)//kΪc�ĳ���
{
	//int aexp=0, bexp=0;
	int adot = findDot(a);
	int bdot = findDot(b);
	int alength = 0 , blength = 0;//a��b�ַ������ܳ���
	while(a[alength] != '\0')alength++;
	while(b[blength] != '\0')blength++;
	//=============================================================================================
	//��һ�����Σ�a��b���Ǻ���С��
	//=============================================================================================
	if(adot > 0 && bdot > 0)
	{
		int ax = alength - 1 - adot;//aС���������ַ�����
		int bx = blength - 1 - bdot;//bС���������ַ�����	
		//aexp = -ax;
		//bexp = -bx;
		cexp = -ax -bx;
		char *tmp2 = new char[512];//��С�ɵ�������a��
		char *tmp3 = new char[512];//��С�ɵ�������b
		removeDot1(tmp2,a);
		removeDot1(tmp3,b);
		integerMul(c, tmp2, tmp3, k, strlen(tmp2), strlen(tmp3));
		delete[]tmp2;
		delete[]tmp3;
	}
	//=============================================================================================
	//�ڶ������Σ�a��b��������
	//=============================================================================================
	if(adot < 0 && bdot < 0)
	{
		cexp = 0;
		integerMul(c,a,b,k,strlen(a),strlen(b));
	}
	//=============================================================================================
	//���������Σ�a������b��С��
	//=============================================================================================
	if(adot < 0 && bdot > 0)
	{
		char *tmp = new char[512];//��С�ɵ�������b
		int bx = blength - 1 - bdot;//bС���������ַ�����	
		cexp = - bx;
		removeDot1(tmp,b);
		integerMul(c, a, tmp, k, strlen(a),strlen(tmp));
		delete[]tmp;
	}
	//=============================================================================================
	//���������Σ�b������a��С��
	//=============================================================================================
	if(adot > 0 && bdot < 0)
	{
		char *tmp = new char[512];//��С�ɵ�������b
		int ax = alength - 1 - adot;//aС���������ַ�����
		cexp = - ax;
		removeDot1(tmp,a);
		integerMul(c, tmp, b, k, strlen(tmp),strlen(b));
		delete[]tmp;
	}
	return c;
}