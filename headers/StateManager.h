/*
 * StateManager.h
 *
 *  Created on: Jun 7, 2013
 *      Author: Carol
 */

#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_

// #include "SDLBase.h"
// #include "State.h"
#include "StateBatalha.h"
#include "StateCenario.h"
#include "StateIntro.h"
#include "StateSelecaoAID.h"
#include "StateCasaRose.h"
#include "StateGameOver.h"
#include "StateMenu.h"
#include "StateDummie.h"
// #include "Item.h"
// #include "Cena.h"
#include "StateStatus.h"
#include "StateCreditos.h"

class StateManager{
public:
	StateManager();
	~StateManager();
	void loadGame();

	void run();

private:

	int pilha;
	int deltaFrame;
	int frameStart;
	int frameEnd;
	bool quit;

	StateBatalha *stateBatalha;
	StateCenario *stateCenario;
	StateIntro *stateIntro;
	StateSelecaoAID *stateSelecao;
	StateCasaRose *stateCasaRose;
	StateGameOver *stateGameOver;
	StateMenu *stateMenu;
	StateDummie *stateDummie;
	StateStatus *stateStatus;
	StateCreditos *stateCreditos;
	int estadoAtual;

	vector<Item*> vetPossibleItens;

	GrupoCenario *grupoMocinho;
};


#endif /* STATEMANAGER_H_ */
