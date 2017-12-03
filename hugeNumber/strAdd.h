#include<iostream>
using namespace std;

extern void jumpZero(char * nptr);
extern int findDot(const char *nptr);//����С����λ



//��ֵ���ַ�result�ۼ�dst�����������result��
char *integerAdd(char *result,const char * dst,int d1,int d2)//result����Ϊ d1,dst����Ϊ d2����d1>=d2��
{
	d1--,d2--;
	int flag = 0;
	while(d2 >= 0)
	{
		result[d1] += (dst[d2] - '0');
		if(flag)result[d1] += 1;
		if(result[d1] > '9')
		{
			flag = 1;
			result[d1] -= 10;
		}
		else
			flag = 0;
		d1--,d2--;
	}
	while(flag)
	{
		result[d1] += 1;
		if(result[d1] > '9')
		{
			flag = 1;
			result[d1] -= 10;
		}
		else
			flag = 0;
		d1--;//result�㹻��������������˺����
	}
	
	return result;
}


//�����ַ����������
void integerAdd(char *c,const char *a,const char *b,int k,int i,int j,int flag)//a��b��û��С����kΪc���鳤�ȣ�iΪa���鳤�ȡ���flag���޽�λ
{
	int clength = k;//c���鳤��
	c[k] = '\0';
	k--;i--;j--;
	while(j >= 0 && i >= 0)
	{
		c[k] = a[i] + (b[j] - '0');
		if(flag)c[k] += 1;
		if(c[k] > '9')
		{
			flag = 1;
			c[k] -= 10;
		}
		else
			flag = 0;
		k--;i--;j--;
	}
	while(j >= 0)
	{
		c[k] = b[j];
		if(flag)c[k] += 1;
		if(c[k] > '9')
		{
			flag = 1;
			c[k] -= 10;
		}
		else
			flag = 0;
		k--;j--;
	}
	while(i >= 0)
	{
		c[k] = a[i];
		if(flag)c[k] += 1;
		if(c[k] > '9')
		{
			flag = 1;
			c[k] -= 10;
		}
		else
			flag = 0;
		k--;i--;
	}
	if(flag)
	{
		//cout<<"k = "<<k<<endl;
		c[k] = '1';
		
	}
	else
	{//û�н�λ
		c[k] = '0';
		
	}
		
			
	
}

//��ֵ���ַ������
char * strAdd(char *c , const char *a, const char *b)  //c = a + b
{
	int i = findDot(a);//β��aС����λ
	int j = findDot(b);//β��bС����λ
	int k ;
	int flag = 0;
	//==============================================
	//a��b ��Ϊ��������С����
	//==============================================
	if(i == -1 && j == -1)
	{	
		i++;j++;
		while(a[i] != '\0')i++;
		while(b[j] != '\0')j++;
		//��ʱ b[j] == '\0'
		i--;j--;
		k =( (j>=i)? j : i) + 1;//���ǽ�λ
		int clength = k;//c���鳤��
		while(j >= 0 && i >= 0)
		{
			
			c[k] = a[i] + (b[j] - '0');
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;i--;j--;
		}
		while(j >= 0)
		{
			c[k] = b[j];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;j--;
		}
		while(i >= 0)
		{
			c[k] = a[i];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;i--;
		}
		if(flag)
		{
			//cout<<"k = "<<k<<endl;
			c[k] = '1';
			c[clength + 1] = '\0';
		}
		else
		{//�ų���λ�ո񲢼ӽ�����
			int i = 0;
			for(; i < clength; i++ )
			{
				c[i] = c[i+1];//��������Ԫ��ǰ��һλ
			}
			c[i] = '\0';
		}
		
			//return c;
	}
	//==================================================
	//a��b ��һ����С��
	//==================================================
	else if(i == -1 && j > 0)
	{
		
		i++;
		while(a[i] != '\0')i++;//a�ַ����鳤��
		int bx = j + 1;//b����С�����һλ��λ��
		int cx ;
		j--;i--;//�����������һλ
		k =( (j>=i)? j : i) + 1;//���ǽ�λ��k��һλ
		//c[k + 1] = '.';//��¼С����
		int clen1 = k;//c�����������ֳ��ȡ��ݶ���
		
		while(j >=0 && i >= 0)
		{
			c[k] = a[i] + (b[j] - '0');
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;

			}
			k--;j--;i--;
		}
		while(j >= 0)
		{
			c[k] = b[j];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;j--;
			
		}

		while(i >= 0)
		{
			c[k] = a[i];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;i--;
		}
		if(flag)
		{
			//cout<<"k1 = "<<k<<endl;
			c[k] = '1';
			c[clen1+1] = '.';
			cx = clen1 + 2;
		}
		else
		{//�ų���λ�ո񲢼ӽ�����
			int i = 0;
			for(; i < clen1; i++ )
			{
				c[i] = c[i+1];//��������Ԫ��ǰ��һλ
			}
			c[i] = '.';
			cx = i + 1;
		}
				
		//===================================
		//����С��
		//===================================
		while(b[bx] != '\0')
			c[cx++] = b[bx++];
		c[cx] = '\0';//cxΪ���ַ����顾�ܡ�����
	
		//return c;
		
	}
//��һ�����
	else if(j == -1 && i >0)
	{
		j++;
		while(b[j] != '\0')j++;//b�����������b�ַ����鳤��
		int ax = i + 1;//��ʶb����С�����һλ��λ��
		int cx ;
		j--;i--;//�����������һλ
		k =( (j>=i)? j : i) + 1;//���ǽ�λ��k��һλ
		//c[k + 1] = '.';//��¼С����
		int clen1 = k;//c�����������ֳ��ȡ��ݶ���
		
		while(j >=0 && i >= 0)
		{
			c[k] = a[i] + (b[j] - '0');
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;

			}
			k--;j--;i--;
		}
		while(j >= 0)
		{
			c[k] = b[j];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;j--;
			
		}

		while(i >= 0)
		{
			c[k] = a[i];
			if(flag)c[k] += 1;
			if(c[k] > '9')
			{
				flag = 1;
				c[k] -= 10;
			}
			else
				flag = 0;
			k--;i--; 
		}

		if(flag)
		{
			//cout<<"k2 = "<<k<<endl;
			c[k] = '1';
			c[clen1+1] = '.';
			cx = clen1 + 2;
		}
		else
		{//�ų���λ�ո񲢼ӽ�����
			int i = 0;
			for(; i < clen1; i++ )
			{
				c[i] = c[i+1];//��������Ԫ��ǰ��һλ
			}
			c[i] = '.';
			cx = i + 1;
		}
				
		//===================================
		//����С��
		//===================================
		while(a[ax] != '\0')
			c[cx++] = a[ax++];
		c[cx] = '\0';//cxΪ���ַ����顾�ܡ�����
	
		//return c;

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
		int bx = blength -1 - j;//bС���������ַ�����
		//cout<<"ax= "<<ax<<endl;
		//cout<<"bx= "<<bx<<endl;
		int clength = (ax >= bx ? ax : bx) + (i >= j ? i : j) + 2;//c�ַ������ܳ��ȣ�����С����λ��һ������λ
		int k = (i >= j ? i : j) + 1;//c�ַ�����С����λ��Ԥ������λ
		
		int cdot = k;//c�ַ�����С����λ
		c[clength] = '\0';//����������
		int w = 1 ;
		while(ax < bx)//aС������С��b
		{
			c[clength - w] = b[blength - w];
			w++;bx--;
		}		
		while(ax > bx)
		{
			c[clength - w] = a[alength - w];
			w++;ax--;			
		}	
		//cout<<ax<<bx;//���������
		while(bx > 0)//a��b�ַ�����С������һ��ʱ
		{
			//c[clength - w] = a[ax+i] +(b[bx+j] - '0');//�����һ����Чλ��ʼ��ǰ�ۼ�
			c[clength - w] = b[bx+j] +(a[ax+i] - '0');
			if(flag)c[clength - w] += 1;
			if(c[clength - w] > '9')//ת���ɽ�λ
			{
				flag = 1;
				c[clength - w] -= 10;
			}
			else
			{
				flag = 0;
			}
			ax--;bx--;w++;
		}
	

	
		//cout<<clength - w<<endl;//�����ǲ�����������������ַ������С����λ + 1
		//cout<<i<<"    "<<j<<endl;
		
		//���������ۼ�
		
		integerAdd(c,a,b,k,i,j,flag);
		//�ۼӵ�С������
		c[cdot] = '.';
		//c[k] = '.';
		//if(c[0] == '0' && c[1] != '.')//�ų���λ����0
		//{
		//	int i = 0;
		//	for(;c[i] != '\0'; i++)
		//		c[i] = c[i++];
		//	c[i] = '\0';//���c�ַ��������
		//}
	}
	//==========================
	//ȥ����ǰ����Ч0
	//==========================
	jumpZero(c);
	return c;
}

