#if 0


/*
*N皇后，利用CUDA将传统的串行算法——盲目穷举，并行化
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

//初始化二维数组
__device__ void InitMatrix(int L[][N])
{
	int i,j;
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			L[i][j] = 0;
}
//处理【米】字线上的格
__device__ void Mi(int L[][N], int row, int col)
{
	int i,j;
	for(i=0; i<N; i++)
	{
		L[row][i] = -1;//同行
		L[i][col] = -1;//同列
	}
	//正斜线	//反斜线
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			if((i-row == col-j)||(i-row == j-col))
				L[i][j] = -1;
}
//合法性判断——该row某列与其之前所有行比较，Q[]存储之前行合法列位置
__device__ int isLegal(int L[], int row, int pos )
{
	for(int i=0; i<row; i++)
	{
		if(L[i] == -1)return 0;
		if(pos == L[i])return 0;
		if(L[i] - pos == i - row)return 0;//正对角线
		if(L[i] - pos == row - i)return 0;//斜对角线
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
//保存数组_保存可行解至二维数组某行
//__device__ void saveQueen(int Queen[][N], int cnt, int L[])
//{	
//	for(int i=0; i<N; i++)
//		Queen[cnt][i] = L[i];	
//}
__device__ static int myCount = 0;//统计解个数，没用上

//固定一个棋子后，查找该状态下的所有可能，返回解个数
/***************************************** 4皇后*****************************************/
//__device__ int findQueen4(int row, int col)//row为0，col为threadIdx
//{
//	//int i,j,flag;
//	//int L[N][N];
//	//int temp[N];
//	///*棋盘初始化*/
//	////正斜线	//反斜线
//	//for(i=0; i<N; i++)
//	//	for(j=0; j<N; j++)
//	//		if((i-row == col-j)||(i-row == j-col))
//	//			L[i][j] = -1;
//	//		else
//	//			L[i][j]=0;
//
//	//for(i=0; i<N; i++)
//	//{
//	//	L[row][i] = -1;//同行
//	//	L[i][col] = -1;//同列
//	//}
//	int cnt = 0;
//	int L[N] = {0};
//	L[row] = col;
//	for(int i1=0; i1<N; i1++)/*第1层*/
//	{
//		//if(L[1][i1]==-1)continue;		
//		if(isLegal(L, 1, i1 ))
//		{
//			L[1] = i1;
//			for(int i2=0; i2<N; i2++)/*第2层*/
//			{
//				
//				//if(L[2][i2]==-1)continue;
//				
//				if(isLegal(L, 2, i2 ))
//				{
//					L[2] = i2;
//					for(int i3=0; i3<N; i3++)/*第3层*/
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
	//InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(row==3)goto Layer4;
												else
													if(L[3][i3] != -1 && isLegal(Q, 3, i3))
													{
														Q[3] = i3;
		Layer4:											//到此为可行解
														cnt++;
														//myCount++;
														//saveQueen(Queen,myCount,Q);
													}
										}
							}
			}	
	return cnt;
}
//***************************************** 5皇后*****************************************/
__device__ int findQueen5(int row, int col)
{
	int L[N][N] = {0};
	int i,i0, i1, i2, i3, i4;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
																//到此为可行解
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
//***************************************** 6皇后*****************************************/
__device__ int findQueen6(int row, int col)
{
	int L[N][N] = {0};
	int i,i0, i1, i2, i3, i4, i5;
	int Q[N] = {0};
	int cnt = 0;

	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																			//到此为可行解
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
//***************************************** 7皇后*****************************************/
__device__ int findQueen7(int row, int col )
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																					//到此为可行解
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
//***************************************** 8皇后*****************************************/
__device__ int findQueen8(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																							//到此为可行解
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
///***************************************** 9皇后*****************************************/
__device__ int findQueen9(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8;
	int Q[N] = {0} ;
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								//到此为可行解
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
//***************************************** 10皇后*****************************************/
__device__ int findQueen10(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										//到此为可行解
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
//***************************************** 11皇后*****************************************/
__device__ int findQueen11(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*第10层*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												//到此为可行解
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
//***************************************** 12皇后*****************************************/
__device__ int findQueen12(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*第10层*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*第11层*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														//到此为可行解
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
//***************************************** 13皇后*****************************************/
__device__ int findQueen13(int row, int col )
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*第10层*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*第11层*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*第12层*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																//到此为可行解
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
//***************************************** 14皇后*****************************************/
__device__ int findQueen14(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*第10层*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*第11层*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*第12层*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*第13层*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		//到此为可行解
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
//***************************************** 15皇后*****************************************/
//int findQueen15(int row, int col)
//{
//	int L[N][N], i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14;
//	int Q[N],count=-1;
//	for(i=0; i<N; i++)
//		Q[i] = 0;
//	InitMatrix(L);//初始化棋盘
//	Mi(L, row, col);//处理【米】字线上的格
//	Q[row] = col;//记录指定棋子
//	//从每行提取一个可用格，并判断是否为可行解
//
//		//for(i0=0; i0<N; i0++)/*第0层*/
//			if(row==0)goto Layer1;
//			else
//				if(L[0][i0] != -1)//棋子可放位置
//				{
//					Q[0] = i0;
//
//		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
//						if(row==1)goto Layer2;
//						else
//							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
//							{
//								Q[1] = i1;
//
//		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
//									if(row==2)goto Layer3;
//									else
//										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
//										{
//											Q[2] = i2;
//
//		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
//												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
//												{
//													Q[3] = i3;
//													for(i4=0; i4<N; i4++)/*第4层*/
//													{
//														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
//														{
//															Q[4] = i4;
//															for(i5=0; i5<N; i5++)/*第5层*/
//															{																
//																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
//																	{
//																		Q[5] = i5;
//																		for(i6=0; i6<N; i6++)/*第6层*/
//																		{
//																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
//																			{
//																				Q[6] = i6;
//																				for(i7=0; i7<N; i7++)/*第7层*/
//																				{
//																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
//																					{
//																						Q[7] = i7;
//																						for(i8=0; i8<N; i8++)/*第8层*/
//																						{
//																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
//																							{
//																								Q[8] = i8;
//																								for(i9=0; i9<N; i9++)/*第9层*/
//																								{
//																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
//																									{
//																										Q[9] = i9;
//																										for(i10=0; i10<N; i10++)/*第10层*/
//																										{
//																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
//																											{
//																												Q[10] = i10;
//																												for(i11=0; i11<N; i11++)/*第11层*/
//																												{
//																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
//																													{
//																														Q[11] = i11;
//																														for(i12=0; i12<N; i12++)/*第12层*/
//																														{
//																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
//																															{
//																																Q[12] = i12;
//																																for(i13=0; i13<N; i13++)/*第13层*/
//																																{
//																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
//																																	{
//																																		Q[13] = i13;
//																																		for(i14=0; i14<N; i14++)/*第14层*/
//																																		{
//																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
//																																			{
//																																				Q[14] = i14;
//																																				//到此为可行解
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
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*第10层*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*第11层*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*第12层*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*第13层*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*第14层*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				//到此为可行解
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
//***************************************** 16皇后*****************************************/
__device__ int findQueen16(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*第10层*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*第11层*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*第12层*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*第13层*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*第14层*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				for(i15=0; i15<N; i15++)/*第15层*/
																																				{
																																					if(L[15][i15] != -1 && isLegal(Q, 15, i15))
																																					{
																																						Q[15] = i15;
																																						//到此为可行解
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
//***************************************** 17皇后*****************************************/
__device__ int findQueen17(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*第10层*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*第11层*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*第12层*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*第13层*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*第14层*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				for(i15=0; i15<N; i15++)/*第15层*/
																																				{
																																					if(L[15][i15] != -1 && isLegal(Q, 15, i15))
																																					{
																																						Q[15] = i15;
																																						for(i16=0; i16<N; i16++)/*第16层*/
																																						{
																																							if(L[16][i16] != -1 && isLegal(Q, 16, i16))
																																							{
																																								Q[16] = i16;
																																								//到此为可行解
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
//***************************************** 18皇后*****************************************/
__device__ int findQueen18(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*第10层*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*第11层*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*第12层*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*第13层*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*第14层*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				for(i15=0; i15<N; i15++)/*第15层*/
																																				{
																																					if(L[15][i15] != -1 && isLegal(Q, 15, i15))
																																					{
																																						Q[15] = i15;
																																						for(i16=0; i16<N; i16++)/*第16层*/
																																						{
																																							if(L[16][i16] != -1 && isLegal(Q, 16, i16))
																																							{
																																								Q[16] = i16;
																																								for(i17=0; i17<N; i17++)/*第17层*/
																																								{
																																									if(L[17][i17] != -1 && isLegal(Q, 17, i17))
																																									{
																																										Q[17] = i17;
																																										//到此为可行解
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
//***************************************** 19皇后*****************************************/
__device__ int findQueen19(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17, i18;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*第10层*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*第11层*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*第12层*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*第13层*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*第14层*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				for(i15=0; i15<N; i15++)/*第15层*/
																																				{
																																					if(L[15][i15] != -1 && isLegal(Q, 15, i15))
																																					{
																																						Q[15] = i15;
																																						for(i16=0; i16<N; i16++)/*第16层*/
																																						{
																																							if(L[16][i16] != -1 && isLegal(Q, 16, i16))
																																							{
																																								Q[16] = i16;
																																								for(i17=0; i17<N; i17++)/*第17层*/
																																								{
																																									if(L[17][i17] != -1 && isLegal(Q, 17, i17))
																																									{
																																										Q[17] = i17;
																																										for(i18=0; i18<N; i18++)/*第18层*/
																																										{
																																											if(L[18][i18] != -1 && isLegal(Q, 18, i18))
																																											{
																																												Q[18] = i18;
																																												//到此为可行解
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
//***************************************** 20皇后*****************************************/
__device__ int findQueen20(int row, int col)
{
	int L[N][N];
	int i,i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17, i18, i19;
	int Q[N] = {0};
	int cnt = 0;
	InitMatrix(L);//初始化棋盘
	Mi(L, row, col);//处理【米】字线上的格
	Q[row] = col;//记录指定棋子
	//从每行提取一个可用格，并判断是否为可行解

		//for(i0=0; i0<N; i0++)/*第0层*/
			if(row==0)goto Layer1;
			else
				if(L[0][i0] != -1)//棋子可放位置
				{
					Q[0] = i0;

		Layer1:		for(i1=0; i1<N; i1++)/*第1层*/      /*不该循环，却循环了4次，得到4个相同结果*/
						if(row==1)goto Layer2;
						else
							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
							{
								Q[1] = i1;

		Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
									if(row==2)goto Layer3;
									else
										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
										{
											Q[2] = i2;

		Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
												if(L[3][i3] != -1 && isLegal(Q, 3, i3))
												{
													Q[3] = i3;
													for(i4=0; i4<N; i4++)/*第4层*/
													{
														if(L[4][i4] != -1 && isLegal(Q, 4, i4))
														{
															Q[4] = i4;
															for(i5=0; i5<N; i5++)/*第5层*/
															{																
																if(L[5][i5] != -1 && isLegal(Q, 5, i5))
																	{
																		Q[5] = i5;
																		for(i6=0; i6<N; i6++)/*第6层*/
																		{
																			if(L[6][i6] != -1 && isLegal(Q, 6, i6))
																			{
																				Q[6] = i6;
																				for(i7=0; i7<N; i7++)/*第7层*/
																				{
																					if(L[7][i7] != -1 && isLegal(Q, 7, i7))
																					{
																						Q[7] = i7;
																						for(i8=0; i8<N; i8++)/*第8层*/
																						{
																							if(L[8][i8] != -1 && isLegal(Q, 8, i8))
																							{
																								Q[8] = i8;
																								for(i9=0; i9<N; i9++)/*第9层*/
																								{
																									if(L[9][i9] != -1 && isLegal(Q, 9, i9))
																									{
																										Q[9] = i9;
																										for(i10=0; i10<N; i10++)/*第10层*/
																										{
																											if(L[10][i10] != -1 && isLegal(Q, 10, i10))
																											{
																												Q[10] = i10;
																												for(i11=0; i11<N; i11++)/*第11层*/
																												{
																													if(L[11][i11] != -1 && isLegal(Q, 11, i11))
																													{
																														Q[11] = i11;
																														for(i12=0; i12<N; i12++)/*第12层*/
																														{
																															if(L[12][i12] != -1 && isLegal(Q, 12, i12))
																															{
																																Q[12] = i12;
																																for(i13=0; i13<N; i13++)/*第13层*/
																																{
																																	if(L[13][i13] != -1 && isLegal(Q, 13, i13))
																																	{
																																		Q[13] = i13;
																																		for(i14=0; i14<N; i14++)/*第14层*/
																																		{
																																			if(L[14][i14] != -1 && isLegal(Q, 14, i14))
																																			{
																																				Q[14] = i14;
																																				for(i15=0; i15<N; i15++)/*第15层*/
																																				{
																																					if(L[15][i15] != -1 && isLegal(Q, 15, i15))
																																					{
																																						Q[15] = i15;
																																						for(i16=0; i16<N; i16++)/*第16层*/
																																						{
																																							if(L[16][i16] != -1 && isLegal(Q, 16, i16))
																																							{
																																								Q[16] = i16;
																																								for(i17=0; i17<N; i17++)/*第17层*/
																																								{
																																									if(L[17][i17] != -1 && isLegal(Q, 17, i17))
																																									{
																																										Q[17] = i17;
																																										for(i18=0; i18<N; i18++)/*第18层*/
																																										{
																																											if(L[18][i18] != -1 && isLegal(Q, 18, i18))
																																											{
																																												Q[18] = i18;
																																												for(i19=0; i19<N; i19++)/*第19层*/
																																												{
																																													if(L[19][i19] != -1 && isLegal(Q, 19, i19))
																																													{
																																														Q[19] = i19;
																																														//到此为可行解
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

//打印皇后
void showQueen(int Queen[][N], int count)
{
	for(int i=0; i<=count; i++)
	{
		printf("第%d个解： ",i+1);
		for(int j=0; j<N; j++)
			printf("(%d,%d)",j,Queen[i][j]);
		printf("\n");
	}
}

//任务分配
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
	LARGE_INTEGER t1,t2,tc,t3,t4;//定义时间变量
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);//总执行时间start
	int i=0,sum=0;
	//int* dev_row;
	//int* dev_col;
	//int count[N] = {0};
	int* count = (int*)malloc(N*sizeof(int));
	for(i=0; i<N; i++)
		*(count+i) = 0;
	int* dev_c;
	//HANDLE_ERROR(cudaMalloc((void**)&dev_row,sizeof(int)));//行
	//HANDLE_ERROR(cudaMalloc((void**)&dev_col,sizeof(int)));//列
	HANDLE_ERROR(cudaMalloc((void**)&dev_c,N*sizeof(int)));
    HANDLE_ERROR( cudaMemcpy(dev_c, count,
                              N*sizeof(int),
                              cudaMemcpyHostToDevice) );

	QueryPerformanceCounter(&t2);//核函数开始时间
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
	QueryPerformanceCounter(&t3);//核函数结束时间
	HANDLE_ERROR(cudaMemcpy(count,dev_c,N*sizeof(int),cudaMemcpyDeviceToHost));

	for(i=0; i<N; i++ )
		sum += count[i];
	//printf("\n总共%d个解\n", sum2);
	printf("\n总共%d个解\n", sum);
	QueryPerformanceCounter(&t4);//结束时间
	printf("Use Time:%f\n",(t4.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//打印耗时
	printf("Kernel Use Time:%f\n",(t3.QuadPart-t2.QuadPart)*1.0/tc.QuadPart);//打印核函数耗时

	//printf("XX1:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//打印核函数耗时
	//printf("XX1:%f\n",(t4.QuadPart-t3.QuadPart)*1.0/tc.QuadPart);//打印核函数耗时
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
////初始化二维数组
//void InitMatrix(int L[][N])
//{
//	int i,j;
//	for(i=0; i<N; i++)
//		for(j=0; j<N; j++)
//			L[i][j] = 0;
//}
////处理【米】字线上的格
//void Mi(int L[][N], int row, int col)
//{
//	int i,j;
//	for(i=0; i<N; i++)
//	{
//		L[row][i] = -1;//同行
//		L[i][col] = -1;//同列
//	}
//	//正斜线	//反斜线
//	for(i=0; i<N; i++)
//		for(j=0; j<N; j++)
//			if((i-row == col-j)||(i-row == j-col))
//				L[i][j] = -1;
//}
////合法性判断——该row某列与其之前所有行比较，Q[]存储之前行合法列位置
//int isLegal(int L[], int row, int pos)
//{
//	for(int i=0; i<row; i++)
//	{
//		if(pos == L[i])return 0;
//		if(L[i] - pos == i - row)return 0;//正对角线
//		if(L[i] - pos == row - i)return 0;//斜对角线
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
////保存数组_保存可行解至二维数组某行
//void saveQueen(int Queen[][N], int cnt, int L[])
//{	
//	for(int i=0; i<N; i++)
//		Queen[cnt][i] = L[i];	
//}
////固定一个棋子后，查找该状态下的所有可能，返回解个数
//int findQueen(int row, int col)
//{
//	int L[N][N], i,i0, i1, i2, i3;
//	int Q[N],count=-1;
//	for(i=0; i<N; i++)
//		Q[i] = 0;
//	InitMatrix(L);//初始化棋盘
//	Mi(L, row, col);//处理【米】字线上的格
//	Q[row] = col;//记录指定棋子
//	//从每行提取一个可用格，并判断是否为可行解
//
//		for(i0=0; i0<N; i0++)/*第0层*/
//			if(row==0)goto Layer1;
//			else
//				if(L[0][i0] != -1)//棋子可放位置
//				{
//					Q[0] = i0;
//					if(row==1)goto Layer2;
//					else
//			Layer1:		for(i1=0; i1<N; i1++)/*第1层*/
//							if(L[1][i1] != -1 && isLegal(Q, 1, i1))
//							{
//								Q[1] = i1;
//								if(row==2)goto Layer3;
//								else
//			Layer2:					for(i2=0; i2<N; i2++)/*第2层*/
//										if(L[2][i2] != -1 && isLegal(Q, 2, i2))
//										{
//											Q[2] = i2;
//											if(row==3)goto Layer4;
//											else
//			Layer3:								for(i3=0; i3<N; i3++)/*第3层*/
//													if(L[3][i3] != -1 && isLegal(Q, 3, i3))
//													{
//														Q[3] = i3;
//			Layer4:											//到此为可行解
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
////打印皇后
//void showQueen(int Queen[][N], int count)
//{
//	for(int i=0; i<=count; i++)
//	{
//		printf("第%d个解： ",i+1);
//		for(int j=0; j<N; j++)
//			printf("(%d,%d)",j,Queen[i][j]);
//		printf("\n");
//	}
//}
////任务分配
////void Allocate()
////{
////	int i,j;
////	//棋盘上每个格为一个任务
////	for(i=0; i<N; i++)
////		for(j=0; j<N; j++)
////			findQueen(i, j);
////	
////}
//int main()
//{
//	int i=0,cnt,sum=0;
//
//			/*时间计时函数*/
//	LARGE_INTEGER t1,t2,tc;//定义时间变量
//	QueryPerformanceFrequency(&tc);//
//	QueryPerformanceCounter(&t1);//
//	for(i=0; i<N; i++)
//	{
//		cnt = findQueen(0,i);
//		sum+=cnt;
//	}
//	QueryPerformanceCounter(&t2);//结束时间
//	printf("\n总共%d个解",myCount+1);
//
//	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//打印耗时
//	//showQueen(Queen, myCount);
//	return 0;
//}