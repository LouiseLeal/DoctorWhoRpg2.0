/*
 * Timer.cpp
 *
 *  Created on: Jun 7, 2013
 *      Author: Carol
 */

#include "../headers/Tempo.h"

void Tempo::start(){
	initialTime = SDL_GetTicks();
	paused = false;
}

void Tempo::pause(){
	pauseTime = SDL_GetTicks();
	paused = true;
}

void Tempo::resume(){
	int stopedTime = SDL_GetTicks() - pauseTime;
	initialTime += stopedTime;
	paused = false;
}


int Tempo::getTime(){
	if(paused)
		return (pauseTime - initialTime);
	else
		return (SDL_GetTicks() - initialTime);
}

