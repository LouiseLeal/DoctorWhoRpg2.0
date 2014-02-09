/*
 * State.h
 *
 *  Created on: Jun 7, 2013
 *      Author: Carol
 */

#ifndef STATE_H_
#define STATE_H_

// #include "SDLBase.h" -- sprite
#include "Sprite.h"
#include "TextOpcoes.h"
#include "InputManager.h"
#include "TileMap.h"
#include "CaixaTexto.h"
#include "Audio.h"

class State{
public:
	virtual void load(int pilha) = 0;
	virtual int unload() = 0;
	virtual int update(int deltaFrame) = 0;
	virtual void render() = 0;
	virtual ~State(){}
};



#endif /* STATE_H_ */
