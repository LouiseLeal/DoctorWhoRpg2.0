/*
 * Ataque.h
 *
 *  Created on: 01/06/2013
 *      Author: Louise
 */

#ifndef ATAQUE_H_
#define ATAQUE_H_

#include "Sprite.h"
//#include "SDLBase.h" -- sprite ja inclui

using namespace std;
class Ataque{
public:
	string nome;
	AID_TYPES tipoAtaque;

	//"Musica";

	Ataque(string nome, AID_TYPES tipoAtaque);
};

#endif /* ATAQUE_H_ */
