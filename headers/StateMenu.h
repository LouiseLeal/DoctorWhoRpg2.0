/*
 * StateMenu.h
 *
 *  Created on: Jul 19, 2013
 *      Author: Carol
 */

#ifndef STATEMENU_H_
#define STATEMENU_H_

// #include "Types.h"
// #include "SDLBase.h"
// #include "Sprite.h"
// #include "CaixaTexto.h"
// #include "InputManager.h"
// #include "TextOpcoes.h"
// #include "Audio.h"

#include "State.h"

class StateMenu : public State {
public:
	void load(int pilha);
	int unload();
	int update(int deltaFrame);
	void render();
	void begin();

	void loadStrings();

	void processEvents();

	TextOpcoes *opcoesMenus;
	Text *txtTitulo;
	Text *txtSubTitulo;
	Audio *sfxMenu;
	Sprite *background;
	Audio *sfxBlip;
	Sprite *spriteIntrucoes;

	vector<string> vetStr;

	bool printInstrucoes;

	int returnUpdate;
};


#endif /* STATEMENU_H_ */
