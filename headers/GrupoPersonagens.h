/*
 * GrupoPersonagens.h
 *
 *  Created on: May 29, 2013
 *      Author: Carol
 */

#ifndef GRUPOPERSONAGENS_H_
#define GRUPOPERSONAGENS_H_

//#include "Personagem.h" -- vem do personagem ativo
// #include "Level.h" -- grupobatalha
// #include "PersonagemAtivo.h" -- grupobatalha
#include "GrupoBatalha.h"

using std::vector;

class GrupoPersonagens {
public:
	//funcoes
	GrupoPersonagens(Level *levelInicial);
	~GrupoPersonagens();
	void setLevel(Level *vLevel) {level = vLevel;};
	Level *getLevel();
	void addPersonagem(PersonagemAtivo *personagem);
	void removePersonagem(PersonagemAtivo *personagem);
	vector<PersonagemAtivo*> vetorPersonages;
	vector<PersonagemAtivo*> vectorPersonagensBatalha;

	//variaveis
	Level *level;
	int experiencia;
	int levelDisponivel;

};


#endif /* GRUPOPERSONAGENS_H_ */
