/*
 * Graphics.c
 *
 *  Created on: Sep 28, 2015
 *      Author: superman
 */
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "xio.h"
#include "time.h"
#include "unistd.h"
#include "globals.h"
#include "graphics.h"
#include "input.h"
#include "gameLogic.h"
#include "sound.h"




void print(char *str);



//pos moves right, neg moves left, zero moves down
char movementdirection;

unsigned int * framePointer;
unsigned int * framePointerBackground;

int alienAlive[NUM_ALIEN_COL * NUM_ALIEN_ROW];
int alienMarchNum = 1;
int alienBullet[MAX_ALIEN_BULLETS];
int currentalienbullets;
int shipdirection;
int oldscorearray[4] = {-1,-1,-1,-1};

int getShipDirection()
{
	return shipdirection;
}

void setShipDirection(int direction)
{
	shipdirection = direction;
}

void graphics_init(unsigned int * framePointer0, unsigned int * framePointerbg)
{
	//start moving to the right
	xil_printf("paused at start up \n\r");
	pauseGame();
	oldscorearray[0] = -1;
	oldscorearray[1] = -1;
	oldscorearray[2] = -1;
	oldscorearray[3] = -1;
	movementdirection = 1;
	shipdirection = 1;
	framePointer = framePointer0;
	framePointerBackground = framePointerbg;
	paintWords();
	paintTankLives();
	paintTank();
	paintBunker(0);
	paintBunker(1);
	paintBunker(2);
	paintBunker(3);
	currentalienbullets = 0;
	int i;
	for(i = 0; i < NUM_ALIEN_COL * NUM_ALIEN_ROW; i++)
	{
		alienAlive[i] = 1;
	}
	for(i = 0; i < MAX_ALIEN_BULLETS; i++)
	{
		alienBullet[i] = 0;
	}
	srand(BEGINNING_SRAND);
	paintAliens();
	paintEarthLine();
	paintScore();
}

void paintShip()
{
	int row, col, color, pos;
	for(row = 0; row < SHIP_HEIGHT; row++)
	{
		for(col = 0; col < SHIP_WIDTH; col++)
		{
			pos = (row + SHIP_Y) * SCREEN_WIDTH + col + getShipPos();
			color = ((saucer[row] >> (SHIP_WIDTH-1-col)) & MASK_ONE);
			if(color && (getShipPos() + col) < SCREEN_WIDTH && (getShipPos() + col) > 0)
				framePointer[pos] = RED;
			else
				framePointer[pos] = framePointerBackground[pos];
		}
	}
	//clear behind
	for(row = 0; row < SHIP_HEIGHT; row++)
	{
		for(col = 0; col < SHIP_SPEED; col++)
		{
			if(shipdirection)
				pos = (row + SHIP_Y) * SCREEN_WIDTH - (col+1) + getShipPos();
			else
				pos = (row + SHIP_Y) * SCREEN_WIDTH + col + getShipPos() + SHIP_WIDTH;
			framePointer[pos] = framePointerBackground[pos];
		}
	}
}

void removeShip()
{
	int row, col, pos;
	for(row = 0; row < SHIP_HEIGHT; row++)
	{
		for(col = 0; col < SHIP_WIDTH; col++)
		{
			pos = (row + SHIP_Y) * SCREEN_WIDTH + col + getShipPos();
			framePointer[pos] = framePointerBackground[pos];
		}
	}

	setShipActive(0);

	shipdirection = !shipdirection;
}

void marchShip()
{
	if(shipdirection)
	{
		setShipPos(getShipPos()+SHIP_SPEED);
	}
	else
	{
		setShipPos(getShipPos()-SHIP_SPEED);
	}
	if(getShipPos() < -SHIP_WIDTH || getShipPos() > SCREEN_WIDTH + SHIP_WIDTH)
	{
		removeShip();
	}
	else
	{
		paintShip();
	}


}



void paintWords()
{
	int row, col;
	for(row = 0; row < ALPHA_NUM_HEIGHT; row++)
	{
		for(col = 0; col < ALPHA_NUM_WIDTH; col++)
		{
			//print score
			framePointer[(row + SCORE_Y)*SCREEN_WIDTH + col + SCORE_X] = (WHITE) * ((s_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointer[(row + SCORE_Y)*SCREEN_WIDTH + col + SCORE_X + ALPHA_NUM_WIDTH] = (WHITE) * ((c_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointer[(row + SCORE_Y)*SCREEN_WIDTH + col + SCORE_X + ALPHA_NUM_WIDTH * 2] = (WHITE) * ((o_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointer[(row + SCORE_Y)*SCREEN_WIDTH + col + SCORE_X + ALPHA_NUM_WIDTH * 3] = (WHITE) * ((r_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointer[(row + SCORE_Y)*SCREEN_WIDTH + col + SCORE_X + ALPHA_NUM_WIDTH * 4] = (WHITE) * ((e_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);

			//set up background frame
			framePointerBackground[(row + SCORE_Y)*SCREEN_WIDTH + col + SCORE_X] = (WHITE) * ((s_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointerBackground[(row + SCORE_Y)*SCREEN_WIDTH + col + SCORE_X + ALPHA_NUM_WIDTH] = (WHITE) * ((c_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointerBackground[(row + SCORE_Y)*SCREEN_WIDTH + col + SCORE_X + ALPHA_NUM_WIDTH * 2] = (WHITE) * ((o_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointerBackground[(row + SCORE_Y)*SCREEN_WIDTH + col + SCORE_X + ALPHA_NUM_WIDTH * 3] = (WHITE) * ((r_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointerBackground[(row + SCORE_Y)*SCREEN_WIDTH + col + SCORE_X + ALPHA_NUM_WIDTH * 4] = (WHITE) * ((e_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);

			//print lives
			framePointer[(row + LIVES_Y)*SCREEN_WIDTH + col + LIVES_X] = (WHITE) * ((l_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			if(col < ALPHA_I_WIDTH)
			{
				framePointer[(row + LIVES_Y)*SCREEN_WIDTH + col + LIVES_X + ALPHA_NUM_WIDTH] = (WHITE) * ((i_bitmap[row] >> (ALPHA_I_WIDTH-1-col)) & MASK_ONE);
			}
			framePointer[(row + LIVES_Y)*SCREEN_WIDTH + col + LIVES_X + ALPHA_NUM_WIDTH + ALPHA_I_WIDTH] = (WHITE) * ((v_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointer[(row + LIVES_Y)*SCREEN_WIDTH + col + LIVES_X + ALPHA_NUM_WIDTH * 2 + ALPHA_I_WIDTH] = (WHITE) * ((e_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointer[(row + LIVES_Y)*SCREEN_WIDTH + col + LIVES_X + ALPHA_NUM_WIDTH * 3 + ALPHA_I_WIDTH] = (WHITE) * ((s_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);


			framePointerBackground[(row + LIVES_Y)*SCREEN_WIDTH + col + LIVES_X] = (WHITE) * ((l_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			if(col < ALPHA_I_WIDTH)
			{
				framePointerBackground[(row + LIVES_Y)*SCREEN_WIDTH + col + LIVES_X + ALPHA_NUM_WIDTH] = (WHITE) * ((i_bitmap[row] >> (ALPHA_I_WIDTH-1-col)) & MASK_ONE);
			}
			framePointerBackground[(row + LIVES_Y)*SCREEN_WIDTH + col + LIVES_X + ALPHA_NUM_WIDTH + ALPHA_I_WIDTH] = (WHITE) * ((v_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointerBackground[(row + LIVES_Y)*SCREEN_WIDTH + col + LIVES_X + ALPHA_NUM_WIDTH * 2 + ALPHA_I_WIDTH] = (WHITE) * ((e_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
			framePointerBackground[(row + LIVES_Y)*SCREEN_WIDTH + col + LIVES_X + ALPHA_NUM_WIDTH * 3 + ALPHA_I_WIDTH] = (WHITE) * ((s_bitmap[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
		}
	}
}


int getThousands()
{
	return getScore() / 1000;
}

int getHundreds()
{
	return (getScore() - getThousands() * 1000) / 100;
}

int getTens()
{
	return (getScore() - ((getThousands() * 1000) + getHundreds() * 100))/10;
}

int getOnes()
{
	return (getScore() - ((getThousands() * 1000) + getHundreds() * 100 + getTens()*10));
}

void paintScore()
{
	int row, col, pos, color, i, num;
	int offset = SCORE_NUM_X;
	int scorearray[4] = {getThousands(), getHundreds(), getTens(), getOnes()};
	for(i = 0; i < 4; i++)
	{
		num = scorearray[i];
		if(scorearray[i] != oldscorearray[i])
		{
			oldscorearray[i] = scorearray[i];
			for(row = 0; row < ALPHA_NUM_HEIGHT; row++)
			{
				for(col = 0; col < ALPHA_NUM_WIDTH; col++)
				{

					pos = (row + SCORE_Y)*SCREEN_WIDTH + col + offset;
					switch(num)
					{
						case 0:
							color = ((num_bitmap_0[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
							break;
						case 1:
							color = ((num_bitmap_1[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
							break;
						case 2:
							color = ((num_bitmap_2[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
							break;
						case 3:
							color = ((num_bitmap_3[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
							break;
						case 4:
							color = ((num_bitmap_4[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
							break;
						case 5:
							color = ((num_bitmap_5[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
							break;
						case 6:
							color = ((num_bitmap_6[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
							break;
						case 7:
							color = ((num_bitmap_7[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
							break;
						case 8:
							color = ((num_bitmap_8[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
							break;
						case 9:
							color = ((num_bitmap_9[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
							break;
					}
					if(color)
						framePointer[pos] =GREEN;
					else
						framePointer[pos] = framePointerBackground[pos];
				}
			}
		}
		offset += ALPHA_NUM_WIDTH;
	}
}

void paintTankLives()
{
	int life, row, col, pos, color;
	int lifecount = getLives();
	for(life = 0; life < MAX_LIVES; life++)
	{
		for(row = 0; row < TANK_HEIGHT; row++)
		{
			for(col = 0; col < TANK_WIDTH; col++)
			{
				pos = (row + TANK_LIVES_Y)*SCREEN_WIDTH + col + TANK_LIVES_X + (life * (TANK_WIDTH + TANK_LIVES_SPACING));
				if(life < lifecount)
					color = (GREEN) * ((tank[row] >> (TANK_WIDTH-1-col)) & MASK_ONE);
				else
					color = 0;
				if(color)
					framePointer[pos] = GREEN;
				else
					framePointer[pos] = framePointerBackground[pos];
			}
		}
	}
}



int getFirstColAlive()
{
	int i, result;
	for(i = 0; i < NUM_ALIEN_COL; i++)
	{
		if(alienAlive[i] || alienAlive[i + NUM_ALIEN_COL] || alienAlive[i + NUM_ALIEN_COL * 2] || alienAlive[i + NUM_ALIEN_COL * 3] || alienAlive[i + NUM_ALIEN_COL * 4])
		{
			result = i;
			break;
		}
	}
	return i;
}

int  getLastColAlive()
{
	int i, result;
	for(i = NUM_ALIEN_COL-1; i >= 0; i--)
	{
		if(alienAlive[i] || alienAlive[i + NUM_ALIEN_COL] || alienAlive[i + NUM_ALIEN_COL * 2] || alienAlive[i + NUM_ALIEN_COL * 3] || alienAlive[i + NUM_ALIEN_COL * 4])
		{
			result = i;
			break;
		}
	}
	return i;
}


//marches the aliens a distance of ALIEN_HORIZONTAL_DISTANCE or ALIEN_VERTICAL_DISTANCE
//depending on which direction the aliens are moving
void alienMarch()
{
	int leftendofaliens, rightendofaliens;
	setMovement(!getMovement());

	//Play alien sound

	switch(alienMarchNum)
	{
	case 1:
		setSound(march1_getSound(),march1_getNumFrames(), ALIEN_MARCH_PRIORITY);

		break;
	case 2:
		setSound(march2_getSound(),march2_getNumFrames(), ALIEN_MARCH_PRIORITY);


		break;
	case 3:
		setSound(march3_getSound(),march3_getNumFrames(), ALIEN_MARCH_PRIORITY);


		break;
	case 4:
		setSound(march4_getSound(),march4_getNumFrames(), ALIEN_MARCH_PRIORITY);

		break;
	default:
		break;
	}

	if(alienMarchNum == 4)
	{
		alienMarchNum = 1;
	}
	else
	{
		alienMarchNum++;
	}


	//check outofbounds
	point_t newloc = getAlienLocation();
	leftendofaliens = newloc.x + (getFirstColAlive() * ALIEN_WIDTH);
	rightendofaliens = newloc.x + (ALIEN_WIDTH * (getLastColAlive() + 1));
	if(rightendofaliens + ALIEN_HORIZONTAL_DISTANCE >= SCREEN_WIDTH
				&& movementdirection >= 0)
	{
		movementdirection--;
	}
	else if((leftendofaliens - ALIEN_HORIZONTAL_DISTANCE) <= 0)
	{
		movementdirection++;
	}
	if(movementdirection > 0)
	{
		newloc.x += ALIEN_HORIZONTAL_DISTANCE;
	}
	else if (movementdirection < 0)
	{
		newloc.x -= ALIEN_HORIZONTAL_DISTANCE;
	}
	else
	{
		newloc.y += ALIEN_VERTICAL_DISTANCE;
	}
	setAlienLocation(newloc);
	paintAliens();


	//Check for bunker collisions and damage the bunker if they hit the bunker.
	int i;
	for(i = 0; i < TOTAL_NUM_ALIENS; i++)
	{
		if(getAlienAlive(i))
		{
			point_t tempPoint2 = alienPosition(i);
			tempPoint2.y += ALIEN_HEIGHT;
			if(tempPoint2.y > ARBRITARY_LINE_OF_DOOM)
			{
				pauseGame();
				setLives(0);
			}
			tempPoint2.x += ALIEN_WIDTH/2;
			point_t tempPoint = bunkerHitDetection(tempPoint2);
			if(tempPoint.x != -1)
			{
				if(getBunkerDamage(tempPoint) < MAX_BUNKER_DAMAGE)
				bunkerHit(tempPoint.x, tempPoint.y);
				paintAlien(i);
			}
		}
	}
}



void paintAlien(int alienId)
{
	int alien_col, row, inbetween, col, alien_row, aliencolor, pos;
	point_t alienpos = alienPosition(alienId);
	for(row = 0; row < ALIEN_HEIGHT; row++)
	{
		for(col = 0; col < ALIEN_WIDTH; col++)
		{
			pos = (row + alienpos.y)*SCREEN_WIDTH + col + alienpos.x;
			if(getMovement())
			{
				if(alienId < NUM_ALIEN_COL)
					aliencolor = ((alien_top_out[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
				else if(alienId < NUM_ALIEN_COL * 3)
					aliencolor = ((alien_middle_out[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
				else
					aliencolor = ((alien_bottom_out[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
			}
			else
			{
				if(alienId < NUM_ALIEN_COL)
					aliencolor = ((alien_top_in[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
				else if(alienId < NUM_ALIEN_COL * 3)
					aliencolor = ((alien_middle_in[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
				else
					aliencolor = ((alien_bottom_in[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
			}
			if(aliencolor)
				framePointer[pos] = WHITE;
			else
				framePointer[pos] = framePointerBackground[pos];
		}
	}
}

void eraseExplosion(alienId)
{
	int row, col, pos;
	alienAlive[alienId] = 0;
	point_t alienpos = alienPosition(alienId);
	for(row = 0; row < EXPLOSION_HEIGHT + 2; row++)
	{
		for(col = EXPLOSION_ERASE_COL_START; col < ALIEN_WIDTH; col++)
		{
			pos = (row + alienpos.y)*SCREEN_WIDTH + col + alienpos.x;
			framePointer[pos] = framePointerBackground[pos];
		}
	}
}

void eraseTrail(int alienId)
{
	if(alienId < NUM_ALIEN_COL || movementdirection <= 0)
	{
		//no trails left
		return;
	}
	int row, col, pos;
	point_t alienpos = alienPosition(alienId);
	for(row = 0; row < ALIEN_HEIGHT; row++)
	{
		for(col = 1; col <= ALIEN_HORIZONTAL_DISTANCE; col++)
		{
			pos = (row + alienpos.y)*SCREEN_WIDTH - col + alienpos.x + ALIEN_WIDTH;
			framePointer[pos] = framePointerBackground[pos];
		}
	}
}

void eraseFirstTrail()
{
	int row, col, pos, alienId, i;
	for(i = 1; i < NUM_ALIEN_COL; i++)
	{
		alienId = i*NUM_ALIEN_COL;
		if(alienAlive[alienId])
		{
			point_t alienpos = alienPosition(alienId);
			for(row = 0; row < ALIEN_HEIGHT; row++)
			{
				for(col = 0; col < ALIEN_HORIZONTAL_DISTANCE; col++)
				{
					pos = (row + alienpos.y)*SCREEN_WIDTH + col + alienpos.x - ALIEN_HORIZONTAL_DISTANCE;
					framePointer[pos] = framePointerBackground[pos];
				}
			}
		}
	}
}

void eraseInBetweenRows()
{
	int row, col, pos, alienId, i;
	alienId = i*NUM_ALIEN_COL;
	for(i = 0; i < NUM_ALIEN_COL * NUM_ALIEN_ROW; i++)
	{
		alienId = i;
		point_t alienpos = alienPosition(alienId);
		for(row = 1; row <= ALIEN_VERTICAL_DISTANCE; row++)
		{
			for(col = 0; col < ALIEN_WIDTH; col++)
			{
				pos = (alienpos.y - row)*SCREEN_WIDTH + col + alienpos.x;
				framePointer[pos] = framePointerBackground[pos];
			}
		}
	}

}

void paintAliens()
{
	int  i;
	for(i = 0; i < NUM_ALIEN_COL*NUM_ALIEN_ROW; i++)
	{
		if(alienAlive[i] == 1)
			paintAlien(i);
		else if (alienAlive[i] > 1)
		{
			eraseExplosion(i);
		}
		else
		{
			//print black square
			eraseTrail(i);
		}
	}
	playSound();
	eraseFirstTrail();
	if(movementdirection == 0)
	{
		eraseInBetweenRows();
	}
}

void killAlien(int alienId)
{
	if(alienId >= 0 && alienId < NUM_ALIEN_COL * NUM_ALIEN_ROW)
	{
		alienAlive[alienId] = 2;
		removeTankBullet();
		if(alienId < NUM_ALIEN_COL)
			setScore(getScore()+TOP_ALIEN_SCORE);
		else if (alienId < NUM_ALIEN_COL * 3)
			setScore(getScore()+MIDDLE_ALIEN_SCORE);
		else
			setScore(getScore() + BOTTOM_ALIEN_SCORE);

		int alien_row = alienId / NUM_ALIEN_COL;
		int alien_col = alienId % NUM_ALIEN_COL;
		int row, col, pos, color;
		for(row = 0; row < EXPLOSION_HEIGHT; row++)
		{
			for(col = 0; col < ALIEN_WIDTH; col++)
			{
				pos = (row + getAlienLocation().y + (ALIEN_HEIGHT + ROW_SPACING) * alien_row) * SCREEN_WIDTH +
						col + (alien_col * ALIEN_WIDTH) + getAlienLocation().x;
				color = ((alien_explosion[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
				if(color)
					framePointer[pos] = WHITE;
				else
					framePointer[pos] = framePointerBackground[pos];

			}
		}
		setSound(explosion_getSound(), explosion_getNumFrames(), ALIEN_DEATH_PRIORITY);
		paintScore();
	}
	int i;
	for(i = 0; i < TOTAL_NUM_ALIENS; i++)
	{
		if(alienAlive[i])
			return;
	}
	pauseGame();
	setLives(0);


}

void paintShipScore(int flash)
{
	int row, col, pos, color, i, offset;
	offset = 0;
	for(i = 0; i < 3; i++)
	{
		for(row = 0; row < ALPHA_NUM_HEIGHT; row++)
		{
			for(col = 0; col < ALPHA_NUM_WIDTH; col++)
			{
				pos = (row+SHIP_Y)*SCREEN_WIDTH + col + getShipPos() + offset;
				switch (i)
				{
					case 0:
						color = ((num_bitmap_3[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
						break;
					case 1:
						color = ((num_bitmap_0[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
						break;
					case 2:
						color = ((num_bitmap_0[row] >> (ALPHA_NUM_WIDTH-1-col)) & MASK_ONE);
						break;
				}
				if(!flash)
				{
					color = 0;
				}
				if(color)
					framePointer[pos] = RED;
				else
					framePointer[pos] = framePointerBackground[pos];
			}
		}
		offset+= ALPHA_NUM_WIDTH;
	}
}

//moves the tank in the desired direction, 0 is left, non zero is right
void tankMove(int direction)
{
	if(direction && getTankPositionGlobal() < (SCREEN_WIDTH - (TANK_WIDTH + TANK_MOVE_DISTANCE)))
	{
		setTankPositionGlobal(getTankPositionGlobal() + TANK_MOVE_DISTANCE);
	}
	else if(getTankPositionGlobal() > TANK_MOVE_DISTANCE)
	{
		setTankPositionGlobal(getTankPositionGlobal() - TANK_MOVE_DISTANCE);
	}
	paintTank();
}

//draws the tank and erases any trails
void paintTank()
{
	int row, col, pos, color;
	for(row = 0; row < TANK_HEIGHT; row++)
	{
		for(col = 0; col < TANK_WIDTH; col++)
		{
			pos = ((TANK_Y_VALUE + row) * SCREEN_WIDTH) + (getTankPositionGlobal() + col);
			color = ((tank[row] >> (TANK_WIDTH-1-col)) & MASK_ONE);
			if (color)
				framePointer[pos] = (GREEN);
			else
				framePointer[pos] = framePointerBackground[pos];
		}
	}

	//Cover up any trails
	for(row = 0; row < TANK_HEIGHT; row++)
	{
		for(col = 0; col < TANK_MOVE_DISTANCE; col++)
		{
			pos = ((TANK_Y_VALUE + row) * SCREEN_WIDTH) + (getTankPositionGlobal() + col) - TANK_MOVE_DISTANCE;
			framePointer[pos] = framePointerBackground[pos];
			pos = ((TANK_Y_VALUE + row) * SCREEN_WIDTH) + (getTankPositionGlobal() + TANK_WIDTH + col);
			framePointer[pos] = framePointerBackground[pos];
		}
	}
}

//fires a bullet from the tank, there can only be one bullet at a time
void fireBullet()
{
	if(!getNumTankBullet())
	{
		setNumTankBullet(1);
		point_t bulletpos;
		bulletpos.x = (getTankPositionGlobal() + (TANK_WIDTH/2) - TANK_BULLET_WIDTH/2);
		bulletpos.y = TANK_Y_VALUE - TANK_BULLET_HEIGHT;
		setTankBulletPosition(bulletpos);
		setSound(shoot_getSound(),shoot_getNumFrames(), TANK_SHOOT_PRIORITY);
		bulletMove();
	}

}

//fires an alien bullet from a random alien on the bottom row
void fireAlienBullet()
{
	if(currentalienbullets >= MAX_ALIEN_BULLETS)
	{
		return;
	}
	int row, col, pos, color, i;
	int aliennum = rand() % NUM_ALIEN_COL;
	aliennum += NUM_ALIEN_COL * (NUM_ALIEN_ROW-1);
	while(!alienAlive[aliennum])
	{
		for(i = 0; i < NUM_ALIEN_ROW; i++)
		{
			if(alienAlive[aliennum])
			{
				break;
			}
			aliennum -= NUM_ALIEN_COL;
		}

		if(aliennum < 0)
			aliennum += NUM_ALIEN_COL;
		if(!alienAlive[aliennum])
		{
			aliennum++;
			if(aliennum > 10)
			{
				aliennum = 0;
			}
			aliennum += NUM_ALIEN_COL * (NUM_ALIEN_ROW-1);
		}
	}
	int bullettype = rand() % NUM_ALIEN_BULLET_TYPES; //to be implemented to fire different bullets
	//int bullettype = 1;
	point_t bulletpos;
	int currentbullet;
	point_t temp = alienPosition(aliennum);
	bulletpos.y = temp.y + ALIEN_HEIGHT;
	bulletpos.x = temp.x + (ALIEN_WIDTH/2) - ALIEN_BULLET_OFFSET;
	for(row = 0; row < MAX_ALIEN_BULLETS; row++)
	{
		if(alienBullet[row] <= 0)
		{
			currentbullet = row;
			break;
		}
	}
	updateAlienBulletPos(bulletpos, currentbullet);
	for(row = 0; row < ALIEN_BULLET_HEIGHT; row++)
	{
		for(col = 0; col < ALIEN_BULLET_WIDTH; col++)
		{
			pos = (row + bulletpos.y)*SCREEN_WIDTH + col + bulletpos.x;
			if(!bullettype) //paints the correct bullet
			{
				alienBullet[currentbullet] = 1;
				color = ((alien_bullet1_1[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);

			}
			else
			{
				alienBullet[currentbullet] = 5;
				color = ((alien_bullet2_1[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);
			}
			if(color)
				framePointer[pos] = WHITE;
			else
				framePointer[pos] = framePointerBackground[pos];

		}
	}
	currentalienbullets++;
}

//removes the tank bullet so the user can shoot another
void removeTankBullet()
{
	int row, col, pos;
	for(row = 0; row < TANK_BULLET_HEIGHT; row++)
	{
		for(col = 0; col < TANK_BULLET_WIDTH; col++)
		{
			pos = (getTankBulletPosition().y + row) * SCREEN_WIDTH + getTankBulletPosition().x + col;
			framePointer[pos] = framePointerBackground[pos];
		}
	}
	setNumTankBullet(0);
}

//erases the alien bullet that just moved off screen
void eraseAlienBullet(point_t alienbulletpos)
{
	int row, col, pos;
	for(row = 0; row < ALIEN_BULLET_HEIGHT; row++)
	{
		for(col = 0; col < ALIEN_BULLET_WIDTH; col++)
		{
			pos = (alienbulletpos.y + row) * SCREEN_WIDTH + col + alienbulletpos.x;
			framePointer[pos] = framePointerBackground[pos];
		}
	}
}

//moves tank bullet and alien bullets and redraws them
void bulletMove()
{
	//moves tankbullet
	int row, col, pos, color, alienhit;
	point_t bulletpos = getTankBulletPosition();
	if(bulletpos.y - TANK_BULLET_SPEED < EFFECTIVE_SCREEN_TOP)
	{
		removeTankBullet();
	}
	if(getNumTankBullet() > 0)
	{
		bulletpos.y -= TANK_BULLET_SPEED;
		setTankBulletPosition(bulletpos);
		point_t hitbulletpoint = getTankBulletPosition();
		hitbulletpoint.x += TANK_BULLET_WIDTH/2;
		alienhit = alienHitDetection(hitbulletpoint);
		for(row = 0; row < TANK_BULLET_HEIGHT; row++)
		{
			for(col = 0; col < TANK_BULLET_WIDTH; col++)
			{
				pos = (getTankBulletPosition().y + row) * SCREEN_WIDTH
						+ getTankBulletPosition().x + col;
				color = ((tankBullet_graphic[row] >> (TANK_BULLET_WIDTH-1-col)) & MASK_ONE);
				if(color)
					framePointer[pos] = WHITE;
				else
					framePointer[pos] = framePointerBackground[pos];
				pos = (getTankBulletPosition().y + row + TANK_BULLET_HEIGHT) * SCREEN_WIDTH +
						getTankBulletPosition().x + col;
				framePointer[pos] = framePointerBackground[pos];
			}
		}
		if(alienhit >= 0)
		{
			killAlien(alienhit);
		}
		else if(bulletpos.y > BUNKER_Y_VALUE && bulletpos.y < BUNKER_Y_VALUE + BUNKER_HEIGHT)
		{
			point_t temp = bunkerHitDetection(bulletpos);
			if(temp.x >= 0 && getBunkerDamage(temp) < MAX_BUNKER_DAMAGE)
			{
				bunkerHit(temp.x, temp.y);
				removeTankBullet();
			}
		}
		else if(bulletpos.y > SHIP_Y && bulletpos.y < SHIP_Y+SHIP_HEIGHT)
		{
			if(motherShipHitDetection(bulletpos))
			{
				setShipAlive(0);
				setShipActive(0);
				setMothershipKilled(1);
				removeShip();
				removeTankBullet();
				setScore(getScore() + SHIP_SCORE);
				paintScore();
			}
		}
	}



	//moves alien bullet
	int alienbullet;
	point_t alienbulletpos;
	for(alienbullet = 0; alienbullet < MAX_ALIEN_BULLETS; alienbullet++)
	{
		if(alienBullet[alienbullet] > 0)
		{
			alienbulletpos = getAlienBulletPos()[alienbullet];
			alienbulletpos.y += ALIEN_BULLET_SPEED;

			updateAlienBulletPos(alienbulletpos, alienbullet);
			alienbulletpos = getAlienBulletPos()[alienbullet];
			for(row = 0; row < ALIEN_BULLET_HEIGHT; row++)
			{
				for(col = 0; col < ALIEN_BULLET_WIDTH; col++)
				{
					pos = (alienbulletpos.y + row) * SCREEN_WIDTH + col + alienbulletpos.x;
					switch (alienBullet[alienbullet])
					{
						case 1:
							color = ((alien_bullet1_1[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);
							break;
						case 2:
							color = ((alien_bullet1_2[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);
							break;
						case 3:
							color = ((alien_bullet1_3[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);
							break;
						case 4:
							color = ((alien_bullet1_2[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);
							break;
						case 5:
							color = ((alien_bullet2_1[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);
							break;
						case 6:
							color = ((alien_bullet2_2[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);
							break;
						case 7:
							color = ((alien_bullet2_3[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);
							break;
						case 8:
							color = ((alien_bullet2_4[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);
							break;
					}
					if(color)
						framePointer[pos] = WHITE;
					else
						framePointer[pos] = framePointerBackground[pos];

					if(row <= ALIEN_BULLET_SPEED && row > 0)
					{
						pos = (alienbulletpos.y - row) * SCREEN_WIDTH + col + alienbulletpos.x;
						framePointer[pos] = framePointerBackground[pos];
					}
				}
			}
			switch(alienBullet[alienbullet])
			{
				case 1:
					alienBullet[alienbullet] = 2;
					break;
				case 2:
					alienBullet[alienbullet] = 3;
					break;
				case 3:
					alienBullet[alienbullet] = 4;
					break;
				case 4:
					alienBullet[alienbullet] = 1;
					break;
				case 5:
					alienBullet[alienbullet] = 6;
					break;
				case 6:
					alienBullet[alienbullet] = 7;
					break;
				case 7:
					alienBullet[alienbullet] = 8;
					break;
				case 8:
					alienBullet[alienbullet] = 5;
					break;
			}
			if(alienbulletpos.y + ALIEN_BULLET_HEIGHT> GREEN_EARTH_LINE_Y )
			{
				currentalienbullets--;
				alienBullet[alienbullet] = 0;
				eraseAlienBullet(alienbulletpos);
			}
			if(alienbulletpos.y + ALIEN_BULLET_HEIGHT > BUNKER_Y_VALUE && alienbulletpos.y < BUNKER_Y_VALUE+BUNKER_HEIGHT)
			{
				point_t alienbullethitpoint = alienbulletpos;
				alienbullethitpoint.y += ALIEN_BULLET_HEIGHT;
				alienbullethitpoint.x += ALIEN_BULLET_WIDTH/2;
				point_t temp = bunkerHitDetection(alienbullethitpoint);
				short bunkerid = temp.x;
				short bunkerarea = temp.y;
				if(bunkerid >= 0 && bunkerid <= 3 && bunkerarea >= 0 && bunkerarea <= 11 && getBunkerDamage(temp) < MAX_BUNKER_DAMAGE) //check magic numbers
				{
					currentalienbullets--;
					alienBullet[alienbullet] = 0;
					eraseAlienBullet(alienbulletpos);
					bunkerHit(bunkerid, bunkerarea);
				}
			}
			if(alienbulletpos.y > TANK_Y_VALUE && alienbulletpos.y < TANK_Y_VALUE + TANK_HEIGHT)
			{
				point_t alienbullethitpoint = alienbulletpos;
				alienbullethitpoint.y += ALIEN_BULLET_HEIGHT;
				alienbullethitpoint.x += ALIEN_BULLET_WIDTH/2;
				if(tankHitDetection(alienbullethitpoint))
				{

					currentalienbullets--;
					alienBullet[alienbullet] = 0;
					eraseAlienBullet(alienbulletpos);
					paintTankDead();
//					xil_printf("paused because tank was hit\n\r");
					pauseGame();
					setLives(getLives()-1);
					paintTankLives();
					//GAMEOVER
					//exit(0);
				}
			}
		}
	}
}

void paintTankDead()
{
	setSound(explosion_getSound(),explosion_getNumFrames(), TANK_DEATH_PRIORITY);
	int row, col, pos, color;
		for(row = 0; row < TANK_HEIGHT; row++)
		{
			for(col = 0; col < TANK_WIDTH; col++)
			{
				pos = ((TANK_Y_VALUE + row) * SCREEN_WIDTH) + (getTankPositionGlobal() + col);
				color = ((tank_dead[row] >> (TANK_WIDTH-1-col)) & MASK_ONE);
				if (color)
					framePointer[pos] = (GREEN);
				else
					framePointer[pos] = framePointerBackground[pos];
			}
		}
}

//Draws a bunker in the position indicated by bunkerID ie 0, 1, 2, 3
void paintBunker(int bunkerId)
{
	int row, col;
	for(row = 0; row < BUNKER_HEIGHT; row++)
	{
		for(col = 0; col < (BUNKER_WIDTH/2); col++)
		{
			framePointer[((BUNKER_Y_VALUE + row) * SCREEN_WIDTH) + 
				(col + (bunkerId * SCREEN_WIDTH/4)) + BUNKER_OFFSET] = 
					(GREEN) * ((bunkerLeft[row] >> ((BUNKER_WIDTH/2)-1-col)) & MASK_ONE);

			//background frame
			framePointerBackground[((BUNKER_Y_VALUE + row) * SCREEN_WIDTH) +
							(col + (bunkerId * SCREEN_WIDTH/4)) + BUNKER_OFFSET] =
								(GREEN) * ((bunkerLeft[row] >> ((BUNKER_WIDTH/2)-1-col)) & MASK_ONE);
		}
	}

	for(row = 0; row < BUNKER_HEIGHT; row++)
	{
		for(col = 0; col < (BUNKER_WIDTH/2); col++)
		{
			framePointer[((BUNKER_Y_VALUE + row) * SCREEN_WIDTH) + 
				(col + BUNKER_WIDTH/2) + (bunkerId * SCREEN_WIDTH/4) + BUNKER_OFFSET] = 
					(GREEN) * ((bunkerRight[row] >> ((BUNKER_WIDTH/2)-1-col)) & MASK_ONE);

			//background frame
			framePointerBackground[((BUNKER_Y_VALUE + row) * SCREEN_WIDTH) +
							(col + BUNKER_WIDTH/2) + (bunkerId * SCREEN_WIDTH/4) + BUNKER_OFFSET] =
								(GREEN) * ((bunkerRight[row] >> ((BUNKER_WIDTH/2)-1-col)) & MASK_ONE);
		}
	}
}

//draws damage at the location of the bunker
void bunkerHit(int bunkerId, int hitLocation)
{
	int row, col;
	point_t hitspot;
	point_t temp;
	temp.x = bunkerId;
	temp.y = hitLocation;
	//damages the appropriate location on the correct bunker
	incrementBunkerDamage(temp);
	hitspot.y = BUNKER_Y_VALUE;
	//sets the x position to be where the bunker starts
	switch(bunkerId)
	{
		case 0:
			hitspot.x = BUNKER_0_XPOSITION;
			break;
		case 1:
			hitspot.x = BUNKER_1_XPOSITION;
			break;
		case 2:
			hitspot.x = BUNKER_2_XPOSITION;
			break;
		case 3:
			hitspot.x = BUNKER_3_XPOSITION;
			break;
	}
	//offsets the damage x position to be in the correct spot in the x direction
	switch(hitLocation % 4)
	{
		case 0:
			break;
		case 1:
			hitspot.x += BUNKER_DAMAGE_WIDTH;
			break;
		case 2:
			hitspot.x += BUNKER_DAMAGE_WIDTH*2;
			break;
		case 3:
			hitspot.x += BUNKER_DAMAGE_WIDTH*3;
			break;

	}
	//offsets the y vaue to the correct height so that it draws at the correct position
	if(hitLocation > 7)
	{
		hitspot.y += BUNKER_DAMAGE_HEIGHT *2;
	}
	else if(hitLocation > 3)
	{
		hitspot.y += BUNKER_DAMAGE_HEIGHT;
	}
	//gets the magnitude of damage at the correct spot
	int damage = getBunkerDamage(temp);
	//draws the correct bitmap at the desired location
	for(row = 0; row < BUNKER_DAMAGE_HEIGHT; row++)
	{
		for(col = 0; col < BUNKER_DAMAGE_WIDTH; col++)
		{
			//pos is the correct pixel on the screen to be drawn
			int pos = (row + hitspot.y) * SCREEN_WIDTH + hitspot.x + col;
			int color;	//1 or 0 depending on the pixel in the bitmap
			switch (damage)	//assigns color to the correct bit in the bitmap
			{
				case 0:
					color = 0;
					break;
				case 1:
					if(hitLocation == 0)
						color = ((bunkerDamage0_0[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else if (hitLocation == 3)
						color = ((bunkerDamage0_3[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else if (hitLocation == 5)
						color = ((bunkerDamage0_5[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else if (hitLocation == 6)
						color = ((bunkerDamage0_6[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else
						color = ((bunkerDamage0[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					break;
				case 2:
					if(hitLocation == 0)
						color = ((bunkerDamage1_0[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else if (hitLocation == 3)
						color = ((bunkerDamage1_3[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else if (hitLocation == 5)
						color = ((bunkerDamage1_5[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else if (hitLocation == 6)
						color = ((bunkerDamage1_6[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else
						color = ((bunkerDamage1[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);

					break;
				case 3:
					if(hitLocation == 0)
						color = ((bunkerDamage2_0[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else if (hitLocation == 3)
						color = ((bunkerDamage2_3[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else if (hitLocation == 5)
						color = ((bunkerDamage2_5[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else if (hitLocation == 6)
						color = ((bunkerDamage2_6[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					else
						color = ((bunkerDamage2[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);

					break;
				case 4:
					color = ((bunkerDamage3[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
					break;
			}
			if(!color)
			{
				framePointer[pos] =	GREEN;
				framePointerBackground[pos] =	GREEN;
			}
			else
			{
				framePointer[pos] = BLACK;
				framePointerBackground[pos] = BLACK;
			}

			//background
			//framePointerBackground[pos] = (GREEN) * ((bunkerDamage0[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
		}
	}



}

//paints the green line at the bottom of the screen
void paintEarthLine()
{
	int row, col;
	for(row = 0; row < GREEN_EARTH_LINE_HEIGHT; row++)
	{
		for(col = 0; col < SCREEN_WIDTH; col++)
		{
			framePointer[(row + GREEN_EARTH_LINE_Y)*SCREEN_WIDTH + col] = GREEN;

			//background
			framePointerBackground[(row + GREEN_EARTH_LINE_Y)*SCREEN_WIDTH + col] = GREEN;
		}
	}
}

//Returns 1 if the alienID is alive or 0 if it is dead
int getAlienAlive(int alienID)
{
    return alienAlive[alienID];
}









