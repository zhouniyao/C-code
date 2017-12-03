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

clock_t start_time;
int frame_count = 0;

__global__ void kernel(unsigned char *ptr, int ticks)
{
    // map from threadIdx/BlockIdx to pixel position
    int x = blockIdx.x;
    int y = blockIdx.y;
    int offset = x + y * gridDim.x;

    int ty = ticks / gridDim.x;
    int tx = ticks % gridDim.x;

    if ((int) sqrtf(
            (float) pow((float) (tx - x), 2.0f)
                    + (float) pow((float) ty - y, 2.0f)) < 10)
    {
        unsigned char old_red = ptr[offset * 4 + 0];
        unsigned char old_green = ptr[offset * 4 + 1];
        unsigned char old_blue = ptr[offset * 4 + 2];

        //Gray=(R*30+G*59+B*11)/100
        //unsigned int grey = (unsigned int)(old_red*30+old_green*59+old_blue*11+50)/100;
        unsigned int grey = (int)((old_red+old_green+old_blue)/3.0+0.5);
        //unsigned char grey = 50;
        ptr[offset * 4 + 0] = grey;
        ptr[offset * 4 + 1] = grey;
        ptr[offset * 4 + 2] = grey;
        ptr[offset * 4 + 3] = 255;
        //*(unsigned int *)(ptr+offset*4) = grey;
    }

}

struct DataBlock
{
    unsigned char *dev_bitmap;
    CPUAnimBitmap *bitmap;
};

void generate_frame(DataBlock *d, int ticks)
{
    int w = d->bitmap->width;
    int h = d->bitmap->height;
    dim3 blocks(w, h);
    kernel<<<blocks, 1>>>(d->dev_bitmap, ticks);

    HANDLE_ERROR(
            cudaMemcpy(d->bitmap->get_ptr(), d->dev_bitmap,
                    d->bitmap->image_size(), cudaMemcpyDeviceToHost));

    ++frame_count;
    if ((double) (clock() - start_time) / CLOCKS_PER_SEC > 1.0)
    {
        printf("the fps is:%d\n", frame_count);
        frame_count = 0;
        start_time = clock();
    }
}

// clean up memory allocated on the GPU
void cleanup(DataBlock *d)
{
    HANDLE_ERROR(cudaFree(d->dev_bitmap));
}

int main(void)
{
    DataBlock data;
    start_time = clock();
    CPUAnimBitmap bitmap("/home/ct/Pictures/b16.bmp", &data);
    data.bitmap = &bitmap;
    HANDLE_ERROR(cudaMalloc((void** )&data.dev_bitmap, bitmap.image_size()));
    HANDLE_ERROR(
            cudaMemcpy(data.dev_bitmap, bitmap.get_ptr(), bitmap.image_size(),
                    cudaMemcpyHostToDevice));
    bitmap.anim_and_exit((void (*)(void*, int))generate_frame, (void (*)(void*))cleanup );
}
