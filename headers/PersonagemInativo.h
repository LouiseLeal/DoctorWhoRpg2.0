/*
 * PersonagemInativo.h
 *
 *  Created on: Jun 17, 2013
 *      Author: Carol
 */

#ifndef PERSONAGEMINATIVO_H_
#define PERSONAGEMINATIVO_H_

//#include "Tempo.h" - personagem
//#include "Camera.h"
//#include "map" - personagem
//#include <iostream>
//#include <fstream>
//#include <string>
//#include "Audio.h" - animation - personagem

#include "Personagem.h"
#include "InputManager.h"

class PersonagemInativo : public Personagem {
public:
	PersonagemInativo(string filePath, string nome, Sprite *spriteRef);
	void render();
	int update(int dt);
	bool collidesWith(SDL_Rect *rect);

	void loadXml(string filePath);

	map<string,Animation*> listAnimacoes;
	int spriteIndex;
	Animation *currentAnimation;

	string fala;
};


#endif /* PERSONAGEMINATIVO_H_ */
