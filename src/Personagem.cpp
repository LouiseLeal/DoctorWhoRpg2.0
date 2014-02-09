/*
 * Personagem.cpp
 *
 *  Created on: Jun 17, 2013
 *      Author: Carol
 */

#include "../headers/Personagem.h"

Personagem::Personagem(string nome, Sprite *spriteRef) : GameObject(0,0,0,0){
	Personagem::nome = nome;

	spriteW = 0;
	spriteH = 0;
	imageW = 0;
	imageH = 0;

	sprite = spriteRef;
	sprite->clip(0,0,64,64);
}
