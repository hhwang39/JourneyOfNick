/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode0 fontW font.png 
 * Time-stamp: Thursday 11/27/2014, 19:08:06
 * 
 * Image Information
 * -----------------
 * font.png 128@48
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * Those who can't write programs, write help files.
 * 
 * A fresh start will put you on your way.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef FONTW_BITMAP_H
#define FONTW_BITMAP_H

extern const unsigned short fontW_palette[256];
#define FONTW_PALETTE_SIZE 256

#define FONTW_PALETTE_TYPE (1 << 7)

extern const unsigned short fontW_tiles[3104];
#define FONTW_TILES 97
#define FONTW_TILES_SIZE 3104

extern const unsigned short font_map[96];
#define FONT_WIDTH 16
#define FONT_HEIGHT 6
#define FONT_MAP_SIZE 96
#define FONT_MAP_TYPE (0 << 14)

#endif

