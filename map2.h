/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode0 -animated -bpp=4 map2 castle.png eye.png 
 * Time-stamp: Monday 11/24/2014, 00:50:57
 * 
 * Image Information
 * -----------------
 * castle.png 512@512
 * eye.png 512@512
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * People think that computer science is the art of geniuses
 *  but the actual reality is the opposite, just many people doing things that build on each other,
 *  like a wall of mini stones. - Donald Knuth
 * 
 * If you continually give, you will continually have.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef MAP2_BITMAP_H
#define MAP2_BITMAP_H

extern const unsigned short map2_palette[256];
#define MAP2_PALETTE_SIZE 256

#define MAP2_PALETTE_TYPE (0 << 7)

extern const unsigned short map2_tiles[2880];
#define MAP2_TILES 180
#define MAP2_TILES_SIZE 2880

extern const unsigned short castle_map[4096];
#define CASTLE_WIDTH 64
#define CASTLE_HEIGHT 64
#define CASTLE_MAP_SIZE 4096
#define CASTLE_MAP_TYPE (3 << 14)

extern const unsigned short eye_map[4096];
#define EYE_WIDTH 64
#define EYE_HEIGHT 64
#define EYE_MAP_SIZE 4096
#define EYE_MAP_TYPE (3 << 14)

extern const unsigned short* map2_frames[2];
#define MAP2_ANIMATION_FRAMES 2

#endif

