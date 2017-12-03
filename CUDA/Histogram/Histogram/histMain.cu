#include"E:\VisualStudio\CUDA\CUDAColorToGray\CUDAColorToGray\bmploader_zhang.h"
#include"E:\VisualStudio\CUDA\CUDAColorToGray\CUDAColorToGray\color_fading.h"
#include"E:\VisualStudio\CUDA\cudaDome03\common\cpu_bitmap.h"
#include "math.h"
#include<iostream>
using namespace std;
#define WIDTH 1024
#define	HEIGHT 683
int width = WIDTH;
int height = HEIGHT;

unsigned char *fade(unsigned char *ptr, unsigned char *dst)//褪色
{
	
	for(int y=0; y<HEIGHT; y++)
		for(int x=0; x<WIDTH; x++)
		{
			int offset = x + y * WIDTH;
			//int offset = x * WIDTH + y ;  //错误
			//从RGB色转为灰度公式：
			//Gray = R*0.299 + G*0.587 + B*0.114
            //ptr[offset*4 + 0] = ptr[offset*4 + 0]*0.299 + ptr[offset*4 + 1] *0.587 + ptr[offset*4 + 2] * 0.114 ;
            //ptr[offset*4 + 1] = ptr[offset*4 + 0]*0.299 + ptr[offset*4 + 1] *0.587 + ptr[offset*4 + 2] * 0.114 ;
            //ptr[offset*4 + 2] = ptr[offset*4 + 0]*0.299 + ptr[offset*4 + 1] *0.587 + ptr[offset*4 + 2] * 0.114 ;
			ptr[offset*4 + 0] = (dst[offset*4 + 0] + dst[offset*4 + 1]  + dst[offset*4 + 2] )/3 ;
            ptr[offset*4 + 1] = (dst[offset*4 + 0] + dst[offset*4 + 1]  + dst[offset*4 + 2] )/3 ;
            ptr[offset*4 + 2] = (dst[offset*4 + 0] + dst[offset*4 + 1]  + dst[offset*4 + 2] )/3 ;
            ptr[offset*4 + 3] = 255;
        }
	return ptr;		
}
void scan(unsigned char *ptr, int *hist)//扫描，并生成直方图
{
	for(int y=0; y<HEIGHT; y++)
		for(int x=0; x<WIDTH; x+=4)
		{
			long int offset = x + y * WIDTH;
			//int offset = x * WIDTH + y ;  //错误
			hist[ptr[offset]]++;
        }
}
//累积分布函数
void accumulate(int *hist)
{
	int temp[256]={0};//部分和全部初始化0
	for(int i=1;i<256;i++)
	{
		//for(int j=0;j<=i;j++)
		//	temp[i] += hist[j];
		temp[i] = temp[i-1] + hist[i];
	}
	for(int i=1;i<256;i++)
		hist[i]=temp[i];

}

//均衡化
int *balance( int *hist)
{
	int *bala = new int[256];//记录均衡化后的灰度值	
	memset(bala,'\0',256*4);//全部至0,正确——该转换按字符处理所有的类型
	int i=0;//查找第一个不为0的部分和的坐标
	for(;i<256;i++)
		if(hist[i])break;
	int min = i;
	cout<<min<<"********************************************************************";
	for(i=min;i<256;i++)
	{
		//bala[i] = (int)((hist[i]-hist[min])*255/(width*height-hist[min])+0.5);
		bala[i] = round( (double)(hist[i] - hist[min]) * 255 / (width*height - hist[min]));
	}
	//for(i=1;i<256;i++)
	//{
	//	bala[i] = round( (double)(hist[i] - hist[0]) * 255 / (width*height - hist[0]));
	//}
	return bala;
}
void change(unsigned char *ptr, int *bala)//生成直方均衡化图
{
	//for(int y=0; y<HEIGHT; y++)
	//	for(int x=0; x<WIDTH; x++)
	//	{
	//		int offset = x + y * WIDTH;
	//		ptr[offset*4 ] = (unsigned char)bala[ptr[offset*4 ]];
 //       }
	for(int y=0; y<HEIGHT; y++)
		for(int x=0; x<WIDTH; x++)
		{
			int offset = x + y * WIDTH;//遍历每个像素点
			ptr[offset*4 + 0] = bala[ptr[offset*4 + 0]];
            ptr[offset*4 + 1] = bala[ptr[offset*4 + 1]];
            ptr[offset*4 + 2] = bala[ptr[offset*4 + 2]];
            ptr[offset*4 + 3] = 255;
        }

}
int main()
{
	int w,h;
	w=width;h=height;
	unsigned char *dst;
	//dst=(unsigned char *)malloc(sizeof(char)*w*h*4);//无需分配空间
	
	CPUBitmap bitmap(w, h);
	//char *name="nature_monte.bmp";
	char *name="un.bmp";
	//LoadBMPFile(&dst, &w,  &h, name);	 
	LoadBMPFile(&bitmap.pixels, &w,  &h, name);//导入成功
	
	//blur(ptr,dst1);//模糊
	//fade(bitmap.pixels, dst);//褪色


	//分配空间——直方图
	int *hist = new int[256];
	memset(hist,'\0',256*4);//全部至0,正确——该转换按字符处理所有的类型

	scan(bitmap.pixels, hist);//记录直方图
	accumulate(hist);//累积分布函数
	int *bala = balance( hist);
	change(bitmap.pixels, bala);

	bitmap.display_and_exit(); 
	free(dst);
	delete []hist;
	delete []bala;

}