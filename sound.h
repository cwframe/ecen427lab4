/*
 * sound.h
 *
 *  Created on: Oct 26, 2015
 *      Author: superman
 */

#ifndef SOUND_H_
#define SOUND_H_


/*extern alienSound1_soundData;
extern alienSound1_numberOfSamples;
extern alienSound1_sampleRate;*/

void init_Sound();

void playSound();

void setSound(unsigned int* soundtoplay, int numFrames, int prioirty);

unsigned int* explosion_getSound();
int explosion_getSoundRate();
int explosion_getNumFrames();

unsigned int* shoot_getSound();
int shoot_getSoundRate();
int shoot_getNumFrames();

unsigned int* invaderkilled_getSound();
int invaderkilled_getSoundRate();
int invaderkilled_getNumFrames();

unsigned int* ufohighpitch_getSound();
int ufohighpitch_getSoundRate();
int ufohighpitch_getNumFrames();

unsigned int* ufolowpitch_getSound();
int ufolowpitch_getSoundRate();
int ufolowpitch_getNumFrames();

unsigned int* march1_getSound();
int march1_getSoundRate();
int march1_getNumFrames();



#endif /* SOUND_H_ */
