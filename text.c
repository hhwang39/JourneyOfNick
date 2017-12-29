//author:Hokyung Hwang
#include "mylib.h"
#include "text.h"
#include <stdlib.h>
#include <stdio.h>
#include "sprite3.h"
#include "myGame.h"
#include "sprite.h"
#include "sprite2.h"
const int fontPos[] = {FONT1_ID, FONT2_ID, FONT3_ID, FONT4_ID, FONT5_ID, FONT6_ID, FONT7_ID, FONT8_ID, FONT9_ID, FONT10_ID, FONT11_ID, FONT12_ID, FONT13_ID, FONT14_ID, FONT15_ID, FONT16_ID, FONT17_ID, FONT18_ID, FONT19_ID, FONT20_ID, FONT21_ID, FONT22_ID, FONT23_ID, FONT24_ID, FONT25_ID, FONT26_ID, FONT27_ID, FONT28_ID, FONT29_ID, FONT30_ID, FONT31_ID, FONT32_ID, FONT33_ID, FONT34_ID, FONT35_ID, FONT36_ID, FONT37_ID, FONT38_ID, FONT39_ID, FONT40_ID, FONT41_ID, FONT42_ID, FONT43_ID, FONT44_ID, FONT45_ID, FONT46_ID, FONT47_ID, FONT48_ID, FONT49_ID, FONT50_ID, FONT51_ID, FONT52_ID, FONT53_ID, FONT54_ID, FONT55_ID, FONT56_ID, FONT57_ID, FONT58_ID, FONT59_ID, FONT60_ID, FONT61_ID, FONT62_ID, FONT63_ID, FONT64_ID, FONT65_ID, FONT66_ID, FONT67_ID, FONT68_ID, FONT69_ID, FONT70_ID, FONT71_ID, FONT72_ID, FONT73_ID, FONT74_ID, FONT75_ID, FONT76_ID, FONT77_ID, FONT78_ID, FONT79_ID, FONT80_ID, FONT81_ID, FONT82_ID, FONT83_ID, FONT84_ID, FONT85_ID, FONT86_ID, FONT87_ID, FONT88_ID, FONT89_ID, FONT90_ID, FONT91_ID, FONT92_ID, FONT93_ID, FONT94_ID, FONT95_ID, FONT96_ID};
const int fontNumPos[] = {FONTW17_ID,FONTW18_ID, FONTW19_ID, FONTW20_ID, FONTW21_ID, FONTW22_ID, FONTW23_ID, FONTW24_ID, FONTW25_ID, FONTW26_ID};
const int fontNumPos2[] = {FONTWk17_ID,FONTWk18_ID, FONTWk19_ID, FONTWk20_ID, FONTWk21_ID, FONTWk22_ID, FONTWk23_ID, FONTWk24_ID, FONTWk25_ID, FONTWk26_ID};
void drawChar(int row, int col, char ch, unsigned short color)
{
    int r,c;
    for(r=0; r<8; r++)
    {
        for(c=0; c< 6; c++)
        {
            if(fontdata_6x8[OFFSET(r, c, 6)+48*ch])
            {
                setPixel(r+row, c+col, color);
            }
        }
    }
    
}

void drawString(int row, int col, char *str, unsigned short color)
{
    while(*str)
    {
        drawChar(row, col, *str++, color);
        col += 6;
    }
}
void drawNumber(int r, int c, int number, char* str, u16 color) {
    sprintf(str, "%d", number);
    drawString(r, c, str, color);
}      
void drawChar4(int row, int col, char ch, u8 index)
{
    int r, c;
    for(r=0; r<8; r++)
    {
        for(c=0; c<6; c++)
        {
            if(fontdata_6x8[OFFSET(r,c, 6)+ch*48])
            {
                setPixel4(row+r, col+c, index);
            }
        }
    }
}

void drawString4(int row, int col, char *str, u8 index)
{
    while(*str)
    {
        drawChar4(row, col, *str++, index);
        col += 6;
    }
}
/*
void initStrMap() {
    for (int i = 0; i < 1024; ++i) {
        font_Map[i] = i + 5;
    }
}*/
void setFont(int row, int col, char ch, ObjAttr* shadowOAM) {
    int pos = ch - ' ';
    static int p = 6;
    shadowOAM[p].attr0 = row | ATTR0_8BPP | FONT76_SHAPE;
    shadowOAM[p].attr1 = col | FONT76_SIZE;
    shadowOAM[p].attr2 = fontPos[pos] | SPRITE3_PALETTE_TYPE;
    p++;
    if (p > 128) {
        p = 1;
    }
}
void drawFontStr(int row, int col, char* str, ObjAttr* shadowOAM) {
    while (*str) {
        setFont(row, col, *str++, shadowOAM);
        col += 8;
    }
    DMAcopyMap(shadowOAM, SPRITEMEM, (128*sizeof(ObjAttr))>>1);
}
void setNum(int row, int col, char ch, ObjAttr* shadowOAM, int ind) {
    int pos = ch - '0';
    shadowOAM[ind].attr0 = row | ATTR0_8BPP | FONTW26_SHAPE;
    shadowOAM[ind].attr1 = col | FONTW26_SIZE;
    shadowOAM[ind].attr2 = fontNumPos[pos] | SPRITE_PALETTE_TYPE;
}
void drawNumFont(int row, int col, int num, ObjAttr* shadowOAM) {
    char lol[4];
    sprintf(lol, "%d", num);
    int k = 10;
    char* str = lol;
    for (int i = 10; i < 14; ++i) {
        shadowOAM[i].attr0 = ATTR0_HIDE;
    }
    while (*str) {
        setNum(row, col, *str++, shadowOAM, k);
        k = k + 1;
        col += 8;
    }
    DMAcopyMap(shadowOAM, SPRITEMEM, (16*sizeof(ObjAttr))>>1);
}
void setNum2(int row, int col, char ch, ObjAttr* shadowOAM, int ind) {
    int pos = ch - '0';
    shadowOAM[ind].attr0 = row | ATTR0_8BPP | FONTW26_SHAPE;
    shadowOAM[ind].attr1 = col | FONTW26_SIZE;
    shadowOAM[ind].attr2 = fontNumPos2[pos] | SPRITE_PALETTE_TYPE;
}
void drawNumFont2(int row, int col, int num, ObjAttr* shadowOAM) {
    char lol[4];
    sprintf(lol, "%d", num);
    int k = 10;
    char* str = lol;
    for (int i = 10; i < 14; ++i) {
        shadowOAM[i].attr0 = ATTR0_HIDE;
    }
    while (*str) {
        setNum2(row, col, *str++, shadowOAM, k);
        k = k + 1;
        col += 8;
    }
    DMAcopyMap(shadowOAM, SPRITEMEM, (16*sizeof(ObjAttr))>>1);
}