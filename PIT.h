/*
 * PIT.h
 *
 *  Created on: Nov 5, 2015
 *      Author: superman
 */

#ifndef PIT_H_
#define PIT_H_


void PIT_enable_counter();
void PIT_disable_counter();

void PIT_enable_interrupts();
void PIT_disable_interrupts();

void PIT_enable_reload();
void PIT_disable_reload();

void PIT_set_counter(int count);


#endif /* PIT_H_ */
