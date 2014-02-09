/*
 * GrupoViloes.h
 *
 *  Created on: May 29, 2013
 *      Author: Carol
 */

#ifndef GRUPOVILOES_H_
#define GRUPOVILOES_H_

#include "GrupoPersonagens.h"
// #include "Personagem.h"
// #include "PersonagemAtivo.h"
// #include "Level.h"

using namespace tinyxml2;

class GrupoViloes : public GrupoPersonagens {
public:
	GrupoViloes(Level *vLevelMocinhos);
	Ataque *selecionaAtaque();
	~GrupoViloes();

	void calculaProbabilidades();
	Level *calculaLevel(Level *level);

	vector<PersonagemAtivo*> listVilans;


//-------------------------------  IA ------------------
	int nivelDificuldade;

	//probabilidades de escolher multiplicador
	int limiteAtaque;// = 33;
	int limiteInteligencia;// = 67;
	int limiteDefesa;// = 100;

	//probabilidade de ele escolher ataque de defesa aumenta quando chegar a 20% de vida
	//probabilidade de escolha de ataque e distribuida de acordo com multiplicadores

	int levelTotal;
	int pAtaque;// = (mulAtaque * 100) / levelTotal;
	int pInteligencia;// = (mulInteligencia * 100) / levelTotal;
	int pDefesa;// = (mulDefesa * 100) / levelTotal;

	int limitePAtaque;// = pAtaque;
	int limitePInteligencia;// = limiteMulAtaque + pInteligencia;
	int limitePDefesa;// = limiteMulInteligencia + pDefesa;
	//int diferenca = 100 - limiteMulDefesa;


private:
	//funcoes
	void geraViloes();

	//variaveis
	Level *levelMocinhos;


};


#endif /* GRUPOVILOES_H_ */
