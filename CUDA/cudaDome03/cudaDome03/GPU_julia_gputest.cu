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

//���ϴ�julia_gpu������û�иĶ�

__global__ void kernel( unsigned char *ptr, int ticks ) {
	// map from blockIdx to pixel position
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x + y * gridDim.x;

	// now calculate the value at that position
	int juliaValue = julia(x, y);
	
	ptr[offset * 4 + 0] = (255-ticks*20)* juliaValue;       //��ɫ���������ڡ�  ÿ�ε��úͺ�����ticks�������� ticks����20��Ŀ���ǣ��ñ�ɫЧ�������ԡ�
	ptr[offset * 4 + 1] = (100+ticks*20) *juliaValue;
	ptr[offset * 4 + 2] = (25+ticks*20) * juliaValue;		//ǰ����ptr��RGB
	ptr[offset * 4 + 3] = 255;								//���һ��ptr��͸����alpha
}

struct DataBlock {                                  //��CPU��GPU�Ĵ洢�����໥����
    unsigned char   *dev_bitmap;
    CPUAnimBitmap  *bitmap;
};

void generate_frame(DataBlock *d, int ticks) {
	
   // dim3    blocks(DIM/16,DIM/16);
	dim3    grid(DIM, DIM);       
   // dim3    threads(16,16);
    //kernel<<<blocks,threads>>>( d->dev_bitmap, ticks );
	kernel << <grid, 1 >> >(d->dev_bitmap,ticks++);
	printf("%d", ticks);                //�˾��ڿ���̨��ʾticks��ֵ�����԰���ע�͵�
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
    data.bitmap = &bitmap;       ////////�໥ָ�����Ի������

    HANDLE_ERROR( cudaMalloc( (void**)&data.dev_bitmap,    //////data����ṹ����ֻ������ָ��
                              bitmap.image_size() ) );    

    bitmap.anim_and_exit( (void (*)(void*,int))generate_frame,    /////void(*)����ָ�룬generate_frame ��������֡///julia��ɫ
                            (void (*)(void*))cleanup );   /////cleanup ���

	
}
#endif