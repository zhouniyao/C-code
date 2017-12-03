
#define WIDTH 640
#define	HEIGHT 480
void fade( unsigned char *ptr ){
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            int offset = x + y * WIDTH;
			//int offset = x * WIDTH + y ;  //错误
	//从RGB色转为灰度公式：
	//Gray = R*0.299 + G*0.587 + B*0.114
            //ptr[offset*4 + 0] = ptr[offset*4 + 0]*0.299 + ptr[offset*4 + 1] *0.587 + ptr[offset*4 + 2] * 0.114 ;
            //ptr[offset*4 + 1] = ptr[offset*4 + 0]*0.299 + ptr[offset*4 + 1] *0.587 + ptr[offset*4 + 2] * 0.114 ;
            //ptr[offset*4 + 2] = ptr[offset*4 + 0]*0.299 + ptr[offset*4 + 1] *0.587 + ptr[offset*4 + 2] * 0.114 ;
			ptr[offset*4 + 0] = (ptr[offset*4 + 0] + ptr[offset*4 + 1]  + ptr[offset*4 + 2] )/3 ;
            ptr[offset*4 + 1] = (ptr[offset*4 + 0] + ptr[offset*4 + 1]  + ptr[offset*4 + 2] )/3 ;
            ptr[offset*4 + 2] = (ptr[offset*4 + 0] + ptr[offset*4 + 1]  + ptr[offset*4 + 2] )/3 ;
            ptr[offset*4 + 3] = 255;
        }
    }
 }