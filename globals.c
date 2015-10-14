/*
 * globals.c
 *
 *  Created on: Sep 28, 2015
 *      Author: CT
 */
#include "globals.h"


unsigned int tankpos;
point_t tankBullet;
point_t alienlocation;
int movement; //1 is out, 0 is in
int numtankbullet;
int numalienbullets;
point_t alienbulletpos[MAX_ALIEN_BULLETS];
char bunker0Damage;
char bunker1Damage;
char bunker2Damage;
char bunker3Damage;
int score;
int lives;


void globals_init()
{
	movement = 0;
	numtankbullet = 0;
	tankpos = SCREEN_WIDTH/2 - TANK_WIDTH/2;
	tankBullet.x = 0;
	tankBullet.y = 0;
	alienlocation.x = 0;
	alienlocation.y = ALIEN_START_Y;
	bunker0Damage = 0;
	bunker1Damage = 0;
	bunker2Damage = 0;
	bunker3Damage = 0;
	score = 0;
	lives = MAX_LIVES;
}

int getLives()
{
	return lives;
}
void setLives(int newlives)
{
	lives = newlives;
}

void setScore(int newscore)
{
	score = newscore;
}

int getScore()
{
	return score;
}

char getBunkerDamage(int bunkerId)
{
	switch (bunkerId)
	{
		case 0:
			return bunker0Damage;
			break;
		case 1:
			return bunker1Damage;
			break;
		case 2:
			return bunker2Damage;
			break;
		case 3:
			return bunker3Damage;
			break;
		default:
			return -1;
			break;
	}
}


void incrementBunkerDamage(int bunkerId)
{
	switch (bunkerId)
	{
		case 0:
			if(bunker0Damage >= MAX_BUNKER_DAMAGE)
			{
				bunker0Damage++;
			}
			break;
		case 1:
			if(bunker1Damage >= MAX_BUNKER_DAMAGE)
			{
				bunker1Damage++;
			}
			break;
		case 2:
			if(bunker2Damage >= MAX_BUNKER_DAMAGE)
			{
				bunker2Damage++;
			}
			break;
		case 3:
			if(bunker3Damage >= MAX_BUNKER_DAMAGE)
			{
				bunker3Damage++;
			}
			break;
		default:
			break;
	}
}

point_t* getAlienBulletPos()
{
	return alienbulletpos;
}
void updateAlienBulletPos(point_t pos, int index)
{
	alienbulletpos[index].x = pos.x;
	alienbulletpos[index].y = pos.y;
}

int getNumTankBullet()
{
	return numtankbullet;
}

void setNumTankBullet(int val)
{
	numtankbullet = val;
}

int getNumAlienBullet()
{
	return numtankbullet;
}

void setNumAlienBullet(int val)
{
	numtankbullet = val;
}


void setTankPositionGlobal(unsigned short val)
{
	tankpos = val;
}

unsigned short getTankPositionGlobal()
{
	return tankpos;
}

void setTankBulletPosition(point_t val)
{
	tankBullet.x = val.x;
	tankBullet.y = val.y;
}

point_t getTankBulletPosition()
{
	return tankBullet;
}

void setMovement(int i)
{
	movement = i;
}
int getMovement()
{
	return movement;
}

void setAlienLocation(point_t loc)
{
	alienlocation.x = loc.x;
	alienlocation.y = loc.y;
}

point_t getAlienLocation()
{
	return alienlocation;
}


