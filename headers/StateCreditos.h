/*
 * StateCreditos.h
 *
 *  Created on: Jul 26, 2013
 *      Author: Carol
 */

#ifndef STATECREDITOS_H_
#define STATECREDITOS_H_

// #include "GrupoCenario.h"
// #include "TileMap.h"
// #include "TileSet.h"
// #include "Types.h"
// #include "TextOpcoes.h"
// #include "InputManager.h"
// #include "Audio.h"

#include "State.h"
#include "Tempo.h"

class StateCreditos : public State {
public:
	void load(int pilha);
	int unload();
	int update(int deltaFrame);
	void render();
	void processEvents();
	void begin();

	Tempo timer;

	int time;
	int frameSkip;
	int frameTime;

	Sprite *background;
	Audio *sfxBackground;
	int returnUpdate;
};



#endif /* STATECREDITOS_H_ */
