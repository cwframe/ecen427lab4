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
int bunker0Damage[] = {0,0,0,0,0,0,0,0,0,0,0,0};
int bunker1Damage[] = {0,0,0,0,0,0,0,0,0,0,0,0};
int bunker2Damage[] = {0,0,0,0,0,0,0,0,0,0,0,0};
int bunker3Damage[] = {0,0,0,0,0,0,0,0,0,0,0,0};
int score;
int lives;
unsigned int shippos;
char shipActive;
char shipAlive;

void globals_init()
{
	movement = 0;
	numtankbullet = 0;
	tankpos = BUNKER_1_XPOSITION;
	tankBullet.x = 0;
	tankBullet.y = 0;
	alienlocation.x = 0;
	alienlocation.y = ALIEN_START_Y;
	score = 0;
	lives = MAX_LIVES;
	shipAlive = 0;
}

char getShipActive()
{
    return shipActive;
}

void setShipActive(char active)
{
    shipActive = active;
}

char getShipAlive()
{
	return shipAlive;
}

void setShipAlive(char alive)
{
	shipAlive = alive;
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

void setShipPos(unsigned short val)
{
	shippos = val;
}
unsigned int getShipPos()
{
	return shippos;
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

int getBunkerDamage(point_t bunkerDamageID)
{
	switch(bunkerDamageID.x)
	{
		case 0:
			return bunker0Damage[bunkerDamageID.y];
			break;
		case 1:
			return bunker1Damage[bunkerDamageID.y];
			break;
		case 2:
			return bunker2Damage[bunkerDamageID.y];
			break;
		case 3:
			return bunker3Damage[bunkerDamageID.y];
			break;
	}
	return -1;
}

void incrementBunkerDamage(point_t bunkerDamageID)
{
	switch(bunkerDamageID.x)
	{
		case 0:
			bunker0Damage[bunkerDamageID.y]++;
			break;
		case 1:
			bunker1Damage[bunkerDamageID.y]++;
			break;
		case 2:
			bunker2Damage[bunkerDamageID.y]++;
			break;
		case 3:
			bunker3Damage[bunkerDamageID.y]++;
			break;
	}
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


