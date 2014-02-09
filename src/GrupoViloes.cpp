/*
 * GrupoViloes.cpp
 *
 *  Created on: May 29, 2013
 *      Author: Carol
 */


#include "../headers/GrupoViloes.h"

GrupoViloes::GrupoViloes(Level *vLevelMocinhos) : GrupoPersonagens(vLevelMocinhos){

	limiteAtaque = 42;
	limiteInteligencia = 85;
	limiteDefesa = 100;

	levelMocinhos = vLevelMocinhos;
	level = calculaLevel(levelMocinhos);
	calculaProbabilidades();
	geraViloes();
}

void GrupoViloes::geraViloes() {
	//carrega viloes baseado no level
	//load no vilao a partir do level do mocinho
	for(int i = 0; i < 3 ; i++) {
		char fileName[50];
		sprintf(fileName, "../resources/fantasma%d.xml",i);
		//repassar sprite geral
		Sprite *sprite = new Sprite("../images/ghosts.png");
		char nomeVilao[50];
		sprintf(nomeVilao, "fantasma%d",i);
		PersonagemAtivo *vilao = new PersonagemAtivo(fileName,nomeVilao, sprite);
		listVilans.push_back(vilao);
	}
}

Ataque *GrupoViloes::selecionaAtaque() {
	vector<PersonagemAtivo*>::iterator iteratorPersonagem;

	int pEscolha = rand() % 100;
	printf("pescolha: %d\n",pEscolha);

	AID_TYPES tipoEscolhido;
	if(pEscolha <= limitePAtaque){
		tipoEscolhido = ATAQUE;
	}
	else if(pEscolha <= limitePInteligencia  && pEscolha > limitePAtaque){
		tipoEscolhido = INTELIGENCIA;
	}
	else if(pEscolha <= 100 && pEscolha > limitePInteligencia){
		tipoEscolhido = DEFESA;
	}

	map<string,Ataque*>::iterator iteratorAtaque;
	Ataque *ataqueEscolhido;
	for(iteratorPersonagem = listVilans.begin(); iteratorPersonagem < listVilans.end(); iteratorPersonagem++){
			PersonagemAtivo * personagemAux = (*iteratorPersonagem);
			for(iteratorAtaque = personagemAux->listAttack.begin(); iteratorAtaque != personagemAux->listAttack.end(); iteratorAtaque++){
				if((*iteratorAtaque).second->tipoAtaque == tipoEscolhido){
					ataqueEscolhido = (*iteratorAtaque).second;
					printf("VILAO ataqueEscolhido: %s\n",ataqueEscolhido->nome.c_str());
					break;
				}
			}
	}

	for(iteratorPersonagem = listVilans.begin(); iteratorPersonagem < listVilans.end(); iteratorPersonagem++){
		(*iteratorPersonagem)->setCurrentAnimation(ataqueEscolhido->nome);
	}
	return (*iteratorAtaque).second;

	//return ((listVilans[0])->listAttack[0]);
}

GrupoViloes::~GrupoViloes(){
	// this->~GrupoPersonagens();
}

void GrupoViloes::calculaProbabilidades(){
	int levelMax = level->getLevelMax();

	if(levelMax == 0) {
		limitePAtaque = 50;
		if(limitePInteligencia > limitePDefesa){
			limitePInteligencia = 80;
			limitePDefesa = 100;
		}
		else {
			limitePInteligencia = 70;
			limitePDefesa = 100;
		}
	}
	else if(levelMax == 1){
		if(limitePAtaque > limitePDefesa){
			limitePAtaque = 30;
			limitePInteligencia = 80;
			limitePDefesa = 100;
		}
		else {
			limitePAtaque = 20;
			limitePInteligencia = 70;
			limitePDefesa = 100;
		}
	}
	else if(levelMax == 2){
		if(limitePAtaque > limitePInteligencia){
			limitePAtaque = 30;
			limitePInteligencia = 50;
			limitePDefesa = 100;
		}
		else {
			limitePAtaque = 20;
			limitePInteligencia = 50;
			limitePDefesa = 100;
		}
	}
	//printf("lPA %d lPI %d lPD %d\n",limitePAtaque,limitePInteligencia,limitePDefesa);
}

Level *GrupoViloes::calculaLevel(Level *level) {
	Level *levelAux = new Level(1,1,1);
	int levelMaior = level->getLevelMax();
	int levelTotalMocinhos = level->getAttackLevel() + level->getIntelligenceLevel() + level->getDefenseLevel();
	levelTotalMocinhos -= 3;

	if(levelTotalMocinhos == 0)
		return levelAux;

	switch (SDLBase::LEVEL_DIFICULDADE) {
	case 1:
		levelTotalMocinhos -= 1;
		if(levelTotalMocinhos == 0)
			return levelAux;
		break;
	case 3:
		levelMocinhos += 1;
		break;
	}

	if(levelMaior == 0) {
		limiteAtaque = 50;
		limiteInteligencia = 75;
		limiteDefesa = 100;
	}
	else if(levelMaior == 1){
		limiteAtaque = 25;
		limiteInteligencia = 75;
		limiteDefesa = 100;
	}
	else if(levelMaior == 2){
		limiteAtaque = 25;
		limiteInteligencia = 50;
		limiteDefesa = 100;
	}

	while(levelTotalMocinhos != 0){
		int pLevel = rand() % 100;
		if(pLevel <= limiteAtaque ){
			levelAux->setAttackLevel(levelAux->getAttackLevel() + 1);
			levelTotalMocinhos--;
			limiteAtaque -= 10;
			limiteInteligencia += 5;
		}
		else if(pLevel <= limiteInteligencia && pLevel > limiteAtaque){
			levelAux->setIntelligenceLevel(levelAux->getIntelligenceLevel() + 1);
			levelTotalMocinhos--;
			limiteAtaque += 5;
			limiteInteligencia -= 5;
		}
		else if(pLevel <= 100 && limiteDefesa > limiteInteligencia){
			levelAux->setIntelligenceLevel(levelAux->getIntelligenceLevel() + 1);
			levelTotalMocinhos--;
			limiteAtaque += 5;
			limiteInteligencia += 5;
		}
	}

	return levelAux;
}
