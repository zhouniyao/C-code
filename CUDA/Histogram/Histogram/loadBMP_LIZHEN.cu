//#include"E:\VisualStudio\CUDA\CUDAColorToGray\CUDAColorToGray\bmploader_zhang.h"
//#include"E:\VisualStudio\CUDA\CUDAColorToGray\CUDAColorToGray\color_fading.h"
//#include"E:\VisualStudio\CUDA\cudaDome03\common\cpu_bitmap.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <cmath>
//#define  width   1024
//#define  height  683
//#define  size       width*height
//void kernel(unsigned char *ptr, unsigned char *dst1){
//
//	for (int y = 0; y<height; y++) {
//		for (int x = 0; x<width; x++) {
//			int offset = x + y * width;
//			ptr[offset * 4 + 0] = dst1[offset * 4 + 0] * 0.299 + dst1[offset * 4 + 1] * 0.587 + dst1[offset * 4 + 2] * 0.114;
//			ptr[offset * 4 + 1] = dst1[offset * 4 + 0] * 0.299 + dst1[offset * 4 + 1] * 0.587 + dst1[offset * 4 + 2] * 0.114;
//			ptr[offset * 4 + 2] = dst1[offset * 4 + 0] * 0.299 + dst1[offset * 4 + 1] * 0.587 + dst1[offset * 4 + 2] * 0.114;
//			ptr[offset * 4 + 3] = 255;
//		}
//	}
//	 
//}
//int main(void)
//{
//	unsigned char *dst1;
//	dst1 = (unsigned char *)malloc(sizeof(int));
//	unsigned char **dst;
//	dst = &dst1;
//	int w, h;
//	w = width; h = height;
//	char *name = "un.bmp";
//	LoadBMPFile(dst, &w, &h, name);
//	CPUBitmap bitmap(w, h);
//	unsigned char *ptr = bitmap.get_ptr();
//	kernel(ptr, dst1);//ÍÊÉ«
//	unsigned char *  buffer;
//	buffer = (unsigned char *)malloc(sizeof(unsigned char )*size);
//	 
//	for (int y = 0; y<height; y++) {
//		for (int x = 0; x<width; x++) {
//			int offset = x + y * width;		
//		   buffer[offset] = ptr[offset * 4 + 0];  //  
//			 
//		}
//	}
//	int  histo[256];//Ö±·½Í¼
//	for (int i = 0; i < 256; i++)
//		histo[i] = 0;
//	for (long i = 0; i < size; i++)
//		histo[buffer[i]]++;
//	/*for (int i = 0; i < 256; i++)
//	{
//		printf("%d:,%d", i, histo[i]);
//		printf("\n");
//	}*/
//	long  histoCount[256];
//	histoCount[0] = histo[0];
//	printf("%d", histoCount[0]); printf("\n");
//	for (int i = 1; i < 256; i++)
//	{
//		histoCount[i] = histo[i] + histoCount[i - 1];
//		 
//	}
//	
//	 
//	long  new_grey[256];
//	for (int i = 0; i < 256; i++) new_grey[i] = 0;
//	for (int i = 1; i < 256; i++)
//	{
//		new_grey[i] =round( (long  double)(histoCount[i] - histoCount[0]) / (size - histoCount[0]) * 255);
//		 
//	}
//	kernel(ptr, dst1);
//	for (int y = 0; y < height; y++) {
//		for (int x = 0; x < width; x++) {
//			int offset = x + y * width;
//			ptr[offset * 4 + 0] = new_grey[ptr[offset * 4 + 0]];
//			ptr[offset * 4 + 1] = new_grey[ptr[offset * 4 + 1]];
//			ptr[offset * 4 + 2] = new_grey[ptr[offset * 4 + 2]];
//			ptr[offset * 4 + 3] = 255;
//		}
//	}
//	bitmap.display_and_exit();
//	free(dst1);
//	free(buffer);	 
//
//}
