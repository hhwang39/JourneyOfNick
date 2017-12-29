#include "mylib.h"
#include "myGame.h"
#include "sprite.h"
#include "map.h"
#include "map2.h"
#include "sprite2.h"
#include "text.h"
#include "sprite3.h"
int arrPos[4] = {IMAGE_5_ID, IMAGE_6_ID, IMAGE_7_ID, IMAGE_8_ID};
int arr2Pos[3] = {IMAGE_37_ID, IMAGE_38_ID, IMAGE_39_ID};
int bossPos[3] = {IMAGE_2_ID, IMAGE_13_ID, IMAGE_17_ID};
//draw first map - 2 layer
void drawMap() {
	DMAcopyMap(map_tiles, CHARBLOCKBASE[0].tileimg, MAP_TILES_SIZE);
	DMAcopyMap(map_map, SCREENBLOCKBASE[24].tilemap, MAP_MAP_SIZE);
	DMAcopyMap(map2_map, SCREENBLOCKBASE[26].tilemap, MAP_MAP_SIZE);
	DMAcopyMap(map_palette, PALETTE, MAP_PALETTE_SIZE);
}
//draw Boss map
void drawBossMap() {
	DMAcopyMap(map2_tiles, CHARBLOCKBASE[0].tileimg, MAP2_TILES_SIZE);
	DMAcopyMap(eye_map, SCREENBLOCKBASE[24].tilemap, CASTLE_MAP_SIZE);
	DMAcopyMap(map2_palette, PALETTE, MAP2_PALETTE_SIZE);
	DMAcopyMap(castle_map, SCREENBLOCKBASE[28].tilemap, CASTLE_MAP_SIZE);
}
//initalize positions of sprites
void initSprites(PLAYER* pl, ENEMY* enArr, ObjAttr* shadowOAM) {
	DMAcopyMap(sprite_palette, SPRITEPAL, SPRITE_PALETTE_SIZE);
	DMAcopyMap(sprite, CHARBLOCKBASE[4].tileimg, SPRITE_SIZE);
	pl->shape = IMAGE_8_SHAPE;
	pl->size = IMAGE_8_SIZE;
	pl->row = 80;
	pl->col = 10;
	pl->start = P1_ID;
	pl->moveSpeed = 5;
	pl->attPower = 10;
	pl->jumpSpeed = 10;
	pl->health = 500;
	//initalize shark
	for (int i = 0; i < NUM_ENE - NUM_PIG; ++i) {
		enArr[i].shape = IMAGE_7_SHAPE;
		enArr[i].size = IMAGE_6_SIZE;
		enArr[i].row = 80;
		enArr[i].col = (i+1)<<7;
		enArr[i].start = IMAGE_5_ID;
		enArr[i].health = 50;
		enArr[i].alive = 1;
		enArr[i].attPower = 10;
	}
	//initalize pigs
	for (int i = NUM_PIG; i < NUM_ENE; ++i) {
		enArr[i].shape = IMAGE_37_SHAPE;
		enArr[i].size = IMAGE_37_SIZE;
		enArr[i].row = 80;
		enArr[i].col = (i+1)<<7;
		enArr[i].start = IMAGE_37_ID;
		enArr[i].health = 50;
		enArr[i].alive = 1;
		enArr[i].attPower = 5;
	}
	shadowOAM[0].attr0 = pl->row | ATTR0_8BPP | pl->shape;
    shadowOAM[0].attr1 = pl->col | pl->size;
    shadowOAM[0].attr2 = pl->start | SPRITE_PALETTE_TYPE;
	for (int i = 1; i < NUM_ENE + 1; ++i) {
			shadowOAM[i].attr0 = enArr[i - 1].row | ATTR0_8BPP | enArr[i - 1].shape;
	        shadowOAM[i].attr1 = enArr[i - 1].col | enArr[i - 1].size;
	        shadowOAM[i].attr2 = enArr[i - 1].start | SPRITE_PALETTE_TYPE;
	}
	for(int i=NUM_ENE + 2; i<128; i++) {
	        shadowOAM[i].attr0 = ATTR0_HIDE;
	}
	DMAcopyMap(shadowOAM, SPRITEMEM, (128*sizeof(ObjAttr))>>1);
	waitForvBlank();
}
//draw sprite using magic with animation
void redrawSprites(PLAYER* pl, ENEMY* enArr, ObjAttr* shadowOAM) {
	pl->start = P1_ID;
	MAGIC mg = {pl->row, pl->col + 52, P8_SHAPE, P8_SIZE, P8_ID};
	shadowOAM[1+NUM_ENE].attr0 = mg.row | ATTR0_8BPP | mg.shape;
	shadowOAM[1+NUM_ENE].attr1 = mg.col | mg.size;
	shadowOAM[1+NUM_ENE].attr2 = mg.start | SPRITE_PALETTE_TYPE;
	shadowOAM[0].attr2 = pl->start | SPRITE_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 2)*sizeof(ObjAttr))>>1);
	delay(3);
	waitForvBlank();
	pl->start = P3_ID;
	shadowOAM[0].attr2 = pl->start | SPRITE_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 2)*sizeof(ObjAttr))>>1);
	delay(3);
	waitForvBlank();
	pl->start = P4_ID;
	shadowOAM[0].attr2 = pl->start | SPRITE_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 2)*sizeof(ObjAttr))>>1);
	delay(3);
	pl->start = P6_ID;
	shadowOAM[0].attr2 = pl->start | SPRITE_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 2)*sizeof(ObjAttr))>>1);
	delay(3);
	waitForvBlank();
	pl->start = P7_ID;
	shadowOAM[0].attr2 = pl->start | SPRITE_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 2)*sizeof(ObjAttr))>>1);
	delay(3);
	pl->start = 0;
	shadowOAM[0].attr2 = pl->start | SPRITE_PALETTE_TYPE;
	shadowOAM[1+NUM_ENE].attr0 = ATTR0_HIDE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 2)*sizeof(ObjAttr))>>1);
	waitForvBlank();
	for (int i = 0; i < NUM_ENE; ++i) {
		if (collision(mg, enArr[i], 32, 32, 32, 32)) {
			enArr[i].health -= pl->attPower;
			if (enArr[i].health <= 0) {
				enArr[i].alive = 0;
			}
		}
		if (!enArr[i].alive) {
			shadowOAM[i + 1].attr0 = ATTR0_HIDE;
		}
	}
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 2)*sizeof(ObjAttr))>>1);
}
void walkPlayer1(ObjAttr* shadowOAM, PLAYER* pl) {
	if (pl->start == P1_ID) {
		pl->start = P2_ID;
	} else {
		pl->start = P1_ID;
	}
	shadowOAM[0].attr2 = pl->start | SPRITE_PALETTE_TYPE;
	waitForvBlank();
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 2)*sizeof(ObjAttr))>>1);
}
void jumpPlayer1(ObjAttr* shadowOAM, PLAYER* pl) {
	if (pl->start == P5_ID) {
		pl->start = P1_ID;
	} else {
		pl->start = P5_ID;
	}
	shadowOAM[0].attr2 = pl->start | SPRITE_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 2)*sizeof(ObjAttr))>>1);	
}
void redrawEnemy(ENEMY* ene, ObjAttr* shadowOAM) {
	//animate shark
	static int count = 0;
	for (int i = 0; i < NUM_ENE - NUM_PIG; ++i) {
		if (ene[i].start == arrPos[0]) {
			ene[i].start = arrPos[1];
			ene[i].col -= 10;
		} else if (ene[i].start == arrPos[1]) {
			ene[i].start = arrPos[2];
			ene[i].col += 10;
		} else if (ene[i].start == arrPos[2]) {
			ene[i].start = arrPos[3];		
		} else if (ene[i].start == arrPos[3]) {
			ene[i].start = arrPos[0];		
		}
	}
	for (int i = NUM_PIG; i < NUM_ENE; ++i) {
		ene[i].start = arr2Pos[count % 3];
	}
	for (int i = 1; i < NUM_ENE + 1; ++i) {
		shadowOAM[i].attr2 = ene[i - 1].start | SPRITE_PALETTE_TYPE;
		if (ene[i-1].col - hoff <= 0 || ene[i - 1].col - hoff >= 240 || (!ene[i - 1].alive)) {
	    	shadowOAM[i].attr0 = ATTR0_HIDE;
		} else {
	    	shadowOAM[i].attr0 = ene[i - 1].row | ATTR0_8BPP | ene[i - 1].shape;
	    	shadowOAM[i].attr1 = ((ene[i - 1].col - hoff) & 0x1FF) | ene[i - 1].size;
		}
	}
	delay(2);
	waitForvBlank();
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 1)*sizeof(ObjAttr))>>1);
	count++;
}
//draw player in new pos
void redrawPlayer(PLAYER* pl, ObjAttr* shadowOAM) {
	shadowOAM[0].attr0 = pl->row | ATTR0_8BPP | pl->shape;
    shadowOAM[0].attr1 = ((pl->col) & 0x1FF) | pl->size;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((NUM_ENE + 1)*sizeof(ObjAttr))>>1);
}
//check collison
int collision(MAGIC axe, ENEMY boss, int bossWidth, int bossHeigt, int width, int height) {
	boss.col -= hoff;
	int log = ((axe.row >= boss.row  && axe.row <= boss.row + bossHeigt) || (axe.row + height>= boss.row  && axe.row  + height <= boss.row + bossHeigt)) && ((axe.col >= boss.col  && axe.col <= boss.col + bossWidth) || (axe.col + width >= boss.col  && axe.col + width <= boss.col + bossWidth));
	return log;
}
int collisionPlayer(PLAYER axe, ENEMY boss, int bossWidth, int bossHeigt, int width, int height) {
	boss.col -= hoff;
	int log = ((axe.row >= boss.row  && axe.row <= boss.row + bossHeigt) || (axe.row + height>= boss.row  && axe.row  + height <= boss.row + bossHeigt)) && ((axe.col >= boss.col  && axe.col <= boss.col + bossWidth) || (axe.col + width >= boss.col  && axe.col + width <= boss.col + bossWidth));
	return log;	
}
void initTalkMap(ObjAttr* shadowOAM) {
	DMAcopyMap(sprite3_palette, SPRITEPAL, SPRITE3_PALETTE_SIZE);
	DMAcopyMap(sprite3, CHARBLOCKBASE[4].tileimg, SPRITE3_SIZE);
	PLAYER pl;
	pl.row = 80;
	pl.col = 10;
	pl.shape = IMAGE_15_SHAPE;
	pl.size = IMAGE_15_SIZE;
	pl.start = IMAGE_15_ID;
	pl.moveSpeed = 0;
	pl.attPower = 0;
	pl.jumpSpeed = 0;
	pl.health = 0;
	shadowOAM[0].attr0 = pl.row | ATTR0_8BPP | pl.shape | ATTR0_MOSAIC;
    shadowOAM[0].attr1 = pl.col | pl.size;
    shadowOAM[0].attr2 = pl.start;// | SPRITE3_PALETTE_TYPE;
    drawFontStr(pl.row - 10, pl.col + 20, "It feels weird", shadowOAM);
    delay(20);
    drawFontStr(pl.row, pl.col + 40, "the blood of demon", shadowOAM);
    delay(20);
    drawFontStr(pl.row + 10, pl.col + 40, "has awaken my true power", shadowOAM);
    shadowOAM[0].attr0 = pl.row | ATTR0_8BPP | pl.shape | ATTR0_MOSAIC;
    DMAcopyMap(shadowOAM, SPRITEMEM, (128*sizeof(ObjAttr))>>1);
    delay(50);
    //drawFontStr(pl.row + 20, pl.col + 40, "!!!!!", shadowOAM);
}
void clearSprites(ObjAttr* shadowOAM) {
	for (int i = 0; i < 128; ++i) {
		shadowOAM[i].attr0 = ATTR0_HIDE;
	}
    DMAcopyMap(shadowOAM, SPRITEMEM, (128*sizeof(ObjAttr))>>1);
}
void drawNewSprite(ObjAttr* shadowOAM) {
	DMAcopyMap(sprite2_palette, SPRITEPAL, SPRITE2_PALETTE_SIZE);
	DMAcopyMap(sprite2, CHARBLOCKBASE[4].tileimg, SPRITE2_SIZE);
	PLAYER pl;
	pl.row = 80;
	pl.col = 10;
	pl.shape = IMAGE_50_SHAPE;
	pl.size = IMAGE_50_SIZE;
	pl.start = IMAGE_50_ID;
	shadowOAM[0].attr0 = pl.row | ATTR0_8BPP | pl.shape;
    shadowOAM[0].attr1 = pl.col | pl.size;
    shadowOAM[0].attr2 = pl.start;
    waitForvBlank();
    DMAcopyMap(shadowOAM, SPRITEMEM, (128*sizeof(ObjAttr))>>1);
}
void initalize2(PLAYER* pl, ENEMY* boss, ObjAttr* shadowOAM) {
	DMAcopyMap(sprite2_palette, SPRITEPAL, SPRITE2_PALETTE_SIZE);
	DMAcopyMap(sprite2, CHARBLOCKBASE[4].tileimg, SPRITE2_SIZE);
	pl->shape = IMAGE_50_SHAPE;
	pl->size = IMAGE_50_SIZE;
	pl->row = 80;
	pl->col = 10;
	pl->start = IMAGE_50_ID;
	pl->moveSpeed = 5;
	pl->attPower = 20;
	pl->jumpSpeed = 10;
	pl->health = 500;	
	boss->shape = IMAGE_2_SHAPE;
	boss->size = IMAGE_2_SIZE;
	boss->row = 48;
	boss->col = 350;
	boss->start = IMAGE_2_ID;
	boss->attPower = 20;
	boss->health = 300;
	boss->alive = 1;
	shadowOAM[0].attr0 = pl->row | ATTR0_8BPP | pl->shape;
    shadowOAM[0].attr1 = pl->col | pl->size;
    shadowOAM[0].attr2 = pl->start | SPRITE2_PALETTE_TYPE;
    shadowOAM[1].attr0 = boss->row | ATTR0_8BPP | boss->shape;
    shadowOAM[1].attr1 = boss->col | boss->size;
    shadowOAM[1].attr2 = boss->start | SPRITE2_PALETTE_TYPE;
    waitForvBlank();
    DMAcopyMap(shadowOAM, SPRITEMEM, (128*sizeof(ObjAttr))>>1);
}
void useMagicStage2(PLAYER* pl, ENEMY* boss, ObjAttr* shadowOAM) {
	pl->start = IMAGE_50_ID;
	MAGIC mg = {pl->row, pl->col + 52, IMAGE_146_SHAPE, IMAGE_146_SIZE, IMAGE_146_ID};
	shadowOAM[2].attr0 = mg.row | ATTR0_8BPP | mg.shape;
	shadowOAM[2].attr1 = mg.col | mg.size;
	shadowOAM[2].attr2 = mg.start | SPRITE2_PALETTE_TYPE;
	shadowOAM[0].attr2 = pl->start | SPRITE2_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((3)*sizeof(ObjAttr))>>1);
	delay(3);
	waitForvBlank();
	pl->start = IMAGE_53_ID;
	shadowOAM[0].attr2 = pl->start | SPRITE2_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((3)*sizeof(ObjAttr))>>1);
	delay(3);
	waitForvBlank();
	pl->start = IMAGE_56_ID;
	shadowOAM[0].attr2 = pl->start | SPRITE2_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((3)*sizeof(ObjAttr))>>1);
	delay(3);
	pl->start = IMAGE_57_ID;
	shadowOAM[0].attr2 = pl->start | SPRITE2_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((3)*sizeof(ObjAttr))>>1);
	delay(3);
	waitForvBlank();
	pl->start = IMAGE_58_ID;
	shadowOAM[0].attr2 = pl->start | SPRITE2_PALETTE_TYPE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((3)*sizeof(ObjAttr))>>1);
	delay(3);
	pl->start = IMAGE_50_ID;
	shadowOAM[0].attr2 = pl->start | SPRITE2_PALETTE_TYPE;
	shadowOAM[2].attr0 = ATTR0_HIDE;
	DMAcopyMap(shadowOAM, SPRITEMEM, ((3)*sizeof(ObjAttr))>>1);
	waitForvBlank();
	if (collision(mg, *boss, 64, 64, 32, 32)) {
		boss->health -= pl->attPower;
		if (boss->health <= 0) {
			shadowOAM[1].attr1 = ATTR0_HIDE;
			boss->alive = 0;
		}
	}
	DMAcopyMap(shadowOAM, SPRITEMEM, ((3)*sizeof(ObjAttr))>>1);
}
void updateSprites(PLAYER* pl, ENEMY* boss, ObjAttr* shadowOAM) {
	shadowOAM[0].attr0 = pl->row | ATTR0_8BPP | pl->shape;
    shadowOAM[0].attr1 = ((pl->col) & 0x1FF) | pl->size;
    waitForvBlank();
	DMAcopyMap(shadowOAM, SPRITEMEM, ((4)*sizeof(ObjAttr))>>1);
}
void updateBoss(PLAYER* pl, ENEMY* boss, ObjAttr*shadowOAM) {
	static int counter = 0;
    boss->start = bossPos[counter % 3];
    if (counter % 3 == 2) {
    	pl->health -= 10;
    }
    if (boss->alive) {
  	    shadowOAM[1].attr1 = ((boss->col - hoff) & 0x1FF) | boss->size;
		shadowOAM[1].attr2 = boss->start | SPRITE2_PALETTE_TYPE;  	
    }	
    waitForvBlank();
	DMAcopyMap(shadowOAM, SPRITEMEM, ((4)*sizeof(ObjAttr))>>1);
	counter++;
}

void jumpPlayer2(ObjAttr* shadowOAM, PLAYER* pl) {
	if (pl->start == IMAGE_50_ID) {
		pl->start = IMAGE_22_ID;
	} else {
		pl->start = IMAGE_50_ID;
	}
	shadowOAM[0].attr2 = pl->start | SPRITE_PALETTE_TYPE;
    waitForvBlank();
	DMAcopyMap(shadowOAM, SPRITEMEM, ((128)*sizeof(ObjAttr))>>1);	
}