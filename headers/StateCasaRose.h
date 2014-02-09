/*
 * StateCasaRose.h
 *
 *  Created on: Jul 11, 2013
 *      Author: Carol
 */

#ifndef STATECASAROSE_H_
#define STATECASAROSE_H_

// #include "TileSet.h"
// #include "Tempo.h" -- cena
// #include "InputManager.h" -- cena
// #include "InputManager.h" -- cena// #include "Types.h"
// #include "CaixaTexto.h"
// #include "TileMap.h"

#include "State.h"
#include "GrupoCenario.h"
#include "Cena.h"
#include "math.h" // colocar no sdlbase



class StateCasaRose : public State {
public:
	void load(int pilha);
	int unload();
	int update(int deltaFrame);
	void render();
	void processEvents();
	void begin(GrupoCenario *grupoMocinhos);

	TileMap *tileMap;
	TileSet *tileSet;
	Tempo timer;

	Sprite *background;
	Sprite *tardisBox;
	Sprite *rostoPersonagem;
	Sprite *spriteTardisFade;

	CaixaTexto *caixaDialogo;
	string fala;

	GrupoCenario *grupoCenario;
	Cena *cena;

	int time;
	int frameSkip;
	int frameTime;

	int currentFrameTardis;
	int maxFrameTardis;
	int somaFrameTardis;

	FRAME currentFrame;

	int contaTempo;
	int returnUpdate;
	bool renderCaixaTexto;
	bool seguraRender;

	PersonagemAtivo *fantasma;

	Audio *sfxBackground;
	Audio *sfxPorta;
	Audio *sfxTardisLanding;
	bool ligaMusica;
	Text *txtTARDIS;
	Text *txtTimeAndRelative;
};

#endif /* STATECASAROSE_H_ */
