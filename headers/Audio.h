/*
 * Audio.h
 *
 *  Created on: Jun 7, 2013
 *      Author: Carol
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include "SDLBase.h"

#define MUSIC_TYPE 0
#define SOUND_TYPE 1

class Audio {
public:
	Audio(string fileName, int type);
	~Audio();
	void play(int loops);
	void stop();

	string fileName;

private:
	Mix_Chunk *sound;
	Mix_Music *music;
	int channel;

};


#endif /* AUDIO_H_ */
