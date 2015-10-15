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
#define DEBUG
#define ALIEN_HORIZONTAL_DISTANCE 4
#define ALIEN_VERTICAL_DISTANCE 10
#define NUM_ALIEN_COL 11
#define NUM_ALIEN_ROW 5
#define WHITE 0xFFFFFFFF
#define GREEN 0x000FFF00
#define BLACK 0x00000000
#define TANK_MOVE_DISTANCE 4
#define TANK_BULLET_SPEED 4
#define ALIEN_BULLET_OFFSET 4
#define NUM_ALIEN_BULLET_TYPES 2
#define ALIEN_BULLET_SPEED 4
#define BEGINNING_SRAND 77



void graphics_init(unsigned int * framePointer, unsigned int * framePointerbg);

void alienMarch();

void paintAliens();

void killAlien(int alienId);


void tankMove(int direction);

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

#endif /* GRAPHICS_H_ */
