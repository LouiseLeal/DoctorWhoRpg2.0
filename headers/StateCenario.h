/*
 * StateCenario.h
 *
 *  Created on: Jun 11, 2013
 *      Author: Carol
 */

#ifndef STATECENARIO_H_
#define STATECENARIO_H_

// #include "TileSet.h"
// #include "InputManager.h"
// #include "CaixaTexto.h"
// #include "TileMap.h"

#include "State.h"
#include "GrupoCenario.h"
#include "PersonagemInativo.h"


#define DESLOCAMENTO 4.0

class StateCenario : public State {
public:
	void load(int pilha);
	int unload();
	int update(int deltaFrame);
	void render();
	void processEvent();
	void begin();
	void end();


	GrupoCenario *grupoCenario;

	Sprite *background;
	TileMap *tileMap;
	TileSet *tileSet;

	int returnUpdate;

private:
	bool verificaColisao(int,int,int,int);
	void geraInativos();
	int limiteProbBatalha;

	Audio *sfxBackgroundMusic;
	Audio *sfxEnterBattle;

	Tempo timerTransicao;
	bool EM_ESPERA;

	int oldX;
	int oldY;


	int pbBatalhaEsq;
	int pbBatalhaDir;
	int pbBatalhaFre;
	int pbBatalhaCos;

	int limiteMapaLeft;
	int limiteMapaBotton;

	vector<PersonagemInativo*> vetPersonagensInativos;

	bool renderCaixaTexto;

	CaixaTexto *caixaDialogo;

	struct TILE_BATALHA{
		int x;
		int y;
	};

	vector<TILE_BATALHA> vetTilesBatalha;

	int currentFrameFadeBatalha;
	int maxFrameFadeBatalha;
	int somaFrameFadeBatalha;
	int ultimoFrame;

	Sprite *spriteFadeBatalha;

	int time;
	int frameSkip;
	int frameTime;

	int TARDIS_TILE_X; //tile 37
	int TARDIS_TILE_Y; //tile 32
	bool ENTRA_TARDIS;
	Tempo timerTARDIS;
	int waitTARDIS;
	int ultimoTempoTARDIS;
	int currentFrameTARDIS;
	int maxFrameTARDIS;
	int somaFrameTARDIS;
	Sprite *spriteToBeContinued;

	bool tocaIntroBatalha;
};

#endif /* STATECENARIO_H_ */
