/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode0 -animated map map.png map2.png 
 * Time-stamp: Wednesday 11/26/2014, 17:53:50
 * 
 * Image Information
 * -----------------
 * map.png 512@256
 * map2.png 512@256
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * It used to take me all vacation to grow a new hide in place of the one they flogged off me during school term.  ~Mark Twain
 * 
 * Your abilities are unparalleled.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef MAP_BITMAP_H
#define MAP_BITMAP_H

extern const unsigned short map_palette[15];
#define MAP_PALETTE_SIZE 15

#define MAP_PALETTE_TYPE (1 << 7)

extern const unsigned short map_tiles[2304];
#define MAP_TILES 72
#define MAP_TILES_SIZE 2304

extern const unsigned short map_map[2048];
#define MAP_WIDTH 64
#define MAP_HEIGHT 32
#define MAP_MAP_SIZE 2048
#define MAP_MAP_TYPE (1 << 14)

extern const unsigned short map2_map[2048];
#define MAP2_WIDTH 64
#define MAP2_HEIGHT 32
#define MAP2_MAP_SIZE 2048
#define MAP2_MAP_TYPE (1 << 14)

extern const unsigned short* map_frames[2];
#define MAP_ANIMATION_FRAMES 2

#endif

