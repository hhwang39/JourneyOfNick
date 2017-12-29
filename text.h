//author:Hokyung Hwang

extern const unsigned char fontdata_6x8[12288];
#define NUMPL 1
extern const int fontPos[];
void drawChar(int row, int col, char ch, unsigned short color);

void drawNumber(int r, int c, int number, char* str, u16 color);
void drawString(int row, int col, char *str, unsigned short color);
void drawChar4(int row, int col, char ch, u8 index);
void drawString4(int row, int col, char *str, u8 index);
void setFont(int row, int col, char ch, ObjAttr* shadowOAM);
void drawFontStr(int row, int col, char* str, ObjAttr* shadowOAM);
void setNum(int row, int col, char ch, ObjAttr* shadowOAM, int ind);
void drawNumFont(int row, int col, int num, ObjAttr* shadowOAM);
void setNum2(int row, int col, char ch, ObjAttr* shadowOAM, int ind);
void drawNumFont2(int row, int col, int num, ObjAttr* shadowOAM);

//void initStrMap();