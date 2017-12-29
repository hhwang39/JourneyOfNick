/*author: Hokyung Hwang*/
#include "type.h"
typedef struct {
	const volatile void *src;
	volatile void *dst;
	volatile unsigned int cnt;
} DMAREC;
extern u16* videoBuffer;
#define RGB(r, g, b) ((r) | ((g)<<5) | ((b)<<10))
#define OFFSET(r, c, x) ((x)*(r) + (c))
#define REG_DIPCNT	*(unsigned short *) 0x4000000
#define MODE 3
#define MODE4 4
#define BUFFER1FLAG (1<<4)
#define BUFFER0 (unsigned short *)0x6000000
#define BUFFER1 (unsigned short *)0x600A000
// Modes
#define MODE0 0
#define MODE3 3
#define MODE4 4

// Backgrounds
#define BG0_ENABLE (1<<8)
#define BG1_ENABLE (1<<9)
#define BG2_ENABLE (1<<10)
#define BG3_ENABLE (1<<11)
#define Sp_ON (1 << 12)
#define WHITE RGB(31, 31, 31)
#define BLUE RGB(0, 0, 31)
#define PALETTE ((unsigned short *)0x5000000)
#define RED RGB(31, 0, 0)
#define BLACK 0
#define REG_KEYINPUT *(volatile unsigned int *) 0x4000130
#define REG_KEYCNT *(unsigned int *) 0x4000132
#define KEY_EN (1 << 14)
#define KEY_DOWN_NOW(key) (~(REG_KEYINPUT) & key)
#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200
#define REG_IME *(u16*) 0x4000208
#define REG_IE *(u16*) 0x4000200
#define SCOUNTER *(volatile u16*) 0x4000006
#define DMA ((volatile DMAREC *)0x040000B0)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)
#define SCREENSIZE 38400

//background offset registers
#define REG_BG0HOFS *(volatile unsigned short *)0x04000010
#define REG_BG1HOFS *(volatile unsigned short *)0x04000014
#define REG_BG2HOFS *(volatile unsigned short *)0x04000018
#define REG_BG3HOFS *(volatile unsigned short *)0x0400001C

#define REG_BG0VOFS *(volatile unsigned short *)0x04000012
#define REG_BG1VOFS *(volatile unsigned short *)0x04000016
#define REG_BG2VOFS *(volatile unsigned short *)0x0400001A
#define REG_BG3VOFS *(volatile unsigned short *)0x0400001E

typedef struct { u16 tileimg[8192]; } charblock;
typedef struct { u16 tilemap[1024]; } screenblock;
//macros and bit constants for setting the background control register specifics
#define SBB(num) num << 8
#define CBB(num) num << 2
#define COLOR256 1 << 7
#define BG_SIZE0 0<<14      // 32 x 32 tiles
#define BG_SIZE1 1<<14      // 64 x 32
#define BG_SIZE2 2<<14      // 32 x 64
#define BG_SIZE3 3<<14      // 64 x 64

#define CHARBLOCKBASE ((charblock *)0x6000000)
#define SCREENBLOCKBASE ((screenblock *)0x6000000)

//background control registers
#define REG_BG0CNT *(volatile unsigned short*)0x4000008
#define REG_BG1CNT *(volatile unsigned short*)0x400000A
#define REG_BG2CNT *(volatile unsigned short*)0x400000C
#define REG_BG3CNT *(volatile unsigned short*)0x400000E


typedef struct {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 fill;
} ObjAttr;

//Sprite definitions
#define SPRITEMEM  ((ObjAttr *)0x7000000)
#define SPRITEDATA ((u16 *)(0x6010000) )
#define SPRITEPAL  ((u16 *)0x5000200)
#define OBJ_ENABLE 0x1000
#define MODE1D (1<<6)

// ATTR0

// 0-7 Row position of the top of the sprite.

// 8-9 Object Mode
#define ATTR0_REG (0<<8)
#define ATTR0_AFF (1<<8)
#define ATTR0_HIDE (2<<8)
#define ATTR0_AFF_DBL (3<<8)

// 10-11 Graphics Mode for special effects
#define ATTR0_BLEND (1<<10) // Forbidden to use both of these
#define ATTR0_WIN (2<<10)
#define ATTR2_PALETTE_BANK(pbn) ((pbn)<<12)
// 12 Mosaic Effect
#define ATTR0_MOSAIC (1<<12)
//mosaic reg
#define REG_MOSAIC *(volatile unsigned short *) 0x400004C
#define MOSOBJSTRE(num) (num << 8)
#define MOSOBJVSTRE(num) (num << 12)
#define BDMOS(num) (num << 4)
#define BDMOSH(num) (num)
// 13 Color Mode
#define ATTR0_4BPP 0          // 16 colors
#define ATTR0_8BPP (1<<13)    // 256 colors

// 14-15 Shape
#define ATTR0_SQUARE 0
#define ATTR0_WIDE (1<<14)
#define ATTR0_TALL (2<<14)
#define ATTR1_SIZE8 0
#define ATTR1_SIZE16 (1<<14)
#define ATTR1_SIZE32 (2<<14)
#define ATTR1_SIZE64 (3<<14)
void setPixel(int, int ,u16);
void drawRect(int, int, int, int, u16);
void drawHollowRect(int, int, int, int, u16);
void plotLine(int, int, int, int, u16);
void clear();
void delay(int);
void waitForvBlank();
u16 chooseColor(int);
void drawDMAImg(const u16*, int, int, int, int);
void eraseDMAImg(volatile u16, int, int, int, int);
void drawDMABDImg(const u16*);
void drawDMAcolor(volatile u16);
void drawDMAtext(volatile u16);
void FlipPage();
void drawMode4Img(const u16* img, int row, int col, int height, int width);
void drawMode4ImgSprite(const u16* img, int row, int col, int height, int width, int imgHeight, int imgWidth, int idX, int idY);
void drawRect4(int row, int col, int height, int width, unsigned char index);
void drawMode4Screen(u8 idx);
void drawMode4BD(const u16* img);
void setPixel4(int row, int col, u8 index);
void DMAcopyMap(const void* src, void* dst, int length);

