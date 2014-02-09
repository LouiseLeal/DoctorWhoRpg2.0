/*
 * EstruturaStatus.h
 *
 *  Created on: Jul 21, 2013
 *      Author: Carol
 */

#ifndef ESTRUTURASTATUS_H_
#define ESTRUTURASTATUS_H_

// #include "State.h"
// #include "GrupoCenario.h"
// #include "TileMap.h"
// #include "TileSet.h"
// #include "Tempo.h"
// #include "Types.h"
// #include "TextOpcoes.h"
// #include "InputManager.h"

#include "Sprite.h"
#include "Text.h"
 #include "PersonagemAtivo.h"

class EstruturaStatus {
public:
	EstruturaStatus(PersonagemAtivo *pesonagem, int posX, int posY);
	Sprite *sprite;
	Text *nome;
	Text *tipo;
	Text *ataque;
	Text *inteligencia;
	Text *defesa;

	void render();

	int posX;
	int posY;

};


#endif /* ESTRUTURASTATUS_H_ */
