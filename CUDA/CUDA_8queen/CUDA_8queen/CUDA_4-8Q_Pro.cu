////3.5�ܹ�����֧�֡����˺������ú˺���
//#include <stdio.h>
//
//
//
//__global__ void childKernel(int i)
//{
//	int tid = blockIdx.x*blockDim.x+threadIdx.x;
//	printf("parent:%d,child:%d\n",i,tid);
//	for(int j=i;j<i+10;j++)
//	{
//		printf(",%d",j);
//	}
//	printf("\n");
//}
//
//__global__ void kernel()
//{
//
//	int tid = blockIdx.x*blockDim.x+threadIdx.x;
//	childKernel<<<1,2>>>(tid);
//}
//
//int main()
//{
//
//	kernel<<<1,1>>>();
//	cudaDeviceSynchronize();
//
//return 0;
//}
