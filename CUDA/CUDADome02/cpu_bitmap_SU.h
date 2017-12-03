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

#include "../common/gl_helper.h"

struct CPUBitmap {
	unsigned char    *pixels;
	int     x, y;
	void    *dataBlock;
	void(*bitmapExit)(void*);
	void(*fAnim)(void*, int);/////用来存储图像的地址

	CPUBitmap(int width, int height, void *d) { //最后一个参数d不再是NULL
		pixels = new unsigned char[width * height * 4];
		x = width;
		y = height;
		dataBlock = d;
	}

	~CPUBitmap() {
		delete[] pixels;
	}

	unsigned char* get_ptr(void) const   { return pixels; }
	long image_size(void) const { return x * y * 4; }

	void display_and_exit(void(*f)(void*, int), void(*e)(void*)) {
		CPUBitmap**   bitmap = get_bitmap_ptr();
		*bitmap = this;
		bitmapExit = e;
		fAnim = f;     //传递图像地址
		//printf("f:%p\n", f);
		// a bug in the Windows GLUT implementation prevents us from
		// passing zero arguments to glutInit()
		int c = 1;
		char* dummy = "";
		glutInit(&c, &dummy);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
		glutInitWindowSize(x, y);
		glutCreateWindow("bitmap");
		glutKeyboardFunc(Key);
		glutDisplayFunc(Draw);
		glutIdleFunc(idle_func);   //增加闲置回调函数
		glutMainLoop();
	}

	// static method used for glut callbacks
	static CPUBitmap** get_bitmap_ptr(void) {
		static CPUBitmap   *gBitmap;
		return &gBitmap;
	}

	// static method used for glut callbacks
	static void Key(unsigned char key, int x, int y) {
		switch (key) {
		case 27:
			CPUBitmap*   bitmap = *(get_bitmap_ptr());
			if (bitmap->dataBlock != NULL && bitmap->bitmapExit != NULL)
				bitmap->bitmapExit(bitmap->dataBlock);
			exit(0);
		}
	}

	// static method used for glut callbacks
	static void Draw(void) {
		CPUBitmap*   bitmap = *(get_bitmap_ptr());
		//printf("draw:%p\n", *bitmap);
		//bitmap->fAnim(bitmap->dataBlock,1);
		glClearColor(1.0, 1.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawPixels(bitmap->x, bitmap->y, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->pixels);
		glFlush();
	}

	static void idle_func(void) {
		static int ticks = 1;
		CPUBitmap*   bitmap = *(get_bitmap_ptr());
		bitmap->fAnim(bitmap->dataBlock, ticks++);   //不断画图
		glutPostRedisplay();
		//printf("idle:%d\n", ticks);
	}
};

#endif  // __CPU_BITMAP_H__
