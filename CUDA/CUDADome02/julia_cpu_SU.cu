/*
* Copyright 1993-2010 NVIDIA Corporation.  All rights reserved.
*
* NVIDIA Corporation and its licensors retain all intellectual property and
* proprietary rights in and to this software and related documentation.
* Any use, reproduction, disclosure, or distribution of this software
* and related documentation without an express license agreement from
* NVIDIA Corporation is strictly prohibited.
*
* Please refer to the applicable NVIDIA end user license agreement (EULA)
* associated with this source code for terms and conditions that govern
* your use of this NVIDIA software.
*
*/


#include "../common/book.h"
#include "cpu_bitmaptest.h"    //引用cpu_bitmap的副本

#define DIM 1000



struct cuComplex {
	float   r;
	float   i;
	cuComplex(float a, float b) : r(a), i(b)  {}
	float magnitude2(void) { return r * r + i * i; }
	cuComplex operator*(const cuComplex& a) {
		return cuComplex(r*a.r - i*a.i, i*a.r + r*a.i);
	}
	cuComplex operator+(const cuComplex& a) {
		return cuComplex(r + a.r, i + a.i);
	}
};

int julia(int x, int y) {
	const float scale = 1.5;
	float jx = scale * (float)(DIM / 2 - x) / (DIM / 2);
	float jy = scale * (float)(DIM / 2 - y) / (DIM / 2);

	cuComplex c(-0.8, 0.156);
	cuComplex a(jx, jy);

	int i = 0;
	for (i = 0; i<200; i++) {
		a = a * a + c;
		if (a.magnitude2() > 1000)
			return 0;
	}

	return 1;
}
///以上为朱丽叶级数相关，原模原样复制过来，不用改动


//DataBlock的作用是在各个函数之间传递图像的内存
struct DataBlock {
	unsigned char   *dev_bitmap;   //存储要涂色的区域
	CPUBitmap  *bitmap;
};


void kernel(unsigned char *ptr,int ticks){
	printf("kernel:%d\n",ticks);
	for (int y = 0; y<DIM; y++) {
		for (int x = 0; x<DIM; x++) {
			int offset = x + y * DIM;
			int juliaValue = julia(x, y);
			ptr[offset * 4 + 0] = (255-ticks*10) * juliaValue;  
			ptr[offset * 4 + 1] = (0 + ticks * 15)* juliaValue;
			ptr[offset * 4 + 2] = (100 + ticks * 25)* juliaValue;  //前三个ptr用来上色，为了让变色更明显，所以令ticks乘以一个值
			ptr[offset * 4 + 3] = 255;  //决定透明度
		}
	}
}


//不断变色
void generate_frame(DataBlock *d, int ticks) {
	unsigned char *ptr =  d->dev_bitmap;  //获取图像像素点的内存地址
	kernel(ptr, ticks);  //这儿是生成图像的核函数
}


void cleanup(DataBlock *d) {
	free(d->dev_bitmap);   
}
int main(void) {
	DataBlock data;
	CPUBitmap bitmap(DIM, DIM,&data);
	data.bitmap = &bitmap;
	data.dev_bitmap = bitmap.get_ptr();
	//unsigned char *ptr =bitmap.get_ptr();

	//kernel(ptr,1);
	//printf("frame:%p\n", generate_frame); 
	bitmap.display_and_exit((void(*)(void*, int))generate_frame,
		(void(*)(void*))cleanup);
}

