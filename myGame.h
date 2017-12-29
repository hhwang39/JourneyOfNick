#define NUM_ENE 4
#define NUM_PIG 2
extern int hoff;
typedef struct {
	int shape, row, col, size, start, attPower, health, moveSpeed, jumpSpeed;
} PLAYER;
typedef struct {
	int shape, row, col, size, start, attPower, health, alive;
} ENEMY;
typedef struct {
	int row, col, shape, size, start;
} MAGIC;
typedef enum {START, EXP, PLAY, TALK, BOSS, WINEXP, WIN, LOSE} STATE;

void drawMap();
void drawBossMap();
void initSprites(PLAYER* pl, ENEMY* enArr, ObjAttr* ob);
void redrawSprites(PLAYER* pl, ENEMY* enArr, ObjAttr* ob);
void redrawEnemy(ENEMY* ene, ObjAttr* ob);
void redrawPlayer(PLAYER* pl, ObjAttr* shadowOAM);
int collision(MAGIC mg, ENEMY ene, int bossWidth, int bossHeigt, int width, int height);
int collisionPlayer(PLAYER axe, ENEMY boss, int bossWidth, int bossHeigt, int width, int height);
void walkPlayer1(ObjAttr* shadowOAM, PLAYER* pl);
void jumpPlayer1(ObjAttr* shadowOAM, PLAYER* pl);
void initTalkMap(ObjAttr* shadowOAM);
void drawNewSprite(ObjAttr* shadowOAM);
void clearSprites(ObjAttr* shadowOAM);
void initalize2(PLAYER* pl, ENEMY* boss, ObjAttr* shadowOAM);
void jumpPlayer2(ObjAttr* shadowOAM, PLAYER* pl);
void updateSprites(PLAYER* player, ENEMY* boss, ObjAttr*shadowOAM);
void updateBoss(PLAYER* pl, ENEMY* boss, ObjAttr*shadowOAM);
void useMagicStage2(PLAYER* pl, ENEMY* boss, ObjAttr* shadowOAM);