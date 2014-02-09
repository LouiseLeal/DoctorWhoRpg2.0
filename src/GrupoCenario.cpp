/*
 * GrupoCenario.cpp
 *
 *  Created on: May 30, 2013
 *      Author: Carol
 */

#include "../headers/GrupoCenario.h"

GrupoCenario::GrupoCenario(Sprite *spriteDoctor,Sprite *spriteRose,Sprite *spriteJackie) : GrupoPersonagens( new Level(1,1,1)){
	//inicializado com o Doctor e a Rose e a Mae da rose
	PersonagemAtivo *Doctor = new PersonagemAtivo("../resources/Doctor.xml","Doctor",spriteDoctor);
	PersonagemAtivo *Rose = new PersonagemAtivo("../resources/Rose.xml","Rose",spriteRose);
	PersonagemAtivo *Jackie = new PersonagemAtivo("../resources/Jackie.xml","Jackie",spriteJackie);

	addPersonagem(Doctor);
	addPersonagem(Rose);
	addPersonagem(Jackie);

	level = new Level(1,1,1);
	levelDisponivel = 0;

	//grupoBatalha = new GrupoBatalha(level, vetorPersonages);
	//grupoBatalha->calculaValores();

	experiencia = 0;
	nextLevel = 2*exp(level->getTotalLevel()*0.7) + 50;//+ 200;

	//Item *itemAux = new Item("banana","bananas are cool",10,0,0,0,0);
	//listaItens.push_back(itemAux);

	listaItens.clear();
}

GrupoCenario::~GrupoCenario(){
	//listaItens.~vector();
	//this->~GrupoPersonagens();
}

