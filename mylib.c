/*author: Hokyung Hwang*/
#include "mylib.h"
unsigned short *videoBuffer = (unsigned short *)0x6000000;
void plotLine(int x0, int y0, int x1, int y1, u16 color) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	int D = (dy << 1) - dx;
	setPixel(y0,x0, color);
	int y = y0;
	int x;
	for (x = x0 + 1; x < x1 + 1; x++) {
		if (D > 0) {
			y = y + 1;
			setPixel(y, x, color);
			D = D + (dy << 1) - (dx << 1);
		} else {
			setPixel(y, x, color);
			D = D + (dy << 1);
		}
	}
}
void setPixel(int r, int c, u16 color) {
	*(videoBuffer + OFFSET(r,c, 240)) = color;
}
void drawRect(int r, int c, int width, int height, u16 color) {
	int i, j;
	for (i = r; i <= r + height; ++i) {
		for (j = c; j <= c + width; ++j) {
			setPixel(i, j, color);
		}
	}
}
void drawHollowRect(int r, int c, int width, int height, u16 color) {
	int i,j;
	int jj = c;
	int ii = r;
	int ii2 = r + height;
	int jj2 = c + width;
	for (i = r; i <= r + height; ++i) {
		setPixel(i, jj, color);
		setPixel(i, jj2, color);
	}
	for (j = c; j <= c + width; ++j) {
		setPixel(ii, j, color);
		setPixel(ii2, j, color);
	}
}
void clear() {
	int k, m;
	for (k = 0; k < 160; ++k) {
		for (m = 0; m < 240; ++m) {
			setPixel(k, m, 0);
		}
	}
}
u16 chooseColor(int count) {
	if (count == 0) {
		return RGB(31, 0, 0);
	} else if (count == 1) {
		return RGB(0, 31, 0);
	} else if (count == 2) {
		return RGB(0, 0, 31);
	} else if (count == 3) {
		return RGB(31, 31, 31);
	} else if (count == 4) {
		return RGB(0, 31, 0);
	} else if (count == 5) {
		return RGB(31, 31, 0);
	} else if (count == 6){
		return RGB(31, 0, 31);
	} else if (count == 7){
		return RGB(0, 31, 31);
	} else if (count == 8) {
		return RGB(25, 2, 15);
	} else if (count == 9) {
		return RGB(5, 7, 16);
	}
	return RGB(0, 0, 0);
}
void waitForvBlank() {
	while (SCOUNTER >= 160);
	while (SCOUNTER < 160);
}
void delay(int n) {
	volatile int x = 0;
	while (x < n * 10000) x++;
}
void drawDMAImg(const u16* img, int row, int col, int width, int height) {
	int r;
	for (r = 0; r < height; ++r) {
		DMA[3].src = &(img[OFFSET(r, 0, width)]);
		DMA[3].dst = &(videoBuffer[OFFSET(row + r, col, 240)]);
		DMA[3].cnt = width | DMA_ON;
	}
}
void eraseDMAImg(volatile u16 color, int row, int col, int width, int height) {
	int r;
	for (r = 0; r < height; ++r) {
		DMA[3].src = &color;
		DMA[3].dst = &(videoBuffer[OFFSET(row + r, col, 240)]);
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}
void drawDMABDImg(const u16* img) {
	DMA[3].src = img;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = SCREENSIZE | DMA_ON;
}
void drawDMAcolor(volatile u16 color) {
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = SCREENSIZE | DMA_ON | DMA_SOURCE_FIXED;
}
void drawDMAtext(volatile u16 color) {
	DMA[3].src = &color;
	DMA[3].dst = &videoBuffer[OFFSET(140, 0, 240)];
	DMA[3].cnt = 4800 | DMA_ON | DMA_SOURCE_FIXED;
}
void FlipPage() {
    if(REG_DIPCNT & BUFFER1FLAG)
    {
        // Bit was on so we were displaying BUFFER1
        REG_DIPCNT = REG_DIPCNT & (~BUFFER1FLAG);
        videoBuffer = BUFFER1;
    }
    else
    {
        REG_DIPCNT = REG_DIPCNT | BUFFER1FLAG;
        videoBuffer = BUFFER0;
    }
}
void drawMode4Img(const u16* img, int row, int col, int height, int width) {
	for (int i = 0; i < height; ++i) {
		DMA[3].src = &img[OFFSET(i, 0, width>>1)];
		DMA[3].dst = videoBuffer + (OFFSET(i + row, col, 240) >> 1);
		DMA[3].cnt = DMA_ON | (width >> 1) | DMA_16;
	}
}
void drawMode4ImgSprite(const u16* img, int row, int col, int height, int width, int imgHeight, int imgWidth, int idX, int idY) {
	for (int i = 0; i < imgHeight; ++i) {
		DMA[3].src = &img[OFFSET(i, imgWidth * idX, width>>1) + (width>>1)*idY*imgHeight];
		DMA[3].dst = videoBuffer + (OFFSET(i + row, col, 240) >> 1);
		DMA[3].cnt = DMA_ON | (imgWidth >> 1) | DMA_16;
	}
}
void drawRect4(int row, int col, int height, int width, unsigned char index)
{
    volatile int color = index << 8 | index;
    int r;
    for(r=0; r<height; r++)
    {
        DMA[3].src = &color;
        DMA[3].dst = videoBuffer + OFFSET(row+r, col, 240)/2;
        DMA[3].cnt = (width/2) | DMA_ON | DMA_SOURCE_FIXED;
    }
}
void drawMode4Screen(u8 index) {
	volatile u16 color = index << 8 | index;
	DMA[3].src = &color;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = ((240*160)>>1) | DMA_SOURCE_FIXED | DMA_ON;
}
void drawMode4BD(const u16* img) {
	DMA[3].src = img;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = ((240*160)>>1) | DMA_SOURCE_FIXED | DMA_ON;
}
void setPixel4(int row, int col, u8 index)
{
	int pixel = OFFSET(row, col, 240);
	int shrt = pixel/2;
	if(col & 1)
	{
		// column is odd
		videoBuffer[shrt] = (videoBuffer[shrt] & 0x00FF) | (index<<8);
	}
	else
	{
		// column is even
		videoBuffer[shrt] = (videoBuffer[shrt] & 0xFF00) | (index);
	}
}
void DMAcopyMap(const void* srca, void* dsta, int lengtha) {
	DMA[3].src = srca;
	DMA[3].dst = dsta;
	DMA[3].cnt = DMA_ON | lengtha;
}

