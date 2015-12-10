/*
 * graphics.h
 *
 *  Created on: Sep 28, 2015
 *      Author: superman
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#define MASK_ONE 0x1
#define ALIEN_WIDTH 32
#define ROW_SPACING 10
#define DEBUG 0
#define ALIEN_HORIZONTAL_DISTANCE 4
#define ALIEN_VERTICAL_DISTANCE 10
#define NUM_ALIEN_COL 11
#define NUM_ALIEN_ROW 5
#define TOTAL_NUM_ALIENS (NUM_ALIEN_COL * NUM_ALIEN_ROW)
#define WHITE 0xFFFFFFFF
#define GREEN 0x000FFF00
#define BLACK 0x00000000
#define RED 0xFFF00000
#define TANK_MOVE_DISTANCE 4
#define TANK_BULLET_SPEED 4
#define ALIEN_BULLET_OFFSET 4
#define NUM_ALIEN_BULLET_TYPES 2
#define ALIEN_BULLET_SPEED 4
#define BEGINNING_SRAND 77



void graphics_init(unsigned int * framePointer0, unsigned int * framePointerbg, unsigned int * framePointer2);

void alienMarch();

void paintAliens();

void killAlien(int alienId);

int getFirstColAlive();

int getLastColAlive();

void tankMove(int direction);

void paintTankDead();

void paintTank();

void bulletMove();

void fireBullet();

void fireAlienBullet();

void removeTankBullet();

void paintBunker(int bunkerId);

void bunkerHit(int bunkerId, int hitLocation);

void paintWords();

void paintTankLives();

void paintEarthLine();

//Returns 1 if the alienID is alive or 0 if it is dead
int getAlienAlive(int alienID);

void paintScore();

void paintShip();

void paintShipScore(int flash);

void marchShip();

void removeShip();

int getShipDirection();

void setShipDirection(int direction);

void paintScreenCapture();
void paintAfterScreenCapture();

void softwareScreenCapture();


#endif /* GRAPHICS_H_ */
