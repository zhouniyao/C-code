#include <stdio.h>
#include <conio.h>

#define n 8

void Table(int i, int j, int a[][n]) //�ӵ�i�е���j��
{
	int p,q,k=(j-i)/2;
	if(i==j)
	{
		a[i][0] = i+1;
		return;
	}
	

	Table(i, (i+j)/2, a);
	for(p=i; p<=(i+j)/2; p++)  //����->����
		for(q=0; q<=k; q++)
			a[p+k+1][q+k+1] = a[p][q];

	Table((i+j)/2+1, j, a);
	for(p=(i+j)/2+1; p<=j; p++) //����->����
		for(q=0; q<=k; q++)
			a[p-k-1][q+k+1] = a[p][q];

}

void main()
{
	int a[n][n];

	Table(0,n-1,a);
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
			printf("%3d", a[i][j]);
		printf("\n");
	}
	printf("\n");
}
