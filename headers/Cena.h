/*
 * Cena.h
 *
 *  Created on: Jul 22, 2013
 *      Author: Carol
 */

#ifndef CENA_H_
#define CENA_H_

#include "State.h"
// #include "SDLBase.h"
#include "Tempo.h"
#include "TextOpcoes.h"
#include "InputManager.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class Cena {
public:
	Cena(string filePath);

	vector<FRAME> vetFrames;

};


#endif /* CENA_H_ */
