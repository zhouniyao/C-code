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

unsigned char *fade(unsigned char *ptr, unsigned char *dst)//��ɫ
{
	
	for(int y=0; y<HEIGHT; y++)
		for(int x=0; x<WIDTH; x++)
		{
			int offset = x + y * WIDTH;
			//int offset = x * WIDTH + y ;  //����
			//��RGBɫתΪ�Ҷȹ�ʽ��
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
void scan(unsigned char *ptr, int *hist)//ɨ�裬������ֱ��ͼ
{
	for(int y=0; y<HEIGHT; y++)
		for(int x=0; x<WIDTH; x+=4)
		{
			long int offset = x + y * WIDTH;
			//int offset = x * WIDTH + y ;  //����
			hist[ptr[offset]]++;
        }
}
//�ۻ��ֲ�����
void accumulate(int *hist)
{
	int temp[256]={0};//���ֺ�ȫ����ʼ��0
	for(int i=1;i<256;i++)
	{
		//for(int j=0;j<=i;j++)
		//	temp[i] += hist[j];
		temp[i] = temp[i-1] + hist[i];
	}
	for(int i=1;i<256;i++)
		hist[i]=temp[i];

}

//���⻯
int *balance( int *hist)
{
	int *bala = new int[256];//��¼���⻯��ĻҶ�ֵ	
	memset(bala,'\0',256*4);//ȫ����0,��ȷ������ת�����ַ��������е�����
	int i=0;//���ҵ�һ����Ϊ0�Ĳ��ֺ͵�����
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
void change(unsigned char *ptr, int *bala)//����ֱ�����⻯ͼ
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
			int offset = x + y * WIDTH;//����ÿ�����ص�
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
	//dst=(unsigned char *)malloc(sizeof(char)*w*h*4);//�������ռ�
	
	CPUBitmap bitmap(w, h);
	//char *name="nature_monte.bmp";
	char *name="un.bmp";
	//LoadBMPFile(&dst, &w,  &h, name);	 
	LoadBMPFile(&bitmap.pixels, &w,  &h, name);//����ɹ�
	
	//blur(ptr,dst1);//ģ��
	//fade(bitmap.pixels, dst);//��ɫ


	//����ռ䡪��ֱ��ͼ
	int *hist = new int[256];
	memset(hist,'\0',256*4);//ȫ����0,��ȷ������ת�����ַ��������е�����

	scan(bitmap.pixels, hist);//��¼ֱ��ͼ
	accumulate(hist);//�ۻ��ֲ�����
	int *bala = balance( hist);
	change(bitmap.pixels, bala);

	bitmap.display_and_exit(); 
	free(dst);
	delete []hist;
	delete []bala;

}