/*
 * Types.h
 *
 *  Created on: May 29, 2013
 *      Author: Carol
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using namespace tinyxml2; 

enum AID_TYPES {
	ATAQUE = 0,
	INTELIGENCIA = 1,
	DEFESA = 2
};

enum ATACANTE {
	MOCINHOS,
	VILOES
};

enum TIPO_ITEM{
	HP_TYPE,
	XP_TYPE
};

//estados do jogo
enum{
		ESTADO_INTRODUCAO,
		ESTADO_MENU,
		ESTADO_CENARIO,
		ESTADO_CASAROSE,
		ESTADO_SELECAO,
		ESTADO_BATALHA,
		ESTADO_FIM,
		ESTADO_GAME_OVER,
		ESTADO_DUMMIE,
		ESTADO_STATUS,
		ESTADO_CREDITOS
	};

//estados do state batalha
enum{
	ESTADOTIPOACAO,
	ESTADOTIPOATAQUE,
	ESTADORUN,
	ESTADOTIPOITEM,
	ESTADOATAQUESELECIONADO,
	ESTADORENDER,
	ESTADOITEMSELECIONADO,
	ESTADOGAMEOVER,
	ESTADOVITORIA,
	ESTADOLEVADANO

};

//estrutura que guarda os dados de um frame da animacao
typedef struct DADOS_ANIMACAO {
	int largura;
	int altura;
	vector<int> vetCropX;
	vector<int> vetCropY;
	vector<int> vetPosX;
	vector<int> vetPosY;
}DADOS_ANIMACAO;

//estrutura que guarda os dados de um personagem de um frame de animacao
typedef struct PERSONAGEM {
	int posX;
	int posY;
	string direcao;
	int fala;
	string conteudo;
	string expressao;
	int passos;
}PERSONAGEM;

//estrutura que guarda os dados de um frame
typedef struct FRAME {
	vector<PERSONAGEM> vetPersonagem;
	PERSONAGEM fantasma;//precisamo ARRUMAR isso
	int frame;
	int tempo;
}FRAME;

#endif /* TYPES_H_ */
