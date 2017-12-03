#if 1

#include "../common/book.h"
#include "../common/cpu_bitmap.h"
#include "cuda.h"
#include "../common/cpu_anim.h"

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
//__device__ int julia( int x, int y ) {
//    const float scale = 1.5;
//    float jx = scale * (float)(DIM/2 - x)/(DIM/2);
//    float jy = scale * (float)(DIM/2 - y)/(DIM/2);
//
//    //cuComplex c(-0.8, 0.156);
//	cuComplex c(-0.8, 0.156);//图像变换
//    cuComplex a(jx, jy);
//
//    int i = 0;
//    for (i=0; i<200; i++) {
//        a = a * a + c;
//        if (a.magnitude2() > 1000)
//            return 0;
//    }
//
//    return 1;
//}


__device__ int julia( int x, int y,int ticks ) {
    const float scale = 1.5;
    float jx = scale * (float)(DIM/2 - x)/(DIM/2);
    float jy = scale * (float)(DIM/2 - y)/(DIM/2);

	//角度旋转
	//double radian = ticks*PI/180;
	//float jx1 = jx*cos(radian)-jy*sin(radian);
	//float jx2 = jx*sin(radian)+jy*cos(radian);


    //cuComplex c(-0.8, 0.156);
	cuComplex c(-0.8, 0.156+ticks/1000.0);//图像变换
    cuComplex a(jx, jy);

    int i = 0;
    for (i=0; i<200; i++) {
        a = a * a + c;
        if (a.magnitude2() > 1000)
            return 0;
    }

    return 1;
}//以上为朱丽叶级数

struct DataBlock {
	unsigned char   *dev_bitmap;   //存储要涂色的区域
	CPUAnimBitmap  *bitmap;
};

__global__ void kernel( unsigned char *ptr,int ticks ) {
    // map from blockIdx to pixel position
    int x = threadIdx.x + blockIdx.x * blockDim.x;//(横)块内该线程索引+该块前所有索引块的线程数
    int y = threadIdx.y + blockIdx.y * blockDim.y;//(纵)块内该线程索引+该块前所有索引块的线程数
    int offset = x + y * blockDim.x * gridDim.x;  //二维转换成一维

    // now calculate the value at that position
    int juliaValue = julia( x, y ,ticks);
/*	ptr[offset * 4 + 0] = (255-ticks*20)* juliaValue;     
	ptr[offset * 4 + 1] = (100+ticks*20) *juliaValue;
	ptr[offset * 4 + 2] = (25+ticks*20) * juliaValue;	*/	

	ptr[offset*4 + 0] = (255) * juliaValue;
    ptr[offset*4 + 1] = 0;
    ptr[offset*4 + 2] = 0;
    ptr[offset*4 + 3] = 255;	


}
void generate_frame( DataBlock *d, int ticks ) {
    dim3    blocks(DIM/8,DIM/8);
    dim3    threads(8,8);

	/*dim3    blocks(DIM/16,DIM/16);
    dim3    threads(16,16);
*/
	//dim3 grid(DIM,DIM);
    //kernel<<<grid , 1>>>( d->dev_bitmap, ticks );
	kernel<<<blocks,threads>>>(  d->dev_bitmap, ticks );

    HANDLE_ERROR( cudaMemcpy( d->bitmap->get_ptr(),
                              d->dev_bitmap,
                              d->bitmap->image_size(),
                              cudaMemcpyDeviceToHost ) );
}
void cleanup( DataBlock *d ) {
    HANDLE_ERROR( cudaFree( d->dev_bitmap ) ); 
}

int main( void ) {
    DataBlock   data;
    CPUAnimBitmap  bitmap( DIM, DIM, &data );
    data.bitmap = &bitmap;

    HANDLE_ERROR( cudaMalloc( (void**)&data.dev_bitmap,
                              bitmap.image_size() ) );

    bitmap.anim_and_exit( (void (*)(void*,int))generate_frame,
                            (void (*)(void*))cleanup );
}
#endif