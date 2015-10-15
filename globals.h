#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdio.h>
#define TOP_ALIEN_SCORE 40
#define MIDDLE_ALIEN_SCORE 20
#define BOTTOM_ALIEN_SCORE 10
#define SHIP_SPEED 2
#define SHIP_WIDTH 32
#define SHIP_HEIGHT 14
#define MAX_LIVES 3
#define ALIEN_HEIGHT 16
#define SAUCER_HEIGHT 14
#define TANK_HEIGHT 16
#define TANK_WIDTH 30
#define BUNKER_HEIGHT 38
#define BUNKER_WIDTH 48
#define BUNKER_Y_VALUE 350
#define MAX_BUNKER_DAMAGE 5
#define BUNKER_DAMAGE_HEIGHT 12
#define BUNKER_DAMAGE_WIDTH 12
#define BUNKER_OFFSET 50
#define TANK_Y_VALUE 400
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define EXPLOSION_HEIGHT 20
#define ALIEN_BULLET_HEIGHT 10
#define ALIEN_BULLET_WIDTH 6
#define TANK_BULLET_HEIGHT 4
#define TANK_BULLET_WIDTH 2
#define MAX_ALIEN_BULLETS 4
#define	ALPHA_NUM_WIDTH 12
#define ALPHA_NUM_HEIGHT 10
#define ALPHA_I_WIDTH 4
#define NUM_1_WIDTH 6
#define ALIEN_START_Y (ALIEN_HEIGHT * 4)
#define SCREEN_BUFFER 20
#define SCORE_Y SCREEN_BUFFER
#define SCORE_X SCREEN_BUFFER
#define	SCORE_NUM_X SCORE_X + 10
#define LIVES_Y SCREEN_BUFFER
#define TANK_LIVES_SPACING 6
#define LIVES_WORD_TANK_SPACING 10
#define LIVES_WORD_WIDTH ((ALPHA_NUM_WIDTH * 4) + ALPHA_I_WIDTH)
#define TANK_LIVES_WIDTH ((TANK_WIDTH + TANK_LIVES_SPACING) * MAX_LIVES)
#define LIVES_X (SCREEN_WIDTH - TANK_LIVES_WIDTH - LIVES_WORD_WIDTH - SCREEN_BUFFER - LIVES_WORD_TANK_SPACING)
#define TANK_LIVES_X LIVES_X + LIVES_WORD_WIDTH + LIVES_WORD_TANK_SPACING
#define TANK_LIVES_Y (LIVES_Y - (TANK_HEIGHT - ALPHA_NUM_HEIGHT))
#define EFFECTIVE_SCREEN_TOP (SCREEN_BUFFER + ALPHA_NUM_HEIGHT)
#define SHIP_Y (EFFECTIVE_SCREEN_TOP + 4)
#define GREEN_EARTH_LINE_Y 460
#define GREEN_EARTH_LINE_HEIGHT 1
#define BUNKER_0_XPOSITION (BUNKER_OFFSET)
#define BUNKER_1_XPOSITION ((SCREEN_WIDTH/4) + BUNKER_OFFSET)
#define BUNKER_2_XPOSITION ((2 * (SCREEN_WIDTH/4)) + BUNKER_OFFSET)
#define BUNKER_3_XPOSITION ((3 * (SCREEN_WIDTH/4)) + BUNKER_OFFSET)



// Packs each horizontal line of the figures into a single 32 bit word.
#define packWord32(b31,b30,b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
((b31 << 31) | (b30 << 30) | (b29 << 29) | (b28 << 28) | (b27 << 27) | (b26 << 26) | (b25 << 25) | (b24 << 24) |						  \
 (b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packWord30(b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)		  \
((b29 << 29) | (b28 << 28) | (b27 << 27) | (b26 << 26) | (b25 << 25) | (b24 << 24) |													  \
 (b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )


#define packWord24(b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)		  						  \
 ((b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
 (b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )


#define packWord12(b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)		  \
((b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |		  \
 (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) |		  \
 (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packWord6(b5,b4,b3,b2,b1,b0) \
((b5  << 5 ) | (b4  << 4 ) |		  \
 (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packWord4(b3,b2,b1,b0) \
( (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

#define packWord2(b1,b0)	\
((b1  << 1 ) | (b0  << 0 ) )



typedef struct {short x; short y;} point_t;




void globals_init();

int getShipAlive();
void setShipAlive(int alive);

int getLives();
void setLives(int newlives);

void setTankPositionGlobal(unsigned short val);
unsigned short getTankPositionGlobal();

void setTankBulletPosition(point_t val);
point_t getTankBulletPosition();

void setShipPos(unsigned short val);
unsigned int getShipPos();

void setMovement(int movement);
int getMovement();

void setAlienLocation(point_t loc);
point_t getAlienLocation();

int getNumAlienBullet();
void setNumAlienBullet(int val);

int getNumTankBullet();
void setNumTankBullet(int val);

point_t* getAlienBulletPos();
void updateAlienBulletPos(point_t pos, int index);

void setScore(int newscore);
int getScore();

//bitmaps of the space invader graphics

static const int alien_top_out[ALIEN_HEIGHT] =
{
	packWord32(0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0)
};

static const int alien_top_in[ALIEN_HEIGHT] =
{
	packWord32(0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
};

static const int saucer[SAUCER_HEIGHT] =
{
	packWord32(0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0),
	packWord32(0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0),
	packWord32(0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0),
	packWord32(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord32(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord32(0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0)
};

static const int alien_explosion[EXPLOSION_HEIGHT] =
{
	packWord32(0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
};

static const int alien_middle_in[ALIEN_HEIGHT] =
{
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
};

static const int alien_middle_out[ALIEN_HEIGHT] =
{
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0)
};

static const int alien_bottom_in[ALIEN_HEIGHT] =
{
	packWord32(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0)
};

static const int alien_bottom_out[ALIEN_HEIGHT] =
{
	packWord32(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord32(1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0)
};

static const int tank[] =
{
	packWord30(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord30(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord30(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord30(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord30(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord30(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord30(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0),
	packWord30(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0),
	packWord30(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord30(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord30(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord30(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord30(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord30(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord30(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord30(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)
};

// Shape of the left half of bunker.
static const int bunkerLeft[BUNKER_HEIGHT] =
{
	packWord24(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0)
};


// Shape of the right half of bunker.
static const int bunkerRight[BUNKER_HEIGHT] =
{
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1),
	packWord24(0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1)
};

// These are the blocks that comprise the bunker and each time a bullet
// strikes one of these blocks, you erod the block as you sequence through
// these patterns.
static const int bunkerDamage0[] =
{
	packWord12(0,0,1,1,1,1,0,0,0,0,0,0),
	packWord12(0,0,1,1,1,1,0,0,0,0,0,0),
	packWord12(0,0,0,0,0,0,0,0,0,0,1,1),
	packWord12(0,0,0,0,0,0,0,0,0,0,1,1),
	packWord12(1,1,1,1,0,0,1,1,0,0,0,0),
	packWord12(1,1,1,1,0,0,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(0,0,0,0,1,1,1,1,0,0,0,0),
	packWord12(0,0,0,0,1,1,1,1,0,0,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0)
};

static const int bunkerDamage1[] =
{
	packWord12(1,1,1,1,1,1,0,0,1,1,0,0),
	packWord12(1,1,1,1,1,1,0,0,1,1,0,0),
	packWord12(1,1,0,0,1,1,0,0,0,0,1,1),
	packWord12(1,1,0,0,1,1,0,0,0,0,1,1),
	packWord12(1,1,1,1,0,0,1,1,1,1,1,1),
	packWord12(1,1,1,1,0,0,1,1,1,1,1,1),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,1,1),
	packWord12(0,0,1,1,1,1,1,1,0,0,1,1),
	packWord12(0,0,1,1,1,1,0,0,1,1,0,0),
	packWord12(0,0,1,1,1,1,0,0,1,1,0,0)
};

static const int bunkerDamage2[] =
{
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,0,0,1,1,1,1,0,0,1,1),
	packWord12(1,1,0,0,1,1,1,1,0,0,1,1),
	packWord12(1,1,1,1,0,0,1,1,1,1,1,1),
	packWord12(1,1,1,1,0,0,1,1,1,1,1,1),
	packWord12(1,1,1,1,0,0,1,1,1,1,0,0),
	packWord12(1,1,1,1,0,0,1,1,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,1,1),
	packWord12(0,0,1,1,1,1,1,1,0,0,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1)
};

static const int bunkerDamage3[] =
{
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1),
	packWord12(1,1,1,1,1,1,1,1,1,1,1,1)
};

static const char tankBullet_graphic[] =
{
	packWord2(1,1),
	packWord2(1,1),
	packWord2(1,1),
	packWord2(1,1)
};

static const short alien_bullet1_1[] =
{
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(1,1,1,1,1,1),
	packWord6(1,1,1,1,1,1),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0)
};

static const short alien_bullet1_2[] =
{
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(1,1,1,1,1,1),
	packWord6(1,1,1,1,1,1),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0)
};

static const short alien_bullet1_3[] =
{
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(1,1,1,1,1,1),
	packWord6(1,1,1,1,1,1),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0)
};

static const short alien_bullet2_1[] =
{
	packWord6(1,1,0,0,0,0),
	packWord6(1,1,0,0,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,0,0,1,1),
	packWord6(0,0,0,0,1,1),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(1,1,0,0,0,0),
	packWord6(1,1,0,0,0,0)
};

static const short alien_bullet2_2[] =
{
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(1,1,0,0,0,0),
	packWord6(1,1,0,0,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,0,0,1,1),
	packWord6(0,0,0,0,1,1),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0)
};

static const short alien_bullet2_3[] =
{
	packWord6(0,0,0,0,1,1),
	packWord6(0,0,0,0,1,1),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(1,1,0,0,0,0),
	packWord6(1,1,0,0,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,0,0,1,1),
	packWord6(0,0,0,0,1,1)
};

static const short alien_bullet2_4[] =
{
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,0,0,1,1),
	packWord6(0,0,0,0,1,1),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(1,1,0,0,0,0),
	packWord6(1,1,0,0,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0)
};

static const int s_bitmap[] =
{
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0)
};

static const int c_bitmap[] =
{
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0)
};

static const int o_bitmap[] =
{
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0)
};

static const int r_bitmap[] =
{
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0)
};

static const int e_bitmap[] =
{
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0)
};

static const int l_bitmap[] =
{
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0)
};

static const int i_bitmap[] =
{
	packWord4(1,1,0,0),
	packWord4(1,1,0,0),
	packWord4(1,1,0,0),
	packWord4(1,1,0,0),
	packWord4(1,1,0,0),
	packWord4(1,1,0,0),
	packWord4(1,1,0,0),
	packWord4(1,1,0,0),
	packWord4(1,1,0,0),
	packWord4(1,1,0,0),
};

static const int v_bitmap[] =
{
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,1,1,0,0,1,1,0,0,0,0),
	packWord12(0,0,1,1,0,0,1,1,0,0,0,0),
	packWord12(0,0,0,0,1,1,0,0,0,0,0,0),
	packWord12(0,0,0,0,1,1,0,0,0,0,0,0)
};


static const int num_bitmap_0[] =
{
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0)
};

static const int num_bitmap_1[] =
{
	packWord6(1,1,1,1,0,0),
	packWord6(1,1,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
	packWord6(0,0,1,1,0,0),
};

static const int num_bitmap_2[] =
{
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0)
};


static const int num_bitmap_3[] =
{
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0)
};

static const int num_bitmap_4[] =
{
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0)
};


static const int num_bitmap_5[] =
{
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0)
};

static const int num_bitmap_6[] =
{
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0)
};

static const int num_bitmap_7[] =
{
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,1,1,0,0,0,0),
	packWord12(0,0,0,0,0,0,1,1,0,0,0,0),
	packWord12(0,0,0,0,0,0,1,1,0,0,0,0),
	packWord12(0,0,0,0,0,0,1,1,0,0,0,0)
};

static const int num_bitmap_8[] =
{
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0)
};

static const int num_bitmap_9[] =
{
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(1,1,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,0,0,0,0,0,0,1,1,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0),
	packWord12(0,0,1,1,1,1,1,1,0,0,0,0)
};


#endif /* GLOBALS_H_ */
