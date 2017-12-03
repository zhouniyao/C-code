#if 0


/*
*N�ʺ�����CUDA����ͳ�Ĵ����㷨����äĿ��٣����л�
*
*
*/
#include "E:\VisualStudio\CUDA\common\book.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

#define MAXSIZE 100
//int (*Queen)[N] = new int[INT_MAX/100][N];
//int (*Queen)[N] = (int (*)[N])malloc(MAXSIZE*N*sizeof(int));

//��ʼ����ά����
__device__ void InitMatrix(int L[][N])
{
	int i,j;
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			L[i][j] = 0;
}
//�����ס������ϵĸ�
__device__ void Mi(int L[][N], int row, int col)
{
	int i,j;
	for(i=0; i<N; i++)
	{
		L[row][i] = -1;//ͬ��
		L[i][col] = -1;//ͬ��
	}
	//��б��	//��б��
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			if((i-row == col-j)||(i-row == j-col))
				L[i][j] = -1;
}
//�Ϸ����жϡ�����rowĳ������֮ǰ�����бȽϣ�Q[]�洢֮ǰ�кϷ���λ��
__device__ int isLegal(int L[], int row, int pos )
{
	for(int i=0; i<row; i++)
	{
		if(L[i] == -1)return 0;
		if(pos == L[i])return 0;
		if(L[i] - pos == i - row)return 0;//���Խ���
		if(L[i] - pos == row - i)return 0;//б�Խ���
	}
	
	return 1;
}
//int isLegal(int Q[], int row, int col)
//{
//	int i;
//	if(row == 0)return 1;
//	for(i=0; i<row; i++)
//		if(col==Q[i] || col-i == row-Q[i] || i-col == row-Q[i])
//			return 0;
//	return 1;
//	
//}
//��������_������н�����ά����ĳ��
//__device__ void saveQueen(int Queen[][N], int cnt, int L[])
//{	
//	for(int i=0; i<N; i++)
//		Queen[cnt][i] = L[i];	
//}
__device__ static int myCount = 0;//ͳ�ƽ������û����

//�̶�һ�����Ӻ󣬲��Ҹ�״̬�µ����п��ܣ����ؽ����
/***************************************** 4�ʺ�*****************************************/
//__device__ int findQueen4(int row, int col)//rowΪ0��colΪthreadIdx
//{
//	//int i,j,flag;
//	//int L[N][N];
//	//int temp[N];
//	///*���̳�ʼ��*/
//	////��б��	//��б��
//	//for(i=0; i<N; i++)
//	//	for(j=0; j<N; j++)
//	//		if((i-row == col-j)||(i-row == j-col))
//	//			L[i][j] = -1;
//	//		else
//	//			L[i][j]=0;
//
//	//for(i=0; i<N; i++)
//	//{
//	//	L[row][i] = -1;//ͬ��
//	//	L[i][col] = -1;//ͬ��
//	//}
//	int cnt = 0;
//	int L[N] = {0};
//	L[row] = col;
//	for(int i1=0; i1<N; i1++)/*��1��*/
//	{
//		//if(L[1][i1]==-1)continue;		
//		if(isLegal(L, 1, i1 ))
//		{
//			L[1] = i1;
//			for(int i2=0; i2<N; i2++)/*��2��*/
//			{
//				
//				//if(L[2][i2]==-1)continue;
//				
//				if(isLegal(L, 2, i2 ))
//				{
//					L[2] = i2;
//					for(int i3=0; i3<N; i3++)/*��3��*/
//					{
//						
//						//if(L[3][i3]==-1)continue;
//						if(isLegal(L, 3, i3 ))
//						{
//							L[3] = i3;
//							cnt++;
//							myCount++;
//						}
//			
//					}
//				}
//			}
//		}
//	}
//				
//	return cnt;
//}
__device__ int findQueen4(int row, int col)
{

	int  i,i0, i1, i2, i3;
	int cnt = 0;
	int Q[N] = {0};
	int L[N][N] = {0};
	//for(i=0; i<N; i++)
	//	Q[i] = 0;
	//InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(row==3)goto Layer4;
												else
													if(L[3][i3] != -1 && isLegal(Q, 3, i3))
													{
														Q[3] = i3;
		Layer4:											//����Ϊ���н�
														cnt++;
														//myCount++;
														//saveQueen(Queen,myCount,Q);
													}
										}
							}
			}	
	return cnt;
}
//***************************************** 5�ʺ�*****************************************/
__device__ int findQueen5(int row, int col)
{
	int L[N][N] = {0};
	int i,i0, i1, i2, i3, i4;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
																//����Ϊ���н�
																cnt++;
																//myCount++;
																//saveQueen(Queen,myCount,Q);
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 6�ʺ�*****************************************/
__device__ int findQueen6(int row, int col)
{
	int L[N][N] = {0};
	int i,i0, i1, i2, i3, i4, i5;
	int Q[N] = {0};
	int cnt = 0;

	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																			//����Ϊ���н�
																			cnt++;
																			//myCount++;
																			//saveQueen(Queen,myCount,Q);
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 7�ʺ�*****************************************/
__device__ int findQueen7(int row, int col )
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																					//����Ϊ���н�
																					cnt++;
																					//myCount++;
																					//saveQueen(Queen,myCount,Q);
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 8�ʺ�*****************************************/
__device__ int findQueen8(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																							//����Ϊ���н�
																							cnt++;
																							//myCount++;
																							//saveQueen(Queen,myCount,Q);
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
///***************************************** 9�ʺ�*****************************************/
__device__ int findQueen9(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8;
	int Q[N] = {0} ;
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								//����Ϊ���н�
																								cnt++;
																								//myCount++;
																								//saveQueen(Queen,myCount,Q);
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt ;
}
//***************************************** 10�ʺ�*****************************************/
__device__ int findQueen10(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										//����Ϊ���н�
																										cnt++;
																										//myCount++;
																										//saveQueen(Queen,myCount,Q);
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 11�ʺ�*****************************************/
__device__ int findQueen11(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*��10��*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												//����Ϊ���н�
																												cnt++;
																												//myCount++;
																												//saveQueen(Queen,myCount,Q);
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 12�ʺ�*****************************************/
__device__ int findQueen12(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*��10��*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*��11��*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														//����Ϊ���н�
																														cnt++;
																														//myCount++;
																														//saveQueen(Queen,myCount,Q);
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 13�ʺ�*****************************************/
__device__ int findQueen13(int row, int col )
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*��10��*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*��11��*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*��12��*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																//����Ϊ���н�
																																cnt++;
																																//myCount++;
																																//saveQueen(Queen,myCount,Q);
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 14�ʺ�*****************************************/
__device__ int findQueen14(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*��10��*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*��11��*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*��12��*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*��13��*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		//����Ϊ���н�
																																		cnt++;
																																		//myCount++;
																																		//saveQueen(Queen,myCount,Q);
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 15�ʺ�*****************************************/
//int findQueen15(int row, int col)
//{
//	int L[N][N], i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14;
//	int Q[N],count=-1;
//	for(i=0; i<N; i++)
//		Q[i] = 0;
//	InitMatrix(L);//��ʼ������
//	Mi(L, row, col);//�����ס������ϵĸ�
//	Q[row] = col;//��¼ָ������
//	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�
//
//		//for(i0=0; i0<N; i0++)/*��0��*/
//			if(row==0)goto Layer1;
//			else
//				if(L[0][i0] != -1)//���ӿɷ�λ��
//				{
//					Q[0] = i0;
//
//		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
//						if(row==1)goto Layer2;
//						else
//							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
//							{
//								Q[1] = i1;
//
//		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
//									if(row==2)goto Layer3;
//									else
//										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
//										{
//											Q[2] = i2;
//
//		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
//												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
//												{
//													Q[3] = i3;
//													for(i4=0; i4<N; i4++)/*��4��*/
//													{
//														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
//														{
//															Q[4] = i4;
//															for(i5=0; i5<N; i5++)/*��5��*/
//															{																
//																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
//																	{
//																		Q[5] = i5;
//																		for(i6=0; i6<N; i6++)/*��6��*/
//																		{
//																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
//																			{
//																				Q[6] = i6;
//																				for(i7=0; i7<N; i7++)/*��7��*/
//																				{
//																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
//																					{
//																						Q[7] = i7;
//																						for(i8=0; i8<N; i8++)/*��8��*/
//																						{
//																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
//																							{
//																								Q[8] = i8;
//																								for(i9=0; i9<N; i9++)/*��9��*/
//																								{
//																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
//																									{
//																										Q[9] = i9;
//																										for(i10=0; i10<N; i10++)/*��10��*/
//																										{
//																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
//																											{
//																												Q[10] = i10;
//																												for(i11=0; i11<N; i11++)/*��11��*/
//																												{
//																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
//																													{
//																														Q[11] = i11;
//																														for(i12=0; i12<N; i12++)/*��12��*/
//																														{
//																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
//																															{
//																																Q[12] = i12;
//																																for(i13=0; i13<N; i13++)/*��13��*/
//																																{
//																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
//																																	{
//																																		Q[13] = i13;
//																																		for(i14=0; i14<N; i14++)/*��14��*/
//																																		{
//																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
//																																			{
//																																				Q[14] = i14;
//																																				//����Ϊ���н�
//																																				count++;
//																																				myCount++;
//																																				saveQueen(Queen,myCount,Q);
//																																			}
//																																		}
//																																	}
//																																}
//																															}
//																														}
//																													}
//																												}
//																											}
//																										}
//																									}
//																								}
//																							}
//																						}
//																					}
//																				}
//																			}
//																		}
//																	}
//															}
//														}
//													}
//												}
//										}
//							}
//			}	
//	return count+1;
//}
__device__ int findQueen15(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*��10��*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*��11��*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*��12��*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*��13��*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*��14��*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				//����Ϊ���н�
																																				cnt++;
																																				//myCount++;
																																				//saveQueen(Queen,myCount,Q);
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 16�ʺ�*****************************************/
__device__ int findQueen16(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*��10��*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*��11��*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*��12��*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*��13��*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*��14��*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				for(i15=0; i15<N; i15++)/*��15��*/
																																				{
																																					if(L[15][i15] != -1 && isLegal(Q, 15, i15))
																																					{
																																						Q[15] = i15;
																																						//����Ϊ���н�
																																						cnt++;
																																						//myCount++;
																																						//saveQueen(Queen,myCount,Q);
																																					}
																																				}
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt ;
}
//***************************************** 17�ʺ�*****************************************/
__device__ int findQueen17(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*��10��*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*��11��*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*��12��*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*��13��*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*��14��*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				for(i15=0; i15<N; i15++)/*��15��*/
																																				{
																																					if(L[15][i15] != -1 && isLegal(Q, 15, i15))
																																					{
																																						Q[15] = i15;
																																						for(i16=0; i16<N; i16++)/*��16��*/
																																						{
																																							if(L[16][i16] != -1 && isLegal(Q, 16, i16))
																																							{
																																								Q[16] = i16;
																																								//����Ϊ���н�
																																								cnt++;
																																								//myCount++;
																																								//saveQueen(Queen,myCount,Q);
																																							}
																																						}
																																					}
																																				}
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 18�ʺ�*****************************************/
__device__ int findQueen18(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*��10��*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*��11��*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*��12��*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*��13��*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*��14��*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				for(i15=0; i15<N; i15++)/*��15��*/
																																				{
																																					if(L[15][i15] != -1 && isLegal(Q, 15, i15))
																																					{
																																						Q[15] = i15;
																																						for(i16=0; i16<N; i16++)/*��16��*/
																																						{
																																							if(L[16][i16] != -1 && isLegal(Q, 16, i16))
																																							{
																																								Q[16] = i16;
																																								for(i17=0; i17<N; i17++)/*��17��*/
																																								{
																																									if(L[17][i17] != -1 && isLegal(Q, 17, i17))
																																									{
																																										Q[17] = i17;
																																										//����Ϊ���н�
																																										cnt++;
																																										//myCount++;
																																										//saveQueen(Queen,myCount,Q);
																																									}
																																								}
																																							}
																																						}
																																					}
																																				}
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt ;
}
//***************************************** 19�ʺ�*****************************************/
__device__ int findQueen19(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17, i18;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*��10��*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*��11��*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*��12��*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*��13��*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*��14��*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				for(i15=0; i15<N; i15++)/*��15��*/
																																				{
																																					if(L[15][i15] != -1 && isLegal(Q, 15, i15))
																																					{
																																						Q[15] = i15;
																																						for(i16=0; i16<N; i16++)/*��16��*/
																																						{
																																							if(L[16][i16] != -1 && isLegal(Q, 16, i16))
																																							{
																																								Q[16] = i16;
																																								for(i17=0; i17<N; i17++)/*��17��*/
																																								{
																																									if(L[17][i17] != -1 && isLegal(Q, 17, i17))
																																									{
																																										Q[17] = i17;
																																										for(i18=0; i18<N; i18++)/*��18��*/
																																										{
																																											if(L[18][i18] != -1 && isLegal(Q, 18, i18))
																																											{
																																												Q[18] = i18;
																																												//����Ϊ���н�
																																												cnt++;
																																												//myCount++;
																																												//saveQueen(Queen,myCount,Q);
																																											}
																																										}
																																									}
																																								}
																																							}
																																						}
																																					}
																																				}
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}
//***************************************** 20�ʺ�*****************************************/
__device__ int findQueen20(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17, i18, i19;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//��ʼ������
	Mi(L, row, col);//�����ס������ϵĸ�
	Q[row] = col;//��¼ָ������
	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�

		//for(i0=0; i0<N; i0++)/*��0��*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//���ӿɷ�λ��
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*��1��*/      /*����ѭ����ȴѭ����4�Σ��õ�4����ͬ���*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*��4��*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*��5��*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*��6��*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*��7��*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*��8��*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*��9��*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*��10��*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*��11��*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*��12��*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*��13��*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*��14��*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				for(i15=0; i15<N; i15++)/*��15��*/
																																				{
																																					if(L[15][i15] != -1 && isLegal(Q, 15, i15))
																																					{
																																						Q[15] = i15;
																																						for(i16=0; i16<N; i16++)/*��16��*/
																																						{
																																							if(L[16][i16] != -1 && isLegal(Q, 16, i16))
																																							{
																																								Q[16] = i16;
																																								for(i17=0; i17<N; i17++)/*��17��*/
																																								{
																																									if(L[17][i17] != -1 && isLegal(Q, 17, i17))
																																									{
																																										Q[17] = i17;
																																										for(i18=0; i18<N; i18++)/*��18��*/
																																										{
																																											if(L[18][i18] != -1 && isLegal(Q, 18, i18))
																																											{
																																												Q[18] = i18;
																																												for(i19=0; i19<N; i19++)/*��19��*/
																																												{
																																													if(L[19][i19] != -1 && isLegal(Q, 19, i19))
																																													{
																																														Q[19] = i19;
																																														//����Ϊ���н�
																																														cnt++;
																																														//myCount++;
																																														//saveQueen(Queen,myCount,Q);
																																													}
																																												}
																																											}
																																										}
																																									}
																																								}
																																							}
																																						}
																																					}
																																				}
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
															}
														}
													}
												}
										}
							}
			}	
	return cnt;
}

//��ӡ�ʺ�
void showQueen(int Queen[][N], int count)
{
	for(int i=0; i<=count; i++)
	{
		printf("��%d���⣺ ",i+1);
		for(int j=0; j<N; j++)
			printf("(%d,%d)",j,Queen[i][j]);
		printf("\n");
	}
}

//�������
__global__ void kernel4(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen4(0, i);
			
}
__global__ void kernel5(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen5(0, i);
			
}
__global__ void kernel6(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen6(0, i);
			
}
__global__ void kernel7(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen7(0, i);
			
}
__global__ void kernel8(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen8(0, i);
			
}
__global__ void kernel9(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen9(0, i);
			
}
__global__ void kernel10(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen10(0, i);
			
}
__global__ void kernel11(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen11(0, i);
			
}
__global__ void kernel12(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen12(0, i);
			
}
__global__ void kernel13(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen13(0, i);
			
}
__global__ void kernel14(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen14(0, i);
			
}
__global__ void kernel15(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen15(0, i);
			
}
__global__ void kernel16(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen16(0, i);
			
}
__global__ void kernel17(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen17(0, i);
			
}
__global__ void kernel18(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen18(0, i);
			
}
__global__ void kernel19(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen19(0, i);
			
}
__global__ void kernel20(int* dev_c)
{
	int i = blockIdx.x;
	//int i=threadIdx.x;
	if(i < N)
		*(dev_c+i) = findQueen20(0, i);
			
}
int main()
{
	LARGE_INTEGER t1,t2,tc,t3,t4;//����ʱ�����
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);//��ִ��ʱ��start
	int i=0,sum=0;
	//int* dev_row;
	//int* dev_col;
	//int count[N] = {0};
	int* count = (int*)malloc(N*sizeof(int));
	for(i=0; i<N; i++)
		*(count+i) = 0;
	int* dev_c;
	//HANDLE_ERROR(cudaMalloc((void**)&dev_row,sizeof(int)));//��
	//HANDLE_ERROR(cudaMalloc((void**)&dev_col,sizeof(int)));//��
	HANDLE_ERROR(cudaMalloc((void**)&dev_c,N*sizeof(int)));
    HANDLE_ERROR( cudaMemcpy(dev_c, count,
                              N*sizeof(int),
                              cudaMemcpyHostToDevice) );

	QueryPerformanceCounter(&t2);//�˺�����ʼʱ��
	switch(N)
	{
	case 4:
		//Allocate<<<1,N>>>(dev_c);
		kernel4<<<N,1>>>(dev_c);
		break;
	case 5:
		kernel5<<<N,1>>>(dev_c);
		break;
	case 6:
		kernel6<<<N,1>>>(dev_c);
		break;
	case 7:
		kernel7<<<N,1>>>(dev_c);
		break;
	case 8:
		kernel8<<<N,1>>>(dev_c);
		break;
	case 9:
		kernel9<<<N,1>>>(dev_c);
		break;
	case 10:
		kernel10<<<N,1>>>(dev_c);
		break;
	case 11:
		kernel11<<<N,1>>>(dev_c);
		break;
	case 12:
		kernel12<<<N,1>>>(dev_c);
		break;
	case 13:
		kernel13<<<N,1>>>(dev_c);
		break;
	case 14:
		kernel14<<<N,1>>>(dev_c);
	case 15:
		kernel15<<<N,1>>>(dev_c);
	case 16:
		kernel16<<<N,1>>>(dev_c);
	case 17:
		kernel17<<<N,1>>>(dev_c);
		break;
	case 18:
		kernel18<<<N,1>>>(dev_c);
		break;
	case 19:
		kernel19<<<N,1>>>(dev_c);
		break;
	case 20:
		kernel20<<<N,1>>>(dev_c);
			

		default:
			;
	
	}
	QueryPerformanceCounter(&t3);//�˺�������ʱ��
	HANDLE_ERROR(cudaMemcpy(count,dev_c,N*sizeof(int),cudaMemcpyDeviceToHost));

	for(i=0; i<N; i++ )
		sum += count[i];
	//printf("\n�ܹ�%d����\n", sum2);
	printf("\n�ܹ�%d����\n", sum);
	QueryPerformanceCounter(&t4);//����ʱ��
	printf("Use Time:%f\n",(t4.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//��ӡ��ʱ
	printf("Kernel Use Time:%f\n",(t3.QuadPart-t2.QuadPart)*1.0/tc.QuadPart);//��ӡ�˺�����ʱ

	//printf("XX1:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//��ӡ�˺�����ʱ
	//printf("XX1:%f\n",(t4.QuadPart-t3.QuadPart)*1.0/tc.QuadPart);//��ӡ�˺�����ʱ
	return 0;
}

#endif




//#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//#define N 4
//
//int (*Queen)[N] = new int[100][N];
//int myCount=-1;
////��ʼ����ά����
//void InitMatrix(int L[][N])
//{
//	int i,j;
//	for(i=0; i<N; i++)
//		for(j=0; j<N; j++)
//			L[i][j] = 0;
//}
////�����ס������ϵĸ�
//void Mi(int L[][N], int row, int col)
//{
//	int i,j;
//	for(i=0; i<N; i++)
//	{
//		L[row][i] = -1;//ͬ��
//		L[i][col] = -1;//ͬ��
//	}
//	//��б��	//��б��
//	for(i=0; i<N; i++)
//		for(j=0; j<N; j++)
//			if((i-row == col-j)||(i-row == j-col))
//				L[i][j] = -1;
//}
////�Ϸ����жϡ�����rowĳ������֮ǰ�����бȽϣ�Q[]�洢֮ǰ�кϷ���λ��
//int isLegal(int L[], int row, int pos)
//{
//	for(int i=0; i<row; i++)
//	{
//		if(pos == L[i])return 0;
//		if(L[i] - pos == i - row)return 0;//���Խ���
//		if(L[i] - pos == row - i)return 0;//б�Խ���
//	}
//	return 1;
//}
////int isLegal(int Q[], int row, int col)
////{
////	int i;
////	if(row == 0)return 1;
////	for(i=0; i<row; i++)
////		if(col==Q[i] || col-i == row-Q[i] || i-col == row-Q[i])
////			return 0;
////	return 1;
////	
////}
////��������_������н�����ά����ĳ��
//void saveQueen(int Queen[][N], int cnt, int L[])
//{	
//	for(int i=0; i<N; i++)
//		Queen[cnt][i] = L[i];	
//}
////�̶�һ�����Ӻ󣬲��Ҹ�״̬�µ����п��ܣ����ؽ����
//int findQueen(int row, int col)
//{
//	int L[N][N], i,i0, i1, i2, i3;
//	int Q[N],count=-1;
//	for(i=0; i<N; i++)
//		Q[i] = 0;
//	InitMatrix(L);//��ʼ������
//	Mi(L, row, col);//�����ס������ϵĸ�
//	Q[row] = col;//��¼ָ������
//	//��ÿ����ȡһ�����ø񣬲��ж��Ƿ�Ϊ���н�
//
//		for(i0=0; i0<N; i0++)/*��0��*/
//			if(row==0)goto Layer1;
//			else
//				if(L[0][i0] != -1)//���ӿɷ�λ��
//				{
//					Q[0] = i0;
//					if(row==1)goto Layer2;
//					else
//			Layer1:		for(i1=0; i1<N; i1++)/*��1��*/
//							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
//							{
//								Q[1] = i1;
//								if(row==2)goto Layer3;
//								else
//			Layer2:					for(i2=0; i2<N; i2++)/*��2��*/
//										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
//										{
//											Q[2] = i2;
//											if(row==3)goto Layer4;
//											else
//			Layer3:								for(i3=0; i3<N; i3++)/*��3��*/
//													if(L[3][i3] != -1 && isLegal(Q, 3, i3))
//													{
//														Q[3] = i3;
//			Layer4:											//����Ϊ���н�
//														count++;
//														myCount++;
//														saveQueen(Queen,myCount,Q);
//														for(i=0; i<N; i++)
//															Q[i] = 0;
//													}
//										}
//							}
//			}	
//	return count+1;
//}
////��ӡ�ʺ�
//void showQueen(int Queen[][N], int count)
//{
//	for(int i=0; i<=count; i++)
//	{
//		printf("��%d���⣺ ",i+1);
//		for(int j=0; j<N; j++)
//			printf("(%d,%d)",j,Queen[i][j]);
//		printf("\n");
//	}
//}
////�������
////void Allocate()
////{
////	int i,j;
////	//������ÿ����Ϊһ������
////	for(i=0; i<N; i++)
////		for(j=0; j<N; j++)
////			findQueen(i, j);
////	
////}
//int main()
//{
//	int i=0,cnt,sum=0;
//
//			/*ʱ���ʱ����*/
//	LARGE_INTEGER t1,t2,tc;//����ʱ�����
//	QueryPerformanceFrequency(&tc);//
//	QueryPerformanceCounter(&t1);//
//	for(i=0; i<N; i++)
//	{
//		cnt = findQueen(0,i);
//		sum+=cnt;
//	}
//	QueryPerformanceCounter(&t2);//����ʱ��
//	printf("\n�ܹ�%d����",myCount+1);
//
//	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//��ӡ��ʱ
//	//showQueen(Queen, myCount);
//	return 0;
//}