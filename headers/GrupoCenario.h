/*
 * GrupoCenario.h
 *
 *  Created on: May 29, 2013
 *      Author: Carol
 */

#ifndef GRUPOCENARIO_H_
#define GRUPOCENARIO_H_

#include "GrupoPersonagens.h"
// #include "GrupoViloes.h"
#include "Item.h"

class GrupoCenario : public GrupoPersonagens {
public:
	GrupoCenario(Sprite *spriteDoctor, Sprite *spriteRose, Sprite *spriteJackie);
	~GrupoCenario();

	vector<Item*> listaItens;
	int experiencia;
	int nextLevel;
};


#endif /* GRUPOCENARIO_H_ */
