/*
 * graphics.h
 *
 *  Created on: Sep 28, 2015
 *      Author: superman
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_



void graphics_init(unsigned int * framePointer);

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
