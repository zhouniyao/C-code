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
    unsigned char    *pixels;  /*像素点的总个数*/
    int     x, y;              /*图像的长宽*/
    void    *dataBlock;
    void (*bitmapExit)(void*); /*这是一个函数 */

    CPUBitmap( int width, int height, void *d = NULL ) {
       pixels = new unsigned char[width * height * 4];/*计算总的像素点数，并分配新的空间*/
		
        x = width;                                     /*图像的宽*/
        y = height;                                    /*图像的高*/
        dataBlock = d;
    }

    ~CPUBitmap() {
        delete [] pixels;                               /*删除像素点动态分配的空间*/
    }

    unsigned char* get_ptr( void ) const   { return pixels; }   /*取得所有像素点*/    
    long image_size( void ) const { return x * y * 4; }         /*取得图片总大小*/


    void display_and_exit( void(*e)(void*) = NULL ) {
        CPUBitmap**   bitmap = get_bitmap_ptr();
        *bitmap = this;
        bitmapExit = e;
        // a bug in the Windows GLUT implementation prevents us from
        // passing zero arguments to glutInit()
        int c=1;
        char* dummy = "";
		 /*glutInit,对 GLUT (OpenGl 里面的一个工具包，包含很多函数)进行初始化,
		 这个函数必须在其它的 GLUT使用之前调用一次。其格式比较死板,
		 一般照抄这句glutInit(&argc, argv)就可以了*/
        glutInit( &c, &dummy );
		 /*设置显示方式,其中 GLUT_RGBA 表示使用 RGBA 颜色,与之对应的还有GLUT_INDEX(表示使用索引颜色) ；
		 GLUT_SINGLE 表示使用单缓冲,。与之对应的还有 GLUT_DOUBLE(使用双缓冲)。*/    
        glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
        glutInitWindowSize( x, y );        /*这个也简单,设置窗口的大小*/
        glutCreateWindow( "bitmap" );      /*根据前面设置的信息创建窗口。参数将被作为窗口的标题。注意:窗口被创建后,并不立即显示到屏幕上。需要调用 glutMainLoop 才能看到窗口。*/
        glutKeyboardFunc(Key);             /* 当有普通按键被按，调用Key函数*/
        glutDisplayFunc(Draw);             /* 设置一个函数,当需要进行画图时,这个函数就会被调用。*/
        glutMainLoop();                    /*显示窗口*/ 
    }

     // static method used for glut callbacks
    static CPUBitmap** get_bitmap_ptr( void ) {
        static CPUBitmap   *gBitmap;
        return &gBitmap;
    }

   // static method used for glut callbacks
    static void Key(unsigned char key, int x, int y) {
        switch (key) {
            case 27:                        /* 如果按键按的是Esc按键，则退出程序。*/
                CPUBitmap*   bitmap = *(get_bitmap_ptr());
                if (bitmap->dataBlock != NULL && bitmap->bitmapExit != NULL)
                    bitmap->bitmapExit( bitmap->dataBlock );
                exit(0);
        }
    }

    // static method used for glut callbacks
    static void Draw( void ) {           /* 画图 */
        CPUBitmap*   bitmap = *(get_bitmap_ptr());
        glClearColor( 0.0, 0.0, 0.0, 1.0 );               /*设置背景颜色*/
        glClear( GL_COLOR_BUFFER_BIT );                   /*清除。GL_COLOR_BUFFER_BIT 表示清除颜色*/
        glDrawPixels( bitmap->x, bitmap->y, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->pixels ); /*绘制像素点*/
        glFlush(); /*保证前面的 OpenGL 命令立即执行(而不是让它们在缓冲区中等待)。其作用跟 fflush(stdout)类似。*/
    }
};

#endif  // __CPU_BITMAP_H__
