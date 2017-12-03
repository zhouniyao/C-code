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

#if 0
#include "cuda.h"
#include "../common/book.h"
#include "../common/cpu_anim.h"


#define DIM 1000
#define PI 3.1415926535897932f


struct cuComplex {
	float   r;
	float   i;
	__device__ cuComplex(float a, float b) : r(a), i(b)  {}
	__device__ float magnitude2(void) {
		return r * r + i * i;
	}
	__device__ cuComplex operator*(const cuComplex& a) {
		return cuComplex(r*a.r - i*a.i, i*a.r + r*a.i);
	}
	__device__ cuComplex operator+(const cuComplex& a) {
		return cuComplex(r + a.r, i + a.i);
	}
};

__device__ int julia(int x, int y) {
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

//以上从julia_gpu搬来，没有改动

__global__ void kernel( unsigned char *ptr, int ticks ) {
	// map from blockIdx to pixel position
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x + y * gridDim.x;

	// now calculate the value at that position
	int juliaValue = julia(x, y);
	
	ptr[offset * 4 + 0] = (255-ticks*20)* juliaValue;       //变色的秘密所在。  每次调用和函数，ticks都自增。 ticks乘以20的目的是，让变色效果更明显。
	ptr[offset * 4 + 1] = (100+ticks*20) *juliaValue;
	ptr[offset * 4 + 2] = (25+ticks*20) * juliaValue;		//前三个ptr是RGB
	ptr[offset * 4 + 3] = 255;								//最后一个ptr是透明度alpha
}

struct DataBlock {                                  //让CPU和GPU的存储可以相互访问
    unsigned char   *dev_bitmap;
    CPUAnimBitmap  *bitmap;
};

void generate_frame(DataBlock *d, int ticks) {
	
   // dim3    blocks(DIM/16,DIM/16);
	dim3    grid(DIM, DIM);       
   // dim3    threads(16,16);
    //kernel<<<blocks,threads>>>( d->dev_bitmap, ticks );
	kernel << <grid, 1 >> >(d->dev_bitmap,ticks++);
	printf("%d", ticks);                //此句在控制台显示ticks的值，可以把它注释掉
    HANDLE_ERROR( cudaMemcpy( d->bitmap->get_ptr(),
                              d->dev_bitmap,
                              d->bitmap->image_size(),
                              cudaMemcpyDeviceToHost ) );

	/*HANDLE_ERROR(cudaMemcpy(bitmap.get_ptr(), dev_bitmap,
		bitmap.image_size(),
		cudaMemcpyDeviceToHost));*/
}

// clean up memory allocated on the GPU
void cleanup( DataBlock *d ) {
    HANDLE_ERROR( cudaFree( d->dev_bitmap ) ); 
	//HANDLE_ERROR(cudaFree(dev_bitmap));
}

int main( void ) {
    DataBlock   data;
    CPUAnimBitmap  bitmap( DIM, DIM, &data );
    data.bitmap = &bitmap;       ////////相互指，可以互相访问

    HANDLE_ERROR( cudaMalloc( (void**)&data.dev_bitmap,    //////data这个结构体里只有两个指针
                              bitmap.image_size() ) );    

    bitmap.anim_and_exit( (void (*)(void*,int))generate_frame,    /////void(*)函数指针，generate_frame 产生动画帧///julia换色
                            (void (*)(void*))cleanup );   /////cleanup 清除

	
}
#endif