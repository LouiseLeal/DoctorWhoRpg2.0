/*
 * StateManager.cpp
 *
 *  Created on: Jun 7, 2013
 *      Author: Carol
 */


#include "../headers/StateManager.h"

StateManager::StateManager(){
	SDLBase::inicializaSDL();
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	SDLBase::strLanguage = ".xml";

	//loadGame
	loadGame();

	//inicializa os estados
	stateBatalha = new StateBatalha();
	stateCenario = new StateCenario();
	stateIntro = new StateIntro();
	stateSelecao = new StateSelecaoAID();
	stateCasaRose = new StateCasaRose();
	stateGameOver = new StateGameOver();
	stateMenu = new StateMenu();
	//stateDummie = new StateDummie();
	stateStatus = new StateStatus();
	stateCreditos = new StateCreditos();

	//load dos estados
	stateCasaRose->load(0);
	stateBatalha->load(0);
	stateCenario->load(0);
	stateIntro->load(0);
	stateSelecao->load(0);
	stateGameOver->load(0);
	stateMenu->load(0);
	//stateDummie->load(0);
	stateStatus->load(0);
	stateCreditos->load(0);

	//inicializa variaveis
	grupoMocinho = stateCenario->grupoCenario;
	grupoMocinho->listaItens.push_back(vetPossibleItens.front());
	//stateBatalha->setGrupoMocinhos(grupoMocinho);
	//stateSelecao->setGrupoCenario(grupoMocinho);
	//state cenario
	estadoAtual = ESTADO_MENU;
	stateMenu->begin();
	//stateCasaRose->begin(grupoMocinho);
	//stateCenario->begin();
	pilha = 0;
	frameStart = 0;
	frameEnd = 0;
	quit = false;
	deltaFrame = 0;

	//Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

StateManager::~StateManager(){
	SDLBase::finalizaSDL();
}

void StateManager::run(){
	quit = false;
	stateCasaRose->timer.start();
	while(!SDL_QuitRequested() && !quit){
		frameStart = SDL_GetTicks();

		switch (estadoAtual) {
		//estado para testes
		case ESTADO_DUMMIE:
			estadoAtual = stateDummie->update(deltaFrame);
			stateDummie->render();
			break;
		case ESTADO_CREDITOS:
			estadoAtual = stateCreditos->update(deltaFrame);
			if(estadoAtual == ESTADO_MENU)
				stateMenu->begin();
			stateCreditos->render();
			break;
		case ESTADO_STATUS:
			estadoAtual = stateStatus->update(deltaFrame);
			if(estadoAtual == ESTADO_CENARIO){
				stateCenario->begin();
			}
			else if(estadoAtual == ESTADO_SELECAO)
				stateSelecao->setGrupoCenario(grupoMocinho, ESTADO_STATUS);
			else if(estadoAtual == ESTADO_MENU)
				stateMenu->begin();
			stateStatus->render();
			break;
		//estado de game over
			case ESTADO_FIM:
				quit = true;
				stateBatalha->unload();
				break;
			case ESTADO_MENU:
				estadoAtual = stateMenu->update(deltaFrame);
				if(estadoAtual == ESTADO_INTRODUCAO)
					stateIntro->begin();
				else if(estadoAtual == ESTADO_CREDITOS)
					stateCreditos->begin();
				stateMenu->render();
				break;
		//estado de monolog da rose
			case ESTADO_INTRODUCAO:
				estadoAtual = stateIntro->update(deltaFrame);
				if(estadoAtual == ESTADO_CASAROSE){
					//stateCasaRose->timer.start();
					stateCasaRose->begin(grupoMocinho);
				}
				stateIntro->render();
				break;
		//estado de monolog da rose
			case ESTADO_CASAROSE:
				estadoAtual = stateCasaRose->update(deltaFrame);
				if(estadoAtual == ESTADO_CENARIO){
					stateCenario->begin();
				}
				stateCasaRose->render();
				break;
		//estado de andando por londres
			case ESTADO_CENARIO:
				estadoAtual = stateCenario->update(deltaFrame*1.2);
				stateCenario->render();
				if(estadoAtual == ESTADO_BATALHA) {
					if(grupoMocinho->vectorPersonagensBatalha.empty()){
						estadoAtual = ESTADO_SELECAO;
						stateSelecao->setGrupoCenario(grupoMocinho, ESTADO_BATALHA);
					}
					else
						stateBatalha->setGrupoMocinhos(grupoMocinho);
				}
				else if(estadoAtual == ESTADO_STATUS)
					stateStatus->begin(grupoMocinho);
				else if(estadoAtual == ESTADO_MENU)
					stateMenu->begin();
				else if(estadoAtual == ESTADO_CREDITOS)
					stateCreditos->begin();
				break;
			case ESTADO_SELECAO:
				estadoAtual = stateSelecao->update(deltaFrame);
				stateSelecao->render();
				if(estadoAtual == ESTADO_BATALHA)
					stateBatalha->setGrupoMocinhos(grupoMocinho);
				else if(estadoAtual == ESTADO_STATUS)
					stateStatus->begin(grupoMocinho);
				break;
		//estado de batalha
			case ESTADO_BATALHA:
				estadoAtual = stateBatalha->update(deltaFrame*1.2);
				stateBatalha->render();
				if(estadoAtual == ESTADO_BATALHA)
					stateBatalha->render();
				else if(estadoAtual == ESTADO_CENARIO)
					stateCenario->begin();
				else if(estadoAtual == ESTADOGAMEOVER)
					stateGameOver->begin();
				break;
		//estado de perda na batalha
			case ESTADO_GAME_OVER:
				estadoAtual = stateGameOver->update(deltaFrame);
				if(estadoAtual == ESTADO_SELECAO)
					stateSelecao->setGrupoCenario(grupoMocinho, ESTADO_BATALHA);
				stateGameOver->render();
				//restore the returnUpdate do gameover
				stateGameOver->returnUpdate = ESTADO_GAME_OVER;
				break;
		}
		SDLBase::updateScreen();

		frameEnd =  SDL_GetTicks();
		deltaFrame = frameEnd - frameStart;
		if (deltaFrame < SDLBase::FPS)
			SDL_Delay(SDLBase::FPS - deltaFrame);

	}
	SDL_Quit();
}

void StateManager::loadGame() {
	XMLDocument itensDoc;
	char strAux[90] = RESOURCE_PATH;
	strcat(strAux,"itens.xml");
	string filePath = strAux;//RESOURCE_PATH + "itens.xml";
	itensDoc.LoadFile(filePath.c_str());
	if(itensDoc.ErrorID() != 0){
		printf("Erro ao tentar abrir o xml %s. ErrodId: %d\n",filePath.c_str(),itensDoc.ErrorID());
		exit(1);
	}

	int hpEffect = 0;
	int xpEffect = 0;
	int attackEffect = 0;
	int inteligenceEffect = 0;
	int defenseEffect = 0;
	string nome;
	string descricao;
	//itens
	XMLNode *itensLista = itensDoc.RootElement();
	XMLNode *childIten;
	for(childIten = itensLista->FirstChildElement("iten"); childIten; childIten = childIten->NextSibling()){
		nome = childIten->FirstChildElement("nome")->GetText();
		descricao = childIten->FirstChildElement("descricao")->GetText();

		childIten->FirstChildElement("xpEffect")->QueryIntText(&xpEffect);
		childIten->FirstChildElement("hpEffect")->QueryIntText(&hpEffect);
		childIten->FirstChildElement("attackEffect")->QueryIntText(&attackEffect);
		childIten->FirstChildElement("inteligenceEffect")->QueryIntText(&inteligenceEffect);
		childIten->FirstChildElement("defenceEffect")->QueryIntText(&defenseEffect);

		Item *itemAux = new Item(nome, descricao, hpEffect, xpEffect, attackEffect,inteligenceEffect, defenseEffect);

		vetPossibleItens.push_back(itemAux);
	}
}
