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





void print(char *str);



//pos moves right, neg moves left, zero moves down
char movementdirection;

unsigned int * framePointer;
unsigned int * framePointerBackground;

int alienAlive[NUM_ALIEN_COL * NUM_ALIEN_ROW];
int alienBullet[MAX_ALIEN_BULLETS];
int currentalienbullets;
int shipdirection;

void graphics_init(unsigned int * framePointer0, unsigned int * framePointerbg)
{
	//start moving to the right
	movementdirection = 1;
	shipdirection = 1;
	framePointer = framePointer0;
	framePointerBackground = framePointerbg;
	paintWords();
	paintTankLives();
	paintAliens();
	paintTank();
	paintBunker(1);
	paintBunker(2);
	paintBunker(3);
	paintBunker(4);
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
			if(color)
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
				pos = (row + SHIP_Y) * SCREEN_WIDTH - col + getShipPos();
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
	setShipAlive(0);
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
	if(getShipPos() < 0 || getShipPos() + SHIP_WIDTH > SCREEN_WIDTH)
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


void paintScore()
{
	int row, col, pos, color;
	int score = getScore();
	int offset = SCORE_NUM_X;
	for(row = 0; row < ALPHA_NUM_HEIGHT; row++)
	{
		for(col = 0; col < ALPHA_NUM_WIDTH; col++)
		{

		}
	}
}

void paintTankLives()
{
	int life, row, col;
	int lifecount = getLives();
	for(life = 0; life < lifecount; life++)
	{
		for(row = 0; row < TANK_HEIGHT; row++)
		{
			for(col = 0; col < TANK_WIDTH; col++)
			{
				framePointer[(row + TANK_LIVES_Y)*SCREEN_WIDTH + col + TANK_LIVES_X + (life * (TANK_WIDTH + TANK_LIVES_SPACING))] = (GREEN) * ((tank[row] >> (TANK_WIDTH-1-col)) & MASK_ONE);
			}
		}
	}
}


//marches the aliens a distance of ALIEN_HORIZONTAL_DISTANCE or ALIEN_VERTICAL_DISTANCE
//depending on which direction the aliens are moving
void alienMarch()
{
	setMovement(!getMovement());
	//check outofbounds
	point_t newloc = getAlienLocation();
	if((newloc.x + (ALIEN_WIDTH * NUM_ALIEN_COL)) + ALIEN_HORIZONTAL_DISTANCE >= SCREEN_WIDTH
				&& movementdirection >= 0)
	{
		movementdirection--;
	}
	else if((newloc.x - ALIEN_HORIZONTAL_DISTANCE) <= 0)
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
	paintAliens(framePointer);
}

void paintAliens()
{
	int alien_col, row, inbetween, col, alien_row, aliencolor, pos;
	for(alien_row = 0; alien_row < NUM_ALIEN_ROW; alien_row++)
	{
		for (alien_col = 0; alien_col < NUM_ALIEN_COL; alien_col++)
		{
			for(row = 0; row < EXPLOSION_HEIGHT; row++)
			{
				for(col = 0; col < ALIEN_WIDTH; col++)
				{
					if(alienAlive[(alien_row * NUM_ALIEN_COL) + alien_col] && row < ALIEN_HEIGHT)
					{
						switch (alien_row)
						{
							case 0:
								pos = (row + getAlienLocation().y)*SCREEN_WIDTH + col + (alien_col * ALIEN_WIDTH) + getAlienLocation().x;
								if (getMovement())
								{
									aliencolor = ((alien_top_out[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
								}
								else
								{
									aliencolor = ((alien_top_in[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
								}
								break;
							case 1:
								pos = (row + getAlienLocation().y + ALIEN_HEIGHT + ROW_SPACING) *SCREEN_WIDTH +
										col + (alien_col * ALIEN_WIDTH) + getAlienLocation().x;
								if (getMovement())
								{
									aliencolor = ((alien_middle_out[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
								}
								else
								{
									aliencolor = ((alien_middle_in[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
								}
								break;
							case 2:
								pos = (row + getAlienLocation().y + (ALIEN_HEIGHT + ROW_SPACING)*alien_row) *SCREEN_WIDTH +
											col + (alien_col * ALIEN_WIDTH) + getAlienLocation().x;
								if (getMovement())
								{
									aliencolor = ((alien_middle_out[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
								}
								else
								{
									aliencolor = ((alien_middle_in[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
								}
								break;
							case 3:
								pos = (row + getAlienLocation().y + (ALIEN_HEIGHT + ROW_SPACING)*alien_row) *SCREEN_WIDTH
											+ col + (alien_col * ALIEN_WIDTH) + getAlienLocation().x;
								if (getMovement())
								{
									aliencolor = ((alien_bottom_out[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
								}
								else
								{
									aliencolor = ((alien_bottom_in[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
								}

								break;
							case 4:
								pos = (row + getAlienLocation().y + (ALIEN_HEIGHT + ROW_SPACING)*alien_row) *SCREEN_WIDTH +
											col + (alien_col * ALIEN_WIDTH) + getAlienLocation().x;
								if (getMovement())
								{
									aliencolor = ((alien_bottom_out[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
								}
								else
								{
									aliencolor = ((alien_bottom_in[row] >> (ALIEN_WIDTH-1-col)) & MASK_ONE);
								}
								break;
							default:
								break;
						}
						if (aliencolor)
						{
							if(framePointer[pos] != WHITE)
								framePointer[pos] = WHITE;
						}
						else
						{
							if(framePointer[pos] != framePointerBackground[pos])
								framePointer[pos] = framePointerBackground[pos];
						}
					}
					else
					{
						pos = (row + getAlienLocation().y + (ALIEN_HEIGHT + ROW_SPACING)*alien_row) *SCREEN_WIDTH +
								col + (alien_col * ALIEN_WIDTH) + getAlienLocation().x;
						framePointer[pos] = framePointerBackground[pos];
					}
				}
			}
		}
	}
	//erase aliens
	if(movementdirection != 0)
	{
		for(row = 0; row < (ALIEN_HEIGHT * NUM_ALIEN_ROW + ROW_SPACING * 4); row++)
		{
			for(col = 0; col < ALIEN_HORIZONTAL_DISTANCE; col++)
			{
				if(movementdirection > 0)
				{
					pos = (getAlienLocation().y+row)*SCREEN_WIDTH +
							(getAlienLocation().x-col-1);
					framePointer[pos] = framePointerBackground[pos]; //black out part left behind
				}
				else
				{
					pos = (getAlienLocation().y+row)*SCREEN_WIDTH +
							(getAlienLocation().x + col + 1+  (ALIEN_WIDTH * NUM_ALIEN_COL));
					framePointer[pos]  = framePointerBackground[pos]; //black out part left behind
				}
			}
		}
	}
	else
	{
		for(inbetween = 0; inbetween < NUM_ALIEN_ROW; inbetween++)
		{
			for(row = 1; row <= ALIEN_VERTICAL_DISTANCE; row++)
			{
				for(col = 0; col < (ALIEN_WIDTH * NUM_ALIEN_COL); col++)
				{
					if(inbetween && row <= ROW_SPACING)
					{
						pos = ((getAlienLocation().y - row) + (inbetween * ALIEN_HEIGHT) + (ROW_SPACING * inbetween))*SCREEN_WIDTH +
								(getAlienLocation().x) + col;
						framePointer[pos] = framePointerBackground[pos]; //black out part left behind
					}
					else if(!inbetween)
					{
						pos = ((getAlienLocation().y - row) + (inbetween * ALIEN_HEIGHT))*SCREEN_WIDTH +
								(getAlienLocation().x) + col;
						framePointer[pos] = framePointerBackground[pos]; //black out part left behind
					}
				}
			}
		}
	}
}

void killAlien(int alienId)
{
	if(alienId >= 0 && alienId < NUM_ALIEN_COL * NUM_ALIEN_ROW)
	{
		alienAlive[alienId] = 0;

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
	int row, col, pos, color;
	int aliennum = rand() % NUM_ALIEN_COL;
	//int bullettype = rand() % NUM_ALIEN_BULLET_TYPES; //to be implemented to fire different bullets
	int bullettype = 0;
	point_t bulletpos;
	int currentbullet;
	bulletpos.y = getAlienLocation().y + (ALIEN_HEIGHT * NUM_ALIEN_ROW + ROW_SPACING * (NUM_ALIEN_ROW-1));
	bulletpos.x = getAlienLocation().x + (aliennum * ALIEN_WIDTH) - (ALIEN_BULLET_WIDTH/2) + (ALIEN_WIDTH/2) - ALIEN_BULLET_OFFSET;
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
			if(!bullettype) //paints the correct bullet
			{
				alienBullet[currentbullet] = 1;
				pos = (row + bulletpos.y)*SCREEN_WIDTH + col + bulletpos.x;
				color = ((alien_bullet1_1[row] >> (ALIEN_BULLET_WIDTH-1-col)) & MASK_ONE);

			}
			else
			{
				alienBullet[currentalienbullets] = 5;
				pos = (row + bulletpos.y)*SCREEN_WIDTH + col + bulletpos.x;
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
	int row, col, pos, color;
	point_t bulletpos = getTankBulletPosition();
	if(bulletpos.y - TANK_BULLET_SPEED < EFFECTIVE_SCREEN_TOP)
	{
		removeTankBullet();
	}
	if(getNumTankBullet() > 0)
	{
		bulletpos.y -= TANK_BULLET_SPEED;
		setTankBulletPosition(bulletpos);
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
			if(alienbulletpos.y > GREEN_EARTH_LINE_Y - ALIEN_BULLET_HEIGHT)
			{
				currentalienbullets--;
				alienBullet[alienbullet] = 0;
				eraseAlienBullet(alienbulletpos);
			}
		}
	}
}

//Draws a bunker in the position indicated by bunkerID ie 1, 2, 3, 4
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

	//paintBunker(bunkerId);
	int row, col;
	for(row = 0; row < BUNKER_DAMAGE_HEIGHT; row++)
	{
		for(col = 0; col < BUNKER_DAMAGE_WIDTH; col++)
		{
			framePointer[((BUNKER_Y_VALUE + row) * SCREEN_WIDTH) + 
				(col + hitLocation) + (bunkerId * SCREEN_WIDTH/4) + BUNKER_OFFSET] = 
					(GREEN) * ((bunkerDamage0[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);

			//background
			framePointerBackground[((BUNKER_Y_VALUE + row) * SCREEN_WIDTH) +
							(col + hitLocation) + (bunkerId * SCREEN_WIDTH/4) + BUNKER_OFFSET] =
								(GREEN) * ((bunkerDamage0[row] >> ((BUNKER_DAMAGE_WIDTH)-1-col)) & MASK_ONE);
		}
	}



}


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















