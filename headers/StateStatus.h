/*
 * StateStatus.h
 *
 *  Created on: Jul 21, 2013
 *      Author: Carol
 */

#ifndef STATESTATUS_H_
#define STATESTATUS_H_

// #include "TileMap.h"
// #include "TileSet.h"
// #include "Item.h"
// #include "Types.h"
// #include "TextOpcoes.h"
// #include "InputManager.h"

#include "State.h"
#include "GrupoCenario.h"
#include "Tempo.h"
#include "EstruturaStatus.h"
#include "EstruturaItem.h"


class StateStatus : public State {
public:
	void load(int pilha);
	void begin(GrupoCenario *grupoMocinhos);
	int unload();
	int update(int deltaFrame);
	void render();
	void processEvents();

	Tempo timer;

	Sprite *background;

	struct itemDados {
		string nome;
		int quantidade;
	};

	TextOpcoes *opcoesInicial;
	TextOpcoes *opcoesPersonagens;
	TextOpcoes *opcoesItens;
	vector<itemDados> listItens;
	GrupoCenario *grupoMocinhos;
	Sprite *spriteSeta;


private:
	void getListaItens();
	void getListaPersonagens();

	Audio *sfxBlip;

	int box1X;
	int box1Y;

	int box2X;
	int box2Y;

	int box3X;
	int box3Y;

	EstruturaStatus *estruturaStatus;
	EstruturaItem *estruturaItem;

	int renderColuna;
	int renderDados;
	bool renderSetaInicial;
	bool renderSetaSecundario;

	// int personagemEscolhido;
	// int itemEscolhido;

	enum {
		RENDER1,
		RENDER2,
		RENDER3
	};
	enum {
		RENDER_Itens,
		RENDER_Personagens,
		RENDER_AID,
	};

	int returnUpdate;


	Audio *sfxBackground;
};


#endif /* STATESTATUS_H_ */
