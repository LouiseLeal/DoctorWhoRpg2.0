/*
 * GrupoPersonagens.cpp
 *
 *  Created on: May 29, 2013
 *      Author: Carol
 */

#include "../headers/GrupoPersonagens.h"

void GrupoPersonagens::addPersonagem(PersonagemAtivo *personagem) {
	vetorPersonages.insert(vetorPersonages.end(),1,personagem);
}

void GrupoPersonagens::removePersonagem(PersonagemAtivo *personagem){
	vector<PersonagemAtivo*>::iterator iterator;
	for(iterator = vetorPersonages.begin(); iterator <= vetorPersonages.end(); iterator++){
		if((*iterator) == personagem) {
			vetorPersonages.erase(iterator);
			break;
		}
	}
}

GrupoPersonagens::GrupoPersonagens(Level *levelInicial){
	experiencia = 0;
	level = levelInicial;
}

GrupoPersonagens::~GrupoPersonagens(){
	vetorPersonages.~vector();
}


Level *GrupoPersonagens::getLevel() {
	if(level == NULL){
		printf("Level grupo personagem é nulo.\n");
		exit(1);
	}

	return level;
}
