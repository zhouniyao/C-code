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


#include "cuda.h"
#include "../common/book.h"
#include "../common/cpu_anim.h"
#include <stdio.h>
#include <time.h>
#define DIM 1000
int count = 0;
clock_t start_time;
//#define PI 3.1415926535897932f

//__global__ void kernel( unsigned char *ptr, int ticks ) {
//    // map from threadIdx/BlockIdx to pixel position
//    int x = threadIdx.x + blockIdx.x * blockDim.x;
//    int y = threadIdx.y + blockIdx.y * blockDim.y;
//    int offset = x + y * blockDim.x * gridDim.x;
//
//    // now calculate the value at that position
//    float fx = x - DIM/2;
//    float fy = y - DIM/2;
//    float d = sqrtf( fx * fx + fy * fy );
//    unsigned char grey = (unsigned char)(128.0f + 127.0f *
//                                         cos(d/10.0f - ticks/7.0f) /
//                                         (d/10.0f + 1.0f));
//    ptr[offset*4 + 0] = grey;
//    ptr[offset*4 + 1] = grey;
//    ptr[offset*4 + 2] = grey;
//    ptr[offset*4 + 3] = 255;
//}
struct cuComplex {
    float   r;
    float   i;
    __device__ cuComplex( float a, float b ) : r(a), i(b)  {}
    __device__ float magnitude2( void ) {
        return r * r + i * i;
    }
    __device__ cuComplex operator*(const cuComplex& a) {
        return cuComplex(r*a.r - i*a.i, i*a.r + r*a.i);
    }
    __device__ cuComplex operator+(const cuComplex& a) {
        return cuComplex(r+a.r, i+a.i);
    }
};
__device__ int julia( int x, int y ) {
    const float scale = 1.5;
    float jx = scale * (float)(DIM/2 - x)/(DIM/2);
    float jy = scale * (float)(DIM/2 - y)/(DIM/2);

    cuComplex c(-0.8, 0.156);
    cuComplex a(jx, jy);

    int i = 0;
    for (i=0; i<200; i++) {
        a = a * a + c;
        if (a.magnitude2() > 1000)
            return 0;
    }

    return 1;
}
__global__ void kernel2( unsigned char *ptr ,int rand) {
    // map from blockIdx to pixel position
    int x = blockIdx.x;
    int y = blockIdx.y;
    int offset = x + y * gridDim.x;

    // now calculate the value at that position
    int juliaValue = julia( x, y );
    ptr[offset*4 + 0] = juliaValue*rand;
    ptr[offset*4 + 1] = 0;
    ptr[offset*4 + 2] = 0;
    ptr[offset*4 + 3] = 255;
}
struct DataBlock {
    unsigned char   *dev_bitmap;
    CPUAnimBitmap  *bitmap;
};

void generate_frame( DataBlock *d, int ticks ) {
	static int times = 1;
	times = times+10;
	times = times%255+1;

	count ++ ;
	if((double)(clock()-start_time) / CLOCKS_PER_SEC > 1.0 ){
		printf("fps:%d\n",count);
		start_time = clock();
		count = 0;
	}
    dim3    grid(DIM,DIM);
    kernel2<<<grid,1>>>( d->dev_bitmap ,times);
    HANDLE_ERROR( cudaMemcpy( d->bitmap->get_ptr(),
                              d->dev_bitmap,
                              d->bitmap->image_size(),
                              cudaMemcpyDeviceToHost ) );
}

// clean up memory allocated on the GPU
void cleanup( DataBlock *d ) {
    HANDLE_ERROR( cudaFree( d->dev_bitmap ) ); 
}

int main( void ) {

    DataBlock   data;
    CPUAnimBitmap  bitmap( DIM, DIM, &data );
    data.bitmap = &bitmap;

    HANDLE_ERROR( cudaMalloc( (void**)&data.dev_bitmap,
                              bitmap.image_size() ) );
    start_time = clock();
    bitmap.anim_and_exit( (void (*)(void*,int))generate_frame,
                            (void (*)(void*))cleanup );
}
