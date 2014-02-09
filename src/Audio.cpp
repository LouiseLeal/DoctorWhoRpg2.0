/*
 * Audio.cpp
 *
 *  Created on: Jun 7, 2013
 *      Author: Carol
 */

#include "../headers/Audio.h"

Audio::Audio(string fileName, int type){
	Audio::fileName = fileName;
	//music
	if(type == 0){
		music = Mix_LoadMUS(fileName.c_str());
		if(!music) {
		    printf("Mix_LoadMUS: %s\n", Mix_GetError());
		    //exit(1);
		}
		sound = NULL;
	}
	else{
		//printf("fileName no audio: %s\n",fileName.c_str());
		sound = Mix_LoadWAV(fileName.c_str());
		if(!sound) {
		    printf("Mix_LoadWAV: %s\n%s\n", fileName.c_str(),Mix_GetError());
		    //exit(1);
		}
		music = NULL;
	}
//implementar a abordagem onde verifica a extencao do arquivo
}

Audio::~Audio(){
	if(music != NULL)
		Mix_FreeMusic(music);
	else if(sound != NULL)
		Mix_FreeChunk(sound);
}

void Audio::play(int loops){

	if(music != NULL)
		Mix_PlayMusic(music, loops);

	else if(sound != NULL)
		channel = Mix_PlayChannel(-1,sound, loops);
}

void Audio::stop(){
	if(music != NULL){
		Mix_FadeOutMusic(50);
	}
	else if(sound != NULL)
		Mix_HaltChannel(channel);
}

