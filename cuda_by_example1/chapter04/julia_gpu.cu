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
#include"windows.h"
#include "../common/book.h"
#include "../common/cpu_bitmap.h"

#define DIM 1000


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

__global__ void kernel( unsigned char *ptr , int*  dev_ix, int*  dev_iy) {
    // map from blockIdx to pixel position
    //int x = blockIdx.x;
    //int y = blockIdx.y;
    //int offset = x + y * gridDim.x;//gridDim线程格每一维的大小
	*dev_ix = gridDim.x;//blockDim.x = 8;gridDim.x = 125
	*dev_iy = gridDim.y;//blockDim.y = 8;gridDim.y = 125

	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;

	int offset = x + y *gridDim.x * blockDim.x;
    // now calculate the value at that position
    int juliaValue = julia( x, y );
    ptr[offset*4 + 0] = 255 * juliaValue;
    ptr[offset*4 + 1] = 0;
    ptr[offset*4 + 2] = 0;
    ptr[offset*4 + 3] = 255;
}

// globals needed by the update routine
struct DataBlock {
    unsigned char   *dev_bitmap;
};

int main( void ) {
    DataBlock   data;
    CPUBitmap bitmap( DIM, DIM, &data );
    unsigned char    *dev_bitmap;

	int ix,iy;
	int* dev_ix;
	int* dev_iy;
	cudaMalloc((void**)&dev_ix,sizeof(int));
	cudaMalloc((void**)&dev_iy,sizeof(int));
    HANDLE_ERROR( cudaMalloc( (void**)&dev_bitmap, bitmap.image_size() ) );
    data.dev_bitmap = dev_bitmap;

    dim3    grid(DIM/8,DIM/8);
	dim3    threads(8,8);
    kernel<<<grid,threads>>>( dev_bitmap , dev_ix, dev_iy);

    HANDLE_ERROR( cudaMemcpy( bitmap.get_ptr(), dev_bitmap,
                              bitmap.image_size(),
                              cudaMemcpyDeviceToHost ) );
    cudaMemcpy(&ix,dev_ix,sizeof(int),cudaMemcpyDeviceToHost );    
	cudaMemcpy(&iy,dev_iy,sizeof(int),cudaMemcpyDeviceToHost );   
    HANDLE_ERROR( cudaFree( dev_bitmap ) );

/*	printf("=================");
     printf("%d  %d",ix,iy);  */                       
    bitmap.display_and_exit();
}

#endif