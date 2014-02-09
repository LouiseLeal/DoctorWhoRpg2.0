/*
 * EstruturaItem.h
 *
 *  Created on: Jul 22, 2013
 *      Author: Carol
 */

#ifndef ESTRUTURAITEM_H_
#define ESTRUTURAITEM_H_

// #include "SDLBase.h"
// #include "State.h"
// #include "GrupoCenario.h"
// #include "TileMap.h"
// #include "TileSet.h"
// #include "Tempo.h"
// #include "TextOpcoes.h"
// #include "InputManager.h"

#include "Sprite.h"
#include "Text.h"
 #include "Item.h"

class EstruturaItem {
public:
	EstruturaItem(Item *item, int posX, int posY);
	Sprite *sprite;
	Text *nome;
	Text *descricao;
	vector<Text*> vetEfeito;

	void render();

	int posX;
	int posY;

	vector<string> vetStrings;
	vector<Text*> vetText;

};
#endif /* ESTRUTURAITEM_H_ */
