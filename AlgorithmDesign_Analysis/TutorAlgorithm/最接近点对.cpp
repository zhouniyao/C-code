#include<iostream>
#include<cmath>
using namespace std;



class PointX{    //��X��Ϊ����ĵ㼯
private:
	float x,y;
	int ID;
public:
	int operator<=(PointX a)const{return(x<=a.x);}
};

class PointY{    //��Y��Ϊ����ĵ㼯
private:
	float x,y;
	int p;
public:
	int operator<=(PointY a)const{return(y<=a.y);}
};
//============================================================
//�����������
//============================================================
template<typename T>
float distance(const T&u,const T&v)
{
	float x=u.x-v.x;
	float y=u.y-v.y;
	return (sqrt(x*x+y*y));
}
//============================================================
//X[l:r]���Ա���㼯��a��bΪ�����ҵ�һ����ӽ���ԣ�dΪ������
//============================================================
bool Cpair2(PointX X[],int n,PointX &a,PointX &b,float &d)
{
	if(n<2)return false;
	MergeSort(X,0,n-1);  //��X�᷽�����е㼯
	PointY *Y=new PointY[n];
	for(int i=0;i<n;i++)//��X[l:r]�㼯һһ���Ƶ�Y[l:r]
	{
		Y[i].p=i;       //��¼��ӦX[]���к�,����Ӧ��X�᷽��Ϊ��Ĵ���
		Y[i].x=X[i].x;
		Y[i].y=X[i].y;
	}
	MergeSort(Y,0,n-1); //��Y�᷽�����е㼯
	PointY *Z=new PointY[n];
	closest(X,Y,Z,0,n-1,a,b,d);//������ӽ����
	delete[] Y;
	delete[] Z;
	return true;

}
//============================================================
//������ӽ����
//============================================================
void closest(PointX X[],PointY Y[],PointY Z[],int l,int r,PointX &a,PointX &b,float &d)//lΪ����˵㣬rΪ���Ҷ˵�
{
	if(r-l==1){a=X[l];b=X[r];d=distance(a,b);return;}//2������
	if(r-l==2)//3������
	{
		d=distance(X[l],X[l+1]);
		float temp=distance(X[l],X[r]);
		if(d>temp)d=temp;
		temp=distance(X[l+1],X[r]);
		if(d>temp)d=temp;
	}
	
	int m=(l+r)/2;//ȡX���ϵķָ��
	/*

	*/
	int f=l,g=m+1;
	for(int i=l;i<=r;i++)
	{
		if(Y[i].p>m)Z[g++]=Y[i];
		else Z[f++]=Y[i];
	}

	
	closest(X,Y,Z,l,m,a,b,d);
	float d2;
	PointX a2,b2;
	closest(X,Y,Z,m+1,r,a2,b2,d2);
	if(d>d2)
	{
		a=a2;
		b=b2;
		d=d2;
	}
	Merge(Z,Y,l,m,r);//�ع�����Y
	//d�������ڵĵ�����Z��
	int k=l;
	for(int i =l;i<=r;i++)
		if(fabs(Y[m].x-Y[i].x)<d)Z[k++]=Y[i];
	//����Z[l:k-1]
	for(int i=l;i<k;i++)
	{
		for(int j=i+1;j<k&&Z[j].y-Z[i].y<d;j++)
		{
			float dp=distance(Z[i],Z[j]);
			if(dp<d){d=dp;a=X[Z[i].p];b=X[Z[j].p];}
		}
	}


	/*
	for(int i=l;i<=m;i++)//�ռ�S1��������Lֱ�ߣ�x=X[m]�������С��dl�ĵ�
	{
		int k=0;
		if(abs(X[i].x-X[m].x)<dl)Z[k++]=X[i];

	}
	int record=k-1;//��¼S1��S2�ķֽ�

		for(int i=m+1;i<=r;i++)//�ռ�S2��������Lֱ�ߣ�x=X[m]�������С��dl�ĵ�
	{
		
		if(abs(X[i].x-X[m].x)<dl)Z[k++]=X[i];

	}
	Mergesort(Z,0,record);//ǰ�����Y�᷽������	
	Mergesort(Z,record+1��k-1); 
	ss//������Y�᷽������

	*/
}
//============================================================
//������ɵ㼯
//============================================================
void Random(PointX& X)
{
	
}