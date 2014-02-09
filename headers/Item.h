/*
 * Item.h
 *
 *  Created on: May 29, 2013
 *      Author: Carol
 */

#ifndef ITEM_H_
#define ITEM_H_

// #include "SDLBase.h"
// #include "Types.h"
#include "Sprite.h"

class Item {
public:
	Item(string nome, string descricao, int hpEffect, int xpEffect, int attackEffect, int inteligenceEffect, int defenseEffect);
	~Item();

	int hpEffect;
	int xpEffect;
	int attackEffect;
	int inteligenceEffect;
	int defenseEffect;
	// true hp false xp
	string nome;
	Sprite *sprite;
	string descricao;

};


#endif /* ITEM_H_ */
