/*
 * Animation.h
 *
 *  Created on: Jun 1, 2013
 *      Author: Carol
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

// #define FRAME_TIME 100

//#include "SDLBase.h" -- sprite jah inclui
#include "Sprite.h"
#include "Tempo.h"
#include "Audio.h"

class Animation{
public:
	Animation(Sprite *sprite, int indexSprite, int nSprites, int loop, string nome, DADOS_ANIMACAO dadosAnimacao, Audio *sfx = NULL);
	void update(int deltaFrame);//, int spriteW, int spriteH, int imageCollumns, int imageLines);
	void render(int x, int y);
	void reset();
	void start();
	bool animationRunning();

	int linhaSprite;
	int currentFrame;
	int ultimoFrame;
	int nSprites;
	int time;
	int frameSkip;
	int frameTime;
	int clipX;
	int clipY;
	Sprite *refSprite;
	string name;
	int loop;
	bool running;
	DADOS_ANIMACAO dadosAnimacao;
	Tempo timer;
	Audio *sfxAnimation;
};



#endif /* ANIMATION_H_ */
