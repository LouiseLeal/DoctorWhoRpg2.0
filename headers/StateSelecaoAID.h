/*
 * StateSelecaoAID.h
 *
 *  Created on: Jul 1, 2013
 *      Author: Carol
 */

#ifndef STATESELECAOAID_H_
#define STATESELECAOAID_H_


#include "State.h"
#include "GrupoCenario.h"
// #include "InputManager.h"
// #include "Text.h"
// #include "Audio.h"

class StateSelecaoAID : public State {
public:
	void load(int pilha);
	int unload();
	int update(int deltaFrame);
	void render();

	void setGrupoCenario(GrupoCenario *grupoMocinhos, int estado_retorno_ok);

	void processEvents();

	void populaTextoAid();
	void populaTextoGrupo(int indicePersonagem);


	enum{
			ESTADO_AID,
			ESTADO_GRUPO,
			ESTADO_OK,
		};

	GrupoCenario *grupoCenario;

	Sprite *background;
	Sprite *botao;
	Sprite *botaoSelecionado;

	vector<Sprite*> vetSpriteAid;
	vector<Sprite*> vetSpriteGrupo;

	//vector<PersonagemAtivo*> vetGrupoEscolhido;

	bool btSelecionado;

	int estadoAtual;

	int btX, btY;
	int aidX, aidY;
	int grupoX,grupoY;
	int setaX, setaY;

	int valorAtaque;
	int valorInteligencia;
	int valorDefesa;
	int valorLife;

	int aidEscolhido;

	bool levelDisponivel;
//
//	int ataqueEscolhido;
//	int inteligenciaEscolhido;
//	int defesaEscolhido;

	//sprites
	Sprite * spriteAid;
	Sprite * spriteAidSelecionado;
	Sprite * spriteSeta;
	Sprite * spriteBlock;
	Sprite * iconeLevelDisponivel;
	Tempo timerLevelDisponivel;

	//textos
	vector<Text*> textoAid;
	vector<Text*> textoGrupo;
	vector<Text*> textoMultiplicadores;

	Audio *sfxBlip;
	Audio *sfxSelectNot;
	Audio *sfxBackground;

	int ESTADO_RETORNO_OK;
	int returnUpdate;

	vector<bool> vetSelecionados;

	vector<int> vetAid;
	vector<int> vetGroup;


	int aidXIntervalo;
	int groupXIntervalo;
};


#endif /* STATESELECAOAID_H_ */
