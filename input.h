/*
 * input.h
 *
 *  Created on: Sep 30, 2015
 *      Author: superman
 */

#ifndef INPUT_H_
#define INPUT_H_

void handleButton();
void input(char c);
void interrupt_handler_dispatcher(void* ptr);
void timer_interrupt_handler();
void pauseGame();
void resumeGame();


#endif /* INPUT_H_ */
