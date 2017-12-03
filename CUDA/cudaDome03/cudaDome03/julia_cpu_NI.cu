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
julia��������ĳ���������㺯�������е㹹�ɵı߽硣���ں�������������ȡֵ�����ɵı߽罫�γ�һ�ֲ��������Ƭ��״��������ѧ������Ȥ����Ư������״֮һ��
����julia���㷨�ǳ��򵥣�Julia���Ļ����㷨��,ͨ��һ���򵥵ĵ�����ʽ�Ը�ƽ���еĵ���ֵ��
����ڼ���ĳ����ʱ��������ʽ�ļ������Ƿ�ɢ�ģ���ô�����Ͳ�����Julia���ϣ�
�෴������ڵ�����ʽ�м���õ���һϵ��ֵ��λ��ĳ���߽緶Χ֮�ڣ���ô����������Julia���ϡ�
������ʽΪ��

	Z(n+1)=Z(n)*Z(n)+C

����GPU��Julia�����㷨���£�

*/

#include<windows.h>
#include "../common/book.h"
#include "../common/cpu_bitmap.h"

#define DIM 500

struct cuComplex {
    float   r;
    float   i;
    cuComplex( float a, float b ) : r(a), i(b)  {}
    float magnitude2( void ) { return r * r + i * i; }//��Ա������ģ��ƽ��
    cuComplex operator*(const cuComplex& a) {          //��Ա�����������˷�������
        return cuComplex(r*a.r - i*a.i, i*a.r + r*a.i);
    }
    cuComplex operator+(const cuComplex& a) {
        return cuComplex(r+a.r, i+a.i);
    }
};


int julia( int x, int y ) 
//�������ܣ�������ת��Ϊ����
{ 
    const float scale = 1.5;                         //&scale �ȼ����Ŵ�ϵ������ֵԽС��Խ�Ŵ�
    float jx = scale * (float)(DIM/2 - x)/(DIM/2);   //����������ת��Ϊ�����ռ������
    float jy = scale * (float)(DIM/2 - y)/(DIM/2);


    cuComplex c(-0.8, 0.156);        //&���������г���C�Ķ���
    cuComplex a(jx, jy);             //����������Z�����ĳ�ֵ

    int i = 0;
    for (i=0; i<100; i++) {          //$$$����200�ε���(��������Խ�࣬ͼ��Խ��ϸ)
        a = a * a + c;
        if (a.magnitude2() >1000)   //ģ��ƽ������1000����ֵ���Ļ�����˵����ɢ��������julia��
            return 0;
    }

    return 1;                //Z(a)����julia�����򷵼�1
}

/*��һ������kernel����Ϊһ��__global__ ���͵ĺ������̸߳�ÿһά��
��С��ͼ��ÿһά��С����ȵģ���Щ�ڣ�0��0��
�ͣ�DIM-1��DIM-1��֮���ÿ�����ص㶼�ܻ��һ���߳̿�
�ڶ������õ���� ������ptr�е�����ƫ�ƣ����ƫ����ͨ����һ��
���ñ���girdDim������ģ������е��߳̿���˵��gidDim��һ��������
���������̸߳��һά�Ĵ�С.��ʾ���У�gridDim��ֵ��(DIM,DIM), ��ˣ�
�������������̸߳�Ŀ��ټ������������͵õ���ptr�е�Ψһ������
��ȡֵ��ΧΪ��DIM*DIM-1����
�������ж�ĳ�����Ƿ�����Julia���Ĵ��롣
*/
/*
__global__ void kernel(unsigned char *ptr)
{
   //��threadIdx/BlockIdxӳ������λ��
    int x=blockIdx.x;
    int y=blockIdx.y;
    int offset=x+y*gridDim.x; //�̸߳�һά�Ĵ�С���Ǹ�����

    //�������λ���ϵ�ֵ
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
            int offset = x + y * DIM;//��һά��ʾͼ���е����е�

            int juliaValue = julia( x, y );
            ptr[offset*4 + 0] = 255 * juliaValue;   //R
            ptr[offset*4 + 1] = 0;					//G
            ptr[offset*4 + 2] = 0;				    //B
            ptr[offset*4 + 3] = 255;                //͸����
        }
    }
 }

//ͨ�����߿ⴴ��һ����С���ʵ�λͼͼ����һ��ָ��λͼ���ݵ�ָ�봫�ݸ��˺�����
int main( void ) {
    CPUBitmap bitmap( DIM, DIM );  //����λͼ����
	unsigned char *ptr = bitmap.get_ptr();//���������豸�����ݵĸ�����

    kernel( ptr );
	bitmap.display_and_exit();
	return 0;
}
#endif
#if 0
	/*ʱ���ʱ����*/
	LARGE_INTEGER t1,t2,tc;//����ʱ�����
	QueryPerformanceFrequency(&tc);//
	QueryPerformanceCounter(&t1);//
	��������
	QueryPerformanceCounter(&t2);//
	printf("Use Time:%f\n",(t2.QuadPart-t1.QuadPart)*1.0/tc.QuadPart);//��ӡ��ʱ

#endif