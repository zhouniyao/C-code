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


#ifndef __CPU_BITMAP_H__
#define __CPU_BITMAP_H__

#include "gl_helper.h"

struct CPUBitmap {
    unsigned char    *pixels;  /*���ص���ܸ���*/
    int     x, y;              /*ͼ��ĳ���*/
    void    *dataBlock;
    void (*bitmapExit)(void*); /*����һ������ */

    CPUBitmap( int width, int height, void *d = NULL ) {
       pixels = new unsigned char[width * height * 4];/*�����ܵ����ص������������µĿռ�*/
		
        x = width;                                     /*ͼ��Ŀ�*/
        y = height;                                    /*ͼ��ĸ�*/
        dataBlock = d;
    }

    ~CPUBitmap() {
        delete [] pixels;                               /*ɾ�����ص㶯̬����Ŀռ�*/
    }

    unsigned char* get_ptr( void ) const   { return pixels; }   /*ȡ���������ص�*/    
    long image_size( void ) const { return x * y * 4; }         /*ȡ��ͼƬ�ܴ�С*/


    void display_and_exit( void(*e)(void*) = NULL ) {
        CPUBitmap**   bitmap = get_bitmap_ptr();
        *bitmap = this;
        bitmapExit = e;
        // a bug in the Windows GLUT implementation prevents us from
        // passing zero arguments to glutInit()
        int c=1;
        char* dummy = "";
		 /*glutInit,�� GLUT (OpenGl �����һ�����߰��������ܶຯ��)���г�ʼ��,
		 ������������������� GLUTʹ��֮ǰ����һ�Ρ����ʽ�Ƚ�����,
		 һ���ճ����glutInit(&argc, argv)�Ϳ�����*/
        glutInit( &c, &dummy );
		 /*������ʾ��ʽ,���� GLUT_RGBA ��ʾʹ�� RGBA ��ɫ,��֮��Ӧ�Ļ���GLUT_INDEX(��ʾʹ��������ɫ) ��
		 GLUT_SINGLE ��ʾʹ�õ�����,����֮��Ӧ�Ļ��� GLUT_DOUBLE(ʹ��˫����)��*/    
        glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
        glutInitWindowSize( x, y );        /*���Ҳ��,���ô��ڵĴ�С*/
        glutCreateWindow( "bitmap" );      /*����ǰ�����õ���Ϣ�������ڡ�����������Ϊ���ڵı��⡣ע��:���ڱ�������,����������ʾ����Ļ�ϡ���Ҫ���� glutMainLoop ���ܿ������ڡ�*/
        glutKeyboardFunc(Key);             /* ������ͨ��������������Key����*/
        glutDisplayFunc(Draw);             /* ����һ������,����Ҫ���л�ͼʱ,��������ͻᱻ���á�*/
        glutMainLoop();                    /*��ʾ����*/ 
    }

     // static method used for glut callbacks
    static CPUBitmap** get_bitmap_ptr( void ) {
        static CPUBitmap   *gBitmap;
        return &gBitmap;
    }

   // static method used for glut callbacks
    static void Key(unsigned char key, int x, int y) {
        switch (key) {
            case 27:                        /* �������������Esc���������˳�����*/
                CPUBitmap*   bitmap = *(get_bitmap_ptr());
                if (bitmap->dataBlock != NULL && bitmap->bitmapExit != NULL)
                    bitmap->bitmapExit( bitmap->dataBlock );
                exit(0);
        }
    }

    // static method used for glut callbacks
    static void Draw( void ) {           /* ��ͼ */
        CPUBitmap*   bitmap = *(get_bitmap_ptr());
        glClearColor( 0.0, 0.0, 0.0, 1.0 );               /*���ñ�����ɫ*/
        glClear( GL_COLOR_BUFFER_BIT );                   /*�����GL_COLOR_BUFFER_BIT ��ʾ�����ɫ*/
        glDrawPixels( bitmap->x, bitmap->y, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->pixels ); /*�������ص�*/
        glFlush(); /*��֤ǰ��� OpenGL ��������ִ��(�������������ڻ������еȴ�)�������ø� fflush(stdout)���ơ�*/
    }
};

#endif  // __CPU_BITMAP_H__
