/*
 * GrupoBatalha.cpp
 *
 *  Created on: May 30, 2013
 *      Author: Carol
 */


#include "../headers/GrupoBatalha.h"

GrupoBatalha::GrupoBatalha(Level *vLevel, vector<PersonagemAtivo*> listaPersonagens){
	level = vLevel;
	attackValue = 0;
	inteligenceValue = 0;
	defenceValue = 0;

	lifeValue = 0;
	manaValue = 0;

	personagemAtaque = listaPersonagens[0];
	personagemInteligencia = listaPersonagens[1];
	personagemDefesa = listaPersonagens[2];

	personagens = listaPersonagens;
}

vector<PersonagemAtivo*> GrupoBatalha::getPersonagensBatalha(){
	vector<PersonagemAtivo*> vectorAux;
	vectorAux.push_back(personagemAtaque);
	vectorAux.push_back(personagemInteligencia);
	vectorAux.push_back(personagemDefesa);

	return vectorAux;
}

void GrupoBatalha::calculaValores(){
	if(personagemAtaque != NULL){
		attackValue += personagemAtaque->getHability().ataque;
		inteligenceValue += personagemAtaque->getHability().inteligencia;
		defenceValue += personagemAtaque->getHability().defesa;
		lifeValue += personagemAtaque->life;
	}

	if(personagemInteligencia != NULL){
		attackValue += personagemInteligencia->getHability().ataque;
		inteligenceValue += personagemInteligencia->getHability().inteligencia;
		defenceValue += personagemInteligencia->getHability().defesa;
		lifeValue += personagemInteligencia->life;
	}

	if(personagemDefesa != NULL){
		attackValue += personagemDefesa->getHability().ataque;
		inteligenceValue += personagemDefesa->getHability().inteligencia;
		defenceValue += personagemDefesa->getHability().defesa;
		lifeValue += personagemDefesa->life;
	}

	attackValue *= level->getAttackLevel();
	inteligenceValue *= level->getIntelligenceLevel();
	defenceValue *= level->getDefenseLevel();
	lifeValue *= level->getAttackLevel() + level->getIntelligenceLevel() + level->getDefenseLevel();

	manaValue = attackValue + inteligenceValue;
}

GrupoBatalha::~GrupoBatalha(){
	// personagemAtaque->~Personagem();
	// personagemInteligencia->~Personagem();
	// personagemDefesa->~Personagem();
}

