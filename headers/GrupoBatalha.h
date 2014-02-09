/*
 * GrupoBatalha.h
 *
 *  Created on: May 29, 2013
 *      Author: Carol
 */

#ifndef GRUPOBATALHA_H_
#define GRUPOBATALHA_H_

// #include "SDLBase.h"
#include "PersonagemAtivo.h"
#include "Level.h"

class GrupoBatalha {
public:
	GrupoBatalha(Level *level, vector<PersonagemAtivo*> listaPersonagens);
	~GrupoBatalha();
	void setPersonagemAtaque(PersonagemAtivo *personagem) {personagemAtaque = personagem;};
	void setPersonagemInteligencia(PersonagemAtivo *personagem) {personagemInteligencia = personagem;};
	void setPersonagemDefesa(PersonagemAtivo *personagem) {personagemDefesa = personagem;};
	void calculaValores();
	vector<PersonagemAtivo*> getPersonagensBatalha();

	int getMulAtaque() {return level->getAttackLevel();};
	int getMulInteligencia() { return level->getIntelligenceLevel();};
	int getMulDefesa() {return level->getDefenseLevel();};

	//variaveis
	PersonagemAtivo *personagemAtaque;
	PersonagemAtivo *personagemInteligencia;
	PersonagemAtivo *personagemDefesa;

	int attackValue;
	int inteligenceValue;
	int defenceValue;
	int lifeValue;
	int manaValue;
	Level *level;

	vector<PersonagemAtivo*> personagens;

};


#endif /* GRUPOBATALHA_H_ */
