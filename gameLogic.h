/*
 * graphics.h
 *
 *  Created on: Sep 28, 2015
 *      Author: superman
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

void handleButton(int currentButtonState);
void bulletHitDetection();
int  alienHitDetection(point_t position);
point_t alienPosition(int alienNumber);
point_t bunkerHitDetection(point_t position);

#endif /* GRAPHICS_H_ */
