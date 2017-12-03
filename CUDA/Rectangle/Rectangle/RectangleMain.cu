#include "E:\VisualStudio\CUDA\CUDAColorToGray\CUDAColorToGray\bmploader_zhang.h"
#include"E:\VisualStudio\CUDA\CUDAColorToGray\common/cpu_bitmap.h"
#include<iostream>
#define WIDTH 640
#define	HEIGHT 480

void fade( unsigned char *dst ,unsigned char *ptr)//褪色
{
	int i = 0;
	 for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH;  x++) {
            int offset = x + y * WIDTH;
			
		//Gray = R*0.299 + G*0.587 + B*0.114
            //ptr[offset*4 + 0] = ptr[offset*4 + 0]*0.299 + ptr[offset*4 + 1] *0.587 + ptr[offset*4 + 2] * 0.114 ;
            //ptr[offset*4 + 1] = ptr[offset*4 + 0]*0.299 + ptr[offset*4 + 1] *0.587 + ptr[offset*4 + 2] * 0.114 ;
            //ptr[offset*4 + 2] = ptr[offset*4 + 0]*0.299 + ptr[offset*4 + 1] *0.587 + ptr[offset*4 + 2] * 0.114 ;
			dst[i] = ptr[offset*4 + 0]*0.299 + ptr[offset*4 + 1] *0.587 + ptr[offset*4 + 2] * 0.114;
			i++;
		}
	 }
}

//累加像素灰度值0-255
void addgray(int Cpixels[], unsigned char *ptr, int nCount){
	for(int i=0; n<nCount; i++)
	{
		Cpixels[ptr[i]]++;
	}
}
int main()
{
	unsigned char *dst1;

	
	int w,h;
	w=WIDTH;h=HEIGHT;	
	dst1=(unsigned char *)malloc(w*h*sizeof(char));
	char *name="nature_monte.bmp";


	LoadBMPFile(&dst1, &w,  &h, name);	

	CPUBitmap bitmap(w, h/4);
	fade(bitmap.pixels, dst1);
	int Cpixels[256] = malloc(256*sizeof(int));
	memset(0,Cpixels);//清0
	bitmap.display_and_exit(); 
	free(dst1);
}
