/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -sprites sprite3 Boss1/2.png Boss1/13.png Boss1/17.png Player2/146.png Player2/22.png Player2/50.png Player2/53.png Player2/56.png Player2/57.png Player2/58.png 
 * Time-stamp: Friday 11/28/2014, 02:36:32
 * 
 * Image Information
 * -----------------
 * Boss1/2.png 64@64
 * Boss1/13.png 64@64
 * Boss1/17.png 64@64
 * Player2/146.png 32@32
 * Player2/22.png 32@32
 * Player2/50.png 32@32
 * Player2/53.png 32@32
 * Player2/56.png 32@32
 * Player2/57.png 32@32
 * Player2/58.png 32@32
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * Those who can't write programs, write help files.
 * 
 * Your life will be happy and peaceful.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef SPRITE3_BITMAP_H
#define SPRITE3_BITMAP_H

#define SPRITE3_PALETTE_TYPE (1 << 13)
#define SPRITE3_DIMENSION_TYPE (1 << 6)

extern const unsigned short sprite3_palette[256];
#define SPRITE3_PALETTE_SIZE 256

extern const unsigned short sprite3[9728];
#define SPRITE3_SIZE 9728

#define IMAGE_2_SHAPE (0 << 14)
#define IMAGE_2_SIZE (3 << 14)
#define IMAGE_2_ID 0

#define IMAGE_13_SHAPE (0 << 14)
#define IMAGE_13_SIZE (3 << 14)
#define IMAGE_13_ID 128

#define IMAGE_17_SHAPE (0 << 14)
#define IMAGE_17_SIZE (3 << 14)
#define IMAGE_17_ID 256

#define IMAGE_146_SHAPE (0 << 14)
#define IMAGE_146_SIZE (2 << 14)
#define IMAGE_146_ID 384

#define IMAGE_22_SHAPE (0 << 14)
#define IMAGE_22_SIZE (2 << 14)
#define IMAGE_22_ID 416

#define IMAGE_50_SHAPE (0 << 14)
#define IMAGE_50_SIZE (2 << 14)
#define IMAGE_50_ID 448

#define IMAGE_53_SHAPE (0 << 14)
#define IMAGE_53_SIZE (2 << 14)
#define IMAGE_53_ID 480

#define IMAGE_56_SHAPE (0 << 14)
#define IMAGE_56_SIZE (2 << 14)
#define IMAGE_56_ID 512

#define IMAGE_57_SHAPE (0 << 14)
#define IMAGE_57_SIZE (2 << 14)
#define IMAGE_57_ID 544

#define IMAGE_58_SHAPE (0 << 14)
#define IMAGE_58_SIZE (2 << 14)
#define IMAGE_58_ID 576

#endif

