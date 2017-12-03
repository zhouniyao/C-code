/*
������������������
���ߣ�������       ���ʱ�䣺2010.7.5
������
��Ҫ�����б�
      1.show()     ��ʾ��ǰ�������������
	  2.exchange() ���������е� begin[row_one][column_one] �� begin[row_two][column_two] ��������
	  3.judge()    �жϴ��������������������������ȷλ������ĸ���
      4.yidong()   ������������ӿ�ʼλ���ƶ�����ֹλ�ã�������������
	  5.shuru()    ���û����������������������״̬��������������뵽begin[][]������
����˵�����˳������õ�����ʽ�����Ĳ��ԣ�
          ��1�������ո�ĵط��洢�㣬�������ڲ���
		  ��2����ÿ�ν���0��������4������Ԫ�ص�λ�ã�������λ�ú���ȷ������� ���ڻ���� ����ǰ��ȷ����ĸ������㽻���ɹ���
		         �����ɹ����ظ�����2��ʧ�ܵĻ���������һ�ֽ�����
		  ��3�������������������е������λ�ö���ȷʱ����
*/

#include"stdio.h"
#define num 3 //�궨�������������Ϊ3

/*��ʾ��ǰ�������������*/
void show(int begin[num][num])  
{
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
			printf("%d ", begin[i][j]);
		printf("\n");
	}
	printf("\n");
}

/*���������е� begin[row_one][column_one] �� begin[row_two][column_two] ��������*/
void exchange(int begin[num][num], int row_one, int column_one, int row_two, int column_two)  
{
	int temp;
	temp = begin[row_two][column_two] ;
	begin[row_two][column_two] = begin[row_one][column_one];
	begin[row_one][column_one] = temp;
}

/*�жϴ��������������������������ȷλ������ĸ���*/
int judge(int begin[num][num], int end[num][num]) 
{
	int count=0;           //count��¼��������ȷλ�õĸ���
	for(int i = 0; i < num; i++)   //��鵱ǰͼ�ε���ȷ��
		for(int j = 0; j < num; j++)
		{
			if(begin[i][j] == end[i][j] && end[i][j] != 0)
				count++;
		}
	return count;           //������������ȷλ�õĸ���
}
 
/* ������������ӿ�ʼλ���ƶ�����ֹλ�ã�������������*/
int yidong(int begin[num][num], int end[num][num]
		   , int right, int jishu, int ji_shu[50][3][3]  //right ��ȷƥ�Ե���right<=8
		   , int biaoji, int row, int column) //biaoji�洢��һ���ƶ��ķ��������
{ 
	int temp_zhi;
	show(begin);   //��ʾ�������
	if(jishu >= 20)
		return 0;
	int node;  //,nodeΪ���
	int temp;               //�洢��ǰ������������ȷ�ĸ���
    for(int q=0; q<jishu; q++)  //��齻�����end[][]ͼ���Ƿ���ǰ�Ѿ���������
	{
		node = 1;
		for(int w=0; w<num && node; w++)
			for(int r=0; r<num && node; r++)
				if(ji_shu[q][w][r] != begin[w][r])  //shu[][][]��ά�����¼�����С��п��ܵġ��������Ľڵ�
					node = 0;
		if(node == 1)   //�����ǰ������������0
		{
	    	return 0;
		}
	}
	for(int i = 0; i < num; i++)   
		for(int j = 0; j < num; j++)
			ji_shu[jishu][i][j] = begin[i][j];//���һ���ڵ�¼��begin[][]
	
	if(right == num * num - 1)  //�������������������������ȫ��ͬʱ������1
		return 1;
	if(row > 0 && biaoji != 0)             //�洢0��λ�ò����ڵ�һ��
	{
		exchange(begin, row - 1, column, row , column);  //��0���������Ԫ�ؽ����洢λ��
		temp = judge(begin, end);
	    if(temp < right)   //�����������ȷ����ĸ���������ԭ����ȷ����ĸ���
	    	exchange(begin, row - 1, column, row , column); //�ٽ��佻������		
		else if(temp >= right)          //�����������ȷ����ĸ������ڻ����ԭ����ȷ����ĸ���
		{
			temp_zhi = yidong(begin, end, temp, jishu+1, ji_shu, 2, row-1, column);
     		if( temp_zhi == 1)  //������һ�����ƶ�
	     	    return 1;
			exchange(begin, row - 1, column, row , column); //�ٽ��佻������
		}
	}
	if(column > 0 && biaoji != 1)
	{
	   	exchange(begin, row, column - 1, row , column); //��0������ߵ�Ԫ�ؽ����洢λ��
		temp = judge(begin, end);		
		if(temp < right)   
   		   exchange(begin, row, column - 1, row , column);			
		else if(temp >= right)
		{
			temp_zhi = yidong(begin, end, temp, jishu+1, ji_shu ,3, row, column - 1);
		    if(temp_zhi == 1)  
                 return 1;
			exchange(begin, row, column - 1, row , column);
		}
	}

	if(row < num-1 && biaoji != 2)
	{
	    exchange(begin, row + 1, column, row , column); //��0���������Ԫ�ؽ����洢λ��
		temp = judge(begin, end);	
		if(temp < right) 
			exchange(begin, row + 1, column, row , column);
		else if(temp >= right)
		{
			temp_zhi =yidong(begin, end, temp, jishu+1, ji_shu, 0, row+1, column);
		   if(temp_zhi == 1)  
		      return 1;
		   exchange(begin, row + 1, column, row , column);
		}
	}
	if(column < num-1 && biaoji != 3)
	{
	    exchange(begin, row, column + 1, row , column); //��0�����ұߵ�Ԫ�ؽ����洢λ��
		temp = judge(begin, end);	
		if(temp < right)   
		    exchange(begin, row, column + 1, row , column);		
	    else if(temp >= right)  
		{
			temp_zhi = yidong(begin, end, temp, jishu+1, ji_shu, 1, row, column+1);
			if(temp_zhi == 1)  
		       return 1;
			exchange(begin, row, column + 1, row , column);	
		}
	}
	return 0;   //�ƶ�ʧ�ܣ�����0
}

/*���û����������������������״̬��������������뵽begin[][]������*/
void shuru(int begin[][num],int blank[])  
{	int temp, node, zero = 0;
	for (int i = 0; i < num; i++)
		for(int j = 0; j < num; j++)
		{
			node = 1;
			printf("�������%d�У���%d�е�Ԫ�ص�ֵ��", i+1, j+1);
		    scanf("%d", &temp);
			for (int q = 0; q <= i && node == 1; q++)  //�������ֵ���ظ��ģ���ʾ��������
				for (int w = 0; w < j; w++)
					if(temp == begin[q][w])
					{
						printf("�����ظ�������������\n");
						node = 0;
						j--;
						break;
					}
			if(temp < 0 || temp > num*num-1)   //�������ֵ��������������䷶Χ��ʱ����ʾ��������
			{
				printf("�������%d��%d����\n", zero, num*num-1);
				node = 0;
			    j--;
			}
			if(node == 1)   //���������������	
			{
				if(temp == 0) //��������ֵΪ�㣬��blank[0]��¼�кţ�blank[1]��¼�к�
				{
					blank[0] = i;
					blank[1] = j;
				}
				begin[i][j] = temp;//������������ֵ�洢����
			}
		}
}

int main()
{
	int jishu = 0, ji_shu[50][3][3];//jishu�洢�Ѿ��������İ�����ͼ�εĸ�����jishu[][][]�洢�Ѿ��������İ�����ͼ�ε���״
    int row;     //�洢�����������
    int column;  //�洢�����������
	int begin[num][num], blank[2],count=1; 	
	int end[num][num] = {1, 2, 3, 8, 0, 4, 7, 6, 5};  //������״̬���������ֵ
    printf ("-------%d������Ϸ��ʼ��--------\n", num);
    shuru(begin, blank);   //���������״̬����������ֵ
	row = blank[0];
	column = blank[1];
	if(yidong (begin, end,judge(begin,end),jishu,ji_shu,4,row,column) == 0)  
	   printf("\n��8�������������޽⣡");
	else 
	   show(begin);
	getchar();getchar();
	return 0;
}