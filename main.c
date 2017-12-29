#include "mylib.h"
#include "myGame.h"
#include "text.h"
#include <stdio.h>
#include "bd.h"
#include "win.h"
#include "end.h"
#define PLAYER_SIZE 32


PLAYER	player;
ENEMY ene[NUM_ENE];
ENEMY boss;
ObjAttr shadowOAM[128];
int hoff = 0;
int playGame();
int BossGame();
int main() {
	STATE state = START;
	// play using different states 
	while (1) {
		if (state == START) {
			REG_DIPCNT = MODE3 | BG2_ENABLE;
			drawDMABDImg(start);
    		while (!KEY_DOWN_NOW(KEY_START));
    		state = EXP;
    		while (KEY_DOWN_NOW(KEY_START));
		} else if (state == EXP) {
			REG_DIPCNT = MODE3 | BG2_ENABLE;
			drawDMABDImg(start2);
    		while (!KEY_DOWN_NOW(KEY_START));
    		state = PLAY;
    		while (KEY_DOWN_NOW(KEY_START));
		}else if (state == PLAY) {
			REG_DIPCNT = MODE0 | BG0_ENABLE | OBJ_ENABLE | MODE1D | BG1_ENABLE;
			drawMap();
			REG_BG0CNT = BG_SIZE2 | SBB(26) | CBB(0) | COLOR256 | 1;
			REG_BG1CNT = BG_SIZE2 | SBB(24) | CBB(0) | COLOR256 | 0;
		    initSprites(&player, ene, shadowOAM);
		    state = playGame();
		    if (state == TALK) {
		    	delay(50);
		    }
		} else if (state == TALK){
			REG_DIPCNT = MODE0 | BG0_ENABLE | OBJ_ENABLE | MODE1D | BG1_ENABLE;
			drawMap();
			//initStrMap();
			REG_BG0CNT = BG_SIZE2 | SBB(26) | CBB(0) | COLOR256 | 2;
			REG_BG1CNT = BG_SIZE2 | SBB(24) | CBB(0) | COLOR256 | 1;
			REG_BG0HOFS = 0;
			REG_BG0VOFS = 50;
			REG_BG1HOFS = 0;
			REG_BG1VOFS = 80;
			initTalkMap(shadowOAM);
			REG_MOSAIC = MOSOBJSTRE(2) | MOSOBJVSTRE(2);
			delay(100);
			clearSprites(shadowOAM);
			drawNewSprite(shadowOAM);
			//state = BOSS;
			delay(100);
			state = BOSS;
		} else if (state == BOSS){
			REG_DIPCNT = MODE0 | BG0_ENABLE | OBJ_ENABLE | MODE1D | BG1_ENABLE;
			drawBossMap();
			REG_BG1CNT = BG_SIZE3 | SBB(24) | CBB(0) | 1;
			REG_BG0CNT = BG_SIZE3 | SBB(28) | CBB(0) | 0;
			initalize2(&player, &boss, shadowOAM);
			delay(5);
			REG_BG0HOFS = 0;
			REG_BG0VOFS = 210;
			REG_BG1VOFS = 210;
			REG_BG1HOFS = 0;
			state = BossGame();
		} else if (state == WINEXP) {
			REG_DIPCNT = MODE3 | BG2_ENABLE;
			drawDMABDImg(win2);
    		delay(300);
    		state = WIN;
		} else if (state == WIN) {
			REG_DIPCNT = MODE3 | BG2_ENABLE;
			drawDMABDImg(win);
			while (!KEY_DOWN_NOW(KEY_START));
			state = START;
    		while (KEY_DOWN_NOW(KEY_START));
		} else if (state == LOSE) {
			REG_DIPCNT = MODE3 | BG2_ENABLE;
			drawDMABDImg(DIED);
			while (!KEY_DOWN_NOW(KEY_START));
			state = START;
    		while (KEY_DOWN_NOW(KEY_START));
		}
	}
    return 0;
}

int playGame() {
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 50;
	REG_BG1HOFS = 0;
	REG_BG1VOFS = 80;
	int gravity = -5;
	int jump = 0;
	hoff = 0;
	int voff = 50;	// These two variables store our values for vertical
	while (1) {
		redrawEnemy(ene, shadowOAM);
		redrawPlayer(&player, shadowOAM);
		drawNumFont(130, 200, player.health, shadowOAM);
		//use magic
		if (KEY_DOWN_NOW(KEY_A)) {
			redrawSprites(&player, ene, shadowOAM);
		}
		//move left
		if (KEY_DOWN_NOW(KEY_LEFT)) {
			player.col -= player.moveSpeed;
			if (player.col < 10) {
				player.col = 10;
			}
			if (player.col < 120) {
				hoff -= 5;
			}
			if (hoff < 0) {
				hoff = 0;
			}
			for (int i = 0; i < NUM_ENE; ++i) {
				if (collisionPlayer(player, ene[i], 32, 32, 32 , 32) && ene[i].alive) {
					player.health -= ene[i].attPower;
				}
			}
			walkPlayer1(shadowOAM, &player);
		}
		//move right
		if (KEY_DOWN_NOW(KEY_RIGHT)) {
			player.col += player.moveSpeed;
			if (player.col > 120) {
				hoff += 5;
			}
			if (player.col > 240 - PLAYER_SIZE) {
				player.col = 240 - PLAYER_SIZE;
			}
			if (hoff > 480) {
				hoff = 480;
			}
			for (int i = 0; i < NUM_ENE; ++i) {
				if (collisionPlayer(player, ene[i], 32, 32, 32 , 32) && ene[i].alive) {
					player.health -= ene[i].attPower;
				}
			}
			walkPlayer1(shadowOAM, &player);
		}
		if (KEY_DOWN_NOW(KEY_UP)) {
			jump = 1;
			jumpPlayer1(shadowOAM, &player);
		}
		//jump
		if (jump) {
			player.row -= player.jumpSpeed + gravity;
			if (player.row < 50) {
				player.jumpSpeed = 0;
			}
			if (player.row >= 80) {
				player.row = 80;
				player.jumpSpeed = 10;
				jumpPlayer1(shadowOAM, &player);
				jump = 0;
			}
		}
		
		REG_BG0HOFS = hoff;
	    REG_BG0VOFS = voff;
	    REG_BG1HOFS = hoff;
	    REG_BG1HOFS = voff;
	    if (player.health < 0) {
	    	return LOSE;
	    }
	    int sum = 0;
	    for (int j = 0; j < NUM_ENE; ++j) {
	    	sum += ene[j].alive;
	    }
	    if (!sum) {
	    	return TALK;
	    }
	}
	return LOSE;
}
int BossGame() {
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 210;
	REG_BG1VOFS = 210;
	REG_BG1HOFS = 0;
	int gravity = -5;
	int jump = 0;
	int voff = 210;
	hoff = 0;
	int track = 0;
	while (1) {
		if (track % 15 == 0) {
			updateBoss(&player, &boss, shadowOAM);
		}
		drawNumFont2(130, 200, player.health, shadowOAM);
		updateSprites(&player, &boss, shadowOAM);

		if (KEY_DOWN_NOW(KEY_A)) {
			useMagicStage2(&player, &boss, shadowOAM);
		}
		//move left
		if (KEY_DOWN_NOW(KEY_LEFT)) {
			player.col -= player.moveSpeed;
			if (player.col < 10) {
				player.col = 10;
			}
			if (player.col < 120) {
				hoff -= 5;
				player.moveSpeed = 1;
			} else {
				player.moveSpeed = 5;
			}
			if (hoff < 0) {
				hoff = 0;
			}
			if (collisionPlayer(player, boss, 64, 64, 32, 32) && boss.alive) {
				player.health -= boss.attPower;
			}
		}
		//move right
		if (KEY_DOWN_NOW(KEY_RIGHT)) {
			player.col += player.moveSpeed;
			if (player.col > 120) {
				hoff += 5;
				player.moveSpeed = 1;
			} else {
				player.moveSpeed = 5;	
			}
			if (player.col > 240 - PLAYER_SIZE) {
				player.col = 240 - PLAYER_SIZE;
			}
			if (hoff > 480) {
				hoff = 480;
			}
			if (collisionPlayer(player, boss, 64, 64, 32, 32) && boss.alive) {
				player.health -= boss.attPower;
			}
		}
		if (KEY_DOWN_NOW(KEY_UP)) {
			jump = 1;
			jumpPlayer2(shadowOAM, &player);
		}
		//jump
		if (jump) {
			player.row -= player.jumpSpeed + gravity;
			if (player.row < 50) {
				player.jumpSpeed = 0;
			}
			if (player.row >= 80) {
				player.row = 80;
				player.jumpSpeed = 10;
				jumpPlayer2(shadowOAM, &player);
				jump = 0;
			}
		}
		REG_BG0HOFS = hoff;
	    REG_BG0VOFS = voff;
	    REG_BG1HOFS = hoff;
	    REG_BG1HOFS = voff;
	    track++;
	    if (!boss.alive) {
	    	return WINEXP;
	    }
	    if (player.health < 0) {
	    	return LOSE;
	    }
	}
	return LOSE;
}