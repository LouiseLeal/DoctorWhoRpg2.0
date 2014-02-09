/*
 * StateGameOver.h
 *
 *  Created on: Jul 17, 2013
 *      Author: Carol
 */

#ifndef STATEGAMEOVER_H_
#define STATEGAMEOVER_H_

// #include "TileSet.h"
// #include "Tempo.h"
// #include "Types.h"
// #include "InputManager.h" -- vem do personagem - trocar pro state
// #include "TileMap.h"
// #include "TextOpcoes.h"

#include "State.h"
#include "GrupoCenario.h"

class StateGameOver : public State {
public:
	void load(int pilha);
	int unload();
	int update(int deltaFrame);
	void render();
	void processEvents();
	void begin();

	Tempo timer;

	Sprite *background;
	TextOpcoes *opcoes;
	Text *txtGameOver;
	int returnUpdate;
	Audio *sfxBackground;
};


#endif /* STATEGAMEOVER_H_ */
