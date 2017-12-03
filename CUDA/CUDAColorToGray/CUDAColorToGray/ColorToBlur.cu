#include"E:\VisualStudio\CUDA\CUDAColorToGray\CUDAColorToGray\bmploader_zhang.h"
#include"E:\VisualStudio\CUDA\CUDAColorToGray\CUDAColorToGray\color_fading.h"
#include"E:\VisualStudio\CUDA\cudaDome03\common/cpu_bitmap.h"
#include<iostream>
using namespace std;
#define WIDTH 640
#define	HEIGHT 480

int width = WIDTH;
int height = HEIGHT;
extern void fade( unsigned char *ptr );//褪色

void blur(unsigned char *ptr, unsigned char *src)//模糊
{
	int offset = 0, i = 0, count = 0;		
	for (int y=0; y<height; y++, count++) {
		for (int x=0; x<width; x++,i+=4) {
			offset = x + y * width + width * count;  
			//int left = offset - 1;
			//int right = offset + 1;
			//if (x == 0)   left++;
			//if (x == width-1) right--; 

			//int top = offset - width;
			//int bottom = offset + width;
			//if (y == 0)   top += width;
			//if (y == height-1) bottom -= width;

		/*	int left = offset - 1;
			int right = offset + 1;
			int top = offset - width;
			int topl = top - 5;
			int topr = top + 5;
			int bottom = offset + width;
			int bottoml = bottom - 5;
			int bottomr = bottom + 5;
			if (x == 0)   
			{
				left++;
				topl = top;
				bottoml = bottom;
			}
			if (x == width-1)
			{
				right--; 
				topr = top;
				bottomr = bottom;
			}

	
			if (y == 0)   
			{
				top += width;
				topr = topl = top;
			}
			if (y == height-1) 
			{
				bottom -= width;
				bottomr = bottoml = bottom;
			}
*/
			int left = i - 1;
			int right = i + 1;
			int top = i - width;
			int topl = top - 5;
			int topr = top + 5;
			int bottom = i + width;
			int bottoml = bottom - 5;
			int bottomr = bottom + 5;
			if (x == 0)   
			{
				left++;
				topl = top;
				bottoml = bottom;
			}
			if (x == width-1)
			{
				right--; 
				topr = top;
				bottomr = bottom;
			}	
			if (y == 0)   
			{
				top += width;
				topr = topl = top;
			}
			if (y == height-1) 
			{
				bottom -= width;
				bottomr = bottoml = bottom;
			}

			//高斯模糊
			ptr[offset*4 + 0] = src[topl+0]*0.0947416+src[top+0]*0.118318+src[topr+0]*0.0947416+src[bottoml+0]*0.0947416+src[bottom+0]*0.118318+src[bottomr+0]*0.0947416+src[left+0]*0.118318+src[right+0]*0.118318;
			ptr[offset*4 + 1] = src[topl+1]*0.0947416+src[top+1]*0.118318+src[topr+1]*0.0947416+src[bottoml+1]*0.0947416+src[bottom+1]*0.118318+src[bottomr+1]*0.0947416+src[left+1]*0.118318+src[right+1]*0.118318;
			ptr[offset*4 + 2] = src[topl+2]*0.0947416+src[top+2]*0.118318+src[topr+2]*0.0947416+src[bottoml+2]*0.0947416+src[bottom+2]*0.118318+src[bottomr+2]*0.0947416+src[left+2]*0.118318+src[right+2]*0.118318;
			ptr[offset*4 + 3] = 255;

			//ptr[offset*4 + 0] = ptr[topl+0]*0.0947416+ptr[top+0]*0.118318+ptr[topr+0]*0.0947416+ptr[bottoml+0]*0.0947416+ptr[bottom+0]*0.118318+ptr[bottomr+0]*0.0947416+ptr[left+0]*0.118318+ptr[right+0]*0.118318;
			//ptr[offset*4 + 1] = ptr[topl+1]*0.0947416+ptr[top+1]*0.118318+ptr[topr+1]*0.0947416+ptr[bottoml+1]*0.0947416+ptr[bottom+1]*0.118318+ptr[bottomr+1]*0.0947416+ptr[left+1]*0.118318+ptr[right+1]*0.118318;
			//ptr[offset*4 + 2] = ptr[topl+2]*0.0947416+ptr[top+2]*0.118318+ptr[topr+2]*0.0947416+ptr[bottoml+2]*0.0947416+ptr[bottom+2]*0.118318+ptr[bottomr+2]*0.0947416+ptr[left+2]*0.118318+ptr[right+2]*0.118318;
			//ptr[offset*4 + 3] = 255;



		}
	}


	//显示原图
	offset = 0, i = 0, count = 1;		
	for (int y=0; y<height; y++, count++) {
		for (int x=0; x<width; x++,i+=4) {
			offset = x + y * width + width * count;  
			ptr[offset*4 + 0] = src[i + 0] ;
			ptr[offset*4 + 1] = src[i + 1] ;
			ptr[offset*4 + 2] = src[i + 2] ;
			ptr[offset*4 + 3] = 255;

		}
	}

	//for (int y=0; y<height; y++, count++) {
	//	for (int x=0; x<width; x++,i+=4) {
	//		offset = x + y * width + width * count;  


	//		int left = offset - 1;
	//		int right = offset + 1;
	//		if (x == 0)   left++;
	//		if (x == width-1) right--; 

	//		int top = offset - width;
	//		int bottom = offset + width;
	//		if (y == 0)   top += width;
	//		if (y == height-1) bottom -= width;

	//		ptr[offset*4 + 0] = src[offset*4+0];
	//		ptr[offset*4 + 1] = src[offset*4+1];
	//		ptr[offset*4 + 2] = src[offset*4+2] ;
	//		ptr[offset*4 + 3] = 255;

	//		//ptr[offset*4 + 0] = (src[top+0]+src[bottom+0]+src[left+0]+src[right+0])/3;
	//		//ptr[offset*4 + 1] = (src[top+1]+src[bottom+1]+src[left+1]+src[right+1])/3;
	//		//ptr[offset*4 + 2] = (src[top+2]+src[bottom+2]+src[left+2]+src[right+2])/3 ;
	//		//ptr[offset*4 + 3] = 255;

	//		//ptr[offset*4 + 0] = (ptr[top+0]+ptr[bottom+0]+ptr[left+0]+ptr[right+0])/3;
	//		//ptr[offset*4 + 1] = (ptr[top+1]+ptr[bottom+1]+ptr[left+1]+ptr[right+1])/3;
	//		//ptr[offset*4 + 2] = (ptr[top+2]+ptr[bottom+2]+ptr[left+2]+ptr[right+2])/3 ;
	//		//ptr[offset*4 + 3] = 255;
	//	}
	//}

}

//int main()
//{
//	unsigned char *dst1;
//	dst1=(unsigned char *)malloc(sizeof(int));
//	
//	int w,h;
//	w=width;h=height;	
//	char *name="nature_monte.bmp";
//	LoadBMPFile(&dst1, &w,  &h, name);	 
//	CPUBitmap bitmap(2*w, h);
//	unsigned char *ptr = bitmap.get_ptr(); 
//	blur(ptr,dst1);
//	bitmap.display_and_exit(); 
//	free(dst1);
//
//}
