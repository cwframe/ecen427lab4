/*
 * graphics.h
 *
 *  Created on: Sep 28, 2015
 *      Author: superman
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_


void handleButton(int currentButtonState);
void handleController(int currentControllerState);
void bulletHitDetection();
int  alienHitDetection(point_t position);
point_t alienPosition(int alienNumber);
point_t bunkerHitDetection(point_t position);
int tankHitDetection(point_t bulletPosition);
int motherShipHitDetection(point_t bulletPosition);


#endif /* GAMELOGIC_H_ */
