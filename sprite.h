/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -sprites sprite Player1/p1.png Player1/p2.png Player1/p3.png Player1/p4.png Player1/p5.png Player1/p6.png Player1/p7.png Player1/p8.png Monster1/5.png Monster1/6.png Monster1/7.png Monster1/8.png Monster2/37.png Monster2/38.png Monster2/39.png Num/fontw-17.png Num/fontw-18.png Num/fontw-19.png Num/fontw-20.png Num/fontw-21.png Num/fontw-22.png Num/fontw-23.png Num/fontw-24.png Num/fontw-25.png Num/fontw-26.png 
 * Time-stamp: Saturday 11/29/2014, 14:55:32
 * 
 * Image Information
 * -----------------
 * Player1/p1.png 32@32
 * Player1/p2.png 32@32
 * Player1/p3.png 32@32
 * Player1/p4.png 32@32
 * Player1/p5.png 32@32
 * Player1/p6.png 32@32
 * Player1/p7.png 32@32
 * Player1/p8.png 32@32
 * Monster1/5.png 32@32
 * Monster1/6.png 32@32
 * Monster1/7.png 32@32
 * Monster1/8.png 32@32
 * Monster2/37.png 32@32
 * Monster2/38.png 32@32
 * Monster2/39.png 32@32
 * Num/fontw-17.png 8@8
 * Num/fontw-18.png 8@8
 * Num/fontw-19.png 8@8
 * Num/fontw-20.png 8@8
 * Num/fontw-21.png 8@8
 * Num/fontw-22.png 8@8
 * Num/fontw-23.png 8@8
 * Num/fontw-24.png 8@8
 * Num/fontw-25.png 8@8
 * Num/fontw-26.png 8@8
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * Helpdesk: There is an icon on your computer labeled "My Computer".
 *  Double click on it.
 *  User: What's your computer doing on mine?
 * 
 * All the effort you are making will ultimately pay off.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef SPRITE_BITMAP_H
#define SPRITE_BITMAP_H

#define SPRITE_PALETTE_TYPE (1 << 13)
#define SPRITE_DIMENSION_TYPE (1 << 6)

extern const unsigned short sprite_palette[256];
#define SPRITE_PALETTE_SIZE 256

extern const unsigned short sprite[8000];
#define SPRITE_SIZE 8000

#define P2_SHAPE (0 << 14)
#define P2_SIZE (2 << 14)
#define P2_ID 0

#define IMAGE_39_SHAPE (0 << 14)
#define IMAGE_39_SIZE (2 << 14)
#define IMAGE_39_ID 32

#define IMAGE_38_SHAPE (0 << 14)
#define IMAGE_38_SIZE (2 << 14)
#define IMAGE_38_ID 64

#define IMAGE_37_SHAPE (0 << 14)
#define IMAGE_37_SIZE (2 << 14)
#define IMAGE_37_ID 96

#define IMAGE_8_SHAPE (0 << 14)
#define IMAGE_8_SIZE (2 << 14)
#define IMAGE_8_ID 128

#define IMAGE_7_SHAPE (0 << 14)
#define IMAGE_7_SIZE (2 << 14)
#define IMAGE_7_ID 160

#define IMAGE_6_SHAPE (0 << 14)
#define IMAGE_6_SIZE (2 << 14)
#define IMAGE_6_ID 192

#define IMAGE_5_SHAPE (0 << 14)
#define IMAGE_5_SIZE (2 << 14)
#define IMAGE_5_ID 224

#define P7_SHAPE (0 << 14)
#define P7_SIZE (2 << 14)
#define P7_ID 256

#define P6_SHAPE (0 << 14)
#define P6_SIZE (2 << 14)
#define P6_ID 288

#define P5_SHAPE (0 << 14)
#define P5_SIZE (2 << 14)
#define P5_ID 320

#define P4_SHAPE (0 << 14)
#define P4_SIZE (2 << 14)
#define P4_ID 352

#define P3_SHAPE (0 << 14)
#define P3_SIZE (2 << 14)
#define P3_ID 384

#define P1_SHAPE (0 << 14)
#define P1_SIZE (2 << 14)
#define P1_ID 416

#define P8_SHAPE (0 << 14)
#define P8_SIZE (2 << 14)
#define P8_ID 448

#define FONTW26_SHAPE (0 << 14)
#define FONTW26_SIZE (0 << 14)
#define FONTW26_ID 480

#define FONTW25_SHAPE (0 << 14)
#define FONTW25_SIZE (0 << 14)
#define FONTW25_ID 482

#define FONTW24_SHAPE (0 << 14)
#define FONTW24_SIZE (0 << 14)
#define FONTW24_ID 484

#define FONTW23_SHAPE (0 << 14)
#define FONTW23_SIZE (0 << 14)
#define FONTW23_ID 486

#define FONTW22_SHAPE (0 << 14)
#define FONTW22_SIZE (0 << 14)
#define FONTW22_ID 488

#define FONTW21_SHAPE (0 << 14)
#define FONTW21_SIZE (0 << 14)
#define FONTW21_ID 490

#define FONTW20_SHAPE (0 << 14)
#define FONTW20_SIZE (0 << 14)
#define FONTW20_ID 492

#define FONTW19_SHAPE (0 << 14)
#define FONTW19_SIZE (0 << 14)
#define FONTW19_ID 494

#define FONTW18_SHAPE (0 << 14)
#define FONTW18_SIZE (0 << 14)
#define FONTW18_ID 496

#define FONTW17_SHAPE (0 << 14)
#define FONTW17_SIZE (0 << 14)
#define FONTW17_ID 498

#endif

