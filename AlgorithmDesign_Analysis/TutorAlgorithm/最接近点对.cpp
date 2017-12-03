#include<iostream>
#include<cmath>
using namespace std;



class PointX{    //以X轴为主轴的点集
private:
	float x,y;
	int ID;
public:
	int operator<=(PointX a)const{return(x<=a.x);}
};

class PointY{    //以Y轴为主轴的点集
private:
	float x,y;
	int p;
public:
	int operator<=(PointY a)const{return(y<=a.y);}
};
//============================================================
//计算两点距离
//============================================================
template<typename T>
float distance(const T&u,const T&v)
{
	float x=u.x-v.x;
	float y=u.y-v.y;
	return (sqrt(x*x+y*y));
}
//============================================================
//X[l:r]用以保存点集，a、b为待查找的一对最接近点对，d为最近点距
//============================================================
bool Cpair2(PointX X[],int n,PointX &a,PointX &b,float &d)
{
	if(n<2)return false;
	MergeSort(X,0,n-1);  //按X轴方向排列点集
	PointY *Y=new PointY[n];
	for(int i=0;i<n;i++)//将X[l:r]点集一一复制到Y[l:r]
	{
		Y[i].p=i;       //记录对应X[]序列号,即对应以X轴方向为序的次序。
		Y[i].x=X[i].x;
		Y[i].y=X[i].y;
	}
	MergeSort(Y,0,n-1); //按Y轴方向排列点集
	PointY *Z=new PointY[n];
	closest(X,Y,Z,0,n-1,a,b,d);//查找最接近点对
	delete[] Y;
	delete[] Z;
	return true;

}
//============================================================
//查找最接近点对
//============================================================
void closest(PointX X[],PointY Y[],PointY Z[],int l,int r,PointX &a,PointX &b,float &d)//l为最左端点，r为最右端点
{
	if(r-l==1){a=X[l];b=X[r];d=distance(a,b);return;}//2点情形
	if(r-l==2)//3点情形
	{
		d=distance(X[l],X[l+1]);
		float temp=distance(X[l],X[r]);
		if(d>temp)d=temp;
		temp=distance(X[l+1],X[r]);
		if(d>temp)d=temp;
	}
	
	int m=(l+r)/2;//取X轴上的分割点
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
	Merge(Z,Y,l,m,r);//重构数组Y
	//d矩形条内的点置于Z中
	int k=l;
	for(int i =l;i<=r;i++)
		if(fabs(Y[m].x-Y[i].x)<d)Z[k++]=Y[i];
	//搜索Z[l:k-1]
	for(int i=l;i<k;i++)
	{
		for(int j=i+1;j<k&&Z[j].y-Z[i].y<d;j++)
		{
			float dp=distance(Z[i],Z[j]);
			if(dp<d){d=dp;a=X[Z[i].p];b=X[Z[j].p];}
		}
	}


	/*
	for(int i=l;i<=m;i++)//收集S1中所有在L直线（x=X[m]）间距离小于dl的点
	{
		int k=0;
		if(abs(X[i].x-X[m].x)<dl)Z[k++]=X[i];

	}
	int record=k-1;//记录S1与S2的分界

		for(int i=m+1;i<=r;i++)//收集S2中所有在L直线（x=X[m]）间距离小于dl的点
	{
		
		if(abs(X[i].x-X[m].x)<dl)Z[k++]=X[i];

	}
	Mergesort(Z,0,record);//前半段以Y轴方向排序	
	Mergesort(Z,record+1，k-1); 
	ss//后半段以Y轴方向排序

	*/
}
//============================================================
//随机生成点集
//============================================================
void Random(PointX& X)
{
	
}