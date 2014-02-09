/*
 * Timer.h
 *
 *  Created on: Jun 7, 2013
 *      Author: Carol
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "SDLBase.h"

class Tempo{
public:
	void start();
	void pause();
	void resume();
	int getTime();

private:
	int initialTime;
	int pauseTime;
	bool paused;

};


#endif /* TIMER_H_ */
