#if 1
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
/*
julia集是满足某个复数计算函数的所有点构成的边界。对于函数参数的所有取值，生成的边界将形成一种不规则的碎片形状，这是数学中最有趣和最漂亮的形状之一。
生成julia的算法非常简单，Julia集的基本算法是,通过一个简单的迭代等式对复平面中的点求值，
如果在计算某个点时，迭代等式的计算结果是发散的，那么这个点就不属于Julia集合，
相反，如果在迭代等式中计算得到的一系列值都位于某个边界范围之内，那么这个点就属于Julia集合。
迭代等式为：

	Z(n+1)=Z(n)*Z(n)+C

基于GPU的Julia集的算法如下：

*/

#include<windows.h>
#include "../common/book.h"
#include "../common/cpu_bitmap.h"

#define DIM 500

struct cuComplex {
    float   r;
    float   i;
    cuComplex( float a, float b ) : r(a), i(b)  {}
    float magnitude2( void ) { return r * r + i * i; }//成员函数，模的平方
    cuComplex operator*(const cuComplex& a) {          //成员函数，复数乘法的重载
        return cuComplex(r*a.r - i*a.i, i*a.r + r*a.i);
    }
    cuComplex operator+(const cuComplex& a) {
        return cuComplex(r+a.r, i+a.i);
    }
};


int julia( int x, int y ) 
//函数功能，将像素转换为得数
{ 
    const float scale = 1.5;                         //&scale 等级，放大系数（数值越小，越放大）
    float jx = scale * (float)(DIM/2 - x)/(DIM/2);   //将像素坐标转换为复数空间的坐标
    float jy = scale * (float)(DIM/2 - y)/(DIM/2);


    cuComplex c(-0.8, 0.156);        //&迭代函数中常量C的定义
    cuComplex a(jx, jy);             //迭代函数中Z变量的初值

    int i = 0;
    for (i=0; i<100; i++) {          //$$$进行200次迭代(迭代次数越多，图像越精细)
        a = a * a + c;
        if (a.magnitude2() >1000)   //模的平方大于1000（阈值）的话，则说明发散，不属于julia集
            return 0;
    }

    return 1;                //Z(a)属于julia集，则返加1
}

/*第一步：将kernel声明为一个__global__ 类型的函数。线程格每一维的
大小与图像每一维大小是相等的，因些在（0，0）
和（DIM-1，DIM-1）之间的每个像素点都能获得一个线程块
第二步：得到输出 缓冲区ptr中的线性偏移，这个偏移是通中另一个
内置变量girdDim来计算的，对所有的线程块来说，gidDim是一个常数，
用来保存线程格第一维的大小.在示例中，gridDim的值是(DIM,DIM), 因此，
将行索引乘以线程格的宽，再加上列索引，就得到了ptr中的唯一索引，
其取值范围为（DIM*DIM-1）。
最后分析判断某个点是否属于Julia集的代码。
*/
/*
__global__ void kernel(unsigned char *ptr)
{
   //将threadIdx/BlockIdx映身到像素位置
    int x=blockIdx.x;
    int y=blockIdx.y;
    int offset=x+y*gridDim.x; //线程格一维的大小，是个常量

    //计算这个位置上的值
    int juliaValue=julia(x,y);
 
     ptr[offset*4+0]=255*juliaValue;
     ptr[offset*4+1]=0;
     ptr[offset*4+2]=0;
     ptr[offset*4+3]=255;
}

*/
void kernel( unsigned char *ptr ){
    for (int y=0; y<DIM; y++) {
        for (int x=0; x<DIM; x++) {
            int offset = x + y * DIM;//用一维表示图像中的所有点

            int juliaValue = julia( x, y );
            ptr[offset*4 + 0] = 255 * juliaValue;   //R
            ptr[offset*4 + 1] = 0;					//G
            ptr[offset*4 + 2] = 0;				    //B
            ptr[offset*4 + 3] = 255;                //透明度
        }
    }
 }

//通过工具库创建一个大小合适的位图图像，用一个指向位图数据的指针传递给核函数。
int main( void ) {
    CPUBitmap bitmap( DIM, DIM );  //定义位图对象
	unsigned char *ptr = bitmap.get_ptr();//用来保存设备上数据的副本。

    kernel( ptr );
	bitmap.display_and_exit();
	return 0;
}
#endif
#if 0
	/*时间计时函数*/
	LARGE_INTEGER t1,t2,tc;//定义时间变量
	QueryPerformanceFrequency(&tc);//
	QueryPerformanceCounter(&t1);//
	…………
	QueryPerformanceCounter(&t2);//
	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//打印耗时

#endif