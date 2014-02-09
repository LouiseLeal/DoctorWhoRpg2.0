/*
 * PersonagemAtivo.h
 *
 *  Created on: 01/06/2013
 *      Author: Louise
 */

#ifndef PERSONAGEMATIVO_H_
#define PERSONAGEMATIVO_H_

//#include "Habilidade.h" - pelo personagem
//#include "Audio.h" - pelo animation
//#include "Camera.h" - pelo personagem
//#include <iostream> - sdlbase
//#include "Ataque.h"
//#include "Tempo.h" - vem pelo personagem
//#include <string> - sdlbase

#include "Personagem.h"
#include "InputManager.h"
#include "map"
#include <fstream>


using namespace std;

class PersonagemAtivo: public Personagem{
public:
	PersonagemAtivo(string filePath, string nome, Sprite *spritRef);
	string getName();
	Habilidade getHability();
	int getType();

	void render();
	int update(int dt);
	void loadXml(string filePath);
	void processEvent();
	void setCurrentAnimation(string nomeAnimacao);
	void loadDadosAnimacoes(string filePath);
	bool collidesWith(SDL_Rect *rect);


	//vector<Animation*> listAnimacoes;
	//vector<Ataque*> listAttack;
	map<string,Animation*> listAnimacoes;
	map<string,Ataque*> listAttack;
	//vector<vector<int> > vetDadosAnimacoes;

	Habilidade habilidade;
	int type;
	int life;
	int mana;
	int spriteIndex;
	AID_TYPES tipo;

	bool parado;
	Tempo timerAnimacao;
	int fimAnimacao;
	string animacaoEscolhida;
	Animation *currentAnimation;
	Audio *sfxAtaque;

	int spriteW;
	int spriteH;
	int imageW;
	int imageH;

};


#endif /* PERSONAGEMATIVO_H_ */
