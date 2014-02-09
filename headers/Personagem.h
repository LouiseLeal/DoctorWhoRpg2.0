/*
 * Personagem.h
 *
 *  Created on: May 29, 2013
 *      Author: Carol
 */

#ifndef PERSONAGEM_H_
#define PERSONAGEM_H_

// #include "SDLBase.h"
// #include "Types.h"
// #include <iostream>
// #include "BoundingBox.h"

#include "GameObject.h"
#include "Ataque.h"
#include "Animation.h"
#include "tinyxml2.h"
#include "Habilidade.h"


using namespace std;
using namespace tinyxml2;

class Personagem : public GameObject{
public:
	Personagem(string nome, Sprite *spriteRef);
	virtual void render()=0;
	virtual int update(int dt)=0;
	virtual void loadXml(string filePath)=0;
	virtual bool collidesWith(SDL_Rect *rect) = 0;

	//rect que circunda o personagem
	BoundingBox boundingBox;
	//referencia ao sprite
	Sprite* sprite;

	//dados do sprite
	int spriteW;
	int spriteH;
	int imageW;
	int imageH;

	//nome do personagem
	string nome;
};


#endif /* PERSONAGEM_H_ */
