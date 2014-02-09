/*
 * StateDummie.h
 *
 *  Created on: Jul 19, 2013
 *      Author: Carol
 */

#ifndef STATEDUMMIE_H_
#define STATEDUMMIE_H_

#include "State.h"
#include "GrupoCenario.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Tempo.h"
#include "Types.h"
#include "TextOpcoes.h"
#include "InputManager.h"
#include "Audio.h"

// #define FRAME_TIME 100

class StateDummie : public State {
public:
	void load(int pilha);
	int unload();
	int update(int deltaFrame);
	void render();
	void processEvents();

	Tempo timer;

	Sprite *background;
	Sprite *animacaoTardis;
	int returnUpdate;
	int rotacao;
	int contaRotacao;

	int time;
	int frameSkip;
	int frameTime;

	int tardisX;
	int tardisY;
	int tardisWidth;
	int tardisHeight;

	int currentFrame;
	int maxFrame;

	int currentFrameVortex;
	int maxFrameVortex;

	Audio *sfxBackground;
};


#endif /* STATEDUMMIE_H_ */
