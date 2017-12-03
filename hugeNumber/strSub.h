#include <string>
#include <iostream>
using namespace std;
extern void integerAdd(char *c,const char *a,const char *b,int k,int i,int j,int flag);
extern void jumpZero(char * nptr);
extern int findDot(const char *nptr);//����С����λ

//�޳�С����
char *removeDot(char *tmp, const char *nptr)
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


//�����ַ����鳤�ȣ��Ƚ�����ֵ�ʹ�С,s1�Ӵ�����s2�Ӵ�����1����ȷ���0��s1�Ӵ�С��s2�Ӵ�����-1��
int my_strcmp(const char *s1, const char * s2, int i, int j, int m, int n)//i-jΪs1�Ӵ���ֹλ��m-nΪs2�Ӵ���ֹλ
{
	int d1 = j + 1 - i;//�Ӵ���0��ʼ�ĳ���
	int d2 = n + 1 - m;
	char * tmp1 = new char[d1];
	char * tmp2 = new char[d2];
	for(int k = 0; k < d1; k++)
	{
		tmp1[k] = s1[i + k];
	}
	tmp1[d1] = '\0';
	for(int k = 0; k < d2; k++)
	{
		tmp2[k] = s2[i + k];
	}
	tmp2[d2] = '\0';
	return(strcmp(tmp1,tmp2));
}
//�����ַ����������c = a - b;���涨 a > b
void integerSub(char *c,const char *a,const char *b,int k,int i,int j,int refund)//a��b��û��С����kΪc���鳤�ȣ�iΪa���鳤�ȡ���refundΪ�˻� 1 ��ʶ
{
	// k = a;
	c[k] = '\0';
	k--;i--;j--;//�޳����ı�ǽ���λ
	while(j >= 0)
	{
		if(a[i] < b[j])//������
		{
			c[k] = a[i] - (b[j] -  '0') + 10;
			if(refund)c[k] -= 1;//�һ�֮ǰ�Ľ�λ
			refund = 1;			//a ������ǰһλ��λ
		}
		else if(a[i] == b[j])
		{
			if(!refund)c[k] = '0';
			else//�һ�֮ǰ�Ľ�λ
			{
				c[k] = '9';
				refund = 1;	
			}
		}
		else
		{
			c[k] = a[i] - (b[j] -  '0');
			if(refund)c[k] -= 1;//�һ�֮ǰ�Ľ�λ
			refund = 0;
		}
		k--;i--;j--;
	}
	while(i >= 0)
	{
		c[k] = a[i];
		if(refund)c[k] -= 1;//�һ�֮ǰ�Ľ�λ
		if(c[k] < '0')
		{
			refund = 1;
			c[k] += 10;
		}
		k--;i--;
	}
}

//��ֵ���ַ��������sign��������
char * strSub(char *c , const char *a, const char *b, int &sign)  //c = a - b, sign���ط���
{
	int i = findDot(a);//β��aС����λ
	int j = findDot(b);//β��bС����λ
	
	int refund = 0;
	//==============================================
	//a��b ��Ϊ��������С����
	//==============================================

	if(i == -1 && j == -1)
	{	
		int k = 0;
		i++;j++;
		while(a[i] != '\0')i++;//a���鳤��
		while(b[j] != '\0')j++;//b���鳤��
		//��ʱ b[j] == '\0'		
		if(i > j)//a����b
		{
			k = i;
			sign = 1;
			integerSub(c, a, b, k, i, j, 0);
		}
		else if (i == j && a[0] > b[0])
		{
			k = i;
			sign = 1;
			integerSub(c, a, b, k, i, j, 0);
		}
		else//aС��b
		{
			k = j;
			sign = -1;
			integerSub(c, b, a, k, j, i, 0);
		}
	}
	//==================================================
	//a��b ��һ����С��
	//==================================================
	else if(i == -1 && j > 0)//a��������b��С��
	{
		i++;
		while(a[i] != '\0')i++;//a�ַ����鳤��
		if(i > j)//a����b
		{
			sign = 1;
			integerSub(c, a, b, i, i, j, 0);
			//cout<<c<<endl;//��ȷ
			//����С���������⡿��bС��ȫ����Ч0���㷨�����
			char *tmp = new char[512];//��С�ɵ�
			int blen = 0;
			while(b[blen] != '\0')blen++;
			int bx = blen - 1 - j;  //b����С�����ֳ���
		
			for(int k = j +1, d = 0 ; k < blen ; )
			{
				tmp[d++] = b[k++];//����bС������	
				//cout<<bx<<"   "<<d<<endl;
			}
			
			tmp[bx] = '\0';//���tmp����λ						
			char *tmp2 = new char[bx +1];//����ռ䳤����0---bx
			char *tmp3 = new char[bx +1];//����ռ䳤����0-��-bx
			for(int d = 0 ; d < bx ; d++)
				tmp2[d] = '9';
			tmp2[bx] = '\0';
			
			integerSub(tmp3, tmp2, tmp, bx, bx, bx, 0);// tmp3 = tmp2 - tmp
				//cout<<"�˴�"<<tmp3<<endl;//��ȷ
			for(int d = 0 ; d < bx - 1 ; d++)//tmp2���ó���ʱ����"00000000001"
			{
				tmp2[d] = '0';
			}
			tmp2[bx - 1] = '1';
			tmp2[bx] = '\0';
			//cout<<tmp2;//��ȷ
			integerAdd(tmp, tmp3, tmp2, bx, bx, bx, 0);//tmp = tmp3 + "00000000001"
			//cout<<tmp;//��ȷ
			
			tmp[bx + 1] = '\0';	
			for( int d = bx ; d > 0; d--)//�ڳ�λ������С����
			{
				tmp[d] = tmp[d - 1];
			}
			tmp[0] = '.';
			//c��������-1
			c[i-1] -= 1;
			if(c[i-1] < '0')//��λ����
			{
				int d = i-1;
				c[d--] += 10;//��λ��λ�ɹ�
				while(1)
				{
					c[d] -= 1;
					if(c[d] < '0')
					{						
						c[d--] += 10;//��λ��λ�ɹ�
					}
					else
						break;
				}
			}
			
			
			//==========================
			//����������β��
			//==========================
			strcat(c, tmp);

			delete[]tmp;//?����Ŀռ䲻���ջأ�����
			delete[]tmp2;
			delete[]tmp3;
				
		}
		else if (i == j && my_strcmp(a,b,0,i-1,0,j-1) > 0)
		{
			sign = 1;
			integerSub(c, a, b, i, i, j, 0);
			//cout<<c<<endl;//��ȷ
			//����С���������⡿��bС��ȫ����Ч0���㷨�����
			char *tmp = new char[512];//��С�ɵ�
			int blen = 0;
			while(b[blen] != '\0')blen++;
			int bx = blen - 1 - j;  //b����С�����ֳ���
		
			for(int k = j +1, d = 0 ; k < blen ; )
			{
				tmp[d++] = b[k++];//����bС������	
				//cout<<bx<<"   "<<d<<endl;
			}
			
			tmp[bx] = '\0';//���tmp����λ						
			char *tmp2 = new char[bx +1];//����ռ䳤����0---bx
			char *tmp3 = new char[bx +1];//����ռ䳤����0-��-bx
			for(int d = 0 ; d < bx ; d++)
				tmp2[d] = '9';
			tmp2[bx] = '\0';
			
			integerSub(tmp3, tmp2, tmp, bx, bx, bx, 0);// tmp3 = tmp2 - tmp
				//cout<<"�˴�"<<tmp3<<endl;//��ȷ
			for(int d = 0 ; d < bx - 1 ; d++)//tmp2���ó���ʱ����"00000000001"
			{
				tmp2[d] = '0';
			}
			tmp2[bx - 1] = '1';
			tmp2[bx] = '\0';
			//cout<<tmp2;//��ȷ
			integerAdd(tmp, tmp3, tmp2, bx, bx, bx, 0);//tmp = tmp3 + "00000000001"
			//cout<<tmp;//��ȷ
			
			tmp[bx + 1] = '\0';	
			for( int d = bx ; d > 0; d--)//�ڳ�λ������С����
			{
				tmp[d] = tmp[d - 1];
			}
			tmp[0] = '.';
			//c��������-1
			c[i-1] -= 1;
			if(c[i-1] < '0')//��λ����
			{
				int d = i-1;
				c[d--] += 10;//��λ��λ�ɹ�
				while(1)
				{
					c[d] -= 1;
					if(c[d] < '0')
					{						
						c[d--] += 10;//��λ��λ�ɹ�
					}
					else
						break;
				}
			}
			
			
			//==========================
			//����������β��
			//==========================
			strcat(c, tmp);
			//delete[]tmp;
			//delete[]tmp2;
			//delete[]tmp3;
		}
		else//aС��b
		{
			sign = -1;//a��bС
			integerSub(c, b, a, j, j, i, 0);
			int d = 0;
			for(d = j; b[d] != '\0'; d++)//����С��������С����
				c[d]=b[d];
			c[d] = '\0';
		}
		
	}
	else if(i > 0 && j < 0)
		//==============================
		//a��С����b�����������������Ρ�
		//==============================
	{
		j++;
		while(b[j] != '\0')j++;//b�ַ����鳤��
		//=============================================================================================
		//a��С����a���������ִ��ڵ���b�������֣���a > b,ͼʾ���Σ�3��
		//=============================================================================================
		if(i > j )
		{		
			sign = 1;
			integerSub(c,a,b,i,i,j,0);
			int d = 0;
			for(d = i; a[d] != '\0'; d++)//����С��������С����
				c[d]=a[d];
			c[d] = '\0';
		}
		else if(i == j && my_strcmp(a,b,0,i-1,0,j-1) >= 0)
		{
			sign = 1;
			integerSub(c,a,b,i,i,j,0);
			int d = 0;
			for(d = i; a[d] != '\0'; d++)//����С��������С����
				c[d]=a[d];
			c[d] = '\0';
		}
		else
		{ 
			//=============================================================================================
			//a��С����a����������С��b�������֣���a < b,ͼʾ���Σ�4��
			//=============================================================================================
		 	sign = -1;
			integerSub(c, b, a, j, j, i, 0);
			//cout<<c<<endl;//��ȷ
			//����С���������⡿��bС��ȫ����Ч0���㷨�����
			char *tmp = new char[512];//��С�ɵ�
			int alen = 0;
			while(a[alen] != '\0')alen++;
			int ax = alen - 1 - i;  //a����С�����ֳ���
		
			for(int k = i +1, d = 0 ; k < alen ; )
			{
				tmp[d++] = a[k++];//����bС������,������С����	
				//cout<<bx<<"   "<<d<<endl;
			}			
			tmp[ax] = '\0';//���tmp����λ		

			//cout<<tmp<<endl;//��ȷ
			char *tmp2 = new char[ax +1];//����ռ䳤����0---ax
			char *tmp3 = new char[ax +1];//����ռ䳤����0-��-ax
			for(int d = 0 ; d < ax ; d++)
				tmp2[d] = '9';
			tmp2[ax] = '\0';
			//cout<<tmp2<<endl;//��ȷ
			integerSub(tmp3, tmp2, tmp, ax, ax, ax, 0);// tmp3 = tmp2 - tmp
			//cout<<"�˴�"<<tmp3<<endl;//��ȷ
			for(int d = 0 ; d < ax - 1 ; d++)//tmp2���ó���ʱ����"00000000001"
			{
				tmp2[d] = '0';
			}
			tmp2[ax - 1] = '1';
			tmp2[ax] = '\0';
			//cout<<tmp2;//��ȷ
			integerAdd(tmp, tmp3, tmp2, ax, ax, ax, 0);//tmp = tmp3 + "00000000001"
			//cout<<tmp;//��ȷ
			
			tmp[ax + 1] = '\0';	//�ڳ�λ������С����
			for( int d = ax ; d > 0; d--)
			{
				tmp[d] = tmp[d - 1];
			}
			tmp[0] = '.';
			//cout<<tmp;//��ȷ
			//c��������-1
			c[j-1] -= 1;
			if(c[j-1] < '0')//��λ����
			{
				int d = j-1;
				c[d--] += 10;//��λ��λ�ɹ�
				while(1)
				{
					c[d] -= 1;
					if(c[d] < '0')
					{						
						c[d--] += 10;//��λ��λ�ɹ�
					}
					else
						break;
				}
			}
			
			//==========================
			//����������β��
			//==========================
			strcat(c, tmp);
			//delete[]tmp;
			//delete[]tmp2;
			//delete[]tmp3;
		}
			
	}
	else
	{
		//===================================
		//a��b ������С��
		//===================================
		int alength = 0 , blength = 0;//a��b�ַ������ܳ���
		while(a[alength] != '\0')alength++;
		while(b[blength] != '\0')blength++;
		int ax = alength - 1 - i;//aС���������ַ�����
		int bx = blength - 1 - j;//bС���������ַ�����		
		//cout<<my_strcmp(a,b,0,i,0,j);//�Ƚ�a��b�������ִ�С
		if( i==j && (strcmp(a,b) == 0)) //a��b���
		{
			c[0] = '0';
			c[1] = '\0';
			return c;
		}
		//=============================================================================================
		//��һ�����Σ�a���������ִ��ڵ���b�������֣���a > b,ͬʱa��С�����ֶ���b��С�����֣�ͼʾ���Σ�5��
		//=============================================================================================
		if((i > j ||( i==j && (strcmp(a,b) > 0))) && ax <= bx)
		{
			sign = 1;
			int clength = i + 1 + bx;//i+1��a���������ְ���С����ĳ���
			char *tmp = new char[512];//��С�ɵ�
			char *tmp2 = new char[512];//��С�ɵ�������a�����油0
			char *tmp3 = new char[512];//��С�ɵ�������b
			////����С���㡾�ɡ�
			//int k = 0;
			//for(int d = 0; a[d] != '\0'; d++)
			//{
			//	if( a[d] == '.')continue;
			//	tmp2[k] = a[d];
			//	k++;
			//}
			//int count = bx - ax;//aĩβ��0��
			//while(count > 0)
			//{
			//	tmp2[k++] = '0';
			//	count--;
			//}
			//int tmp2len = k;//��¼tmp2����
			//tmp2[k] = '\0';
			//k = 0;
			//for(int d = 0; b[d] != '\0'; d++)
			//{
			//	if( b[d] == '.')continue;
			//	tmp3[k] = b[d];
			//	k++;
			//}
			//tmp3[k] = '\0';

			//����С���㡾�¡�
			removeDot(tmp2,a);			
			removeDot(tmp3,b);
			int tmp2len = strlen(tmp2);		
			int count = bx - ax;//aĩβ��0��
			while(count > 0)
			{
				tmp2[tmp2len++] = '0';
				count--;
			}
			tmp2[tmp2len] = '\0';
			integerSub(tmp,tmp2,tmp3,tmp2len,tmp2len,strlen(tmp3),0);
			
			//����С����
			int d = tmp2len;
			for(; d > i; d--)
			{
				tmp[d] = tmp[d-1];
			}
			tmp[d--] = '.';
			tmp[tmp2len + 1] = '\0';
			strcpy(c,tmp);
			delete[]tmp;
			delete[]tmp2;
			delete[]tmp3;
		}
		//=============================================================================================
		//�ڶ������Σ�b���������ִ��ڵ���a�������֣�a < b��ͬʱa��С�����ֶ���b��С�����֣�ͼʾ���Σ�6��
		//=============================================================================================
		if((i < j ||( i==j && (strcmp(a,b) < 0))) && ax<=bx)
		{
			sign = -1;
			int clength = blength;
			char *tmp = new char[512];//��С�ɵ�
			char *tmp2 = new char[512];//��С�ɵ�������a
			char *tmp3 = new char[512];//��С�ɵ�������b�����油0
			removeDot(tmp2,b);			
			removeDot(tmp3,a);
			int tmp3len = strlen(tmp3);	//ȥС�����ĳ���
			int count = bx - ax;
			while(count > 0)
			{
				tmp3[tmp3len++] = '0';
				count--;
			}
			tmp3[tmp3len] = '\0';
			integerSub(tmp,tmp2,tmp3,strlen(tmp2),strlen(tmp2),tmp3len,0);
			//����С����
			int d = strlen(tmp2);
			for(; d > j; d--)
			{
				tmp[d] = tmp[d-1];
			}
			tmp[d--] = '.';
			tmp[strlen(tmp2) + 1] = '\0';
			strcpy(c,tmp);
			
			delete[]tmp;
			delete[]tmp2;
			delete[]tmp3;
		}
		//=============================================================================================
		//���������Σ�a���������ִ��ڵ���b�������֣�a > b��ͬʱa��С�����ֳ���b��С�����֣�ͼʾ���Σ�7��
		//=============================================================================================
		if((i > j ||( i==j && (strcmp(a,b) > 0))) && ax>=bx)
		{
			sign = 1;
			int clength = alength;
			char *tmp = new char[512];//��С�ɵ�
			char *tmp2 = new char[512];//��С�ɵ�������a
			char *tmp3 = new char[512];//��С�ɵ�������b�����油0
			removeDot(tmp2,a);			
			removeDot(tmp3,b);
			int tmp3len = strlen(tmp3);	//ȥС�����ĳ���
			int count = ax - bx;
			while(count > 0)
			{
				tmp3[tmp3len++] = '0';
				count--;
			}
			tmp3[tmp3len] = '\0';
			integerSub(tmp,tmp2,tmp3,strlen(tmp2),strlen(tmp2),tmp3len,0);
			//����С����
			int d = strlen(tmp2);
			for(; d > i; d--)
			{
				tmp[d] = tmp[d-1];
			}
			tmp[d--] = '.';
			tmp[strlen(tmp2) + 1] = '\0';
			strcpy(c,tmp);
			
			delete[]tmp;
			delete[]tmp2;
			delete[]tmp3;
		}
		//=============================================================================================
		//���������Σ�b���������ִ��ڵ���a�������֣�a < b��ͬʱa��С�����ֳ���b��С�����֣�ͼʾ���Σ�8��
		//=============================================================================================
		if((i < j ||( i==j && (strcmp(a,b) < 0))) && ax>=bx)
		{
			sign = -1;
			int clength = j + 1 + ax;//i+1��a���������ְ���С����ĳ���
			char *tmp = new char[512];//��С�ɵ�
			char *tmp2 = new char[512];//��С�ɵ�������b�����油0
			char *tmp3 = new char[512];//��С�ɵ�������a
			removeDot(tmp2,b);			
			removeDot(tmp3,a);
			int tmp2len = strlen(tmp2);		
			int count = ax - bx;//bĩβ��0��
			while(count > 0)
			{
				tmp2[tmp2len++] = '0';
				count--;
			}
			tmp2[tmp2len] = '\0';
			
			integerSub(tmp,tmp2,tmp3,tmp2len,tmp2len,strlen(tmp3),0);
			cout<<tmp<<endl;
			//����С����
			int d = tmp2len;
			for(; d > i; d--)
			{
				tmp[d] = tmp[d-1];
			}
			tmp[d--] = '.';
			tmp[tmp2len + 1] = '\0';
			strcpy(c,tmp);
			delete[]tmp;
			delete[]tmp2;
			delete[]tmp3;
		}
	}


	jumpZero(c);
	
	return c;
}

//
//void *__CRTDECL operator new(size_t) /*_THROW1(std::bad_alloc)*/;
//
//void * operator new[]( size_t cb )
//{
//    void *res = operator new(cb);
//
//    RTCCALLBACK(_RTC_Allocate_hook, (res, cb, 0));
//
//    return res;
//}
