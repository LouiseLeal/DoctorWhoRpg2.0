/*
 * StateIntro.h
 *
 *  Created on: Jun 30, 2013
 *      Author: Carol
 */

#ifndef STATEINTRO_H_
#define STATEINTRO_H_

// #include "SDLBase.h" - sprite
// #include "Sprite.h" -- state
// #include "Types.h" -- sdlbase
// #include "CaixaTexto.h"
// #include "InputManager.h"
// #include "Audio.h"

#include "State.h"

class StateIntro : public State {
public:
	void load(int pilha);
	int unload();
	int update(int deltaFrame);
	void render();
	void begin();

	int returnUpdate;

	void processEvents();

	CaixaTexto *caixaMonologo;
	Sprite *background;
	Sprite *sprite1;
	Sprite *sprite2;
	Sprite *sprite3;
	Audio *sfxBackground;
};



#endif /* STATEINTRO_H_ */
